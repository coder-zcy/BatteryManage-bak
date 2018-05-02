#include "stdafx.h"
#include "DCabinetInfo.h"


DcabinetInfo::DcabinetInfo()
{
	idFld = CDbColumn("ID", NUM_TYPE, 10, false);
	cabinetIdFld = CDbColumn("CABINET_ID", INT_TYPE, 10, true);
	deviceNameFld = CDbColumn("DEVICE_NAME", STR_TYPE, 20, true);
	deviceIdFld = CDbColumn("DEVICE_ID", STR_TYPE, 10, true);
	groupNumPerColFld = CDbColumn("GROUPNUM_PERCOL", INT_TYPE, 10, true);
	colShowNumFld = CDbColumn("COL_SHOWNUM", INT_TYPE, 10, true);
	numPerGroupFld = CDbColumn("NUM_PERGROUP", INT_TYPE, 10, true);
	constVmaxFld = CDbColumn("CONST_VMAX", INT_TYPE, 20, true);
	constVminFld = CDbColumn("CONST_VMIN", INT_TYPE, 20, true);
	constAMaxFld = CDbColumn("CONST_AMAX", INT_TYPE, 20, true);
	constAminFld = CDbColumn("CONST_AMIN", INT_TYPE, 20, true);
	//constVchgFld = CDbColumn("CONST_VCHG", INT_TYPE, 20, true);
	//omTestFld = CDbColumn("OM_TEST", INT_TYPE, 20, true);
	//saveToFileFld = CDbColumn("SAVETO_FILE", INT_TYPE, 10, true);
	vdisFld = CDbColumn("VDIS", INT_TYPE, 10, true);
	vdisValFld = CDbColumn("VDIS_VAL", INT_TYPE, 10, true);
	adisFld = CDbColumn("ADIS", INT_TYPE, 10, true);
	adisValFld = CDbColumn("ADIS_VAL", INT_TYPE, 10, true);
	timeDisFld = CDbColumn("TIMEDIS", INT_TYPE, 10, true);
	timeDisValFld = CDbColumn("TIMEDIS_VAL", INT_TYPE, 10, true);
	//vshowMaxFld = CDbColumn("VSHOW_MAX", INT_TYPE, 10, true);
	//vshowMinFld = CDbColumn("VSHOW_MIN", INT_TYPE, 10, true);
	//svShowMaxFld = CDbColumn("SVSHOW_MAX", INT_TYPE, 10, true);
	//svShowMinFld = CDbColumn("SVSHOW_MIN", INT_TYPE, 10, true);
	//saShowMaxld = CDbColumn("SASHOW_MAX", INT_TYPE, 10, true);
	//saShowMinFld = CDbColumn("SASHOW_MIN", INT_TYPE, 10, true);
	//srShowMaxFld = CDbColumn("SRSHOW_MAX", INT_TYPE, 10, true);
	//srShowMinFld = CDbColumn("SRSHOW_MIN", INT_TYPE, 10, true);

	dcabinetInfoFlds.push_back(idFld);
	dcabinetInfoFlds.push_back(cabinetIdFld);
	dcabinetInfoFlds.push_back(deviceNameFld);
	dcabinetInfoFlds.push_back(deviceIdFld);
	dcabinetInfoFlds.push_back(groupNumPerColFld);
	dcabinetInfoFlds.push_back(colShowNumFld);
	dcabinetInfoFlds.push_back(constVmaxFld);
	dcabinetInfoFlds.push_back(constVminFld);
	dcabinetInfoFlds.push_back(constAMaxFld);
	dcabinetInfoFlds.push_back(constAminFld);
	//dcabinetInfoFlds.push_back(constVchgFld);
	//dcabinetInfoFlds.push_back(omTestFld);
	//dcabinetInfoFlds.push_back(saveToFileFld);
	dcabinetInfoFlds.push_back(vdisFld);
	dcabinetInfoFlds.push_back(vdisValFld);
	dcabinetInfoFlds.push_back(adisFld);
	dcabinetInfoFlds.push_back(adisValFld);
	dcabinetInfoFlds.push_back(timeDisFld);
	dcabinetInfoFlds.push_back(timeDisValFld);
	//dcabinetInfoFlds.push_back(vshowMaxFld);
	//dcabinetInfoFlds.push_back(vshowMinFld);
	//dcabinetInfoFlds.push_back(svShowMaxFld);
	//dcabinetInfoFlds.push_back(svShowMinFld);
	//dcabinetInfoFlds.push_back(saShowMaxld);
	//dcabinetInfoFlds.push_back(saShowMinFld);
	//dcabinetInfoFlds.push_back(srShowMaxFld);
	//dcabinetInfoFlds.push_back(srShowMinFld);
}


DcabinetInfo::~DcabinetInfo()
{

}
