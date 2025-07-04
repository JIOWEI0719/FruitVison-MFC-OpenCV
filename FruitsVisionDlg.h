
// FruitsVisionDlg.h: 头文件
//

#include "DataInterface.h"
#include "CImageProcessing.h"
#include "CFruitSegmentation.h"

#pragma once


// CFruitsVisionDlg 对话框
class CFruitsVisionDlg : public CDialogEx
{
// 构造
public:
	CFruitsVisionDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FRUITSVISION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedSelect();
	//afx_msg void OnLvnItemchangedList5(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedList6(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl m_list;

	DataInterface _DataInterface;

	CString strFilePath;

	CStatic m_p1;
	afx_msg void OnStnClickedPicture();

	Mat src;//原始图像
	Mat dst;//处理后图像
	void ShowDst();

	CImageProcessing ImageProcessing;

	afx_msg void OnRGB_2_Gray();
	CStatic m_p2;

	//图像分割
	CFruitSegmentation m_segmentation;
	vector<Mat> m_fruitImages;
	void DisplaySegmentationResults();
	void MeasureAllFruits();
	void DisplayImage(const cv::Mat& image, UINT controlID);
	void ClearPictureControl(CStatic* pPictureCtrl);
	void DisplayMatToPictureControl(const cv::Mat& mat, CStatic* pPictureCtrl);
	CString IdentifyFruitType(const cv::Mat& fruitImage);
	//图像保存
	BOOL SavePictureControlImage(CWnd* pParent, UINT nID, LPCTSTR lpszFilePath);

	afx_msg void OnStnClickedFruit9();
	afx_msg void OnStnClickedFruit11();
	afx_msg void OnStnClickedFruit8();
	afx_msg void OnStnClickedFruit12();
	afx_msg void OnStnClickedStatic10();
	afx_msg void OnStnClickedFruit4();
	afx_msg void OnStnClickedFruit5();
	afx_msg void OnStnClickedFruit2();
	afx_msg void OnStnClickedFruit7();
	afx_msg void OnStnClickedFruit6();
	afx_msg void OnStnClickedFruit3();
	afx_msg void OnBinarizeImage();
	CStatic m_Fruit1;
	CStatic m_Fruit2;
	CStatic m_Fruit3;
	CStatic m_Fruit4;
	CStatic m_Fruit5;
	CStatic m_Fruit6;
//	CStatic m_Fruit7;
//	CStatic m_Fruit8;
	CStatic m_Fruit9;
	CStatic m_Fruit10;
	CStatic m_Fruit11;
	CStatic m_Fruit12;
	afx_msg void OnStnDblclickFruit1();
	afx_msg void OnStnDblclickFruit2();
	afx_msg void OnStnDblclickFruit3();
	afx_msg void OnStnDblclickFruit4();
	afx_msg void OnStnDblclickFruit5();
	afx_msg void OnStnDblclickFruit6();
	afx_msg void OnStnDblclickFruit7();
	afx_msg void OnStnDblclickFruit8();
	afx_msg void OnStnDblclickFruit9();
	afx_msg void OnStnDblclickStatic10();
	afx_msg void OnStnDblclickFruit11();
	afx_msg void OnStnDblclickFruit12();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnStnClickedFruit1();
};
