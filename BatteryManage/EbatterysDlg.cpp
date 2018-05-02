// EbatterysDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "EbatterysDlg.h"
#include "afxdialogex.h"

// CEbatterysDlg 对话框

IMPLEMENT_DYNAMIC(CEbatterysDlg, CDialog)

CEbatterysDlg::CEbatterysDlg(CWnd* pParent /*=NULL*/)
: CDialog(CEbatterysDlg::IDD, pParent)
{
	ColNum = 7;
}

CEbatterysDlg::~CEbatterysDlg()
{
}

void CEbatterysDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXCEP_LIST, excepList);
}


BEGIN_MESSAGE_MAP(CEbatterysDlg, CDialog)
	ON_WM_RBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CEbatterysDlg 消息处理程序


void CEbatterysDlg::OnRButtonDown(UINT nFlags, CPoint point)
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


void CEbatterysDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (this->m_hWnd) {
		CRect rect(0, 0, cx, cy);
		this->MoveWindow(rect.left + MARGIN_LEFT_BATPANE, rect.top + MARGIN_TOP_BATPANE, rect.Width(), rect.Height(), TRUE);
		
		if (excepList.m_hWnd)
		{
			excepList.MoveWindow(&rect, true);

			colWidth = rect.Width() / ColNum;

			excepList.SetColumnWidth(0, (rect.Width() - (ColNum - 1) * colWidth));
			for (int idx = 1; idx < ColNum; ++idx)
			{
				excepList.SetColumnWidth(idx, colWidth);
			}

		}
	}
}


BOOL CEbatterysDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect;
	GetWindowRect(&rect);  //获取窗口rect，

	//excepList.GetClientRect(&rect);
	excepList.MoveWindow(&rect, true);

	// 为列表视图控件添加全行选中和栅格风格   
	excepList.SetExtendedStyle(excepList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	colWidth = rect.Width() / ColNum;

	excepList.InsertColumn(0, L"序号", LVCFMT_LEFT, rect.Width() - (ColNum - 1)*colWidth);
	excepList.InsertColumn(1, L"柜号", LVCFMT_LEFT, colWidth);
	excepList.InsertColumn(2, L"电池工位", LVCFMT_LEFT, colWidth);
	excepList.InsertColumn(3, L"产品批号", LVCFMT_LEFT, colWidth);
	excepList.InsertColumn(4, L"电芯编号", LVCFMT_LEFT, colWidth);
	excepList.InsertColumn(5, L"工作状态", LVCFMT_LEFT, colWidth);
	excepList.InsertColumn(6, L"异常情况", LVCFMT_LEFT, colWidth);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CEbatterysDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
}
