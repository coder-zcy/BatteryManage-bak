#include "stdafx.h"
#include "LowerUtils.h"

// 全局变量,记录下位机状态
CLowerCabs lowerCabs;

const CString BATSTATE_CSTR[16] = {
	L"未结束", L"时间到", L"上限电压到", L"终止电流到", L"-▲V到",
	L"电流异常", L"电压异常", L"容量异常", L"偏离平均电压异常", L"手动寄存",
	L"无电池或电池接触不良", L"不良电池", L"下限电压到"
};


CLowerUtils::CLowerUtils()
{
}


CLowerUtils::~CLowerUtils()
{
}
