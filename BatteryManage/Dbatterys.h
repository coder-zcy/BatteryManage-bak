#pragma once
class CDbattery
{
public:
	CDbattery();
	~CDbattery();
public:
	int id;
	int cabId;
	int batId;
	int stepId;
	int cycleId;
	int num;
	CString workEname;
	CTime testTime;
	double atime;
	double voltage;
	double curnt;
	double capacity;
	double energy;
	double power;
	int cabState;
	int batState;
	int cacvState;	//判断恒流恒压工步到的标志 1为真 0为假
};

