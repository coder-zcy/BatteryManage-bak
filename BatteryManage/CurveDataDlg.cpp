// CurveDataDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "CurveDataDlg.h"
#include "afxdialogex.h"


// CCurveDataDlg 对话框

IMPLEMENT_DYNAMIC(CCurveDataDlg, CDialog)

CCurveDataDlg::CCurveDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCurveDataDlg::IDD, pParent)
{

}

CCurveDataDlg::~CCurveDataDlg()
{
}

void CCurveDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCurveDataDlg, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CCurveDataDlg 消息处理程序


void CCurveDataDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
}
