
// MainFrm.cpp : CMainFrame ���ʵ��
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
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// ��Ҫ����
	//initDlg = NULL;
	//opLoginDlg = NULL;
	//setNumDlg = NULL;
	//opManagerDlg = NULL;
	//adminLoginDlg = NULL;
	//opLogDlg = NULL;
	
	//
	//startWorkDlg = NULL;

	// TODO:  �ڴ���ӳ�Ա��ʼ������
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
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO:  �������Ҫ��ͣ������������ɾ��������
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE | WS_THICKFRAME
		| WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;
	return TRUE;
}

// CMainFrame ���

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


// CMainFrame ��Ϣ�������



//void CMainFrame::OnBatteryCheck()
//{
//	// TODO:  �ڴ���������������
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
	// TODO:  �ڴ���������������
}


void CMainFrame::OnWindowTileHorz()
{
	MDITile(MDITILE_HORIZONTAL);
	UnlockWindowUpdate();
	// TODO:  �ڴ���������������
}


void CMainFrame::OnWindowTileVert()
{
	MDITile(MDITILE_VERTICAL);
	UnlockWindowUpdate();
	// TODO:  �ڴ���������������
}


void CMainFrame::OnWindowArrange()
{
	MDIIconArrange();
	UnlockWindowUpdate();
	// TODO:  �ڴ���������������
}


void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
		case DBT_DEVICEREMOVECOMPLETE://�Ƴ��豸
			batteryMainView->CloseConsoleDevice();
			break;
		case DBT_DEVICEARRIVAL://����豸  
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
	// TODO:  �ڴ˴������Ϣ����������
}

LRESULT CMainFrame::OnCloseDateFileView(WPARAM wParam, LPARAM lParam)
{
	this->UpdateWindow();
	return NULL;
}


void CMainFrame::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//CMDIFrameWnd::OnClose();
}
