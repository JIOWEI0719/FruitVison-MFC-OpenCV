#include "pch.h"
#include "CCalibrate.h"

CCalibrate::CCalibrate() : m_pixelToMmRatio(1.0), m_isCalibrated(false) {}

// 网格自动校准
bool CCalibrate::CalibrateWithGrid(const cv::Mat& image, double gridSpacingMm )
{
    try
    {
        cv::Mat gray, binary;
        cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

        // 检测网格线
        cv::Mat edges;
        cv::Canny(gray, edges, 50, 150);

        // 检测直线
        std::vector<cv::Vec4i> lines;
        cv::HoughLinesP(edges, lines, 1, CV_PI / 180, 50, 30, 10);

        if (lines.size() < 4) {
            return false; // 检测到的线条太少
        }

        // 分离水平和垂直线
        std::vector<cv::Vec4i> horizontalLines, verticalLines;
        for (const auto& line : lines) {
            int dx = abs(line[2] - line[0]);
            int dy = abs(line[3] - line[1]);

            if (dx > dy * 2) {
                horizontalLines.push_back(line);
            }
            else if (dy > dx * 2) {
                verticalLines.push_back(line);
            }
        }

        // 计算网格间距（像素）
        double avgHorizontalSpacing = CalculateAverageSpacing(horizontalLines, true);
        double avgVerticalSpacing = CalculateAverageSpacing(verticalLines, false);

        if (avgHorizontalSpacing > 0 && avgVerticalSpacing > 0) {
            // 使用两个方向的平均值
            double avgSpacing = (avgHorizontalSpacing + avgVerticalSpacing) / 2.0;
            m_pixelToMmRatio = gridSpacingMm / avgSpacing;
            m_isCalibrated = true;
            return true;
        }

        return false;
    }
    catch (...) {
        return false;
    }
}

// 手动校准
bool CCalibrate::ManualCalibrate(cv::Point2f point1, cv::Point2f point2, double actualDistanceMm)
{
    double pixelDistance = cv::norm(point2 - point1);
    if (pixelDistance > 0 && actualDistanceMm > 0) {
        m_pixelToMmRatio = actualDistanceMm / pixelDistance;
        m_isCalibrated = true;
        return true;
    }
    return false;
}

// 设置已知校准比例
void CCalibrate::SetCalibrationRatio(double pixelToMmRatio) {
    m_pixelToMmRatio = pixelToMmRatio;
    m_isCalibrated = true;
}

// 获取校准状态
bool CCalibrate::IsCalibrated() const { return m_isCalibrated; }
double CCalibrate::GetPixelToMmRatio() const { return m_pixelToMmRatio; }

// 集成校准功能的轮廓筛选函数
std::vector<std::vector<cv::Point>> CCalibrate::FilterContoursWithCalibration(
    const std::vector<std::vector<cv::Point>>& contours,
    double minAreaThreshold,
    double maxAreaThreshold,
    bool useRealUnits)  // 是否使用实际单位进行筛选
{
    std::vector<std::vector<cv::Point>> filteredContours;

    // 如果已校准且要求使用实际单位，则转换阈值
    double actualMinArea = minAreaThreshold;
    double actualMaxArea = maxAreaThreshold;

    if (m_isCalibrated && useRealUnits) {
        // 将mm²转换为像素²
        double pixelAreaRatio = 1.0 / (m_pixelToMmRatio * m_pixelToMmRatio);
        actualMinArea = minAreaThreshold * pixelAreaRatio;
        actualMaxArea = maxAreaThreshold * pixelAreaRatio;
    }

    // 筛选轮廓：基于面积和形状
    for (const auto& contour : contours)
    {
        double area = cv::contourArea(contour);
        double perimeter = cv::arcLength(contour, true);

        // 动态面积过滤
        if (area < std::max(500.0, actualMinArea) || area > actualMaxArea)
            continue;

        // 周长检查，避免除零
        if (perimeter < 10) continue;

        // 计算圆度（4π*面积/周长²），接近1表示更圆
        double circularity = 4 * CV_PI * area / (perimeter * perimeter);

        // 计算矩形度（轮廓面积/边界矩形面积）
        cv::Rect boundingRect = cv::boundingRect(contour);
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

// 获取单个轮廓的校准测量结果
CalibratedMeasurements CCalibrate::GetCalibratedMeasurementsFromContour(const std::vector<cv::Point>& contour)
{
    CalibratedMeasurements result;

    // 基本测量
    double area = cv::contourArea(contour);
    double perimeter = cv::arcLength(contour, true);

    // 边界矩形
    cv::Rect boundingRect = cv::boundingRect(contour);

    // 计算椭圆拟合
    double majorAxis = 0, minorAxis = 0;
    if (contour.size() >= 5) {
        cv::RotatedRect ellipse = cv::fitEllipse(contour);
        majorAxis = std::max(ellipse.size.width, ellipse.size.height);
        minorAxis = std::min(ellipse.size.width, ellipse.size.height);
    }

    // 保存原始像素值
    result.areaPixels = area;
    result.perimeterPixels = perimeter;
    result.majorAxisPixels = majorAxis;
    result.minorAxisPixels = minorAxis;

    // 计算形状参数
    result.circularity = 4 * CV_PI * area / (perimeter * perimeter);
    result.rectangularity = area / (boundingRect.width * boundingRect.height);
    result.aspectRatio = (double)boundingRect.width / boundingRect.height;

    // 计算横截面积
    result.crossSectionAreaPixels = CalculateCrossSectionArea(area, minorAxis, result.circularity);

    // 如果已校准，转换为实际单位
    if (m_isCalibrated) {
        result.areaSquareMm = area * m_pixelToMmRatio * m_pixelToMmRatio;
        result.perimeterMm = perimeter * m_pixelToMmRatio;
        result.majorAxisMm = majorAxis * m_pixelToMmRatio;
        result.minorAxisMm = minorAxis * m_pixelToMmRatio;
        result.crossSectionAreaSquareMm = result.crossSectionAreaPixels * m_pixelToMmRatio * m_pixelToMmRatio;
    }
    else {
        // 未校准时返回像素值
        result.areaSquareMm = area;
        result.perimeterMm = perimeter;
        result.majorAxisMm = majorAxis;
        result.minorAxisMm = minorAxis;
        result.crossSectionAreaSquareMm = result.crossSectionAreaPixels;
    }

    return result;
}

// 改进的横截面积计算
double CCalibrate::CalculateCrossSectionArea(double areaPixels, double minorAxisPixels, double circularity)
{
    //// 方法1：等效圆面积
    //double equivalentRadius = sqrt(areaPixels / CV_PI);
    //double method1 = CV_PI * equivalentRadius * equivalentRadius;

    // 方法2：短轴圆面积加圆度修正（推荐用于红枣）
    if (minorAxisPixels > 0) {
        double radius = minorAxisPixels / 2.0;
        double method2 = CV_PI * radius * radius * circularity;
        return method2;
    }

    //// 方法3：直接使用轮廓面积
    //return areaPixels;
}

// 批量处理轮廓并返回校准后的测量结果
std::vector<CalibratedMeasurements> CCalibrate::ProcessContoursWithCalibration(
    const std::vector<std::vector<cv::Point>>& contours,
    double minAreaThresholdMm2,    // 最小面积阈值(mm²)
    double maxAreaThresholdMm2)   // 最大面积阈值(mm²)
{
    std::vector<CalibratedMeasurements> results;

    // 先筛选轮廓
    std::vector<std::vector<cv::Point>> filteredContours = FilterContoursWithCalibration(
        contours, minAreaThresholdMm2, maxAreaThresholdMm2, true);

    // 对每个筛选后的轮廓进行测量
    for (const auto& contour : filteredContours) {
        CalibratedMeasurements measurement = GetCalibratedMeasurementsFromContour(contour);
        results.push_back(measurement);
    }

    return results;
}

// 格式化输出函数
CString CCalibrate::FormatMeasurement(double value, const CString& unit, bool isCalibrated) const
{
    CString result;
    if (isCalibrated) {
        result.Format(_T("%.2f %s"), value, unit);
    }
    else {
        result.Format(_T("%.2f px%s"), value, unit.IsEmpty() ? _T("") : _T(" (uncalibrated)"));
    }
    return result;
}

    // 计算平均间距的辅助函数
    double CCalibrate::CalculateAverageSpacing(const std::vector<cv::Vec4i>& lines, bool isHorizontal)
    {
        if (lines.size() < 2) return 0;

        std::vector<int> positions;
        for (const auto& line : lines) {
            if (isHorizontal) {
                positions.push_back((line[1] + line[3]) / 2); // Y坐标
            }
            else {
                positions.push_back((line[0] + line[2]) / 2); // X坐标
            }
        }

        std::sort(positions.begin(), positions.end());

        std::vector<int> spacings;
        for (size_t i = 1; i < positions.size(); i++) {
            int spacing = positions[i] - positions[i - 1];
            if (spacing > 10) { // 过滤太小的间距
                spacings.push_back(spacing);
            }
        }

        if (spacings.empty()) return 0;

        // 计算平均间距
        double sum = 0;
        for (int spacing : spacings) {
            sum += spacing;
        }
        return sum / spacings.size();
    }