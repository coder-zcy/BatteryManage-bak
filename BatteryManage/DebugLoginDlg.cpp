// DebugLoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "DebugLoginDlg.h"
#include "afxdialogex.h"


// CDebugLoginDlg 对话框

IMPLEMENT_DYNAMIC(CDebugLoginDlg, CDialog)

CDebugLoginDlg::CDebugLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDebugLoginDlg::IDD, pParent)
{

}

CDebugLoginDlg::~CDebugLoginDlg()
{
}

void CDebugLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDebugLoginDlg, CDialog)
END_MESSAGE_MAP()


// CDebugLoginDlg 消息处理程序
