#include "stdafx.h"
#include "GradeDetailInfo.h"
#include "StringUtils.h"

CGradeDetailInfo::CGradeDetailInfo(CString detailStr)
{
	vector<CString> helpStrs = StringUtils::SplitByCstr(detailStr,L";");
	// 需要加健壮性判断
	int length = helpStrs.size();
	
	codeName = length > 0 ? helpStrs[0] : L"";
	levelCount = length > 1 ? _ttoi(helpStrs[1]) : 0;
	
	para = length > 2 ? helpStrs[2] : L"0000000000000";
	if (para.GetLength() < MAX_DIS_NUM) {
		while (para.GetLength() < MAX_DIS_NUM)
		{
			para += L"0";
		}
	}

	CString defStartValsStr = length > 3 ? helpStrs[3] : L"100,100,100,100,100,100,100,100,100,100,100,100,100";
	startArraysStr = StringUtils::SplitByCstr(defStartValsStr, L",");

	while (startArraysStr.size() < MAX_DIS_NUM)
	{
		startArraysStr.push_back(L"100");
		
	}
	for (int idx = 0; idx < MAX_DIS_NUM; ++idx)
	{
		startArrays[idx] = _ttoi(startArraysStr[idx]);
	}

	CString defDisValsStr = length > 4 ? helpStrs[4] : L"100,100,100,100,100,100,100,100,100,100,100,100,100";
	disArraysStr = StringUtils::SplitByCstr(defDisValsStr, L",");


	while (disArraysStr.size() < MAX_DIS_NUM)
	{
		disArraysStr.push_back(L"100");
	}
	for (int idx = 0; idx < MAX_DIS_NUM; ++idx)
	{
		disArrays[idx] = _ttoi(disArraysStr[idx]);
	}

	CString levelNamesStr = length > 5 ? helpStrs[5] : L"";
	levelNames = StringUtils::SplitByCstr(levelNamesStr, L",");

	while (levelNames.size() < MAX_DIS_NUM)
	{
		levelNames.push_back(L"");
	}
}


CGradeDetailInfo::CGradeDetailInfo()
{
	codeName = "分容测试";
	para = "0000000000000";
	int levelCount;
	//int capDis;
	//int	timeDis;
	//int openDis;
	//int avgDis;
	//int point1Dis;
	//int point2Dis;
	//int point3Dis;
	//int point4Dis;
	//int point5Dis;
	//int endDis;
	//int resistDis;
	//int sdDis;
	//int midDis;
	memset(disArrays, 0, sizeof(int)* MAX_DIS_NUM);
	memset(startArrays, 0, sizeof(int)*MAX_DIS_NUM);
	CString str;
	for (int idx = 0; idx < MAX_DIS_NUM; ++idx)
	{
		str.Format(_T("%d"), idx + 1);
		startArraysStr.push_back(0);
		disArraysStr.push_back(0);
		levelNames.push_back(L"等级" + str);
	}
}

/*
codeName + levelCount + para + startArraysStr + disArraysStr + levelNames
*/
CString CGradeDetailInfo::ToCstring()
{
	CString result = codeName;
	CString levelCountStr, startStr = L"", disStr=L"", levelNamesStr=L"";
	int idx;
	levelCountStr.Format(_T("%d"), levelCount);
	result += L";" + levelCountStr + L";" + para;

	for (idx = 0; idx < startArraysStr.size()-1; ++idx)
	{
		startStr += startArraysStr[idx] + L",";
	}
	startStr += startArraysStr[idx];
	
	for (idx = 0; idx < disArraysStr.size()-1; ++idx)
	{
		disStr += disArraysStr[idx] + L",";
	}
	disStr += disArraysStr[idx];

	for (idx = 0; idx < levelNames.size()-1; ++idx)
	{
		levelNamesStr += levelNames[idx] + L",";
	}
	levelNamesStr += levelNames[idx];

	result += L";" + startStr + L";" + disStr + L";" + levelNamesStr;

	return result;
}

CGradeDetailInfo::~CGradeDetailInfo()
{
}

CGradeDetailInfo& CGradeDetailInfo::operator=(const CGradeDetailInfo gradeDetailInfo)
{
	this->codeName = gradeDetailInfo.codeName;
	memcpy(this->disArrays, gradeDetailInfo.disArrays, sizeof(int)* MAX_DIS_NUM);
	this->disArraysStr = gradeDetailInfo.disArraysStr;
	this->levelCount = gradeDetailInfo.levelCount;
	this->levelNames = gradeDetailInfo.levelNames;
	this->para = gradeDetailInfo.para;
	memcpy(this->startArrays, gradeDetailInfo.startArrays, sizeof(int) * MAX_DIS_NUM);
	this->startArraysStr = gradeDetailInfo.startArraysStr;

	return *this;
}
