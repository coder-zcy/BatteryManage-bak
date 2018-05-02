#pragma once
#include "StepMsg.h"

class OverMsg :public StepMsg{
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
	CString loopStr;

	BYTE technologyCode = 0x05;
	BYTE dataLen = 0x07;

	BYTE startStep;
	BYTE endStep;

	BYTE loop_high;
	BYTE loop_low;

public:
	OverMsg(string);
	void serialization(CByteArray &result);
};

