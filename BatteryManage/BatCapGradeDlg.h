#pragma once
#include"BCG_DrawingCircleDlg.h"
#include"BCG_ImportResistanceDLG.h"
#include"BCG_OptionDLG.h"
#include"BCG_PairDLG.h"
#include"ExcludeExceptionDLG.h"
#include "AutoAdapt.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "FileStepData.h"
#include "GradeContentDlg.h"
#include "CapGradeConf.h"
#include "GridCtrl_src\GridCtrl.h"

// CBatteryCapacityGradingDLG  分容 对话框
#define MAX_BAT_NUM 1024

class CBatCapGradeDlg : public CDialog
{
	DECLARE_DYNAMIC(CBatCapGradeDlg)

public:
	CBatCapGradeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBatCapGradeDlg();
	virtual BOOL OnInitDialog();

	void SetEditsPos();
	void InitGradeComb();

	// 对话框数据
	enum { IDD = IDD_BatteryCapacityGradingDlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CFileStepData fileStepData;
	CString filePath;

	CGradeContentDlg *gradeContentDlg;
	CAutoAdapt autoAdaptHelper;
	CBCG_DrawingCircleDlg *draw_circleDlg;
	CBCG_ImportResistanceDLG *importResistancedlg;
	CBCG_OptionDLG *OptionDlg;
	CBCG_PairDLG *pairDLg;
	CExcludeExceptionDLG *excludeExceptiondlg;


	CStatic DrawCircle_rect;
	//CListCtrl LC_BatteryPercent;
	//CListCtrl LC_BatteryStatus;
	afx_msg void OnBnClickedBcgBtnoption();
	afx_msg void OnBnClickedBcgBtnpair();
	afx_msg void OnBnClickedBcgBtnimportresistance();
	afx_msg void OnBnClickedBcgBtnexcludeexception();


	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCbnSelchangeCombo2();
	void InitEditContent();
	void InitFileStepData();	//	初始化工步信息
	CComboBox cabComb;
	CEdit numEdit;
	CEdit ratioEdit;
	afx_msg void OnBnClickedBcgBtncoldgrading();
	afx_msg LRESULT OnUpdateBatCapGrid(WPARAM wParam, LPARAM lParam);	//更新表格
	void LoadStepToGrid(int stepId);
	void LoadStepsToGrid(int stepIds[]);
	void InitGradeBasicSet();
	void InitDataGridBasicSet();
	void InitGradeGridHead();
	void InitDataGridHead();
	void InitDataGridContent();
	void InitCabComb();


	CGridCtrl gradeGrid;
	CGridCtrl stepDataGrid;

	
	void InitDefCapGradeSet();
	CComboBox gradeNameComb;
	afx_msg void OnBnClickedBcgMin();
	afx_msg void OnBnClickedBcgAdd();
	afx_msg LRESULT OnCalCapGrade(WPARAM wParam, LPARAM lParam);
	void CalCapGrade();

	int stepId;
	double validBatCount;
	int levelNum[MAX_LEVEL_NUM];
	double levelRatio[MAX_LEVEL_NUM];
	CapGradeConf *capGridConf;

	vector<CBatCapInfo> batCapInfos;
	int batCount = 0;
	int batLevelStats[MAX_BAT_NUM];
	const COLORREF gridSelColor = RGB(205, 0, 205);
	COLORREF gridDefColor = RGB(255, 255, 255);

	void LightPane(int gradeId);	//点亮主面板
	void LightGradeGrid(int gradeId);
	void LightStepDataGrid(int gradeId);
	void CalCapRatio();
	afx_msg void OnBnClickedBcgBtnsend();


	afx_msg void OnCbnSelchangeGradenameComb();
	afx_msg void OnClose();
};
