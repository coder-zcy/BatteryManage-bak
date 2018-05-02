#pragma once
#include "StepMsg.h"

class AchargeMsg : public StepMsg{
public:
	//5	����	04	1	ָ����4
	//	6	������	04	1	������繤����
	//	7	���޵�ѹ	1068	2	4200mV����ѹֵ��
	//	9	������	03E8	2	1000mA
	//	10	���ʱ��	0064	2	100min
	//	11	��ѹ��	0005	2	5mV
	//	12	������	0005	2	5mA
	//	13	ʱ���	0001	2	1min
	//  14	��ֹ����	0001	2

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


