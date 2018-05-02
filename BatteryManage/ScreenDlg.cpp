// ScreenDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "ScreenDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;


// CScreenDlg 对话框

IMPLEMENT_DYNAMIC(CScreenDlg, CDialog)

CScreenDlg::CScreenDlg(CWnd* pParent /*=NULL*/)
: CDialog(CScreenDlg::IDD, pParent)
{
	this->copyDlg = NULL;

	// 初始化屏号(柜号)
	screenChks.clear();
	screenChks.push_back(&screenChk1);
	screenChks.push_back(&screenChk2);
	screenChks.push_back(&screenChk3);
	screenChks.push_back(&screenChk4);
	screenChks.push_back(&screenChk5);

	screenChks.push_back(&screenChk6);
	screenChks.push_back(&screenChk7);
	screenChks.push_back(&screenChk8);
	screenChks.push_back(&screenChk9);
	screenChks.push_back(&screenChk10);

	screenChks.push_back(&screenChk11);
	screenChks.push_back(&screenChk12);
	screenChks.push_back(&screenChk13);
	screenChks.push_back(&screenChk14);
	screenChks.push_back(&screenChk15);

	screenChks.push_back(&screenChk16);
	screenChks.push_back(&screenChk17);
	screenChks.push_back(&screenChk18);
	screenChks.push_back(&screenChk19);
	screenChks.push_back(&screenChk20);
}

CScreenDlg::~CScreenDlg()
{
}

void CScreenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SCRNUM, screenNumCom);
	DDX_Control(pDX, IDC_DEVICEID, deviceIdEdit);
	DDX_Control(pDX, IDC_TEAMNUM_PERCOL, groupNumPerColEdit);
	DDX_Control(pDX, IDC_COL_SHOWNUM, colShowNumEdit);
	DDX_Control(pDX, IDC_NUM_PERTEAM, numPerGroupEdit);
	DDX_Control(pDX, IDC_CONST_VMAX, constVmaxEdit);
	DDX_Control(pDX, IDC_CONST_VMIN, constVminEdit);
	DDX_Control(pDX, IDC_CONST_AMAX, constAmaxEdit);
	DDX_Control(pDX, IDC_CONST_AMIN, constAminEdit);
	DDX_Control(pDX, IDC_CONST_VCHG, constVchargeChk);
	DDX_Control(pDX, IDC_OM_TEST, omTestChk);
	DDX_Control(pDX, IDC_SAVETO_FILE, saveToFileChk);
	DDX_Control(pDX, IDC_VDIS, vdisChk);
	DDX_Control(pDX, IDC_VDIS_VAL, vdisValEdit);
	DDX_Control(pDX, IDC_ADIS, adisChk);
	DDX_Control(pDX, IDC_ADIS_VAL, adisValEdit);
	DDX_Control(pDX, IDC_TIMEDIS, timeDisChk);
	DDX_Control(pDX, IDC_TIMEDIS_VAL, timeDisValEdit);
	DDX_Control(pDX, IDC_VSHOW_MAX, vshowMaxEdit);
	DDX_Control(pDX, IDC_VSHOW_MIN, vshowMinEdit);
	DDX_Control(pDX, IDC_SVSHOW_MAX, svshowMaxEdit);
	DDX_Control(pDX, IDC_SVSHOW_MIN, svshowMinEdit);
	DDX_Control(pDX, IDC_SASHOW_MAX, sashowMaxEdit);
	DDX_Control(pDX, IDC_SASHOW_MIN, sashowMinEdit);
	DDX_Control(pDX, IDC_SRSHOW_MAX, srshowMaxEdit);
	DDX_Control(pDX, IDC_SRSHOW_MIN, srshowMinEdit);
	DDX_Control(pDX, IDC_SCREEN1, screenChk1);
	DDX_Control(pDX, IDC_SCREEN2, screenChk2);
	DDX_Control(pDX, IDC_SCREEN3, screenChk3);
	DDX_Control(pDX, IDC_SCREEN4, screenChk4);
	DDX_Control(pDX, IDC_SCREEN5, screenChk5);
	DDX_Control(pDX, IDC_SCREEN6, screenChk6);
	DDX_Control(pDX, IDC_SCREEN7, screenChk7);
	DDX_Control(pDX, IDC_SCREEN8, screenChk8);
	DDX_Control(pDX, IDC_SCREEN9, screenChk9);
	DDX_Control(pDX, IDC_SCREEN10, screenChk10);
	DDX_Control(pDX, IDC_SCREEN11, screenChk11);
	DDX_Control(pDX, IDC_SCREEN12, screenChk12);
	DDX_Control(pDX, IDC_SCREEN13, screenChk13);
	DDX_Control(pDX, IDC_SCREEN14, screenChk14);
	DDX_Control(pDX, IDC_SCREEN15, screenChk15);
	DDX_Control(pDX, IDC_SCREEN16, screenChk16);
	DDX_Control(pDX, IDC_SCREEN17, screenChk17);
	DDX_Control(pDX, IDC_SCREEN18, screenChk18);
	DDX_Control(pDX, IDC_SCREEN19, screenChk19);
	DDX_Control(pDX, IDC_SCREEN20, screenChk20);
	DDX_Control(pDX, IDC_COMBO_DEVICENAME, deviceNameCom);
}


BEGIN_MESSAGE_MAP(CScreenDlg, CDialog)
	ON_BN_CLICKED(IDC_SCRNUMP, &CScreenDlg::OnBnClickedScrnump)
	ON_BN_CLICKED(IDC_SCRNUMP, &CScreenDlg::OnBnClickedScrnump)
	ON_BN_CLICKED(IDC_SCRNUMM, &CScreenDlg::OnBnClickedScrnumm)
	ON_BN_CLICKED(IDC_PARACOPY, &CScreenDlg::OnBnClickedParacopy)
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_COMBO_SCRNUM, &CScreenDlg::OnCbnSelchangeComboScrnum)
END_MESSAGE_MAP()


// CScreenDlg 消息处理程序

BOOL CScreenDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitScreenSet();
	ConnectToDatabase();
	InitDefCabinet();

	this->screenNumCom.SetCurSel(0);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CScreenDlg::ConnectToDatabase()
{
	// (1) 获取DB的绝对路径
	dbConfigPath = CBatteryUtils::GetConfigPath(_T("\\config\\init\\cabinet.ini"));
	wchar_t str[MAX_PATH_LENGTH];
	GetPrivateProfileString(_T("dbpath"), _T("dbpath"), _T("D:\\BatteryManage.mdb"), str, MAX_PATH_LENGTH, dbConfigPath);

	CString dbPath = CBatteryUtils::GetConfigPath(str);
	_bstr_t sqlStr = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" +
		(_bstr_t)dbPath;
	try
	{
		//先创建连接实例
		hr = pConnection.CreateInstance(__uuidof(Connection));//创建Connection对象
		if (SUCCEEDED(hr))
		{
			// 打开本地Access库Demo.mdb
			hr = pConnection->Open(sqlStr, "", "", adModeUnknown);
		}
	}
	catch (_com_error e)///捕捉异常
	{
		CString strMsg;
		strMsg.Format(_T("错误描述：%s\n错误消息%s"),
			(LPCTSTR)e.Description(),
			(LPCTSTR)e.ErrorMessage());
		AfxMessageBox(strMsg);
	}
}

void CScreenDlg::InitDefCabinet()
{
	//pRecordset.CreateInstance(__uuidof(Recordset));
	//// 在ADO操作中建议语句中要常用try...catch()来捕获错误信息，
	//// 因为它有时会经常出现一些想不到的错误。
	//_bstr_t querySql = "select * from CABINET_INFO where CABINET_ID = " + defCabIdStr;
	//try
	//{
	//	pRecordset->Open("select * from CABINET_INFO where CABINET_ID = 1",		 // 查询DemoTable表中所有字段
	//		pConnection.GetInterfacePtr(),			// 获取库连接的IDispatch指针
	//		adOpenDynamic,
	//		adLockOptimistic,
	//		adCmdText);
	//}
	//catch (_com_error * e)
	//{
	//	CString errormessage;
	//	errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
	//	AfxMessageBox(errormessage);
	//}
	//
	//try
	//{
	//	if (!pRecordset->BOF)//如果此时记录集指针指向的不是第一条记录
	//	{
	//		pRecordset->MoveFirst();//指向第一条记录
	//	}

	//	//如果打开没有记录的 Recordset 对象，BOF 和 EOF 属性将设置为 True，而 Recordset 对象的 RecordCount 属性设置为零。
	//	if (pRecordset->BOF && pRecordset->BOF)//这个是判断记录集是否为空!!
	//	{
	//		AfxMessageBox(_T("表内数据为空"));
	//		return;
	//	}
	//	//获取数据库中的数据
	//	int j, i = -1;  //骂得。。如果放在while里面就会每次都会插在第零的位置。。。。
	//	CabinetInfo cabinetInfo;
	//	while (!pRecordset->ADOEOF)
	//	{
	//		cabinetInfo = GetResultSetCabInfo();
	//		break;
	//	}
	//	InitCabinetInfo(cabinetInfo);

	//}
	//catch (_com_error e)
	//{
	//	CString errormessage;
	//	errormessage.Format(_T("错误信息:%s"), e.ErrorMessage());
	//	AfxMessageBox(errormessage);
	//}

	InitCabinetInfoById(defCabId);

}


void CScreenDlg::InitCabinetInfo(CabinetInfo cabinetInfo)
{
	wchar_t str[MAX_PATH_LENGTH];
	adisChk.SetCheck(cabinetInfo.adis);
	
	_itow_s(cabinetInfo.adisVal, str, INT_LENGTH);
	adisValEdit.SetWindowTextW(str);

	_itow_s(cabinetInfo.colShowNum, str, INT_LENGTH);
	colShowNumEdit.SetWindowTextW(str);

	constVchargeChk.SetCheck(cabinetInfo.constVchg);

	_itow_s(cabinetInfo.constAmax, str, INT_LENGTH);
	constAmaxEdit.SetWindowTextW(str);

	_itow_s(cabinetInfo.constAmin, str, INT_LENGTH);
	constAminEdit.SetWindowTextW(str);

	_itow_s(cabinetInfo.constVmax, str, INT_LENGTH);
	constVmaxEdit.SetWindowTextW(str);

	_itow_s(cabinetInfo.constVmin, str, INT_LENGTH);
	constVminEdit.SetWindowTextW(str);

	deviceIdEdit.SetWindowTextW(cabinetInfo.deviceId);
	
	int ifind = deviceNameCom.FindString(-1, cabinetInfo.deviceName);
	deviceNameCom.SetCurSel(ifind);

	_itow_s(cabinetInfo.groupNumPerCol, str, INT_LENGTH);
	groupNumPerColEdit.SetWindowTextW(str);

	_itow_s(cabinetInfo.colShowNum, str, INT_LENGTH);
	colShowNumEdit.SetWindowTextW(str);

	_itow_s(cabinetInfo.numPerGroup, str, INT_LENGTH);
	numPerGroupEdit.SetWindowTextW(str);

	omTestChk.SetCheck(cabinetInfo.omTest);

	_itow_s(cabinetInfo.sashowMax, str, INT_LENGTH);
	sashowMaxEdit.SetWindowTextW(str);

	_itow_s(cabinetInfo.sashowMin, str, INT_LENGTH);
	sashowMinEdit.SetWindowTextW(str);

	saveToFileChk.SetCheck(cabinetInfo.saveToFile);

	_itow_s(cabinetInfo.srshowMax, str, INT_LENGTH);
	srshowMaxEdit.SetWindowTextW(str);

	_itow_s(cabinetInfo.srshowMin, str, INT_LENGTH);
	srshowMinEdit.SetWindowTextW(str);

	_itow_s(cabinetInfo.svshowMax, str, INT_LENGTH);
	svshowMaxEdit.SetWindowTextW(str);

	_itow_s(cabinetInfo.svshowMin, str, INT_LENGTH);
	svshowMinEdit.SetWindowTextW(str);

	timeDisChk.SetCheck(cabinetInfo.timeDis);

	_itow_s(cabinetInfo.timeDisVal, str, INT_LENGTH);
	timeDisValEdit.SetWindowTextW(str);

	vdisChk.SetCheck(cabinetInfo.vdis);

	_itow_s(cabinetInfo.vdisVal, str, INT_LENGTH);
	vdisValEdit.SetWindowTextW(str);

	_itow_s(cabinetInfo.vshowMax, str, INT_LENGTH);
	vshowMaxEdit.SetWindowTextW(str);

	_itow_s(cabinetInfo.vshowMin, str, INT_LENGTH);
	vshowMinEdit.SetWindowTextW(str);
}

void CScreenDlg::InitScreenSet()
{
	for (int idx = 0; idx < cabSelStr.GetLength(); ++idx)
		screenChks[idx]->SetCheck(cabSelStr.GetAt(idx) == '1' ? 1 : 0);

	wchar_t deviceStr[MAX_STR_LENGTH + 1];
	CString deviceCstr;
	CStringArray deviceNames;
	GetPrivateProfileString(_T("device"), _T("deviceNames"), _T("无"), deviceStr, MAX_STR_LENGTH + 1, cabPath);
	deviceCstr = deviceStr;
	
	CBatteryUtils::GetSplitedStr(deviceCstr, deviceNames, ';');

	deviceNameCom.Clear();
	for (int idx = 0; idx < deviceNames.GetCount(); ++idx)
	{
		deviceNameCom.AddString(deviceNames[idx]);
	}

}

void CScreenDlg::SaveScreenSet()
{	
	if (MessageBox(_T("确定要保存屏号设置么"), _T("提示"), MB_OKCANCEL | MB_ICONWARNING) == IDOK)
	{
		wchar_t str[MAX_CAB_NUM + 1];
		int cabId = -1;
		
		for (int idx = 0; idx < MAX_CAB_NUM; ++idx)
		{
			str[idx] = screenChks[idx]->GetCheck() == 1 ? '1' : '0';
			if (str[idx] == '1')
			{
				cabId = cabId == -1 ? idx + 1 : cabId;
			}
		}
		str[MAX_CAB_NUM] = '\0';
		// 保存时记得更新defCabId;defCabIdStr;cabSelStr
		defCabId = cabId;
		defCabIdStr = cabIds[cabId - 1];
		cabSelStr = str;

		BOOL res = WritePrivateProfileString(_T("cabs"), _T("cabSels"), str, cabPath);
		
		CabinetInfo cabinetInfo = GetDlgCabInfo();
		screenNumCom.GetWindowTextW(str, INT_LENGTH);
		cabId = _ttoi(str);
		SaveCabInfoToDb(cabId, cabinetInfo);

		MessageBox(_T("保存柜号设置成功!"));
	}
}

BOOL CScreenDlg::SaveCabInfoToDb(int cabId, CabinetInfo cabinetInfo)
{
	wchar_t str[INT_LENGTH+1];
	pRecordset.CreateInstance(__uuidof(Recordset));
	// 在ADO操作中建议语句中要常用try...catch()来捕获错误信息，
	// 因为它有时会经常出现一些想不到的错误。
	_itow_s(cabId, str, INT_LENGTH);
	_bstr_t cabIdStr = str;
	_bstr_t querySql = "select * from CABINET_INFO where CABINET_ID = " + cabIdStr;
	
	try
	{
		pRecordset->Open(querySql,		 // 查询DemoTable表中所有字段
			pConnection.GetInterfacePtr(),			// 获取库连接的IDispatch指针
			adOpenStatic,
			adLockOptimistic,
			adCmdText);
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
	}
	int count = 0;
	try
	{
		count = pRecordset->GetRecordCount();
	}
	catch (_com_error e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s"), e.ErrorMessage());
		AfxMessageBox(errormessage);
	}

	if (count == 0)
	{
		try
		{
			pRecordset->AddNew();
			pRecordset->PutCollect("CABINET_ID", _variant_t(cabId));
			pRecordset->PutCollect("DEVICE_NAME", _variant_t(cabinetInfo.deviceName));
			pRecordset->PutCollect("DEVICE_ID", _variant_t(cabinetInfo.deviceId));
			pRecordset->PutCollect("GROUPNUM_PERCOL", _variant_t(cabinetInfo.groupNumPerCol));
			pRecordset->PutCollect("COL_SHOWNUM", _variant_t(cabinetInfo.colShowNum));
			pRecordset->PutCollect("NUM_PERGROUP", _variant_t(cabinetInfo.numPerGroup));
			pRecordset->PutCollect("CONST_VMAX", _variant_t(cabinetInfo.constVmax));
			pRecordset->PutCollect("CONST_VMIN", _variant_t(cabinetInfo.constVmin));
			pRecordset->PutCollect("CONST_AMAX", _variant_t(cabinetInfo.constAmax));
			pRecordset->PutCollect("CONST_AMIN", _variant_t(cabinetInfo.constAmin));
			pRecordset->PutCollect("CONST_VCHG", _variant_t(cabinetInfo.constVchg));
			pRecordset->PutCollect("OM_TEST", _variant_t(cabinetInfo.omTest));
			pRecordset->PutCollect("SAVETO_FILE", _variant_t(cabinetInfo.saveToFile));
			pRecordset->PutCollect("VDIS", _variant_t(cabinetInfo.vdis));
			pRecordset->PutCollect("VDIS_VAL", _variant_t(cabinetInfo.vdisVal));
			pRecordset->PutCollect("ADIS", _variant_t(cabinetInfo.adis));
			pRecordset->PutCollect("ADIS_VAL", _variant_t(cabinetInfo.adisVal));
			pRecordset->PutCollect("TIMEDIS", _variant_t(cabinetInfo.timeDis));
			pRecordset->PutCollect("TIMEDIS_VAL", _variant_t(cabinetInfo.timeDisVal));
			pRecordset->PutCollect("VSHOW_MAX", _variant_t(cabinetInfo.vshowMax));
			pRecordset->PutCollect("VSHOW_MIN", _variant_t(cabinetInfo.vshowMin));
			pRecordset->PutCollect("SVSHOW_MAX", _variant_t(cabinetInfo.svshowMax));
			pRecordset->PutCollect("SVSHOW_MIN", _variant_t(cabinetInfo.svshowMin));
			pRecordset->PutCollect("SASHOW_MAX", _variant_t(cabinetInfo.sashowMax));
			pRecordset->PutCollect("SASHOW_MIN", _variant_t(cabinetInfo.sashowMin));
			pRecordset->PutCollect("SRSHOW_MAX", _variant_t(cabinetInfo.srshowMax));
			pRecordset->PutCollect("SRSHOW_MIN", _variant_t(cabinetInfo.srshowMin));

			pRecordset->Update();

			// 保存全局变量cabinetInfos
			SaveGlbCabInfos(cabId, cabinetInfo);

		}
		catch (_com_error * e)
		{
			CString errormessage;
			errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
			AfxMessageBox(errormessage);
		}
	}
	else
	{
		try
		{
			pRecordset->MoveFirst();
			pRecordset->PutCollect("DEVICE_NAME", _variant_t(cabinetInfo.deviceName));
			pRecordset->PutCollect("DEVICE_ID", _variant_t(cabinetInfo.deviceId));
			pRecordset->PutCollect("GROUPNUM_PERCOL", _variant_t(cabinetInfo.groupNumPerCol));
			pRecordset->PutCollect("COL_SHOWNUM", _variant_t(cabinetInfo.colShowNum));
			pRecordset->PutCollect("NUM_PERGROUP", _variant_t(cabinetInfo.numPerGroup));
			pRecordset->PutCollect("CONST_VMAX", _variant_t(cabinetInfo.constVmax));
			pRecordset->PutCollect("CONST_VMIN", _variant_t(cabinetInfo.constVmin));
			pRecordset->PutCollect("CONST_AMAX", _variant_t(cabinetInfo.constAmax));
			pRecordset->PutCollect("CONST_AMIN", _variant_t(cabinetInfo.constAmin));
			pRecordset->PutCollect("CONST_VCHG", _variant_t(cabinetInfo.constVchg));
			pRecordset->PutCollect("OM_TEST", _variant_t(cabinetInfo.omTest));
			pRecordset->PutCollect("SAVETO_FILE", _variant_t(cabinetInfo.saveToFile));
			pRecordset->PutCollect("VDIS", _variant_t(cabinetInfo.vdis));
			pRecordset->PutCollect("VDIS_VAL", _variant_t(cabinetInfo.vdisVal));
			pRecordset->PutCollect("ADIS", _variant_t(cabinetInfo.adis));
			pRecordset->PutCollect("ADIS_VAL", _variant_t(cabinetInfo.adisVal));
			pRecordset->PutCollect("TIMEDIS", _variant_t(cabinetInfo.timeDis));
			pRecordset->PutCollect("TIMEDIS_VAL", _variant_t(cabinetInfo.timeDisVal));
			pRecordset->PutCollect("VSHOW_MAX", _variant_t(cabinetInfo.vshowMax));
			pRecordset->PutCollect("VSHOW_MIN", _variant_t(cabinetInfo.vshowMin));
			pRecordset->PutCollect("SVSHOW_MAX", _variant_t(cabinetInfo.svshowMax));
			pRecordset->PutCollect("SVSHOW_MIN", _variant_t(cabinetInfo.svshowMin));
			pRecordset->PutCollect("SASHOW_MAX", _variant_t(cabinetInfo.sashowMax));
			pRecordset->PutCollect("SASHOW_MIN", _variant_t(cabinetInfo.sashowMin));
			pRecordset->PutCollect("SRSHOW_MAX", _variant_t(cabinetInfo.srshowMax));
			pRecordset->PutCollect("SRSHOW_MIN", _variant_t(cabinetInfo.srshowMin));
			pRecordset->Update();

			// 保存全局变量cabinetInfos
			SaveGlbCabInfos(cabId, cabinetInfo);
		}
		catch (_com_error * e)
		{
			CString errormessage;
			errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
			AfxMessageBox(errormessage);
		}
	}
	return TRUE;
}

void CScreenDlg::SaveGlbCabInfos(int cabId, CabinetInfo cabinetInfo)
{
	if (cabId > 0)
	{
		cabinetInfo.cabinetId = cabId;
		cabInfos[cabId - 1] = cabinetInfo;
	}
}
// 按钮增加时进行更新
void CScreenDlg::OnBnClickedScrnump()
{
	int sel = screenNumCom.GetCurSel();

	if (sel + 1 >= MIN_CAB_NUM && sel + 1 < MAX_CAB_NUM)
		screenNumCom.SetCurSel(sel + 1);
	
	CString curCabIdStr;
	int curCabId;
	screenNumCom.GetLBText(screenNumCom.GetCurSel(), curCabIdStr);
	curCabId = _ttoi(curCabIdStr);

	InitCabinetInfoById(curCabId);

}

void CScreenDlg::InitCabinetInfoById(int curCabId)
{
	pRecordset.CreateInstance(__uuidof(Recordset));
	CString querySql;
	querySql.Format(_T("select * from CABINET_INFO where CABINET_ID = %d"), curCabId);

	try
	{
		pRecordset->Open(variant_t(querySql),// 查询DemoTable表中所有字段
			pConnection.GetInterfacePtr(),			// 获取库连接的IDispatch指针
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
	}

	try
	{
		if (!pRecordset->ADOBOF)//如果此时记录集指针指向的不是第一条记录
		{
			pRecordset->MoveFirst();//指向第一条记录
		}

		//如果打开没有记录的 Recordset 对象，BOF 和 EOF 属性将设置为 True，而 Recordset 对象的 RecordCount 属性设置为零。
		if (pRecordset->ADOBOF && pRecordset->ADOBOF)//这个是判断记录集是否为空!!
		{
			//AfxMessageBox(_T("表内数据为空"));
			return;
		}
		//获取数据库中的数据
		int j, i = -1;  //骂得。。如果放在while里面就会每次都会插在第零的位置。。。。
		CabinetInfo cabinetInfo;
		while (!pRecordset->ADOEOF)
		{
			cabinetInfo = GetResultSetCabInfo();
			break;
		}
		InitCabinetInfo(cabinetInfo);

	}
	catch (_com_error e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s"), e.ErrorMessage());
		AfxMessageBox(errormessage);
	}
}

CabinetInfo CScreenDlg::GetDlgCabInfo()
{
	CabinetInfo cabinetInfo;

	wchar_t str[MAX_PATH_LENGTH];
	cabinetInfo.adis = adisChk.GetCheck();

	adisValEdit.GetWindowTextW(str, INT_LENGTH);
	cabinetInfo.adisVal = _ttoi(str);

	colShowNumEdit.GetWindowTextW(str, INT_LENGTH);
	cabinetInfo.colShowNum = _ttoi(str);

	cabinetInfo.constVchg = constVchargeChk.GetCheck();

	constAmaxEdit.GetWindowTextW(str, INT_LENGTH);
	cabinetInfo.constAmax = _ttoi(str);

	constAminEdit.GetWindowTextW(str, INT_LENGTH);
	cabinetInfo.constAmin = _ttoi(str);
	
	constVmaxEdit.GetWindowTextW(str, INT_LENGTH);
	cabinetInfo.constVmax = _ttoi(str);

	constVminEdit.GetWindowTextW(str, INT_LENGTH);
	cabinetInfo.constVmin = _ttoi(str);

	deviceIdEdit.GetWindowTextW(str, MAX_PATH_LENGTH - 1);
	cabinetInfo.deviceId = str;

	deviceNameCom.GetWindowTextW(cabinetInfo.deviceName);


	groupNumPerColEdit.GetWindowTextW(str, INT_LENGTH);
	cabinetInfo.groupNumPerCol = _ttoi(str);

	colShowNumEdit.GetWindowTextW(str, INT_LENGTH);
	cabinetInfo.colShowNum = _ttoi(str);

	numPerGroupEdit.GetWindowTextW(str, INT_LENGTH);
	cabinetInfo.numPerGroup = _ttoi(str);

	cabinetInfo.omTest = omTestChk.GetCheck();

	sashowMaxEdit.GetWindowTextW(str, INT_LENGTH);
	cabinetInfo.sashowMax = _ttoi(str);

	sashowMinEdit.GetWindowTextW(str, INT_LENGTH);
	cabinetInfo.sashowMin = _ttoi(str);

	cabinetInfo.saveToFile = saveToFileChk.GetCheck();

	srshowMaxEdit.GetWindowTextW(str, INT_LENGTH);
	cabinetInfo.srshowMax = _ttoi(str);

	srshowMinEdit.GetWindowTextW(str, INT_LENGTH);
	cabinetInfo.srshowMin = _ttoi(str);

	svshowMaxEdit.GetWindowTextW(str, INT_LENGTH);
	cabinetInfo.svshowMax = _ttoi(str);

	svshowMinEdit.GetWindowTextW(str, INT_LENGTH);
	cabinetInfo.svshowMin = _ttoi(str);

	cabinetInfo.timeDis = timeDisChk.GetCheck();

	timeDisValEdit.GetWindowTextW(str, INT_LENGTH);
	cabinetInfo.timeDisVal = _ttoi(str);

	cabinetInfo.vdis = vdisChk.GetCheck();

	vdisValEdit.GetWindowTextW(str, INT_LENGTH);
	cabinetInfo.vdisVal = _ttoi(str);

	vshowMaxEdit.GetWindowTextW(str, INT_LENGTH);
	cabinetInfo.vshowMax = _ttoi(str);

	vshowMinEdit.GetWindowTextW(str, INT_LENGTH);
	cabinetInfo.vshowMin = _ttoi(str);

	return cabinetInfo;
}

CabinetInfo CScreenDlg::GetResultSetCabInfo()
{
	_variant_t var;
	CabinetInfo cabinetInfo;

	var = pRecordset->GetCollect(_T("ADIS"));
	if (var.vt != VT_NULL)
		cabinetInfo.adis = int(var);

	var = pRecordset->GetCollect(_T("ADIS_VAL"));
	cabinetInfo.adisVal = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("CABINET_ID"));
	cabinetInfo.cabinetId = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("COL_SHOWNUM"));
	cabinetInfo.colShowNum = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("CONST_VCHG"));
	cabinetInfo.constVchg = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("CONST_AMAX"));
	cabinetInfo.constAmax = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("CONST_AMIN"));
	cabinetInfo.constAmin = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("CONST_VMAX"));
	cabinetInfo.constVmax = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("CONST_VMIN"));
	cabinetInfo.constVmin = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("DEVICE_ID"));
	cabinetInfo.deviceId = var.vt != NULL ? (LPCTSTR)_bstr_t(var) : _T("");

	var = pRecordset->GetCollect(_T("DEVICE_NAME"));
	cabinetInfo.deviceName = var.vt != NULL ? (LPCTSTR)_bstr_t(var) : _T("");

	var = pRecordset->GetCollect(_T("GROUPNUM_PERCOL"));
	cabinetInfo.groupNumPerCol = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("NUM_PERGROUP"));
	cabinetInfo.numPerGroup = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("COL_SHOWNUM"));
	cabinetInfo.colShowNum = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("OM_TEST"));
	cabinetInfo.omTest = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("SASHOW_MAX"));
	cabinetInfo.sashowMax = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("SASHOW_MIN"));
	cabinetInfo.sashowMin = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("SAVETO_FILE"));
	cabinetInfo.saveToFile = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("SRSHOW_MAX"));
	cabinetInfo.srshowMax = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("SRSHOW_MIN"));
	cabinetInfo.srshowMin = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("SVSHOW_MAX"));
	cabinetInfo.svshowMax = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("SVSHOW_MIN"));
	cabinetInfo.svshowMin = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("TIMEDIS"));
	cabinetInfo.timeDis = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("TIMEDIS_VAL"));
	cabinetInfo.timeDisVal = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("VDIS"));
	cabinetInfo.vdis = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("VDIS_VAL"));
	cabinetInfo.vdisVal = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("VSHOW_MAX"));
	cabinetInfo.vshowMax = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("VSHOW_MIN"));
	cabinetInfo.vshowMin = var.vt != NULL ? int(var) : 0;

	return cabinetInfo;
}
void CScreenDlg::OnBnClickedScrnumm()
{
	//CString selStr;
	int sel = screenNumCom.GetCurSel();
	//selStr.Format(_T("%d"), sel);

	if (sel + 1 > MIN_CAB_NUM && sel + 1 <= MAX_CAB_NUM)
		screenNumCom.SetCurSel(sel - 1);
	
	CString curCabIdStr;
	int curCabId;
	screenNumCom.GetLBText(screenNumCom.GetCurSel(), curCabIdStr);
	curCabId = _ttoi(curCabIdStr);

	InitCabinetInfoById(curCabId);
}


void CScreenDlg::OnBnClickedParacopy()
{
	if (this->copyDlg == NULL)
	{
		this->copyDlg = new CInitCopyDlg();
	}

	this->copyDlg->DoModal();
}


void CScreenDlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (pConnection->State)
		pConnection->Close();// 关闭ADO连接状态
	pConnection = NULL;

	CDialog::OnClose();
}


void CScreenDlg::OnCbnSelchangeComboScrnum()
{
	CString curCabIdStr;
	int curCabId;
	screenNumCom.GetLBText(screenNumCom.GetCurSel(), curCabIdStr);
	curCabId = _ttoi(curCabIdStr);

	InitCabinetInfoById(curCabId);
}

//void CScreenDlg::InitCabinetInfoByCabId(int cabId)
//{
//	pRecordset.CreateInstance(__uuidof(Recordset));
//	CString querySql;
//	querySql.Format(_T("select * from CABINET_INFO where CABINET_ID = %d"), cabId);
//
//	try
//	{
//		pRecordset->Open(variant_t(querySql),// 查询DemoTable表中所有字段
//			pConnection.GetInterfacePtr(),			// 获取库连接的IDispatch指针
//			adOpenDynamic,
//			adLockOptimistic,
//			adCmdText);
//	}
//	catch (_com_error * e)
//	{
//		CString errormessage;
//		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
//		AfxMessageBox(errormessage);
//	}
//
//	try
//	{
//		if (!pRecordset->BOF)//如果此时记录集指针指向的不是第一条记录
//		{
//			pRecordset->MoveFirst();//指向第一条记录
//		}
//
//		//如果打开没有记录的 Recordset 对象，BOF 和 EOF 属性将设置为 True，而 Recordset 对象的 RecordCount 属性设置为零。
//		if (pRecordset->BOF && pRecordset->BOF)//这个是判断记录集是否为空!!
//		{
//			//AfxMessageBox(_T("表内数据为空"));
//			return;
//		}
//		//获取数据库中的数据
//		int j, i = -1;  //骂得。。如果放在while里面就会每次都会插在第零的位置。。。。
//		CabinetInfo cabinetInfo;
//		while (!pRecordset->ADOEOF)
//		{
//			cabinetInfo = GetResultSetCabInfo();
//			break;
//		}
//		InitCabinetInfo(cabinetInfo);
//
//	}
//	catch (_com_error e)
//	{
//		CString errormessage;
//		errormessage.Format(_T("错误信息:%s"), e.ErrorMessage());
//		AfxMessageBox(errormessage);
//	}
//}