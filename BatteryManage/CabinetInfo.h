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
	int groupNumPerCol;	//  每列组数
	int colShowNum;		//	每列显示
	int numPerGroup;	//	每组个数
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

