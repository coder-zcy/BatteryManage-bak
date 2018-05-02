// CbatterysDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "CbatterysDlg.h"
#include "afxdialogex.h"


// CbatterysDlg 对话框

IMPLEMENT_DYNAMIC(CbatterysDlg, CDialog)

CbatterysDlg::CbatterysDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CbatterysDlg::IDD, pParent)
{
	ColNum = 6;
	subGroupBatNum = 8;
	cabBattery = NULL;
}

CbatterysDlg::~CbatterysDlg()
{
}

void CbatterysDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMP_LIST, compList);
}


BEGIN_MESSAGE_MAP(CbatterysDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CbatterysDlg 消息处理程序


void CbatterysDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	if (this->m_hWnd) {
		CRect rect(0, 0, cx, cy);
		this->MoveWindow(rect.left + MARGIN_LEFT_BATPANE, rect.top + MARGIN_TOP_BATPANE, rect.Width(), rect.Height(), TRUE);
		//CRect  rect;
		//GetWindowRect(&rect);  //获取窗口rect，
		//ScreenToClient(rect);  //从窗口尺寸转换到用户区rect
		if (compList.m_hWnd)
		{
			compList.MoveWindow(&rect, true);

			colWidth = rect.Width() / ColNum;

			compList.SetColumnWidth(0, (rect.Width() - (ColNum - 1) * colWidth));
			for (int idx = 1; idx < ColNum; ++idx)
			{
				compList.SetColumnWidth(idx, colWidth);
			}

		}

	}
}


BOOL CbatterysDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//(1) 获取数据

	cabInfo = cabInfos[curCabId - 1];
	groupPerCol = cabInfo.groupNumPerCol;	//	每列组数
	colShowNum = cabInfo.colShowNum;		//	显示列数	
	numPerGroup = cabInfo.numPerGroup;		//	每组个数

	batCount = groupPerCol * colShowNum * numPerGroup;

	//(lowerCabs.cabBatterys[curCabId - 1])->batterys[batSeqId].GetSpecStateStr(STATE_SEL_CODE);

	//(2) 移动位置,创建ListCtrl

	GetWindowRect(&rect);  //获取窗口rect，

	//compList.GetClientRect(&rect);
	compList.MoveWindow(&rect, true);

	// 为列表视图控件添加全行选中和栅格风格   
	compList.SetExtendedStyle(compList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	colWidth = rect.Width() / ColNum;

	compList.InsertColumn(0, L"电池工位", LVCFMT_LEFT, rect.Width() - (ColNum - 1)*colWidth);
	compList.InsertColumn(1, L"电芯编号", LVCFMT_LEFT, colWidth);
	compList.InsertColumn(2, L"电压(mV)", LVCFMT_LEFT, colWidth);
	compList.InsertColumn(3, L"电流(mA)", LVCFMT_LEFT, colWidth);
	compList.InsertColumn(4, L"时间(Min)", LVCFMT_LEFT, colWidth);
	compList.InsertColumn(5, L"容量(mAh)", LVCFMT_LEFT, colWidth);

	FillTable();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CbatterysDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()

	//CDC memDC;			//	定义一个显示设备对象
	//CBitmap memBitMap;	//	定义一个位图对象
	//// 建立与屏幕显示兼容的内存显示设备
	//memDC.CreateCompatibleDC(NULL);
	//// 建立一个与屏幕显示兼容的位图,位图的大小与窗口大小相一致
	//this->GetClientRect(&rect);
	//memBitMap.CreateCompatibleBitmap(this->GetDC(), rect.Width(), rect.Height());

	//// 将位图选入到内存显示设备中
	//CBitmap *oldBit = memDC.SelectObject(&memBitMap);

	////(3) 将生成的数据填充到ListCtrl中
	//FillCompTable();
	//CDialog::OnPaint();

	//this->GetDC()->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
	//memBitMap.DeleteObject();
	//memDC.DeleteDC();
}

void CbatterysDlg::FillTable()
{
	cabBattery = lowerCabs.cabBatterys[curCabId - 1];

	for (int rowIdx = 0; rowIdx < batCount; ++rowIdx)
	{
		groupId = rowIdx / numPerGroup + 1;
		subGroupId = (rowIdx % numPerGroup) / subGroupBatNum + 1;
		subGroupBatId = (rowIdx % numPerGroup) % subGroupBatNum + 1;

		groupIdStr.Format(_T("%d"), groupId);
		subGroupIdStr.Format(_T("%d"), subGroupId);
		subGroupBatIdStr.Format(_T("%d"), subGroupBatId);

		str = L"第" + groupIdStr + L"-" + subGroupIdStr + L"-" + subGroupBatIdStr + L"个";

		compList.InsertItem(rowIdx, str);

		int valideDataNum = cabBattery == NULL ? 0 : cabBattery->batterys.size();


		int seqId = rowIdx + 1;
		if (seqId <= valideDataNum)
		{
			str.Format(_T("%d"), cabBattery->batterys[seqId - 1].voltVal);
			compList.SetItemText(rowIdx, 2, str == INVALIDE_STATE_CSTR ? INVALIDE_STATE_CSTR2 : str);
			str.Format(_T("%d"), cabBattery->batterys[seqId - 1].currentVal);
			compList.SetItemText(rowIdx, 3, str == INVALIDE_STATE_CSTR ? INVALIDE_STATE_CSTR2 : str);
			str.Format(_T("%d"), cabBattery->batterys[seqId - 1].timeVal);
			compList.SetItemText(rowIdx, 4, str == INVALIDE_STATE_CSTR ? INVALIDE_STATE_CSTR2 : str);
			str.Format(_T("%d"), cabBattery->batterys[seqId - 1].capacityVal);
			compList.SetItemText(rowIdx, 5, str == INVALIDE_STATE_CSTR ? INVALIDE_STATE_CSTR2 : str);

		}
		else
		{
			str = L"";
			compList.SetItemText(rowIdx, 2, str == INVALIDE_STATE_CSTR ? INVALIDE_STATE_CSTR2 : str);
			compList.SetItemText(rowIdx, 3, str == INVALIDE_STATE_CSTR ? INVALIDE_STATE_CSTR2 : str);
			compList.SetItemText(rowIdx, 4, str == INVALIDE_STATE_CSTR ? INVALIDE_STATE_CSTR2 : str);
			compList.SetItemText(rowIdx, 5, str == INVALIDE_STATE_CSTR ? INVALIDE_STATE_CSTR2 : str);
		}
		str.Format(_T("%d"), rowIdx + 1);
		compList.SetItemText(rowIdx, 1, str == INVALIDE_STATE_CSTR ? INVALIDE_STATE_CSTR2 : str);
	}
}
