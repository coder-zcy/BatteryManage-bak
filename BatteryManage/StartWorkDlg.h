#pragma once
#include"GridCtrl_src\GridCtrl.h"
#include"SW_AddRowNumDlg.h"
#include"SW_DelRowNumDlg.h"
#include"SW_CopyParameterDlg.h"
#include"SW_SendDlg.h"
#include"SW_NumberingDlg.h"
#include "FileUtils.h"
#include "SW_CycleDlg.h"
#include "afxcmn.h"
#include "ChannelInfo.h"
#include "ChannelCurve.h"
#include "ChannelStep.h"
#include "TestInfo.h"
#include "DlgComm.h"	// 对话框之间通信用的辅助类
#include "DbUtils.h"
#include "StepMsg.h"

// 工序类
#include "WorkProc.h"
#include "WorkStep.h"

#include <iostream>
#include <ctime>
#include <vector>
#include "afxwin.h"

using namespace std;

// CStartWorkDlg 对话框

#define CONST_AV_CHARGE		0
#define CONST_A_CHARGE		1
#define CONST_A_DISCHARGE	2
#define LAY					3
#define OVER				4
#define CYCLE				5
#define STORE				6
#define UNSTORE             7

// GridControl

#define GRID_ROW_HEIGHT 25
#define GRID_SEL_WIDTH 100
#define GRID_COL_WIDTH 76

extern CWorkProc* workProcs[MAX_CAB_NUM];

class CStartWorkDlg : public CDialog
{
	DECLARE_DYNAMIC(CStartWorkDlg)

public:
	CStartWorkDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStartWorkDlg();
	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_STARTWORK_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CGridCtrl m_GridCtrl;
	
	CSW_AddRowNumDlg *addrowNumDlg;
	CSW_DelRowNumDlg *delrowNumDlg;
	CSW_CopyParameterDlg *cpDlg;
	CSW_SendDlg *sendDlg;
	CSW_NumberingDlg *numberingDlg;
	CSW_CycleDlg *cycleDlg;
public:
	//刷新最左边序号
	void updateAllRow();
	void m_InsertRow(int nRow);
	void AddOneRow();
	void DelOneRow();
	void AddMultiRow();
	void DelMultiRow();
	void DelRow();
	//刷新表格中的状态
	void updateGridStatus();

	afx_msg void OnGridStartSelChange(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnGridEndSelChange(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnGridRClick(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedBtnSwOpenproc();
	afx_msg void OnBnClickedBtnSwSaveproc();
	afx_msg void OnBnClickedBtnSwCopyparameter();
	afx_msg void OnBnClickedBtnSwBatteryNum();
	afx_msg void OnBnClickedBtnSwSend();
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

	CRect cabRect1;
	CRect cabRect2;
	CRect cabRect3;
	CRect cabRect4;
	CRect cabRect5;
	CRect cabRect6;
	CRect cabRect7;
	CRect cabRect8;
	CRect cabRect9;
	CRect cabRect10;
	CRect cabRect11;
	CRect cabRect12;
	CRect cabRect13;
	CRect cabRect14;
	CRect cabRect15;
	CRect cabRect16;
	CRect cabRect17;
	CRect cabRect18;
	CRect cabRect19;
	CRect cabRect20;
	
    CStatic cabSel;
	CString cabInitPath;
	vector<CLinkCtrl *> cabLinks;
	vector<CRect> cabRects;


	vector<CString> linkNames;
	vector<CString> hoverLinkNames;

	time_t nowTimeInfo;
	tm nowTime;
	int defaultCabId;
	int stepCabId;				//记录机柜编号的Id

	void InitColorSet();
	void InitCabLinks();
	void InitOtherInfo();
	void CreateTimePath();
	void InitSpecCabInfoByPara();						// 通过内存中定义的参数来初始化
	void InitSpecCabInfoByFile(int cabId);	// 通过硬盘中定义的参数来初始化
	void InitOtherCabInfo(int cabId);		// 初始化除该Id以外的所有数据
	void InitSpecStepInfoByFile(int cabId, CString filePath);
	void InitSpecStepInfoByFile2(int cabId, CString filePath);
	void InitSpecStepInfoByPara(int cabId);
	void InitOtherInfo(int cabId, CString otherInitPath);
	void InitGrid();
	CString CheckGrid();

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
	
	CEdit workProcEdit;		// 工序名称
	CEdit modelEdit;		// 型号名称

	CEdit batCapEdit;
	CEdit warnCapEdit;
	CEdit vseperateEdit;
	CEdit vcycleEdit;
	CEdit stopStepNumEdit;
	CEdit stopCycleEdit;
	CEdit featureEdit1;
	CEdit featureEdit2;
	CEdit featureEdit3;
	CEdit featureEdit4;
	CEdit featureEdit5;
	CEdit dataFileEdit;
	CEdit fileRemarkEdit;

	CString otherInitPath;
	CString stepInitPath;	//	工步初始化位置
	CString defaultBasePath;
	CString defaultDbPath;
	CString timePath;		//	根据时间产生的path

	CString workProcVal;
	CString modelVal;

	//CWorkProc* workProcs[MAX_CAB_NUM];

	int batCapVal;
	int warnCapVal;
	int vseperateVal;
	int vcycleVal;
	int stopStepNumVal;
	int stopCycleVal;
	int vpointVal;
	int tpointVal;
	int featureVal1;
	int featureVal2;
	int featureVal3;
	int featureVal4;
	int featureVal5;
	CString dataFileVal;
	CString fileRemarkVal;

	vector<CString> stepNames;
	vector<COLORREF> stepColors;
	COLORREF defaultStepColor;
	CString colorPath;

	int cycleLastStep; 
	int beginSelRow;//记录开始选择的行
	int endSelRow;//记录结束选择的行
	//bool isOpenProc;
	vector<vector<CString>> m_GridPasteBoard;	//	表格的粘贴板
	BOOL GridCopyFlag;							//	表格的复制粘贴标记
	BOOL GridCutFlag;							//  表格的剪切标记
	void m_GridCopyRow();
	void m_GridCutRow();
	void m_GridPasteRow();

	// 每当Grid进行改变时更新相应的工序
	void UpdateWorkProcs(int cabId);
	
	_CommandPtr pCommand;
	_RecordsetPtr pRecordset;
	_ConnectionPtr pConnection;

	BOOL CreateDatabase(CString dbNameStr);
	BOOL ConnectToDatabase(CString dbNameStr);
	BOOL CreateDbTables(CString dbNameStr);
	BOOL CreateTable(CString dbNameStr, CString tableNameStr, CString &createTestInfoStr);
	
	afx_msg void OnBnClickedCreateDatabase();
	afx_msg void OnBnClickedBtnSwClose();


	
protected:
	afx_msg LRESULT OnCloseStartDlg(WPARAM wParam, LPARAM lParam);
	void UpdateWorkStep(CWorkStep& workStep, CString colStr, int colId);
public:
	afx_msg void OnClose();
};
