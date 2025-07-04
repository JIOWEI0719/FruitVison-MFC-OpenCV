#pragma once
// 校准测量结果结构体
struct CalibratedMeasurements {
    double areaSquareMm;        // 面积(mm²)
    double perimeterMm;         // 周长(mm)
    double circularity;         // 圆度(无单位)
    double majorAxisMm;         // 长轴(mm)
    double minorAxisMm;         // 短轴(mm)
    double crossSectionAreaSquareMm; // 横截面积(mm²)
    double rectangularity;      // 矩形度
    double aspectRatio;         // 长宽比

    // 原始像素值
    double areaPixels;
    double perimeterPixels;
    double majorAxisPixels;
    double minorAxisPixels;
    double crossSectionAreaPixels;
};

class CCalibrate
{
public:
    double m_pixelToMmRatio;  // 像素到毫米的转换比例
    bool m_isCalibrated;      // 是否已校准

public:
    CCalibrate();

    // 网格自动校准
    bool CalibrateWithGrid(const cv::Mat& image, double gridSpacingMm = 10.0);

    // 手动校准
    bool ManualCalibrate(cv::Point2f point1, cv::Point2f point2, double actualDistanceMm);

    // 设置已知校准比例
    void SetCalibrationRatio(double pixelToMmRatio);

    // 获取校准状态
    bool IsCalibrated() const;
    double GetPixelToMmRatio() const;

    // 集成校准功能的轮廓筛选函数
    std::vector<std::vector<cv::Point>> FilterContoursWithCalibration(
        const std::vector<std::vector<cv::Point>>& contours,
        double minAreaThreshold ,
        double maxAreaThreshold ,
        bool useRealUnits );

    // 获取单个轮廓的校准测量结果
    CalibratedMeasurements GetCalibratedMeasurementsFromContour(const std::vector<cv::Point>& contour);

    // 改进的横截面积计算
    double CalculateCrossSectionArea(double areaPixels, double minorAxisPixels, double circularity);

    // 批量处理轮廓并返回校准后的测量结果
    std::vector<CalibratedMeasurements> ProcessContoursWithCalibration(
        const std::vector<std::vector<cv::Point>>& contours,
        double minAreaThresholdMm2 = 50.0,    // 最小面积阈值(mm²)
        double maxAreaThresholdMm2 = 500.0);

    // 格式化输出函数
    CString FormatMeasurement(double value, const CString& unit, bool isCalibrated) const;

private:
    // 计算平均间距的辅助函数
    double CalculateAverageSpacing(const std::vector<cv::Vec4i>& lines, bool isHorizontal);

};

