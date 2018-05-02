#pragma once
#include "stdafx.h"
#include "DTestInfo.h"

DtestInfo::DtestInfo()
{
	idFld = CDbColumn("ID", NUM_TYPE, 10, false);
	startTimeFld = CDbColumn("START_TIME", DATETIME_TYPE, 135, true);
	cabinetFld = CDbColumn("CABINET", INT_TYPE, 10, true);
	setValueFld = CDbColumn("SET_VALUE", INT_TYPE, 10, true);
	informationFld = CDbColumn("INFORMATION", STR_TYPE, 255, true);
	paNameFld = CDbColumn("PC_NAME", STR_TYPE, 50, true);
	cabinetTagFld = CDbColumn("CABINET_TAG", STR_TYPE, 50, true);
	fileNameFld = CDbColumn("FILE_NAME", STR_TYPE, 255, true);
	workNameFld = CDbColumn("WORK_NAME", STR_TYPE, 50, true);
	finishFlagFld = CDbColumn("FINISH_FLAG", INT_TYPE, 10, true);
	cellNumberFld = CDbColumn("CELL_NUMBER", INT_TYPE, 10, true);
	finishTimeFld = CDbColumn("FINISH_TIME", DATETIME_TYPE, 135, true);
	
	deviceNameFld = CDbColumn("DEVICE_NAME", STR_TYPE, 50, true);
	groupNumPerColFld = CDbColumn("GROUPNUM_PERCOL", INT_TYPE, 10, true);
	colShowNumFld = CDbColumn("COLSHOW_NUM", INT_TYPE, 10, true);
	numPerGroupFld = CDbColumn("NUM_PERGROUP", INT_TYPE, 10, true);
	constVmaxFld = CDbColumn("CONST_VMAX", INT_TYPE, 10, true);
	constVminFld = CDbColumn("CONST_VMIN", INT_TYPE, 10, true);
	constAmaxFld = CDbColumn("CONST_AMAX", INT_TYPE, 10, true);
	constAminFld = CDbColumn("CONST_AMIN", INT_TYPE, 10, true);
	vdisFld = CDbColumn("VDIS", INT_TYPE, 10, true);
	vdisValFld = CDbColumn("VDIS_VAL", INT_TYPE, 10, true);
	adisFld = CDbColumn("ADIS", INT_TYPE, 10, true);
	adisValFld = CDbColumn("ADIS_VAL", INT_TYPE, 10, true);
	timeDisFld = CDbColumn("TIMEDIS", INT_TYPE, 10, true);
	timeDisValFld = CDbColumn("TIMEDIS_VAL", INT_TYPE, 10, true);


	testInfoFlds.push_back(idFld);
	testInfoFlds.push_back(startTimeFld);
	testInfoFlds.push_back(cabinetFld);
	testInfoFlds.push_back(setValueFld);
	testInfoFlds.push_back(informationFld);
	testInfoFlds.push_back(paNameFld);
	testInfoFlds.push_back(cabinetTagFld);
	testInfoFlds.push_back(fileNameFld);
	testInfoFlds.push_back(workNameFld);
	testInfoFlds.push_back(finishFlagFld);
	testInfoFlds.push_back(cellNumberFld);
	testInfoFlds.push_back(finishTimeFld);

	testInfoFlds.push_back(deviceNameFld);
	testInfoFlds.push_back(groupNumPerColFld);
	testInfoFlds.push_back(colShowNumFld);
	testInfoFlds.push_back(numPerGroupFld);
	testInfoFlds.push_back(constVmaxFld);
	testInfoFlds.push_back(constVminFld);
	testInfoFlds.push_back(constAmaxFld);
	testInfoFlds.push_back(constAminFld);
	testInfoFlds.push_back(vdisFld);
	testInfoFlds.push_back(vdisValFld);
	testInfoFlds.push_back(adisFld);
	testInfoFlds.push_back(adisValFld);
	testInfoFlds.push_back(timeDisFld);
	testInfoFlds.push_back(timeDisValFld);

}

DtestInfo::~DtestInfo()
{

}
