#include "stdafx.h"
#include "CapGradeConf.h"
#include "BatteryUtils.h"
#include "StringUtils.h"

CapGradeConf* CapGradeConf::capGradeConf = new CapGradeConf();



CapGradeConf::CapGradeConf()
{
	CString filePath = CBatteryUtils::GetConfigPath(_T("\\config\\init\\capgrade.ini"));
	codeNames;
	gradeDetailInfos;

	int idx;
	CString tmpStr, codeGradeStr;
	wchar_t str[MAX_STR_LENGTH]; 
	codeNames.clear();
	gradeDetailInfos.clear();

	GetPrivateProfileString(_T("grade"), _T("codeSel"), _T(""), str, MAX_PATH_LENGTH, filePath);
	codeSel = _ttoi(str);

	GetPrivateProfileString(_T("grade"), _T("codeSelCount"), _T("0"), str, MAX_PATH_LENGTH, filePath);
	codeSelCount = _ttoi(str);

	for (idx = 0; idx < codeSelCount; ++idx)
	{
		tmpStr.Format(_T("%d"), idx + 1);
		tmpStr = L"codeInfo" + tmpStr;
		GetPrivateProfileString(_T("grade"), tmpStr, _T(""), str, MAX_PATH_LENGTH, filePath);
		codeGradeStr = str;
		CGradeDetailInfo gradeDetailInfo(codeGradeStr);
		gradeDetailInfos.push_back(gradeDetailInfo);
		codeNames.push_back(gradeDetailInfo.codeName);
	}
}


CapGradeConf::~CapGradeConf()
{

}

void CapGradeConf::SaveToFile()
{
	CString filePath = CBatteryUtils::GetConfigPath(_T("\\config\\init\\capgrade.ini"));
	codeNames;
	gradeDetailInfos;

	int idx;
	CString tmpStr, codeGradeStr, codeSelStr, codeSelCountStr;
	wchar_t str[MAX_STR_LENGTH];
	
	codeSelStr.Format(_T("%d"), codeSel);
	WritePrivateProfileStringW(_T("grade"), _T("codeSel"), codeSelStr, filePath);

	codeSelCountStr.Format(_T("%d"), codeSelCount);
	WritePrivateProfileStringW(_T("grade"), _T("codeSelCount"), codeSelCountStr, filePath);


	for (idx = 0; idx < codeSelCount; ++idx)
	{
		tmpStr.Format(_T("%d"), idx + 1);
		tmpStr = L"codeInfo" + tmpStr;
		WritePrivateProfileStringW(_T("grade"), tmpStr, gradeDetailInfos[idx].ToCstring(), filePath);
	}

}

void CapGradeConf::SetCodeSel(int codeSel)
{
	CString filePath = CBatteryUtils::GetConfigPath(_T("\\config\\init\\capgrade.ini"));
	
	this->codeSel = codeSel;

	CString codeSelStr;
	codeSelStr.Format(_T("%d"), codeSel);
	WritePrivateProfileStringW(_T("grade"), _T("codeSel"), codeSelStr, filePath);

}

void CapGradeConf::SetCodeSelCount(int codeSelCount)
{
	CString filePath = CBatteryUtils::GetConfigPath(_T("\\config\\init\\capgrade.ini"));

	this->codeSelCount = codeSelCount;

	CString codeSelCountStr;
	codeSelCountStr.Format(_T("%d"), codeSelCountStr);
	WritePrivateProfileStringW(_T("grade"), _T("codeSel"), codeSelCountStr, filePath);
}

