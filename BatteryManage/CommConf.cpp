#include "stdafx.h"
#include "CommConf.h"
#include "BatteryUtils.h"

CommConf* CommConf::commConf = new CommConf();

CommConf::CommConf()
{
	commPath = CBatteryUtils::GetConfigPath(_T("\\config\\init\\comm.ini"));

	wchar_t str[MAX_PATH_LENGTH];
	GetPrivateProfileString(_T("communicate"), _T("commPort"), _T("COM1"), str, MAX_PATH_LENGTH, commPath);
	commPortStr = str;
	commPortVal = _ttoi(commPortStr.Right(1));

	GetPrivateProfileString(_T("communicate"), _T("commBaud"), _T("57600"), str, MAX_PATH_LENGTH, commPath);
	commBaudStr = str;
	commBaudVal = _ttoi(commBaudStr);

	GetPrivateProfileString(_T("communicate"), _T("commTime"), _T("60"), str, MAX_PATH_LENGTH, commPath);
	commTimeStr = str;
	commTimeVal = _ttoi(commTimeStr);

	chkVal = GetPrivateProfileInt(_T("login"), _T("chk"), 0, commPath);
	needLoginVal = GetPrivateProfileInt(_T("login"), _T("needLogin"), 0, commPath);
	forbdModifyVal = GetPrivateProfileInt(_T("login"), _T("forbdModify"), 0, commPath);
	onlineReadVal = GetPrivateProfileInt(_T("login"), _T("onlineRead"), 0, commPath);
	exitReadVal = GetPrivateProfileInt(_T("login"), _T("exitRead"), 0, commPath);
	forbdOtherVal = GetPrivateProfileInt(_T("login"), _T("forbdOther"), 0, commPath);
}


CommConf* CommConf::GetInstance()
{
	return commConf;
}

BOOL CommConf::SaveCommConf()
{
	wchar_t str[MAX_PATH_LENGTH];

	WritePrivateProfileString(_T("communicate"), _T("commPort"), commPortStr, commPath);
	WritePrivateProfileString(_T("communicate"), _T("commBaud"), commBaudStr, commPath);
	WritePrivateProfileString(_T("communicate"), _T("commTime"), commTimeStr, commPath);

	_itow_s(chkVal, str, 10, 10);
	WritePrivateProfileString(_T("login"), _T("chk"), str, commPath);
	_itow_s(needLoginVal, str, 10, 10);
	WritePrivateProfileString(_T("login"), _T("needLogin"), str, commPath);
	_itow_s(forbdModifyVal, str, 10, 10);
	WritePrivateProfileString(_T("login"), _T("forbdModify"), str, commPath);
	_itow_s(onlineReadVal, str, 10, 10);
	WritePrivateProfileString(_T("login"), _T("onlineRead"), str, commPath);
	_itow_s(exitReadVal, str, 10, 10);
	WritePrivateProfileString(_T("login"), _T("exitRead"), str, commPath);
	_itow_s(forbdOtherVal, str, 10, 10);
	WritePrivateProfileString(_T("login"), _T("forbdOther"), str, commPath);

	return TRUE;
}

BOOL CommConf::UpdateCommConf()
{
	commPath = CBatteryUtils::GetConfigPath(_T("\\config\\init\\comm.ini"));

	wchar_t str[MAX_PATH_LENGTH];
	GetPrivateProfileString(_T("communicate"), _T("commPort"), _T("COM1"), str, MAX_PATH_LENGTH, commPath);
	commPortStr = str;
	commPortVal = _ttoi(commPortStr.Right(1));

	GetPrivateProfileString(_T("communicate"), _T("commBaud"), _T("57600"), str, MAX_PATH_LENGTH, commPath);
	commBaudStr = str;
	commBaudVal = _ttoi(commBaudStr);

	GetPrivateProfileString(_T("communicate"), _T("commTime"), _T("60"), str, MAX_PATH_LENGTH, commPath);
	commTimeStr = str;
	commTimeVal = _ttoi(commTimeStr);

	chkVal = GetPrivateProfileInt(_T("login"), _T("chk"), 0, commPath);
	needLoginVal = GetPrivateProfileInt(_T("login"), _T("needLogin"), 0, commPath);
	forbdModifyVal = GetPrivateProfileInt(_T("login"), _T("forbdModify"), 0, commPath);
	onlineReadVal = GetPrivateProfileInt(_T("login"), _T("onlineRead"), 0, commPath);
	exitReadVal = GetPrivateProfileInt(_T("login"), _T("exitRead"), 0, commPath);
	forbdOtherVal = GetPrivateProfileInt(_T("login"), _T("forbdOther"), 0, commPath);
	
	return TRUE;
}

