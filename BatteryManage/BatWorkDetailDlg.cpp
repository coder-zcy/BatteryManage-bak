// BatWorkDetailDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "BatWorkDetailDlg.h"
#include "PartBattery.h"
#include "afxdialogex.h"
#include "WorkStateStr.h"


// CBatWorkDetailDlg �Ի���

IMPLEMENT_DYNAMIC(CBatWorkDetailDlg, CDialog)

CBatWorkDetailDlg::CBatWorkDetailDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBatWorkDetailDlg::IDD, pParent)
{

}

CBatWorkDetailDlg::CBatWorkDetailDlg(CWnd* pParent /*=NULL*/, CFileCabData fileCabData, int windowFlag)
: CDialog(CBatWorkDetailDlg::IDD, pParent)
{
	this->fileCabData = fileCabData;
	this->windowFlag = windowFlag;
}

CBatWorkDetailDlg::~CBatWorkDetailDlg()
{
}

void CBatWorkDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WORK_DETAIL_EDIT, workDetailEdit);
}


BEGIN_MESSAGE_MAP(CBatWorkDetailDlg, CDialog)
END_MESSAGE_MAP()


// CBatWorkDetailDlg ��Ϣ�������


BOOL CBatWorkDetailDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//if (this->windowFlag == COMP_DLG_ID || this->windowFlag == PART_DLG_ID)
	//{
	//	InitDialogByWorkingInfo();
	//}
	//else 
	if (this->windowFlag == STATISTIC_DLG_ID || this->windowFlag == COMP_DLG_ID || this->windowFlag == PART_DLG_ID )
	{
		InitDialogByDataFile();
	}
	else if (this->windowFlag == CURVE_DLG_ID)
	{
		InitDialogBySingleBat();
	}
	else {}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CBatWorkDetailDlg::InitDialogByWorkingInfo()
{
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CDbUtils *dbUtils = CDbUtils::GetInstance();
	//(1) ��ȡ������
	int cabId = curCabId;
	//(2) ��ȡ��ر��
	int batId = curBatteryId;
	//(3) ��ȡ���ݿ���
	CString dbPath = cabDbPaths[cabId - 1];
	//(4) �����ݿ��в�ѯ�ÿ��صĵ�ع�����ɹ����еĽ��
	vector<CDbattery> batteryRecords = dbUtils->GetBatDataById(dbPath, batId);
	//(5) ��ȡ������Ϣ
	/*CWorkProc* workProc = theApp.startWorkDlg->workProcs[cabId - 1];*/
	CWorkProc* workProc = workProcs[cabId - 1];
	//(6) ���ݹ�����Ϣ�����ӡ���
	if (workProc != NULL)
	{
		vector<CString> workDescs;
		workDescs.push_back(L"�������ƣ�" + workProc->workProcName + L"    �ͺţ�" + workProc->model + L"\r\n\r\n");
		int preDescId = 1;

		int stepNum = workProc->stepNum;
		vector<CWorkStep> workSteps = workProc->workSteps;
		CString voltStr, currentStr, timeStr, capicityStr, energyStr;

		int preStepIdx = -1;
		//BOOL tailNullFlag = FALSE;
		CString str;
		for (int idx = 0; idx < stepNum - 1; ++idx)
		{
			int jdx;
			//tailNullFlag = FALSE;
			// ��ȡ������Ϣ
			CString stepName = workSteps[idx].workStepName;
			int stepId = workSteps[idx].stepId;

			str.Format(_T("%d"), idx + 1);

			workDescs.push_back(L"����" + str + L"    ����״̬��");

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

					workDescs.push_back(L"���" + str + L"    ��ѹ��" + voltStr + L" , ������" + currentStr + L" , ʱ�䣺"
						+ timeStr + L" , ������" + capicityStr + " , ������" + energyStr + L"\r\n");
				}
				//workDescs[workDescs.size() - 1] += L"\r\n";

				if (jdx > preStepIdx + 1)
				{
					workDescs[workDescs.size() - 1] += L"\r\n";
					str = BATSTATE_CSTR[batteryRecords[jdx - 1].batState];
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
					str = L"������";
					if (preDescId + 1 < workDescs.size())
						workDescs[++preDescId] += str + L"\r\n\r\n";
				}
			}
			else if (stepName == L"ѭ��")
			{

			}
		}

		CString workDescStr = L"";
		for (int idx = 0; idx < workDescs.size(); ++idx)
		{
			workDescStr += workDescs[idx];
		}
		workDetailEdit.SetWindowTextW(workDescStr);
	}
}

void CBatWorkDetailDlg::InitDialogByDataFile()
{
	//// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CDbUtils *dbUtils = CDbUtils::GetInstance();
	vector<WorkProcInfo> workProcInfos = fileCabData.workProcInfos;
	TestInfo testInfo = fileCabData.testInfo;
	CString workDesStr(testInfo.cabinetTag.c_str());

	workDesStr = L"�豸��־: " + workDesStr + L"\r\n\r\n�����趨ֵ:\r\n";
	
	CString str;
	CString astr, uvstr, tstr, ecstr;
	for (int idx = 0; idx < workProcInfos.size(); ++idx)
	{
		str.Format(_T("%d"), idx + 1);
		str += L": ";
		if (workProcInfos[idx].workStepName == CA_WORKNAME_STR)
		{
			astr.Format(_T("%d"),workProcInfos[idx].current);
			tstr.Format(_T("%d"), workProcInfos[idx].workTime);
			uvstr.Format(_T("%d"), workProcInfos[idx].maxVolt);

			str += CA_WORKNAME_CSTR + L"  CI: " + astr + L"  T: " + tstr + L"min  UV: " + uvstr + L"mV\r\n";
		}
		else if (workProcInfos[idx].workStepName == CACV_WORKNAME_STR)
		{
			astr.Format(_T("%d"), workProcInfos[idx].current);
			tstr.Format(_T("%d"), workProcInfos[idx].workTime);
			uvstr.Format(_T("%d"), workProcInfos[idx].maxVolt);
			ecstr.Format(_T("%d"), workProcInfos[idx].endCurrent);

			str += CACV_WORKNAME_CSTR + L"  CI: " + astr + L"  T: " + tstr + L"min  CV: " 
				+ uvstr + L"mV   EC: " + ecstr + L"mA\r\n";
		}
		else if (workProcInfos[idx].workStepName == CADIS_WORKNAME_STR)
		{
			astr.Format(_T("%d"), workProcInfos[idx].current);
			tstr.Format(_T("%d"), workProcInfos[idx].workTime);
			uvstr.Format(_T("%d"), workProcInfos[idx].minVolt);
			
			str += CADIS_WORKNAME_CSTR + L"  CI: " + astr + L"  T: " + tstr + L"min  DV: "
				+ uvstr + L"mV\r\n";
		}
		else if (workProcInfos[idx].workStepName == LAY_WORKNAME_STR)
		{
			tstr.Format(_T("%d"), workProcInfos[idx].workTime);

			str += LAY_WORKNAME_CSTR + L"  T: " + tstr + L"min\r\n";
		}
		else if (workProcInfos[idx].workStepName == END_STR)
		{
			str += END_CSTR + L"\r\n\r\n";
		}
		workDesStr += str;
	}

	str.Format(_T("%d"), testInfo.vdisVal);
	str = L"�ŵ�������:��ѹ(mV) " + str + L"\r\n\r\n";
	workDesStr += str + L"���߲�������:";
	CString adisValStr, vdisValStr, timeValStr;
	str.Format(_T("%d"), testInfo.vdisVal);
	vdisValStr = testInfo.vdis == 1 ? (str + L" mV") : L"";
	workDesStr += vdisValStr;
	
	str.Format(_T("%d"), testInfo.adisVal);
	adisValStr = testInfo.adis == 1 ? (str + L" mA") : L"";
	workDesStr += adisValStr;

	str.Format(_T("%d"), testInfo.timeDisVal);
	timeValStr = testInfo.timeDis == 1 ? (str + L" min") : L"";
	workDesStr += timeValStr + L"\r\n";

	workDesStr += L"������������";

	workDetailEdit.SetWindowTextW(workDesStr);
}

void CBatWorkDetailDlg::InitDialogBySingleBat()
{
	int mappings[MAX_BAT_NUM];
	memcpy(mappings, fileCabData.mappings, sizeof(int)*MAX_BAT_NUM);

	CMDIFrameWnd* hMainFrame = (CMDIFrameWnd*)AfxGetMainWnd();
	CMDIChildWnd *hChild = (CMDIChildWnd *)hMainFrame->MDIGetActive();
	CView *hView = (CView *)hChild->GetActiveView();
	if (hView->IsKindOf(RUNTIME_CLASS(CDataFileView)))
	{
		CDataFileView *dataFileView = (CDataFileView*)hView;

		CCurveDlg * curveDlg = (CCurveDlg*)(dataFileView->dlgArray[CURVE_DLG_ID]);

		if (curveDlg != NULL && curveDlg->m_hWnd)
		{
			int batId = curveDlg->batIdCom.GetCurSel() + 1;

			CString batIdStr, str, tmpStr; 
			curveDlg->batIdCom.GetWindowText(batIdStr);

			CString batWorkDesStr = L"��о���: " + batIdStr + L"\r\n";
			
			if (mappings[batId] >= 0)
			{
				vector<WorkProcInfo> workProcInfos = fileCabData.workProcInfos;
				int workStepLength = workProcInfos.size();

				workStepLength = workStepLength > 0 ?
					(fileCabData.workProcInfos[workStepLength - 1].workStepName == END_STR ? workStepLength - 1 : workStepLength) : 0;

				for (int idx = 0; idx < workStepLength; ++idx)
				{
					str.Format(_T("%d"), idx + 1);
					str += L"  :";
					if (workProcInfos[idx].workStepName == CA_WORKNAME_STR)
					{
						tmpStr.Format(_T("%d"), workProcInfos[idx].workTime);
						str += L"�������    ʱ��:" + tmpStr + L"min    ";
						tmpStr.Format(_T("%d"), workProcInfos[idx].current);
						str += L"����:" + tmpStr + L"mA    ";
						//tmpStr.Format(_T("%d"), fileCabData.endStepInfos[idx][mappings[batId]].capacity);
						tmpStr.Format(_T("%d"), fileCabData.batStepInfos[idx][mappings[batId]].endStepInfo.capacity);
						str += L"����:" + tmpStr + L"mAh    ";
						//tmpStr.Format(_T("%d"), fileCabData.startStepInfos[idx][mappings[batId]].voltage);
						tmpStr.Format(_T("%d"), fileCabData.batStepInfos[idx][mappings[batId]].startStepInfo.voltage);
						str += L"��·��ѹ:" + tmpStr + L"mV    ";
						//tmpStr.Format(_T("%d"), fileCabData.endStepInfos[idx][mappings[batId]].voltage);
						tmpStr.Format(_T("%d"), fileCabData.batStepInfos[idx][mappings[batId]].endStepInfo.voltage);
						str += L"��ֹ��ѹ:" + tmpStr + L"mV";
					}
					else if (workProcInfos[idx].workStepName == CACV_WORKNAME_STR)
					{
						tmpStr.Format(_T("%d"), workProcInfos[idx].workTime);
						str += L"������ѹ���    ʱ��:" + tmpStr + L"min    ";
						tmpStr.Format(_T("%d"), workProcInfos[idx].current);
						str += L"����:" + tmpStr + L"mA    ";
						tmpStr.Format(_T("%d"), fileCabData.batStepInfos[idx][mappings[batId]].endStepInfo.capacity);
						str += L"����:" + tmpStr + L"mAh    ";
						tmpStr.Format(_T("%d"), fileCabData.batStepInfos[idx][mappings[batId]].startStepInfo.voltage);
						str += L"��·��ѹ:" + tmpStr + L"mV    ";
						tmpStr.Format(_T("%d"), fileCabData.batStepInfos[idx][mappings[batId]].endStepInfo.voltage);
						str += L"��ֹ��ѹ:" + tmpStr + L"mV";
					}
					else if (workProcInfos[idx].workStepName == CADIS_WORKNAME_STR)
					{
						tmpStr.Format(_T("%d"), workProcInfos[idx].workTime);
						str += L"�����ŵ�    ʱ��:" + tmpStr + L"min    ";
						tmpStr.Format(_T("%d"), workProcInfos[idx].current);
						str += L"����:" + tmpStr + L"mA    ";
						tmpStr.Format(_T("%d"), fileCabData.batStepInfos[idx][mappings[batId]].endStepInfo.capacity);
						str += L"����:" + tmpStr + L"mAh    ";
						tmpStr.Format(_T("%d"), fileCabData.batStepInfos[idx][mappings[batId]].startStepInfo.voltage);
						str += L"��·��ѹ:" + tmpStr + L"mV    ";
						tmpStr.Format(_T("%d"), fileCabData.batStepInfos[idx][mappings[batId]].endStepInfo.voltage);
						str += L"��ֹ��ѹ:" + tmpStr + L"mV";
					}
					else if (workProcInfos[idx].workStepName == LAY_WORKNAME_STR)
					{
						tmpStr.Format(_T("%d"), workProcInfos[idx].workTime);
						str += L"����    ʱ��:" + tmpStr + L"min    ";
						tmpStr.Format(_T("%d"), fileCabData.batStepInfos[idx][mappings[batId]].startStepInfo.voltage);
						str += L"��·��ѹ:" + tmpStr + L"mV    ";
						tmpStr.Format(_T("%d"), fileCabData.batStepInfos[idx][mappings[batId]].endStepInfo.voltage);
						str += L"��ֹ��ѹ:" + tmpStr + L"mV";
					}
					str += L"\r\n";
					batWorkDesStr += str;
				}
			}
			workDetailEdit.SetWindowTextW(batWorkDesStr);
		}
	}
}
