// OpManageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "OpManageDlg.h"
#include "afxdialogex.h"


// COpManageDlg 对话框

IMPLEMENT_DYNAMIC(COpManageDlg, CDialog)

COpManageDlg::COpManageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COpManageDlg::IDD, pParent)
{

}

COpManageDlg::~COpManageDlg()
{
}

void COpManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COpManageDlg, CDialog)
END_MESSAGE_MAP()


// COpManageDlg 消息处理程序
