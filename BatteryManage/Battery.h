#pragma once
#include "StringUtils.h"


//1	恒流恒压充电的工艺码为	1
extern const int SASC_CHARGE_CODE;
//2	搁置的工艺码为		2
extern const int LAY_CODE;
//3	恒流放电工艺码为	3
extern const int DISCHARGE_CODE;
//4	恒流充电工艺码为	4
extern const int CHARGE_CODE;
//5 循环指令
extern const int LOOP_CODE;
//6 获取电池参数指令
extern const int PARA_CODE;

//7 电池非可用状态
extern const int INVALIDE_STATE;

// 电池工作状态
extern const int WORKING_STATE;

extern const CString INVALIDE_STATE_CSTR;
extern const CString INVALIDE_STATE_CSTR2;

//  BatterymainView中参数选择的定义
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
	int energyVal;   // 电量	
	int capacityVal; // 容量
};

