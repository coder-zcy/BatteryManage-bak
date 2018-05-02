// CapExportDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "CapExportDlg.h"
#include "afxdialogex.h"


// CCapExportDlg 对话框

IMPLEMENT_DYNAMIC(CCapExportDlg, CDialog)

CCapExportDlg::CCapExportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCapExportDlg::IDD, pParent)
{

}

CCapExportDlg::~CCapExportDlg()
{
}

void CCapExportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCapExportDlg, CDialog)
END_MESSAGE_MAP()


// CCapExportDlg 消息处理程序
