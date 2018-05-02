// SetNumDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "SetNumDlg.h"
#include "afxdialogex.h"


// CSetNODlg 对话框

IMPLEMENT_DYNAMIC(CSetNumDlg, CDialog)

CSetNumDlg::CSetNumDlg(CWnd* pParent /*=NULL*/)
: CDialog(CSetNumDlg::IDD, pParent)
{

}

CSetNumDlg::~CSetNumDlg()
{
}

void CSetNumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INVALID_NO_EDIT, invalidNOEdit);
	DDX_Control(pDX, IDC_OP_NO_COMBO, opNOCombo);
	DDX_Control(pDX, IDC_INVALIDSET_NO_EDIT, invalidSetEdit);
	DDX_Control(pDX, IDC_FROM_NO_COMBO, fromNOCombo);
	DDX_Control(pDX, IDC_NOMM, noMMBtn);
	DDX_Control(pDX, IDC_NOMP, noMPBtn);
	DDX_Control(pDX, IDC_APPLY_BTN, applyBtn);
	DDX_Control(pDX, IDC_OP_NO_LIST, opNOList);
	DDX_Control(pDX, ID_OP_NO_SET_OK, opNOSetOK);
	DDX_Control(pDX, ID_OP_NO_SET_CANCEL, opNOSetCancel);
}


BEGIN_MESSAGE_MAP(CSetNumDlg, CDialog)
END_MESSAGE_MAP()


// CSetNODlg 消息处理程序
