#include "stdafx.h"
#include "BatteryPane.h"


CBatteryPane::CBatteryPane(CabinetInfo cabinetInfo)
{
	//(1) ���ؼ��������ļ�
	//(2) ��������ļ�
	this->SetPaneType(0); // Ĭ�ϵ�ع�ı��Ϊ ����
	//this->SetCapId(1);
	this->SetRowNum(cabinetInfo.groupNumPerCol);
	this->SetColNum(cabinetInfo.numPerGroup);
	this->SetSubGroupBatNum(8);

	this->SetBodyHeightRowRatio(0.8);
	this->SetBatHeightRowRatio(0.9);
	this->SetSelHeightRowRatio(0.95);

	//this->SetGroupGapRatio(0.01);
}


CBatteryPane::~CBatteryPane()
{
}

void CBatteryPane::CalParamter(CRect batPicRect)
{
	// 1 ���㻭�������Rect
	this->paneRect = batPicRect;
	// 2 ��ΪRect���������������Ե�ط���Ŀ�Ȳ����ܱ�ÿ�α������������������ȶ�ÿһ�е�ط������ȡ��
	subGroupNum = (colNum + subGroupBatNum - 1) / subGroupBatNum;
	this->SetRightBlankWidth(paneRect.Width() % subGroupNum);
	// 3 ����ÿ��ǰ�ߵĿհ�,��д����õ�
	this->SetGroupWidth(paneRect.Width() / subGroupNum);
	this->SetGroupBlankWidth(16 + groupWidth % subGroupBatNum);

	// 4 �����صĸ�������
	batteryBodyWidth = ((groupWidth - groupBlankWidth) / subGroupBatNum);
	this->batteryRowHeight = (paneRect.Height()) / rowNum;
	batteryCapWidth = batteryBodyWidth / 2;
	batteryBodyHeight = batteryRowHeight * bodyHeightRowRatio;
	batteryCapHeight = (batHeightRowRatio - bodyHeightRowRatio) * batteryRowHeight;
}

