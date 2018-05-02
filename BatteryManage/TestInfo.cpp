#include "stdafx.h"
#include "TestInfo.h"



TestInfo::TestInfo()
{
	isValid = FALSE;
}

TestInfo::TestInfo(CabinetInfo cabInfo, CString timeStr, CString cabDbPath)
{
	this->startTime = CT2A(timeStr.GetBuffer());

	this->adis = cabInfo.adis;
	this->adisVal = cabInfo.adisVal;
	this->cabinet = cabInfo.cabinetId;
	this->cabinetTag = CT2A(cabInfo.deviceId.GetBuffer());
	this->colShowNum = cabInfo.colShowNum;
	this->constAmax = cabInfo.constAmax;
	this->constAmin = cabInfo.constAmin;
	this->constVmax = cabInfo.constVmax;
	this->constVmin = cabInfo.constVmin;
	this->deviceName = CT2A(cabInfo.deviceName.GetBuffer());
	this->fileName = CT2A(cabDbPath.GetBuffer());
	this->finishFlag = 0;	//	表示未结束
	this->finishTime = CT2A(timeStr.GetBuffer());
	this->groupNumPerCol = cabInfo.groupNumPerCol;
	//this->information =	//	先不管
	this->numPerGroup = cabInfo.numPerGroup;
	//this->pcName =		//	先不管
	//this->setValue		//	先不管
	this->timeDis = cabInfo.timeDis;
	this->timeDisVal = cabInfo.timeDisVal;
	this->vdis = cabInfo.vdis;
	this->vdisVal = cabInfo.vdisVal;
	
}


TestInfo::~TestInfo()
{
}
