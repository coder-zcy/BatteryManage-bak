#pragma once
#include "StepMsg.h"

class LoopMsg :public StepMsg{
	//5	工步	05	1
	//6	工艺码	05	1
	//7	起始工步	01	1
	//8	结束工步	04	1
	//9	循环次数	0003	2

public:

	CString cabIdStr;
	CString stepIdStr;
	CString startStepIdStr;
	CString endStepIdStr;
	CString loopNumStr;

	BYTE technologyCode;
	BYTE dataLen;

	BYTE startStep;
	BYTE endStep;

	//BYTE loop_high;
	//BYTE loop_low;
	BYTE loopNum;
public:
	LoopMsg();
	LoopMsg(CString stepIdStr, string stepStr, CabinetInfo cabInfo);
	void serialization(CByteArray &result);
};


