#pragma once
#include "afxwin.h"
#include "GridCtrl_src\GridCtrl.h"
#include "GridUtils.h"
#include "TestInfo.h"
#include "bat_chart.h"
#include "CapShowType.h"



//默认分容数组大小
const int DEF_PART_CNT = 8;
const int PART_CNT = 16;

#define MAX_FLAG_NUM 16

// CStatisticDlg 对话框

class CStatisticDlg : public CDialog
{
	DECLARE_DYNAMIC(CStatisticDlg)

public:
	CStatisticDlg(CWnd* pParent = NULL);   // 标准构造函数
	CStatisticDlg(CWnd* pParent, CFileCabData fileCabData);

	virtual ~CStatisticDlg();

// 对话框数据
	enum { IDD = IDD_STATISTIC_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CStatic batNumStatic;
	CStatic checkOutNumStatic;
	CStatic checkoutRatioStatic;
	CStatic maxStatic;
	CStatic minStatic;
	CStatic avgStatic;

	CGridCtrl segGrid;
	CGridCtrl capGrid;

	afx_msg void OnGridRClick(NMHDR *pNotifyStruct, LRESULT* pResult);

	virtual BOOL OnInitDialog();
	void InitPartSize(CRect rect);
	void InitSegGird();
	void InitCapGrid();
	void InitSegGridSize();
	void InitSegGridHead();
	void InitSegGridContent();
	void InitCapGridSize();

	void InitCapGridColHead();

	void InitCapGridRowHead();
	void InitCapGridContent();
	void UpdateSegData(int autoCheck);
	void UpdateCapData(int autoCheck);
	//CString dataFilePath;

	int TOP_MARGIN, LEFT_MARGIN;
	int segWidth, segHeight;
	int capWidth, capHeight;
	int disWidth, disHeight;
	int GAP_WIDTH, GAP_HEIGHT;


	int SEG_ROW_COUNT;
	int SEG_COL_COUNT;
	int SEG_ROW_HEIGHT;
	int SEG_COL_WIDTH;

	int CAP_ROW_COUNT;
	int CAP_COL_COUNT;
	int CAP_ROW_HEIGHT;
	int CAP_COL_WIDTH;

	int groupNumPerCol;
	int colShowNum;
	int numPerGroup;
	int subGroupBatNum;
	int batCount;
	//CStatic segStatic;
	//CStatic capStatic;
	//CStatic disStatic;

	TestInfo testInfo;
	vector<WorkProcInfo> workProcInfos;
	vector<CPartBattery *> endDisBatterys;




	afx_msg void OnBnClickedDisStatic();
	void InitCapChart();
	
	
	CBat_chart disChart;
	// 分容直方图
	int distributeVals[MAX_FLAG_NUM];
	double valideBatCount;
	void CreateDistribData();
	void SetCapChartPos();
	void DrawDistribChart();
	void UpdateChartData();
};
