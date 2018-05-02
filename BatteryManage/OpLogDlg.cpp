// OpLogDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "OpLogDlg.h"
#include "afxdialogex.h"


// COpLogDlg 对话框

IMPLEMENT_DYNAMIC(COpLogDlg, CDialog)

COpLogDlg::COpLogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COpLogDlg::IDD, pParent)
{

}

COpLogDlg::~COpLogDlg()
{
}

void COpLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COpLogDlg, CDialog)
END_MESSAGE_MAP()


// COpLogDlg 消息处理程序
