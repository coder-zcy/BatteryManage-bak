#include "stdafx.h"
#include "OverMsg.h"


OverMsg::OverMsg(string)
{

}

void OverMsg::serialization( CByteArray &result)
{
	BYTE tmp;
	cstring2Byte(cabIdStr, tmp, cabinetNo);
	cstring2Byte(stepIdStr, tmp, step);
	cstring2Byte(startStepIdStr, tmp, startStep);
	cstring2Byte(endStepIdStr, tmp, endStep);
	cstring2Byte(loopStr, loop_high, loop_low);

	result.SetSize(13);
	result.SetAt(0, preCode_high);
	result.SetAt(1, preCode_low);
	result.SetAt(2, cabinetNo);
	result.SetAt(3, dataLen);
	result.SetAt(4, writeCommand);
	result.SetAt(5, step);
	result.SetAt(6, technologyCode);
	result.SetAt(7, startStep);
	result.SetAt(8, endStep);
	result.SetAt(9, loop_high);
	result.SetAt(10, loop_low);

	result.SetAt(12, endCode);
	CheckCode = preCode_high ^ preCode_low;
	for (int i = 2; i < result.GetSize() - 1; ++i)
	{
		CheckCode = CheckCode ^ result.GetAt(i);
	}

	result.SetAt(11, CheckCode);
}
