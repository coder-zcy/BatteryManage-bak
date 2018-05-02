#pragma once
/*
从Curve表中筛选出相关数据组成,每条记录为BatCapInfo
*/
class CBatCapInfo
{
public:
	CBatCapInfo();
	~CBatCapInfo();
public:
	CString cabIdCstr;
	CString batIdCstr;
	int batId;
	CString gradeName;
	CString capacityCstr;
	CString timeCstr;
	CString openVoltCstr;
	CString avgVoltCstr;
	CString point1Cstr;
	CString point2Cstr;
	CString point3Cstr;
	CString point4Cstr;
	CString point5Cstr;
	CString endVoltCstr;
	CString sdCstr;
	CString midVoltCstr;
	CString energyCstr;
};

