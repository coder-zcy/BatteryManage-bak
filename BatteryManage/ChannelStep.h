#pragma once
#include "DbColumn.h"

class ChannelStep
{
public:
	ChannelStep();
	~ChannelStep();
public:

	CDbColumn idFld;
	CDbColumn testItemFld;
	CDbColumn channelFld;
	CDbColumn stepFld;
	CDbColumn cycleFld;
	CDbColumn stationFld;
	CDbColumn saveTimeFld;
	CDbColumn setCurrentFld;
	CDbColumn atimeFld;
	CDbColumn capicityFld;
	CDbColumn energyFld;
	CDbColumn openvFld;
	CDbColumn meanvFld;
	CDbColumn midvFld;
	CDbColumn endVFld;
	CDbColumn endcFld;
	CDbColumn ccTimeFld;
	CDbColumn ccCapacityFld;
	CDbColumn ccRatioFld;
	CDbColumn capacitySpoilageFld;
	CDbColumn dischargeEfficiencyFld;
	CDbColumn lossRateFld;
	CDbColumn v1TimeFld;
	CDbColumn v2TimeFld;
	CDbColumn v3TimeFld;
	CDbColumn v4TimeFld;
	CDbColumn v5TimeFld;
	CDbColumn v1CapacityFld;
	CDbColumn v2CapacityFld;
	CDbColumn v3CapacityFld;
	CDbColumn v4CapacityFld;
	CDbColumn v5CapacityFld;

	vector<CDbColumn> channelStepFlds;
};

