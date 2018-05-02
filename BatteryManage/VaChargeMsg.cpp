#include "stdafx.h"
#include "VaChargeMsg.h"



VaChargeMsg::VaChargeMsg()
{

}


VaChargeMsg::VaChargeMsg(CString stepIdStr, string stepStr,CabinetInfo cabInfo)
{
	this->technologyCode = 0x01;
	this->dataLen = 0x1B;

	this->cabIdStr.Format(_T("%d"), cabInfo.cabinetId);	// ������
	this->stepIdStr = stepIdStr;						// ������
	vector<string> stepDetailStr = StringUtils::SplitByStr(stepStr, " ");
	this->chargeTimeStr = stepDetailStr[TIME_PARAID].c_str();		//	ʱ��
	this->chargeCurrentStr = stepDetailStr[CURRENT_PARAID].c_str();	//	������
	this->voltageMaxLimitStr = stepDetailStr[MAX_VOLT_PARAID].c_str();//	���ߵ�ѹ
	this->deltaVoltStr = stepDetailStr[DELTA_VOLT_PARAID].c_str();			// delta��ѹ
	this->endCurrentStr = stepDetailStr[END_CURRENT_PARAID].c_str();		//	��ֹ����
	this->endCapacityStr = stepDetailStr[END_CAPACITY_PARAID].c_str();	//	��ֹ����
	

	this->voltageDiffStr.Format(_T("%d"),cabInfo.vdisVal);//	��ѹ�� 
	this->currentDiffStr.Format(_T("%d"), cabInfo.adisVal);//  ������
	this->timeDiffStr.Format(_T("%d"), cabInfo.timeDisVal);//  ʱ���	
	
}

void VaChargeMsg::serialization(CByteArray &result)
{
	//5	����	01	1	ָ����1
	//	6	������	01	1	������ѹ��繤����
	//	7	���޵�ѹ	1068	2	4200mV����ѹֵ��
	//	8	������	03E8	2	1000mA
	//	9	��ֹ����	000A	2	10mA
	//	10	���ʱ��	0064	2	100min
	//	11	��ѹ��	0005	2	5mV
	//	12	������	0005	2	5mA
	//	13	ʱ���	0064	2	100min

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
