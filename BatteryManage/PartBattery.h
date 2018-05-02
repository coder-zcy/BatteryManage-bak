#pragma once
#include "BatStepInfo.h"

/*
	��ط�������
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
	int capFlag;	//	���ݱ�־,�����ÿ��ش��ڷ��ݵĵڼ�������



};

