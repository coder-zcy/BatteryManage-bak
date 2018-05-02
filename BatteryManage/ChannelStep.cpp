#include "stdafx.h"
#include "ChannelStep.h"


ChannelStep::ChannelStep()
{
	idFld = CDbColumn("ID", NUM_TYPE, 10, false);
	testItemFld = CDbColumn("TESTITEM", INT_TYPE, 10, true);
	channelFld = CDbColumn("CHANNEL", INT_TYPE, 10, true);
	stepFld = CDbColumn("STEP", INT_TYPE, 10, true);
	cycleFld = CDbColumn("CYCLE", INT_TYPE, 10, true);
	stationFld = CDbColumn("STATION", STR_TYPE, 10, true);
	saveTimeFld = CDbColumn("SAVETIME", DATETIME_TYPE, 135, true);
	setCurrentFld = CDbColumn("SETCURRENT", DOUBLE_TYPE, 20, true);
	atimeFld = CDbColumn("ATIME", DOUBLE_TYPE, 20, true);
	capicityFld = CDbColumn("CAPACITY", DOUBLE_TYPE, 20, true);
	energyFld = CDbColumn("ENERGY", DOUBLE_TYPE, 20, true);
	openvFld = CDbColumn("OPEN_V", DOUBLE_TYPE, 20, true);
	meanvFld = CDbColumn("MEAN_V", DOUBLE_TYPE, 20, true);
	midvFld = CDbColumn("MID_V", DOUBLE_TYPE, 20, true);
	endVFld = CDbColumn("END_V", DOUBLE_TYPE, 20, true);
	endcFld = CDbColumn("END_C", DOUBLE_TYPE, 20, true);
	ccTimeFld = CDbColumn("C_CC_Time", DOUBLE_TYPE, 20, true);
	ccCapacityFld = CDbColumn("C_CC_Capacity", DOUBLE_TYPE, 20, true);
	ccRatioFld = CDbColumn("C_CC_Ratio", DOUBLE_TYPE, 20, true);
	capacitySpoilageFld = CDbColumn("Capacity_Spoilage", DOUBLE_TYPE, 20, true);
	dischargeEfficiencyFld = CDbColumn("Discharge_Efficiency", DOUBLE_TYPE, 20, true);
	lossRateFld = CDbColumn("Loss_Rate", DOUBLE_TYPE, 20, true);
	v1TimeFld = CDbColumn("V1_Time", DOUBLE_TYPE, 20, true);
	v2TimeFld = CDbColumn("V2_Time", DOUBLE_TYPE, 20, true);
	v3TimeFld = CDbColumn("V3_Time", DOUBLE_TYPE, 20, true);
	v4TimeFld = CDbColumn("V4_Time", DOUBLE_TYPE, 20, true);
	v5TimeFld = CDbColumn("V5_Time", DOUBLE_TYPE, 20, true);
	v1CapacityFld = CDbColumn("V1_Capacity", DOUBLE_TYPE, 20, true);
	v2CapacityFld = CDbColumn("V2_Capacity", DOUBLE_TYPE, 20, true);
	v3CapacityFld = CDbColumn("V3_Capacity", DOUBLE_TYPE, 20, true);
	v4CapacityFld = CDbColumn("V4_Capacity", DOUBLE_TYPE, 20, true);
	v5CapacityFld = CDbColumn("V5_Capacity", DOUBLE_TYPE, 20, true);

	channelStepFlds.push_back(idFld);
	channelStepFlds.push_back(testItemFld);
	channelStepFlds.push_back(channelFld);
	channelStepFlds.push_back(stepFld);
	channelStepFlds.push_back(cycleFld);
	channelStepFlds.push_back(stationFld);
	channelStepFlds.push_back(saveTimeFld);
	channelStepFlds.push_back(setCurrentFld);
	channelStepFlds.push_back(atimeFld);
	channelStepFlds.push_back(capicityFld);
	channelStepFlds.push_back(energyFld);
	channelStepFlds.push_back(openvFld);
	channelStepFlds.push_back(meanvFld);
	channelStepFlds.push_back(midvFld);
	channelStepFlds.push_back(endVFld);
	channelStepFlds.push_back(endcFld);
	channelStepFlds.push_back(ccTimeFld);
	channelStepFlds.push_back(ccCapacityFld);
	channelStepFlds.push_back(ccRatioFld);
	channelStepFlds.push_back(capacitySpoilageFld);
	channelStepFlds.push_back(dischargeEfficiencyFld);
	channelStepFlds.push_back(lossRateFld);
	channelStepFlds.push_back(v1TimeFld);
	channelStepFlds.push_back(v2TimeFld);
	channelStepFlds.push_back(v3TimeFld);
	channelStepFlds.push_back(v4TimeFld);
	channelStepFlds.push_back(v5TimeFld);
	channelStepFlds.push_back(v1CapacityFld);
	channelStepFlds.push_back(v2CapacityFld);
	channelStepFlds.push_back(v3CapacityFld);
	channelStepFlds.push_back(v4CapacityFld);
	channelStepFlds.push_back(v5CapacityFld);
}


ChannelStep::~ChannelStep()
{
}
