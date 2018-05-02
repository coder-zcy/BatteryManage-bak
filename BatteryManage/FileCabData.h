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
	int subGroupBatNum;	//	��ʾ�˸����һ��

	CString filePath;
	TestInfo testInfo;
	vector<WorkProcInfo> workProcInfos;
	vector<vector<CPartBattery *>> stepPartbatterys;
	vector<CPartBattery *> endDisBatterys;

	//3.1 ��ȡ������ʼʱ�ĵ�ѹ��������ʱ�䡢��������������Ϣ
	//vector<vector<CDbattery>> startStepInfos;
	//3.2 ��ȡÿ��������ƽ����ѹ�������ȴ������ֵ
	//vector<vector<double>>  avgVolts; 
	//3.3 ��ȡ��������ʱ�ĵ�ѹ��������ʱ�䡢��������������Ϣ
	//vector<vector<CDbattery>> endStepInfos;
	vector<vector<CBatStepInfo>> batStepInfos;

	vector<int> cacvStepIds;
	vector<vector<CDbattery>> cacvStepInfos;
	

	vector<int> preDisStepIds;

	int mappings[MAX_BAT_NUM];
};

