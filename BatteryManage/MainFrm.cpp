
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "Dbt.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
//	ON_COMMAND(ID_BATTERY_CHECK, &CMainFrame::OnBatteryCheck)
ON_WM_DEVICECHANGE()
ON_COMMAND(ID_WINDOW_CASCADE, &CMainFrame::OnWindowCascade)
ON_COMMAND(ID_WINDOW_TILE_HORZ, &CMainFrame::OnWindowTileHorz)
ON_COMMAND(ID_WINDOW_TILE_VERT, &CMainFrame::OnWindowTileVert)
ON_COMMAND(ID_WINDOW_ARRANGE, &CMainFrame::OnWindowArrange)
ON_WM_SYSCOMMAND()
ON_WM_NCLBUTTONDBLCLK()
ON_WM_CHILDACTIVATE()

ON_MESSAGE(WM_COLSE_DATAFILEVIEW_MSG, &CMainFrame::OnCloseDateFileView)

ON_WM_CLOSE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// 主要设置
	//initDlg = NULL;
	//opLoginDlg = NULL;
	//setNumDlg = NULL;
	//opManagerDlg = NULL;
	//adminLoginDlg = NULL;
	//opLogDlg = NULL;
	
	//
	//startWorkDlg = NULL;

	// TODO:  在此添加成员初始化代码
	batteryCheckFrame = NULL;
}

CMainFrame::~CMainFrame()
{
	//if (batteryCheckFrame != NULL) {
	//	delete batteryCheckFrame;
	//	batteryCheckFrame = NULL;
	//}



}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO:  如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE | WS_THICKFRAME
		| WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;
	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



//void CMainFrame::OnBatteryCheck()
//{
//	// TODO:  在此添加命令处理程序代码
//	//if (batteryCheckFrame == NULL) {
//
//	//	batteryCheckFrame = new CBatteryCheckFrame();
//
//	//	batteryCheckFrame->Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, rectDefault);
//
//	//	batteryCheckFrame->ShowWindow(SW_MAXIMIZE);
//	//}
//	//batteryCheckFrame->UpdateWindow();
//}





void CMainFrame::OnWindowCascade()
{
	MDICascade();
	UnlockWindowUpdate();
	// TODO:  在此添加命令处理程序代码
}


void CMainFrame::OnWindowTileHorz()
{
	MDITile(MDITILE_HORIZONTAL);
	UnlockWindowUpdate();
	// TODO:  在此添加命令处理程序代码
}


void CMainFrame::OnWindowTileVert()
{
	MDITile(MDITILE_VERTICAL);
	UnlockWindowUpdate();
	// TODO:  在此添加命令处理程序代码
}


void CMainFrame::OnWindowArrange()
{
	MDIIconArrange();
	UnlockWindowUpdate();
	// TODO:  在此添加命令处理程序代码
}


void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CMDIFrameWnd::OnSysCommand(nID, lParam);
	
	if (nID == SC_MAXIMIZE) {
		UnlockWindowUpdate();
		UpdateWindow();
	}
	if (nID == SC_RESTORE)
	{
		UnlockWindowUpdate();
		UpdateWindow();
	}
}


void CMainFrame::OnNcLButtonDblClk(UINT nHitTest, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	maxminFlag = TRUE;
	CMDIFrameWnd::OnNcLButtonDblClk(nHitTest, point);
}

BOOL CMainFrame::OnDeviceChange(UINT nEventType, DWORD_PTR dwData)
{
	CBatteryMainFrame *batteryMainFrame = (CBatteryMainFrame *)theApp.batteryMainWnd;


	CView  *pView = batteryMainFrame->GetActiveView();


	if (!pView->IsKindOf(RUNTIME_CLASS(CBatteryMainView)))
	{
			
		pView = NULL;
	}
	if (pView != NULL)
	{
		CBatteryMainView *batteryMainView = (CBatteryMainView *)pView;
		switch (nEventType)
		{
		case DBT_DEVICEREMOVECOMPLETE://移除设备
			batteryMainView->CloseConsoleDevice();
			break;
		case DBT_DEVICEARRIVAL://添加设备  
			batteryMainView->InitilizeConsoleDevice();
			break;

		default:
			break;
		}

	}
	return TRUE;
}


void CMainFrame::OnChildActivate()
{
	CMDIFrameWnd::OnChildActivate();

	this->UpdateWindow();
	// TODO:  在此处添加消息处理程序代码
}

LRESULT CMainFrame::OnCloseDateFileView(WPARAM wParam, LPARAM lParam)
{
	this->UpdateWindow();
	return NULL;
}


void CMainFrame::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	//CMDIFrameWnd::OnClose();
}
