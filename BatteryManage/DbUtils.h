#pragma once

#include "CabBattery.h"
#include "Dbatterys.h"
#include "TestInfo.h"
#include "WorkProcInfo.h"
#include "PartBattery.h"
#include "BatStepInfo.h"

#include "BatCapInfo.h"

#include <iostream>
#include <vector>

using namespace  std;


extern const CString ERROR_PATH;

extern CString cabDbPaths[];

extern CString workEnames[];
extern CString workCnames[];

class CDbUtils
{
private:
	CDbUtils();
	~CDbUtils();

	static CDbUtils *dbUtils;

public:
	_CommandPtr pCommand;
	_RecordsetPtr pRecordset;
	_ConnectionPtr pConnection;

	static CDbUtils * GetInstance();

	BOOL CreateDatabases(CString cabSelStr);

	BOOL CreateDatabase(CString dbNameStr);

	BOOL CreateDbTables(CString dbNameStr);

	BOOL CreateDbTable(CString dbNameStr, CString tableNameStr, CString &createTestInfoStr);

	BOOL CDbUtils::ConnectToDatabase(CString dbNameStr);

	CString defaultBasePath;			//数据库目录的默认前缀

	BOOL SaveBatDataToDb(CabBattery *cabBattery);	// 将下位机获取的电池数据存至数据库


public:
	CString GetDefaultBasePath();
	
	vector<CDbattery> GetNoneCycleBatData(int cabId, int curBatteryId);
	vector<CDbattery> GetCycleBatData(int cabId, int curBatteryId);

	vector<CDbattery> GetNoneCycleBatData(CString filePath, int curBatteryId, int stepId);

	vector<CDbattery> GetNoneCycleDataByBatId(_bstr_t sqlStr, _bstr_t querySql, int curBatteryId);


	vector<CDbattery> GetCycleBatData(CString filePath, int curBatteryId, int stepId);

	vector<CDbattery> GetCycleDataByBatId(_bstr_t sqlStr, _bstr_t querySql, int curBatteryId);

	vector<CDbattery> GetBatDataById(CString dbPath, int batId);
	void SaveWorkProcToDb(int cabIdx, vector< vector<string>> strss);
	BOOL SaveTestInfoToDb(int cabIdx, TestInfo* testInfo);
	BOOL UpdateTestInfoToDb(int cabIdx, TestInfo* testInfo);
	static TestInfo GetTestInfo(CString dbPath);
	static vector<WorkProcInfo> GetWorkProcInfos(CString dataFilePath);
	static vector<CDbattery> GetWorkProcDatas(CString dataFilePath);


	static CDbattery CreateCdbatteryByRecordSet(_RecordsetPtr recordset);
	static CBatCapInfo CreateBatCapInfoByRecordSet(_RecordsetPtr recordset);
	static CPartBattery CreatePartBatteryByRecordSet(_RecordsetPtr recordset);


	static vector<CDbattery> GetSpecificStepInfos(CString dataFilePath, _bstr_t querySql);
	static vector<CPartBattery> GetPartBatData(CString dbFilePath, int StepId);
	static vector<CBatCapInfo> GetBatCapInfoById(CString dbFilePath, int stepId);
	//static vector<vector<CPartBattery>> GetPartBatData(CString dbFilePath);
	
	
	// GetStartStepInfos，GetAvgVolt，GetEndStepInfos即将被废弃,由GetBatStepInfos代替
	static vector<CDbattery> GetStartStepInfos(CString dataFilePath, int stepId);
	static vector<double> GetAvgVolt(CString dataFilePath, int stepId);
	static vector<CDbattery> GetEndStepInfos(CString dataFilePath, int stepId);
	static vector<CBatStepInfo> GetBatStepInfos(CString dataFilePath, int stepId);
	static CBatStepInfo CreateBatStepInfoByRecordSet(_RecordsetPtr recordset);
	static vector<CDbattery> GetBatCacvSetpInfos(CString dataFilePath, int param2);
};

