// StatisticMenuDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "StatisticMenuDlg.h"
#include "afxdialogex.h"


// CStatisticMenuDlg 对话框

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


// CStatisticMenuDlg 消息处理程序


BOOL CStatisticMenuDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CStatisticMenuDlg::OnBnClickedRefreshBtn()
{
	CMDIFrameWnd* hMainFrame = (CMDIFrameWnd*)AfxGetMainWnd();
	CMDIChildWnd *hChild = (CMDIChildWnd *)hMainFrame->MDIGetActive();
	CView *hView = (CView *)hChild->GetActiveView();
	if (hView->IsKindOf(RUNTIME_CLASS(CDataFileView)))
	{
		HWND hWnd = hView->m_hWnd;
		// 向父窗口发送消息  
		if (hWnd == NULL) return (void)MessageBox(_T("获得父窗口句柄失败！"));
		CString flag = L"1";


		::SendNotifyMessage(hWnd, WM_REFRESG_DATAOPENVIEW_MSG, WPARAM(&flag), NULL);

	}
}


void CStatisticMenuDlg::OnBnClickedDataSrcBtn()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CStatisticMenuDlg::OnBnClickedLoadSegBtn()
{
	TCHAR szFilter[] = _T("文本文件(*.ini)|*.ini||");
	CFileDialog fileDlg(TRUE, _T("mdb"), NULL, 0, szFilter, theApp.m_pMainWnd);
	CString filePath;

	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		filePath = fileDlg.GetPathName();
		openFilePath = filePath;

		CMDIFrameWnd* hMainFrame = (CMDIFrameWnd*)AfxGetMainWnd();
		CMDIChildWnd *hChild = (CMDIChildWnd *)hMainFrame->MDIGetActive();
		CView *hView = (CView *)hChild->GetActiveView();
		if (hView->IsKindOf(RUNTIME_CLASS(CDataFileView)))
		{
			HWND hWnd = hView->m_hWnd;
			// 向父窗口发送消息  
			if (hWnd == NULL) return (void)MessageBox(_T("获得父窗口句柄失败！"));
			
			::SendNotifyMessage(hWnd, WM_UPDATE_PART_BAT_MSG, WPARAM(openFilePath.AllocSysString()), NULL);
		}
		
	}
}


void CStatisticMenuDlg::OnBnClickedSaveSegBtn()
{
	BOOL isOpen = FALSE;
	CString defaultDir = L"D:\\";
	CString fileName = L"test.ini";
	CString filter = L"文件(*.ini)|*.ini||";
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = L"D:\\test.ini";
	CString filePath = defaultDir + fileName;
	if (openFileDlg.DoModal() == IDOK)
	{
		CapShowType *capShowType = CapShowType::GetInstance();
		filePath = openFileDlg.GetPathName();
		capShowType->SavePartCapCondToFile(filePath);

		MessageBox(_T("保存区段信息成功"));
	}
	else
	{
		return;
	}
}
