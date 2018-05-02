#pragma once
#include "StringUtils.h"


//1	������ѹ���Ĺ�����Ϊ	1
extern const int SASC_CHARGE_CODE;
//2	���õĹ�����Ϊ		2
extern const int LAY_CODE;
//3	�����ŵ繤����Ϊ	3
extern const int DISCHARGE_CODE;
//4	������繤����Ϊ	4
extern const int CHARGE_CODE;
//5 ѭ��ָ��
extern const int LOOP_CODE;
//6 ��ȡ��ز���ָ��
extern const int PARA_CODE;

//7 ��طǿ���״̬
extern const int INVALIDE_STATE;

// ��ع���״̬
extern const int WORKING_STATE;

extern const CString INVALIDE_STATE_CSTR;
extern const CString INVALIDE_STATE_CSTR2;

//  BatterymainView�в���ѡ��Ķ���
extern const int VOLT_SEL;
extern const int CURRENT_SEL;
extern const int TIME_SEL;
extern const int CAPACITY_SEL;
extern int STATE_SEL_CODE;

class CBattery
{
public:
	CBattery(CString batStr, int cabState);

	CBattery();
	~CBattery();

	int GetSpecStateVal(int SEL_CODE);
	CString GetSpecStateStr(int SEL_CODE);

public:
	int batStatVal;
	int timeVal;
	int voltVal;
	int currentVal;
	int energyVal;   // ����	
	int capacityVal; // ����
};

