// BatteryCheckFrame.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "BatteryMainFrame.h"


// CBatteryCheckFrame

IMPLEMENT_DYNCREATE(CBatteryMainFrame, CMDIChildWnd)

CBatteryMainFrame::CBatteryMainFrame()
{
	paintFlag = FALSE;
	maxminFlag = FALSE;
}

CBatteryMainFrame::~CBatteryMainFrame()
{
}


BEGIN_MESSAGE_MAP(CBatteryMainFrame, CMDIChildWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_GETMINMAXINFO()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_CLIPBOARDUPDATE()
	ON_WM_SIZECLIPBOARD()
	ON_WM_NCLBUTTONDBLCLK()
	ON_WM_INITMENU()

	ON_MESSAGE(WM_COLSE_DATAFILEVIEW_MSG, &CBatteryMainFrame::OnCloseDateFileView)
END_MESSAGE_MAP()


// CBatteryCheckFrame 消息处理程序


int CBatteryMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	//ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	// TODO:  在此添加您专用的创建代码
	//取得系统菜单
	CMenu *pMenu = GetSystemMenu(FALSE);
	//取得系统菜单数量
	int Count = pMenu->GetMenuItemCount();
	//取得关闭菜单的ID
	UINT id = pMenu->GetMenuItemID(Count - 1);
	//禁止关闭菜单
	pMenu->EnableMenuItem(id, MF_GRAYED);

	return 0;
}


void CBatteryMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	CMDIChildWnd::OnSetFocus(pOldWnd);

	batteryCheckView->SetFocus();
	// TODO:  在此处添加消息处理程序代码
}


BOOL CBatteryMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (batteryCheckView->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;
	return CMDIChildWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


BOOL CBatteryMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO:  在此添加专用代码和/或调用基类
	//ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	CCreateContext cc;
	cc.m_pCurrentFrame = this;
	cc.m_pNewViewClass = RUNTIME_CLASS(CBatteryMainView);
	batteryCheckView = (CBatteryMainView *)CreateView(&cc);
	return NULL != batteryCheckView;

}


void CBatteryMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	lpMMI->ptMinTrackSize.x = MIN_FRAME_WIDTH;

	lpMMI->ptMinTrackSize.y = MIN_FRAME_HEIGHT;
		


	CMDIChildWnd::OnGetMinMaxInfo(lpMMI);

	//UnlockWindowUpdate();
	//UpdateWindow();
	

	


}


BOOL CBatteryMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此添加专用代码和/或调用基类
	//cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE | WS_THICKFRAME
	//	| WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
	//cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

	return CMDIChildWnd::PreCreateWindow(cs);
}


void CBatteryMainFrame::ActivateFrame(int nCmdShow)
{
	// TODO:  在此添加专用代码和/或调用基类

	nCmdShow = SW_SHOWMAXIMIZED;
	CMDIChildWnd::ActivateFrame(nCmdShow);
}


void CBatteryMainFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	paintFlag = TRUE;

	//CBitmap bmp;;//定义一个位图对象
	//CDC memDC;  //首先定义一个显示设备对象
	////dc.SetBkColor();
	//CRect rect;
	//GetClientRect(&rect);
	//CDC *pdc = GetDC();
	//bmp.CreateCompatibleBitmap(pdc, rect.Width(), rect.Height());
	////bmp.LoadBitmap(IDB_MAINBMP);//上传位图，即所要修改为的背景图形

	//memDC.CreateCompatibleDC(pdc);
	//memDC.SelectObject(&bmp);
	////获取窗口的大小 
	//BITMAP bmInfo;
	//bmp.GetBitmap(&bmInfo);
	//int width = bmInfo.bmWidth;
	//int heigth = bmInfo.bmHeight;
	//CRect rc;
	//GetClientRect(rc);
	//pdc->SetStretchBltMode(COLORONCOLOR);
	//pdc->StretchBlt(0, 0, rc.Width(), rc.Height(), &memDC, 0, 0, width, heigth, SRCCOPY);
	////绘图完成后的清理
	//memDC.DeleteDC();
	//bmp.DeleteObject();
}


void CBatteryMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CMDIChildWnd::OnSize(nType, cx, cy);

	if (paintFlag)
	{
		LockWindowUpdate();
		if (maxminFlag) {
			UnlockWindowUpdate();
			//UpdateWindow();
			//maxminFlag = FALSE;
		}
	}
	// TODO:  在此处添加消息处理程序代码
}


void CBatteryMainFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CMDIChildWnd::OnSysCommand(nID, lParam);

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


void CBatteryMainFrame::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CMDIChildWnd::OnClose();
	//theApp.batteryMainWnd
	theApp.batteryMainWnd = NULL;
}


void CBatteryMainFrame::OnClipboardUpdate()
{
	// 此功能要求 Windows Vista 或更高版本。
	// _WIN32_WINNT 符号必须 >= 0x0600。
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CMDIChildWnd::OnClipboardUpdate();
}


void CBatteryMainFrame::OnSizeClipboard(CWnd* pClipAppWnd, HGLOBAL hRect)
{
	CMDIChildWnd::OnSizeClipboard(pClipAppWnd, hRect);
	// TODO:  在此处添加消息处理程序代码
}


void CBatteryMainFrame::OnNcLButtonDblClk(UINT nHitTest, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	
	maxminFlag = TRUE;
	CMDIChildWnd::OnNcLButtonDblClk(nHitTest, point);
	UpdateWindow();

}


void CBatteryMainFrame::OnInitMenu(CMenu* pMenu)
{
	CMDIChildWnd::OnInitMenu(pMenu);

}


LRESULT CBatteryMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO:  在此添加专用代码和/或调用基类
	return CMDIChildWnd::WindowProc(message, wParam, lParam);
}

LRESULT CBatteryMainFrame::OnCloseDateFileView(WPARAM wParam, LPARAM lParam)
{
	batteryCheckView->UnlockWindowUpdate();
	batteryCheckView->UpdateWindow();
	batteryCheckView->OnPaint();

	return NULL;
}


