#include "stdafx.h"
#include "Battery.h"

//1	������ѹ���Ĺ�����Ϊ	1
const int SASC_CHARGE_CODE = 1;
//2	���õĹ�����Ϊ		2
const int LAY_CODE = 2;
//3	�����ŵ繤����Ϊ	3
const int DISCHARGE_CODE = 3;
//4	������繤����Ϊ	4
const int CHARGE_CODE = 4;
//5 ѭ��ָ��
const int LOOP_CODE = 5;
//6 ��ȡ��ز���ָ��
const int PARA_CODE = 6;

//7 ���û��״ָ̬��
const int INVALIDE_STATE = -999999;
// ��������״̬
const int WORKING_STATE = 0;

const CString INVALIDE_STATE_CSTR = L"-999999";
const CString INVALIDE_STATE_CSTR2 = L"������";


// ����ѡ��Ķ���
const int VOLT_SEL = 0;
const int CURRENT_SEL = 1;
const int TIME_SEL = 2;
const int CAPACITY_SEL = 3;

int STATE_SEL_CODE = 0;

CBattery::CBattery()
{
	this->batStatVal = INVALIDE_STATE;
	timeVal = INVALIDE_STATE;
	currentVal = INVALIDE_STATE;
	voltVal = INVALIDE_STATE;
	energyVal = INVALIDE_STATE;
	capacityVal = INVALIDE_STATE;
}

CBattery::CBattery(CString batStr, int cabState)
{
	int strIdx = 0;
	strIdx += 4;
	
	CString  batStatStr = batStr.Mid(strIdx, 2); strIdx += 2;
	CString voltStr = batStr.Mid(strIdx, 4); strIdx += 4;
	CString currentStr = batStr.Mid(strIdx, 4); strIdx += 4;
	CString timeStr = batStr.Mid(strIdx, 4); strIdx += 4;
	CString capacityStr = batStr.Mid(strIdx, 4); strIdx += 4;
	CString energyStr = batStr.Mid(strIdx, 8); strIdx += 8;
	

	batStatVal = StringUtils::XStrToInt(batStatStr);
	timeVal = StringUtils::XStrToInt(timeStr);
	currentVal = StringUtils::XStrToInt(currentStr);
	voltVal = StringUtils::XStrToInt(voltStr);
	capacityVal = StringUtils::XStrToInt(capacityStr);
	energyVal = StringUtils::XStrToInt(energyStr); // ����
	

	currentVal = cabState == DISCHARGE_CODE ? 0 - currentVal : currentVal;

}

CBattery::~CBattery()
{

}

int CBattery::GetSpecStateVal(int SEL_CODE)
{
	// ����������Ч��Ϣ,�򷵻���ص���Ч��Ϣ,���򷵻�INVALIDE_STATE
	if (batStatVal != INVALIDE_STATE)
	{
		switch (SEL_CODE)
		{
		case VOLT_SEL:
			return voltVal;
			break;
		case CURRENT_SEL:
			return currentVal;
			break;
		case TIME_SEL:
			return timeVal;
			break;
		case CAPACITY_SEL:
			return capacityVal;
			break;
		default:
			return INVALIDE_STATE;
			break;
		}
	}
	return INVALIDE_STATE;
}

CString CBattery::GetSpecStateStr(int SEL_CODE)
{
	CString stateStr = INVALIDE_STATE_CSTR2;
	if (batStatVal != INVALIDE_STATE)
	{
		switch (SEL_CODE)
		{
		case VOLT_SEL:
			stateStr.Format(_T("%d"), voltVal);
			break;
		case CURRENT_SEL:
			stateStr.Format(_T("%d"), currentVal);
			break;
		case TIME_SEL:
			stateStr.Format(_T("%d"), timeVal);
			break;
		case CAPACITY_SEL:
			stateStr.Format(_T("%d"), capacityVal);
			break;
		default:
			break;
		}
	}
	return stateStr;
}

