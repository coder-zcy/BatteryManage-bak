#include "stdafx.h"
#include "AdischargeMsg.h"

AdischargeMsg::AdischargeMsg()
{

}

AdischargeMsg::AdischargeMsg(CString stepIdStr, string stepStr, CabinetInfo cabInfo)
{
	this->technologyCode = 0x03;
	this->dataLen = 0x17;

	this->cabIdStr.Format(_T("%d"), cabInfo.cabinetId);
	this->stepIdStr = stepIdStr;							//	工步号
	vector<string> stepDetailStr = StringUtils::SplitByStr(stepStr, " ");
	this->dischargeTimeStr = stepDetailStr[TIME_PARAID].c_str();		//	放电时间
	this->disChargeCurrentStr = stepDetailStr[CURRENT_PARAID].c_str();	//	放电电流
	this->voltageMinLimitStr = stepDetailStr[MIN_VOLT_PARAID].c_str();	//	下限电压
	this->endCapacityStr = stepDetailStr[END_CAPACITY_PARAID].c_str();		//	终止容量

	this->voltageDiffStr.Format(_T("%d"), cabInfo.vdisVal);	//	电压差 
	this->currentDiffStr.Format(_T("%d"), cabInfo.adisVal);	//  电流差
	this->timeDiffStr.Format(_T("%d"), cabInfo.timeDisVal);	//  时间差
	
}

void AdischargeMsg::serialization(CByteArray &result)
{
	//6	工艺码	03	1	恒流放电工艺码
	//	7	下限电压	0BB8	2	3000mV（恒压值）
	//	8	放电电流	03E8	2	1000mA
	//	9	充电时间	0064	2	100min
	//	10	电压差	0005	2	5mV
	//	11	电流差	0005	2	5mA
	//	12	时间差	0064	2	100mim
	//	13	校验码		1	总异或
	//	14	结束码	0xAB	1	结束位


	BYTE tmp;
	cstring2Byte(cabIdStr, tmp, cabinetNo);
	cstring2Byte(stepIdStr, tmp, step);
	cstring2Byte(voltageMinLimitStr, voltageMinLimit_high, voltageMinLimit_low);
	cstring2Byte(disChargeCurrentStr, disChargeCurrent1, disChargeCurrent2, disChargeCurrent3, disChargeCurrent4);
	cstring2Byte(dischargeTimeStr, chargeTime_high, chargeTime_low);
	cstring2Byte(voltageDiffStr, voltageDiff_high, voltageDiff_low);
	cstring2Byte(currentDiffStr, currentDiff_high, currentDiff_low);
	cstring2Byte(timeDiffStr, timeDiff_high, timeDiff_low);
	cstring2Byte(endCapacityStr, endCapacity1, endCapacity2, endCapacity3, endCapacity4);
	

	result.SetSize(27);
	result.SetAt(0, preCode_high);
	result.SetAt(1, preCode_low);
	result.SetAt(2, cabinetNo);
	result.SetAt(3, dataLen);
	result.SetAt(4, writeCommand);
	result.SetAt(5, step);
	result.SetAt(6, technologyCode);
	result.SetAt(7, voltageMinLimit_high);
	result.SetAt(8, voltageMinLimit_low);
	result.SetAt(9, disChargeCurrent1);
	result.SetAt(10, disChargeCurrent2);
	result.SetAt(11, disChargeCurrent3);
	result.SetAt(12, disChargeCurrent4);

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

	result.SetAt(26, endCode);
	CheckCode = preCode_high ^ preCode_low;
	for (int i = 2; i < result.GetSize() - 1; ++i)
	{
		CheckCode = CheckCode ^ result.GetAt(i);
	}

	result.SetAt(25, CheckCode);
}
