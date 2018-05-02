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
	////3.1 获取工步初始时的电压、电流、时间、容量、电量等信息
	//vector<CDbattery> startStepInfos = CDbUtils::GetStartStepInfos(dataFilePath, stepId);
	////3.2 获取每个工步的平均电压、电流等待计算的值
	//vector<double> avgVolts = CDbUtils::GetAvgVolt(dataFilePath, stepId);
	////3.3 获取工步结束时的电压、电流、时间、容量、电量等信息
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
