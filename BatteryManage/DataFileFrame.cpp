// DataFileFrame.cpp : ʵ���ļ�
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


// CDataFileFrame ��Ϣ�������


int CDataFileFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}


void CDataFileFrame::OnSetFocus(CWnd* pOldWnd)
{
	CMDIChildWnd::OnSetFocus(pOldWnd);

	dataFileView->SetFocus();

	// TODO:  �ڴ˴������Ϣ����������
}


BOOL CDataFileFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// TODO:  �ڴ����ר�ô����/����û���
	if (dataFileView->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
	{
		return TRUE;
	}

	return CMDIChildWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


BOOL CDataFileFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO:  �ڴ����ר�ô����/����û���
	CCreateContext cc;
	cc.m_pCurrentFrame = this;
	cc.m_pNewViewClass = RUNTIME_CLASS(CDataFileView);

	dataFileView = (CDataFileView*)CreateView(&cc);

	return NULL != dataFileView;
	//return CMDIChildWnd::OnCreateClient(lpcs, pContext);
}


void CDataFileFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	lpMMI->ptMinTrackSize.x = MIN_FRAME_WIDTH;

	lpMMI->ptMinTrackSize.y = MIN_FRAME_HEIGHT;
	CMDIChildWnd::OnGetMinMaxInfo(lpMMI);
}


void CDataFileFrame::ActivateFrame(int nCmdShow)
{
	// TODO:  �ڴ����ר�ô����/����û���
	nCmdShow = SW_SHOWMAXIMIZED;
	CMDIChildWnd::ActivateFrame(nCmdShow);
}


BOOL CDataFileFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ����ר�ô����/����û���
	//this->SetTitle(openFilePath);
	cs.style &= ~FWS_ADDTOTITLE;
	return CMDIChildWnd::PreCreateWindow(cs);
}



void CDataFileFrame::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CMDIChildWnd::OnClose();
	CString flag = L"1";
	::SendNotifyMessage(theApp.batteryMainWnd->m_hWnd, WM_COLSE_DATAFILEVIEW_MSG, WPARAM(flag.AllocSysString()), NULL);
}


void CDataFileFrame::PostNcDestroy()
{
	// TODO:  �ڴ����ר�ô����/����û���


	CMDIChildWnd::PostNcDestroy();

}


void CDataFileFrame::OnDestroy()
{
	
	CMDIChildWnd::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
}


void CDataFileFrame::OnDestroyClipboard()
{
	CMDIChildWnd::OnDestroyClipboard();

	// TODO:  �ڴ˴������Ϣ����������
}


void CDataFileFrame::OnNcDestroy()
{
	CMDIChildWnd::OnNcDestroy();

	// TODO:  �ڴ˴������Ϣ����������
}


void CDataFileFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
