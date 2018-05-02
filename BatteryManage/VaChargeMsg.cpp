#include "stdafx.h"
#include "VaChargeMsg.h"



VaChargeMsg::VaChargeMsg()
{

}


VaChargeMsg::VaChargeMsg(CString stepIdStr, string stepStr,CabinetInfo cabInfo)
{
	this->technologyCode = 0x01;
	this->dataLen = 0x1B;

	this->cabIdStr.Format(_T("%d"), cabInfo.cabinetId);	// 机柜编号
	this->stepIdStr = stepIdStr;						// 工步号
	vector<string> stepDetailStr = StringUtils::SplitByStr(stepStr, " ");
	this->chargeTimeStr = stepDetailStr[TIME_PARAID].c_str();		//	时间
	this->chargeCurrentStr = stepDetailStr[CURRENT_PARAID].c_str();	//	充电电流
	this->voltageMaxLimitStr = stepDetailStr[MAX_VOLT_PARAID].c_str();//	上线电压
	this->deltaVoltStr = stepDetailStr[DELTA_VOLT_PARAID].c_str();			// delta电压
	this->endCurrentStr = stepDetailStr[END_CURRENT_PARAID].c_str();		//	终止电流
	this->endCapacityStr = stepDetailStr[END_CAPACITY_PARAID].c_str();	//	终止容量
	

	this->voltageDiffStr.Format(_T("%d"),cabInfo.vdisVal);//	电压差 
	this->currentDiffStr.Format(_T("%d"), cabInfo.adisVal);//  电流差
	this->timeDiffStr.Format(_T("%d"), cabInfo.timeDisVal);//  时间差	
	
}

void VaChargeMsg::serialization(CByteArray &result)
{
	//5	工步	01	1	指令行1
	//	6	工艺码	01	1	恒流恒压充电工艺码
	//	7	上限电压	1068	2	4200mV（恒压值）
	//	8	充电电流	03E8	2	1000mA
	//	9	终止电流	000A	2	10mA
	//	10	充电时间	0064	2	100min
	//	11	电压差	0005	2	5mV
	//	12	电流差	0005	2	5mA
	//	13	时间差	0064	2	100min

	BYTE tmp;
	//cabIdStr = _T("1");
	//stepIdStr = _T("1");
	//voltageMaxLimitStr = _T("4200");
	//chargeCurrentStr = _T("1000");
	//endCurrentStr = _T("10");
	//chargeTimeStr = _T("100");
	//voltageDiffStr = _T("5");
	//currentDiffStr = _T("5");
	//timeDiffStr = _T("100");


	cstring2Byte(cabIdStr, tmp, cabinetNo);
	cstring2Byte(stepIdStr, tmp, step);
	cstring2Byte(voltageMaxLimitStr, voltageMaxLimit_high, voltageMaxLimit_low);
	cstring2Byte(chargeCurrentStr, chargeCurrent1, chargeCurrent2, chargeCurrent3, chargeCurrent4);
	cstring2Byte(endCurrentStr, endCurrent_high, endCurrent_low);
	cstring2Byte(chargeTimeStr, chargeTime_high, chargeTime_low);
	cstring2Byte(voltageDiffStr, voltageDiff_high, voltageDiff_low);
	cstring2Byte(currentDiffStr, currentDiff_high, currentDiff_low);
	cstring2Byte(timeDiffStr, timeDiff_high, timeDiff_low);
	cstring2Byte(endCapacityStr, endCapacity1, endCapacity2, endCapacity3, endCapacity4);
	cstring2Byte(deltaVoltStr, deltaVolt_high, deltaVolt_low);



	result.SetSize(31);
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
	result.SetAt(13, endCurrent_high);
	result.SetAt(14, endCurrent_low);
	result.SetAt(15, chargeTime_high);
	result.SetAt(16, chargeTime_low);
	result.SetAt(17, voltageDiff_high);
	result.SetAt(18, voltageDiff_low);
	result.SetAt(19, currentDiff_high);
	result.SetAt(20, currentDiff_low);
	result.SetAt(21, timeDiff_high);
	result.SetAt(22, timeDiff_low);
	result.SetAt(23, endCapacity1);
	result.SetAt(24, endCapacity2);
	result.SetAt(25, endCapacity3);
	result.SetAt(26, endCapacity4);
	result.SetAt(27, deltaVolt_high);
	result.SetAt(28, deltaVolt_low);

	result.SetAt(30, endCode);

	CheckCode = preCode_high ^ preCode_low;
	for (int i = 2; i < result.GetSize() - 1; ++i)
	{
		CheckCode = CheckCode ^ result.GetAt(i);
	}

	result.SetAt(29, CheckCode);
}
