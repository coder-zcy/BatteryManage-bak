#pragma once
#include "StepMsg.h"

class VaChargeMsg : public StepMsg{
public:
/*	    6	工艺码	01	1	恒流恒压充电工艺码
		7	上限电压	1068	2	4200mV（恒压值）
		8	充电电流	03E8	2	1000mA
		9	终止电流	000A	2	10mA
		10	充电时间	0064	2	100min
		11	电压差	0005	2	5mV
		12	电流差	0005	2	5mA
		13	时间差	0064	2	100min
*/
	CString cabIdStr;
	CString stepIdStr;
	CString voltageMaxLimitStr;
	CString chargeCurrentStr;
	CString endCurrentStr; 
	CString chargeTimeStr;
	CString voltageDiffStr;
	CString currentDiffStr;
	CString timeDiffStr;
	CString endCapacityStr;
	CString deltaVoltStr;

	BYTE technologyCode;
	BYTE dataLen;

	BYTE voltageMaxLimit_high;
	BYTE voltageMaxLimit_low;
	
	BYTE chargeCurrent1;
	BYTE chargeCurrent2;
	BYTE chargeCurrent3;
	BYTE chargeCurrent4;

	BYTE endCurrent_high;
	BYTE endCurrent_low;

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

	BYTE deltaVolt_high;
	BYTE deltaVolt_low;

public:

	VaChargeMsg();
	VaChargeMsg(CString stepIdStr, string stepStr, CabinetInfo cabInfo);
	
	void serialization(CByteArray &result);
};

