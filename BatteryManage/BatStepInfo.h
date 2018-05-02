#pragma once
/*
分容时从mdb文件时打开的获取每个工步数据的信息记载
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
	//int capFlag;	//	分容标志,表明该块电池处于分容的第几个级别

	CDbattery startStepInfo;
	CDbattery endStepInfo;

	int avgCapacity;
	int avgVolt;

};

