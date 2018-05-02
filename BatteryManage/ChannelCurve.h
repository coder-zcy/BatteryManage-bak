#pragma once
#include "DbColumn.h"

class ChannelCurve
{
public:
	ChannelCurve();
	~ChannelCurve();
public:
	CDbColumn idFld;
	CDbColumn testItemFld;
	CDbColumn channelFld;
	CDbColumn stepFld;
	CDbColumn cycleFld;
	CDbColumn numFld;
	CDbColumn testTimeFld;
	CDbColumn atimeFld;
	CDbColumn voltageFld;
	CDbColumn currentFld;
	CDbColumn capacityFld;
	CDbColumn energyFld;
	CDbColumn powerFld;
	CDbColumn cabStateFld;
	CDbColumn batStateFld;

	vector<CDbColumn> channelCurveFlds;
};

