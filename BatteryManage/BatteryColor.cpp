#include "stdafx.h"
#include "BatteryColor.h"


CBatteryColor::CBatteryColor()
{
	offVoltCol = COLORREF(RGB(0, 0, 0));		//	偏离平均电压颜色
	badBatCol = COLORREF(RGB(0, 0, 0));			//	不良电池颜色
	waitCol = COLORREF(RGB(255,255,255));		//	待机颜色
	offlineCol = COLORREF(RGB(255, 153, 102));	//	整个板不在线状态

}


CBatteryColor::~CBatteryColor()
{
}
