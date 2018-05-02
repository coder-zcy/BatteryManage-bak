#include "stdafx.h"
#include "LoopMsg.h"

LoopMsg::LoopMsg()
{

}

LoopMsg::LoopMsg(CString stepIdStr, string stepStr, CabinetInfo cabInfo)
{
	this->technologyCode = 0x05;
	this->dataLen = 0x08;

	this->cabIdStr.Format(_T("%d"), cabInfo.cabinetId);
	this->stepIdStr = stepIdStr;							//	工步号
	vector<string> stepDetailStr = StringUtils::SplitByStr(stepStr, " ");
	this->startStepIdStr = stepDetailStr[START_STEP_PARAID].c_str();			//	搁置时间
	this->endStepIdStr = stepDetailStr[END_CURRENT_PARAID].c_str();
	this->loopNumStr = stepDetailStr[LOOP_NUM_PARAID].c_str();

}

void LoopMsg::serialization( CByteArray &result)
{
	BYTE tmp;
	cstring2Byte(cabIdStr, tmp, cabinetNo);
	cstring2Byte(stepIdStr, tmp, step);
	cstring2Byte(startStepIdStr, tmp, startStep);
	cstring2Byte(endStepIdStr, tmp, endStep);
	cstring2Byte(loopNumStr, tmp, loopNum);

	result.SetSize(12);
	result.SetAt(0, preCode_high);
	result.SetAt(1, preCode_low);
	result.SetAt(2, cabinetNo);
	result.SetAt(3, dataLen);
	result.SetAt(4, writeCommand);
	result.SetAt(5, step);
	result.SetAt(6, technologyCode);
	result.SetAt(7, startStep);
	result.SetAt(8, endStep);
	result.SetAt(9, loopNum);
	result.SetAt(11, endCode);
	CheckCode = preCode_high ^ preCode_low;
	for (int i = 2; i < result.GetSize() - 1; ++i)
	{
		CheckCode = CheckCode ^ result.GetAt(i);
	}

	result.SetAt(10, CheckCode);
}