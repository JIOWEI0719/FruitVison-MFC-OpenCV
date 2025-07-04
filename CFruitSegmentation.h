#pragma once
class CFruitSegmentation
{
public:
    // ��Ҫ��ˮ���ָ��
    vector<Mat> SegmentFruits(const Mat& inputImage);
    
    // ͼ��Ԥ����
    Mat PreprocessImage(const Mat& src);
    
    // ������ɫ�ķָ�
    Mat ColorBasedSegmentation(const Mat& src);
    
    // ��������ɸѡ
    vector<vector<Point>> FindFruitContours(const Mat& mask);
    
    // ��ȡ����ˮ��
    vector<Mat> ExtractIndividualFruits(const Mat& src, const vector<vector<Point>>& contours);
    
    // ����ˮ������ֵ
    void MeasureFruit(const Mat& fruitImage, const vector<Point>& contour, 
                      int& pixelCount, double& area, double& perimeter);

private:
    // ��̬ѧ����
    Mat MorphologyOperation(const Mat& src);
};
