#include "stdafx.h"
#include "LayMsg.h"

LayMsg::LayMsg()
{

}

LayMsg::LayMsg(CString stepIdStr, string stepStr, CabinetInfo cabInfo)
{
	this->technologyCode = 0x02;
	this->dataLen = 0x0B;

	this->cabIdStr.Format(_T("%d"), cabInfo.cabinetId);
	this->stepIdStr = stepIdStr;							//	工步号
	vector<string> stepDetailStr = StringUtils::SplitByStr(stepStr, " ");
	this->layTimeStr = stepDetailStr[TIME_PARAID].c_str();			//	搁置时间

	this->voltageDiffStr.Format(_T("%d"), cabInfo.vdis);	//	电压差 
	this->timeDiffStr.Format(_T("%d"), cabInfo.timeDis);	//  时间差
}

void LayMsg::serialization(CByteArray &result)
{
	BYTE tmp;
	cstring2Byte(cabIdStr, tmp, cabinetNo);
	cstring2Byte(stepIdStr, tmp, step);
	cstring2Byte(layTimeStr, putAsideTime_high, putAsideTime_low);
	cstring2Byte(voltageDiffStr, voltageDiff_high, voltageDiff_low);
	cstring2Byte(timeDiffStr, timeDiff_high, timeDiff_low);

	result.SetSize(15);
	result.SetAt(0, preCode_high);
	result.SetAt(1, preCode_low);
	result.SetAt(2, cabinetNo);
	result.SetAt(3, dataLen);
	result.SetAt(4, writeCommand);
	result.SetAt(5, step);
	result.SetAt(6, technologyCode);
	result.SetAt(7, putAsideTime_high);
	result.SetAt(8, putAsideTime_low);
	result.SetAt(9, voltageDiff_high);
	result.SetAt(10, voltageDiff_low);
	result.SetAt(11, timeDiff_high);
	result.SetAt(12, timeDiff_low);

	result.SetAt(14, endCode);

	//计算校验位
	CheckCode = preCode_high ^ preCode_low;
	for (int i = 2; i < result.GetSize() - 1; ++i)
	{
		CheckCode = CheckCode ^ result.GetAt(i);
	}

	result.SetAt(13, CheckCode);
}