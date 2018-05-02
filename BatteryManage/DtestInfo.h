#pragma once
#include "stdafx.h"
#include "DbColumn.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class DtestInfo
{
public:
	DtestInfo();
	~DtestInfo();

public:

	CDbColumn idFld;
	CDbColumn startTimeFld;
	CDbColumn cabinetFld;
	CDbColumn setValueFld;
	CDbColumn informationFld;
	CDbColumn paNameFld;
	CDbColumn cabinetTagFld;
	CDbColumn fileNameFld;
	CDbColumn workNameFld;
	CDbColumn finishFlagFld;
	CDbColumn cellNumberFld;
	CDbColumn finishTimeFld;

	CDbColumn deviceNameFld;
	CDbColumn groupNumPerColFld;
	CDbColumn colShowNumFld;
	CDbColumn numPerGroupFld;
	CDbColumn constVmaxFld;
	CDbColumn constVminFld;
	CDbColumn constAmaxFld;
	CDbColumn constAminFld;
	CDbColumn vdisFld;
	CDbColumn vdisValFld;
	CDbColumn adisFld;
	CDbColumn adisValFld;
	CDbColumn timeDisFld;
	CDbColumn timeDisValFld;

	vector<CDbColumn> testInfoFlds;
};

