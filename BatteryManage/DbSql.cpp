#include "stdafx.h"
#include "DbSql.h"

CDbSql* CDbSql::dbsql = new CDbSql();

CDbSql::CDbSql()
{
	createTestInfoStr = _T("\
		CREATE TABLE TEST_INFO(\
		ID AUTOINCREMENT PRIMARY KEY,\
		START_TIME datetime,\
		CABINET int,\
		SET_VALUE varchar(255),\
		INFORMATION varchar(255),\
		PC_NAME varchar(50),\
		CABINET_TAG varchar(50),\
		FILE_NAME varchar(255),\
		WORK_NAME varchar(50),\
		FINISH_FLAG int,\
		CELL_NUMBER int,\
		FINISH_TIME datetime,\
		DEVICE_NAME varchar(50),\
		GROUPNUM_PERCOL int,\
		COLSHOW_NUM int,\
		NUM_PERGROUP int,\
		CONST_VMAX int,\
		CONST_VMIN int,\
		CONST_AMAX int,\
		CONST_AMIN int,\
		VDIS int,\
		VDIS_VAL int,\
		ADIS int,\
		ADIS_VAL int,\
		TIMEDIS int,\
		TIMEDIS_VAL int\
		);"
		);
	createChlInfoStr = _T("\
	    CREATE TABLE CHANNEL_INFO(\
		ID AUTOINCREMENT PRIMARY KEY,\
		TESTITEM int,\
		CHANNEL_POSITION varchar(10),\
		CHANNEL int,\
		BATCH varchar(50),\
		BAT_CODE varchar(50),\
		CELL_TAG varchar(50)\
		);"
	);
	createChlStepStr = _T("\
		CREATE TABLE CHANNEL_STEP(\
		ID AUTOINCREMENT PRIMARY KEY,\
		TESTITEM int,\
		CHANNEL int,\
		STEP int,\
		CYCLE int,\
		STATION varchar(10),\
		SAVETIME datetime,\
		SETCURRENT double,\
		ATIME double,\
		CAPACITY double,\
		ENERGY double,\
		OPEN_V double,\
		MEAN_V double,\
		MID_V double,\
		END_V double,\
		END_C double,\
		C_CC_Time double,\
		C_CC_Capacity double,\
		C_CC_Ratio double,\
		Capacity_Spoilage double,\
		Discharge_Efficiency double,\
		Loss_Rate double,\
		V1_Time double,\
		V2_Time double,\
		V3_Time double,\
		V4_Time double,\
		V5_Time double,\
		V1_Capacity double,\
		V2_Capacity double,\
		V3_Capacity double,\
		V4_Capacity double,\
		V5_Capacity double\
		);"
	);
	createChlCurveStr = _T("\
	    CREATE TABLE CHANNEL_CURVE(\
		ID AUTOINCREMENT PRIMARY KEY,\
		TESTITEM int,\
		CHANNEL int,\
		STEP int,\
		CYCLE int,\
		NUM int,\
		STATION varchar(20),\
		TEST_TIME datetime,\
		ATIME double,\
		VOLTAGE double,\
		CURNT double,\
		CAPACITY double,\
		ENERGY double,\
		POWER double,\
		CABSTATE int,\
		BATSTATE int\
		);"
		);

	createWorkProcStr = _T("\
		CREATE TABLE WORKPROC_INFO(\
		ID AUTOINCREMENT PRIMARY KEY,\
		STEP_ID int,\
		STEP_NAME varchar(20),\
		STEP_TIME double,\
		CURNT double,\
		MAX_VOLT double,\
		MIN_VOLT double,\
		DELTAV double,\
		END_CURRENT double,\
		END_CAPACITY double,\
		START_STEP int,\
		END_STEP int,\
		LOOP_NUM int\
		);"
		);
	//createWorkProcStr = _T("\
	//	CREATE TABLE WORKPROC_INFO(\
	//	ID AUTOINCREMENT PRIMARY KEY,\
	//	STEP_ID int,\
	//	STEP_NAME varchar(20),\
	//	STEP_TIME double,\
	//	CURRENT double,\
	//	MAX_VOLT double,\
	//	MIN_VOLT double,\
	//	DELTAV double,\
	//	END_CURRENT double,\
	//	END_CAPACITY double\
	//	);"
	//	);
}

CDbSql* CDbSql::GetInstance()
{
	return dbsql;
}

