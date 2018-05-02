// AdminLoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "AdminLoginDlg.h"
#include "afxdialogex.h"


// CAdminLoginDlg 对话框

IMPLEMENT_DYNAMIC(CAdminLoginDlg, CDialog)

CAdminLoginDlg::CAdminLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAdminLoginDlg::IDD, pParent)
{

}

CAdminLoginDlg::~CAdminLoginDlg()
{
}

void CAdminLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAdminLoginDlg, CDialog)
END_MESSAGE_MAP()


// CAdminLoginDlg 消息处理程序
