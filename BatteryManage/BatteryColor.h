#pragma once
class CBatteryColor
{
public:
	CBatteryColor();
	~CBatteryColor();

public:
	COLORREF chargeCol;			
	COLORREF recycleCol;
	COLORREF storCol;
	COLORREF unstorCol;
	COLORREF stopCol;
	COLORREF dischargeCol;
	COLORREF layCol;
	COLORREF vaChargeCol;
	COLORREF verrorCol;
	COLORREF aerrorCol;
	COLORREF overAlarmCol;
	COLORREF leakAlarmCol;
	COLORREF badContCol;
	COLORREF voverCol;
	COLORREF batteryWinCol;

	COLORREF offVoltCol;		//	偏离平均电压
	COLORREF badBatCol;			//	坏电池颜色
	COLORREF waitCol;			//	待机
	COLORREF offlineCol;		//	整个板不在线状态

};

