// StatisticMenuDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "StatisticMenuDlg.h"
#include "afxdialogex.h"


// CStatisticMenuDlg �Ի���

IMPLEMENT_DYNAMIC(CStatisticMenuDlg, CDialog)

CStatisticMenuDlg::CStatisticMenuDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStatisticMenuDlg::IDD, pParent)
{

}

CStatisticMenuDlg::~CStatisticMenuDlg()
{
}

void CStatisticMenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStatisticMenuDlg, CDialog)
	ON_BN_CLICKED(ID_REFRESH_BTN, &CStatisticMenuDlg::OnBnClickedRefreshBtn)
	ON_BN_CLICKED(IDC_DATA_SRC_BTN, &CStatisticMenuDlg::OnBnClickedDataSrcBtn)
	ON_BN_CLICKED(IDC_LOAD_SEG_BTN, &CStatisticMenuDlg::OnBnClickedLoadSegBtn)
	ON_BN_CLICKED(IDC_SAVE_SEG_BTN, &CStatisticMenuDlg::OnBnClickedSaveSegBtn)
END_MESSAGE_MAP()


// CStatisticMenuDlg ��Ϣ�������


BOOL CStatisticMenuDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CStatisticMenuDlg::OnBnClickedRefreshBtn()
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


void CStatisticMenuDlg::OnBnClickedDataSrcBtn()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CStatisticMenuDlg::OnBnClickedLoadSegBtn()
{
	TCHAR szFilter[] = _T("�ı��ļ�(*.ini)|*.ini||");
	CFileDialog fileDlg(TRUE, _T("mdb"), NULL, 0, szFilter, theApp.m_pMainWnd);
	CString filePath;

	if (IDOK == fileDlg.DoModal())
	{
		// ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭����   
		filePath = fileDlg.GetPathName();
		openFilePath = filePath;

		CMDIFrameWnd* hMainFrame = (CMDIFrameWnd*)AfxGetMainWnd();
		CMDIChildWnd *hChild = (CMDIChildWnd *)hMainFrame->MDIGetActive();
		CView *hView = (CView *)hChild->GetActiveView();
		if (hView->IsKindOf(RUNTIME_CLASS(CDataFileView)))
		{
			HWND hWnd = hView->m_hWnd;
			// �򸸴��ڷ�����Ϣ  
			if (hWnd == NULL) return (void)MessageBox(_T("��ø����ھ��ʧ�ܣ�"));
			
			::SendNotifyMessage(hWnd, WM_UPDATE_PART_BAT_MSG, WPARAM(openFilePath.AllocSysString()), NULL);
		}
		
	}
}


void CStatisticMenuDlg::OnBnClickedSaveSegBtn()
{
	BOOL isOpen = FALSE;
	CString defaultDir = L"D:\\";
	CString fileName = L"test.ini";
	CString filter = L"�ļ�(*.ini)|*.ini||";
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = L"D:\\test.ini";
	CString filePath = defaultDir + fileName;
	if (openFileDlg.DoModal() == IDOK)
	{
		CapShowType *capShowType = CapShowType::GetInstance();
		filePath = openFileDlg.GetPathName();
		capShowType->SavePartCapCondToFile(filePath);

		MessageBox(_T("����������Ϣ�ɹ�"));
	}
	else
	{
		return;
	}
}
