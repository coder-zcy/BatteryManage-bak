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

	COLORREF offVoltCol;		//	ƫ��ƽ����ѹ
	COLORREF badBatCol;			//	�������ɫ
	COLORREF waitCol;			//	����
	COLORREF offlineCol;		//	�����岻����״̬

};

