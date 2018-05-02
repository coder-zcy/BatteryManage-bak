// SW_CycleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "SW_CycleDlg.h"
#include "afxdialogex.h"


// CSW_CycleDlg 对话框

IMPLEMENT_DYNAMIC(CSW_CycleDlg, CDialog)

CSW_CycleDlg::CSW_CycleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSW_CycleDlg::IDD, pParent)
	, startStep(0)
	, cycleTime(0)
{

}

CSW_CycleDlg::~CSW_CycleDlg()
{
}

BOOL CSW_CycleDlg::OnInitDialog()
{
	CString tmp;
	tmp.Format(_T("%d"), theApp.startWorkDlg->cycleLastStep);
	//editEndStep.SetWindowTextW(tmp);
	//editEndStep.SetWindowTextW(_T("1"));	
	GetDlgItem(IDC_SW_CYCLE_ENDSTEP)->SetWindowTextW(tmp);
	return TRUE;
}

void CSW_CycleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, startStep);
	DDV_MinMaxInt(pDX, startStep, 1, 65536);
	DDX_Text(pDX, IDC_EDIT4, cycleTime);
	DDV_MinMaxInt(pDX, cycleTime, 1, 65536);
}


BEGIN_MESSAGE_MAP(CSW_CycleDlg, CDialog)
END_MESSAGE_MAP()


// CSW_CycleDlg 消息处理程序
