#pragma once
#include "StepMsg.h"

class LightLedMsg : public StepMsg
{
public:

	CString cabIdStr;
	CString stepIdStr;
	CString voltageMaxLimitStr;
	CString chargeCurrentStr;
	CString chargeTimeStr;
	CString voltageDiffStr;
	CString currentDiffStr;
	CString timeDiffStr;
	CString endCapacityStr;
	CString deltavStr;

	BYTE technologyCode;
	BYTE dataLen;

	BYTE voltageMaxLimit_high;
	BYTE voltageMaxLimit_low;

	BYTE chargeCurrent1;
	BYTE chargeCurrent2;
	BYTE chargeCurrent3;
	BYTE chargeCurrent4;

	BYTE chargeTime_high;
	BYTE chargeTime_low;

	BYTE voltageDiff_high;
	BYTE voltageDiff_low;

	BYTE currentDiff_high;
	BYTE currentDiff_low;

	BYTE timeDiff_high;
	BYTE timeDiff_low;

	BYTE endCapacity1;
	BYTE endCapacity2;
	BYTE endCapacity3;
	BYTE endCapacity4;

	BYTE deltav_high;
	BYTE deltav_low;
public:
	LightLedMsg();
	~LightLedMsg();

	void serialization(CByteArray &result);
};

