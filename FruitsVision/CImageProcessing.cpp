#include "pch.h"
#include "CImageProcessing.h"

Mat CImageProcessing::RGB_2_Gray(Mat src)
{
    Mat result;
    //RGB转GRAY图像
    cvtColor(src, result, cv::COLOR_BGR2GRAY);
    return result;
}

Mat CImageProcessing::BinarizeImage(const Mat& src)
{
    Mat dst;
    
    // 如果输入图像为空，返回空Mat
    if (src.empty()) {
        return dst;
    }
    
    // 预处理：高斯模糊去噪
    Mat blurred;
    GaussianBlur(src, blurred, Size(5, 5), 0);
    
    // 转换到HSV色彩空间，更适合水果颜色分析
    Mat hsv;
    cvtColor(blurred, hsv, COLOR_BGR2HSV);
    
    // 提取V通道（明度），对水果的形状轮廓更敏感
    vector<Mat> hsvChannels;
    split(hsv, hsvChannels);
    Mat valueChannel = hsvChannels[2];
    
    // 使用自适应阈值，更好地处理光照不均匀的水果图片
    Mat adaptiveResult;
    adaptiveThreshold(valueChannel, adaptiveResult, 255, 
                     ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 11, 2);
    
    // 结合OTSU方法获得全局最优阈值
    Mat otsuResult;
    threshold(valueChannel, otsuResult, 0, 255, THRESH_BINARY | THRESH_OTSU);
    
    // 将自适应阈值和OTSU结果进行按位与运算，获得更好的效果
    bitwise_and(adaptiveResult, otsuResult, dst);
    
    // 形态学操作：去除小噪点，填充小孔洞
    Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
    morphologyEx(dst, dst, MORPH_OPEN, kernel);   // 开运算：去除小噪点
    morphologyEx(dst, dst, MORPH_CLOSE, kernel);  // 闭运算：填充小孔洞
    
    // 使用连通域分析去除小的黑色区域（小黑点）
    Mat labels, stats, centroids;
    Mat invertedDst = ~dst; // 反转图像，使黑点变成白色连通域
    int numComponents = connectedComponentsWithStats(invertedDst, labels, stats, centroids);
    
    // 遍历所有连通域（跳过背景，从索引1开始）
    for(int i = 1; i < numComponents; i++) {
        int area = stats.at<int>(i, CC_STAT_AREA);
        
        // 如果连通域面积小于阈值，将其从原图中移除（设为白色）
        if(area < 30) { // 可调整参数：面积小于100像素的黑色区域将被移除
            dst.setTo(255, labels == i);
        }
    }
    
    // 可选：再次进行轻微的形态学操作以平滑边缘
    Mat finalKernel = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
    morphologyEx(dst, dst, MORPH_CLOSE, finalKernel);
    
    return dst;
}