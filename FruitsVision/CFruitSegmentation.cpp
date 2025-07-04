#include "pch.h"
#include "CFruitSegmentation.h"

// 主要分割函数实现
vector<Mat> CFruitSegmentation::SegmentFruits(const Mat& inputImage)
{
    vector<Mat> fruitImages;

    // 1. 图像预处理
    Mat preprocessed = PreprocessImage(inputImage);

    // 2. 颜色分割
    Mat mask = ColorBasedSegmentation(preprocessed);

    // 3. 形态学操作
    Mat morphed = MorphologyOperation(mask);

    // 4. 轮廓检测
    vector<vector<Point>> contours = FindFruitContours(morphed);

    // 5. 提取单个水果
    fruitImages = ExtractIndividualFruits(inputImage, contours);

    return fruitImages;
}

// 图像预处理 - 优化高斯模糊参数
Mat CFruitSegmentation::PreprocessImage(const Mat& src)
{
    Mat result;

    // 调整高斯模糊核大小，减少过度模糊
    GaussianBlur(src, result, Size(3, 3), 0);

    // 可选：直方图均衡化增强对比度
    vector<Mat> channels;
    cvtColor(result, result, COLOR_BGR2YUV);
    split(result, channels);
    equalizeHist(channels[0], channels[0]);
    merge(channels, result);
    cvtColor(result, result, COLOR_YUV2BGR);

    return result;
}

// 基于颜色的分割 - 优化HSV颜色范围
Mat CFruitSegmentation::ColorBasedSegmentation(const Mat& src)
{
    Mat hsv, mask, finalMask;
    cvtColor(src, hsv, COLOR_BGR2HSV);

    // 定义不同水果的HSV颜色范围 - 扩大范围以提高检测率
    // 红色水果（苹果、草莓、樱桃等）- 扩大饱和度和亮度范围
    Mat redMask1, redMask2;
    inRange(hsv, Scalar(0, 30, 30), Scalar(15, 255, 255), redMask1);
    inRange(hsv, Scalar(165, 30, 30), Scalar(180, 255, 255), redMask2);
    Mat redMask = redMask1 | redMask2;

    // 橙色水果（橘子、橙子、柿子等）- 调整范围覆盖更多橙色变化
    Mat orangeMask;
    inRange(hsv, Scalar(8, 40, 40), Scalar(28, 255, 255), orangeMask);

    // 黄色水果（香蕉、柠檬、黄苹果等）- 扩大范围
    Mat yellowMask;
    inRange(hsv, Scalar(15, 30, 50), Scalar(40, 255, 255), yellowMask);

    // 绿色水果（青苹果、青葡萄、猕猴桃等）- 调整范围
    Mat greenMask;
    inRange(hsv, Scalar(30, 25, 30), Scalar(90, 255, 255), greenMask);

    // 紫色/蓝色水果（葡萄、蓝莓、茄子等）- 扩大范围
    Mat purpleMask;
    inRange(hsv, Scalar(110, 30, 30), Scalar(160, 255, 255), purpleMask);

    // 棕色水果（猕猴桃皮、椰子等）- 新增
    Mat brownMask;
    inRange(hsv, Scalar(8, 20, 20), Scalar(25, 180, 200), brownMask);

    // 合并所有颜色掩膜
    finalMask = redMask | orangeMask | yellowMask | greenMask | purpleMask | brownMask;

    return finalMask;
}

// 形态学操作 - 优化操作顺序和核大小
Mat CFruitSegmentation::MorphologyOperation(const Mat& src)
{
    Mat result;

    // 先进行中值滤波去除椒盐噪声
    medianBlur(src, result, 3);

    // 创建更小的结构元素用于开运算
    Mat kernel_open = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));

    // 开运算：去除小噪点，但保持主要形状
    morphologyEx(result, result, MORPH_OPEN, kernel_open, Point(-1, -1), 1);

    // 创建适中的结构元素用于闭运算
    Mat kernel_close = getStructuringElement(MORPH_ELLIPSE, Size(7, 7));

    // 闭运算：填充内部小孔
    morphologyEx(result, result, MORPH_CLOSE, kernel_close, Point(-1, -1), 1);

    // 最后进行轻微的膨胀操作，确保轮廓完整
    Mat kernel_dilate = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
    dilate(result, result, kernel_dilate, Point(-1, -1), 1);

    return result;
}

// 轮廓检测和筛选 - 优化筛选条件
vector<vector<Point>> CFruitSegmentation::FindFruitContours(const Mat& mask)
{
    vector<vector<Point>> contours, filteredContours;
    vector<Vec4i> hierarchy;

    // 查找轮廓
    findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // 计算图像总面积，用于动态调整阈值
    double imageArea = mask.rows * mask.cols;
    double minAreaThreshold = imageArea * 0.001;  // 最小面积为图像的0.1%
    double maxAreaThreshold = imageArea * 0.5;    // 最大面积为图像的50%

    // 筛选轮廓：基于面积和形状
    for (const auto& contour : contours)
    {
        double area = contourArea(contour);
        double perimeter = arcLength(contour, true);

        // 动态面积过滤
        if (area < max(500.0, minAreaThreshold) || area > maxAreaThreshold)
            continue;

        // 周长检查，避免除零
        if (perimeter < 10) continue;

        // 计算圆度（4π*面积/周长²），接近1表示更圆
        double circularity = 4 * CV_PI * area / (perimeter * perimeter);

        // 计算矩形度（轮廓面积/边界矩形面积）
        Rect boundingRect = cv::boundingRect(contour);
        double rectangularity = area / (boundingRect.width * boundingRect.height);

        // 计算长宽比
        double aspectRatio = (double)boundingRect.width / boundingRect.height;

        // 保留形状合理的轮廓（放宽圆度要求，增加矩形度和长宽比检查）
        if (circularity > 0.2 &&           // 降低圆度要求
            rectangularity > 0.3 &&        // 轮廓应该相对填满边界矩形
            aspectRatio > 0.3 && aspectRatio < 3.0)  // 长宽比不能太极端
        {
            filteredContours.push_back(contour);
        }
    }

    return filteredContours;
}

// 提取单个水果 - 优化边界扩展
// 改进的水果提取函数 - 避免尺寸调整影响分割
vector<Mat> CFruitSegmentation::ExtractIndividualFruits(const Mat& src,
    const vector<vector<Point>>& contours)
{
    vector<Mat> fruitImages;

    for (size_t i = 0; i < contours.size(); i++)
    {
        // 计算边界矩形
        Rect boundingRect = cv::boundingRect(contours[i]);

        // 固定边界扩展，不受显示尺寸影响
        int margin = 15;  // 固定边距

        // 安全地扩展边界
        int x = max(0, boundingRect.x - margin);
        int y = max(0, boundingRect.y - margin);
        int width = min(src.cols - x, boundingRect.width + 2 * margin);
        int height = min(src.rows - y, boundingRect.height + 2 * margin);

        Rect expandedRect(x, y, width, height);

        // 提取ROI（原始尺寸，不进行任何缩放）
        Mat fruitROI = src(expandedRect).clone();

        // 创建掩膜
        Mat mask = Mat::zeros(expandedRect.size(), CV_8UC1);
        vector<vector<Point>> adjustedContour(1);

        // 调整轮廓坐标到ROI坐标系
        for (const Point& pt : contours[i])
        {
            Point adjustedPt(pt.x - expandedRect.x, pt.y - expandedRect.y);
            adjustedPt.x = max(0, min(adjustedPt.x, expandedRect.width - 1));
            adjustedPt.y = max(0, min(adjustedPt.y, expandedRect.height - 1));
            adjustedContour[0].push_back(adjustedPt);
        }

        // 填充轮廓
        fillPoly(mask, adjustedContour, Scalar(255));

        // 应用掩膜
        Mat maskedFruit;
        fruitROI.copyTo(maskedFruit, mask);

        // 存储原始尺寸的水果图像
        fruitImages.push_back(maskedFruit);
    }

    return fruitImages;
}

// 测量水果像素值 - 添加更多测量指标
void CFruitSegmentation::MeasureFruit(const Mat& fruitImage, const vector<Point>& contour,
    int& pixelCount, double& area, double& perimeter)
{
    // 计算轮廓面积
    area = contourArea(contour);

    // 计算轮廓周长
    perimeter = arcLength(contour, true);

    // 计算像素数量
    Mat mask = Mat::zeros(fruitImage.size(), CV_8UC1);
    vector<vector<Point>> contours_temp(1, contour);
    fillPoly(mask, contours_temp, Scalar(255));
    pixelCount = countNonZero(mask);

    // 可选：添加更多测量指标
    // 圆度
    double circularity = 4 * CV_PI * area / (perimeter * perimeter);

    // 边界矩形
    Rect boundingRect = cv::boundingRect(contour);
    double aspectRatio = (double)boundingRect.width / boundingRect.height;

    // 可以将这些值通过引用参数返回，或者存储在类成员变量中
}