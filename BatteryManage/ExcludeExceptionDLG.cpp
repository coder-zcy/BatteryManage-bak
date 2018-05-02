// ExcludeExceptionDLG.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "ExcludeExceptionDLG.h"
#include "afxdialogex.h"


// CExcludeExceptionDLG �Ի���

IMPLEMENT_DYNAMIC(CExcludeExceptionDLG, CDialog)

CExcludeExceptionDLG::CExcludeExceptionDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CExcludeExceptionDLG::IDD, pParent)
{

}

CExcludeExceptionDLG::~CExcludeExceptionDLG()
{
}

void CExcludeExceptionDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BCG_EEDlg_CHECK1, current_exption);
	DDX_Control(pDX, IDC_BCG_EEDlg_CHECK2, charge_delterI_warning);
	DDX_Control(pDX, IDC_BCG_EEDlg_CHECK3, leak_current_warning);
	DDX_Control(pDX, IDC_BCG_EEDlg_CHECK4, voltage_exception);
	DDX_Control(pDX, IDC_BCG_EEDlg_CHECK5, open_voltage_outofrange);
	DDX_Control(pDX, IDC_BCG_EEDlg_CHECK6, charge_deltaV_warning);
	DDX_Control(pDX, IDC_BCG_EEDlg_CHECK7, discharge_deltaV_warning);
	DDX_Control(pDX, IDC_BCG_EEDlg_CHECK8, OCV_exception);
	DDX_Control(pDX, IDC_BCG_EEDlg_CHECK9, voltage_high_warning);
	DDX_Control(pDX, IDC_BCG_EEDlg_CHECK10, capacity_over_warning);
	DDX_Control(pDX, IDC_BCG_EEDlg_CHECK21, poor_contact);
}


BEGIN_MESSAGE_MAP(CExcludeExceptionDLG, CDialog)
	ON_BN_CLICKED(IDC_BCG_EEDlg_RADIO1, &CExcludeExceptionDLG::OnBnClickedBcgEedlgRadio1)
	ON_BN_CLICKED(IDC_BCG_EEDlg_RADIO2, &CExcludeExceptionDLG::OnBnClickedBcgEedlgRadio2)
	ON_BN_CLICKED(IDC_BCG_EEDlg_RADIO3, &CExcludeExceptionDLG::OnBnClickedBcgEedlgRadio3)
	ON_BN_CLICKED(IDC_BCG_EEDlg_RADIO4, &CExcludeExceptionDLG::OnBnClickedBcgEedlgRadio4)
END_MESSAGE_MAP()


// CExcludeExceptionDLG ��Ϣ�������


void CExcludeExceptionDLG::OnBnClickedBcgEedlgRadio1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	current_exption.SetCheck(BST_CHECKED);
	charge_delterI_warning.SetCheck(BST_CHECKED);
	leak_current_warning.SetCheck(BST_CHECKED);
	voltage_exception.SetCheck(BST_CHECKED);
	open_voltage_outofrange.SetCheck(BST_CHECKED);
	charge_deltaV_warning.SetCheck(BST_CHECKED);
	discharge_deltaV_warning.SetCheck(BST_CHECKED);
	OCV_exception.SetCheck(BST_CHECKED);
	voltage_high_warning.SetCheck(BST_CHECKED);
	capacity_over_warning.SetCheck(BST_CHECKED);
	poor_contact.SetCheck(BST_CHECKED);
}


void CExcludeExceptionDLG::OnBnClickedBcgEedlgRadio2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	current_exption.SetCheck(BST_UNCHECKED);
	charge_delterI_warning.SetCheck(BST_UNCHECKED);
	leak_current_warning.SetCheck(BST_UNCHECKED);
	voltage_exception.SetCheck(BST_UNCHECKED);
	open_voltage_outofrange.SetCheck(BST_UNCHECKED);
	charge_deltaV_warning.SetCheck(BST_UNCHECKED);
	discharge_deltaV_warning.SetCheck(BST_UNCHECKED);
	OCV_exception.SetCheck(BST_UNCHECKED);
	voltage_high_warning.SetCheck(BST_UNCHECKED);
	capacity_over_warning.SetCheck(BST_UNCHECKED);
	poor_contact.SetCheck(BST_UNCHECKED);
}


void CExcludeExceptionDLG::OnBnClickedBcgEedlgRadio3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	OnBnClickedBcgEedlgRadio2();
	current_exption.SetCheck(BST_CHECKED);
	charge_delterI_warning.SetCheck(BST_CHECKED);
	leak_current_warning.SetCheck(BST_CHECKED);
}


void CExcludeExceptionDLG::OnBnClickedBcgEedlgRadio4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	OnBnClickedBcgEedlgRadio2();
	voltage_exception.SetCheck(BST_CHECKED);
	open_voltage_outofrange.SetCheck(BST_CHECKED);
	charge_deltaV_warning.SetCheck(BST_CHECKED);
	discharge_deltaV_warning.SetCheck(BST_CHECKED);
	OCV_exception.SetCheck(BST_CHECKED);
	voltage_high_warning.SetCheck(BST_CHECKED);
}
