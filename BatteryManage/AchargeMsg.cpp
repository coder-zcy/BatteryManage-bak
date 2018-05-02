#include "stdafx.h"
#include "AchargeMsg.h"


AchargeMsg::AchargeMsg()
{

}

AchargeMsg::AchargeMsg(CString stepIdStr, string stepStr, CabinetInfo cabInfo)
{
	this->technologyCode = 0x04;
	this->dataLen = 0x19;
	this->cabIdStr.Format(_T("%d"), cabInfo.cabinetId);
	this->stepIdStr = stepIdStr;						// 工步号
														// 工艺码
	vector<string> stepDetailStr = StringUtils::SplitByStr(stepStr, " ");
	this->chargeTimeStr = stepDetailStr[TIME_PARAID].c_str();		//	时间
	this->chargeCurrentStr = stepDetailStr[CURRENT_PARAID].c_str();	//	充电电流
	this->voltageMaxLimitStr = stepDetailStr[MAX_VOLT_PARAID].c_str();//	上限电压
	this->deltavStr = stepDetailStr[DELTA_VOLT_PARAID].c_str();
	this->endCapacityStr = stepDetailStr[END_CAPACITY_PARAID].c_str();	//	终止容量

	this->voltageDiffStr.Format(_T("%d"), cabInfo.vdisVal);//	电压差 
	this->currentDiffStr.Format(_T("%d"), cabInfo.adisVal);//  电流差
	this->timeDiffStr.Format(_T("%d"), cabInfo.timeDisVal);//	时间差
}

void AchargeMsg::serialization(CByteArray &result)
{
	BYTE tmp;


	cstring2Byte(cabIdStr, tmp, cabinetNo);
	cstring2Byte(stepIdStr, tmp, step);
	cstring2Byte(voltageMaxLimitStr, voltageMaxLimit_high, voltageMaxLimit_low);
	cstring2Byte(chargeCurrentStr, chargeCurrent1, chargeCurrent2, chargeCurrent3, chargeCurrent4);
	cstring2Byte(chargeTimeStr, chargeTime_high, chargeTime_low);
	cstring2Byte(voltageDiffStr, voltageDiff_high, voltageDiff_low);
	cstring2Byte(currentDiffStr, currentDiff_high, currentDiff_low);
	cstring2Byte(timeDiffStr, timeDiff_high, timeDiff_low);
	cstring2Byte(endCapacityStr, endCapacity1, endCapacity2, endCapacity3, endCapacity4);
	cstring2Byte(deltavStr, deltav_high, deltav_low);

	result.SetSize(29);
	result.SetAt(0, preCode_high);
	result.SetAt(1, preCode_low);
	result.SetAt(2, cabinetNo);
	result.SetAt(3, dataLen);
	result.SetAt(4, writeCommand);
	result.SetAt(5, step);
	result.SetAt(6, technologyCode);
	result.SetAt(7, voltageMaxLimit_high);
	result.SetAt(8, voltageMaxLimit_low);
	result.SetAt(9, chargeCurrent1);
	result.SetAt(10, chargeCurrent2);
	result.SetAt(11, chargeCurrent3);
	result.SetAt(12, chargeCurrent4);
	result.SetAt(13, chargeTime_high);
	result.SetAt(14, chargeTime_low);
	result.SetAt(15, voltageDiff_high);
	result.SetAt(16, voltageDiff_low);
	result.SetAt(17, currentDiff_high);
	result.SetAt(18, currentDiff_low);
	result.SetAt(19, timeDiff_high);
	result.SetAt(20, timeDiff_low);
	result.SetAt(21, endCapacity1);
	result.SetAt(22, endCapacity2);
	result.SetAt(23, endCapacity3);
	result.SetAt(24, endCapacity4);
	result.SetAt(25, deltav_high);
	result.SetAt(26, deltav_low);

	result.SetAt(28, endCode);

	CheckCode = preCode_high ^ preCode_low;
	for (int i = 2; i < result.GetSize() - 1; ++i)
	{
		CheckCode = CheckCode ^ result.GetAt(i);
	}

	result.SetAt(27, CheckCode);



}
