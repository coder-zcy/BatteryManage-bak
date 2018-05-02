#pragma once
#include "StepMsg.h"

class AchargeMsg : public StepMsg{
public:
	//5	工步	04	1	指令行4
	//	6	工艺码	04	1	恒流充电工艺码
	//	7	上限电压	1068	2	4200mV（恒压值）
	//	9	充电电流	03E8	2	1000mA
	//	10	充电时间	0064	2	100min
	//	11	电压差	0005	2	5mV
	//	12	电流差	0005	2	5mA
	//	13	时间差	0001	2	1min
	//  14	终止容量	0001	2

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
	AchargeMsg();
	AchargeMsg(CString stepIdStr, string stepStr, CabinetInfo cabInfo);
	void serialization(CByteArray &result);
};


