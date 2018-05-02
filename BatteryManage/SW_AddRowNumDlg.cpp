// SW_AddRowNumDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "SW_AddRowNumDlg.h"
#include "afxdialogex.h"


// CSW_AddRowNumDlg 对话框

IMPLEMENT_DYNAMIC(CSW_AddRowNumDlg, CDialog)

CSW_AddRowNumDlg::CSW_AddRowNumDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSW_AddRowNumDlg::IDD, pParent)
{

}

CSW_AddRowNumDlg::~CSW_AddRowNumDlg()
{
}

void CSW_AddRowNumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SW_ADDROWNUM, rowNum);
	DDV_MinMaxInt(pDX, rowNum, 1, 65535);
}


BEGIN_MESSAGE_MAP(CSW_AddRowNumDlg, CDialog)
END_MESSAGE_MAP()


// CSW_AddRowNumDlg 消息处理程序
