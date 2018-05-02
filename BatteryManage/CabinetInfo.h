#pragma once

#include <iostream>
#include <string>
using namespace std;

class CabinetInfo
{
public:
	CabinetInfo();
	~CabinetInfo();
public:
	CString id;
	int cabinetId;
	CString deviceName;
	CString deviceId;
	int groupNumPerCol;	//  ÿ������
	int colShowNum;		//	ÿ����ʾ
	int numPerGroup;	//	ÿ�����
	int constVmax;
	int constVmin;
	int constAmax;
	int constAmin;
	int constVchg;
	int omTest;
	int saveToFile; 
	int vdis;
	int vdisVal;
	int adis;
	int adisVal;
	int timeDis;
	int timeDisVal;
	int vshowMax;
	int vshowMin;
	int svshowMax;
	int svshowMin;
	int sashowMax;
	int sashowMin;
	int srshowMax;
	int srshowMin;
	int groupNum;
};

