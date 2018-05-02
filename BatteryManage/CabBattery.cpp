#include "stdafx.h"
#include "CabBattery.h"
#include "CabinetInfo.h"
#include "BatteryManage.h"



CabBattery::CabBattery(int cabId, int workId, int stepId, int cycleId)
{
	this->cabId = cabId;
	this->workId = workId;
	this->stepId = stepId;
	this->cycleId = cycleId;

	wirteToDb = FALSE;


	CabinetInfo cabInfo = cabInfos[cabId - 1];
	// 获取总得cab个数
	int count = cabInfo.groupNumPerCol * cabInfo.numPerGroup * cabInfo.colShowNum;
	
	batterys.clear();
	for (int idx = 0; idx < count; ++ idx)
	{
		CBattery battery;
		batterys.push_back(battery);
	}
}

CabBattery::CabBattery()
{
	
}


CabBattery::~CabBattery()
{
}
