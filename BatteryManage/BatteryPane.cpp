#include "stdafx.h"
#include "BatteryPane.h"


CBatteryPane::CBatteryPane(CabinetInfo cabinetInfo)
{
	//(1) 加载加载配置文件
	//(2) 加载相关文件
	this->SetPaneType(0); // 默认电池柜的编号为 正面
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
	// 1 计算画电池面板的Rect
	this->paneRect = batPicRect;
	// 2 因为Rect必须是整数，所以电池分组的宽度不可能被每次背面版整除，计算面板宽度对每一行电池分组个数取余
	subGroupNum = (colNum + subGroupBatNum - 1) / subGroupBatNum;
	this->SetRightBlankWidth(paneRect.Width() % subGroupNum);
	// 3 计算每组前边的空白,供写编号用的
	this->SetGroupWidth(paneRect.Width() / subGroupNum);
	this->SetGroupBlankWidth(16 + groupWidth % subGroupBatNum);

	// 4 计算电池的各项属性
	batteryBodyWidth = ((groupWidth - groupBlankWidth) / subGroupBatNum);
	this->batteryRowHeight = (paneRect.Height()) / rowNum;
	batteryCapWidth = batteryBodyWidth / 2;
	batteryBodyHeight = batteryRowHeight * bodyHeightRowRatio;
	batteryCapHeight = (batHeightRowRatio - bodyHeightRowRatio) * batteryRowHeight;
}

