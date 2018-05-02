// CurveDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "CurveDlg.h"
#include "afxdialogex.h"
#include "CSeries.h"
#include "CLegend.h"
#include "CAxis.h"
#include "CAxes.h"
#include "WorkStateStr.h"

#include <vector>
#include <iostream>
#include <iterator>
using namespace std;

// CCurveDlg 对话框

IMPLEMENT_DYNAMIC(CCurveDlg, CDialog)

CCurveDlg::CCurveDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCurveDlg::IDD, pParent)
{

}
CCurveDlg::CCurveDlg(CWnd* pParent, CFileCabData fileCabData)
{
	this->fileCabData = fileCabData;
	multiSel = FALSE;
}
CCurveDlg::~CCurveDlg()
{
}

void CCurveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STEP_COMBO, stepCom);
	DDX_Control(pDX, IDC_BATID_COMBO, batIdCom);
	DDX_Control(pDX, IDC_DATETIME_COMBO, dateTimeCom);
	DDX_Control(pDX, IDC_BAT_TCHART, batChart);
	DDX_Control(pDX, IDC_WORK_DES_EDIT, workDesEdit);
}


BEGIN_MESSAGE_MAP(CCurveDlg, CDialog)
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_STEP_COMBO, &CCurveDlg::OnCbnSelchangeStepCombo)
	ON_CBN_SELCHANGE(IDC_BATID_COMBO, &CCurveDlg::OnCbnSelchangeBatidCombo)
	ON_CBN_SELCHANGE(IDC_DATETIME_COMBO, &CCurveDlg::OnCbnSelchangeDatetimeCombo)
END_MESSAGE_MAP()


// CCurveDlg 消息处理程序


void CCurveDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (this->m_hWnd) {
		CRect rect(0, 0, cx, cy);

		this->MoveWindow(rect.left + MARGIN_LEFT_BATPANE, rect.top + MARGIN_TOP_BATPANE - 28, rect.Width(), rect.Height(), TRUE);
		if (batChart.m_hWnd)
		{
			CRect batRect,editRect;
			batRect.left = rect.left + LEFT_ASSEMBLE_GAP;
			batRect.top = rect.top + MARGIN_TOP_BATPANE;
			batRect.right = rect.Width() - RIGHT_ASSEMBLE_GAP;
			batRect.bottom = rect.Height() - BOTTOM_ASSEMBLE_GAP;

			editRect.left = rect.left  + LEFT_ASSEMBLE_GAP;
			editRect.top = rect.top + MARGIN_TOP_BATPANE + TOP_ASSEMBLE_GAP + rect.Height() / 2;
			editRect.right = rect.Width() - RIGHT_ASSEMBLE_GAP;
			editRect.bottom = rect.Height() - BOTTOM_ASSEMBLE_GAP;

			if (multiSel)
			{
				workDesEdit.ShowWindow(TRUE);
				batRect.bottom = rect.top + MARGIN_TOP_BATPANE + rect.Height() / 2;

				batChart.MoveWindow(batRect);
				workDesEdit.MoveWindow(editRect);
			}
			else
			{
				batRect.bottom = rect.Height() - BOTTOM_ASSEMBLE_GAP;
				workDesEdit.ShowWindow(FALSE);
				batChart.MoveWindow(batRect);
			}
		}
	}
	// TODO:  在此处添加消息处理程序代码
}

void CCurveDlg::ChangeChartPosByCheck(int check)
{
	CRect rect, batRect, editRect;
	this->GetClientRect(rect);

	if (batChart.m_hWnd)
	{
		CRect batRect, editRect;
		batRect.left = rect.left + LEFT_ASSEMBLE_GAP;
		batRect.top = rect.top + MARGIN_TOP_BATPANE;
		batRect.right = rect.Width() - RIGHT_ASSEMBLE_GAP;
		batRect.bottom = rect.Height() - BOTTOM_ASSEMBLE_GAP;

		editRect.left = rect.left + LEFT_ASSEMBLE_GAP;
		editRect.top = rect.top + MARGIN_TOP_BATPANE + TOP_ASSEMBLE_GAP + rect.Height() / 2;
		editRect.right = rect.Width() - RIGHT_ASSEMBLE_GAP;
		editRect.bottom = rect.Height() - BOTTOM_ASSEMBLE_GAP;

		if (check)
		{
			workDesEdit.ShowWindow(TRUE);
			batRect.bottom = rect.top + MARGIN_TOP_BATPANE + rect.Height() / 2;

			batChart.MoveWindow(batRect);
			InitBatWorkRecord();
			workDesEdit.MoveWindow(editRect);

		}
		else
		{
			batRect.bottom = rect.Height() - BOTTOM_ASSEMBLE_GAP;
			workDesEdit.ShowWindow(FALSE);
			batChart.MoveWindow(batRect);
		}
	}
}


BOOL CCurveDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitCombox();
	InitBatChart(0, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CCurveDlg::InitCombox()
{
	vector<WorkProcInfo> workProcInfos = fileCabData.workProcInfos;
	stepCom.AddString(L"0 全部工步");
	int length = (workProcInfos[workProcInfos.size()-1]).workStepName == "结束" ? workProcInfos.size()-1 : workProcInfos.size();
	CString str, str2, str3, batIdStr;

	for (int idx = 0; idx < length; ++idx)
	{
		str.Format(_T("%d"), idx + 1);
		stepCom.AddString(str + L" " + workProcInfos[idx].workStepName.c_str());
	}
	str = (fileCabData.testInfo.startTime).c_str();
	dateTimeCom.AddString(str);

	int groupCount = fileCabData.groupNumPerCol * fileCabData.colShowNum;
	int groupCount2 = (fileCabData.numPerGroup + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
	int seqId = 1;


	for (int groupIdx = 1; groupIdx <= groupCount; ++groupIdx)
	{
		str.Format(_T("%d"), groupIdx);
		str = groupIdx < 10 ? L"0" + str : str;

		for (int groupIdx2 = 1; groupIdx2 <= groupCount2; ++groupIdx2)
		{
			str2.Format(_T("%d"), groupIdx2);

			for (int groupIdx3 = 1; groupIdx3 <= fileCabData.subGroupBatNum; ++groupIdx3)
			{
				str3.Format(_T("%d"), groupIdx3);

				batIdStr.Format(_T("%d"), seqId++);

				batIdCom.AddString(str + L"-" + str2 + L"-" + str3 + L" : [" + batIdStr + L"]");
			}
		}
	}
	stepCom.SetCurSel(0);
	batIdCom.SetCurSel(0);
	dateTimeCom.SetCurSel(0);
}

void CCurveDlg::InitBatChart(int batId, int stepId)
{
	COleSafeArray timeValues;
	COleSafeArray voltValues;
	COleSafeArray currentValues;
	vector<CDbattery> nonCycleRecord, cycleRecord, preCycleRecord, afterCycleRecord;

	const int nDATALENGTH = 100000;
	double dData[nDATALENGTH];
	long idx, jdx;

	DWORD numElements[] = { nDATALENGTH };

	timeValues.Create(VT_R8, 1, numElements);
	voltValues.Create(VT_R8, 1, numElements);
	currentValues.Create(VT_R8, 1, numElements);

	CDbUtils * dbUtils = CDbUtils::GetInstance();

	nonCycleRecord = dbUtils->GetNoneCycleBatData(fileCabData.filePath, batId, stepId);
	cycleRecord = dbUtils->GetCycleBatData(fileCabData.filePath, batId, stepId);

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
	int minCurrent = 10000;			//	最小电流

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

		curIdx++;
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

		//leftAix.put_Minmum(0, maxVolt);
		//leftAix.put_Maximum(maxVolt);
		leftAix.SetMinMax(0, maxVolt);
		//rightAix.put_Minimum(0 - maxCurrent);
		//rightAix.put_Maximum(maxCurrent);
		rightAix.SetMinMax(0-maxCurrent, maxCurrent);

		leftAix.AdjustMaxMin();

		voltSeries.AddArray(recordLength, voltValues, timeValues);
		currentSeries.AddArray(recordLength, currentValues, timeValues);

		

	}
	CLegend legend = (CLegend)batChart.get_Legend();

	legend.put_ShadowSize(0);
	batChart.UpdateWindow();
}

void CCurveDlg::InitBatChart2(int batId, int stepId)
{
	COleSafeArray timeValues;
	COleSafeArray voltValues;
	COleSafeArray currentValues;
	vector<CDbattery> nonCycleRecord, cycleRecord, afterCycleRecord;

	const int nDATALENGTH = 100000;
	double dData[nDATALENGTH];
	long idx, jdx;

	DWORD numElements[] = { nDATALENGTH };

	timeValues.Create(VT_R8, 1, numElements);
	voltValues.Create(VT_R8, 1, numElements);
	currentValues.Create(VT_R8, 1, numElements);

	CDbUtils * dbUtils = CDbUtils::GetInstance();

	nonCycleRecord = dbUtils->GetNoneCycleBatData(fileCabData.filePath, batId, stepId);

	int noneSize = nonCycleRecord.size();

	int noneMaxId = noneSize <= 0 ? 0 : nonCycleRecord[noneSize - 1].id;
	int cycleSize = cycleRecord.size();

	long curIdx = 0;

	int recordLength = nonCycleRecord.size();
	double dval;

	int maxVolt = 0;				//	最大电压
	int maxCurrent = 0;				//	最大电流
	int minCurrent = 5000;			//	最小电流

	for (idx = 0; idx < nonCycleRecord.size(); ++idx)
	{
		double a = nonCycleRecord[idx].atime;
		double b = nonCycleRecord[idx].voltage;
		double c = nonCycleRecord[idx].curnt;

		int currentStepId = nonCycleRecord[idx].stepId;

		timeValues.PutElement(&curIdx, &(a));
		voltValues.PutElement(&curIdx, &(b));
		currentValues.PutElement(&curIdx, &(c));

		maxVolt = b > maxVolt ? b : maxVolt;
		maxCurrent = c > maxCurrent ? c : maxCurrent;
		minCurrent = c < minCurrent ? c : minCurrent;

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
		
		//leftAix.put_Minmum(0, maxVolt);
		//leftAix.put_Maximum(maxVolt);
		leftAix.SetMinMax(0, maxVolt);
		//rightAix.put_Minimum(0 - maxCurrent);
		//rightAix.put_Maximum(maxCurrent);
		rightAix.SetMinMax(0 - maxCurrent, maxCurrent);
		
		leftAix.AdjustMaxMin();

		voltSeries.AddArray(recordLength, voltValues, timeValues);
		currentSeries.AddArray(recordLength, currentValues, timeValues);

	}
	CLegend legend = (CLegend)batChart.get_Legend();

	legend.put_ShadowSize(0);
	
	batChart.UpdateWindow();
}

void CCurveDlg::OnCbnSelchangeStepCombo()
{
	int batId = batIdCom.GetCurSel() + 1;
	int stepId = stepCom.GetCurSel();
	if (stepId == 0)
	{
		InitBatChart(batId, stepId);
	}
	else
	{
		InitBatChart2(batId, stepId);
	}
	
}


void CCurveDlg::OnCbnSelchangeBatidCombo()
{
	int batId = batIdCom.GetCurSel() + 1;
	int stepId = stepCom.GetCurSel();

	// 根据DataCheck选中与否进行数据显示
	CMDIFrameWnd* hMainFrame = (CMDIFrameWnd*)AfxGetMainWnd();
	CMDIChildWnd *hChild = (CMDIChildWnd *)hMainFrame->MDIGetActive();
	CView *hView = (CView *)hChild->GetActiveView();
	if (hView->IsKindOf(RUNTIME_CLASS(CDataFileView)))
	{
		HWND hWnd = hView->m_hWnd;
		// 向父窗口发送消息  
		if (hWnd == NULL) return (void)MessageBox(_T("获得父窗口句柄失败！"));
		
		CDataFileView *dataFileView = (CDataFileView*)hView;		
		if (dataFileView->dlgArray[SLOOP_MENU_DLG_ID] && 
			dataFileView->dlgArray[SLOOP_MENU_DLG_ID]->m_hWnd)
		{
			CSloopMenuDlg *sloopMenuDlg = (CSloopMenuDlg*)dataFileView->dlgArray[SLOOP_MENU_DLG_ID];
			int id = this->batIdCom.GetCurSel();
			sloopMenuDlg->OnBnClickedDataChk();
		}
	}

	if (stepId == 0)
	{
		InitBatChart(batId, stepId);
	}
	else
	{
		InitBatChart2(batId, stepId);
	}

}


void CCurveDlg::OnCbnSelchangeDatetimeCombo()
{
	// TODO:  在此添加控件通知处理程序代码
}

/*
	根据batId生成相关数据
*/
void CCurveDlg::InitBatWorkRecord()
{
	int batId = batIdCom.GetCurSel() + 1;
	CDbUtils *dbUtils = CDbUtils::GetInstance();
	CString batIdStr, str, str2, tmpStr;
	
	int groupCount = fileCabData.groupNumPerCol * fileCabData.colShowNum;
	int groupCount2 = (fileCabData.numPerGroup + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
	
	int a = (batId + fileCabData.numPerGroup - 1) / fileCabData.numPerGroup;
	int b = (batId % fileCabData.numPerGroup + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
	int c = (batId % fileCabData.numPerGroup) % fileCabData.subGroupBatNum;
	
	CString astr, bstr, cstr;
	astr.Format(_T("%d"), a); astr = a < 10 ? L"0" + astr : astr;
	bstr.Format(_T("%d"), b);
	cstr.Format(_T("%d"), c);
	batIdStr.Format(_T("%d"), batId); batIdStr = L"[" + batIdStr + L"]";

	batIdStr = astr + L"-" + bstr + L"-" + cstr + L" " + batIdStr;

	CString batWorkDesStr = L"电芯编号: " + batIdStr + L"\r\n";
	vector<WorkProcInfo> workProcInfos = fileCabData.workProcInfos;
	int workStepLength = workProcInfos.size();

	workStepLength = workStepLength > 0 ?
		(fileCabData.workProcInfos[workStepLength - 1].workStepName == END_STR ? workStepLength - 1 : workStepLength) : 0;

	vector<CDbattery> batteryRecords = dbUtils->GetBatDataById(fileCabData.filePath, batId);
	//(5) 获取工序信息

	str = fileCabData.testInfo.workName.c_str();
	str2 = fileCabData.testInfo.deviceName.c_str();

	vector<CString> workDescs;
	workDescs.push_back(L"工序名称：" + str + L"    型号：" + str2 + L"\r\n\r\n");
	int preDescId = 1;

	int stepNum = fileCabData.workProcInfos.size();
	stepNum = fileCabData.workProcInfos[stepNum - 1].workStepName == END_STR ? stepNum - 1 : stepNum;
	vector<WorkProcInfo>workProInfos = fileCabData.workProcInfos;
	CString voltStr, currentStr, timeStr, capicityStr, energyStr;

	int preStepIdx = -1;
	//BOOL tailNullFlag = FALSE;
	CString stepName;
		for (int idx = 0; idx < stepNum; ++idx)
		{
			int jdx;
			//tailNullFlag = FALSE;
			// 获取工步信息
			
			stepName = workProInfos[idx].workStepName.c_str();
			int stepId = workProInfos[idx].stepId;

			str.Format(_T("%d"), idx + 1);

			workDescs.push_back(L"工步" + str + L"    工步状态：");

			if (stepName == CACV_WORKNAME_CSTR || stepName == CA_WORKNAME_CSTR || stepName == CADIS_WORKNAME_CSTR || stepName == CADIS_WORKNAME_CSTR)
			{
				for (jdx = preStepIdx + 1; jdx < batteryRecords.size() && batteryRecords[jdx].stepId == stepId; ++jdx)
				{
					str.Format(_T("%-4d"), jdx + 1);
					voltStr.Format(_T("%-6d"), (int)batteryRecords[jdx].voltage);
					currentStr.Format(_T("%-6d"), (int)batteryRecords[jdx].curnt);
					timeStr.Format(_T("%-6d"), (int)batteryRecords[jdx].atime);
					capicityStr.Format(_T("%-6d"), (int)batteryRecords[jdx].capacity);
					energyStr.Format(_T("%-6d"), (int)batteryRecords[jdx].energy);

					workDescs.push_back(L"序号" + str + L"    电压：" + voltStr + L" , 电流：" + currentStr + L" , 时间："
						+ timeStr + L" , 容量：" + capicityStr + " , 电量：" + energyStr + L"\r\n");
				}
				//workDescs[workDescs.size() - 1] += L"\r\n";

				if (jdx > preStepIdx + 1)
				{
					workDescs[workDescs.size() - 1] += L"\r\n";
					int stateIdx = batteryRecords[jdx - 1].batState;
					if (stateIdx < 0) break;
					str = BATSTATE_CSTR[stateIdx];
					if (idx == 0)
					{
						if (preDescId < workDescs.size())
							workDescs[preDescId] += str + L"\r\n\r\n";
					}
					else
					{
						if (preDescId + 1 < workDescs.size())
							workDescs[preDescId + 1] += str + L"\r\n\r\n";
					}

					preDescId = jdx + idx + 1;

					preStepIdx = jdx - 1;
				}
				else
				{
					str = L"无数据";
					if (preDescId + 1 < workDescs.size())
						workDescs[++preDescId] += str + L"\r\n\r\n";
				}
			}
			else if (stepName == L"循环")
			{

			}
		}

		for (int idx = 0; idx < workDescs.size(); ++idx)
		{
			batWorkDesStr += workDescs[idx];
		}
		workDesEdit.SetWindowTextW(batWorkDesStr);
}
