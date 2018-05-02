#include "stdafx.h"
#include "BatteryUtils.h"


CString CBatteryUtils::GetConfigPath(CString relativePath)
{
	TCHAR szAbsPathFile[MAX_PATH + 1] = { NULL };
	GetModuleFileName(NULL, szAbsPathFile, MAX_PATH);
	PathRemoveFileSpec(szAbsPathFile);
	PathAppend(szAbsPathFile, relativePath);
	return szAbsPathFile;
}


void CBatteryUtils::GetSplitedStr(CString str, CStringArray &strArray, char c)
{
	strArray.RemoveAll();

	CString strTemp = str;
	int iIndex = 0;
	while (1)
	{
		iIndex = strTemp.Find(c);
		if (iIndex >= 0)
		{
			strArray.Add(strTemp.Left(iIndex));
			strTemp = strTemp.Right(strTemp.GetLength() - iIndex - 1);
		}
		else
		{
			break;
		}
	}
	strArray.Add(strTemp);
}

