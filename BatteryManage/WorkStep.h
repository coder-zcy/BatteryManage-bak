#pragma once
/*
π§≤Ω¿‡
*/
class CWorkStep
{
public:
	CWorkStep();
	CWorkStep(int stepId, CString stepStr);

	~CWorkStep();

public:
	BOOL isValide;
	int stepId;
	CString workStepName;
	CString workTime;
	CString current;
	CString maxVolt;
	CString minVolt;
	CString deltaVolt;
	CString endCurrent;
	CString endCapacity;
	CString startStep;
	CString endStep;
	CString loopNum;
};


