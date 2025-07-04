#pragma once
class CFruitSegmentation
{
public:
    // 主要的水果分割函数
    vector<Mat> SegmentFruits(const Mat& inputImage);
    
    // 图像预处理
    Mat PreprocessImage(const Mat& src);
    
    // 基于颜色的分割
    Mat ColorBasedSegmentation(const Mat& src);
    
    // 轮廓检测和筛选
    vector<vector<Point>> FindFruitContours(const Mat& mask);
    
    // 提取单个水果
    vector<Mat> ExtractIndividualFruits(const Mat& src, const vector<vector<Point>>& contours);
    
    // 测量水果像素值
    void MeasureFruit(const Mat& fruitImage, const vector<Point>& contour, 
                      int& pixelCount, double& area, double& perimeter);

private:
    // 形态学操作
    Mat MorphologyOperation(const Mat& src);
};
