#pragma once
#include "Resource.h"
#include "DeviceSetInfoDlg.h"
#include "PbatterysDlg.h"
#include "TbatterysDlg.h"
#include "CbatterysDlg.h"
#include "EbatterysDlg.h"
#include "BatteryMessage.h"
#include "CabinetInfo.h"
#include "LowerUtils.h"
#include "Battery.h"
#include "CommConf.h"


// 工序
#include "WorkProc.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "afxwin.h"
#include "afxcmn.h"
#include "mscomm1.h"
using namespace std;

#define SET_INFO_IDX	0
#define PRE_DATA_IDX	1
#define SHOW_STYLE_IDX	2
#define LEFT_MOUSE_IDX  3
#define SPEC_CTL_IDX    4

#define MAX_STEP_NUM	100



extern const string SCSA_CHARGE_STR;
extern const string SA_CHARGE_STR;
extern const string SA_DISCHARGE_STR;
extern const string LAY_STR;
extern const string OVER_STR;
extern const string LOOP_STR;

//全局变量控制通信模式
extern int COMM_MODE;
extern CString lowerInfos;

//	全局变量
// CBatteryCheckView 窗体视图

class CBatteryMainView : public CFormView
{
	DECLARE_DYNCREATE(CBatteryMainView)

protected:
	CBatteryMainView();           // 动态创建所使用的受保护的构造函数
	virtual ~CBatteryMainView();

public:
	enum { IDD = IDD_BATTERY_MAIN_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

public:
	CDeviceSetInfoDlg *deviceSetInfoDlg;
	afx_msg void OnStnClickedInfoSetStatic();

	afx_msg void OnNMClickSetInfoStatic(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickPreDataStatic(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickShowStyleStatic(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickLeftMouseStatic(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickSpecCtlStatic(NMHDR *pNMHDR, LRESULT *pResult);

	CLinkCtrl preDataStatic;
	CLinkCtrl setInfoStatic;
	CLinkCtrl showStyleStatic;
	CLinkCtrl leftMouseStatic;
	CLinkCtrl specCtlStatic;

	CRect setRect;
	CRect preRect;
	CRect showRect;
	CRect leftRect;
	CRect specRect;

	vector<CString> linkNames;
	vector<CString> hoverLinkNames;

	vector<CLinkCtrl *> links;
	vector<CRect> rects;
	// TestInfo
	vector<TestInfo *> testInfos;

	CommConf *commConf;
	CMscomm1 m_ctrlComm;
	CString m_strEditReceiveMsg;//for test
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual void OnInitialUpdate();
	// 电池面板
public:

	CPbatterysDlg* pbatterysDlgs[MAX_CAB_NUM];	// 图形方式Dlg
	CTbatterysDlg* tbatterysDlgs[MAX_CAB_NUM];	// 表格方式Dlg
	CbatterysDlg*  cbatterysDlgs[MAX_CAB_NUM];	// 综合方式Dlg
	CEbatterysDlg* ebatterysDlgs[MAX_CAB_NUM];	// 异常Dlg

	//CPbatterysDlg  *pbatterysDlg;	// 图形方式Dlg
	//CTbatterysDlg *tbatterysDlg;	// 表格方式Dlg
	//CbatterysDlg *cbatterysDlg;		// 综合方式Dlg
	//CEbatterysDlg *ebatterysDlg;	// 异常Dlg

	BOOL paintFlag;

	CStatic batterysPanePic;
	CBitmap bmp;;//定义一个位图对象
	CDC memDC;  //首先定义一个显示设备对象

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnNMRClickShowStyleStatic(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickLeftMouseStatic(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickSpecCtlStatic(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBatterySelect();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CLinkCtrl cabLink1;
	CLinkCtrl cabLink2;
	CLinkCtrl cabLink3;
	CLinkCtrl cabLink4;
	CLinkCtrl cabLink5;
	CLinkCtrl cabLink6;
	CLinkCtrl cabLink7;
	CLinkCtrl cabLink8;
	CLinkCtrl cabLink9;
	CLinkCtrl cabLink10;
	CLinkCtrl cabLink11;
	CLinkCtrl cabLink12;
	CLinkCtrl cabLink13;
	CLinkCtrl cabLink14;
	CLinkCtrl cabLink15;
	CLinkCtrl cabLink16;
	CLinkCtrl cabLink17;
	CLinkCtrl cabLink18;
	CLinkCtrl cabLink19;
	CLinkCtrl cabLink20;

	CComboBox paraCom;
	CStatic cabSel;

	vector<CRect> cabRects;

	CLinkCtrl paneIdLink;

	vector<CLinkCtrl *> cabLinks;
	CString cabInitPath;
	void InitCabLinks();

	afx_msg void OnNMClickCabLink1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickCabLink2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickCabLink3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickCabLink4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickCabLink5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickCabLink6(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickCabLink7(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickCabLink8(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickCabLink9(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickCabLink10(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickCabLink11(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickCabLink12(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickCabLink13(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickCabLink14(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickCabLink15(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickCabLink16(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickCabLink17(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickCabLink18(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickCabLink19(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickCabLink20(NMHDR *pNMHDR, LRESULT *pResult);

	// 选择特定的CabLink
	void SelSpecCabLink(int cabId, CLinkCtrl &cabLink);

	// 连接Access数据库的东东
	_ConnectionPtr pConnection;
	_CommandPtr pCommand;
	_RecordsetPtr pRecordset;
	HRESULT hr;
	CString dbConfigPath;

	void ConnectToDatabase();
	void LoadBatteryDlg();
	CabinetInfo GetResultSetCabInfo();
	CabinetInfo GetCabInfoByCurId();

	CabinetInfo cabinetInfo;

public:
	BOOL CanConnFlag;		//	判断是否收可以进行联机
	BOOL SendStepFlag;	//	判断是否可进行发送工步标志
	CWinThread* m_hSendThread;
	vector<CByteArray *> obtainModelMsgs;			//	获取每个机柜的下位机型号
	vector<vector<CByteArray *> > cabStepMsgs;		//	工步信息		
	BOOL cabStepFlags[MAX_CAB_NUM][MAX_STEP_NUM];	//	判断某个工部正确收到的标记
	int beatStatus[MAX_CAB_NUM];
	vector<CByteArray *> cabConMsgs;				//	启动联机的信息
	BOOL cabConFlags[MAX_CAB_NUM];					//	判断是否联机的标记
	BOOL OBTAIN_BATDATA_FLAG;						//	单独针对获取超长下位机电池信息的指令

	BOOL obtainModelFlags[MAX_CAB_NUM];				//	判断下位机是否可连接的编号
	BOOL obtainModelFlag;							//	

	//BOOL portOpenFlag;
	BOOL InitSerialPort(int portNum);//测试版

	void CloseSerialPort();

	//static UINT SendThread(LPVOID param);//发送串口数据线程

	BOOL CreateDatabases();

	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm1();//串口数据接收
	int count;


	void HandleLowerInfos();
	
	void ConvertToBatteryInfos(CString lowerInfos);		//	将下位机信息转换成vector
	
	void HandleLowerInfo(CString lowerInfos, int pieceLen);			//	处理下位机上传的数据


	afx_msg void OnNMClickPaneId(NMHDR *pNMHDR, LRESULT *pResult);
	
	
	afx_msg void OnCbnSelchangeParaCom();

	afx_msg void OnBatPicStyle();
	afx_msg void OnBatTableStyle();
	afx_msg void OnBatCompStyle();
	afx_msg void OnExcpShow();

public:
	CMenu batShowMenu;
	CMenu *batShowSubMenu;
	
	int BatShowStyle;

	void InitBatShowMenu();
	CEdit recvDataEdit;
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	void InitilizeConsoleDevice();
	void CloseConsoleDevice();
	CUIntArray  ports;
	CUIntArray  portse;
	CUIntArray  portsu;
	void EnumerateSerialPorts(CUIntArray& ports, CUIntArray& portse, CUIntArray& portsu);
	CStatic workStateDescStatic;
	CString workStateDescStrs[MAX_CAB_NUM];
};


class DBus{
private:
	DBus();
	DBus(const DBus&);
	~DBus();

	static CMscomm1 *_instance;
public:
	static CMscomm1* GetInstance(){ return _instance; }
	static void DelInstance(){ delete _instance; }

public:
	int initialize();
	int run();

	void setDBSock(SOCKET sock){ _dbSock = sock; }
	SOCKET getDBSock()const{ return _dbSock; }

	void setServSock(int servID, SOCKET sock){ _servTab[servID] = sock; }
	SOCKET getServSock(int servID){ return (_servTab.count(servID) > 0) ? _servTab[servID] : INVALID_SOCKET; }

	

	//2014.12.28
	int getNewInstID();

private:

	HANDLE _hSendThread;
	SOCKET _listenSock;
	SOCKET _dbSock;
	std::map<int, SOCKET> _servTab;
	
};
