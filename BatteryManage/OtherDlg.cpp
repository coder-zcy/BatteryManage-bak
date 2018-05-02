// OtherDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "OtherDlg.h"
#include "afxdialogex.h"


// COtherDlg 对话框

IMPLEMENT_DYNAMIC(COtherDlg, CDialog)

COtherDlg::COtherDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COtherDlg::IDD, pParent)
{

}

COtherDlg::~COtherDlg()
{
}

void COtherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADD_PART, addPartChk);
	DDX_Control(pDX, IDC_TWO_PART, twoPartChk);
	DDX_Control(pDX, IDC_ONE_PART, onePartChk);
	DDX_Control(pDX, IDC_STOP_PART, stopPartChk);
	DDX_Control(pDX, IDC_CONST_PART, constPartChk);
	DDX_Control(pDX, IDC_LAY_PART, layPartChk);
	DDX_Control(pDX, IDC_STEP_EXCEPT, stepExceptChk);
	DDX_Control(pDX, IDC_VAVGPM_EXCEPT, vavgpmExceptChk);
	DDX_Control(pDX, IDC_VAVG_EXCEPT, vavgExceptChk);
	DDX_Control(pDX, IDC_VOVER_EXCEPT, voverExceptChk);
	DDX_Control(pDX, IDC_ALERT_EXCEPT, alertExceptChk);
	DDX_Control(pDX, IDC_VAVG_VAL, vavgEdit);
	DDX_Control(pDX, IDC_CREATE_BYTIME, createByTimeChk);
	DDX_Control(pDX, IDC_INIT_PATH, initPathEdit);
	DDX_Control(pDX, IDC_NEED_PARTDATA, needPartDataChk);
	DDX_Control(pDX, IDC_SAVE_CREATE, saveCreateChk);
	DDX_Control(pDX, IDC_MDB_POINT, mdbPointChk);
	DDX_Control(pDX, IDC_COPYTO_CATALOG, copyToCatalogChk);
}


BEGIN_MESSAGE_MAP(COtherDlg, CDialog)
	ON_BN_CLICKED(IDC_FILE_BROWSE, &COtherDlg::OnBnClickedFileBrowse)
END_MESSAGE_MAP()


// COtherDlg 消息处理程序


void COtherDlg::OnBnClickedFileBrowse()
{
	// TODO:  在此添加控件通知处理程序代码
}


BOOL COtherDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	otherPath = CBatteryUtils::GetConfigPath(_T("\\config\\init\\other.ini"));
	wchar_t str[MAX_PATH_LENGTH];

	addPartVal = GetPrivateProfileInt(_T("other"), _T("addPart"), 0, otherPath);
	twoPartVal = GetPrivateProfileInt(_T("other"), _T("twoPart"), 0, otherPath);
	onePartVal = GetPrivateProfileInt(_T("other"), _T("onePart"), 0, otherPath);
	stopPartVal = GetPrivateProfileInt(_T("other"), _T("stopPart"), 0, otherPath);
	constPartVal = GetPrivateProfileInt(_T("other"), _T("constPart"), 0, otherPath);
	layPartVal = GetPrivateProfileInt(_T("other"), _T("layPart"), 0, otherPath);
	stepExceptVal = GetPrivateProfileInt(_T("other"), _T("stepExcept"), 0, otherPath);
	vavgpmExceptVal = GetPrivateProfileInt(_T("other"), _T("vavgpmExcept"), 0, otherPath);
	vavgExceptVal = GetPrivateProfileInt(_T("other"), _T("vavgExcept"), 0, otherPath);
	voverExceptVal = GetPrivateProfileInt(_T("other"), _T("voverExcept"), 0, otherPath);
	alertExceptVal = GetPrivateProfileInt(_T("other"), _T("alertExcept"), 0, otherPath);
	vavgVal = GetPrivateProfileInt(_T("other"), _T("vavg"), 0, otherPath);
	createByTimeVal = GetPrivateProfileInt(_T("other"), _T("createByTime"), 0, otherPath);
	GetPrivateProfileString(_T("other"), _T("initPath"), _T("D:\\"), str, MAX_PATH_LENGTH, otherPath);
	initPathVal = str;

	needPartDataVal = GetPrivateProfileInt(_T("other"), _T("needPartData"), 0, otherPath);
	saveCreateVal = GetPrivateProfileInt(_T("other"), _T("saveCreate"), 0, otherPath);
	mdbPointVal = GetPrivateProfileInt(_T("other"), _T("mdbPoint"), 0, otherPath);
	copyToCatalogVal = GetPrivateProfileInt(_T("other"), _T("copyToCatalog"), 0, otherPath);


	addPartChk.SetCheck(addPartVal);
	twoPartChk.SetCheck(twoPartVal);
	onePartChk.SetCheck(onePartVal);
	stopPartChk.SetCheck(stopPartVal);
	constPartChk.SetCheck(constPartVal);
	layPartChk.SetCheck(layPartVal);
	stepExceptChk.SetCheck(stepExceptVal);
	vavgpmExceptChk.SetCheck(vavgpmExceptVal);
	vavgExceptChk.SetCheck(vavgExceptVal);
	voverExceptChk.SetCheck(voverExceptVal);
	alertExceptChk.SetCheck(alertExceptVal);
	_itow_s(vavgVal, str, 10);
	vavgEdit.SetWindowTextW(str);

	createByTimeChk.SetCheck(createByTimeVal);
	initPathEdit.SetWindowTextW(initPathVal);;
	needPartDataChk.SetCheck(needPartDataVal);
	saveCreateChk.SetCheck(saveCreateVal);
	mdbPointChk.SetCheck(mdbPointVal);
	copyToCatalogChk.SetCheck(copyToCatalogVal);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void COtherDlg::SaveOtherSet()
{
	if (MessageBox(_T("确定要保存其它设置么"), _T("提示"), MB_OKCANCEL | MB_ICONWARNING) == IDOK)
	{
		wchar_t intStr[INT_LENGTH];

		CString vavgStr;
		addPartVal = addPartChk.GetCheck();
		_itow_s(addPartVal, intStr, INT_LENGTH);
		WritePrivateProfileString(_T("other"), _T("addPart"), intStr, otherPath);

		twoPartVal = twoPartChk.GetCheck();
		_itow_s(twoPartVal, intStr, INT_LENGTH);
		WritePrivateProfileString(_T("other"), _T("twoPart"), intStr, otherPath);

		onePartVal = onePartChk.GetCheck();
		_itow_s(onePartVal, intStr, INT_LENGTH);
		WritePrivateProfileString(_T("other"), _T("onePart"), intStr, otherPath);

		stopPartVal = stopPartChk.GetCheck();
		_itow_s(stopPartVal, intStr, INT_LENGTH);
		WritePrivateProfileString(_T("other"), _T("stopPart"), intStr, otherPath);

		constPartVal = constPartChk.GetCheck();
		_itow_s(constPartVal, intStr, INT_LENGTH);
		WritePrivateProfileString(_T("other"), _T("constPart"), intStr, otherPath);

		layPartVal = layPartChk.GetCheck();
		_itow_s(layPartVal, intStr, INT_LENGTH);
		WritePrivateProfileString(_T("other"), _T("layPart"), intStr, otherPath);

		stepExceptVal = stepExceptChk.GetCheck();
		_itow_s(stepExceptVal, intStr, INT_LENGTH);
		WritePrivateProfileString(_T("other"), _T("stepExcept"), intStr, otherPath);

		vavgpmExceptVal = vavgpmExceptChk.GetCheck();
		_itow_s(vavgpmExceptVal, intStr, INT_LENGTH);
		WritePrivateProfileString(_T("other"), _T("vavgpmExcept"), intStr, otherPath);

		vavgExceptVal = vavgExceptChk.GetCheck();
		_itow_s(vavgExceptVal, intStr, INT_LENGTH);
		WritePrivateProfileString(_T("other"), _T("vavgExcept"), intStr, otherPath);

		voverExceptVal = voverExceptChk.GetCheck();
		_itow_s(voverExceptVal, intStr, INT_LENGTH);
		WritePrivateProfileString(_T("other"), _T("voverExcept"), intStr, otherPath);

		alertExceptVal = alertExceptChk.GetCheck();
		_itow_s(alertExceptVal, intStr, INT_LENGTH);
		WritePrivateProfileString(_T("other"), _T("alertExcept"), intStr, otherPath);

		vavgEdit.GetWindowTextW(vavgStr);
		WritePrivateProfileString(_T("other"), _T("vavg"), vavgStr, otherPath);

		createByTimeVal = createByTimeChk.GetCheck();
		_itow_s(createByTimeVal, intStr, INT_LENGTH);
		WritePrivateProfileString(_T("other"), _T("createByTime"), intStr, otherPath);

		initPathEdit.GetWindowTextW(initPathVal);;
		WritePrivateProfileString(_T("other"), _T("initPath"), initPathVal, otherPath);

		needPartDataVal = needPartDataChk.GetCheck();
		_itow_s(needPartDataVal, intStr, INT_LENGTH);
		WritePrivateProfileString(_T("other"), _T("needPartData"), intStr, otherPath);

		saveCreateVal = saveCreateChk.GetCheck();
		_itow_s(saveCreateVal, intStr, INT_LENGTH);
		WritePrivateProfileString(_T("other"), _T("saveCreate"), intStr, otherPath);

		mdbPointVal = mdbPointChk.GetCheck();
		_itow_s(mdbPointVal, intStr, INT_LENGTH);
		WritePrivateProfileString(_T("other"), _T("mdbPoint"), intStr, otherPath);

		copyToCatalogVal = copyToCatalogChk.GetCheck();
		_itow_s(copyToCatalogVal, intStr, INT_LENGTH);
		WritePrivateProfileString(_T("other"), _T("copyToCatalog"), intStr, otherPath);
		
		MessageBox(_T("保存其它设置成功!"));
	}
}

