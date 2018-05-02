#pragma once
#include "StepMsg.h"

class LayMsg : public StepMsg{
/*	6	������	02	1	����
	7	����ʱ��	0004	2	4min
	8	��ѹ��	0005	2	5mV
	9	ʱ���	0064	2	100min
*/
public:
	CString cabIdStr;
	CString stepIdStr;
	CString layTimeStr;
	CString voltageDiffStr;
	CString timeDiffStr;

	BYTE technologyCode;
	BYTE dataLen;

	BYTE putAsideTime_high;
	BYTE putAsideTime_low;

	BYTE voltageDiff_high;
	BYTE voltageDiff_low;

	BYTE timeDiff_high;
	BYTE timeDiff_low;

public:
	LayMsg();
	LayMsg(CString stepIdStr, string stepStr, CabinetInfo cabInfo);
	void serialization(CByteArray &result);
};

