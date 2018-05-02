#include "stdafx.h"
#include "ChannelCurve.h"


ChannelCurve::ChannelCurve()
{
	idFld = CDbColumn("ID", NUM_TYPE, 10, false);
	testItemFld = CDbColumn("TESTITEM", INT_TYPE, 10, true);
	channelFld = CDbColumn("CHANNEL", INT_TYPE, 10, true);
	stepFld = CDbColumn("STEP", INT_TYPE, 10, true);
	cycleFld = CDbColumn("CYCLE", INT_TYPE, 10, true);
	numFld = CDbColumn("NUM", INT_TYPE, 10, true);
	testTimeFld = CDbColumn("TEST_TIME", DATETIME_TYPE, 10, true);
	atimeFld = CDbColumn("ATIME", DOUBLE_TYPE, 20, true);
	voltageFld = CDbColumn("VOLTAGE", DOUBLE_TYPE, 20, true);
	currentFld = CDbColumn("CURRENT", DOUBLE_TYPE, 20, true);
	capacityFld = CDbColumn("CAPACITY", DOUBLE_TYPE, 20, true);
	energyFld = CDbColumn("ENERGY", DOUBLE_TYPE, 20, true);
	powerFld = CDbColumn("POWER", DOUBLE_TYPE, 20, true);
	cabStateFld = CDbColumn("CABSTATE", INT_TYPE, 10, true);
	batStateFld = CDbColumn("BATSTATE", INT_TYPE, 10, true);

	channelCurveFlds.push_back(idFld);
	channelCurveFlds.push_back(testItemFld);
	channelCurveFlds.push_back(channelFld);
	channelCurveFlds.push_back(stepFld);
	channelCurveFlds.push_back(cycleFld);
	channelCurveFlds.push_back(numFld);
	channelCurveFlds.push_back(testTimeFld);
	channelCurveFlds.push_back(atimeFld);
	channelCurveFlds.push_back(voltageFld);
	channelCurveFlds.push_back(currentFld);
	channelCurveFlds.push_back(capacityFld);
	channelCurveFlds.push_back(energyFld);
	channelCurveFlds.push_back(powerFld);
	channelCurveFlds.push_back(cabStateFld);
	channelCurveFlds.push_back(batStateFld);
}


ChannelCurve::~ChannelCurve()
{
}
