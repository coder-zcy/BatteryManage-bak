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


// ����
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

//ȫ�ֱ�������ͨ��ģʽ
extern int COMM_MODE;
extern CString lowerInfos;

//	ȫ�ֱ���
// CBatteryCheckView ������ͼ

class CBatteryMainView : public CFormView
{
	DECLARE_DYNCREATE(CBatteryMainView)

protected:
	CBatteryMainView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
	// ������
public:

	CPbatterysDlg* pbatterysDlgs[MAX_CAB_NUM];	// ͼ�η�ʽDlg
	CTbatterysDlg* tbatterysDlgs[MAX_CAB_NUM];	// ���ʽDlg
	CbatterysDlg*  cbatterysDlgs[MAX_CAB_NUM];	// �ۺϷ�ʽDlg
	CEbatterysDlg* ebatterysDlgs[MAX_CAB_NUM];	// �쳣Dlg

	//CPbatterysDlg  *pbatterysDlg;	// ͼ�η�ʽDlg
	//CTbatterysDlg *tbatterysDlg;	// ���ʽDlg
	//CbatterysDlg *cbatterysDlg;		// �ۺϷ�ʽDlg
	//CEbatterysDlg *ebatterysDlg;	// �쳣Dlg

	BOOL paintFlag;

	CStatic batterysPanePic;
	CBitmap bmp;;//����һ��λͼ����
	CDC memDC;  //���ȶ���һ����ʾ�豸����

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

	// ѡ���ض���CabLink
	void SelSpecCabLink(int cabId, CLinkCtrl &cabLink);

	// ����Access���ݿ�Ķ���
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
	BOOL CanConnFlag;		//	�ж��Ƿ��տ��Խ�������
	BOOL SendStepFlag;	//	�ж��Ƿ�ɽ��з��͹�����־
	CWinThread* m_hSendThread;
	vector<CByteArray *> obtainModelMsgs;			//	��ȡÿ���������λ���ͺ�
	vector<vector<CByteArray *> > cabStepMsgs;		//	������Ϣ		
	BOOL cabStepFlags[MAX_CAB_NUM][MAX_STEP_NUM];	//	�ж�ĳ��������ȷ�յ��ı��
	int beatStatus[MAX_CAB_NUM];
	vector<CByteArray *> cabConMsgs;				//	������������Ϣ
	BOOL cabConFlags[MAX_CAB_NUM];					//	�ж��Ƿ������ı��
	BOOL OBTAIN_BATDATA_FLAG;						//	������Ի�ȡ������λ�������Ϣ��ָ��

	BOOL obtainModelFlags[MAX_CAB_NUM];				//	�ж���λ���Ƿ�����ӵı��
	BOOL obtainModelFlag;							//	

	//BOOL portOpenFlag;
	BOOL InitSerialPort(int portNum);//���԰�

	void CloseSerialPort();

	//static UINT SendThread(LPVOID param);//���ʹ��������߳�

	BOOL CreateDatabases();

	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm1();//�������ݽ���
	int count;


	void HandleLowerInfos();
	
	void ConvertToBatteryInfos(CString lowerInfos);		//	����λ����Ϣת����vector
	
	void HandleLowerInfo(CString lowerInfos, int pieceLen);			//	������λ���ϴ�������


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
