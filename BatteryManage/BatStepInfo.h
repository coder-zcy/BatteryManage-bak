#pragma once
/*
����ʱ��mdb�ļ�ʱ�򿪵Ļ�ȡÿ���������ݵ���Ϣ����
*/
#include "Dbatterys.h"

class CBatStepInfo
{
public:
	CBatStepInfo();
	~CBatStepInfo();

public:
	//CString capacity;
	//CString atime;
	//CString openVolt;
	//CString avgVolt;
	//CString endVolt;
	//CString energy;
	//CString endCurrent;

	//int batId;
	//int capFlag;	//	���ݱ�־,�����ÿ��ش��ڷ��ݵĵڼ�������

	CDbattery startStepInfo;
	CDbattery endStepInfo;

	int avgCapacity;
	int avgVolt;

};

