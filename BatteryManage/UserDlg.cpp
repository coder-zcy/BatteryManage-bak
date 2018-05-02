// UserDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "UserDlg.h"
#include "afxdialogex.h"


// CUserDlg 对话框

IMPLEMENT_DYNAMIC(CUserDlg, CDialog)

CUserDlg::CUserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserDlg::IDD, pParent)
{

}

CUserDlg::~CUserDlg()
{
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHART_NAME, chartNameEdit);
	DDX_Control(pDX, IDC_BODY, bodyEdit);
	DDX_Control(pDX, IDC_DATA, dataEdit);
	DDX_Control(pDX, IDC_REMARK, remarkEdit);
	DDX_Control(pDX, IDC_INIT_REMOVE, initRemoveChk);
	DDX_Control(pDX, IDC_OVER_REMOVE, overRemoveChk);
	DDX_Control(pDX, IDC_SHOW_CAP, showCapChk);
}


BEGIN_MESSAGE_MAP(CUserDlg, CDialog)
END_MESSAGE_MAP()


// CUserDlg 消息处理程序


BOOL CUserDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	wchar_t str[INT_LENGTH];
	userSetPath = CBatteryUtils::GetConfigPath(_T("\\config\\init\\user.ini"));

	maRadVal = GetPrivateProfileInt(_T("show"), _T("maRad"), 0, userSetPath);
	aradVal = GetPrivateProfileInt(_T("show"), _T("arad"), 0, userSetPath);
	chartNameVal = GetPrivateProfileInt(_T("show"), _T("chartNameSize"), 0, userSetPath);
	bodyVal = GetPrivateProfileInt(_T("show"), _T("bodySize"), 0, userSetPath);
	dataVal = GetPrivateProfileInt(_T("show"), _T("dataSize"), 0, userSetPath);
	remarkVal = GetPrivateProfileInt(_T("show"), _T("remarkSize"), 0, userSetPath);
	
	initRemoveVal = GetPrivateProfileInt(_T("other"), _T("initRemove"), 0, userSetPath);
	overRemoveVal = GetPrivateProfileInt(_T("other"), _T("overRemove"), 0, userSetPath);
	showCapVal = GetPrivateProfileInt(_T("other"), _T("showCap"), 0, userSetPath);

	((CButton *)GetDlgItem(IDC_MA_RAD))->SetCheck(maRadVal == 1 ? TRUE : FALSE);
	((CButton *)GetDlgItem(IDC_A_RAD))->SetCheck(aradVal == 1 ? TRUE : FALSE);

	_itow_s(chartNameVal, str, INT_LENGTH);
	chartNameEdit.SetWindowTextW(str);

	_itow_s(bodyVal, str, INT_LENGTH);
	bodyEdit.SetWindowTextW(str);
	
	_itow_s(dataVal, str, INT_LENGTH);
	dataEdit.SetWindowTextW(str);

	_itow_s(remarkVal, str, INT_LENGTH);
	remarkEdit.SetWindowTextW(str);

	initRemoveChk.SetCheck(initRemoveVal);
	overRemoveChk.SetCheck(overRemoveVal);
	showCapChk.SetCheck(showCapVal);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CUserDlg::SaveUserSet()
{
	if (MessageBox(_T("确定要保存用户设置么"), _T("提示"), MB_OKCANCEL | MB_ICONWARNING) == IDOK)
	{

		wchar_t str[INT_LENGTH];
		maRadVal = ((CButton *)GetDlgItem(IDC_MA_RAD))->GetCheck() == TRUE ? 1 : 0;
		WritePrivateProfileString(_T("show"), _T("maRad"),
			maRadVal == 1 ? _T("1") : _T("0"), userSetPath);

		aradVal = ((CButton *)GetDlgItem(IDC_A_RAD))->GetCheck() == TRUE ? 1 : 0;
		WritePrivateProfileString(_T("show"), _T("aRad"),
			aradVal == 1 ? _T("1") : _T("0"), userSetPath);

		chartNameEdit.GetWindowTextW(str, INT_LENGTH);
		WritePrivateProfileString(_T("show"), _T("chartNameSize"), str, userSetPath);

		bodyEdit.GetWindowTextW(str, INT_LENGTH);
		WritePrivateProfileString(_T("show"), _T("bodySize"), str, userSetPath);

		dataEdit.GetWindowTextW(str, INT_LENGTH);
		WritePrivateProfileString(_T("show"), _T("dataSize"), str, userSetPath);

		remarkEdit.GetWindowTextW(str, INT_LENGTH);
		WritePrivateProfileString(_T("show"), _T("remarkSize"), str, userSetPath);

		initRemoveVal = initRemoveChk.GetCheck();
		_itow_s(initRemoveVal, str, INT_LENGTH);
		WritePrivateProfileString(_T("other"), _T("initRemove"), str, userSetPath);

		overRemoveVal = overRemoveChk.GetCheck();
		_itow_s(overRemoveVal, str, INT_LENGTH);
		WritePrivateProfileString(_T("other"), _T("overRemove"), str, userSetPath);

		showCapVal = showCapChk.GetCheck();
		_itow_s(showCapVal, str, INT_LENGTH);
		WritePrivateProfileString(_T("other"), _T("showCap"), str, userSetPath);

		MessageBox(_T("用户设置保存成功!"));
	}
}