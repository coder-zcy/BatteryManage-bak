#pragma once
#include "StepMsg.h"

class AdischargeMsg : public StepMsg{
public:
	//6	������	03	1	�����ŵ繤����
	//	7	���޵�ѹ	0BB8	2	3000mV����ѹֵ��
	//	8	�ŵ����	03E8	2	1000mA
	//	9	���ʱ��	0064	2	100min
	//	10	��ѹ��	0005	2	5mV
	//	11	������	0005	2	5mA
	//	12	ʱ���	0064	2	100mim
	//	13	У����		1	�����
	//	14	������	0xAB	1	����λ

	CString cabIdStr; 
	CString stepIdStr;
	CString voltageMinLimitStr;
	CString disChargeCurrentStr;
	CString dischargeTimeStr;
	CString voltageDiffStr;
	CString currentDiffStr;
	CString timeDiffStr;
	CString endCapacityStr;

	BYTE technologyCode;
	BYTE dataLen;

	BYTE voltageMinLimit_high;
	BYTE voltageMinLimit_low;

	BYTE disChargeCurrent1;
	BYTE disChargeCurrent2;
	BYTE disChargeCurrent3;
	BYTE disChargeCurrent4;

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

public:
	AdischargeMsg();
	AdischargeMsg(CString stepIdStr, string stepStr, CabinetInfo cabInfo);
	void serialization(CByteArray &result);
};


