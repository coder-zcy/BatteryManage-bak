#pragma once
#include "afxwin.h"
#include "bat_chart.h"

#include "FileCabData.h"
#include "LowerUtils.h"
#include "DbUtils.h"

#define MAX_BAT_NUM 1024

#define INVALIDE_BAT_IDX -1

const int TOP_ASSEMBLE_GAP = 5;
const int LEFT_ASSEMBLE_GAP = 2;
const int RIGHT_ASSEMBLE_GAP = 2;
const int BOTTOM_ASSEMBLE_GAP = 2;

// CCurveDlg 对话框

class CCurveDlg : public CDialog
{
	DECLARE_DYNAMIC(CCurveDlg)

public:
	CCurveDlg(CWnd* pParent = NULL);   // 标准构造函数
	CCurveDlg(CWnd* pParent, CFileCabData fileCabData);   // 标准构造函数
	virtual ~CCurveDlg();

// 对话框数据
	enum { IDD = IDD_CURVE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void ChangeChartPosByCheck(int check);
	CComboBox stepCom;
	CComboBox batIdCom;
	CComboBox dateTimeCom;
	CBat_chart batChart;
	CEdit workDesEdit;
	BOOL multiSel;

	CFileCabData fileCabData;

	virtual BOOL OnInitDialog();
	void InitCombox();
	void InitBatChart(int batId, int stepId);
	void InitBatChart2(int batId, int stepId);
	afx_msg void OnCbnSelchangeStepCombo();
	afx_msg void OnCbnSelchangeBatidCombo();
	afx_msg void OnCbnSelchangeDatetimeCombo();
	void InitBatWorkRecord();

};
