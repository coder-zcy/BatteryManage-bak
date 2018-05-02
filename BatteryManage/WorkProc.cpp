#include "stdafx.h"
#include "WorkProc.h"

////全局工序类指针
//void* workProcs[MAX_CAB_NUM] = { NULL };

CWorkProc::CWorkProc()
{
	isNull = FALSE;
	stepNum = 0;
}

CWorkProc::CWorkProc(CString workProcPath)
{

}


CWorkProc::~CWorkProc()
{
}
