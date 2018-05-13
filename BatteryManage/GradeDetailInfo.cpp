#include "stdafx.h"
#include "GradeDetailInfo.h"
#include "StringUtils.h"

#define CODE_NAME_IDX 0
#define LEVEL_COUNT_IDX 1
#define SELECT_IDX 2
#define START_VAL_IDX 3
#define DEF_DIS_IDX 4
#define END_VAL_IDX 5
#define LEVEL_NAME_IDX 6
CGradeDetailInfo::CGradeDetailInfo(CString detailStr)
{
	vector<CString> helpStrs = StringUtils::SplitByCstr(detailStr,L";");
	endArraysStr.clear();
	memset(startIdxs, -1, sizeof(int)*MAX_DIS_NUM);
	// 需要加健壮性判断
	int length = helpStrs.size();
	selCount = 0;
	int idx, jdx;
	codeName = length > CODE_NAME_IDX ? helpStrs[CODE_NAME_IDX] : L"";
	levelCount = length > LEVEL_COUNT_IDX ? _ttoi(helpStrs[LEVEL_COUNT_IDX]) : 0;
	
	// 生成para
	para = length > SELECT_IDX ? helpStrs[SELECT_IDX] : L"0000000000000";
	if (para.GetLength() < MAX_DIS_NUM) {
		while (para.GetLength() < MAX_DIS_NUM)
		{
			para += L"0";
		}
	}
	int kdx = 0;
	for (idx = 0; idx < para.GetLength(); ++idx) {
		if (para[idx] == '1') {
			selCount++;
			startIdxs[kdx++] = idx;
		}
	}

	// 生成startValsStr 最大MAX_DIS_NUM个
	CString defStartValsStr = length > START_VAL_IDX ? helpStrs[START_VAL_IDX] : L"100,100,100,100,100,100,100,100,100,100,100,100,100";
	vector<CString> strs = StringUtils::SplitByCstr(defStartValsStr, L",");

	while (strs.size() < MAX_DIS_NUM)
	{
		strs.push_back(L"100");
	}
	for (int idx = 0; idx < MAX_DIS_NUM; ++idx)
	{
		startArraysStr[idx] = strs[idx];
		startArrays[idx] = _ttoi(startArraysStr[idx]);
	}

	CString defDisValsStr = length > DEF_DIS_IDX ? helpStrs[DEF_DIS_IDX] : 
		L"100,100,100,100,100,100,100,100,100,100,100,100,100";
	strs = StringUtils::SplitByCstr(defDisValsStr, L",");
	
	while (strs.size() < MAX_DIS_NUM)
	{
		strs.push_back(L"0");
	}
	for (int idx = 0; idx < MAX_DIS_NUM; ++idx)
	{
		defDisArraysStr[idx] = strs[idx];
	}

	for (int idx = 0; idx < MAX_DIS_NUM; ++idx)
	{
		defDisArrays[idx] = _ttoi(defDisArraysStr[idx]);
	}

	// 生成每个level每一行的最终数值
	CString endStr = length > END_VAL_IDX ? helpStrs[END_VAL_IDX] : L"";
	vector<CString> endArrayStr = StringUtils::SplitByCstr(endStr, L",");
	int endLength = endArrayStr.size();
	int k = 0;
	for (idx = 0; idx < selCount; ++ idx)
	{
		vector<CString> t;
		endArraysStr.push_back(t);
		for (jdx = 0; jdx < levelCount; ++jdx)
		{
			if (k < endLength) {
				endArraysStr[idx].push_back(endArrayStr[k]);
			}
			else {
				endArraysStr[idx].push_back(0);
			}
			++k;
		}
	}

	// 生成LevelName
	CString levelNamesStr = length > LEVEL_NAME_IDX ? helpStrs[LEVEL_NAME_IDX] : L"";
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
	memset(defDisArrays, 0, sizeof(int)* MAX_DIS_NUM);
	memset(startArrays, 0, sizeof(int)*MAX_DIS_NUM);
	CString str;
	for (int idx = 0; idx < MAX_DIS_NUM; ++idx)
	{
		str.Format(_T("%d"), idx + 1);
		startArraysStr[idx] = L"0";
		defDisArraysStr[idx] = L"0";
		levelNames.push_back(L"等级" + str);
	}
}

/*
codeName + levelCount + para + startArraysStr + disArraysStr + levelNames
*/
CString CGradeDetailInfo::ToCstring()
{
	CString result = codeName;
	CString levelCountStr, startStr = L"", defDisStr=L"", endStr = L"", levelNamesStr=L"";
	int idx, jdx;
	levelCountStr.Format(_T("%d"), levelCount);
	result += L";" + levelCountStr + L";" + para;

	for (idx = 0; idx < MAX_DIS_NUM-1; ++idx)
	{
		startStr += startArraysStr[idx] + L",";
	}
	startStr += startArraysStr[idx];
	
	for (idx = 0; idx < MAX_DIS_NUM - 1; ++idx)
	{
		defDisStr += defDisArraysStr[idx] + L",";
	}
	defDisStr += defDisArraysStr[idx];

	// 生成endStr
	for (idx = 0; idx < selCount; ++idx)
	{
		for (jdx = 0; jdx < levelCount; ++jdx)
		{
			endStr += endArraysStr[idx][jdx] + L",";
		}
	}
	if (endStr.GetLength() > 0)
	{
		endStr = endStr.Mid(0,endStr.GetLength() - 1);
	}
	

	for (idx = 0; idx < levelNames.size()-1; ++idx)
	{
		levelNamesStr += levelNames[idx] + L",";
	}
	levelNamesStr += levelNames[idx];

	result += L";" + startStr + L";" + defDisStr + L";" + endStr + L";" + levelNamesStr;

	return result;
}

CGradeDetailInfo::~CGradeDetailInfo()
{
}

CGradeDetailInfo& CGradeDetailInfo::operator=(const CGradeDetailInfo gradeDetailInfo)
{
	this->codeName = gradeDetailInfo.codeName;
	memcpy(this->defDisArrays, gradeDetailInfo.defDisArrays, sizeof(int)* MAX_DIS_NUM);

	this->endArraysStr = gradeDetailInfo.endArraysStr;

	this->levelCount = gradeDetailInfo.levelCount;
	this->levelNames = gradeDetailInfo.levelNames;
	this->para = gradeDetailInfo.para;
	this->selCount = gradeDetailInfo.selCount;
	
	memcpy(this->startArrays, gradeDetailInfo.startArrays, sizeof(int) * MAX_DIS_NUM);
	//memcpy(this->startArraysStr, gradeDetailInfo.startArraysStr, sizeof(CString)*MAX_DIS_NUM);
	for (int idx = 0; idx < MAX_DIS_NUM; ++idx)
	{
		this->startArraysStr[idx] = gradeDetailInfo.startArraysStr[idx];
		this->defDisArraysStr[idx] = gradeDetailInfo.defDisArraysStr[idx];
	}
	memcpy(this->startIdxs, gradeDetailInfo.startIdxs, sizeof(int)*MAX_DIS_NUM);
	
	
	return *this;
}
