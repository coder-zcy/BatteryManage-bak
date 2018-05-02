// TbatterysDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "TbatterysDlg.h"
#include "afxdialogex.h"


// CTbatterysDlg 对话框

IMPLEMENT_DYNAMIC(CTbatterysDlg, CDialog)

CTbatterysDlg::CTbatterysDlg(CWnd* pParent /*=NULL*/)
: CDialog(CTbatterysDlg::IDD, pParent)
{
	subGroupBatNum = 8;		// 每组有多少块电池构成
}

CTbatterysDlg::~CTbatterysDlg()
{

}

void CTbatterysDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TABLE_LIST, tableList);
}


BEGIN_MESSAGE_MAP(CTbatterysDlg, CDialog)
	ON_WM_RBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CTbatterysDlg 消息处理程序


void CTbatterysDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CMenu   controlMenu;   //定义下面要用到的cmenu对象
	controlMenu.LoadMenu(IDR_CONTROL_MENU); //装载自定义的右键菜单 
	CMenu   *controlContextMenu = controlMenu.GetSubMenu(0); //获取第一个弹出菜单，所以第一个菜单必须有子菜单 
	CRect rect;
	this->GetClientRect(&rect);
	ClientToScreen(&rect);

	POINT point1;
	::GetCursorPos(&point1);

	if (point1.x >= rect.left && point1.x <= rect.right
		&& point1.y >= rect.top && point1.y <= rect.bottom)
	{
		controlContextMenu->TrackPopupMenu(TPM_LEFTALIGN, point1.x, point1.y, AfxGetMainWnd()); //在指定位置显示弹出菜单
	}
	CDialog::OnRButtonDown(nFlags, point);
}


void CTbatterysDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	if (this->m_hWnd) {
		CRect rect(0, 0, cx, cy);
		this->MoveWindow(rect.left + MARGIN_LEFT_BATPANE, rect.top + MARGIN_TOP_BATPANE, rect.Width(), rect.Height(), TRUE);
		//CRect  rect;
		//GetWindowRect(&rect);  //获取窗口rect，
		//ScreenToClient(rect);  //从窗口尺寸转换到用户区rect
		if (tableList.m_hWnd)
		{
			tableList.MoveWindow(&rect, true);
			
			colWidth = rect.Width() / ColNum;

			tableList.SetColumnWidth(0, (rect.Width() - (ColNum - 1) * colWidth));
			for (int idx = 1; idx < ColNum; ++idx)
			{
				tableList.SetColumnWidth(idx, colWidth);
			}

		}
		
	}
}


BOOL CTbatterysDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//(1) 获取数据
	
	//DrawTable();
	cabInfo = cabInfos[curCabId - 1];
	groupPerCol = cabInfo.groupNumPerCol;	//	每列组数
	colShowNum = cabInfo.colShowNum;		//	显示列数	
	numPerGroup = cabInfo.numPerGroup;		//	每组个数


	ColNum = groupPerCol * colShowNum + 1;

	//(lowerCabs.cabBatterys[curCabId - 1])->batterys[batSeqId].GetSpecStateStr(STATE_SEL_CODE);

	//(2) 移动位置,创建ListCtrl

	GetWindowRect(&rect);  //获取窗口rect，

	//tableList.GetClientRect(&rect);
	tableList.MoveWindow(&rect, true);

	// 为列表视图控件添加全行选中和栅格风格   
	tableList.SetExtendedStyle(tableList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	colWidth = rect.Width() / ColNum;

	tableList.InsertColumn(0, L"(mv)", LVCFMT_LEFT, rect.Width() - (ColNum - 1)*colWidth);
	for (int idx = 1; idx < ColNum; ++idx)
	{
		str.Format(_T("%d"), idx);
		tableList.InsertColumn(idx, L"组" + str, LVCFMT_LEFT, colWidth);
	}

	FillTable();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CTbatterysDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
}

void CTbatterysDlg::FillTable()
{
	{
		//(3) 将生成的数据填充到ListCtrl中
		cabBattery = lowerCabs.cabBatterys[curCabId - 1];
		for (int rowIdx = 0; rowIdx < numPerGroup; ++rowIdx)
		{
			subGroupId = rowIdx / subGroupBatNum + 1;
			subGroupBatId = rowIdx % subGroupBatNum + 1;

			subGroupIdStr.Format(_T("%d"), subGroupId);
			subGroupBatIdStr.Format(_T("%d"), subGroupBatId);

			str = L"第" + subGroupIdStr + L"-" + subGroupBatIdStr + L"组";

			tableList.InsertItem(rowIdx, str);

			int valideDataNum = cabBattery == NULL ? 0 : cabBattery->batterys.size();

			if (valideDataNum > 0)
			{
				for (int colIdx = 1; colIdx < ColNum; ++colIdx)
				{
					int seqId = (colIdx - 1) * numPerGroup + rowIdx + 1;
					if (seqId <= valideDataNum)
					{
						tableList.SetItemText(rowIdx, colIdx, cabBattery->batterys[seqId - 1].GetSpecStateStr(STATE_SEL_CODE));
					}
					else
					{
						tableList.SetItemText(rowIdx, colIdx, L"");
					}
				}
			}

		}
	}
}
