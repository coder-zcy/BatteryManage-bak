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
	this->stepIdStr = stepIdStr;							//	������
	vector<string> stepDetailStr = StringUtils::SplitByStr(stepStr, " ");
	this->dischargeTimeStr = stepDetailStr[TIME_PARAID].c_str();		//	�ŵ�ʱ��
	this->disChargeCurrentStr = stepDetailStr[CURRENT_PARAID].c_str();	//	�ŵ����
	this->voltageMinLimitStr = stepDetailStr[MIN_VOLT_PARAID].c_str();	//	���޵�ѹ
	this->endCapacityStr = stepDetailStr[END_CAPACITY_PARAID].c_str();		//	��ֹ����

	this->voltageDiffStr.Format(_T("%d"), cabInfo.vdisVal);	//	��ѹ�� 
	this->currentDiffStr.Format(_T("%d"), cabInfo.adisVal);	//  ������
	this->timeDiffStr.Format(_T("%d"), cabInfo.timeDisVal);	//  ʱ���
	
}

void AdischargeMsg::serialization(CByteArray &result)
{
	//6	������	03	1	�����ŵ繤����
	//	7	���޵�ѹ	0BB8	2	3000mV����ѹֵ��
	//	8	�ŵ����	03E8	2	1000mA
	//	9	���ʱ��	0064	2	100min
	//	10	��ѹ��	0005	2	5mV
	//	11	������	0005	2	5mA
	//	12	ʱ���	0064	2	100mim
	//	13	У����		1	�����
	//	14	������	0xAB	1	����λ


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
