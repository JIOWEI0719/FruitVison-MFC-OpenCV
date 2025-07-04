
// FruitsVisionDlg.cpp: 实现文件
//

#include "FruitData.h" 

#include "pch.h"
#include "framework.h"
#include "FruitsVision.h"
#include "FruitsVisionDlg.h"

#include"CCalibrate.h"
#include "afxdialogex.h"
#include <afx.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFruitsVisionDlg 对话框

CFruitsVisionDlg::CFruitsVisionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FRUITSVISION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFruitsVisionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST6, m_list);
	DDX_Control(pDX, Picture, m_p1);
	DDX_Control(pDX, Picture2, m_p2);
	DDX_Control(pDX, IDC_FRUIT1, m_Fruit1);
	DDX_Control(pDX, IDC_FRUIT2, m_Fruit2);
	DDX_Control(pDX, IDC_FRUIT3, m_Fruit3);
	DDX_Control(pDX, IDC_FRUIT4, m_Fruit4);
	DDX_Control(pDX, IDC_FRUIT6, m_Fruit5);
	DDX_Control(pDX, IDC_FRUIT7, m_Fruit6);
	//  DDX_Control(pDX, IDC_FRUIT5, m_Fruit7);
	//  DDX_Control(pDX, IDC_FRUIT8, m_Fruit8);
	DDX_Control(pDX, IDC_FRUIT10, m_Fruit9);
	DDX_Control(pDX, IDC_FRUIT11, m_Fruit10);
	DDX_Control(pDX, IDC_FRUIT12, m_Fruit11);
	DDX_Control(pDX, IDC_FRUIT9, m_Fruit12);
}

BEGIN_MESSAGE_MAP(CFruitsVisionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOPEN, &CFruitsVisionDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDSELECT, &CFruitsVisionDlg::OnBnClickedSelect)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST6, &CFruitsVisionDlg::OnItemchangedList6)
	ON_STN_CLICKED(Picture, &CFruitsVisionDlg::OnStnClickedPicture)
	ON_COMMAND(ID_32771, &CFruitsVisionDlg::OnRGB_2_Gray)
	ON_STN_CLICKED(IDC_FRUIT9, &CFruitsVisionDlg::OnStnClickedFruit9)
	ON_STN_CLICKED(IDC_FRUIT11, &CFruitsVisionDlg::OnStnClickedFruit11)
	ON_STN_CLICKED(IDC_FRUIT8, &CFruitsVisionDlg::OnStnClickedFruit8)
	ON_STN_CLICKED(IDC_FRUIT12, &CFruitsVisionDlg::OnStnClickedFruit12)
	ON_STN_CLICKED(IDC_FRUIT10, &CFruitsVisionDlg::OnStnClickedStatic10)
	ON_STN_CLICKED(IDC_FRUIT4, &CFruitsVisionDlg::OnStnClickedFruit4)
	ON_STN_CLICKED(IDC_FRUIT5, &CFruitsVisionDlg::OnStnClickedFruit5)
	ON_STN_CLICKED(IDC_FRUIT2, &CFruitsVisionDlg::OnStnClickedFruit2)
	ON_STN_CLICKED(IDC_FRUIT7, &CFruitsVisionDlg::OnStnClickedFruit7)
	ON_STN_CLICKED(IDC_FRUIT6, &CFruitsVisionDlg::OnStnClickedFruit6)
	ON_STN_CLICKED(IDC_FRUIT3, &CFruitsVisionDlg::OnStnClickedFruit3)
	ON_COMMAND(ID_32772, &CFruitsVisionDlg::OnBinarizeImage)
	ON_STN_DBLCLK(IDC_FRUIT1, &CFruitsVisionDlg::OnStnDblclickFruit1)
	ON_STN_DBLCLK(IDC_FRUIT2, &CFruitsVisionDlg::OnStnDblclickFruit2)
	ON_STN_DBLCLK(IDC_FRUIT3, &CFruitsVisionDlg::OnStnDblclickFruit3)
	ON_STN_DBLCLK(IDC_FRUIT4, &CFruitsVisionDlg::OnStnDblclickFruit4)
	ON_STN_DBLCLK(IDC_FRUIT5, &CFruitsVisionDlg::OnStnDblclickFruit5)
	ON_STN_DBLCLK(IDC_FRUIT6, &CFruitsVisionDlg::OnStnDblclickFruit6)
	ON_STN_DBLCLK(IDC_FRUIT7, &CFruitsVisionDlg::OnStnDblclickFruit7)
	ON_STN_DBLCLK(IDC_FRUIT8, &CFruitsVisionDlg::OnStnDblclickFruit8)
	ON_STN_DBLCLK(IDC_FRUIT9, &CFruitsVisionDlg::OnStnDblclickFruit9)
	ON_STN_DBLCLK(IDC_FRUIT10, &CFruitsVisionDlg::OnStnDblclickStatic10)
	ON_STN_DBLCLK(IDC_FRUIT11, &CFruitsVisionDlg::OnStnDblclickFruit11)
	ON_STN_DBLCLK(IDC_FRUIT12, &CFruitsVisionDlg::OnStnDblclickFruit12)
	ON_BN_CLICKED(IDC_BUTTON1, &CFruitsVisionDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_SAVE, &CFruitsVisionDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON2, &CFruitsVisionDlg::OnBnClickedButton2)
	ON_STN_CLICKED(IDC_FRUIT1, &CFruitsVisionDlg::OnStnClickedFruit1)
END_MESSAGE_MAP()


// CFruitsVisionDlg 消息处理程序

BOOL CFruitsVisionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	// 设置对话框字体
	CFont font;
	font.CreatePointFont(90, _T("MS Shell Dlg"));
	SetFont(&font);

	// 设置窗口样式
	ModifyStyle(0, WS_CLIPCHILDREN);
	ModifyStyleEx(0, WS_EX_CONTROLPARENT);

	// 设置扩展样式
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP);

	// 插入列标题
	m_list.InsertColumn(0, TEXT("序号"), LVCFMT_CENTER, 50);
	m_list.InsertColumn(1, TEXT("水果类型"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(2, TEXT("像素数量"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(3, TEXT("面积"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(4, TEXT("周长"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(5, TEXT("圆度"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(6, TEXT("长轴"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(7, TEXT("短轴"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(8, TEXT("横截面积"), LVCFMT_CENTER, 170);




	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFruitsVisionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFruitsVisionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFruitsVisionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFruitsVisionDlg::OnBnClickedOpen()
{
	TCHAR szFilter[] = _T("BMP图像文件(*.bmp)|*.bmp|所有文件(*.*)|*.*||");
	CFileDialog fileDlg(TRUE, _T("bmp"), NULL, 0, szFilter, this);

	if (IDOK == fileDlg.DoModal())
	{
		strFilePath = fileDlg.GetPathName();

		CImage image;
		image.Load(strFilePath);

		// 获取图片控件的矩形区域
		CRect rectControl;
		m_p1.GetClientRect(rectControl);

		CDC* pDc = m_p1.GetDC();

		// 计算保持纵横比的绘制区域
		int imgWidth = image.GetWidth();
		int imgHeight = image.GetHeight();
		double dAspect = (double)imgWidth / imgHeight;

		int destWidth = rectControl.Width();
		int destHeight = rectControl.Height();
		double dControlAspect = (double)destWidth / destHeight;

		int drawWidth, drawHeight;
		if (dAspect > dControlAspect) {
			// 以控件宽度为准
			drawWidth = destWidth;
			drawHeight = (int)(destWidth / dAspect);
		}
		else {
			// 以控件高度为准
			drawHeight = destHeight;
			drawWidth = (int)(destHeight * dAspect);
		}

		// 居中绘制
		int x = (destWidth - drawWidth) / 2;
		int y = (destHeight - drawHeight) / 2;
		CRect rectDraw(x, y, x + drawWidth, y + drawHeight);

		// 设置拉伸模式为HALFTONE，提高缩放质量
		pDc->SetStretchBltMode(HALFTONE);
		::SetBrushOrgEx(pDc->m_hDC, 0, 0, NULL);

		// 绘制图像
		image.Draw(pDc->m_hDC, rectDraw);
		image.Destroy();
		m_p1.ReleaseDC(pDc);

		// 下面这行代码使用了OpenCV，注意：如果同时使用CImage和OpenCV要注意路径字符串的转换
		// 如果不需要同时使用，可以注释掉或根据实际情况调整
		src = imread(strFilePath.GetBuffer(), 1); 
	}
}
void CFruitsVisionDlg::OnBnClickedSelect()
{
	// TODO: 在此添加控件通知处理程序代码

	if (src.empty()) return;

	// 执行分割
	m_fruitImages = m_segmentation.SegmentFruits(src);

	// 显示结果
	DisplaySegmentationResults();

	// 进行测量
	MeasureAllFruits();


}
// 显示分割结果
void CFruitsVisionDlg::DisplaySegmentationResults()
{
	for (size_t i = 0; i < m_fruitImages.size() && i < 12; i++)
	{
		DisplayImage(m_fruitImages[i], IDC_FRUIT1+ i);
	}
}
CString CFruitsVisionDlg::IdentifyFruitType(const cv::Mat& fruitImage)
{
	if (fruitImage.empty()) return _T("未知");

	cv::Mat hsv;
	cv::cvtColor(fruitImage, hsv, cv::COLOR_BGR2HSV);

	// 计算主要颜色的HSV均值
	cv::Scalar meanHSV = cv::mean(hsv);
	double hue = meanHSV[0];
	double saturation = meanHSV[1];
	double value = meanHSV[2];

	// 基于色调判断水果类型
	if (saturation < 50 || value < 50)
		return TEXT("其他");
	else if ((hue >= 0 && hue <= 10) || (hue >= 170 && hue <= 180))
		return TEXT("红色水果");
	else if (hue >= 11 && hue <= 25)
		return TEXT("橙色水果");
	else if (hue >= 26 && hue <= 35)
		return TEXT("黄色水果");
	else if (hue >= 36 && hue <= 85)
		return TEXT("绿色水果");
	else if (hue >= 120 && hue <= 150)
		return TEXT("紫色水果");
	else
		return TEXT("其他");
}
BOOL CFruitsVisionDlg::SavePictureControlImage(CWnd* pParent, UINT nID, LPCTSTR lpszFilePath)
{
	// 参数验证
	if (!pParent || !lpszFilePath)
	{
		TRACE("SavePictureControlImage: 无效参数\n");
		return FALSE;
	}

	// 获取Picture Control控件
	CStatic* pPictureCtrl = (CStatic*)pParent->GetDlgItem(nID);
	if (!pPictureCtrl)
	{
		TRACE("SavePictureControlImage: 无法获取Picture Control控件\n");
		return FALSE;
	}

	// 获取控件窗口句柄
	HWND hWndCtrl = pPictureCtrl->GetSafeHwnd();
	if (!hWndCtrl)
	{
		TRACE("SavePictureControlImage: 无法获取控件句柄\n");
		return FALSE;
	}

	// 获取控件尺寸
	CRect rect;
	pPictureCtrl->GetClientRect(&rect);
	int width = rect.Width();
	int height = rect.Height();

	// 检查尺寸有效性
	if (width <= 0 || height <= 0)
	{
		TRACE("SavePictureControlImage: 无效的控件尺寸 (%d x %d)\n", width, height);
		return FALSE;
	}

	// 获取设备上下文
	CDC* pDC = pPictureCtrl->GetDC();
	if (!pDC)
	{
		TRACE("SavePictureControlImage: 无法获取设备上下文\n");
		return FALSE;
	}

	// 创建内存DC和位图
	CDC memDC;
	CBitmap bitmap;
	CBitmap* pOldBitmap = nullptr;
	BYTE* pBits = nullptr;
	CFile file;

	BOOL bResult = FALSE;

	try
	{
		// 创建兼容的内存DC
		if (!memDC.CreateCompatibleDC(pDC))
		{
			TRACE("SavePictureControlImage: 无法创建兼容DC\n");
			throw FALSE;
		}

		// 创建位图
		if (!bitmap.CreateCompatibleBitmap(pDC, width, height))
		{
			TRACE("SavePictureControlImage: 无法创建位图\n");
			throw FALSE;
		}

		// 选择位图到内存DC
		pOldBitmap = memDC.SelectObject(&bitmap);
		if (!pOldBitmap)
		{
			TRACE("SavePictureControlImage: 无法选择位图到内存DC\n");
			throw FALSE;
		}

		// 复制图像到内存DC
		if (!memDC.BitBlt(0, 0, width, height, pDC, 0, 0, SRCCOPY))
		{
			TRACE("SavePictureControlImage: BitBlt操作失败\n");
			throw FALSE;
		}

		// 创建文件
		if (!file.Open(lpszFilePath, CFile::modeCreate | CFile::modeWrite))
		{
			TRACE("SavePictureControlImage: 无法创建文件 %s\n", lpszFilePath);
			throw FALSE;
		}

		// 设置位图信息头
		BITMAPINFOHEADER bi = { 0 };
		bi.biSize = sizeof(BITMAPINFOHEADER);
		bi.biWidth = width;
		bi.biHeight = -height;  // 负数表示从上到下
		bi.biPlanes = 1;
		bi.biBitCount = 24;     // 24位色
		bi.biCompression = BI_RGB;
		bi.biSizeImage = 0;
		bi.biXPelsPerMeter = 0;
		bi.biYPelsPerMeter = 0;
		bi.biClrUsed = 0;
		bi.biClrImportant = 0;

		// 计算图像数据大小 (每行字节数必须是4的倍数)
		int nBitsSize = ((width * 24 + 31) / 32) * 4 * height;

		// 分配内存存储位图数据
		pBits = new BYTE[nBitsSize];
		if (!pBits)
		{
			TRACE("SavePictureControlImage: 内存分配失败\n");
			throw FALSE;
		}

		// 获取位图数据
		if (!GetDIBits(memDC.GetSafeHdc(), (HBITMAP)bitmap.GetSafeHandle(),
			0, height, pBits, (BITMAPINFO*)&bi, DIB_RGB_COLORS))
		{
			TRACE("SavePictureControlImage: GetDIBits失败\n");
			throw FALSE;
		}

		// 写入文件头
		BITMAPFILEHEADER bmfh = { 0 };
		bmfh.bfType = 0x4D42; // "BM"
		bmfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + nBitsSize;
		bmfh.bfReserved1 = 0;
		bmfh.bfReserved2 = 0;
		bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

		file.Write(&bmfh, sizeof(BITMAPFILEHEADER));
		file.Write(&bi, sizeof(BITMAPINFOHEADER));
		file.Write(pBits, nBitsSize);

		bResult = TRUE;
		TRACE("SavePictureControlImage: 图像保存成功\n");
	}
	catch (...)
	{
		// 异常处理
		bResult = FALSE;
		TRACE("SavePictureControlImage: 发生异常\n");
	}

	// 清理资源
	if (pBits)
	{
		delete[] pBits;
	}

	if (pOldBitmap)
	{
		memDC.SelectObject(pOldBitmap);
	}

	if (pDC)
	{
		pPictureCtrl->ReleaseDC(pDC);
	}

	if (file.m_hFile != CFile::hFileNull)
	{
		file.Close();
	}

	return bResult;
}

// 测量所有水果
//// 测量所有水果（校验版的应用框架，后端的函数接口都已准备好了）
//void CFruitsVisionDlg::MeasureAllFruits()
//{
//	CCalibrate Calibrate;
//	// 尝试校准（如果尚未校准）
//	if (!Calibrate.m_isCalibrated && !m_fruitImages.empty()) {
//		if (Calibrate.CalibrateWithGrid(m_fruitImages[0], 10.0)) {
//			MessageBox(_T("网格校准成功！"), _T("校准信息"), MB_OK | MB_ICONINFORMATION);
//		}
//		else {
//			MessageBox(_T("自动校准失败，将使用像素单位"), _T("校准信息"), MB_OK | MB_ICONWARNING);
//		}
//	}
//
//	// 清空列表
//	m_list.DeleteAllItems();
//
//	for (size_t i = 0; i < m_fruitImages.size(); i++)
//	{
//		// 轮廓检测
//		cv::Mat gray, binary;
//		cv::cvtColor(m_fruitImages[i], gray, cv::COLOR_BGR2GRAY);
//		cv::threshold(gray, binary, 1, 255, cv::THRESH_BINARY);
//
//		std::vector<std::vector<cv::Point>> contours;
//		cv::findContours(binary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
//
//		if (!contours.empty())
//		{
//			// 使用新的校准轮廓筛选函数
//			std::vector<std::vector<cv::Point>> filteredContours =
//				Calibrate.FilterContoursWithCalibration(contours, 50.0, 500.0, Calibrate.m_isCalibrated);
//
//			if (!filteredContours.empty()) {
//				// 找到最大轮廓
//				int maxAreaIdx = 0;
//				double maxArea = 0;
//				for (size_t j = 0; j < filteredContours.size(); j++) {
//					double area = cv::contourArea(filteredContours[j]);
//					if (area > maxArea) {
//						maxArea = area;
//						maxAreaIdx = j;
//					}
//				}
//
//				// 获取校准后的测量结果
//				CalibratedMeasurements measurements =
//					Calibrate.GetCalibratedMeasurementsFromContour(filteredContours[maxAreaIdx]);
//
//				// 识别水果类型
//				CString fruitType = IdentifyFruitType(m_fruitImages[i]);
//
//				// 插入到List Control
//				int nItem = m_list.InsertItem(i, _T(""));
//
//				// 设置各列数据
//				CString strTemp;
//
//				// 序号
//				strTemp.Format(_T("%d"), i + 1);
//				m_list.SetItemText(nItem, 0, strTemp);
//
//				// 水果类型
//				m_list.SetItemText(nItem, 1, fruitType);
//
//				// 像素数量
//				strTemp.Format(_T("%d"), (int)measurements.areaPixels);
//				m_list.SetItemText(nItem, 2, strTemp);
//
//				// 面积
//				strTemp = Calibrate.FormatMeasurement(measurements.areaSquareMm, _T("mm²"), Calibrate.m_isCalibrated);
//				m_list.SetItemText(nItem, 3, strTemp);
//
//				// 周长
//				strTemp = Calibrate.FormatMeasurement(measurements.perimeterMm, _T("mm"), Calibrate.m_isCalibrated);
//				m_list.SetItemText(nItem, 4, strTemp);
//
//				// 圆度
//				strTemp.Format(_T("%.3f"), measurements.circularity);
//				m_list.SetItemText(nItem, 5, strTemp);
//
//				// 长轴
//				strTemp = Calibrate.FormatMeasurement(measurements.majorAxisMm, _T("mm"), Calibrate.m_isCalibrated);
//				m_list.SetItemText(nItem, 6, strTemp);
//
//				// 短轴
//				strTemp = Calibrate.FormatMeasurement(measurements.minorAxisMm, _T("mm"), Calibrate.m_isCalibrated);
//				m_list.SetItemText(nItem, 7, strTemp);
//
//				// 横截面积
//				strTemp = Calibrate.FormatMeasurement(measurements.crossSectionAreaSquareMm, _T("mm²"), Calibrate.m_isCalibrated);
//				m_list.SetItemText(nItem, 8, strTemp);
//			}
//		}
//	}
//}

// 测量所有水果（无校验版）
void CFruitsVisionDlg::MeasureAllFruits()
{
	// 清空列表
	m_list.DeleteAllItems();
	for (size_t i = 0; i < m_fruitImages.size(); i++)
	{
		// 重新计算轮廓
		cv::Mat gray, binary;
		cv::cvtColor(m_fruitImages[i], gray, cv::COLOR_BGR2GRAY);
		cv::threshold(gray, binary, 1, 255, cv::THRESH_BINARY);
		std::vector<std::vector<cv::Point>> contours;
		cv::findContours(binary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
		if (!contours.empty())
		{
			// 找到最大轮廓
			int maxAreaIdx = 0;
			double maxArea = 0;
			for (size_t j = 0; j < contours.size(); j++)
			{
				double area = cv::contourArea(contours[j]);
				if (area > maxArea)
				{
					maxArea = area;
					maxAreaIdx = j;
				}
			}
			// 计算各项测量数据
			int pixelCount;
			double area, perimeter;
			m_segmentation.MeasureFruit(m_fruitImages[i], contours[maxAreaIdx],
				pixelCount, area, perimeter);
			// 计算圆度 (4π*面积/周长²)
			double circularity = 0;
			if (perimeter > 0)
				circularity = 4 * CV_PI * area / (perimeter * perimeter);
			// 计算长短轴（通过拟合椭圆）
			double majorAxis = 0, minorAxis = 0;
			double crossSectionArea = 0; // 横截面积
			if (contours[maxAreaIdx].size() >= 5)
			{
				cv::RotatedRect ellipse = cv::fitEllipse(contours[maxAreaIdx]);
				majorAxis = std::max(ellipse.size.width, ellipse.size.height);
				minorAxis = std::min(ellipse.size.width, ellipse.size.height);
				// 计算横截面积 - 以短轴为直径的圆形面积
				// 假设水果的横截面是圆形，直径等于短轴
				double radius = minorAxis / 2.0;
				crossSectionArea = CV_PI * radius * radius;
			}
			// 识别水果类型
			CString fruitType = IdentifyFruitType(m_fruitImages[i]);
			// 插入到List Control
			int nItem = m_list.InsertItem(i, _T(""));
			// 设置各列数据
			CString strTemp;
			// 序号
			strTemp.Format(_T("%d"), i + 1);
			m_list.SetItemText(nItem, 0, strTemp);
			// 水果类型
			m_list.SetItemText(nItem, 1, fruitType);
			// 像素数量
			strTemp.Format(_T("%d"), pixelCount);
			m_list.SetItemText(nItem, 2, strTemp);
			// 面积
			strTemp.Format(_T("%.2f"), area);
			m_list.SetItemText(nItem, 3, strTemp);
			// 周长
			strTemp.Format(_T("%.2f"), perimeter);
			m_list.SetItemText(nItem, 4, strTemp);
			// 圆度
			strTemp.Format(_T("%.3f"), circularity);
			m_list.SetItemText(nItem, 5, strTemp);
			// 长轴
			strTemp.Format(_T("%.2f"), majorAxis);
			m_list.SetItemText(nItem, 6, strTemp);
			// 短轴
			strTemp.Format(_T("%.2f"), minorAxis);
			m_list.SetItemText(nItem, 7, strTemp);
			// 横截面积
			strTemp.Format(_T("%.2f"), crossSectionArea);
			m_list.SetItemText(nItem, 8, strTemp);
			// 设置行背景色（可选，根据水果类型）
			//SetListItemColor(nItem, fruitType);
		}
	}
}


// 显示图像到Picture Control（带清空功能）
// 修复后的图像显示函数
void CFruitsVisionDlg::DisplayImage(const Mat& image, UINT controlID)
{
	CStatic* pPictureCtrl = (CStatic*)GetDlgItem(controlID);
	if (!pPictureCtrl) return;

	// 清空Picture Control中的内容
	ClearPictureControl(pPictureCtrl);

	// 如果图像为空，只清空后返回
	if (image.empty()) return;

	CRect rect;
	pPictureCtrl->GetClientRect(&rect);

	// 确保尺寸有效
	if (rect.Width() <= 0 || rect.Height() <= 0) return;

	// 调整图像大小，保持宽度为4的倍数（避免内存对齐问题）
	int targetWidth = (rect.Width() / 4) * 4;  // 确保宽度是4的倍数
	int targetHeight = rect.Height();

	Mat resized;
	resize(image, resized, Size(targetWidth, targetHeight), 0, 0, INTER_LINEAR);

	// 确保图像是BGR格式（OpenCV默认格式）
	Mat displayImage;
	if (resized.channels() == 3)
	{
		// 转换BGR到RGB（Windows显示需要RGB格式）
		cvtColor(resized, displayImage, COLOR_BGR2RGB);
	}
	else if (resized.channels() == 1)
	{
		// 灰度图转RGB
		cvtColor(resized, displayImage, COLOR_GRAY2RGB);
	}
	else
	{
		displayImage = resized.clone();
	}

	// 转换为DIB格式显示
	DisplayMatToPictureControl(displayImage, pPictureCtrl);
}
// 清空Picture Control的辅助函数
void CFruitsVisionDlg::ClearPictureControl(CStatic* pPictureCtrl)
{
	if (!pPictureCtrl) return;

	//// 方法1：使用背景色填充
	//CDC* pDC = pPictureCtrl->GetDC();
	//if (pDC)
	//{
	//	// 使用系统背景色或指定颜色填充
	//	CBrush brush(GetSysColor(COLOR_3DFACE)); // 或使用 RGB(240, 240, 240) 等自定义颜色
	//	pDC->FillRect(&rect, &brush);
	//	pPictureCtrl->ReleaseDC(pDC);
	//}

	// 方法2：清除之前设置的位图（如果有的话）
	pPictureCtrl->SetBitmap(NULL);

	// 强制重绘
	pPictureCtrl->Invalidate();
	pPictureCtrl->UpdateWindow();
}

// 修复的Mat到Picture Control显示函数
void CFruitsVisionDlg::DisplayMatToPictureControl(const Mat& mat, CStatic* pPictureCtrl)
{
	if (mat.empty() || !pPictureCtrl) return;

	// 确保图像格式正确
	Mat displayMat;
	if (mat.channels() == 3)
	{
		displayMat = mat.clone();
	}
	else if (mat.channels() == 1)
	{
		cvtColor(mat, displayMat, COLOR_GRAY2RGB);
	}
	else
	{
		return; // 不支持的格式
	}

	// 创建DIB
	int width = displayMat.cols;
	int height = displayMat.rows;
	int channels = displayMat.channels();

	// 计算行字节数（必须是4的倍数）
	int lineBytesCount = (width * channels + 3) & (~3);

	// 创建BITMAPINFO结构
	BITMAPINFO bmi;
	memset(&bmi, 0, sizeof(bmi));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = width;
	bmi.bmiHeader.biHeight = -height;  // 负数表示从上到下
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = channels * 8;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = lineBytesCount * height;

	// 创建DIB数据
	vector<BYTE> dibData(lineBytesCount * height);

	for (int row = 0; row < height; row++)
	{
		const uchar* srcRow = displayMat.ptr<uchar>(row);
		BYTE* destRow = &dibData[row * lineBytesCount];

		for (int col = 0; col < width; col++)
		{
			// 注意：OpenCV是BGR，Windows显示需要RGB
			destRow[col * 3 + 0] = srcRow[col * 3 + 2]; // R
			destRow[col * 3 + 1] = srcRow[col * 3 + 1]; // G
			destRow[col * 3 + 2] = srcRow[col * 3 + 0]; // B
		}
	}

	// 显示到Picture Control
	CDC* pDC = pPictureCtrl->GetDC();
	if (pDC)
	{
		CRect rect;
		pPictureCtrl->GetClientRect(&rect);

		::SetDIBitsToDevice(
			pDC->m_hDC,
			0, 0,           // 目标位置
			width, height,  // 源尺寸
			0, 0,           // 源起始位置
			0, height,      // 扫描线范围
			&dibData[0],    // 位图数据
			&bmi,           // 位图信息
			DIB_RGB_COLORS  // 颜色格式
		);

		pPictureCtrl->ReleaseDC(pDC);
	}
}
//void CFruitsVisionDlg::OnLvnItemchangedList5(NMHDR* pNMHDR, LRESULT* pResult)
//{
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//	*pResult = 0;
//}

void CFruitsVisionDlg::OnItemchangedList6(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CFruitsVisionDlg::OnStnClickedPicture()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CFruitsVisionDlg::ShowDst()
{
	// 获取图片控件的矩形区域
	CRect rectControl;
	m_p2.GetClientRect(rectControl);
	CDC* pDc = m_p2.GetDC();

	// 清除原有图像 - 用背景色填充整个控件区域
	pDc->FillSolidRect(rectControl, GetSysColor(COLOR_BTNFACE)); // 使用系统背景色
	// 或者使用白色背景：pDc->FillSolidRect(rectControl, RGB(255, 255, 255));

	CImage image;
	HRESULT hr = image.Load(TEXT("result.png"));
	if (FAILED(hr)) {
		// 如果图像加载失败，保持清除状态
		m_p2.ReleaseDC(pDc);
		return;
	}

	// 计算保持纵横比的绘制区域
	int imgWidth = image.GetWidth();
	int imgHeight = image.GetHeight();
	double dAspect = (double)imgWidth / imgHeight;
	int destWidth = rectControl.Width();
	int destHeight = rectControl.Height();
	double dControlAspect = (double)destWidth / destHeight;
	int drawWidth, drawHeight;
	if (dAspect > dControlAspect) {
		// 以控件宽度为准
		drawWidth = destWidth;
		drawHeight = (int)(destWidth / dAspect);
	}
	else {
		// 以控件高度为准
		drawHeight = destHeight;
		drawWidth = (int)(destHeight * dAspect);
	}
	// 居中绘制
	int x = (destWidth - drawWidth) / 2;
	int y = (destHeight - drawHeight) / 2;
	CRect rectDraw(x, y, x + drawWidth, y + drawHeight);
	// 设置拉伸模式为HALFTONE，提高缩放质量
	pDc->SetStretchBltMode(HALFTONE);
	::SetBrushOrgEx(pDc->m_hDC, 0, 0, NULL);
	// 绘制图像
	image.Draw(pDc->m_hDC, rectDraw);
	image.Destroy();
	m_p2.ReleaseDC(pDc);
}
void CFruitsVisionDlg::OnRGB_2_Gray()
{
	// TODO: 在此添加命令处理程序代码
	dst = ImageProcessing.RGB_2_Gray(src);
	imwrite("result.png", dst);
	ShowDst();
}

void CFruitsVisionDlg::OnBinarizeImage()
{
	// TODO: 在此添加命令处理程序代码
	dst = ImageProcessing.BinarizeImage(src);
	imwrite("result.png", dst);
	ShowDst();
}


void CFruitsVisionDlg::OnStnClickedFruit9()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CFruitsVisionDlg::OnStnClickedFruit11()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CFruitsVisionDlg::OnStnClickedFruit8()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CFruitsVisionDlg::OnStnClickedFruit12()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CFruitsVisionDlg::OnStnClickedStatic10()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CFruitsVisionDlg::OnStnClickedFruit4()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CFruitsVisionDlg::OnStnClickedFruit5()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CFruitsVisionDlg::OnStnClickedFruit2()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CFruitsVisionDlg::OnStnClickedFruit7()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CFruitsVisionDlg::OnStnClickedFruit6()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CFruitsVisionDlg::OnStnClickedFruit3()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CFruitsVisionDlg::OnStnDblclickFruit1()
{
	//// TODO: 在此添加控件通知处理程序代码
	//CFileDialog dlg(FALSE, _T("bmp"), _T("image.bmp"),
	//	OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	//	_T("位图文件 (*.bmp)|*.bmp|所有文件 (*.*)|*.*||"), this);

	//if (dlg.DoModal() == IDOK)
	//{
	//	if (SavePictureControlImage(this, IDC_FRUIT1, dlg.GetPathName()))
	//	{
	//		MessageBox(_T("图像保存成功！"), _T("提示"), MB_ICONINFORMATION);
	//	}
	//	else
	//	{
	//		MessageBox(_T("图像保存失败！"), _T("错误"), MB_ICONERROR);
	//	}
	//}
}

void CFruitsVisionDlg::OnStnDblclickFruit2()
{
	//// TODO: 在此添加控件通知处理程序代码
	//CFileDialog dlg(FALSE, _T("bmp"), _T("image.bmp"),
	//	OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	//	_T("位图文件 (*.bmp)|*.bmp|所有文件 (*.*)|*.*||"), this);

	//if (dlg.DoModal() == IDOK)
	//{
	//	if (SavePictureControlImage(this, IDC_FRUIT2, dlg.GetPathName()))
	//	{
	//		MessageBox(_T("图像保存成功！"), _T("提示"), MB_ICONINFORMATION);
	//	}
	//	else
	//	{
	//		MessageBox(_T("图像保存失败！"), _T("错误"), MB_ICONERROR);
	//	}
	//}

}

void CFruitsVisionDlg::OnStnDblclickFruit3()
{
	//// TODO: 在此添加控件通知处理程序代码
	//CFileDialog dlg(FALSE, _T("bmp"), _T("image.bmp"),
	//	OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	//	_T("位图文件 (*.bmp)|*.bmp|所有文件 (*.*)|*.*||"), this);

	//if (dlg.DoModal() == IDOK)
	//{
	//	if (SavePictureControlImage(this, IDC_FRUIT3, dlg.GetPathName()))
	//	{
	//		MessageBox(_T("图像保存成功！"), _T("提示"), MB_ICONINFORMATION);
	//	}
	//	else
	//	{
	//		MessageBox(_T("图像保存失败！"), _T("错误"), MB_ICONERROR);
	//	}
	//}
}

void CFruitsVisionDlg::OnStnDblclickFruit4()
{
	//// TODO: 在此添加控件通知处理程序代码
	//CFileDialog dlg(FALSE, _T("bmp"), _T("image.bmp"),
	//	OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	//	_T("位图文件 (*.bmp)|*.bmp|所有文件 (*.*)|*.*||"), this);

	//if (dlg.DoModal() == IDOK)
	//{
	//	if (SavePictureControlImage(this, IDC_FRUIT4, dlg.GetPathName()))
	//	{
	//		MessageBox(_T("图像保存成功！"), _T("提示"), MB_ICONINFORMATION);
	//	}
	//	else
	//	{
	//		MessageBox(_T("图像保存失败！"), _T("错误"), MB_ICONERROR);
	//	}
	//}

}

void CFruitsVisionDlg::OnStnDblclickFruit5()
{
	//// TODO: 在此添加控件通知处理程序代码
	//CFileDialog dlg(FALSE, _T("bmp"), _T("image.bmp"),
	//	OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	//	_T("位图文件 (*.bmp)|*.bmp|所有文件 (*.*)|*.*||"), this);

	//if (dlg.DoModal() == IDOK)
	//{
	//	if (SavePictureControlImage(this, IDC_FRUIT5, dlg.GetPathName()))
	//	{
	//		MessageBox(_T("图像保存成功！"), _T("提示"), MB_ICONINFORMATION);
	//	}
	//	else
	//	{
	//		MessageBox(_T("图像保存失败！"), _T("错误"), MB_ICONERROR);
	//	}
	//}

}

void CFruitsVisionDlg::OnStnDblclickFruit6()
{
	//// TODO: 在此添加控件通知处理程序代码
	//CFileDialog dlg(FALSE, _T("bmp"), _T("image.bmp"),
	//	OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	//	_T("位图文件 (*.bmp)|*.bmp|所有文件 (*.*)|*.*||"), this);

	//if (dlg.DoModal() == IDOK)
	//{
	//	if (SavePictureControlImage(this, IDC_FRUIT6, dlg.GetPathName()))
	//	{
	//		MessageBox(_T("图像保存成功！"), _T("提示"), MB_ICONINFORMATION);
	//	}
	//	else
	//	{
	//		MessageBox(_T("图像保存失败！"), _T("错误"), MB_ICONERROR);
	//	}
	//}

}

void CFruitsVisionDlg::OnStnDblclickFruit7()
{
	/* TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(FALSE, _T("bmp"), _T("image.bmp"),
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("位图文件 (*.bmp)|*.bmp|所有文件 (*.*)|*.*||"), this);

	if (dlg.DoModal() == IDOK)
	{
		if (SavePictureControlImage(this, IDC_FRUIT7, dlg.GetPathName()))
		{
			MessageBox(_T("图像保存成功！"), _T("提示"), MB_ICONINFORMATION);
		}
		else
		{
			MessageBox(_T("图像保存失败！"), _T("错误"), MB_ICONERROR);
		}
	}*/
}

void CFruitsVisionDlg::OnStnDblclickFruit8()
{
	//// TODO: 在此添加控件通知处理程序代码
	//CFileDialog dlg(FALSE, _T("bmp"), _T("image.bmp"),
	//	OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	//	_T("位图文件 (*.bmp)|*.bmp|所有文件 (*.*)|*.*||"), this);

	//if (dlg.DoModal() == IDOK)
	//{
	//	if (SavePictureControlImage(this, IDC_FRUIT8, dlg.GetPathName()))
	//	{
	//		MessageBox(_T("图像保存成功！"), _T("提示"), MB_ICONINFORMATION);
	//	}
	//	else
	//	{
	//		MessageBox(_T("图像保存失败！"), _T("错误"), MB_ICONERROR);
	//	}
	//}

}

void CFruitsVisionDlg::OnStnDblclickFruit9()
{
	//// TODO: 在此添加控件通知处理程序代码
	//CFileDialog dlg(FALSE, _T("bmp"), _T("image.bmp"),
	//	OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	//	_T("位图文件 (*.bmp)|*.bmp|所有文件 (*.*)|*.*||"), this);

	//if (dlg.DoModal() == IDOK)
	//{
	//	if (SavePictureControlImage(this, IDC_FRUIT9, dlg.GetPathName()))
	//	{
	//		MessageBox(_T("图像保存成功！"), _T("提示"), MB_ICONINFORMATION);
	//	}
	//	else
	//	{
	//		MessageBox(_T("图像保存失败！"), _T("错误"), MB_ICONERROR);
	//	}
	//}

}

void CFruitsVisionDlg::OnStnDblclickStatic10()
{
	//// TODO: 在此添加控件通知处理程序代码
	//CFileDialog dlg(FALSE, _T("bmp"), _T("image.bmp"),
	//	OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	//	_T("位图文件 (*.bmp)|*.bmp|所有文件 (*.*)|*.*||"), this);

	//if (dlg.DoModal() == IDOK)
	//{
	//	if (SavePictureControlImage(this, IDC_FRUIT10, dlg.GetPathName()))
	//	{
	//		MessageBox(_T("图像保存成功！"), _T("提示"), MB_ICONINFORMATION);
	//	}
	//	else
	//	{
	//		MessageBox(_T("图像保存失败！"), _T("错误"), MB_ICONERROR);
	//	}
	//}

}

void CFruitsVisionDlg::OnStnDblclickFruit11()
{
	//// TODO: 在此添加控件通知处理程序代码
	//CFileDialog dlg(FALSE, _T("bmp"), _T("image.bmp"),
	//	OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	//	_T("位图文件 (*.bmp)|*.bmp|所有文件 (*.*)|*.*||"), this);

	//if (dlg.DoModal() == IDOK)
	//{
	//	if (SavePictureControlImage(this, IDC_FRUIT11, dlg.GetPathName()))
	//	{
	//		MessageBox(_T("图像保存成功！"), _T("提示"), MB_ICONINFORMATION);
	//	}
	//	else
	//	{
	//		MessageBox(_T("图像保存失败！"), _T("错误"), MB_ICONERROR);
	//	}
	//}

}

void CFruitsVisionDlg::OnStnDblclickFruit12()
{
	//// TODO: 在此添加控件通知处理程序代码
	//CFileDialog dlg(FALSE, _T("bmp"), _T("image.bmp"),
	//	OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	//	_T("位图文件 (*.bmp)|*.bmp|所有文件 (*.*)|*.*||"), this);

	//if (dlg.DoModal() == IDOK)
	//{
	//	if (SavePictureControlImage(this, IDC_FRUIT12, dlg.GetPathName()))
	//	{
	//		MessageBox(_T("图像保存成功！"), _T("提示"), MB_ICONINFORMATION);
	//	}
	//	else
	//	{
	//		MessageBox(_T("图像保存失败！"), _T("错误"), MB_ICONERROR);
	//	}
	//}
}

void CFruitsVisionDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CFruitsVisionDlg::OnBnClickedSave()
{
	//弃用的保存按钮
}

//void CFruitsVisionDlg::OnBnClickedSave()
//{
//	TRACE("OnBnClickedSave() called\n");
//
//	// 创建文件对话框
//	CFileDialog dlg(FALSE, _T("bmp"), _T("image.bmp"),
//		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
//		_T("位图文件 (*.bmp)|*.bmp|JPEG文件 (*.jpg)|*.jpg|PNG文件 (*.png)|*.png|所有文件 (*.*)|*.*||"),
//		this);
//
//	if (dlg.DoModal() == IDOK)
//	{
//		CString strFilePath = dlg.GetPathName();
//
//		// 显示保存进度
//		CWaitCursor waitCursor;
//
//		if (SavePictureControlImage(this, Picture2, strFilePath))
//		{
//			MessageBox(_T("图像保存成功！"), _T("提示"), MB_ICONINFORMATION);
//
//			// 可选：询问是否打开保存的文件
//			if (MessageBox(_T("是否打开保存的文件？"), _T("提示"), MB_YESNO | MB_ICONQUESTION) == IDYES)
//			{
//				ShellExecute(NULL, _T("open"), strFilePath, NULL, NULL, SW_SHOWNORMAL);
//			}
//		}
//		else
//		{
//			MessageBox(_T("图像保存失败！请检查文件路径和权限。"), _T("错误"), MB_ICONERROR);
//		}
//	}
//}
void CFruitsVisionDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	TRACE("OnBnClickedSave() called\n");

	// 创建文件对话框
	CFileDialog dlg(FALSE, _T("bmp"), _T("image.bmp"),
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("位图文件 (*.bmp)|*.bmp|JPEG文件 (*.jpg)|*.jpg|PNG文件 (*.png)|*.png|所有文件 (*.*)|*.*||"),
		this);

	if (dlg.DoModal() == IDOK)
	{
		CString strFilePath = dlg.GetPathName();

		// 显示保存进度
		CWaitCursor waitCursor;

		if (SavePictureControlImage(this, Picture2, strFilePath))
		{
			MessageBox(_T("图像保存成功！"), _T("提示"), MB_ICONINFORMATION);

			// 可选：询问是否打开保存的文件
			if (MessageBox(_T("是否打开保存的文件？"), _T("提示"), MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				ShellExecute(NULL, _T("open"), strFilePath, NULL, NULL, SW_SHOWNORMAL);
			}
		}
		else
		{
			MessageBox(_T("图像保存失败！请检查文件路径和权限。"), _T("错误"), MB_ICONERROR);
		}
	}
}

void CFruitsVisionDlg::OnStnClickedFruit1()
{
	// TODO: 在此添加控件通知处理程序代码
}
