#pragma once

#include <iostream>
#include <vector>

using namespace std;

#include "LowerCabs.h"
#include "WorkStep.h"


/*
工序类
*/

////全局工序类指针
//extern void* workProcs[];

class CWorkProc
{
public:
	CWorkProc();
	CWorkProc(CString workProcPath);

	~CWorkProc();
public:
	
	BOOL isNull;
	CString workProcName;
	CString model;
	int stepNum;
	vector<CWorkStep> workSteps;

};

