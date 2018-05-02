
// BatteryManage.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "BatteryManage.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include <afxstr.h>

#include <fstream>
#include <iostream>
#include <string>


using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 全局ColorInfo
CBatteryColor initColor;
CBatteryColor defColor;


CString colorPath;

// 全局CabinetInfo
int defCabId;
// 当前机柜编号
int curCabId;
// 维护cabinets控制信息的全局变量
vector<CabinetInfo> cabInfos;
CString paneId;
_bstr_t defCabIdStr;
CString cabPath;
CString cabSelStr;
CabinetInfo defCabInfo;
CString dbConfigPath;

// 打开文件下拉菜单全局变量
CString openFilePath;


// 电池编号的组成 当前行号,当前行内组号,当前组内编号
int curRowId;
int curGroupId;
int curGroupInnerId;
int curBatteryId;


// 全局控制双击边框大小的变量
BOOL maxminFlag = FALSE;

HICON selIcon;

// CBatteryManageApp
BEGIN_MESSAGE_MAP(CBatteryManageApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CBatteryManageApp::OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, &CBatteryManageApp::OnFileNew)



	ON_COMMAND(ID_INIT_DIALOG, &CBatteryManageApp::OnInitDialog)
	ON_COMMAND(ID_SET_NUM, &CBatteryManageApp::OnSetNum)
	ON_COMMAND(ID_OP_MANAGE, &CBatteryManageApp::OnOpManage)
	ON_COMMAND(ID_OP_LOG, &CBatteryManageApp::OnOpLog)
	ON_COMMAND(ID_OP_LOGIN, &CBatteryManageApp::OnOpLogin)
	ON_COMMAND(ID_LOCK, &CBatteryManageApp::OnLock)
	ON_COMMAND(ID_EXC_SYSTEM, &CBatteryManageApp::OnExcSystem)
	ON_COMMAND(ID_SHOW_CURVE, &CBatteryManageApp::OnShowCurve)

	ON_COMMAND(ID_START_WORK, &CBatteryManageApp::OnStartWork)
	ON_COMMAND(ID_BATTERY_CHECK, &CBatteryManageApp::OnBatteryCheck)
	ON_COMMAND(ID_BATTERY_CONN, &CBatteryManageApp::OnBatteryConn)
	ON_COMMAND(ID_BATTERY_DIS_CONN, &CBatteryManageApp::OnBatteryDisConn)
	ON_COMMAND(ID_CONN_DIS_SET, &CBatteryManageApp::OnConnDisSet)
	ON_COMMAND(ID_READ_DATA, &CBatteryManageApp::OnReadData)
	ON_COMMAND(ID_SCREEN_RESET, &CBatteryManageApp::OnScreenReset)
	ON_COMMAND(ID_EXCEP_REMOVE, &CBatteryManageApp::OnExcepRemove)
	ON_COMMAND(ID_DEBUG_WINDOW, &CBatteryManageApp::OnDebugWindow)
	ON_COMMAND(ID_RECUR_POWER_CUT, &CBatteryManageApp::OnRecurPowerCut)
	ON_COMMAND(ID_EXCEP_STEP_RECORD, &CBatteryManageApp::OnExcepStepRecord)
	ON_COMMAND(ID_DATAFILE_OPEN, &CBatteryManageApp::OnDatafileOpen)
	ON_COMMAND(ID_EXPORT_TO_MDB, &CBatteryManageApp::OnExportToMdb)
	ON_COMMAND(ID_BATTERY_SEARCH_CREATER, &CBatteryManageApp::OnBatterySearchCreater)
	ON_COMMAND(ID_OPEN_SEARCH_ENGINE, &CBatteryManageApp::OnOpenSearchEngine)
	ON_COMMAND(ID_CAP_COMPARE, &CBatteryManageApp::OnCapCompare)
	ON_COMMAND(ID_CAP_EXPORT_SET, &CBatteryManageApp::OnCapExportSet)
	ON_COMMAND(ID_CHK_BATTERY_ID, &CBatteryManageApp::OnChkBatteryId)
	ON_COMMAND(ID_BATTERY_GRADING, &CBatteryManageApp::OnBatteryGrading)
	ON_COMMAND(ID_SW_RC_ADDONEROW, &CBatteryManageApp::OnSwRcAddonerow)
	ON_COMMAND(ID_SW_RC_ADDMULROW, &CBatteryManageApp::OnSwRcAddmulrow)
	//	ON_COMMAND(ID_SW_RC_DELONEROW, &CBatteryManageApp::OnSwRcDelonerow)
	//	ON_COMMAND(ID_SW_RC_DELMULROW, &CBatteryManageApp::OnSwRcDelmulrow)
	ON_COMMAND(ID_SW_RC_COPY, &CBatteryManageApp::OnSwRcCopy)
	ON_COMMAND(ID_SW_RC_CUT, &CBatteryManageApp::OnSwRcCut)
	ON_COMMAND(ID_SW_RC_PASTE, &CBatteryManageApp::OnSwRcPaste)
	ON_COMMAND(ID_SW_RC_DELROW, &CBatteryManageApp::OnSwRcDelrow)
	ON_COMMAND(WM_SYSCOMMAND, &CBatteryManageApp::OnWmSyscommand)
	ON_COMMAND(WM_COMMAND, &CBatteryManageApp::OnWmCommand)

	//ON_COMMAND(ID_PART_SHOW_BATID, &CBatteryManageApp::OnPartShowBatid)
	//ON_COMMAND(ID_PART_CAP_COND, &CBatteryManageApp::OnPartCapCond)
	//ON_COMMAND(ID_AUTO_PART_CAP, &CBatteryManageApp::OnAutoPartCap)
	ON_COMMAND(ID_OPERTOR_MANAGE, &CBatteryManageApp::OnOpertorManage)
	
END_MESSAGE_MAP()


// CBatteryManageApp 构造

CBatteryManageApp::CBatteryManageApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则: 
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO:  将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("BatteryManage.AppID.NoVersion"));

	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CBatteryManageApp 对象

CBatteryManageApp theApp;


// CBatteryManageApp 初始化

BOOL CBatteryManageApp::InitInstance()
{

	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	

	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		//AfxMessageBox(IDP_OLE_INIT_FAILED);
		AfxMessageBox(_T("OLE初始化失败!"));
		return FALSE;
	}

	//m_pConnection.CreateInstance(__uuidof(Connection));

	//try
	//{
	//	// 打开本地Access库Demo.mdb
	//	m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=Demo.mdb", "", "", adModeUnknown);
	//	//注意这里一个字都不可以错。。。否则。程序会发生错误
	//}
	//catch (_com_error * e)
	//{
	//	CString errormessage;
	//	errormessage.Format(_T("错误信息：%s"), e->ErrorMessage());
	//	AfxMessageBox(errormessage);
	//	AfxMessageBox(_T("数据库连接失败，确认数据库Demo.mdb是否在当前路径下!"));

	//	return FALSE;
	//}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO:  应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));


	// 若要创建主窗口，此代码将创建新的框架窗口
	// 对象，然后将其设置为应用程序的主窗口对象
	CMDIFrameWnd* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// 创建主 MDI 框架窗口
	if (!pFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	// 试图加载共享 MDI 菜单和快捷键表
	//TODO:  添加附加成员变量，并加载对
	//	应用程序可能需要的附加菜单类型的调用
	HINSTANCE hInst = AfxGetResourceHandle();
	m_hMDIMenu  = ::LoadMenu(hInst, MAKEINTRESOURCE(IDR_BatteryManageTYPE));
	m_hMDIAccel = ::LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_BatteryManageTYPE));
	
	//selIcon = (HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_SEL_ICON), IMAGE_ICON, 12, 12, LR_DEFAULTCOLOR);
	selIcon = (HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_SEL_ICON), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	//selIcon = (HICON)LoadIcon(IDI_SEL_ICON);
	CString selBmpPath = CBatteryUtils::GetConfigPath(L"config\\images\\sel.bmp");
	selBmp = LoadBitmap(AfxGetApp()->m_hInstance, selBmpPath);
	// 主要设置
	initDlg  = NULL;
	opLoginDlg = NULL;
	setNumDlg = NULL;
	opManageDlg = NULL;
	adminLoginDlg = NULL;
	opLogDlg = NULL;

	

	// 控制测试
	batteryMainWnd = NULL;
	startWorkDlg = NULL;
	excepRemoveDlg = NULL;
	debugLoginDlg = NULL;
	screenSelDlg = NULL;
	capacityGradingDlg = NULL;

	//数据工具菜单
	searchEngineCreater = NULL;
	searchEngine = NULL;
	capCompareDlg = NULL;
	capExportDlg = NULL;
	chkBatteryDlg = NULL;

	
	// 初始化设置
	InitColorSet();
	GetDefCabId();
	GetCabInfos();
	commConf = CommConf::GetInstance();

	// 主窗口已初始化，因此显示它并对其进行更新
	//batteryCheckWnd = NULL;
	//pFrame->ShowWindow(m_nCmdShow);
	//pFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pFrame->UpdateWindow();

	// 显示电池工作主界面
	if (batteryMainWnd == NULL)
	{
		CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);
		// 创建新的 MDI 子窗口
		batteryMainWnd = pFrame->CreateNewChild(
			RUNTIME_CLASS(CBatteryMainFrame), IDR_BatteryManageTYPE, m_hMDIMenu, m_hMDIAccel);
	}

	return TRUE;
}

int CBatteryManageApp::ExitInstance()
{
	//TODO:  处理可能已添加的附加资源

	// 初始设置
	if (initDlg != NULL){
		initDlg->DestroyWindow();
		delete initDlg;
		initDlg = NULL;
	}
	if (opLoginDlg != NULL){
		opLoginDlg->DestroyWindow();
		delete opLoginDlg;
		opLoginDlg = NULL;
	}
	if (setNumDlg != NULL) {
		setNumDlg->DestroyWindow();
		delete setNumDlg;
		setNumDlg = NULL;
	}
	if (opManageDlg != NULL) {
		opManageDlg->DestroyWindow();
		delete opManageDlg;
		opManageDlg = NULL;
	}
	if (adminLoginDlg != NULL) {
		adminLoginDlg->DestroyWindow();
		delete adminLoginDlg;
		adminLoginDlg = NULL;
	}
	if (opLogDlg != NULL) {
		opLogDlg->DestroyWindow();
		delete opLogDlg;
		opLogDlg = NULL;
	}
	// 控制测试
	if (startWorkDlg != NULL) {
		startWorkDlg->DestroyWindow();
		delete startWorkDlg;
		startWorkDlg = NULL;
	}
	if (excepRemoveDlg != NULL) {
		excepRemoveDlg->DestroyWindow();
		delete excepRemoveDlg;
		excepRemoveDlg = NULL;
	}
	if (debugLoginDlg != NULL) {
		debugLoginDlg->DestroyWindow();
		delete debugLoginDlg;
		debugLoginDlg = NULL;
	}
	if (screenSelDlg != NULL) {
		screenSelDlg->DestroyWindow();
		delete screenSelDlg;
		screenSelDlg = NULL;
	}
	if (capacityGradingDlg != NULL) {
		capacityGradingDlg->DestroyWindow();
		delete capacityGradingDlg;
		capacityGradingDlg = NULL;
	}
	//数据工具
	if (searchEngineCreater != NULL) {
		searchEngineCreater->DestroyWindow();
		delete searchEngineCreater;
		searchEngineCreater = NULL;
	}
	if (searchEngine != NULL) {
		searchEngine->DestroyWindow();
		delete searchEngine;
		searchEngine = NULL;
	}
	if (capCompareDlg != NULL) {
		capCompareDlg->DestroyWindow();
		delete capCompareDlg;
		capCompareDlg = NULL;
	}
	if (capExportDlg != NULL) {
		capExportDlg->DestroyWindow();
		delete capExportDlg;
		capExportDlg = NULL;
	}
	if (chkBatteryDlg != NULL) {
		chkBatteryDlg->DestroyWindow();
		delete chkBatteryDlg;
		chkBatteryDlg = NULL;
	}


	if (m_hMDIMenu != NULL)
		FreeResource(m_hMDIMenu);
	if (m_hMDIAccel != NULL)
		FreeResource(m_hMDIAccel);

	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}


void CBatteryManageApp::InitColorSet()
{
	colorPath = CBatteryUtils::GetConfigPath(_T("\\config\\init\\color.ini"));

	int intIniChargeCol = GetPrivateProfileInt(_T("iniColor"), _T("iniCharge"), 0, colorPath);
	int intIniRecycleCol = GetPrivateProfileInt(_T("iniColor"), _T("iniRecycle"), 0, colorPath);
	int intIniStorCol = GetPrivateProfileInt(_T("iniColor"), _T("iniStor"), 0, colorPath);
	int intIniUnstorCol = GetPrivateProfileInt(_T("iniColor"), _T("iniUnstor"), 0, colorPath);
	int intIniStopCol = GetPrivateProfileInt(_T("iniColor"), _T("iniStop"), 0, colorPath);
	int intIniDischargeCol = GetPrivateProfileInt(_T("iniColor"), _T("iniDischarge"), 0, colorPath);
	int intIniLayCol = GetPrivateProfileInt(_T("iniColor"), _T("iniLay"), 0, colorPath);
	int intIniVaChargeCol = GetPrivateProfileInt(_T("iniColor"), _T("iniVaCharge"), 0, colorPath);

	int intIniVerrorCol = GetPrivateProfileInt(_T("iniColor"), _T("iniVerror"), 0, colorPath);
	int intIniAerrorCol = GetPrivateProfileInt(_T("iniColor"), _T("iniAerror"), 0, colorPath);
	int intIniOverAlarmCol = GetPrivateProfileInt(_T("iniColor"), _T("iniOverAlarm"), 0, colorPath);
	int intIniLeakAlarmCol = GetPrivateProfileInt(_T("iniColor"), _T("iniLeakAlarm"), 0, colorPath);
	int intIniBadContCol = GetPrivateProfileInt(_T("iniColor"), _T("iniBadCont"), 0, colorPath);
	int intIniVoverCol = GetPrivateProfileInt(_T("iniColor"), _T("iniVover"), 0, colorPath);
	int intIniBatteryWinCol = GetPrivateProfileInt(_T("iniColor"), _T("iniBatteryWin"), 0, colorPath);

	initColor.chargeCol = RGB(intIniChargeCol / 1000000, (intIniChargeCol / 1000) % 1000, intIniChargeCol % 1000);
	initColor.recycleCol = RGB(intIniRecycleCol / 1000000, (intIniRecycleCol / 1000) % 1000, intIniRecycleCol % 1000);
	initColor.storCol = RGB(intIniStorCol / 1000000, (intIniStorCol / 1000) % 1000, intIniStorCol % 1000);
	initColor.unstorCol = RGB(intIniUnstorCol / 1000000, (intIniUnstorCol / 1000) % 1000, intIniUnstorCol % 1000);
	initColor.stopCol = RGB(intIniStopCol / 1000000, (intIniStopCol / 1000) % 1000, intIniStopCol % 1000);
	initColor.dischargeCol = RGB(intIniDischargeCol / 1000000, (intIniDischargeCol / 1000) % 1000, intIniDischargeCol % 1000);
	initColor.layCol = RGB(intIniLayCol / 1000000, (intIniLayCol / 1000) % 1000, intIniLayCol % 1000);
	initColor.vaChargeCol = RGB(intIniVaChargeCol / 1000000, (intIniVaChargeCol / 1000) % 1000, intIniVaChargeCol % 1000);
	initColor.verrorCol = RGB(intIniVerrorCol / 1000000, (intIniVerrorCol / 1000) % 1000, intIniVerrorCol % 1000);
	initColor.aerrorCol = RGB(intIniAerrorCol / 1000000, (intIniAerrorCol / 1000) % 1000, intIniAerrorCol % 1000);
	initColor.overAlarmCol = RGB(intIniOverAlarmCol / 1000000, (intIniOverAlarmCol / 1000) % 1000, intIniOverAlarmCol % 1000);
	initColor.leakAlarmCol = RGB(intIniLeakAlarmCol / 1000000, (intIniLeakAlarmCol / 1000) % 1000, intIniLeakAlarmCol % 1000);
	initColor.badContCol = RGB(intIniBadContCol / 1000000, (intIniBadContCol / 1000) % 1000, intIniBadContCol % 1000);
	initColor.voverCol = RGB(intIniVoverCol / 1000000, (intIniVoverCol / 1000) % 1000, intIniVoverCol % 1000);
	initColor.batteryWinCol = RGB(intIniBatteryWinCol / 1000000, (intIniBatteryWinCol / 1000) % 1000, intIniBatteryWinCol % 1000);

	int intDefChargeCol = GetPrivateProfileInt(_T("defColor"), _T("defCharge"), 0, colorPath);
	int intDefRecycleCol = GetPrivateProfileInt(_T("defColor"), _T("defRecycle"), 0, colorPath);
	int intDefStorCol = GetPrivateProfileInt(_T("defColor"), _T("defStor"), 0, colorPath);
	int intDefUnstorCol = GetPrivateProfileInt(_T("defColor"), _T("defUnstor"), 0, colorPath);
	int intDefStopCol = GetPrivateProfileInt(_T("defColor"), _T("defStop"), 0, colorPath);
	int intDefDischargeCol = GetPrivateProfileInt(_T("defColor"), _T("defDischarge"), 0, colorPath);
	int intDefLayCol = GetPrivateProfileInt(_T("defColor"), _T("defLay"), 0, colorPath);
	int intDefVaChargeCol = GetPrivateProfileInt(_T("defColor"), _T("defVaCharge"), 0, colorPath);
	int intDefVerrorCol = GetPrivateProfileInt(_T("defColor"), _T("defVerror"), 0, colorPath);
	int intDefAerrorCol = GetPrivateProfileInt(_T("defColor"), _T("defAerror"), 0, colorPath);
	int intDefOverAlarmCol = GetPrivateProfileInt(_T("defColor"), _T("defOverAlarm"), 0, colorPath);
	int intDefLeakAlarmCol = GetPrivateProfileInt(_T("defColor"), _T("defLeakAlarm"), 0, colorPath);
	int intDefBadContCol = GetPrivateProfileInt(_T("defColor"), _T("defBadCont"), 0, colorPath);
	int intDefVoverCol = GetPrivateProfileInt(_T("defColor"), _T("defVover"), 0, colorPath);
	int intDefBatteryWinCol = GetPrivateProfileInt(_T("defColor"), _T("defBatteryWin"), 0, colorPath);

	defColor.chargeCol = RGB(intDefChargeCol / 1000000, (intDefChargeCol / 1000) % 1000, intDefChargeCol % 1000);
	defColor.recycleCol = RGB(intDefRecycleCol / 1000000, (intDefRecycleCol / 1000) % 1000, intDefRecycleCol % 1000);
	defColor.storCol = RGB(intDefStorCol / 1000000, (intDefStorCol / 1000) % 1000, intDefStorCol % 1000);
	defColor.unstorCol = RGB(intDefUnstorCol / 1000000, (intDefUnstorCol / 1000) % 1000, intDefUnstorCol % 1000);
	defColor.stopCol = RGB(intDefStopCol / 1000000, (intDefStopCol / 1000) % 1000, intDefStopCol % 1000);
	defColor.dischargeCol = RGB(intDefDischargeCol / 1000000, (intDefDischargeCol / 1000) % 1000, intDefDischargeCol % 1000);
	defColor.layCol = RGB(intDefLayCol / 1000000, (intDefLayCol / 1000) % 1000, intDefLayCol % 1000);
	defColor.vaChargeCol = RGB(intDefVaChargeCol / 1000000, (intDefVaChargeCol / 1000) % 1000, intDefVaChargeCol % 1000);
	defColor.verrorCol = RGB(intDefVerrorCol / 1000000, (intDefVerrorCol / 1000) % 1000, intDefVerrorCol % 1000);
	defColor.aerrorCol = RGB(intDefAerrorCol / 1000000, (intDefAerrorCol / 1000) % 1000, intDefAerrorCol % 1000);
	defColor.overAlarmCol = RGB(intDefOverAlarmCol / 1000000, (intDefOverAlarmCol / 1000) % 1000, intDefOverAlarmCol % 1000);
	defColor.leakAlarmCol = RGB(intDefLeakAlarmCol / 1000000, (intDefLeakAlarmCol / 1000) % 1000, intDefLeakAlarmCol % 1000);
	defColor.badContCol = RGB(intDefBadContCol / 1000000, (intDefBadContCol / 1000) % 1000, intDefBadContCol % 1000);
	defColor.voverCol = RGB(intDefVoverCol / 1000000, (intDefVoverCol / 1000) % 1000, intDefVoverCol % 1000);
	defColor.batteryWinCol = RGB(intDefBatteryWinCol / 1000000, (intDefBatteryWinCol / 1000) % 1000, intDefBatteryWinCol % 1000);

}

/*
	根据存储机柜的ini获取
	(1) 初始化默认的机柜编号defaultCabId
*/

void CBatteryManageApp::GetDefCabId()
{
	cabPath = CBatteryUtils::GetConfigPath(_T("\\config\\init\\cabinet.ini"));
	wchar_t str[MAX_CAB_NUM + 1];
	GetPrivateProfileString(_T("cabs"), _T("cabSels"), _T("0"), str, SCREEN_MAX_NUM + 1, cabPath);
	str[MAX_CAB_NUM] = '\0';
	cabSelStr = str;
	
	defCabId = -1;


	for (int idx = 0; idx < cabSelStr.GetLength(); ++idx)
	{
		if (cabSelStr[idx] == '1')
		{
			defCabId = idx + 1;
			defCabIdStr = cabIds[idx];
			break;
		}
	}
}

void CBatteryManageApp::ConnectToDatabase()
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

void CBatteryManageApp::GetCabInfos()
{
	// 初始化cabInfos
	cabInfos.clear();
	CabinetInfo tmpCabInfo;
	for (int idx = 0; idx < MAX_CAB_NUM; ++idx)
	{
		cabInfos.push_back(tmpCabInfo);
	}
	ConnectToDatabase();
	// 从数据库中获取所有的cabInfo
	pRecordset.CreateInstance(__uuidof(Recordset));
	_bstr_t querySql = "select * from CABINET_INFO where CABINET_ID > 0 ORDER BY CABINET_ID ASC";
	try
	{
		pRecordset->Open(querySql,		 // 查询DemoTable表中所有字段
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
		//if (!pRecordset->BOF)//如果此时记录集指针指向的不是第一条记录
		//{
		//	pRecordset->MoveFirst();//指向第一条记录
		//}

		//如果打开没有记录的 Recordset 对象，BOF 和 EOF 属性将设置为 True，而 Recordset 对象的 RecordCount 属性设置为零。
		if (pRecordset->ADOBOF && pRecordset->ADOEOF)//这个是判断记录集是否为空!!
		{
			AfxMessageBox(_T("表内数据为空"));
			return;
		}
		//获取数据库中的数据
		int j, i = -1;  //骂得。。如果放在while里面就会每次都会插在第零的位置。。。。
		CabinetInfo cabinetInfo;
		while (!pRecordset->ADOEOF)
		{
			cabinetInfo = CreateCabinetInfo();
			cabInfos[cabinetInfo.cabinetId - 1] = cabinetInfo;
			pRecordset->MoveNext();
		}
	}
	catch (_com_error e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s"), e.ErrorMessage());
		AfxMessageBox(errormessage);
	}
}

CabinetInfo CBatteryManageApp::CreateCabinetInfo()
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

	cabinetInfo.groupNum = cabinetInfo.groupNumPerCol*cabinetInfo.colShowNum*cabinetInfo.numPerGroup / SUBGROUP_NUM;


	return cabinetInfo;
}

// CBatteryManageApp 消息处理程序
void CBatteryManageApp::OnFileNew() 
{
	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);
	// 创建新的 MDI 子窗口
	pFrame->CreateNewChild(
		RUNTIME_CLASS(CBatteryMainFrame), IDR_BatteryManageTYPE, m_hMDIMenu, m_hMDIAccel);
}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)

END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CBatteryManageApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CBatteryManageApp 消息处理程序


void CBatteryManageApp::OnBatteryCheck()
{
	if (batteryMainWnd == NULL) 
	{
		CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);
		// 创建新的 MDI 子窗口

		batteryMainWnd = pFrame->CreateNewChild(
			RUNTIME_CLASS(CBatteryMainFrame), IDR_BatteryManageTYPE, m_hMDIMenu, m_hMDIAccel);
	}
}

void CBatteryManageApp::OnInitDialog()
{
	if (initDlg == NULL)
	{
		initDlg = new CInitDlg();
	}
	initDlg->DoModal();

	return;
}


void CBatteryManageApp::OnSetNum()
{
	if (setNumDlg == NULL)
	{
		setNumDlg = new CSetNumDlg();
	}
	setNumDlg->DoModal();

	return;
}


void CBatteryManageApp::OnOpManage()
{
	if (opManageDlg == NULL)
	{
		opManageDlg = new COpManageDlg();
	}
	opManageDlg->DoModal();

	return;
}


void CBatteryManageApp::OnOpLog()
{
	if (opLogDlg == NULL)
	{
		opLogDlg = new COpLogDlg();
	}
	opLogDlg->DoModal();

	return;
}


void CBatteryManageApp::OnOpLogin()
{
	if (opLoginDlg == NULL)
	{
		opLoginDlg = new COpLoginDlg();
	}
	opLoginDlg->DoModal();

	return;
}


void CBatteryManageApp::OnLock()
{
	if (adminLoginDlg == NULL)
	{
		adminLoginDlg = new CAdminLoginDlg();
	}
	adminLoginDlg->DoModal();

	return;
}


void CBatteryManageApp::OnExcSystem()
{
	if (adminLoginDlg == NULL)
	{
		adminLoginDlg = new CAdminLoginDlg();
	}
	adminLoginDlg->DoModal();

	return;
}




void CBatteryManageApp::OnShowCurve()
{
	// TODO:  在此添加命令处理程序代码
}


void CBatteryManageApp::OnStartWork()
{
	if (startWorkDlg == NULL)
	{
		startWorkDlg = new CStartWorkDlg();
	}
	startWorkDlg->DoModal();

	return;
}


void CBatteryManageApp::OnBatteryConn()
{
	if (batteryMainWnd == NULL)
	{
		CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);
		// 创建新的 MDI 子窗口
		batteryMainWnd = pFrame->CreateNewChild(
			RUNTIME_CLASS(CBatteryMainFrame), IDR_BatteryManageTYPE, m_hMDIMenu, m_hMDIAccel);
	}
}


void CBatteryManageApp::OnBatteryDisConn()
{
	if (adminLoginDlg == NULL)
	{
		adminLoginDlg = new CAdminLoginDlg();
	}
	adminLoginDlg->DoModal();

	return;
}


void CBatteryManageApp::OnConnDisSet()
{
	if (adminLoginDlg == NULL)
	{
		adminLoginDlg = new CAdminLoginDlg();
	}
	adminLoginDlg->DoModal();

	return;
}


void CBatteryManageApp::OnReadData()
{
	// TODO:  在此添加命令处理程序代码
}


void CBatteryManageApp::OnScreenReset()
{
	// TODO:  在此添加命令处理程序代码
}


void CBatteryManageApp::OnExcepRemove()
{
	if (excepRemoveDlg == NULL)
	{
		excepRemoveDlg = new CExcepRemoveDlg();
	}
	excepRemoveDlg->DoModal();

	return;
}


void CBatteryManageApp::OnDebugWindow()
{
	if (debugLoginDlg == NULL)
	{
		debugLoginDlg = new CDebugLoginDlg();
	}
	debugLoginDlg->DoModal();
}


void CBatteryManageApp::OnRecurPowerCut()
{
	if (screenSelDlg == NULL)
	{
		screenSelDlg = new CScreenSelDlg();
	}
	screenSelDlg->DoModal();
}


void CBatteryManageApp::OnExcepStepRecord()
{
	if (debugLoginDlg == NULL)
	{
		debugLoginDlg = new CDebugLoginDlg();
	}
	debugLoginDlg->DoModal();
}


void CBatteryManageApp::OnDatafileOpen()
{
	TCHAR szFilter[] = _T("文本文件(*.mdb)|*.mdb||");
	CFileDialog fileDlg(TRUE, _T("mdb"), NULL, 0, szFilter, theApp.m_pMainWnd);
	CString filePath;

	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		filePath = fileDlg.GetPathName();
		openFilePath = filePath;
		//SetDlgItemText(IDC_OPEN_EDIT, strFilePath);
		CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);
		// 创建新的 MDI 子窗口

		pFrame->CreateNewChild(
			RUNTIME_CLASS(CDataFileFrame), IDR_BatteryManageTYPE, m_hMDIMenu, m_hMDIAccel);
		
	}




	//if (dataDlg == NULL)
	//{
	//	dataDlg = new CDataDlg();
	//	dataDlg->Create(IDD_DATADLG, view);
	//}

	//dataDlg->ShowWindow(SW_SHOW);
	//dataDlg->SetActiveWindow();

	//}
}


void CBatteryManageApp::OnExportToMdb()
{
	TCHAR szDir[MAX_PATH];
	BROWSEINFO bi;
	ITEMIDLIST *pidl;
	bi.hwndOwner = theApp.GetMainWnd()->GetSafeHwnd();
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szDir;//这个是输出缓冲区   
	bi.lpszTitle = _T("选择导出文件位置：");//标题  
	bi.ulFlags = BIF_NEWDIALOGSTYLE;//使用新的界面,在win7中效果较好//BIF_RETURNONLYFSDIRS;   
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	pidl = SHBrowseForFolder(&bi);//弹出对话框   
	if (pidl == NULL)//点了取消，或者选择了无效的文件夹则返回NULL  
		return;

	if (SHGetPathFromIDList(pidl, szDir))
		int a = 1;
}


void CBatteryManageApp::OnBatterySearchCreater()
{
	if (searchEngineCreater == NULL)
	{
		searchEngineCreater = new CSearchEngineCreater();
	}
	searchEngineCreater->DoModal();
}


void CBatteryManageApp::OnOpenSearchEngine()
{
	if (searchEngine == NULL)
	{
		searchEngine = new CSearchEngine();
	}
	searchEngine->DoModal();
}


void CBatteryManageApp::OnCapCompare()
{
	if (capCompareDlg == NULL)
	{
		capCompareDlg = new CCapCompareDlg();
	}
	capCompareDlg->DoModal();
}


void CBatteryManageApp::OnCapExportSet()
{
	if (capExportDlg == NULL)
	{
		capExportDlg = new CCapExportDlg();
	}
	capExportDlg->DoModal();
}


void CBatteryManageApp::OnChkBatteryId()
{
	if (chkBatteryDlg == NULL)
	{
		chkBatteryDlg = new CChkBatteryDlg();
	}
	chkBatteryDlg->DoModal();
}


void CBatteryManageApp::OnBatteryGrading()
{
	// TODO:  在此添加命令处理程序代码
	if (capacityGradingDlg == NULL)
	{
		capacityGradingDlg = new CBatCapGradeDlg();
	}
	capacityGradingDlg->DoModal();
}


void CBatteryManageApp::OnSwRcAddonerow()
{
	// TODO:  在此添加命令处理程序代码
	startWorkDlg->AddOneRow();
}


void CBatteryManageApp::OnSwRcAddmulrow()
{
	// TODO:  在此添加命令处理程序代码
	startWorkDlg->AddMultiRow();
}

//void CBatteryManageApp::OnSwRcDelonerow()
//{
//	// TODO:  在此添加命令处理程序代码
//	startWorkDlg->DelOneRow();
//}


//void CBatteryManageApp::OnSwRcDelmulrow()
//{
//	// TODO:  在此添加命令处理程序代码
//	startWorkDlg->DelMultiRow();
//}


void CBatteryManageApp::OnSwRcCopy()
{
	// TODO:  在此添加命令处理程序代码
	//startWorkDlg->m_GridCtrl.OnEditCopy();
	startWorkDlg->m_GridCopyRow();
}


void CBatteryManageApp::OnSwRcCut()
{
	// TODO:  在此添加命令处理程序代码
	//startWorkDlg->m_GridCtrl.OnEditCut();
	startWorkDlg->m_GridCutRow();
}


void CBatteryManageApp::OnSwRcPaste()
{
	// TODO:  在此添加命令处理程序代码
	//startWorkDlg->m_GridCtrl.OnEditPaste();
	startWorkDlg->m_GridPasteRow();
}

void CBatteryManageApp::OnSwRcDelrow()
{
	// TODO:  在此添加命令处理程序代码
	//startWorkDlg->DelMultiRow();
	startWorkDlg->DelRow();
}


void CBatteryManageApp::OnWmSyscommand()
{
	int a = 0;
}


void CBatteryManageApp::OnWmCommand()
{
	// TODO:  在此添加命令处理程序代码
	int a = 0;
}


BOOL CBatteryManageApp::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// TODO:  在此添加专用代码和/或调用基类
	int c = 0;
	//fstream out;
	//out.open("log.txt", ios::app | ios::out);
	//out << nID;
	//if (nID == 57664)
	//{
	//	int a = 0;
	//}
	//out.close();
	return CWinApp::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}




//void CBatteryManageApp::OnPartShowBatid()
//{
//	// TODO:  在此添加命令处理程序代码
//
//}
//
//
//void CBatteryManageApp::OnPartCapCond()
//{
//	// TODO:  在此添加命令处理程序代码
//}
//
//
//void CBatteryManageApp::OnAutoPartCap()
//{
//	// TODO:  在此添加命令处理程序代码
//}


void CBatteryManageApp::OnOpertorManage()
{
	// TODO:  在此添加命令处理程序代码
}
