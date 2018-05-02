#include "stdafx.h"
#include "DworkProcInfo.h"


DWorkProcInfo::DWorkProcInfo()
{
	vector<CDbColumn> workProcInfoFlds;

	idFld = CDbColumn("ID", NUM_TYPE, 10, false);
	stepIdFld = CDbColumn("STEP_ID", INT_TYPE, 10, true);
	stepNameFld = CDbColumn("STEP_NAME", STR_TYPE, 20, true);
	stepTimeFld = CDbColumn("STEP_TIME", DOUBLE_TYPE, 20, true);
	curntFld = CDbColumn("CURNT", DOUBLE_TYPE, 20, true);
	maxVoltFld = CDbColumn("MAX_VOLT", DOUBLE_TYPE, 20, true);
	minVoltFld = CDbColumn("MIN_VOLT", DOUBLE_TYPE, 20, true);
	deltavFld = CDbColumn("DELTAV", DOUBLE_TYPE, 20, true);
	endCurrentFld = CDbColumn("END_CURRENT", DOUBLE_TYPE, 20, true);
	endCapacityFld = CDbColumn("END_CAPACITY", DOUBLE_TYPE, 20, true);
	startStepFld = CDbColumn("START_STEP", INT_TYPE, 10, true);
	endStepFld = CDbColumn("END_STEP", INT_TYPE, 10, true);
	loopNumFld = CDbColumn("LOOP_NUM", INT_TYPE, 10, true);

	workProcInfoFlds.push_back(idFld);
	workProcInfoFlds.push_back(stepIdFld);
	workProcInfoFlds.push_back(stepNameFld);
	workProcInfoFlds.push_back(stepTimeFld);
	workProcInfoFlds.push_back(curntFld);
	workProcInfoFlds.push_back(maxVoltFld);
	workProcInfoFlds.push_back(minVoltFld);
	workProcInfoFlds.push_back(deltavFld);
	workProcInfoFlds.push_back(endCurrentFld);
	workProcInfoFlds.push_back(endCapacityFld);
	workProcInfoFlds.push_back(startStepFld);
	workProcInfoFlds.push_back(endStepFld);
	workProcInfoFlds.push_back(loopNumFld);
}


DWorkProcInfo::~DWorkProcInfo()
{
}
