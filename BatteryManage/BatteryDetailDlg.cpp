#include "stdafx.h"

#include "BatteryManage.h"
#include "BatteryDetailDlg.h"
#include "afxdialogex.h"




// CBatteryDetailDlg 对话框

IMPLEMENT_DYNAMIC(CBatteryDetailDlg, CDialog)

CBatteryDetailDlg::CBatteryDetailDlg(CWnd* pParent /*=NULL*/)
: CDialog(CBatteryDetailDlg::IDD, pParent)
{
	curveDataDlg = NULL;
	batWorkDetailDlg = NULL;
}

CBatteryDetailDlg::~CBatteryDetailDlg()
{
	if (curveDataDlg)
	{
		curveDataDlg->DestroyWindow();
		delete curveDataDlg;
		curveDataDlg = NULL;
	}

	if (batWorkDetailDlg)
	{
		batWorkDetailDlg->DestroyWindow();
		delete batWorkDetailDlg;
		batWorkDetailDlg = NULL;
	}
}

void CBatteryDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BAT_ID_COM, batteryIdCom);
	DDX_Control(pDX, IDC_BAT_ID, batIdStatic);
	DDX_Control(pDX, IDC_BAT_CHART, batChart);
	DDX_Control(pDX, IDC_VCHECK, vcheck);
	DDX_Control(pDX, IDC_ACHECK, acheck);
}


BEGIN_MESSAGE_MAP(CBatteryDetailDlg, CDialog)
	ON_STN_CLICKED(IDC_DETAIL_PIC, &CBatteryDetailDlg::OnStnClickedDetailPic)
	ON_BN_CLICKED(IDC_ID_DESC, &CBatteryDetailDlg::OnBnClickedIdDesc)
	ON_BN_CLICKED(IDC_ID_ASC, &CBatteryDetailDlg::OnBnClickedIdAsc)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_VCHECK, &CBatteryDetailDlg::OnBnClickedVcheck)
	ON_BN_CLICKED(IDC_ACHECK, &CBatteryDetailDlg::OnBnClickedAcheck)
	ON_BN_CLICKED(IDC_DETAIL_BTN, &CBatteryDetailDlg::OnBnClickedDetailBtn)
END_MESSAGE_MAP()


// CBatteryDetailDlg 消息处理程序


void CBatteryDetailDlg::OnStnClickedDetailPic()
{

	if (curveDataDlg == NULL)
	{
		curveDataDlg = new CCurveDataDlg();
	}
	curveDataDlg->DoModal();
	// TODO:  在此添加控件通知处理程序代码
}


BOOL CBatteryDetailDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	curCabInfo = cabInfos[curCabId - 1];
	InitBatteryIdCom();
	DrawBatDetailInfo();
	
	SetTimer(1, 5000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CBatteryDetailDlg::InitBatteryIdCom()
{
	batteryIdCom.Clear();
	curCabInfo = cabInfos[curCabId - 1];
	CString batteryIdStr;
	CString rowIdStr, groupIdStr, groupInnerIdStr;

	for (int rowIdx = 0; rowIdx < curCabInfo.groupNumPerCol * curCabInfo.colShowNum; ++rowIdx)
	{
		for (int groupIdx = 0; groupIdx < (curCabInfo.numPerGroup + SUBGROUP_NUM - 1) / SUBGROUP_NUM; ++ groupIdx)
		{
			for (int groupInnerIdx = 0; groupInnerIdx < SUBGROUP_NUM; ++groupInnerIdx)
			{
				rowIdStr.Format(_T("%d"), rowIdx + 1);
				groupIdStr.Format(_T("%d"), groupIdx + 1);
				groupInnerIdStr.Format(_T("%d"), groupInnerIdx + 1);
				batteryIdCom.AddString(rowIdStr + _T("-") + groupIdStr + _T("-") + groupInnerIdStr);
			}
		}
	}
	cabIdCount = batteryIdCom.GetCount();
	if (cabIdCount > 0)
	{
		batteryIdCom.SetCurSel(curBatteryId-1);
	}
	
}

void CBatteryDetailDlg::OnBnClickedIdDesc()
{
	// TODO:  在此添加控件通知处理程序代码
	int curBatteryIdx = batteryIdCom.GetCurSel();

	if (curBatteryIdx  > 0)
	{
		batteryIdCom.SetCurSel(curBatteryIdx - 1);
		DrawBatDetailInfo();
	}
}


void CBatteryDetailDlg::OnBnClickedIdAsc()
{
	int curBatteryIdx = batteryIdCom.GetCurSel();

	if (curBatteryIdx + 1 < cabIdCount)
	{
		batteryIdCom.SetCurSel(curBatteryIdx + 1);
		DrawBatDetailInfo();
	}
}


void CBatteryDetailDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	switch (nIDEvent)
	{
	case 1:
	{
			  DrawBatDetailInfo();
			  break;
	}
	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);
}


void CBatteryDetailDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting


}

void CBatteryDetailDlg::DrawBatDetailInfo()
{
	COleSafeArray timeValues;
	COleSafeArray voltValues;
	COleSafeArray currentValues;


	const int nDATALENGTH = 100000;
	double dData[nDATALENGTH];
	long idx, jdx;

	DWORD numElements[] = { nDATALENGTH };

	timeValues.Create(VT_R8, 1, numElements);
	voltValues.Create(VT_R8, 1, numElements);
	currentValues.Create(VT_R8, 1, numElements);

	CDbUtils * dbUtils = CDbUtils::GetInstance();
	
	nonCycleRecord.clear();
	cycleRecord.clear();
	preCycleRecord.clear();
	afterCycleRecord.clear();
	
	curBatteryId = batteryIdCom.GetCurSel() + 1;
	
	nonCycleRecord = dbUtils->GetNoneCycleBatData(curCabId, curBatteryId);
	cycleRecord = dbUtils->GetCycleBatData(curCabId, curBatteryId);
	
	int noneSize = nonCycleRecord.size();

	int noneMaxId = noneSize <= 0 ? 0 : nonCycleRecord[noneSize - 1].id;
	int cycleSize = cycleRecord.size();

	if (cycleRecord.size() == 0)
	{
		if (nonCycleRecord.size() > 0)
			preCycleRecord = nonCycleRecord;
	}
	else
	{
		int cycleMinId = 0;
		cycleMinId = cycleSize > 0 ? cycleRecord[0].id : 0;

		if (cycleMinId == 0)
		{
			preCycleRecord = nonCycleRecord;
		}
		else
		{
			if (cycleMinId > noneMaxId)
			{
				preCycleRecord = nonCycleRecord;
			}
			else if (cycleMinId < noneMaxId)
			{
				for (idx = 0; idx < cycleMinId; ++idx)
				{
					preCycleRecord.push_back(nonCycleRecord[idx]);
				}
				for (idx = cycleMinId; idx < nonCycleRecord.size(); ++idx)
				{
					afterCycleRecord.push_back(nonCycleRecord[idx]);
				}
			}
		}
	}

	int preStepId = 1;
	int preCycleId = 0;				//上一次循环的ID
	double preTime = 0;
	long preIdx = 0;
	long curIdx = 0;

	int preSize = preCycleRecord.size();
	int afterSize = afterCycleRecord.size();

	int recordLength = nonCycleRecord.size() + cycleRecord.size();
	double dval;

	int maxVolt = 0;				//	最大电压
	int maxCurrent = 0;				//	最大电流
	int minCurrent = 5000;			//	最小电流

	for (idx = 0; idx < preCycleRecord.size(); ++idx)
	{
		double a = preCycleRecord[idx].atime;
		double b = preCycleRecord[idx].voltage;
		double c = preCycleRecord[idx].curnt;

		preCycleId = preCycleRecord[idx].cycleId;

		int currentStepId = preCycleRecord[idx].stepId;

		if (currentStepId != preStepId)
		{
			preIdx = curIdx - 1;
			preStepId = currentStepId;

			timeValues.GetElement(&preIdx, &preTime);
		}
		a += preTime;
		timeValues.PutElement(&curIdx, &(a));
		voltValues.PutElement(&curIdx, &(b));
		currentValues.PutElement(&curIdx, &(c));

		maxVolt = b > maxVolt ? b : maxVolt;
		maxCurrent = c > maxCurrent ? c : maxCurrent;
		minCurrent = c < minCurrent ? c : minCurrent;

		curIdx ++;
	}
/*
	这个有点难，做下记录
*/
	for (idx = 0; idx < cycleRecord.size(); ++idx)
	{
		double a = cycleRecord[idx].atime;
		double b = cycleRecord[idx].voltage;
		double c = cycleRecord[idx].curnt;

		int curCycleId = cycleRecord[idx].cycleId;
		

		int currentStepId = cycleRecord[idx].stepId;

		if (currentStepId != preStepId || curCycleId != preCycleId)
		{
			preIdx = curIdx - 1;
			preStepId = currentStepId;
			timeValues.GetElement(&preIdx, &preTime);
		}
		a += preTime;
		timeValues.PutElement(&curIdx, &(a));
		voltValues.PutElement(&curIdx, &(b));
		currentValues.PutElement(&curIdx, &(c));

		maxVolt = b > maxVolt ? b : maxVolt;
		maxCurrent = c > maxCurrent ? c : maxCurrent;
		minCurrent = c < minCurrent ? c : minCurrent;

		preCycleId = cycleRecord[idx].cycleId;
		curIdx++;
	}
	

	for (idx = 0; idx < afterCycleRecord.size(); ++idx)
	{
		double a = afterCycleRecord[idx].atime;
		double b = afterCycleRecord[idx].voltage;
		double c = afterCycleRecord[idx].curnt;

		int currentStepId = afterCycleRecord[idx].stepId;

		if (currentStepId != preStepId)
		{
			preIdx = curIdx - 1;
			preStepId = currentStepId;

			timeValues.GetElement(&preIdx, &preTime);
		}
		a += preTime;
		timeValues.PutElement(&curIdx, &(a));
		voltValues.PutElement(&curIdx, &(b));
		currentValues.PutElement(&curIdx, &(c));

		maxVolt = b > maxVolt ? b : maxVolt;
		maxCurrent = c > maxCurrent ? c : maxCurrent;
		minCurrent = c < minCurrent ? c : minCurrent;

		curIdx++;
	}


	CSeries voltSeries = (CSeries)batChart.Series(0);
	CSeries currentSeries = (CSeries)batChart.Series(1);


	voltSeries.Clear();
	currentSeries.Clear();

	voltSeries.put_Title(L"电压");
	currentSeries.put_Title(L"电流");

	if (recordLength > 0)
	{


		CAxis leftAix = ((CAxes)batChart.get_Axis()).get_Left();
		CAxis rightAix = ((CAxes)batChart.get_Axis()).get_Right();


		maxVolt = ((int)(maxVolt / 500) + 1) * 500 + 200;
		//maxCurrent = ((int)(maxCurrent / 400 + 1)) * 400 + 200;
		maxCurrent = abs(maxCurrent) > abs(minCurrent) ? abs(maxCurrent) : abs(minCurrent);

		maxCurrent = ((int)(maxCurrent / 400 + 1)) * 400 + 200;
		
		//leftAix.put_Minimum(0);
		//leftAix.put_Maximum(maxVolt);
		//
		//rightAix.put_Minimum(0 - maxCurrent);
		//rightAix.put_Maximum(maxCurrent);
		leftAix.SetMinMax(0, maxVolt);
		rightAix.SetMinMax(0 - maxCurrent, maxCurrent);
		
		voltSeries.AddArray(recordLength, voltValues, timeValues);
		currentSeries.AddArray(recordLength, currentValues, timeValues);

	}
	CLegend legend = (CLegend)batChart.get_Legend();

	legend.put_ShadowSize(0);

	batChart.UpdateWindow();
	//legend.put_Visible(FALSE);
}



BEGIN_EVENTSINK_MAP(CBatteryDetailDlg, CDialog)
	ON_EVENT(CBatteryDetailDlg, IDC_BAT_CHART, 7, CBatteryDetailDlg::OnClickSeriesBatChart, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4)
END_EVENTSINK_MAP()


void CBatteryDetailDlg::OnClickSeriesBatChart(long SeriesIndex, long ValueIndex, long Button, long Shift, long X, long Y)
{
	// TODO:  在此处添加消息处理程序代码
	
	CSeries series = ((CSeries)batChart.Series(SeriesIndex));

	CMarks marks = (CMarks)(series.get_Marks());

	if (marks.get_Visible())
	{
		marks.put_Visible(FALSE);
	}
	else
	{
		marks.put_Visible(TRUE);
	}
}


void CBatteryDetailDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CLegend legend = (CLegend)batChart.get_Legend();
	int leftPos = legend.get_Left();
	int topPos = legend.get_Top();
	int width = legend.get_ColumnWidths(0);
	LPDISPATCH frame = legend.get_Frame();


	CDialog::OnLButtonDown(nFlags, point);
}


void CBatteryDetailDlg::OnBnClickedVcheck()
{
	CSeries series = ((CSeries)batChart.Series(0));

	CMarks marks = (CMarks)(series.get_Marks());

	if (this->vcheck.GetCheck())
	{
		marks.put_Visible(TRUE);
	}
	else
	{
		marks.put_Visible(FALSE);
	}
}


void CBatteryDetailDlg::OnBnClickedAcheck()
{
	CSeries series = ((CSeries)batChart.Series(1));

	CMarks marks = (CMarks)(series.get_Marks());

	if (this->acheck.GetCheck())
	{
		marks.put_Visible(TRUE);
	}
	else
	{
		marks.put_Visible(FALSE);
	}
}


void CBatteryDetailDlg::OnBnClickedDetailBtn()
{
	if (batWorkDetailDlg == NULL || !(batWorkDetailDlg->m_hWnd)) {
		batWorkDetailDlg = new CBatWorkDetailDlg();
		batWorkDetailDlg->DoModal();
	}
}
