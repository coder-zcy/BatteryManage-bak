#pragma once
#include "CabinetInfo.h"

#include <string>
using namespace std;

class TestInfo
{
public:
	TestInfo();
	TestInfo(CabinetInfo cabInfo, CString timeStr, CString cabDbPath);
	~TestInfo();

public:
	string startTime;
	int cabinet;
	int setValue;
	string information;
	string pcName;
	string cabinetTag;
	string fileName;
	string workName;
	int finishFlag;
	int cellNumber;
	string finishTime;
	string deviceName;
	int groupNumPerCol;
	int colShowNum;
	int numPerGroup;
	int constVmax;
	int constVmin;
	int constAmax;
	int constAmin;
	int vdis;
	int vdisVal;
	int adis;
	int adisVal;
	int timeDis;
	int timeDisVal;
	BOOL isValid;	//表明该数据是否有效
};

