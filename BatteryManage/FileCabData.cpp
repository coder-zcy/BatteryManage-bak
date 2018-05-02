#include "stdafx.h"
#include "FileCabData.h"
#include "WorkStateStr.h"


CFileCabData::CFileCabData()
{

}

CFileCabData::CFileCabData(CString dataFilePath)
{
	subGroupBatNum = 8;	//	表示八个电池一组

	filePath = dataFilePath;

	testInfo = CDbUtils::GetTestInfo(dataFilePath);
	workProcInfos = CDbUtils::GetWorkProcInfos(dataFilePath);

	groupNumPerCol = testInfo.groupNumPerCol;
	colShowNum = testInfo.colShowNum;
	numPerGroup = testInfo.numPerGroup;
	
	batCount = testInfo.groupNumPerCol * testInfo.colShowNum * testInfo.numPerGroup;


	int endDisStepId = 0;
	cacvStepIds.clear();

//	1、获取恒流放电的工步编号, 初始化每个工步的vector<CPartBattery>为空
	preDisStepIds.clear();

	for (int idx = 0; idx < workProcInfos.size(); ++idx)
	{
		vector<CPartBattery *> tmpPartBatterys;
		for (int jdx = 0; jdx < batCount; ++jdx)
		{
			tmpPartBatterys.push_back(NULL);
		}
		if (workProcInfos[idx].workStepName == CADIS_WORKNAME_STR)
		{
			endDisStepId = idx + 1;
			preDisStepIds.push_back(idx + 1);	//记录放电的工步
		}
		else if (workProcInfos[idx].workStepName == CACV_WORKNAME_STR)
		{
			cacvStepIds.push_back(idx + 1);
		}
		stepPartbatterys.push_back(tmpPartBatterys);
	}
//  2、生成vector<CPartBattery>
	vector<CPartBattery> endStepPartInfos;
	for (int idx = 0; idx < workProcInfos.size(); ++idx)
	{
		if (workProcInfos[idx].workStepName != "结束"){

			//vector<CDbattery> startStepInfo = CDbUtils::GetStartStepInfos(dataFilePath, idx+1);
			//vector<CDbattery> endStepInfo = CDbUtils::GetEndStepInfos(dataFilePath, idx+1);
			//vector<double> avgVolt = CDbUtils::GetAvgVolt(dataFilePath, idx+1);

			vector<CBatStepInfo> batStepInfo = CDbUtils::GetBatStepInfos(dataFilePath, idx + 1);

			if (idx + 1 == endDisStepId)
			{
				//endStepPartInfos = batStepInfos;
				for (int jdx = 0; jdx < batStepInfo.size(); ++jdx)
				{
					endStepPartInfos.push_back(CPartBattery(batStepInfo[jdx]));
				}
			}

			for (int jdx = 0; jdx < batStepInfo.size(); ++jdx)
			{
				stepPartbatterys[idx][batStepInfo[jdx].startStepInfo.batId - 1] = new CPartBattery();
				*(stepPartbatterys[idx][batStepInfo[jdx].startStepInfo.batId - 1]) = batStepInfo[jdx];
			}

			batStepInfos.push_back(batStepInfo);
		}
	}

	// 生成恒流恒压充电的数据记录
	for (int idx = 0; idx < cacvStepIds.size(); ++idx)
	{
		vector<CDbattery> cacvStepInfo = CDbUtils::GetBatCacvSetpInfos(dataFilePath, cacvStepIds[idx]);
		cacvStepInfos.push_back(cacvStepInfo);
	}

	for (int jdx = 0; jdx < batCount; ++jdx)
	{
		endDisBatterys.push_back(NULL);
	}

	for (int jdx = 0; jdx < endStepPartInfos.size(); ++jdx)
	{
		endDisBatterys[endStepPartInfos[jdx].batId - 1] = new CPartBattery();
		*(endDisBatterys[endStepPartInfos[jdx].batId - 1]) = endStepPartInfos[jdx];
	}

	// 更新stepPartBatterys的capFlag
	CapShowType *capShowType = CapShowType::GetInstance();
	int capacity, capFlag;
	 
	for (int idx = 0; idx < stepPartbatterys.size(); ++idx)
	{
		for (int jdx = 0; jdx < stepPartbatterys[idx].size(); ++jdx)
		{
			if (stepPartbatterys[idx][jdx] != NULL)
			{
				capacity = _ttoi(stepPartbatterys[idx][jdx]->capacity);
				capFlag = 0;

				while (capFlag < capShowType->validenum)
				{
					if (capacity < capShowType->minVals[capFlag])
					{
						stepPartbatterys[idx][jdx]->capFlag = capFlag;
						break;
					}
					else if (capacity <= capShowType->maxVals[capFlag])
					{
						stepPartbatterys[idx][jdx]->capFlag = capFlag;
						break;
					}
					else capFlag++;
				}
				if (capFlag == capShowType->validenum)
				{
					stepPartbatterys[idx][jdx]->capFlag = capFlag;
				}
			}
		}
	}

	// 做endStepInfos中batId和实际选中的batId的映射。
	memset(mappings, -1, sizeof(int)* MAX_BAT_NUM);

	if (batStepInfos.size() > 0 && batStepInfos[0].size() > 0)
	for (int idx = 0; idx < batStepInfos[0].size(); ++idx)
	{
		mappings[batStepInfos[0][0].startStepInfo.batId] = idx;
	}

	

}



CFileCabData::~CFileCabData()
{
}

//CFileCabData::CFileCabData(CString dataFilePath)
//{
//	subGroupBatNum = 8;	//	表示八个电池一组
//
//	filePath = dataFilePath;
//
//	testInfo = CDbUtils::GetTestInfo(dataFilePath);
//	workProcInfos = CDbUtils::GetWorkProcInfos(dataFilePath);
//
//	groupNumPerCol = testInfo.groupNumPerCol;
//	colShowNum = testInfo.colShowNum;
//	numPerGroup = testInfo.numPerGroup;
//
//	batCount = testInfo.groupNumPerCol * testInfo.colShowNum * testInfo.numPerGroup;
//
//
//	int endDisStepId = 0;
//
//	//	1、获取恒流放电的工步编号, 初始化每个工步的vector<CPartBattery>为空
//	for (int idx = 0; idx < workProcInfos.size(); ++idx)
//	{
//		vector<CPartBattery *> tmpPartBatterys;
//		for (int jdx = 0; jdx < batCount; ++jdx)
//		{
//			tmpPartBatterys.push_back(NULL);
//		}
//		if (workProcInfos[idx].workStepName == "恒流放电")
//		{
//			endDisStepId = idx + 1;
//		}
//		stepPartbatterys.push_back(tmpPartBatterys);
//	}
//	//  2、生成vector<CPartBattery>
//	for (int idx = 0; idx < workProcInfos.size(); ++idx)
//	{
//		if (workProcInfos[idx].workStepName != "结束"){
//
//			vector<CDbattery> startStepInfo = CDbUtils::GetStartStepInfos(dataFilePath, idx + 1);
//			vector<CDbattery> endStepInfo = CDbUtils::GetEndStepInfos(dataFilePath, idx + 1);
//			vector<double> avgVolt = CDbUtils::GetAvgVolt(dataFilePath, idx + 1);
//
//			vector<CPartBattery> batPartInfos = CDbUtils::GetPartBatData(dataFilePath, idx + 1);
//
//			vector<CPartBattery>  tmp;
//
//			CString str;
//			for (int idx = 0; idx < startStepInfo.size(); ++idx)
//			{
//				CPartBattery battery;
//				str.Format(_T("%d"), int(endStepInfo[idx].atime + 0.5));
//				battery.atime = str;
//
//				str.Format(_T("%d"), int(avgVolt[idx] + 0.5));
//				battery.avgVolt = str;
//
//				str.Format(_T("%d"), int(endStepInfo[idx].capacity + 0.5));
//				battery.capacity = str;
//
//				str.Format(_T("%d"), int(endStepInfo[idx].curnt + 0.5));
//				battery.endCurrent = str;
//
//				str.Format(_T("%d"), int(endStepInfo[idx].voltage + 0.5));
//				battery.endVolt = str;
//
//				str.Format(_T("%d"), int(endStepInfo[idx].energy + 0.5));
//				battery.energy = str;
//
//				str.Format(_T("%d"), int(startStepInfo[idx].voltage + 0.5));
//				battery.openVolt = str;
//
//				battery.batId = startStepInfo[idx].batId;
//
//				tmp.push_back(battery);
//			}
//
//			for (int jdx = 0; jdx < tmp.size(); ++jdx)
//			{
//				stepPartbatterys[idx][tmp[jdx].batId - 1] = new CPartBattery();
//				*(stepPartbatterys[idx][tmp[jdx].batId - 1]) = tmp[jdx];
//			}
//			startStepInfos.push_back(startStepInfo);
//			avgVolts.push_back(avgVolt);
//			endStepInfos.push_back(endStepInfo);
//		}
//	}
//
//	for (int jdx = 0; jdx < batCount; ++jdx)
//	{
//		endDisBatterys.push_back(NULL);
//	}
//
//	vector<CPartBattery> tmp = CDbUtils::GetPartBatData(dataFilePath, endDisStepId);
//	for (int jdx = 0; jdx < tmp.size(); ++jdx)
//	{
//		endDisBatterys[tmp[jdx].batId - 1] = new CPartBattery();
//		*(endDisBatterys[tmp[jdx].batId - 1]) = tmp[jdx];
//	}
//
//	// 更新stepPartBatterys的capFlag
//	CapShowType *capShowType = CapShowType::GetInstance();
//	int capacity, capFlag;
//
//	for (int idx = 0; idx < stepPartbatterys.size(); ++idx)
//	{
//		for (int jdx = 0; jdx < stepPartbatterys[idx].size(); ++jdx)
//		{
//			if (stepPartbatterys[idx][jdx] != NULL)
//			{
//				capacity = _ttoi(stepPartbatterys[idx][jdx]->capacity);
//				capFlag = 0;
//
//				while (capFlag < capShowType->validenum)
//				{
//					if (capacity < capShowType->minVals[capFlag])
//					{
//						stepPartbatterys[idx][jdx]->capFlag = capFlag;
//						break;
//					}
//					else if (capacity <= capShowType->maxVals[capFlag])
//					{
//						stepPartbatterys[idx][jdx]->capFlag = capFlag;
//						break;
//					}
//					else capFlag++;
//				}
//				if (capFlag == capShowType->validenum)
//				{
//					stepPartbatterys[idx][jdx]->capFlag = capFlag;
//				}
//			}
//		}
//	}
//
//	// 做endStepInfos中batId和实际选中的batId的映射。
//	memset(mappings, -1, sizeof(int)* MAX_BAT_NUM);
//
//	if (endStepInfos.size() > 0 && endStepInfos[0].size() > 0)
//	for (int idx = 0; idx < endStepInfos[0].size(); ++idx)
//	{
//		mappings[endStepInfos[0][0].batId] = idx;
//	}
//}

