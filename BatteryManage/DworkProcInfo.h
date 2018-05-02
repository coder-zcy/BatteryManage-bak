#pragma once
#include "DbColumn.h"

class DWorkProcInfo
{
public:
	DWorkProcInfo();
	~DWorkProcInfo();

public:

	CDbColumn idFld;
	CDbColumn stepIdFld;
	CDbColumn stepNameFld;
	CDbColumn stepTimeFld;
	CDbColumn curntFld;
	CDbColumn maxVoltFld;
	CDbColumn minVoltFld;
	CDbColumn deltavFld;
	CDbColumn endCurrentFld;
	CDbColumn endCapacityFld;

	CDbColumn startStepFld;
	CDbColumn endStepFld;
	CDbColumn loopNumFld;

	vector<CDbColumn> workProcInfoFlds;

};

