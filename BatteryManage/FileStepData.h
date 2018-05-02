#pragma once
#include "TestInfo.h"
#include "WorkProcInfo.h"

#include <iostream>
#include <vector>
using namespace std;

class CFileStepData
{
public:
	CFileStepData();
	CFileStepData(CString dataFilePath);
	~CFileStepData();
	void DestroyData();

public:
	CString filePath;
	TestInfo testInfo;
	vector<WorkProcInfo> workProcInfos;
	int stepNum;
};

