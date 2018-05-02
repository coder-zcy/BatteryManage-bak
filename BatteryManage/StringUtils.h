#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "atltime.h"

using namespace std;

extern const int ascmapping[];
extern const LONGLONG oxmapping[];

// 工序Grid设置的最大有效值
const int MAX_VALIDE_NUM = 65000;	

class StringUtils
{
public:
	StringUtils();
	~StringUtils();
public:
	static vector<string> SplitByStr(const string &s, const string &seperator);
	static vector<CString> StringUtils::SplitByCstr(const CString &s, const CString &seperator);
	static LONGLONG XStrToInt(CString str);
	static BOOL IsValideInt(CString str);
	static string DatetimeToString(CTime srcTime);

	static string BytesToStr(CByteArray &bytes);


};

