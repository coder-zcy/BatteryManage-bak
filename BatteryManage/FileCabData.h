#pragma once


#include "TestInfo.h"
#include "WorkProcInfo.h"
#include "PartBattery.h"
#include "DbUtils.h"
#include "CapShowType.h"
#include "BatStepInfo.h"

#include <iostream>
#include <vector>

using namespace std;



#define ATTR_COUNT 7

#define CAPACITY_SEL2 0
#define TIME_SEL2 1
#define OPEN_VOLT_SEL2 2
#define AVG_VOLT_SEL2 3
#define END_VOLT_SEL2 4
#define ENERGY_SEL2 5
#define END_CURRENT_SEL2 6

#define MAX_BAT_NUM 1024

class CFileCabData
{
public:
	CFileCabData();
	CFileCabData(CString dataFilePath);
	~CFileCabData();

public:
	int batCount;
	int groupNumPerCol;
	int colShowNum;
	int numPerGroup;
	int subGroupBatNum;	//	表示八个电池一组

	CString filePath;
	TestInfo testInfo;
	vector<WorkProcInfo> workProcInfos;
	vector<vector<CPartBattery *>> stepPartbatterys;
	vector<CPartBattery *> endDisBatterys;

	//3.1 获取工步初始时的电压、电流、时间、容量、电量等信息
	//vector<vector<CDbattery>> startStepInfos;
	//3.2 获取每个工步的平均电压、电流等待计算的值
	//vector<vector<double>>  avgVolts; 
	//3.3 获取工步结束时的电压、电流、时间、容量、电量等信息
	//vector<vector<CDbattery>> endStepInfos;
	vector<vector<CBatStepInfo>> batStepInfos;

	vector<int> cacvStepIds;
	vector<vector<CDbattery>> cacvStepInfos;
	

	vector<int> preDisStepIds;

	int mappings[MAX_BAT_NUM];
};

