#include "stdafx.h"
#include "TimeUtils.h"


CTimeUtils::CTimeUtils()
{
}


CTimeUtils::~CTimeUtils()
{
}

CString CTimeUtils::CreateTimePath()
{
	wchar_t str[INT_LENGTH];
	time_t nowTimeInfo;
	tm nowTime;
	CString timePath;

	time(&nowTimeInfo);
	localtime_s(&nowTime, &nowTimeInfo);

	int year = nowTime.tm_year + 1900;
	int month = nowTime.tm_mon + 1;
	int day = nowTime.tm_mday;
	int hour = nowTime.tm_hour;
	int minute = nowTime.tm_min;
	int second = nowTime.tm_sec;

	CString yearStr, monthStr, dayStr, hourStr, minuteStr, secondStr;


	_itow_s(year, str, INT_LENGTH); yearStr = str;
	_itow_s(month, str, INT_LENGTH); monthStr = str; monthStr = month < 10 ? _T("0") + monthStr : monthStr;
	_itow_s(day, str, INT_LENGTH); dayStr = str; dayStr = day < 10 ? _T("0") + dayStr : dayStr;
	_itow_s(hour, str, INT_LENGTH); hourStr = str; hourStr = hour < 10 ? _T("0") + hourStr : hourStr;
	_itow_s(minute, str, INT_LENGTH); minuteStr = str; minuteStr = minute < 10 ? _T("0") + minuteStr : minuteStr;
	_itow_s(second, str, INT_LENGTH); secondStr = str; secondStr = second < 10 ? _T("0") + secondStr : secondStr;

	timePath = yearStr + _T("_") + monthStr + "\\"
		+ dayStr + _T("_") + hourStr + minuteStr + secondStr + _T("_");

	return timePath;
}

CString CTimeUtils::GetCurrentTimeCstr()
{
	wchar_t str[INT_LENGTH];
	time_t nowTimeInfo;
	tm nowTime;

	time(&nowTimeInfo);
	localtime_s(&nowTime, &nowTimeInfo);

	int year = nowTime.tm_year + 1900;
	int month = nowTime.tm_mon + 1;
	int day = nowTime.tm_mday;
	int hour = nowTime.tm_hour;
	int minute = nowTime.tm_min;
	int second = nowTime.tm_sec;

	CString yearStr, monthStr, dayStr, hourStr, minuteStr, secondStr;


	_itow_s(year, str, INT_LENGTH); yearStr = str;
	_itow_s(month, str, INT_LENGTH); monthStr = str; monthStr = month < 10 ? _T("0") + monthStr : monthStr;
	_itow_s(day, str, INT_LENGTH); dayStr = str; dayStr = day < 10 ? _T("0") + dayStr : dayStr;
	_itow_s(hour, str, INT_LENGTH); hourStr = str; hourStr = hour < 10 ? _T("0") + hourStr : hourStr;
	_itow_s(minute, str, INT_LENGTH); minuteStr = str; minuteStr = minute < 10 ? _T("0") + minuteStr : minuteStr;
	_itow_s(second, str, INT_LENGTH); secondStr = str; secondStr = second < 10 ? _T("0") + secondStr : secondStr;

	
	return yearStr + L"-" + monthStr + L"-" + dayStr
		+ L" " + hourStr + L":" + minuteStr + L":" + secondStr;
}
