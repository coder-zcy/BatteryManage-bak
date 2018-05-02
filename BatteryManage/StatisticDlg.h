#pragma once
#include "afxwin.h"
#include "GridCtrl_src\GridCtrl.h"
#include "GridUtils.h"
#include "TestInfo.h"
#include "bat_chart.h"
#include "CapShowType.h"



//Ĭ�Ϸ��������С
const int DEF_PART_CNT = 8;
const int PART_CNT = 16;

#define MAX_FLAG_NUM 16

// CStatisticDlg �Ի���

class CStatisticDlg : public CDialog
{
	DECLARE_DYNAMIC(CStatisticDlg)

public:
	CStatisticDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CStatisticDlg(CWnd* pParent, CFileCabData fileCabData);

	virtual ~CStatisticDlg();

// �Ի�������
	enum { IDD = IDD_STATISTIC_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	// ����ֱ��ͼ
	int distributeVals[MAX_FLAG_NUM];
	double valideBatCount;
	void CreateDistribData();
	void SetCapChartPos();
	void DrawDistribChart();
	void UpdateChartData();
};
