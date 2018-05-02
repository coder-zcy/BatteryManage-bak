#pragma once

#include "Battery.h"
#include <iostream>
#include <vector>

using namespace std;



class CabBattery
{
public:
	CabBattery(int cabId, int workId, int stepId, int cycleId);// 根据cabId 获取CabinetInfo, 然后对CabinetInfo中的batterys进行初始化
	CabBattery();	
	~CabBattery();
public:
	int cabId;
	int cabState;
	int stepId;			//	工步编号
	int cycleId;		//	循环编号
	int workId;			//	工艺码

	BOOL wirteToDb;
	vector<CBattery> batterys;
};

