#pragma once
#include "LowerCabs.h"


extern CLowerCabs lowerCabs;
extern const CString BATSTATE_CSTR[];


#define SASC_CHARGE_CODE	1	//	恒流恒压充电编码
#define LAY_CODE			2	//	搁置编码
#define SA_DISCHARGE_CODE	3	//	恒流放电编码
#define SA_CHARGE_CODE		4	//	恒流充电编码
#define LOOP_CODE			5	//	循环编码
#define OBTAIN_BAT_CODE		6	//	获取电池数据编码
#define OBTAIN_MODEL_CODE	7	//	获取下位机信息编码
#define HEART_BEAT_CODE		8	//	心跳包
#define CAB_CON_CODE		10	//	联机编码

#define MIN_BAT_STATE			0	//	最小状态
#define UNOVER_CODE				0	//  未结束
#define TIME_COME_CODE			1	//	时间到
#define MAX_VOLT_COME_CODE	    2	//	上限电压到
#define END_CURRENT_COME_CODE	3	//	终止电流到
#define DELTA_COME_CODE			4	//	-▲V到
#define CURRENT_ERROR_CODE		5	//	电流异常
#define VOLT_ERROR_CODE			6	//	电压异常
#define CAPACITY_ERROE_CODE		7	//	容量异常
#define OFF_VOLT_CODE			8	//	偏离平均电压异常(先忽略)
#define HAND_REGIDIT_CODE		9	//	手动寄存（寄存颜色）
#define NONE_BAT_CODE			10	//	无电池或电池接触不良
#define BAD_BAT_CODE			11	//	不良电池
#define MIN_VOLT_COME_CODE		12	//	下限电压到（寄存颜色）
#define MAX_BAT_STATE			16	//	最大状态




class CLowerUtils
{
public:
	CLowerUtils();
	~CLowerUtils();
};

