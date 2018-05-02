// DataFileFrame.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "DataFileFrame.h"
#include "BatteryMainFrame.h"

// CDataFileFrame

IMPLEMENT_DYNCREATE(CDataFileFrame, CMDIChildWnd)

CDataFileFrame::CDataFileFrame()
{

}

CDataFileFrame::~CDataFileFrame()
{

}


BEGIN_MESSAGE_MAP(CDataFileFrame, CMDIChildWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_GETMINMAXINFO()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_DESTROYCLIPBOARD()
	ON_WM_NCDESTROY()
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CDataFileFrame 消息处理程序


int CDataFileFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}


void CDataFileFrame::OnSetFocus(CWnd* pOldWnd)
{
	CMDIChildWnd::OnSetFocus(pOldWnd);

	dataFileView->SetFocus();

	// TODO:  在此处添加消息处理程序代码
}


BOOL CDataFileFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (dataFileView->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
	{
		return TRUE;
	}

	return CMDIChildWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


BOOL CDataFileFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO:  在此添加专用代码和/或调用基类
	CCreateContext cc;
	cc.m_pCurrentFrame = this;
	cc.m_pNewViewClass = RUNTIME_CLASS(CDataFileView);

	dataFileView = (CDataFileView*)CreateView(&cc);

	return NULL != dataFileView;
	//return CMDIChildWnd::OnCreateClient(lpcs, pContext);
}


void CDataFileFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	lpMMI->ptMinTrackSize.x = MIN_FRAME_WIDTH;

	lpMMI->ptMinTrackSize.y = MIN_FRAME_HEIGHT;
	CMDIChildWnd::OnGetMinMaxInfo(lpMMI);
}


void CDataFileFrame::ActivateFrame(int nCmdShow)
{
	// TODO:  在此添加专用代码和/或调用基类
	nCmdShow = SW_SHOWMAXIMIZED;
	CMDIChildWnd::ActivateFrame(nCmdShow);
}


BOOL CDataFileFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此添加专用代码和/或调用基类
	//this->SetTitle(openFilePath);
	cs.style &= ~FWS_ADDTOTITLE;
	return CMDIChildWnd::PreCreateWindow(cs);
}



void CDataFileFrame::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CMDIChildWnd::OnClose();
	CString flag = L"1";
	::SendNotifyMessage(theApp.batteryMainWnd->m_hWnd, WM_COLSE_DATAFILEVIEW_MSG, WPARAM(flag.AllocSysString()), NULL);
}


void CDataFileFrame::PostNcDestroy()
{
	// TODO:  在此添加专用代码和/或调用基类


	CMDIChildWnd::PostNcDestroy();

}


void CDataFileFrame::OnDestroy()
{
	
	CMDIChildWnd::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
}


void CDataFileFrame::OnDestroyClipboard()
{
	CMDIChildWnd::OnDestroyClipboard();

	// TODO:  在此处添加消息处理程序代码
}


void CDataFileFrame::OnNcDestroy()
{
	CMDIChildWnd::OnNcDestroy();

	// TODO:  在此处添加消息处理程序代码
}


void CDataFileFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CMDIChildWnd::OnSysCommand(nID, lParam);

	//if (nID == SC_CLOSE) {
	//	//UnlockWindowUpdate();
	//	//UpdateWindow();

	//	theApp.m_pMainWnd->SetActiveWindow();
	//	theApp.m_pMainWnd->Invalidate();
	//	theApp.m_pMainWnd->UpdateWindow();

	//	CBatteryMainFrame *batteryMainFrame = (CBatteryMainFrame *)theApp.batteryMainWnd;

	//	batteryMainFrame->GetActiveView()->Invalidate();
	//	batteryMainFrame->GetActiveView()->UpdateWindow();

	//	CBatteryMainView * batteryMainView = (CBatteryMainView*)(batteryMainFrame->GetActiveView());
	//	batteryMainView->OnPaint();
	//	batteryMainView->SetActiveWindow();
	//	
	//}
}
