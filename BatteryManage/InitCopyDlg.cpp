// InitCopyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "InitCopyDlg.h"
#include "afxdialogex.h"

// CInitCopyDlg �Ի���

IMPLEMENT_DYNAMIC(CInitCopyDlg, CDialog)

CInitCopyDlg::CInitCopyDlg(CWnd* pParent /*=NULL*/)
: CDialog(CInitCopyDlg::IDD, pParent)
{

}

CInitCopyDlg::~CInitCopyDlg()
{
}

void CInitCopyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOWER_LIST, lowerCheckList);
}


BEGIN_MESSAGE_MAP(CInitCopyDlg, CDialog)
	ON_BN_CLICKED(IDC_SELALL, &CInitCopyDlg::OnBnClickedSelall)
	ON_BN_CLICKED(IDC_DELALL, &CInitCopyDlg::OnBnClickedDelall)
	ON_BN_CLICKED(IDOK, &CInitCopyDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CInitCopyDlg ��Ϣ�������


BOOL CInitCopyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString str;
	int idx;
	for (idx = MIN_CAB_NUM; idx <= MAX_CAB_NUM; ++idx)
	{
		str.Format(_T("%d"), idx);
		lowerCheckList.AddString(str);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CInitCopyDlg::OnBnClickedSelall()
{
	int idx;

	for (idx = MIN_CAB_NUM; idx <= MAX_CAB_NUM; ++idx)
	{
		lowerCheckList.SetCheck(idx - 1, TRUE);
	}
}


void CInitCopyDlg::OnBnClickedDelall()
{
	int idx;
	for (idx = MIN_CAB_NUM; idx <= MAX_CAB_NUM; ++idx)
	{
		lowerCheckList.SetCheck(idx - 1, FALSE);
	}
}


void CInitCopyDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
}
