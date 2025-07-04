#include "pch.h"
#include "CImageProcessing.h"

Mat CImageProcessing::RGB_2_Gray(Mat src)
{
    Mat result;
    //RGBתGRAYͼ��
    cvtColor(src, result, cv::COLOR_BGR2GRAY);
    return result;
}

Mat CImageProcessing::BinarizeImage(const Mat& src)
{
    Mat dst;
    
    // �������ͼ��Ϊ�գ����ؿ�Mat
    if (src.empty()) {
        return dst;
    }
    
    // Ԥ������˹ģ��ȥ��
    Mat blurred;
    GaussianBlur(src, blurred, Size(5, 5), 0);
    
    // ת����HSVɫ�ʿռ䣬���ʺ�ˮ����ɫ����
    Mat hsv;
    cvtColor(blurred, hsv, COLOR_BGR2HSV);
    
    // ��ȡVͨ�������ȣ�����ˮ������״����������
    vector<Mat> hsvChannels;
    split(hsv, hsvChannels);
    Mat valueChannel = hsvChannels[2];
    
    // ʹ������Ӧ��ֵ�����õش�����ղ����ȵ�ˮ��ͼƬ
    Mat adaptiveResult;
    adaptiveThreshold(valueChannel, adaptiveResult, 255, 
                     ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 11, 2);
    
    // ���OTSU�������ȫ��������ֵ
    Mat otsuResult;
    threshold(valueChannel, otsuResult, 0, 255, THRESH_BINARY | THRESH_OTSU);
    
    // ������Ӧ��ֵ��OTSU������а�λ�����㣬��ø��õ�Ч��
    bitwise_and(adaptiveResult, otsuResult, dst);
    
    // ��̬ѧ������ȥ��С��㣬���С�׶�
    Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
    morphologyEx(dst, dst, MORPH_OPEN, kernel);   // �����㣺ȥ��С���
    morphologyEx(dst, dst, MORPH_CLOSE, kernel);  // �����㣺���С�׶�
    
    // ʹ����ͨ�����ȥ��С�ĺ�ɫ����С�ڵ㣩
    Mat labels, stats, centroids;
    Mat invertedDst = ~dst; // ��תͼ��ʹ�ڵ��ɰ�ɫ��ͨ��
    int numComponents = connectedComponentsWithStats(invertedDst, labels, stats, centroids);
    
    // ����������ͨ������������������1��ʼ��
    for(int i = 1; i < numComponents; i++) {
        int area = stats.at<int>(i, CC_STAT_AREA);
        
        // �����ͨ�����С����ֵ�������ԭͼ���Ƴ�����Ϊ��ɫ��
        if(area < 30) { // �ɵ������������С��100���صĺ�ɫ���򽫱��Ƴ�
            dst.setTo(255, labels == i);
        }
    }
    
    // ��ѡ���ٴν�����΢����̬ѧ������ƽ����Ե
    Mat finalKernel = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
    morphologyEx(dst, dst, MORPH_CLOSE, finalKernel);
    
    return dst;
}