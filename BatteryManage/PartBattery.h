#pragma once
#include "BatStepInfo.h"

/*
	电池分类数据
*/
class CPartBattery
{
public:
	CPartBattery();
	CPartBattery(CString dbFilePath);
	CPartBattery(const CBatStepInfo batStepInfo);
	~CPartBattery();

public:
	CString capacity;
	CString atime;
	CString openVolt;
	CString avgVolt;
	CString endVolt;
	CString energy;
	CString endCurrent;
	int batId;
	int capFlag;	//	分容标志,表明该块电池处于分容的第几个级别



};

