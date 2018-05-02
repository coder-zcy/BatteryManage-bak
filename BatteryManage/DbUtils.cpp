#include "stdafx.h"
#include "DbUtils.h"

#include "TimeUtils.h"
#include "BatteryUtils.h"
#include "FileUtils.h"
#include "DbSql.h"
#include "LowerCabs.h"

#include "CabUtils.h"
#include <string>

using namespace std;


const int INVALIDE_NUM = -999999;

CDbUtils* CDbUtils::dbUtils = new CDbUtils();

const CString ERROR_PATH = _T("error");

CString cabDbPaths[MAX_CAB_NUM];
/*

恒流恒压充电	----	英文标识:C_CV,	工艺码	----	01
搁置			----	英文标识:REST,	工艺码	----	02
恒流放电		----	英文标识:D_CC,	工艺码	----	03
恒流充电		----	英文标识:C_CC,	工艺码	----	04

*/
CString workEnames[] = { L"", L"C_CV", L"REST", L"D_CC", L"C_CC" };
CString workCnames[] = { L"", L"恒流恒压充电", L"搁置", L"恒流放电", L"恒流充电" };

CDbUtils::CDbUtils()
{
	
}

CDbUtils::~CDbUtils()
{
	if (pConnection && pConnection->State)
	{
		delete pConnection;
		pConnection = NULL;
	}
}

BOOL CDbUtils::CreateDatabases(CString cabSelStr)
{
	// 获取默认Base路径
	CString defaultBasePath = GetDefaultBasePath();
	// 根据当前时间生成timepath
	CString timePath = CTimeUtils::CreateTimePath();

	for (int idx = 0; idx < cabSelStr.GetLength(); ++idx)
	{
		if (cabSelStr[idx] == '1' && SendStepFlags[idx])
		{
			CString cabIdStr;
			cabIdStr.Format(_T("%d"), idx + 1);
			
			cabIdStr= idx + 1 < 10 ? _T("0") + cabIdStr : cabIdStr;


			CString dbNameStr = defaultBasePath + _T("\\") + timePath + cabIdStr + _T(".mdb");
			
			//CString dbSqlPath = _T("");

			if (!CreateDatabase(dbNameStr))
			{
				//MessageBox(_T("创建数据库文件") + dbNameStr + _T("失败!"));
				return FALSE;
			}
			cabDbPaths[idx] = dbNameStr;
			if (!CreateDbTables(dbNameStr))
			{
				//MessageBox(_T("创建数据库表失败!"));
				return FALSE;
			}
		}
	}
	return TRUE;
}


CString CDbUtils::GetDefaultBasePath()
{
	CString cabInitPath = CBatteryUtils::GetConfigPath(_T("\\config\\init\\cabinet.ini"));
	
	CString tmp;

	WCHAR str[MAX_PATH_LENGTH];
	GetPrivateProfileString(_T("basepath"), _T("defBasePath"), _T("error"), str, MAX_PATH_LENGTH, cabInitPath);

	tmp = str;

	return tmp;

}

BOOL CDbUtils::CreateDatabase(CString dbNameStr)
{
	CString dbCatagory;
	int catagoryIdx = dbNameStr.ReverseFind('\\');
	dbCatagory = dbNameStr.Left(catagoryIdx + 1);

	if (!CFileUtils::CreateMuliteDirectory(dbCatagory))
		return FALSE;

	CString mdbConnStr = _T("Provider='Microsoft.JET.OLEDB.4.0';Data source = ") + dbNameStr;

	//CString mdbConnStr = _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=E:\\database\\battery\\BatteryManage2.mdb");
	try
	{
		HRESULT hr = S_OK;
		_CatalogPtr pCatalog = NULL;
		_bstr_t cnnstring(mdbConnStr);

		TESTHR(hr = pCatalog.CreateInstance(__uuidof (Catalog)));
		pCatalog->Create(cnnstring);
	}
	catch (_com_error e)
	{
		_bstr_t bstrDescription(e.Description());
		CString strErro = CString(_T("创建ACCEESS数据库出错: "))
			+ (LPCSTR)e.Description()
			+ CString(_T("Create ACCESS DB error: "))
			+ (LPCSTR)e.Description();
		AfxMessageBox(strErro);
		return FALSE;
	}
	//::CoUninitialize();
	return TRUE;
}

BOOL CDbUtils::CreateDbTables(CString dbNameStr)
{
	if (!ConnectToDatabase(dbNameStr))
		return FALSE;
	CDbSql *dbSql = CDbSql::GetInstance();
	if (!CreateDbTable(dbNameStr, _T("TEST_INFO"), dbSql->createTestInfoStr))
	{
		return FALSE;
	}
	if (!CreateDbTable(dbNameStr, _T("CHANNEL_STEP"), dbSql->createChlStepStr))
	{
		return FALSE;
	}
	if (!CreateDbTable(dbNameStr, _T("CHANNEL_INFO"), dbSql->createChlInfoStr))
	{
		return FALSE;
	}
	if (!CreateDbTable(dbNameStr, _T("CHANNEL_CURVE"), dbSql->createChlCurveStr))
	{
		return FALSE;
	}
	if (!CreateDbTable(dbNameStr, _T("WORKPROC_INFO"), dbSql->createWorkProcStr))
	{
		return FALSE;
	}
	//::CoUninitialize();
	return TRUE;
}

BOOL CDbUtils::CreateDbTable(CString dbNameStr, CString tableNameStr, CString &createTestInfoStr)
{
	CString strConn;
	if (tableNameStr != _T("") && dbNameStr != _T(""))
	{
		_CatalogPtr m_pCatalog = NULL;
		_TablePtr m_pTable = NULL;
		dbNameStr = _T("Provider='Microsoft.JET.OLEDB.4.0';Data source = ") + dbNameStr;

		try
		{
			m_pCatalog.CreateInstance(__uuidof(Catalog));
			m_pCatalog->PutActiveConnection(_bstr_t(dbNameStr));
			int tableCount = m_pCatalog->Tables->Count;
			int i = 0;
			while (i < tableCount)
			{
				m_pTable = (_TablePtr)m_pCatalog->Tables->GetItem((long)i);
				CString tableName = (wchar_t *)_bstr_t(m_pTable->Name);
				if (tableName == tableNameStr)
				{
					AfxMessageBox(_T("该表已经存在!"));
					return FALSE;
				}
				i++;
			}
		}
		catch (_com_error &e)
		{
			return FALSE;
		}

		_ConnectionPtr m_pConnection;
		_variant_t RecordsAffected;
		try
		{
			m_pConnection.CreateInstance(__uuidof(Connection));


			m_pConnection->Open((_bstr_t)dbNameStr, "", "", adModeUnknown);
		}
		catch (_com_error e)
		{
			CString errormessage;
			errormessage.Format(_T("连接数据库失败!\r错误信息:%s"), e.ErrorMessage());
			AfxMessageBox(errormessage);
			return FALSE;
		}
		try
		{
			m_pConnection->Execute(_bstr_t(createTestInfoStr), &RecordsAffected, adCmdText);
			if (m_pConnection->State)
				m_pConnection->Close();
		}
		catch (_com_error &e)
		{
			AfxMessageBox(e.Description());
			return FALSE;
		}
	}
	return TRUE;
}


BOOL CDbUtils::ConnectToDatabase(CString dbNameStr)
{
	_bstr_t sqlStr = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" +
		(_bstr_t)dbNameStr;
	try
	{
		//先创建连接实例
		HRESULT hr = pConnection.CreateInstance(__uuidof(Connection));//创建Connection对象
		if (SUCCEEDED(hr))
		{
			// 打开本地Access库Demo.mdb
			hr = pConnection->Open(sqlStr, "", "", adModeUnknown);
			return TRUE;
		}
	}
	catch (_com_error e)///捕捉异常
	{
		CString strMsg;
		strMsg.Format(_T("错误描述：%s\n错误消息%s"),
			(LPCTSTR)e.Description(),
			(LPCTSTR)e.ErrorMessage());
		AfxMessageBox(strMsg);
		return FALSE;
	}
	return FALSE;
}

CDbUtils * CDbUtils::GetInstance()
{
	return dbUtils;
}

/*
table名:			CHANNEL_CURVE
ID				:	主键
TESTITEM		:	暂定为机柜编号
CHANNEL			:	数字编号
STEP			:	工步编号
CYCLE			:	是否循环,无循环则为0,有循环则为相应的循环编号
NUM				:	还不清楚,暂定为0
STATION			:	状态,C_CC,REST等等
TEST_TIME		:	测试时间,datetime类型
ATIME			:	电池状态返回的时间
VOLTAGE			:	电压
CURNT			:   电流
CAPACITY		:	容量
ENERGY			:	能量,暂不清楚
POWER			:	电量,暂不清楚
CABSTATE		:	机柜状态
BATSTATE		:	电池状态

电量和容量的区别是什么

目前只要收到数据就进行存储

zcy-2017-8-27
*/

BOOL CDbUtils::SaveBatDataToDb(CabBattery *cabBattery)
{
	if (cabBattery == NULL)
		return FALSE;

	CabBattery cabBatteryBak = *cabBattery;
	int cabId = cabBatteryBak.cabId;
	int stationId = cabBatteryBak.cabState;
	int workId = cabBatteryBak.workId;
	int stepId = cabBatteryBak.stepId;
	int cycleId = cabBatteryBak.cycleId;

	CString cabDbName = cabDbPaths[cabId - 1];

	_bstr_t sqlStr = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" +
	(_bstr_t)cabDbName;

	_bstr_t cabIdStr = cabIdsCstr[cabId-1];
	_bstr_t querySql = "select * from CHANNEL_CURVE";


	try
	{
		//先创建连接实例
		HRESULT hr = pConnection.CreateInstance(__uuidof(Connection));//创建Connection对象
		
		if (SUCCEEDED(hr))
		{
			// 打开本地Access库Demo.mdb
			hr = pConnection->Open(sqlStr, "", "", adModeUnknown);
		}
		else
		{
			CString errormessage;
			errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
			AfxMessageBox(errormessage);
			return FALSE;
		}
		if (SUCCEEDED(hr))
		{
			pRecordset.CreateInstance(__uuidof(Recordset));
			pRecordset->Open(querySql,		 // 查询DemoTable表中所有字段
				pConnection.GetInterfacePtr(),			// 获取库连接的IDispatch指针
				adOpenStatic,
				adLockOptimistic,
				adCmdText);
		}
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
	}
	int count = 0;
	try
	{
		count = pRecordset->GetRecordCount();
	}
	catch (_com_error e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s"), e.ErrorMessage());
		AfxMessageBox(errormessage);
	}
	
	try
	{
		for (int idx = 0; idx < cabBattery->batterys.size(); ++ idx)
		{
			pRecordset->AddNew();
			pRecordset->PutCollect("TESTITEM", _variant_t(cabId));
			pRecordset->PutCollect("CHANNEL", _variant_t(idx + 1));
			pRecordset->PutCollect("STEP", _variant_t(stepId));
			pRecordset->PutCollect("CYCLE", _variant_t(cycleId));
			pRecordset->PutCollect("NUM", _variant_t(0));
			pRecordset->PutCollect("STATION", _variant_t(workEnames[workId]));
			//pRecordset->PutCollect("TEST_TIME", _variant_t());

			pRecordset->PutCollect("ATIME", _variant_t(cabBattery->batterys[idx].timeVal));
			pRecordset->PutCollect("VOLTAGE", _variant_t(cabBattery->batterys[idx].voltVal));
			pRecordset->PutCollect("CURNT", _variant_t(cabBattery->batterys[idx].currentVal));
			pRecordset->PutCollect("CAPACITY", _variant_t(cabBattery->batterys[idx].capacityVal));
			pRecordset->PutCollect("ENERGY", _variant_t(cabBattery->batterys[idx].energyVal));
			pRecordset->PutCollect("POWER", _variant_t(0));
			pRecordset->PutCollect("CABSTATE", _variant_t(cabBattery->cabState));
			pRecordset->PutCollect("BATSTATE", _variant_t(cabBattery->batterys[idx].batStatVal));

			pRecordset->Update();
		}
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
	}

	return TRUE;
}

vector<CDbattery> CDbUtils::GetNoneCycleBatData(int cabId, int curBatteryId)
{
	CString cabDbName = cabDbPaths[cabId - 1];
	//CString cabDbName = L"D:\\work\\battery\\data\\2017_09\\09_142729_01.mdb";
	_bstr_t sqlStr = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" +
		(_bstr_t)cabDbName;

	//_bstr_t querySql = "select * from CHANNEL_CURVE where CYCLE = 0 and CHANNEL = " + (_bstr_t)curBatteryId 
	//	+ " order by STEP ASC";

	_bstr_t	querySql = "select * from CHANNEL_CURVE WHERE CYCLE = 0 and CHANNEL = " + (_bstr_t)curBatteryId
		+ " and ATIME <> " + (_bstr_t)INVALIDE_NUM + " order by STEP ASC, ATIME ASC;";

	return GetNoneCycleDataByBatId(sqlStr, querySql, curBatteryId);

}

vector<CDbattery> CDbUtils::GetNoneCycleBatData(CString filePath, int curBatteryId, int stepId)
{
	//CString cabDbName = L"D:\\work\\battery\\data\\2017_09\\09_142729_01.mdb";
	_bstr_t sqlStr = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" +
		(_bstr_t)filePath;
	_bstr_t querySql;
	if (stepId == 0)
		querySql = "select * from CHANNEL_CURVE WHERE CYCLE = 0 and CHANNEL = " + (_bstr_t)curBatteryId
		+ " and ATIME <> " + (_bstr_t)INVALIDE_NUM + " order by STEP ASC, ATIME ASC;";
	else
		querySql = "select * from CHANNEL_CURVE WHERE CYCLE = 0 and CHANNEL = " + (_bstr_t)curBatteryId
		+ " and STEP = " + (_bstr_t)stepId + " and ATIME <> " + (_bstr_t)INVALIDE_NUM + " order by ID ASC, ATIME ASC;";

	return GetNoneCycleDataByBatId(sqlStr, querySql, curBatteryId);
}

vector<CDbattery> CDbUtils::GetNoneCycleDataByBatId(_bstr_t sqlStr, _bstr_t querySql, int curBatteryId)
{

	vector<CDbattery> result;
	result.clear();

	HRESULT hr;
	_RecordsetPtr recordset;
	_ConnectionPtr connection;

	try
	{
		//先创建连接实例
		hr = connection.CreateInstance(__uuidof(Connection));//创建Connection对象

		if (SUCCEEDED(hr))
		{
			// 打开本地Access库Demo.mdb
			hr = connection->Open(sqlStr, "", "", adModeUnknown);
		}
		else
		{
			CString errormessage;
			errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
			AfxMessageBox(errormessage);
			return result;
		}

		if (SUCCEEDED(hr))
		{
			recordset.CreateInstance(__uuidof(Recordset));
			hr = recordset->Open(querySql,		 // 查询DemoTable表中所有字段
				connection.GetInterfacePtr(),			// 获取库连接的IDispatch指针
				adOpenStatic,
				adLockOptimistic,
				adCmdText);
		}
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
		return result;
	}
	int count = 0;
	try
	{
		count = recordset->GetRecordCount();
	}
	catch (_com_error e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s"), e.ErrorMessage());
		AfxMessageBox(errormessage);
		return result;
	}
	if (count == 0)
		return result;
	try
	{
		_variant_t var;
		CDbattery dbattery;
		recordset->MoveFirst();
		while (!recordset->ADOBOF && !recordset->ADOEOF)
		{
			var = recordset->GetCollect(_T("ID"));
			if (var.vt != VT_NULL)
				dbattery.id = int(var);

			var = recordset->GetCollect(_T("TESTITEM"));
			dbattery.cabId = var.vt != NULL ? int(var) : 0;

			var = recordset->GetCollect(_T("CHANNEL"));
			dbattery.batId = var.vt != NULL ? int(var) : 0;

			var = recordset->GetCollect(_T("STEP"));
			dbattery.stepId = var.vt != NULL ? int(var) : 0;

			var = recordset->GetCollect(_T("CYCLE"));
			dbattery.cycleId = var.vt != NULL ? int(var) : 0;

			var = recordset->GetCollect(_T("NUM"));
			dbattery.num = var.vt != NULL ? int(var) : 0;

			var = recordset->GetCollect(_T("STATION"));
			dbattery.workEname = var.vt != NULL ? (LPCTSTR)_bstr_t(var) : L"";

			//var = pRecordset->GetCollect(_T("TESTTIME"));
			//dbattery.testTime = var.vt != NULL ? CTime(var) : ;

			var = recordset->GetCollect(_T("ATIME"));
			dbattery.atime = var.vt != NULL ? double(var) : 0;

			var = recordset->GetCollect(_T("VOLTAGE"));
			dbattery.voltage = var.vt != NULL ? double(var) : 0;

			var = recordset->GetCollect(_T("CURNT"));
			dbattery.curnt = var.vt != NULL ? double(var) : 0;

			var = recordset->GetCollect(_T("CAPACITY"));
			dbattery.capacity = var.vt != NULL ? double(var) : 0;

			var = recordset->GetCollect(_T("ENERGY"));
			dbattery.energy = var.vt != NULL ? double(var) : 0;

			var = recordset->GetCollect(_T("POWER"));
			dbattery.power = var.vt != NULL ? double(var) : 0;

			result.push_back(dbattery);

			recordset->MoveNext();
		}
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
		return result;
	}

	return result;
}

vector<CDbattery> CDbUtils::GetCycleBatData(int cabId, int curBatteryId)
{
	CString cabDbName = cabDbPaths[cabId - 1];
	//CString cabDbName = L"D:\\work\\battery\\data\\2017_09\\09_142729_01.mdb";
	_bstr_t sqlStr = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" +
		(_bstr_t)cabDbName;
	_bstr_t querySql = "select * from CHANNEL_CURVE where CYCLE > 0 and CHANNEL = "
		+ (_bstr_t)curBatteryId + " and ATIME <> " + (_bstr_t)INVALIDE_NUM + " order by STEP ASC, ATIME ASC";

	return GetCycleDataByBatId(sqlStr, querySql, curBatteryId);

}

vector<CDbattery> CDbUtils::GetCycleBatData(CString filePath, int curBatteryId, int stepId)
{
	_bstr_t sqlStr = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" +
		(_bstr_t)filePath;
	_bstr_t querySql;
	if (stepId == 0)
		querySql = "select * from CHANNEL_CURVE where CYCLE > 0 and CHANNEL = "
		+ (_bstr_t)curBatteryId + " and ATIME <> " + (_bstr_t)INVALIDE_NUM + " order by STEP ASC, ATIME ASC";
	else
		querySql = "select * from CHANNEL_CURVE where CYCLE > 0 and CHANNEL = "
		+ (_bstr_t)curBatteryId + " and ATIME <> " + (_bstr_t)INVALIDE_NUM + " and STEP = " + (_bstr_t)stepId + " order by ID ASC, ATIME ASC";

	return GetCycleDataByBatId(sqlStr, querySql, curBatteryId);
}

vector<CDbattery> CDbUtils::GetCycleDataByBatId(_bstr_t sqlStr, _bstr_t querySql, int curBatteryId)
{
	vector<CDbattery> result;
	result.clear();
	HRESULT hr;
	_RecordsetPtr recordset;
	_ConnectionPtr connection;

	try
	{
		//先创建连接实例
		hr = connection.CreateInstance(__uuidof(Connection));//创建Connection对象

		if (SUCCEEDED(hr))
		{
			// 打开本地Access库Demo.mdb
			hr = connection->Open(sqlStr, "", "", adModeUnknown);
		}
		else
		{
			CString errormessage;
			errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
			AfxMessageBox(errormessage);
			return result;
		}
		if (SUCCEEDED(hr))
		{
			recordset.CreateInstance(__uuidof(Recordset));
			recordset->Open(querySql,		 // 查询DemoTable表中所有字段
				connection.GetInterfacePtr(),			// 获取库连接的IDispatch指针
				adOpenStatic,
				adLockOptimistic,
				adCmdText);
		}
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
		return result;
	}
	int count = 0;
	try
	{
		count = recordset->GetRecordCount();
	}
	catch (_com_error e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s"), e.ErrorMessage());
		AfxMessageBox(errormessage);
		return result;
	}

	if (count == 0)
	{
		return result;
	}
	try
	{
		_variant_t var;
		CDbattery dbattery;
		recordset->MoveFirst();
		while (!recordset->ADOBOF && !recordset->ADOEOF)
		{
			var = recordset->GetCollect(_T("ID"));
			if (var.vt != VT_NULL)
				dbattery.id = int(var);

			var = recordset->GetCollect(_T("TESTITEM"));
			dbattery.cabId = var.vt != NULL ? int(var) : 0;

			var = recordset->GetCollect(_T("CHANNEL"));
			dbattery.batId = var.vt != NULL ? int(var) : 0;

			var = recordset->GetCollect(_T("STEP"));
			dbattery.stepId = var.vt != NULL ? int(var) : 0;

			var = recordset->GetCollect(_T("CYCLE"));
			dbattery.cycleId = var.vt != NULL ? int(var) : 0;

			var = recordset->GetCollect(_T("NUM"));
			dbattery.num = var.vt != NULL ? int(var) : 0;

			var = recordset->GetCollect(_T("STATION"));
			dbattery.workEname = var.vt != NULL ? (LPCTSTR)_bstr_t(var) : L"";

			//var = pRecordset->GetCollect(_T("TESTTIME"));
			//dbattery.testTime = var.vt != NULL ? CTime(var) : ;

			var = recordset->GetCollect(_T("ATIME"));
			dbattery.atime = var.vt != NULL ? double(var) : 0;

			var = recordset->GetCollect(_T("VOLTAGE"));
			dbattery.voltage = var.vt != NULL ? double(var) : 0;

			var = recordset->GetCollect(_T("CURNT"));
			dbattery.curnt = var.vt != NULL ? double(var) : 0;

			var = recordset->GetCollect(_T("CAPACITY"));
			dbattery.capacity = var.vt != NULL ? double(var) : 0;

			var = recordset->GetCollect(_T("ENERGY"));
			dbattery.energy = var.vt != NULL ? double(var) : 0;

			var = recordset->GetCollect(_T("POWER"));
			dbattery.power = var.vt != NULL ? double(var) : 0;

			result.push_back(dbattery);

			recordset->MoveNext();
		}
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
		return result;
	}

	return result;
}

vector<CDbattery> CDbUtils::GetBatDataById(CString dbPath, int batId)
{

	_bstr_t sqlStr = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" +
		(_bstr_t)dbPath;

	_bstr_t querySql = "select * from CHANNEL_CURVE where CHANNEL = "
		+ (_bstr_t)batId + " order by ID ASC";

	vector<CDbattery> result;
	result.clear();
	HRESULT hr;
	_RecordsetPtr recordset;
	_ConnectionPtr connection;

	try
	{
		//先创建连接实例
		hr = connection.CreateInstance(__uuidof(Connection));//创建Connection对象

		if (SUCCEEDED(hr))
		{
			// 打开本地Access库Demo.mdb
			hr = connection->Open(sqlStr, "", "", adModeUnknown);
		}
		else
		{
			CString errormessage;
			errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
			AfxMessageBox(errormessage);
			return result;
		}
		if (SUCCEEDED(hr))
		{
			recordset.CreateInstance(__uuidof(Recordset));
			recordset->Open(querySql,		 // 查询DemoTable表中所有字段
				connection.GetInterfacePtr(),			// 获取库连接的IDispatch指针
				adOpenStatic,
				adLockOptimistic,
				adCmdText);
		}
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
		return result;
	}
	int count = 0;
	try
	{
		count = recordset->GetRecordCount();
	}
	catch (_com_error e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s"), e.ErrorMessage());
		AfxMessageBox(errormessage);
		return result;
	}

	if (count == 0)
	{
		return result;
	}
	try
	{
		_variant_t var;
		CDbattery dbattery;
		recordset->MoveFirst();
		while (!recordset->ADOBOF && !recordset->ADOEOF)
		{
			var = recordset->GetCollect(_T("ID"));
			if (var.vt != VT_NULL)
				dbattery.id = int(var);

			var = recordset->GetCollect(_T("TESTITEM"));
			dbattery.cabId = var.vt != NULL ? int(var) : 0;

			var = recordset->GetCollect(_T("CHANNEL"));
			dbattery.batId = var.vt != NULL ? int(var) : 0;

			var = recordset->GetCollect(_T("STEP"));
			dbattery.stepId = var.vt != NULL ? int(var) : 0;

			var = recordset->GetCollect(_T("CYCLE"));
			dbattery.cycleId = var.vt != NULL ? int(var) : 0;

			var = recordset->GetCollect(_T("NUM"));
			dbattery.num = var.vt != NULL ? int(var) : 0;

			var = recordset->GetCollect(_T("STATION"));
			dbattery.workEname = var.vt != NULL ? (LPCTSTR)_bstr_t(var) : L"";

			//var = pRecordset->GetCollect(_T("TESTTIME"));
			//dbattery.testTime = var.vt != NULL ? CTime(var) : ;

			var = recordset->GetCollect(_T("ATIME"));
			dbattery.atime = var.vt != NULL ? double(var) : 0;

			var = recordset->GetCollect(_T("VOLTAGE"));
			dbattery.voltage = var.vt != NULL ? double(var) : 0;

			var = recordset->GetCollect(_T("CURNT"));
			dbattery.curnt = var.vt != NULL ? double(var) : 0;

			var = recordset->GetCollect(_T("CAPACITY"));
			dbattery.capacity = var.vt != NULL ? double(var) : 0;

			var = recordset->GetCollect(_T("ENERGY"));
			dbattery.energy = var.vt != NULL ? double(var) : 0;

			var = recordset->GetCollect(_T("POWER"));
			dbattery.power = var.vt != NULL ? double(var) : 0;

			var = recordset->GetCollect(_T("CABSTATE"));
			dbattery.cabState = var.vt != NULL ? int(var) : 0;

			var = recordset->GetCollect(_T("BATSTATE"));
			dbattery.batState = var.vt != NULL ? int(var) : 0;

			result.push_back(dbattery);

			recordset->MoveNext();
		}
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
		return result;
	}

	return result;
}

void CDbUtils::SaveWorkProcToDb(int cabIdx, vector< vector<string>> strss)
{
	if (strss.size() == 0)
		return;

	CString cabDbName = cabDbPaths[cabIdx];

	_bstr_t sqlStr = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" +
		(_bstr_t)cabDbName;

	_bstr_t cabIdStr = cabIdsCstr[cabIdx];
	_bstr_t querySql = "select * from WORKPROC_INFO";

	try
	{
		//先创建连接实例
		HRESULT hr = pConnection.CreateInstance(__uuidof(Connection));//创建Connection对象

		if (SUCCEEDED(hr))
		{
			// 打开本地Access库Demo.mdb
			hr = pConnection->Open(sqlStr, "", "", adModeUnknown);
		}
		else
		{
			CString errormessage;
			errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
			AfxMessageBox(errormessage);
			return;
		}
		if (SUCCEEDED(hr))
		{
			pRecordset.CreateInstance(__uuidof(Recordset));
			pRecordset->Open(querySql,		 // 查询DemoTable表中所有字段
				pConnection.GetInterfacePtr(),			// 获取库连接的IDispatch指针
				adOpenStatic,
				adLockOptimistic,
				adCmdText);
		}
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
	}
	int count = 0;
	try
	{
		count = pRecordset->GetRecordCount();
	}
	catch (_com_error e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s"), e.ErrorMessage());
		AfxMessageBox(errormessage);
	}

	try
	{
		int length = strss[0].size();
		for (int idx = 0; idx < strss.size(); ++idx)
		{
			pRecordset->AddNew();

			pRecordset->PutCollect("STEP_ID", _variant_t(stoi(strss[idx][length-1])));
			pRecordset->PutCollect("STEP_NAME", _variant_t(strss[idx][0].c_str()));
			pRecordset->PutCollect("STEP_TIME", _variant_t(strss[idx][1].c_str()));
			pRecordset->PutCollect("CURNT", _variant_t(strss[idx][2].c_str()));
			pRecordset->PutCollect("MAX_VOLT", _variant_t(strss[idx][3].c_str()));
			pRecordset->PutCollect("MIN_VOLT", _variant_t(strss[idx][4].c_str()));
			pRecordset->PutCollect("DELTAV", _variant_t(strss[idx][5].c_str()));
			pRecordset->PutCollect("END_CURRENT", _variant_t(strss[idx][6].c_str()));
			pRecordset->PutCollect("END_CAPACITY", _variant_t(strss[idx][7].c_str()));
			pRecordset->PutCollect("START_STEP", _variant_t(strss[idx][2].c_str()));
			pRecordset->PutCollect("END_STEP", _variant_t(strss[idx][4].c_str()));
			pRecordset->PutCollect("LOOP_NUM", _variant_t(strss[idx][6].c_str()));
			
			pRecordset->Update();
		}
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
	}
}

BOOL CDbUtils::SaveTestInfoToDb(int cabIdx, TestInfo* testInfo)
{
	CString cabDbName = cabDbPaths[cabIdx];

	_bstr_t sqlStr = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" +
		(_bstr_t)cabDbName;

	_bstr_t cabIdStr = cabIdsCstr[cabIdx];
	_bstr_t querySql = "select * from TEST_INFO";

	try
	{
		//先创建连接实例
		HRESULT hr = pConnection.CreateInstance(__uuidof(Connection));//创建Connection对象

		if (SUCCEEDED(hr))
		{
			// 打开本地Access库Demo.mdb
			hr = pConnection->Open(sqlStr, "", "", adModeUnknown);
		}
		else
		{
			CString errormessage;
			errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
			AfxMessageBox(errormessage);
			return FALSE;
		}
		if (SUCCEEDED(hr))
		{
			pRecordset.CreateInstance(__uuidof(Recordset));
			pRecordset->Open(querySql,		 // 查询DemoTable表中所有字段
				pConnection.GetInterfacePtr(),			// 获取库连接的IDispatch指针
				adOpenStatic,
				adLockOptimistic,
				adCmdText);
		}
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
		return FALSE;
	}
	int count = 0;
	try
	{
		count = pRecordset->GetRecordCount();
	}
	catch (_com_error e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s"), e.ErrorMessage());
		AfxMessageBox(errormessage);
		return FALSE;
	}
	string startTimeStr, finishTimeStr;
	try
	{
			pRecordset->AddNew();
			pRecordset->PutCollect("START_TIME", _variant_t(testInfo->startTime.c_str()));
			pRecordset->PutCollect("CABINET", _variant_t(testInfo->cabinet));
			pRecordset->PutCollect("SET_VALUE", _variant_t(testInfo->setValue));
			pRecordset->PutCollect("INFORMATION", _variant_t(testInfo->information.c_str()));
			pRecordset->PutCollect("PC_NAME", _variant_t(testInfo->pcName.c_str()));
			pRecordset->PutCollect("CABINET_TAG", _variant_t(testInfo->cabinetTag.c_str()));
			pRecordset->PutCollect("FILE_NAME", _variant_t(testInfo->fileName.c_str()));
			pRecordset->PutCollect("WORK_NAME", _variant_t(testInfo->workName.c_str()));
			pRecordset->PutCollect("FINISH_FLAG", _variant_t(testInfo->finishFlag));
			pRecordset->PutCollect("CELL_NUMBER", _variant_t(testInfo->cellNumber));
			pRecordset->PutCollect("FINISH_TIME", _variant_t(testInfo->finishTime.c_str()));
			pRecordset->PutCollect("DEVICE_NAME", _variant_t(testInfo->deviceName.c_str()));
			pRecordset->PutCollect("GROUPNUM_PERCOL", _variant_t(testInfo->groupNumPerCol));
			pRecordset->PutCollect("COLSHOW_NUM", _variant_t(testInfo->colShowNum));
			pRecordset->PutCollect("NUM_PERGROUP", _variant_t(testInfo->numPerGroup));
			pRecordset->PutCollect("CONST_VMAX", _variant_t(testInfo->constVmax));
			pRecordset->PutCollect("CONST_VMIN", _variant_t(testInfo->constVmin));
			pRecordset->PutCollect("CONST_AMAX", _variant_t(testInfo->constAmax));
			pRecordset->PutCollect("CONST_AMIN", _variant_t(testInfo->constAmin));
			pRecordset->PutCollect("VDIS", _variant_t(testInfo->vdis));
			pRecordset->PutCollect("VDIS_VAL", _variant_t(testInfo->vdisVal));
			pRecordset->PutCollect("ADIS", _variant_t(testInfo->adis));
			pRecordset->PutCollect("ADIS_VAL", _variant_t(testInfo->adisVal));
			pRecordset->PutCollect("TIMEDIS", _variant_t(testInfo->timeDis));
			pRecordset->PutCollect("TIMEDIS_VAL", _variant_t(testInfo->timeDisVal));

			pRecordset->Update();
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
		return FALSE;
	}

	return TRUE;
}

BOOL CDbUtils::UpdateTestInfoToDb(int cabIdx, TestInfo* testInfo)
{
	CString cabDbName = cabDbPaths[cabIdx];

	_bstr_t sqlStr = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" +
		(_bstr_t)cabDbName;

	_bstr_t cabIdStr = cabIdsCstr[cabIdx];
	_bstr_t querySql = "select * from TEST_INFO";

	try
	{
		//先创建连接实例
		HRESULT hr = pConnection.CreateInstance(__uuidof(Connection));//创建Connection对象

		if (SUCCEEDED(hr))
		{
			// 打开本地Access库Demo.mdb
			hr = pConnection->Open(sqlStr, "", "", adModeUnknown);
		}
		else
		{
			CString errormessage;
			errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
			AfxMessageBox(errormessage);
			return FALSE;
		}
		if (SUCCEEDED(hr))
		{
			pRecordset.CreateInstance(__uuidof(Recordset));
			pRecordset->Open(querySql,		 // 查询DemoTable表中所有字段
				pConnection.GetInterfacePtr(),			// 获取库连接的IDispatch指针
				adOpenStatic,
				adLockOptimistic,
				adCmdText);
		}
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
		return FALSE;
	}
	int count = 0;
	try
	{
		count = pRecordset->GetRecordCount();
		if (count <= 0)
			return FALSE;
	}
	catch (_com_error e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s"), e.ErrorMessage());
		AfxMessageBox(errormessage);
		return FALSE;
	}

	string startTimeStr, finishTimeStr;
	try
	{
		pRecordset->MoveFirst();
		pRecordset->PutCollect("START_TIME", _variant_t(testInfo->startTime.c_str()));
		pRecordset->PutCollect("CABINET", _variant_t(testInfo->cabinet));
		pRecordset->PutCollect("SET_VALUE", _variant_t(testInfo->setValue));
		pRecordset->PutCollect("INFORMATION", _variant_t(testInfo->information.c_str()));
		pRecordset->PutCollect("PC_NAME", _variant_t(testInfo->pcName.c_str()));
		pRecordset->PutCollect("CABINET_TAG", _variant_t(testInfo->cabinetTag.c_str()));
		pRecordset->PutCollect("FILE_NAME", _variant_t(testInfo->fileName.c_str()));
		pRecordset->PutCollect("WORK_NAME", _variant_t(testInfo->workName.c_str()));
		pRecordset->PutCollect("FINISH_FLAG", _variant_t(testInfo->finishFlag));
		pRecordset->PutCollect("CELL_NUMBER", _variant_t(testInfo->cellNumber));
		pRecordset->PutCollect("FINISH_TIME", _variant_t(testInfo->finishTime.c_str()));
		pRecordset->PutCollect("DEVICE_NAME", _variant_t(testInfo->deviceName.c_str()));
		pRecordset->PutCollect("GROUPNUM_PERCOL", _variant_t(testInfo->groupNumPerCol));
		pRecordset->PutCollect("COLSHOW_NUM", _variant_t(testInfo->colShowNum));
		pRecordset->PutCollect("NUM_PERGROUP", _variant_t(testInfo->numPerGroup));
		pRecordset->PutCollect("CONST_VMAX", _variant_t(testInfo->constVmax));
		pRecordset->PutCollect("CONST_VMIN", _variant_t(testInfo->constVmin));
		pRecordset->PutCollect("CONST_AMAX", _variant_t(testInfo->constAmax));
		pRecordset->PutCollect("CONST_AMIN", _variant_t(testInfo->constAmin));
		pRecordset->PutCollect("VDIS", _variant_t(testInfo->vdis));
		pRecordset->PutCollect("VDIS_VAL", _variant_t(testInfo->vdisVal));
		pRecordset->PutCollect("ADIS", _variant_t(testInfo->adis));
		pRecordset->PutCollect("ADIS_VAL", _variant_t(testInfo->adisVal));
		pRecordset->PutCollect("TIMEDIS", _variant_t(testInfo->timeDis));
		pRecordset->PutCollect("TIMEDIS_VAL", _variant_t(testInfo->timeDisVal));

		pRecordset->Update();
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
		return FALSE;
	}

	return TRUE;
}

TestInfo CDbUtils::GetTestInfo(CString dbPath)
{
	_bstr_t sqlStr = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" +
		(_bstr_t)dbPath;

	_bstr_t querySql = "select * from TEST_INFO";
	
	TestInfo testInfo;

	HRESULT hr;
	_RecordsetPtr recordset;
	_ConnectionPtr connection;
	try
	{
		//先创建连接实例
		hr = connection.CreateInstance(__uuidof(Connection));//创建Connection对象

		if (SUCCEEDED(hr))
		{
			// 打开本地Access库Demo.mdb
			hr = connection->Open(sqlStr, "", "", adModeUnknown);
		}
		else
		{
			CString errormessage;
			errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
			AfxMessageBox(errormessage);
			return testInfo;
		}
		if (SUCCEEDED(hr))
		{
			recordset.CreateInstance(__uuidof(Recordset));
			recordset->Open(querySql,		 // 查询DemoTable表中所有字段
				connection.GetInterfacePtr(),			// 获取库连接的IDispatch指针
				adOpenStatic,
				adLockOptimistic,
				adCmdText);
		}
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
		return testInfo;
	}
	int count = 0;
	try
	{
		count = recordset->GetRecordCount();
	}
	catch (_com_error e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s"), e.ErrorMessage());
		AfxMessageBox(errormessage);
		return testInfo;
	}

	if (count == 0)
	{
		return testInfo;
	}
	try
	{
		_variant_t var;
		recordset->MoveFirst();
		testInfo.isValid = TRUE;

		var = recordset->GetCollect(_T("START_TIME"));
		testInfo.startTime = var.vt != NULL ? (std::string)_bstr_t(var) : "";

		var = recordset->GetCollect(_T("CABINET"));
		testInfo.cabinet = var.vt != NULL ? int(var) : 0;

		var = recordset->GetCollect(_T("SET_VALUE"));
		testInfo.setValue = var.vt != NULL ? int(var) : 0;

		var = recordset->GetCollect(_T("INFORMATION"));
		testInfo.information = var.vt != NULL ? (std::string)_bstr_t(var) : "";

		var = recordset->GetCollect(_T("PC_NAME"));
		testInfo.pcName = var.vt != NULL ? (std::string)_bstr_t(var) : "";

		var = recordset->GetCollect(_T("CABINET_TAG"));
		testInfo.cabinetTag = var.vt != NULL ? (std::string)_bstr_t(var) : "";

		var = recordset->GetCollect(_T("FILE_NAME"));
		testInfo.fileName = var.vt != NULL ? (std::string)_bstr_t(var) : "";

		var = recordset->GetCollect(_T("WORK_NAME"));
		testInfo.workName = var.vt != NULL ? (std::string)_bstr_t(var) : "";

		var = recordset->GetCollect(_T("FINISH_FLAG"));
		testInfo.finishFlag = var.vt != NULL ? int(var) : 0;

		var = recordset->GetCollect(_T("CELL_NUMBER"));
		testInfo.cellNumber = var.vt != NULL ? int(var) : 0;

		var = recordset->GetCollect(_T("FINISH_TIME"));
		testInfo.finishTime = var.vt != NULL ? (std::string)_bstr_t(var) : "";

		var = recordset->GetCollect(_T("DEVICE_NAME"));
		testInfo.deviceName = var.vt != NULL ? (std::string)_bstr_t(var) : "";
		
		var = recordset->GetCollect(_T("GROUPNUM_PERCOL"));
		testInfo.groupNumPerCol = var.vt != NULL ? int(var) : 0;
		
		var = recordset->GetCollect(_T("COLSHOW_NUM"));
		testInfo.colShowNum = var.vt != NULL ? int(var) : 0;
		
		var = recordset->GetCollect(_T("NUM_PERGROUP"));
		testInfo.numPerGroup = var.vt != NULL ? int(var) : 0;

		var = recordset->GetCollect(_T("CONST_VMAX"));
		testInfo.constVmax = var.vt != NULL ? int(var) : 0;

		var = recordset->GetCollect(_T("CONST_VMIN"));
		testInfo.constVmin = var.vt != NULL ? int(var) : 0;

		var = recordset->GetCollect(_T("CONST_AMAX"));
		testInfo.constAmax = var.vt != NULL ? int(var) : 0;

		var = recordset->GetCollect(_T("CONST_AMIN"));
		testInfo.constAmin = var.vt != NULL ? int(var) : 0;

		var = recordset->GetCollect(_T("VDIS"));
		testInfo.vdis = var.vt != NULL ? int(var) : 0;

		var = recordset->GetCollect(_T("VDIS_VAL"));
		testInfo.vdisVal = var.vt != NULL ? int(var) : 0;

		var = recordset->GetCollect(_T("ADIS"));
		testInfo.adis = var.vt != NULL ? int(var) : 0;

		var = recordset->GetCollect(_T("ADIS_VAL"));
		testInfo.adisVal = var.vt != NULL ? int(var) : 0;

		var = recordset->GetCollect(_T("TIMEDIS"));
		testInfo.timeDis = var.vt != NULL ? int(var) : 0;

		var = recordset->GetCollect(_T("TIMEDIS_VAL"));
		testInfo.timeDisVal = var.vt != NULL ? int(var) : 0;

	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
		return testInfo;
	}

	return testInfo;
}

vector<WorkProcInfo> CDbUtils::GetWorkProcInfos(CString dataFilePath)
{
	_bstr_t sqlStr = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" +
		(_bstr_t)dataFilePath;

	_bstr_t querySql = "select * from WORKPROC_INFO";

	vector<WorkProcInfo> workProcInfos;

	HRESULT hr;
	_RecordsetPtr recordset;
	_ConnectionPtr connection;
	try
	{
		//先创建连接实例
		hr = connection.CreateInstance(__uuidof(Connection));//创建Connection对象

		if (SUCCEEDED(hr))
		{
			// 打开本地Access库Demo.mdb
			hr = connection->Open(sqlStr, "", "", adModeUnknown);
		}
		else
		{
			CString errormessage;
			errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
			AfxMessageBox(errormessage);
			return workProcInfos;
		}
		if (SUCCEEDED(hr))
		{
			recordset.CreateInstance(__uuidof(Recordset));
			recordset->Open(querySql,		 // 查询DemoTable表中所有字段
				connection.GetInterfacePtr(),			// 获取库连接的IDispatch指针
				adOpenStatic,
				adLockOptimistic,
				adCmdText);
		}
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
		return workProcInfos;
	}
	int count = 0;
	try
	{
		count = recordset->GetRecordCount();
	}
	catch (_com_error e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s"), e.ErrorMessage());
		AfxMessageBox(errormessage);
		return workProcInfos;
	}

	if (count == 0)
	{
		return workProcInfos;
	}
	try
	{
		_variant_t var;
		recordset->MoveFirst();
		
		while (!recordset->ADOBOF && !recordset->ADOEOF)
		{
			WorkProcInfo workProcInfo;

			var = recordset->GetCollect(_T("STEP_ID"));
			workProcInfo.stepId = var.vt != NULL ? int(var) : 0;

			var = recordset->GetCollect(_T("STEP_NAME"));
			workProcInfo.workStepName = var.vt != NULL ? (std::string)_bstr_t(var) : "";

			var = recordset->GetCollect(_T("STEP_TIME"));
			workProcInfo.workTime = var.vt != NULL ? int(var) : 0;

			var = recordset->GetCollect(_T("CURNT"));
			workProcInfo.current = var.vt != NULL ? int(var) : 0;

			var = recordset->GetCollect(_T("MAX_VOLT"));
			workProcInfo.maxVolt = var.vt != NULL ? int(var) : 0;

			var = recordset->GetCollect(_T("MIN_VOLT"));
			workProcInfo.minVolt = var.vt != NULL ? int(var) : 0;

			var = recordset->GetCollect(_T("DELTAV"));
			workProcInfo.deltaVolt = var.vt != NULL ? int(var) : 0;

			var = recordset->GetCollect(_T("END_CURRENT"));
			workProcInfo.endCurrent = var.vt != NULL ? int(var) : 0;

			var = recordset->GetCollect(_T("END_CAPACITY"));
			workProcInfo.endCapacity = var.vt != NULL ? int(var) : 0;

			var = recordset->GetCollect(_T("START_STEP"));
			workProcInfo.startStep = var.vt != NULL ? int(var) : 0;

			var = recordset->GetCollect(_T("END_STEP"));
			workProcInfo.endStep = var.vt != NULL ? int(var) : 0;

			var = recordset->GetCollect(_T("LOOP_NUM"));
			workProcInfo.loopNum = var.vt != NULL ? int(var) : 0;

			workProcInfos.push_back(workProcInfo);

			recordset->MoveNext();
		}
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
		return workProcInfos;
	}

	return workProcInfos;
}

vector<CDbattery> CDbUtils::GetWorkProcDatas(CString dataFilePath)
{
	_bstr_t querySql = "select * from CHANNEL_CURVE group by CHANNEL, STEP, CYCLE) order by ID asc STEP ASC;";

	return GetSpecificStepInfos(dataFilePath, querySql);
}

vector<CDbattery> CDbUtils::GetStartStepInfos(CString dataFilePath, int stepId)
{

	_bstr_t querySql = "select * from CHANNEL_CURVE A where A.ID in (select MIN(B.ID) from CHANNEL_CURVE  B where B.VOLTAGE > 0 and B.STEP = " + _bstr_t(stepId)
		+ " group by B.CHANNEL, B.CYCLE) order by ID asc;";

	return GetSpecificStepInfos(dataFilePath, querySql);

}


vector<double> CDbUtils::GetAvgVolt(CString dataFilePath, int stepId)
{
	_bstr_t querySql = "select AVG(VOLTAGE) as AVG_VOLTAGE from CHANNEL_CURVE where VOLTAGE > 0 and STEP = " + _bstr_t(stepId)
		+" group by CHANNEL, CYCLE";

	_bstr_t sqlStr = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" +
		(_bstr_t)dataFilePath;
	vector<double> avgVolts;

	HRESULT hr;
	_RecordsetPtr recordset;
	_ConnectionPtr connection;
	try
	{
		//先创建连接实例
		hr = connection.CreateInstance(__uuidof(Connection));//创建Connection对象

		if (SUCCEEDED(hr))
		{
			// 打开本地Access库Demo.mdb
			hr = connection->Open(sqlStr, "", "", adModeUnknown);
		}
		else
		{
			CString errormessage;
			errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
			AfxMessageBox(errormessage);
			return avgVolts;
		}
		if (SUCCEEDED(hr))
		{
			recordset.CreateInstance(__uuidof(Recordset));
			recordset->Open(querySql,		 // 查询DemoTable表中所有字段
				connection.GetInterfacePtr(),			// 获取库连接的IDispatch指针
				adOpenStatic,
				adLockOptimistic,
				adCmdText);
		}
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
		return avgVolts;
	}
	int count = 0;
	try
	{
		count = recordset->GetRecordCount();
	}
	catch (_com_error e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s"), e.ErrorMessage());
		AfxMessageBox(errormessage);
		return avgVolts;
	}

	if (count == 0)
	{
		return avgVolts;
	}
	try
	{

		recordset->MoveFirst();
		double avg;
		while (!recordset->ADOBOF && !recordset->ADOEOF)
		{
			_variant_t var;
			var = recordset->GetCollect(_T("AVG_VOLTAGE"));
			avg = var.vt != NULL ? double(var) : 0;

			avgVolts.push_back(avg);

			recordset->MoveNext();
		}
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
		return avgVolts;
	}

	return avgVolts;
}

vector<CDbattery> CDbUtils::GetEndStepInfos(CString dataFilePath, int stepId)
{
	_bstr_t querySql = "select * from CHANNEL_CURVE A where A.ID in (select MIN(B.ID) from CHANNEL_CURVE B where B.VOLTAGE > 0 and B.STEP = " + _bstr_t(stepId)
		+ " group by B.CHANNEL, B.CYCLE) order by ID asc;";

	return GetSpecificStepInfos(dataFilePath, querySql);
}

vector<CBatStepInfo> CDbUtils::GetBatStepInfos(CString dataFilePath, int stepId)
{
	HRESULT hr;
	_RecordsetPtr recordset;
	_ConnectionPtr connection;

	CString stepIdStr;
	stepIdStr.Format(_T("%d"), stepId);

	_bstr_t querySql = "select FIRST(ID) as START_ID, FIRST(TESTITEM) AS CABID, FIRST(CHANNEL) AS BATID, FIRST(STEP) AS STEPID, \
	FIRST(CYCLE) AS CYCLE, FIRST(NUM) as NUM, FIRST(STATION) as START_WORKENAME, FIRST(TEST_TIME) as START_TESTTIME, \
	FIRST(ATIME) as START_ATIME, FIRST(VOLTAGE) as START_VOLT, FIRST(CURNT) as START_CURRENT, FIRST(CAPACITY) as START_CAPACITY, \
	FIRST(ENERGY) as START_ENERGY, FIRST(POWER) as START_POWER, FIRST(CABSTATE) as START_CABSTATE, FIRST(BATSTATE) as START_BATSTATE, \
	LAST(ID) as END_ID, LAST(STATION) as END_WORKENAME, LAST(TEST_TIME) as END_TESTTIME, LAST(ATIME) as END_ATIME, \
	LAST(VOLTAGE) as END_VOLT, LAST(CURNT) as END_CURRENT, LAST(CAPACITY) as END_CAPACITY, LAST(ENERGY) as END_ENERGY, \
	LAST(POWER) as END_POWER, LAST(CABSTATE) as END_CABSTATE, LAST(BATSTATE) as END_BATSTATE, \
	AVG(VOLTAGE) as AVG_VOLTAGE, AVG(CAPACITY) as AVG_CAPACITY from CHANNEL_CURVE A where STEP ="\
	+ (_bstr_t)stepIdStr + " and VOLTAGE >= 0 group by CHANNEL, CYCLE, NUM;";
	
	_bstr_t sqlStr = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" +
		(_bstr_t)dataFilePath;
		
	vector<CBatStepInfo> batStepInfos;

	try
	{
		//先创建连接实例
		hr = connection.CreateInstance(__uuidof(Connection));//创建Connection对象

		if (SUCCEEDED(hr))
		{
			// 打开本地Access库Demo.mdb
			hr = connection->Open(sqlStr, "", "", adModeUnknown);
		}
		else
		{
			CString errormessage;
			errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
			AfxMessageBox(errormessage);
			return batStepInfos;
		}
		if (SUCCEEDED(hr))
		{
			recordset.CreateInstance(__uuidof(Recordset));
			recordset->Open(querySql,		 // 查询DemoTable表中所有字段
				connection.GetInterfacePtr(),			// 获取库连接的IDispatch指针
				adOpenStatic,
				adLockOptimistic,
				adCmdText);
		}
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
		return batStepInfos;
	}
	int count = 0;
	try
	{
		count = recordset->GetRecordCount();
	}
	catch (_com_error e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s"), e.ErrorMessage());
		AfxMessageBox(errormessage);
		return batStepInfos;
	}

	if (count == 0)
	{
		return batStepInfos;
	}
	try
	{

		recordset->MoveFirst();

		while (!recordset->ADOBOF && !recordset->ADOEOF)
		{
			CBatStepInfo batteryInfo = CreateBatStepInfoByRecordSet(recordset);
			batStepInfos.push_back(batteryInfo);
			recordset->MoveNext();
		}
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
		return batStepInfos;
	}

	return batStepInfos;

}


CBatStepInfo CDbUtils::CreateBatStepInfoByRecordSet(_RecordsetPtr recordset)
{
	_variant_t var;

	CBatStepInfo batStepInfo;
	
	var = recordset->GetCollect(_T("START_ID"));
	batStepInfo.startStepInfo.id = var.vt != NULL ? int(var) : 0;
	var = recordset->GetCollect(_T("END_ID"));
	batStepInfo.endStepInfo.id = var.vt != NULL ? int(var) : 0;

	var = recordset->GetCollect(_T("CABID"));
	batStepInfo.startStepInfo.cabId = var.vt != NULL ? int(var) : 0;
	batStepInfo.endStepInfo.cabId = batStepInfo.startStepInfo.cabId;

	var = recordset->GetCollect(_T("BATID"));
	batStepInfo.startStepInfo.batId = var.vt != NULL ? int(var) : 0;
	batStepInfo.endStepInfo.batId = batStepInfo.startStepInfo.batId;

	var = recordset->GetCollect(_T("STEPID"));
	batStepInfo.startStepInfo.stepId = var.vt != NULL ? int(var) : 0;
	batStepInfo.endStepInfo.stepId = batStepInfo.startStepInfo.stepId;

	var = recordset->GetCollect(_T("CYCLE"));
	batStepInfo.startStepInfo.cycleId = var.vt != NULL ? int(var) : 0;
	batStepInfo.endStepInfo.cycleId = batStepInfo.startStepInfo.cycleId;

	var = recordset->GetCollect(_T("NUM"));
	batStepInfo.startStepInfo.num = var.vt != NULL ? int(var) : 0;
	batStepInfo.endStepInfo.num = batStepInfo.startStepInfo.num;

	var = recordset->GetCollect(_T("START_WORKENAME"));
	batStepInfo.startStepInfo.workEname = var.vt != VT_NULL ? (LPCTSTR)_bstr_t(var) : L"";
	
	var = recordset->GetCollect(_T("END_WORKENAME"));
	batStepInfo.endStepInfo.workEname = var.vt != VT_NULL ? (LPCTSTR)_bstr_t(var) : L"";

	CTime c = CTime::GetCurrentTime();
	var = recordset->GetCollect(_T("START_TESTTIME"));
	batStepInfo.startStepInfo.testTime = var.vt != VT_NULL ? CTime(var) : c;
	var = recordset->GetCollect(_T("END_TESTTIME"));
	batStepInfo.endStepInfo.testTime = var.vt != VT_NULL ? CTime(var) : c;

	//var = pRecordset->GetCollect(_T("TESTTIME"));
	//dbattery.testTime = var.vt != NULL ? CTime(var) : ;

	var = recordset->GetCollect(_T("START_ATIME"));
	batStepInfo.startStepInfo.atime = var.vt != NULL ? int(double(var)) : 0;
	var = recordset->GetCollect(_T("END_ATIME"));
	batStepInfo.endStepInfo.atime = var.vt != NULL ? int(double(var)) : 0;

	var = recordset->GetCollect(_T("START_VOLT"));
	batStepInfo.startStepInfo.voltage = var.vt != NULL ? int(double(var)) : 0;
	var = recordset->GetCollect(_T("END_VOLT"));
	batStepInfo.endStepInfo.voltage = var.vt != NULL ? int(double(var)) : 0;

	var = recordset->GetCollect(_T("START_CURRENT"));
	batStepInfo.startStepInfo.curnt = var.vt != NULL ? int(double(var)) : 0;
	var = recordset->GetCollect(_T("END_CURRENT"));
	batStepInfo.endStepInfo.curnt = var.vt != NULL ? int(double(var)) : 0;

	var = recordset->GetCollect(_T("START_CAPACITY"));
	batStepInfo.startStepInfo.capacity = var.vt != NULL ? int(double(var)) : 0;
	var = recordset->GetCollect(_T("END_CAPACITY"));
	batStepInfo.endStepInfo.capacity = var.vt != NULL ? int(double(var)) : 0;

	var = recordset->GetCollect(_T("START_ENERGY"));
	batStepInfo.startStepInfo.energy = var.vt != NULL ? int(double(var)) : 0;
	var = recordset->GetCollect(_T("END_ENERGY"));
	batStepInfo.endStepInfo.energy = var.vt != NULL ? int(double(var)) : 0;

	var = recordset->GetCollect(_T("START_POWER"));
	batStepInfo.startStepInfo.power = var.vt != NULL ? int(double(var)) : 0;
	var = recordset->GetCollect(_T("END_POWER"));
	batStepInfo.endStepInfo.power = var.vt != NULL ? int(double(var)) : 0;

	var = recordset->GetCollect(_T("START_CABSTATE"));
	batStepInfo.startStepInfo.cabState = var.vt != NULL ? int(double(var)) : 0;
	var = recordset->GetCollect(_T("END_CABSTATE"));
	batStepInfo.endStepInfo.cabState = var.vt != NULL ? int(double(var)) : 0;

	var = recordset->GetCollect(_T("START_BATSTATE"));
	batStepInfo.startStepInfo.batState = var.vt != NULL ? int(double(var)) : 0;
	var = recordset->GetCollect(_T("END_BATSTATE"));
	batStepInfo.endStepInfo.batState = var.vt != NULL ? int(double(var)) : 0;

	var = recordset->GetCollect(_T("AVG_VOLTAGE"));
	batStepInfo.avgVolt = var.vt != NULL ? int(double(var) + 0.5) : 0;

	var = recordset->GetCollect(_T("AVG_CAPACITY"));
	batStepInfo.avgCapacity = var.vt != NULL ? int(double(var) + 0.5) : 0;

	return batStepInfo;
}

//  每次恒流恒压充电只有一个满足条件时[实际情况就是这样]能进行正确的搜索
vector<CDbattery> CDbUtils::GetBatCacvSetpInfos(CString dataFilePath, int stepId)
{
	HRESULT hr;
	_RecordsetPtr recordset;
	_ConnectionPtr connection;

	CString stepIdStr;
	stepIdStr.Format(_T("%d"), stepId);

	//_bstr_t querySql = "select ID, TESTITEM AS CABID, CHANNEL AS BATID, STEP AS STEPID, \
	//CYCLE, NUM, STATION as WORKENAME, TEST_TIME as TESTTIME, ATIME, VOLTAGE as VOLT, CURNT as CURRENT, CAPACITY, \
	//ENERGY, POWER, CABSTATE, BATSTATE from CHANNEL_CURVE  where STEP = "\
	//+ (_bstr_t)stepIdStr + " and VOLTAGE >= 0 and CACVSTATE = 1";

	_bstr_t querySql = "select * from CHANNEL_CURVE  where STEP = "\
	+ (_bstr_t)stepIdStr + " and VOLTAGE >= 0 and CACVSTATE = 1";

	_bstr_t sqlStr = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" +
		(_bstr_t)dataFilePath;

	vector<CDbattery> batStepInfos = CDbUtils::GetSpecificStepInfos(dataFilePath, querySql);
	return batStepInfos;
}

vector<CDbattery> CDbUtils::GetSpecificStepInfos(CString dataFilePath, _bstr_t querySql)
{
	_bstr_t sqlStr = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" +
		(_bstr_t)dataFilePath;
	vector<CDbattery> batteryInfos;

	HRESULT hr;
	_RecordsetPtr recordset;
	_ConnectionPtr connection;
	try
	{
		//先创建连接实例
		hr = connection.CreateInstance(__uuidof(Connection));//创建Connection对象

		if (SUCCEEDED(hr))
		{
			// 打开本地Access库Demo.mdb
			hr = connection->Open(sqlStr, "", "", adModeUnknown);
		}
		else
		{
			CString errormessage;
			errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
			AfxMessageBox(errormessage);
			return batteryInfos;
		}
		if (SUCCEEDED(hr))
		{
			recordset.CreateInstance(__uuidof(Recordset));
			recordset->Open(querySql,		 // 查询DemoTable表中所有字段
				connection.GetInterfacePtr(),			// 获取库连接的IDispatch指针
				adOpenStatic,
				adLockOptimistic,
				adCmdText);
		}
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
		return batteryInfos;
	}
	int count = 0;
	try
	{
		count = recordset->GetRecordCount();
	}
	catch (_com_error e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s"), e.ErrorMessage());
		AfxMessageBox(errormessage);
		return batteryInfos;
	}

	if (count == 0)
	{
		return batteryInfos;
	}
	try
	{

		recordset->MoveFirst();

		while (!recordset->ADOBOF && !recordset->ADOEOF)
		{
			CDbattery batteryInfo = CreateCdbatteryByRecordSet(recordset);
			batteryInfos.push_back(batteryInfo);
			recordset->MoveNext();
		}
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
		return batteryInfos;
	}

	return batteryInfos;
}



//vector<CPartBattery> CDbUtils::GetPartBatData(CString dbFilePath, int stepId)
//{
//	vector<CDbattery> startStepInfos = GetStartStepInfos(dbFilePath, stepId);
//	vector<CDbattery> endStepInfos = GetEndStepInfos(dbFilePath, stepId);
//	vector<double> avgVolts = GetAvgVolt(dbFilePath, stepId);
//
//	vector<CPartBattery>  partBatterys;
//
//	CString str;
//	for (int idx = 0; idx < startStepInfos.size(); ++idx)
//	{
//		CPartBattery battery;
//		str.Format(_T("%d"), int(endStepInfos[idx].atime + 0.5));
//		battery.atime = str;
//
//		str.Format(_T("%d"), int(avgVolts[idx] + 0.5));
//		battery.avgVolt = str;
//
//		str.Format(_T("%d"), int(endStepInfos[idx].capacity + 0.5));
//		battery.capacity = str;
//
//		str.Format(_T("%d"), int(endStepInfos[idx].curnt + 0.5));
//		battery.endCurrent = str;
//		
//		str.Format(_T("%d"), int(endStepInfos[idx].voltage + 0.5));
//		battery.endVolt = str;
//
//		str.Format(_T("%d"), int(endStepInfos[idx].energy + 0.5));
//		battery.energy = str;
//
//		str.Format(_T("%d"), int(startStepInfos[idx].voltage + 0.5));
//		battery.openVolt = str;
//
//		battery.batId = startStepInfos[idx].batId;
//
//		partBatterys.push_back(battery);
//	}
//	return partBatterys;
//}

vector<CPartBattery> CDbUtils::GetPartBatData(CString dbFilePath, int stepId)
{	
	HRESULT hr;
	_RecordsetPtr recordset;
	_ConnectionPtr connection;
	_bstr_t sqlStr = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" +
		(_bstr_t)dbFilePath;

	CString stepIdStr;
	stepIdStr.Format(_T("%d"), stepId);
	_bstr_t querySql = "select FIRST(A.TESTITEM) AS TESTITEM, FIRST(A.CHANNEL) AS CHANNEL,\
			FIRST(A.STEP) AS STEP,FIRST(A.CYCLE) AS CYCLE, LAST(A.ATIME) AS ATIME, FIRST(A.VOLTAGE) as OPEN_VOLT, \
			LAST(A.VOLTAGE) as END_VOLT, LAST(A.CURNT) as END_CURRENT, AVG(A.VOLTAGE) as AVG_VOLT, LAST(A.CAPACITY) as CAPACITY, LAST(A.ENERGY) \
			as ENERGY from CHANNEL_CURVE A where A.STEP ="\
			+ (_bstr_t)stepIdStr + " and A.VOLTAGE >= 0 group by A.CHANNEL, A.CYCLE, A.NUM;";

	vector<CPartBattery> partBatteryInfos;

	try
	{
		//先创建连接实例
		hr = connection.CreateInstance(__uuidof(Connection));//创建Connection对象

		if (SUCCEEDED(hr))
		{
			// 打开本地Access库Demo.mdb
			hr = connection->Open(sqlStr, "", "", adModeUnknown);
		}
		else
		{
			CString errormessage;
			errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
			AfxMessageBox(errormessage);
			return partBatteryInfos;
		}
		if (SUCCEEDED(hr))
		{
			recordset.CreateInstance(__uuidof(Recordset));
			recordset->Open(querySql,		 // 查询DemoTable表中所有字段
				connection.GetInterfacePtr(),			// 获取库连接的IDispatch指针
				adOpenStatic,
				adLockOptimistic,
				adCmdText);
		}
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
		return partBatteryInfos;
	}
	int count = 0;
	try
	{
		count = recordset->GetRecordCount();
	}
	catch (_com_error e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s"), e.ErrorMessage());
		AfxMessageBox(errormessage);
		return partBatteryInfos;
	}

	if (count == 0)
	{
		return partBatteryInfos;
	}
	try
	{

		recordset->MoveFirst();

		while (!recordset->ADOBOF && !recordset->ADOEOF)
		{
			CPartBattery batteryInfo = CreatePartBatteryByRecordSet(recordset);
			partBatteryInfos.push_back(batteryInfo);
			recordset->MoveNext();
		}
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
		return partBatteryInfos;
	}

	return partBatteryInfos;
}

vector<CBatCapInfo> CDbUtils::GetBatCapInfoById(CString dataFilePath, int stepId)
{
	_bstr_t sqlStr = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" +
		(_bstr_t)dataFilePath;
	vector<CBatCapInfo> batCapInfos;
	CString stepIdStr;
	stepIdStr.Format(L"%d", stepId);
	_bstr_t querySql = "select FIRST(A.TESTITEM) AS TESTITEM, FIRST(A.CHANNEL) AS CHANNEL,FIRST(A.STEP) AS STEP,FIRST(A.CYCLE) AS CYCLE,LAST(A.ATIME) AS ATIME, FIRST(A.VOLTAGE) as OPEN_VOLT, \
	LAST(A.VOLTAGE) as END_VOLT, AVG(A.VOLTAGE) as AVG_VOLT, LAST(A.CAPACITY) as CAPACITY, LAST(A.ENERGY) as ENERGY, (LAST(A.VOLTAGE) + FIRST(A.VOLTAGE)) / 2 as MID_VOLT \
	from CHANNEL_CURVE A where A.STEP =" +(_bstr_t)stepIdStr+ " and A.VOLTAGE >= 0 group by A.CHANNEL, A.CYCLE, A.NUM;";

	HRESULT hr;
	_RecordsetPtr recordset;
	_ConnectionPtr connection;
	try
	{
		//先创建连接实例
		hr = connection.CreateInstance(__uuidof(Connection));//创建Connection对象

		if (SUCCEEDED(hr))
		{
			// 打开本地Access库Demo.mdb
			hr = connection->Open(sqlStr, "", "", adModeUnknown);
		}
		else
		{
			CString errormessage;
			errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
			AfxMessageBox(errormessage);
			return batCapInfos;
		}
		if (SUCCEEDED(hr))
		{
			recordset.CreateInstance(__uuidof(Recordset));
			recordset->Open(querySql,		 // 查询DemoTable表中所有字段
				connection.GetInterfacePtr(),			// 获取库连接的IDispatch指针
				adOpenStatic,
				adLockOptimistic,
				adCmdText);
		}
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
		return batCapInfos;
	}
	int count = 0;
	try
	{
		count = recordset->GetRecordCount();
	}
	catch (_com_error e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s"), e.ErrorMessage());
		AfxMessageBox(errormessage);
		return batCapInfos;
	}

	if (count == 0)
	{
		return batCapInfos;
	}
	try
	{

		recordset->MoveFirst();

		while (!recordset->ADOBOF && !recordset->ADOEOF)
		{
			CBatCapInfo batteryInfo = CreateBatCapInfoByRecordSet(recordset);
			batCapInfos.push_back(batteryInfo);
			recordset->MoveNext();
		}
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("错误信息:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
		return batCapInfos;
	}

	return batCapInfos;
}

//vector<vector<CPartBattery>> CDbUtils::GetPartBatData(CString dbFilePath)
//{
//	vector<CDbattery> workProcDatas = GetWorkProcDatas(dbFilePath);
//	
//	vector<vector<CPartBattery>> partBatterys;
//	vector<CPartBattery>  partBatterys;
//
//	CString str;
//	int preStepId, cycleId;
//
//	for (int idx = 0; idx < workProcDatas.size(); ++idx)
//	{
//
//		CPartBattery battery;
//		str.Format(_T("%d"), int(endStepInfos[idx].atime + 0.5));
//		battery.atime = str;
//
//		str.Format(_T("%d"), int(avgVolts[idx] + 0.5));
//		battery.avgVolt = str;
//
//		str.Format(_T("%d"), int(endStepInfos[idx].capacity + 0.5));
//		battery.capacity = str;
//
//		str.Format(_T("%d"), int(endStepInfos[idx].curnt + 0.5));
//		battery.endCurrent = str;
//
//		str.Format(_T("%d"), int(endStepInfos[idx].voltage + 0.5));
//		battery.endVolt = str;
//
//		str.Format(_T("%d"), int(endStepInfos[idx].energy + 0.5));
//		battery.energy = str;
//
//		str.Format(_T("%d"), int(startStepInfos[idx].voltage + 0.5));
//		battery.openVolt = str;
//
//		battery.batId = startStepInfos[idx].batId;
//
//		partBatterys.push_back(battery);
//	}
//	return partBatterys;
//}

CDbattery CDbUtils::CreateCdbatteryByRecordSet(_RecordsetPtr recordset)
{
	_variant_t var;

	CDbattery dbattery;

	var = recordset->GetCollect(_T("ID"));
	if (var.vt != VT_NULL)
		dbattery.id = int(var);

	var = recordset->GetCollect(_T("TESTITEM"));
	dbattery.cabId = var.vt != NULL ? int(var) : 0;

	var = recordset->GetCollect(_T("CHANNEL"));
	dbattery.batId = var.vt != NULL ? int(var) : 0;

	var = recordset->GetCollect(_T("STEP"));
	dbattery.stepId = var.vt != NULL ? int(var) : 0;

	var = recordset->GetCollect(_T("CYCLE"));
	dbattery.cycleId = var.vt != NULL ? int(var) : 0;

	var = recordset->GetCollect(_T("NUM"));
	dbattery.num = var.vt != NULL ? int(var) : 0;

	var = recordset->GetCollect(_T("STATION"));
	dbattery.workEname = var.vt != NULL ? (LPCTSTR)_bstr_t(var) : L"";

	//var = pRecordset->GetCollect(_T("TESTTIME"));
	//dbattery.testTime = var.vt != NULL ? CTime(var) : ;

	var = recordset->GetCollect(_T("ATIME"));
	dbattery.atime = var.vt != NULL ? double(var) : 0;

	var = recordset->GetCollect(_T("VOLTAGE"));
	dbattery.voltage = var.vt != NULL ? double(var) : 0;

	var = recordset->GetCollect(_T("CURNT"));
	dbattery.curnt = var.vt != NULL ? double(var) : 0;

	var = recordset->GetCollect(_T("CAPACITY"));
	dbattery.capacity = var.vt != NULL ? double(var) : 0;

	var = recordset->GetCollect(_T("ENERGY"));
	dbattery.energy = var.vt != NULL ? double(var) : 0;

	var = recordset->GetCollect(_T("POWER"));
	dbattery.power = var.vt != NULL ? double(var) : 0;

	var = recordset->GetCollect(_T("CABSTATE"));
	dbattery.cabState = var.vt != NULL ? int(var) : 0;

	var = recordset->GetCollect(_T("BATSTATE"));
	dbattery.batState = var.vt != NULL ? int(var) : 0;

	var = recordset->GetCollect(_T("CACVSTATE"));
	dbattery.cacvState = var.vt != VT_NULL ? int(var) : 0;

	return dbattery;
}

CBatCapInfo CDbUtils::CreateBatCapInfoByRecordSet(_RecordsetPtr recordset)
{
	_variant_t var;

	CBatCapInfo batCapInfo;

	var = recordset->GetCollect(_T("TESTITEM"));
	batCapInfo.cabIdCstr = var.vt != NULL ? CString(var) : 0;

	var = recordset->GetCollect(_T("CHANNEL"));
	batCapInfo.batIdCstr = var.vt != NULL ? CString(var) : 0;
	batCapInfo.batId = var.vt != NULL ? int(var) : 0;

	var = recordset->GetCollect(_T("CAPACITY"));
	batCapInfo.capacityCstr = var.vt != NULL ? CString(var) : 0;

	var = recordset->GetCollect(_T("AVG_VOLT"));
	batCapInfo.avgVoltCstr = var.vt != NULL ? CString(var) : 0;

	var = recordset->GetCollect(_T("OPEN_VOLT"));
	batCapInfo.openVoltCstr = var.vt != NULL ? CString(var) : 0;

	var = recordset->GetCollect(_T("END_VOLT"));
	batCapInfo.endVoltCstr = var.vt != NULL ? (LPCTSTR)_bstr_t(var) : L"";

	var = recordset->GetCollect(_T("ATIME"));
	batCapInfo.timeCstr = var.vt != NULL ? CString(var) : 0;

	var = recordset->GetCollect(_T("ENERGY"));
	batCapInfo.energyCstr = var.vt != NULL ? CString(var) : 0;

	var = recordset->GetCollect(_T("MID_VOLT"));
	batCapInfo.midVoltCstr = var.vt != NULL ? CString(var) : 0;

	return batCapInfo;
}

CPartBattery CDbUtils::CreatePartBatteryByRecordSet(_RecordsetPtr recordset)
{
	_variant_t var;

	CPartBattery partBattery;

	var = recordset->GetCollect(_T("CHANNEL"));
	partBattery.batId = var.vt != NULL ? int(var) : 0;

	var = recordset->GetCollect(_T("ATIME"));
	partBattery.atime = var.vt != NULL ? CString(var) : L"0";

	var = recordset->GetCollect(_T("AVG_VOLT"));
	partBattery.avgVolt = var.vt != NULL ? CString(var) : L"0";

	var = recordset->GetCollect(_T("CAPACITY"));
	partBattery.capacity = var.vt != NULL ? CString(var) : L"0";

	var = recordset->GetCollect(_T("END_CURRENT"));
	partBattery.endCurrent = var.vt != NULL ? (LPCTSTR)_bstr_t(var) : L"";

	var = recordset->GetCollect(_T("END_VOLT"));
	partBattery.endVolt = var.vt != NULL ? (LPCTSTR)_bstr_t(var) : L"";

	var = recordset->GetCollect(_T("OPEN_VOLT"));
	partBattery.openVolt = var.vt != NULL ? (LPCTSTR)_bstr_t(var) : L"";
	
	var = recordset->GetCollect(_T("ENERGY"));
	partBattery.energy = var.vt != NULL ? (LPCTSTR)_bstr_t(var) : L"";


	return partBattery;
}
