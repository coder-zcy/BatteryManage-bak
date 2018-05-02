// SW_NumberingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "SW_NumberingDlg.h"
#include "afxdialogex.h"

#define MAX_BATTERY_CABINET 20
#define MAX_BATTERY_NUM 512
// CSW_NumberingDlg 对话框

IMPLEMENT_DYNAMIC(CSW_NumberingDlg, CDialog)

CSW_NumberingDlg::CSW_NumberingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSW_NumberingDlg::IDD, pParent)
{

}

CSW_NumberingDlg::~CSW_NumberingDlg()
{
}

void CSW_NumberingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SW_NUM_COM, ComCabinet);
	DDX_Control(pDX, IDC_SW_NUM_APPLY, BtnApply);
	DDX_Control(pDX, IDC_SW_NUM_LOAD, BtnLoad);
	DDX_Control(pDX, IDC_SW_NUMBERINGLIST, numberingList);
}

BOOL CSW_NumberingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	for (int i = 1; i < 21; ++i)
	{
		CString str;
		str.Format(_T("%d"), i);
		ComCabinet.AddString(str);
	}

	for (int i = 0; i < MAX_BATTERY_CABINET; ++i)
	{
		std::vector<int> tmp;
		for (int j = 0; j < MAX_BATTERY_NUM; ++j)
		{
			tmp.push_back(j + 1);
		}
		battery_number.push_back(tmp);
	}

	LVCOLUMN lvColumn;

	numberingList.SetExtendedStyle(LVS_EX_GRIDLINES);
	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 50;
	lvColumn.pszText = TEXT("所在工位");
	numberingList.InsertColumn(0, &lvColumn);

	numberingList.SetExtendedStyle(LVS_EX_GRIDLINES);
	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 50;
	lvColumn.pszText = TEXT("电芯编号");
	numberingList.InsertColumn(1, &lvColumn);

	LVITEM lvItem;
	int nItem;
	for (int j = MAX_BATTERY_NUM - 1; j >= 0; --j)
	{
		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = 0;
		lvItem.iSubItem = 0;
		CString str;
		str.Format(_T("%d"), j + 1);
		lvItem.pszText = str.GetBuffer();
		nItem = numberingList.InsertItem(&lvItem);
		numberingList.SetItemText(nItem, 0, str);
		str.Format(_T("%d"), battery_number[0][j]);
		numberingList.SetItemText(nItem, 1, str);
	}

	//battery_number[2][0] = 12344;
	return TRUE;

}


BEGIN_MESSAGE_MAP(CSW_NumberingDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_SW_NUM_COM, &CSW_NumberingDlg::OnCbnSelchangeSwNumCom)
	ON_BN_CLICKED(IDC_SW_NUM_APPLY, &CSW_NumberingDlg::OnBnClickedSwNumApply)
	ON_BN_CLICKED(IDC_SW_NUM_LOAD, &CSW_NumberingDlg::OnBnClickedSwNumLoad)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CSW_NumberingDlg 消息处理程序


void CSW_NumberingDlg::OnCbnSelchangeSwNumCom()
{
	// TODO:  在此添加控件通知处理程序代码
	int nSel;
	nSel = ComCabinet.GetCurSel();

	numberingList.DeleteAllItems();
	LVITEM lvItem;
	int nItem;
	for (int j = MAX_BATTERY_NUM - 1; j >= 0; --j)
	{
		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = 0;
		lvItem.iSubItem = 0;
		CString str;
		str.Format(_T("%d"), j + 1);
		lvItem.pszText = str.GetBuffer();
		nItem = numberingList.InsertItem(&lvItem);
		numberingList.SetItemText(nItem, 0, str);
		str.Format(_T("%d"), battery_number[nSel][j]);
		numberingList.SetItemText(nItem, 1, str);
	}
}


void CSW_NumberingDlg::OnBnClickedSwNumApply()
{
	// TODO:  在此添加控件通知处理程序代码
	MessageBox(_T("处理逻辑，改变工位的起始编号，需要了解需求"));
}


void CSW_NumberingDlg::OnBnClickedSwNumLoad()
{
	// TODO:  在此添加控件通知处理程序代码
	MessageBox(_T("载入文件"));
}


void CSW_NumberingDlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}
