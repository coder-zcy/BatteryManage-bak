#pragma once
#include "DbColumn.h"

class DcabinetInfo
{
public:
	DcabinetInfo();
	~DcabinetInfo();

public:
	CDbColumn idFld;
	CDbColumn cabinetIdFld;
	CDbColumn deviceNameFld;
	CDbColumn deviceIdFld;
	CDbColumn groupNumPerColFld;
	CDbColumn colShowNumFld;
	CDbColumn numPerGroupFld;
	CDbColumn constVmaxFld;
	CDbColumn constVminFld;
	CDbColumn constAMaxFld;
	CDbColumn constAminFld;
	//CDbColumn constVchgFld;
	//CDbColumn omTestFld;
	//CDbColumn saveToFileFld;
	CDbColumn vdisFld;
	CDbColumn vdisValFld;
	CDbColumn adisFld;
	CDbColumn adisValFld;
	CDbColumn timeDisFld;
	CDbColumn timeDisValFld;
	//CDbColumn vshowMaxFld;
	//CDbColumn vshowMinFld;
	//CDbColumn svShowMaxFld;
	//CDbColumn svShowMinFld;
	//CDbColumn saShowMaxld;
	//CDbColumn saShowMinFld;
	//CDbColumn srShowMaxFld;
	//CDbColumn srShowMinFld;

	vector<CDbColumn> dcabinetInfoFlds;
};

