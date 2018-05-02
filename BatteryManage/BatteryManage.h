
// BatteryManage.h : BatteryManage 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
// 主要设置
#include "InitDlg.h"
#include "OpLoginDlg.h"
#include "SetNumDlg.h"
#include "OpManageDlg.h"
#include "AdminLoginDlg.h"
#include "OpLogDlg.h"

// 控制测试
#include "StartWorkDlg.h"
#include "AdminLoginDlg.h"
#include "ExcepRemoveDlg.h"
#include "DebugLoginDlg.h"
#include "ScreenSelDlg.h"
#include "BatCapGradeDlg.h"

// 数据工具
#include "SearchEngineCreater.h"
#include "SearchEngine.h"
#include "CapCompareDlg.h"
#include "CapExportDlg.h"
#include "ChkBatteryDlg.h"

// 数据文件
#include "DataFileFrame.h"

//
#include "BatteryUtils.h"

//	通信测试
#include "CommConf.h"

// 下位机帮助

#include "CabUtils.h"


// 全局ColorInfo
extern CBatteryColor initColor;
extern CBatteryColor defColor;
extern CString colorPath;

// 全局CabinetInfo
extern int defCabId;
extern _bstr_t defCabIdStr;

extern vector<CabinetInfo> cabInfos;
extern CString paneId;
extern CString cabPath;
extern CString dbConfigPath;
extern CString cabSelStr;
extern CabinetInfo defCabInfo;

//  当前cabId
extern int curCabId;

// 电池编号
extern int curRowId;
extern int curGroupId;
extern int curGroupInnerId;
extern int curBatteryId;

// 全局控制边框大小的变量
extern BOOL maxminFlag;
extern HICON selIcon;

// 打开文件下拉菜单变量
extern CString openFilePath;

#define STATE_REPAINT  0
#define INIT_REPAINT  1
#define TIP_REPAINT  2
#define BATTERY_BORDER_WIDTH 1

#define MARGIN_LEFT_BATPANE 135
#define MARGIN_TOP_BATPANE 30


#define FRONT_PANE "面板：<a>A</a>"
#define BACK_PANE "面板：<a>B</a>"

//  非法cabId
#define INVALIDE_CABID -1
//  每一小组的个数
#define SUBGROUP_NUM 8

#define WM_COLSE_DATAFILEVIEW_MSG WM_USER+0x01010		//	关闭DataFileView窗口
// CBatteryManageApp:
// 有关此类的实现，请参阅 BatteryManage.cpp
//

class CBatteryManageApp : public CWinApp
{
public:
	CBatteryManageApp();


// 重写
public:
	// 初始化颜色设置
	void InitColorSet();
	// 初始化默认的机柜信息
	void GetDefCabId();
	void GetCabInfos();
	void ConnectToDatabase();
	CabinetInfo CreateCabinetInfo();

	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
protected:
	HMENU  m_hMDIMenu;
	HACCEL m_hMDIAccel;

public:
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	DECLARE_MESSAGE_MAP()


public:
	CInitDlg *initDlg;		//初始设置窗口
	COpLoginDlg *opLoginDlg;
	CSetNumDlg *setNumDlg;
	COpManageDlg *opManageDlg;
	CAdminLoginDlg *adminLoginDlg;
	COpLogDlg *opLogDlg;

	// 通信配置
	CommConf *commConf;

	afx_msg void OnInitDialog();
	afx_msg void OnSetNum();
	afx_msg void OnOpManage();
	afx_msg void OnOpLog();
	afx_msg void OnOpLogin();
	afx_msg void OnLock();
	afx_msg void OnExcSystem();
	
public:
	// 控制测试
	CStartWorkDlg *startWorkDlg;
	//CAdminLoginDlg *adminLoginDlg;
	CExcepRemoveDlg *excepRemoveDlg;
	CDebugLoginDlg *debugLoginDlg;
	CScreenSelDlg *screenSelDlg;
	CBatCapGradeDlg *capacityGradingDlg;
	CMDIChildWnd *batteryMainWnd;

	afx_msg void OnBatteryCheck();
	afx_msg void OnShowCurve();
	afx_msg void OnStartWork();
	afx_msg void OnBatteryConn();
	afx_msg void OnBatteryDisConn();
	afx_msg void OnConnDisSet();
	afx_msg void OnReadData();
	afx_msg void OnScreenReset();
	afx_msg void OnExcepRemove();
	afx_msg void OnDebugWindow();
	afx_msg void OnRecurPowerCut();
	afx_msg void OnExcepStepRecord();
	afx_msg void OnDatafileOpen();

public:
	CSearchEngineCreater *searchEngineCreater;
	CSearchEngine *searchEngine;
	CCapCompareDlg *capCompareDlg;
	CCapExportDlg *capExportDlg;
	CChkBatteryDlg *chkBatteryDlg;

	afx_msg void OnExportToMdb();
	afx_msg void OnBatterySearchCreater();
	afx_msg void OnOpenSearchEngine();
	afx_msg void OnCapCompare();
	afx_msg void OnCapExportSet();
	afx_msg void OnChkBatteryId();
	afx_msg void OnBatteryGrading();
	afx_msg void OnSwRcAddonerow();
	afx_msg void OnSwRcAddmulrow();
//	afx_msg void OnSwRcDelonerow();
//	afx_msg void OnSwRcDelmulrow();
	afx_msg void OnSwRcCopy();
	afx_msg void OnSwRcCut();
	afx_msg void OnSwRcPaste();

public:
	// icon图标
	HICON selIcon;
	HBITMAP selBmp;
public:
	HRESULT hr;
	_CommandPtr pCommand;
	_RecordsetPtr pRecordset;
	_ConnectionPtr pConnection;

	afx_msg void OnSwRcDelrow();
	afx_msg void OnWmSyscommand();
	afx_msg void OnWmCommand();
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//afx_msg void OnPartShowBatid();
	//afx_msg void OnPartCapCond();
	//afx_msg void OnAutoPartCap();
	afx_msg void OnOpertorManage();
	
};

extern CBatteryManageApp theApp;
