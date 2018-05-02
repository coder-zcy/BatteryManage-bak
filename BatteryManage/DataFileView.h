#pragma once


#include "DataContainer.h"
#include "CompDlg.h"
#include "PartDlg.h"
#include "CurveDlg.h"
#include "LoopDlg.h"
#include "StatisticDlg.h"
#include "StatisticMenuDlg.h"
#include "SloopMenuDlg.h"
#include "FileCabData.h"
#include "BatWorkDetailDlg.h"


#include <iostream>
#include <vector>
#include <algorithm>
#include "afxcmn.h"
#include "afxwin.h"

#include "CapShowType.h"
#include "PartCapCondDlg.h"
	

using namespace std;

#define DATA_LEFT_WIDTH 150
#define DATA_TOP_HEIGHT 200
#define COMP_DLG_ID 0
#define PART_DLG_ID 1
#define STATISTIC_DLG_ID 2
#define CURVE_DLG_ID 3
#define LOOP_DLG_ID 4
#define STATISTIC_MENU_DLG_ID 5
#define SLOOP_MENU_DLG_ID 6


#define MAX_VALIDE_NUM  16

// CDataFileView 窗体视图

class CDataFileView : public CFormView
{
	DECLARE_DYNCREATE(CDataFileView)

public:
	CDataFileView();           // 动态创建所使用的受保护的构造函数
	virtual ~CDataFileView();

public:
	enum { IDD = IDD_DATAFILE_VIEW };
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
	afx_msg void OnSize(UINT nType, int cx, int cy);

	virtual void OnInitialUpdate();
public:
	CCompDlg			*compDlg;
	CPartDlg			*partDlg;
	CCurveDlg			*curveDlg;
	CLoopDlg			*loopDlg;
	CStatisticDlg		*statisticDlg;
	CStatisticMenuDlg	*statisticMenuDlg;
	CSloopMenuDlg		*sloopMenuDlg;
	CBatWorkDetailDlg	*batWorkDetailDlg;

	CStatic menuPic;
	vector<CDialog *> dlgArray;

	afx_msg void OnPaint();

	vector<CString> linkNames;
	vector<CString> hoverLinkNames;
	vector<CLinkCtrl *> links;
	vector<CRect> winRects;
	vector<CRect> linkRects;

	CLinkCtrl compLink;
	CLinkCtrl partLink;
	CLinkCtrl statisticLink;
	CLinkCtrl curveLink;
	CLinkCtrl loopLink;

	CRect compRect;
	CRect partRect;
	CRect statisticRect;
	CRect curveRect;
	CRect loopRect;
	int windowFlag;

	void InitWinLinks();
	CStatic winSel;
	afx_msg void OnNMClickCompLink(NMHDR *pNMHDR, LRESULT *pResult);

	void OpenCompDlg();

	afx_msg void OnNMClickPartLink(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickStatisticLink(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickCurveLink(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickLoopLink(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void InitDataContent(CString openFilePath);
	CStatic dataPane;

	BOOL InitCabDataFlag;
	CFileCabData fileCabData;

	//分容条件提示框
	CPartCapCondDlg *partCapCondDlg;
	afx_msg void OnPartCapCond();
	afx_msg void OnPartShowBatid();
	afx_msg void OnAutoPartCap();
	afx_msg LRESULT OnUpdatePartBattery(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRefreshWindow(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnChangeChartPosByCheck(WPARAM wParam, LPARAM lParam);
	
	afx_msg void OnBnClickedFileInfoBtn();
	void UpdateRelativeMenus();
	afx_msg void OnClose();
	virtual BOOL DestroyWindow();
};


