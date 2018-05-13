#pragma once
#include <iostream>
#include <vector>

using namespace std;
#define MAX_LEVEL_NUM 100

#define MAX_DIS_NUM 13

#define CAP_DIS_IDX 0
#define TIME_DIS_IDX 1
#define OPEN_DIS_IDX 2
#define AVG_DIS_IDX 3
#define POINT1_DIS_IDX 4
#define POINT2_DIS_IDX 5
#define POINT3_DIS_IDX 6
#define POINT4_DIS_IDX 7
#define POINT5_DIS_IDX 8
#define END_DIS_IDX 9
#define RESIST_DIS_IDX 10
#define SD_DIS_IDX 11
#define MID_DIS_IDX 12

class CGradeDetailInfo
{
public:
	CGradeDetailInfo();
	CGradeDetailInfo(CString detailStr);
	CString ToCstring();
	~CGradeDetailInfo();
public:
	CString codeName;
	CString para;
	int levelCount;
	int selCount;
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
	int defDisArrays[MAX_DIS_NUM];
	CString startArraysStr[MAX_DIS_NUM];

	int startArrays[MAX_DIS_NUM];
	int startIdxs[MAX_DIS_NUM];
	//vector<CString> defDisArraysStr;
	CString defDisArraysStr[MAX_DIS_NUM];
	vector<vector<CString> > endArraysStr;
	vector<CString> levelNames;
	

	CGradeDetailInfo& operator=(const CGradeDetailInfo gradeDetailInfo);
};

