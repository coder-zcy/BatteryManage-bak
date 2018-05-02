// LoopDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "LoopDlg.h"
#include "afxdialogex.h"


// CLoopDlg 对话框

IMPLEMENT_DYNAMIC(CLoopDlg, CDialog)

CLoopDlg::CLoopDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoopDlg::IDD, pParent)
{

}

CLoopDlg::~CLoopDlg()
{
}

void CLoopDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLoopDlg, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CLoopDlg 消息处理程序


void CLoopDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
}
