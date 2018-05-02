#pragma once
#include "BatWorkDetailDlg.h"
#include "CurveDataDlg.h"
#include "afxwin.h"
#include "Dbatterys.h"


#include "CTChart.h"
#include "CSeries.h"
#include "CLegend.h"
#include "CAxes.h"
#include "CAxis.h"
#include "CMarks.h"
#include "bat_chart.h"


// CBatteryDetailDlg �Ի���

class CBatteryDetailDlg : public CDialog
{
	DECLARE_DYNAMIC(CBatteryDetailDlg)

public:
	CBatteryDetailDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBatteryDetailDlg();

	// �Ի�������
	enum { IDD = IDD_BATTERY_DETAIL_DLG };

	//  ������ϸ����
	CCurveDataDlg *curveDataDlg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedDetailPic();
	virtual BOOL OnInitDialog();

	void DrawBatDetailInfo();
	
	CComboBox batteryIdCom;
	CabinetInfo curCabInfo;
	int cabIdCount;
	void InitBatteryIdCom();

	afx_msg void OnBnClickedIdDesc();
	afx_msg void OnBnClickedIdAsc();
	CStatic batIdStatic;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();

	vector<CDbattery> nonCycleRecord;
	vector<CDbattery> cycleRecord;
	vector<CDbattery> preCycleRecord;
	vector<CDbattery> afterCycleRecord;


	CBat_chart batChart;

	DECLARE_EVENTSINK_MAP()
	void OnClickSeriesBatChart(long SeriesIndex, long ValueIndex, long Button, long Shift, long X, long Y);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CButton vcheck;
	CButton acheck;
	afx_msg void OnBnClickedVcheck();
	afx_msg void OnBnClickedAcheck();
	afx_msg void OnBnClickedDetailBtn();

public:
	CBatWorkDetailDlg *batWorkDetailDlg;
};
