#pragma once
#include <string>

using namespace std;

class WorkProcInfo
{
public:
	WorkProcInfo();
	~WorkProcInfo();

public:
	BOOL isValid;
	int stepId;
	string workStepName;
	int workTime;
	int current;
	int maxVolt;
	int minVolt;
	int deltaVolt;
	int endCurrent;
	int endCapacity;
	int startStep;
	int endStep;
	int loopNum;
};

