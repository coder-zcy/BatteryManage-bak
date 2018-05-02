#pragma once

class CDbSql
{
protected:
	CDbSql();
private: 
	static CDbSql *dbsql;
public:
	CString createChlInfoStr;
	CString createChlStepStr;
	CString createTestInfoStr;
	CString createChlCurveStr;
	CString createWorkProcStr;
	
	static CDbSql *GetInstance();
};


