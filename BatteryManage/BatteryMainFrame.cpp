// BatteryCheckFrame.cpp : ʵ���ļ�
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


// CBatteryCheckFrame ��Ϣ�������


int CBatteryMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	//ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	// TODO:  �ڴ������ר�õĴ�������
	//ȡ��ϵͳ�˵�
	CMenu *pMenu = GetSystemMenu(FALSE);
	//ȡ��ϵͳ�˵�����
	int Count = pMenu->GetMenuItemCount();
	//ȡ�ùرղ˵���ID
	UINT id = pMenu->GetMenuItemID(Count - 1);
	//��ֹ�رղ˵�
	pMenu->EnableMenuItem(id, MF_GRAYED);

	return 0;
}


void CBatteryMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	CMDIChildWnd::OnSetFocus(pOldWnd);

	batteryCheckView->SetFocus();
	// TODO:  �ڴ˴������Ϣ����������
}


BOOL CBatteryMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// TODO:  �ڴ����ר�ô����/����û���
	if (batteryCheckView->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;
	return CMDIChildWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


BOOL CBatteryMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO:  �ڴ����ר�ô����/����û���
	//ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	CCreateContext cc;
	cc.m_pCurrentFrame = this;
	cc.m_pNewViewClass = RUNTIME_CLASS(CBatteryMainView);
	batteryCheckView = (CBatteryMainView *)CreateView(&cc);
	return NULL != batteryCheckView;

}


void CBatteryMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	lpMMI->ptMinTrackSize.x = MIN_FRAME_WIDTH;

	lpMMI->ptMinTrackSize.y = MIN_FRAME_HEIGHT;
		


	CMDIChildWnd::OnGetMinMaxInfo(lpMMI);

	//UnlockWindowUpdate();
	//UpdateWindow();
	

	


}


BOOL CBatteryMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ����ר�ô����/����û���
	//cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE | WS_THICKFRAME
	//	| WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
	//cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

	return CMDIChildWnd::PreCreateWindow(cs);
}


void CBatteryMainFrame::ActivateFrame(int nCmdShow)
{
	// TODO:  �ڴ����ר�ô����/����û���

	nCmdShow = SW_SHOWMAXIMIZED;
	CMDIChildWnd::ActivateFrame(nCmdShow);
}


void CBatteryMainFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	paintFlag = TRUE;

	//CBitmap bmp;;//����һ��λͼ����
	//CDC memDC;  //���ȶ���һ����ʾ�豸����
	////dc.SetBkColor();
	//CRect rect;
	//GetClientRect(&rect);
	//CDC *pdc = GetDC();
	//bmp.CreateCompatibleBitmap(pdc, rect.Width(), rect.Height());
	////bmp.LoadBitmap(IDB_MAINBMP);//�ϴ�λͼ������Ҫ�޸�Ϊ�ı���ͼ��

	//memDC.CreateCompatibleDC(pdc);
	//memDC.SelectObject(&bmp);
	////��ȡ���ڵĴ�С 
	//BITMAP bmInfo;
	//bmp.GetBitmap(&bmInfo);
	//int width = bmInfo.bmWidth;
	//int heigth = bmInfo.bmHeight;
	//CRect rc;
	//GetClientRect(rc);
	//pdc->SetStretchBltMode(COLORONCOLOR);
	//pdc->StretchBlt(0, 0, rc.Width(), rc.Height(), &memDC, 0, 0, width, heigth, SRCCOPY);
	////��ͼ��ɺ������
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
	// TODO:  �ڴ˴������Ϣ����������
}


void CBatteryMainFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CMDIChildWnd::OnClose();
	//theApp.batteryMainWnd
	theApp.batteryMainWnd = NULL;
}


void CBatteryMainFrame::OnClipboardUpdate()
{
	// �˹���Ҫ�� Windows Vista ����߰汾��
	// _WIN32_WINNT ���ű��� >= 0x0600��
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CMDIChildWnd::OnClipboardUpdate();
}


void CBatteryMainFrame::OnSizeClipboard(CWnd* pClipAppWnd, HGLOBAL hRect)
{
	CMDIChildWnd::OnSizeClipboard(pClipAppWnd, hRect);
	// TODO:  �ڴ˴������Ϣ����������
}


void CBatteryMainFrame::OnNcLButtonDblClk(UINT nHitTest, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
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
	// TODO:  �ڴ����ר�ô����/����û���
	return CMDIChildWnd::WindowProc(message, wParam, lParam);
}

LRESULT CBatteryMainFrame::OnCloseDateFileView(WPARAM wParam, LPARAM lParam)
{
	batteryCheckView->UnlockWindowUpdate();
	batteryCheckView->UpdateWindow();
	batteryCheckView->OnPaint();

	return NULL;
}


