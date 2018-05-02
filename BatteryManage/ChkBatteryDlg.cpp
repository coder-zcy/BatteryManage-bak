// ChkBatteryDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "ChkBatteryDlg.h"
#include "afxdialogex.h"


// CChkBatteryDlg 对话框

IMPLEMENT_DYNAMIC(CChkBatteryDlg, CDialog)

CChkBatteryDlg::CChkBatteryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChkBatteryDlg::IDD, pParent)
{

}

CChkBatteryDlg::~CChkBatteryDlg()
{
}

void CChkBatteryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChkBatteryDlg, CDialog)
END_MESSAGE_MAP()


// CChkBatteryDlg 消息处理程序
