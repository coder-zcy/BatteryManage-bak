// ScreenSelDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "ScreenSelDlg.h"
#include "afxdialogex.h"


// CScreenSelDlg 对话框

IMPLEMENT_DYNAMIC(CScreenSelDlg, CDialog)

CScreenSelDlg::CScreenSelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScreenSelDlg::IDD, pParent)
{

}

CScreenSelDlg::~CScreenSelDlg()
{
}

void CScreenSelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CScreenSelDlg, CDialog)
END_MESSAGE_MAP()


// CScreenSelDlg 消息处理程序
