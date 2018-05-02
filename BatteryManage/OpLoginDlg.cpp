// OpLoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "OpLoginDlg.h"
#include "afxdialogex.h"


// COpLoginDlg 对话框

IMPLEMENT_DYNAMIC(COpLoginDlg, CDialog)

COpLoginDlg::COpLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COpLoginDlg::IDD, pParent)
{

}

COpLoginDlg::~COpLoginDlg()
{
}

void COpLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COpLoginDlg, CDialog)
END_MESSAGE_MAP()


// COpLoginDlg 消息处理程序
