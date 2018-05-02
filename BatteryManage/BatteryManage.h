
// BatteryManage.h : BatteryManage Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
// ��Ҫ����
#include "InitDlg.h"
#include "OpLoginDlg.h"
#include "SetNumDlg.h"
#include "OpManageDlg.h"
#include "AdminLoginDlg.h"
#include "OpLogDlg.h"

// ���Ʋ���
#include "StartWorkDlg.h"
#include "AdminLoginDlg.h"
#include "ExcepRemoveDlg.h"
#include "DebugLoginDlg.h"
#include "ScreenSelDlg.h"
#include "BatCapGradeDlg.h"

// ���ݹ���
#include "SearchEngineCreater.h"
#include "SearchEngine.h"
#include "CapCompareDlg.h"
#include "CapExportDlg.h"
#include "ChkBatteryDlg.h"

// �����ļ�
#include "DataFileFrame.h"

//
#include "BatteryUtils.h"

//	ͨ�Ų���
#include "CommConf.h"

// ��λ������

#include "CabUtils.h"


// ȫ��ColorInfo
extern CBatteryColor initColor;
extern CBatteryColor defColor;
extern CString colorPath;

// ȫ��CabinetInfo
extern int defCabId;
extern _bstr_t defCabIdStr;

extern vector<CabinetInfo> cabInfos;
extern CString paneId;
extern CString cabPath;
extern CString dbConfigPath;
extern CString cabSelStr;
extern CabinetInfo defCabInfo;

//  ��ǰcabId
extern int curCabId;

// ��ر��
extern int curRowId;
extern int curGroupId;
extern int curGroupInnerId;
extern int curBatteryId;

// ȫ�ֿ��Ʊ߿��С�ı���
extern BOOL maxminFlag;
extern HICON selIcon;

// ���ļ������˵�����
extern CString openFilePath;

#define STATE_REPAINT  0
#define INIT_REPAINT  1
#define TIP_REPAINT  2
#define BATTERY_BORDER_WIDTH 1

#define MARGIN_LEFT_BATPANE 135
#define MARGIN_TOP_BATPANE 30


#define FRONT_PANE "��壺<a>A</a>"
#define BACK_PANE "��壺<a>B</a>"

//  �Ƿ�cabId
#define INVALIDE_CABID -1
//  ÿһС��ĸ���
#define SUBGROUP_NUM 8

#define WM_COLSE_DATAFILEVIEW_MSG WM_USER+0x01010		//	�ر�DataFileView����
// CBatteryManageApp:
// �йش����ʵ�֣������ BatteryManage.cpp
//

class CBatteryManageApp : public CWinApp
{
public:
	CBatteryManageApp();


// ��д
public:
	// ��ʼ����ɫ����
	void InitColorSet();
	// ��ʼ��Ĭ�ϵĻ�����Ϣ
	void GetDefCabId();
	void GetCabInfos();
	void ConnectToDatabase();
	CabinetInfo CreateCabinetInfo();

	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
protected:
	HMENU  m_hMDIMenu;
	HACCEL m_hMDIAccel;

public:
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	DECLARE_MESSAGE_MAP()


public:
	CInitDlg *initDlg;		//��ʼ���ô���
	COpLoginDlg *opLoginDlg;
	CSetNumDlg *setNumDlg;
	COpManageDlg *opManageDlg;
	CAdminLoginDlg *adminLoginDlg;
	COpLogDlg *opLogDlg;

	// ͨ������
	CommConf *commConf;

	afx_msg void OnInitDialog();
	afx_msg void OnSetNum();
	afx_msg void OnOpManage();
	afx_msg void OnOpLog();
	afx_msg void OnOpLogin();
	afx_msg void OnLock();
	afx_msg void OnExcSystem();
	
public:
	// ���Ʋ���
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
	// iconͼ��
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
