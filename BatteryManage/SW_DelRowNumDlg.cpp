// SW_DelRowNumDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "SW_DelRowNumDlg.h"
#include "afxdialogex.h"


// CSW_DelRowNumDlg �Ի���

IMPLEMENT_DYNAMIC(CSW_DelRowNumDlg, CDialog)

CSW_DelRowNumDlg::CSW_DelRowNumDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSW_DelRowNumDlg::IDD, pParent)
{

}

CSW_DelRowNumDlg::~CSW_DelRowNumDlg()
{
}

void CSW_DelRowNumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SW_DELROWNUM, deleteRowNum);
	DDV_MinMaxInt(pDX, deleteRowNum, 1, 65535);
}


BEGIN_MESSAGE_MAP(CSW_DelRowNumDlg, CDialog)
END_MESSAGE_MAP()


// CSW_DelRowNumDlg ��Ϣ�������
