#pragma once
#include "StepMsg.h"

class VaChargeMsg : public StepMsg{
public:
/*	    6	������	01	1	������ѹ��繤����
		7	���޵�ѹ	1068	2	4200mV����ѹֵ��
		8	������	03E8	2	1000mA
		9	��ֹ����	000A	2	10mA
		10	���ʱ��	0064	2	100min
		11	��ѹ��	0005	2	5mV
		12	������	0005	2	5mA
		13	ʱ���	0064	2	100min
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

