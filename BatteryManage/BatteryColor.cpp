#include "stdafx.h"
#include "BatteryColor.h"


CBatteryColor::CBatteryColor()
{
	offVoltCol = COLORREF(RGB(0, 0, 0));		//	ƫ��ƽ����ѹ��ɫ
	badBatCol = COLORREF(RGB(0, 0, 0));			//	���������ɫ
	waitCol = COLORREF(RGB(255,255,255));		//	������ɫ
	offlineCol = COLORREF(RGB(255, 153, 102));	//	�����岻����״̬

}


CBatteryColor::~CBatteryColor()
{
}
