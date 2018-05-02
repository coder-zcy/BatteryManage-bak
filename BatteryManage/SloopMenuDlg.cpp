// SloopMenuDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "SloopMenuDlg.h"
#include "afxdialogex.h"


// CSloopMenuDlg �Ի���

IMPLEMENT_DYNAMIC(CSloopMenuDlg, CDialog)

CSloopMenuDlg::CSloopMenuDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSloopMenuDlg::IDD, pParent)
{

}

CSloopMenuDlg::~CSloopMenuDlg()
{
}

void CSloopMenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATA_CHK, dataCheck);
}


BEGIN_MESSAGE_MAP(CSloopMenuDlg, CDialog)
	ON_BN_CLICKED(IDC_DATA_CHK, &CSloopMenuDlg::OnBnClickedDataChk)
	ON_BN_CLICKED(ID_REFRESH_BTN, &CSloopMenuDlg::OnBnClickedRefreshBtn)
END_MESSAGE_MAP()


// CSloopMenuDlg ��Ϣ�������


void CSloopMenuDlg::OnBnClickedDataChk()
{
	int check = dataCheck.GetCheck();

	CMDIFrameWnd* hMainFrame = (CMDIFrameWnd*)AfxGetMainWnd();
	CMDIChildWnd *hChild = (CMDIChildWnd *)hMainFrame->MDIGetActive();
	CView *hView = (CView *)hChild->GetActiveView();
	if (hView->IsKindOf(RUNTIME_CLASS(CDataFileView)))
	{
		HWND hWnd = hView->m_hWnd;
		// �򸸴��ڷ�����Ϣ  
		if (hWnd == NULL) return (void)MessageBox(_T("��ø����ھ��ʧ�ܣ�"));
		CString str;
		str.Format(_T("%d"), check);
		::SendNotifyMessage(hWnd, WM_LOOP_MENU_DATA_CHECK_MSG, WPARAM(str.AllocSysString()), NULL);

	}
	
}


void CSloopMenuDlg::OnBnClickedRefreshBtn()
{
	CMDIFrameWnd* hMainFrame = (CMDIFrameWnd*)AfxGetMainWnd();
	CMDIChildWnd *hChild = (CMDIChildWnd *)hMainFrame->MDIGetActive();
	CView *hView = (CView *)hChild->GetActiveView();
	if (hView->IsKindOf(RUNTIME_CLASS(CDataFileView)))
	{
		HWND hWnd = hView->m_hWnd;
		// �򸸴��ڷ�����Ϣ  
		if (hWnd == NULL) return (void)MessageBox(_T("��ø����ھ��ʧ�ܣ�"));
		CString flag = L"1";

		::SendNotifyMessage(hWnd, WM_REFRESG_DATAOPENVIEW_MSG, WPARAM(&flag), NULL);
	}
}
