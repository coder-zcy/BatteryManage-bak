#include "stdafx.h"
#include "PartBattery.h"
#include "Dbatterys.h"
#include "DbUtils.h"


CPartBattery::CPartBattery()
{
	capFlag = 0;
}


CPartBattery::CPartBattery(CString dbFilePath)
{
	capFlag = 0;
	////3.1 ��ȡ������ʼʱ�ĵ�ѹ��������ʱ�䡢��������������Ϣ
	//vector<CDbattery> startStepInfos = CDbUtils::GetStartStepInfos(dataFilePath, stepId);
	////3.2 ��ȡÿ��������ƽ����ѹ�������ȴ������ֵ
	//vector<double> avgVolts = CDbUtils::GetAvgVolt(dataFilePath, stepId);
	////3.3 ��ȡ��������ʱ�ĵ�ѹ��������ʱ�䡢��������������Ϣ
	//vector<CDbattery> endStepInfos = CDbUtils::GetEndStepInfos(dataFilePath, stepId);
}

//CPartBattery::CPartBattery(CBatStepInfo batStepInfo)
//{
//	CString str;
//	capFlag = 0;
//
//	batId = batStepInfo.startStepInfo.batId;
//	
//	str.Format(_T("%d"), int(batStepInfo.endStepInfo.capacity + 0.5));
//	capacity = str;
//
//	str.Format(_T("%d"), int(batStepInfo.endStepInfo.atime + 0.5));
//	atime = str;
//
//	str.Format(_T("%d"), int(batStepInfo.startStepInfo.voltage + 0.5));
//	openVolt = str;
//	
//	str.Format(_T("%d"), int(batStepInfo.avgVolt + 0.5));
//	avgVolt = str;
//
//	str.Format(_T("%d"), int(batStepInfo.endStepInfo.voltage + 0.5));
//	endVolt = str;
//	
//	str.Format(_T("%d"), int(batStepInfo.endStepInfo.energy + 0.5));
//	energy = str;
//
//	str.Format(_T("%d"), int(batStepInfo.endStepInfo.curnt + 0.5));
//	endCurrent = str;
//}

CPartBattery::CPartBattery(const CBatStepInfo batStepInfo)
{
	CString str;
	capFlag = 0;

	batId = batStepInfo.startStepInfo.batId;

	str.Format(_T("%d"), int(batStepInfo.endStepInfo.capacity + 0.5));
	capacity = str;

	str.Format(_T("%d"), int(batStepInfo.endStepInfo.atime + 0.5));
	atime = str;

	str.Format(_T("%d"), int(batStepInfo.startStepInfo.voltage + 0.5));
	openVolt = str;

	str.Format(_T("%d"), int(batStepInfo.avgVolt + 0.5));
	avgVolt = str;

	str.Format(_T("%d"), int(batStepInfo.endStepInfo.voltage + 0.5));
	endVolt = str;

	str.Format(_T("%d"), int(batStepInfo.endStepInfo.energy + 0.5));
	energy = str;

	str.Format(_T("%d"), int(batStepInfo.endStepInfo.curnt + 0.5));
	endCurrent = str;
}

CPartBattery::~CPartBattery()
{
}
