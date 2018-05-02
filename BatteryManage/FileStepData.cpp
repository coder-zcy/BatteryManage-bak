#include "stdafx.h"
#include "FileStepData.h"
#include "DbUtils.h"

CFileStepData::CFileStepData()
{
}


CFileStepData::CFileStepData(CString dataFilePath)
{
	filePath = dataFilePath;
	stepNum = 0;
	testInfo = CDbUtils::GetTestInfo(dataFilePath);
	workProcInfos = CDbUtils::GetWorkProcInfos(dataFilePath);

	stepNum = workProcInfos.size();
	if (stepNum > 0 && workProcInfos[stepNum - 1].workStepName == "½áÊø")
	{
		stepNum--;
	}
}

CFileStepData::~CFileStepData()
{

}

void CFileStepData::DestroyData()
{
	this->filePath = L"";
	this->testInfo.cabinet = -1;
}
