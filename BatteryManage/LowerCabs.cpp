#include "stdafx.h"
#include <iostream>
#include <fstream>

#include "LowerCabs.h"
#include "BatteryUtils.h"
#include "StringUtils.h"
#include "BatteryMainView.h"


const int CABID_POS = 4;		//	lowerInfos 中描述机柜编号的字符串中的字符位置
const int CMDTYPE_POS = 8;		//	lowerInfos 工艺码/命令字段字符位置
const int CMDTYPE_POS2 = 10;	//	lowerInfos 工艺码/命令字段字符位置
const int CMDTYPE_RECV_POS = 6;	//	lowerInfos 工艺码/命令字段位置
const int STATE_POS = 8;		//	该机柜目前所处的状态
//const int STEPID_POS = 6;		//	该机柜目前的工步编号

const int CYCLEID_POS = 14;		//	循环编号
const int BEAT_POS = 14;		//	心跳包的位置
const int STEPID_POS = 10;		//	该机柜目前的工步编号
const int STEPID_POS2 = 14;		//	工步编号
const int CYCLEID_POS2 = 16;		//	工步编号

const int WORKID_POS = 12;		//	工艺码，表示是充电、放电还是其它的编号
const int CHUNK_POS2 = 16;		//	lowerInfos 中描述块编号的字符串中的字符位置
const int CHUNBK_POS = 12;
const int BAT_DES_POS = 18;		//	lowerInfos 中描述第一块电池信息的其实位置


// 表示平均描述一块电池的状态所需的字符数为44
const int BAT_DES_LENGTH = 30;	//	单个电池信息的长度

const int LOWERBATINFO_OTHER_LENGTH = 22;	//	下位机发上来的有效电池信息中，其它如cabId，校验结果等描述信息的长度

const int INVALIDE_BEAT_STATE = 0;	//	表示下位机心跳状态未知
const int STANDBY_BEAT_STATE = 1;	//	待机状态
const int WORKING_BEAT_STATE = 2;	//	工作
const int WORKED_BEAT_STATE = 3;	//	工作结束
const int PAUSE_BEAT_STATE = 4;		//	暂停

const int MIN_LOWERBATINFO_LENGTH = 11;	// 获取下位机电池信息最短的长度

#define SUBGROUP_NUM 8
/*----------------------------------------------------------------------------
设置返回字符串长度

----------------------------------------------------------------------------*/

const CString  FRONT_CODE = L"FCFF";	//	前导码
const int  DATA_LENGTH_POS = 6;		//	数据长度位置

const CString workStateStrs[16] = {
	L"", L"恒流恒压充电", L"搁置", L"恒流放电", L"恒流充电", L"循环"
};

BOOL CanConnFlag = FALSE;
BOOL PortOpenFlag = FALSE;
BOOL WorkFlag = TRUE;							//	表明当前上位机的通信进程的工作状态
BOOL SendStepFlags[MAX_CAB_NUM] = { FALSE };	//	表示发送工步的标记
BOOL PreSendStepFlags[MAX_CAB_NUM] = { FALSE };	//	上一次发送工步的标记
BOOL IntteruptSendFlag = FALSE;					//	表示上位机正在工作时发送工步



CLowerCabs::CLowerCabs()
{

	// 初始化指向各个机柜的电池状态的指针为NULL
	for (int idx = 0; idx < MAX_CAB_NUM; ++idx)
	{
		cabBatterys.push_back(NULL);
	}
}


CLowerCabs::~CLowerCabs()
{
	for (int idx = 0; idx < MAX_CAB_NUM; ++idx)
	{
		if (cabBatterys[idx] != NULL)
		{
			delete cabBatterys[idx];
			cabBatterys[idx] = NULL;
		}
	}
}

// 校验下位机穿上来的下位机型号信息
void CLowerCabs::CheckModelInfo(CString lowerInfos, BOOL* obtainModelFlags, int pieceLen)
{
	//BOOL obtainModelFlag[MAX_CAB_NUM];

	if (lowerInfos.GetLength() < (CABID_POS + 2) || lowerInfos.GetLength() != pieceLen)
	{
		return;
	}
	int cabId = ascmapping[lowerInfos.GetAt(CABID_POS)] * 16 +
		ascmapping[lowerInfos.GetAt(CABID_POS + 1)];
	if (cabId > 0 && cabId <= MAX_CAB_NUM)
	{
		obtainModelFlags[cabId - 1] = TRUE;
	}
}

/*
	根据机柜ID和电池板块号获取的下位机信息
*/

//void CLowerCabs::CreateLowerCabs(CString lowerInfos)
//{
//	// 1 根据lowerInfos字符串获取cabId
//	// 2 根据lowerInfos字符串获取电池初始编号
//	// 3 根据字符串中固定的长度初始化电池
//
//	if (lowerInfos.GetLength() < 4)
//		return;
//	if (!((lowerInfos[0] == 'F') && lowerInfos[1] == 'C' && lowerInfos[2] == 'F' && lowerInfos[3] == 'F'))
//		return;
//	int cabId = ascmapping[lowerInfos.GetAt(CABID_POS)] * 16 +
//		ascmapping[lowerInfos.GetAt(CABID_POS + 1)];
//
//	int startBatId = (ascmapping[lowerInfos.GetAt(CHUNK_POS2)] * 16 +
//		ascmapping[lowerInfos.GetAt(CHUNK_POS2 + 1)]) * SUBGROUP_NUM;
//
//	int endBatId = startBatId + 7;	// 表示一组由8块电池	
//	int cabStat = ascmapping[lowerInfos.GetAt(WORKID_POS)] * 16 +
//		ascmapping[lowerInfos.GetAt(WORKID_POS + 1)];
//	
//	int stepId = ascmapping[lowerInfos.GetAt(STEPID_POS2)] * 16 +
//		ascmapping[lowerInfos.GetAt(STEPID_POS2 + 1)];
//
//	int cycleId = ascmapping[lowerInfos.GetAt(CYCLEID_POS)] * 16 +
//		ascmapping[lowerInfos.GetAt(CYCLEID_POS + 1)];
//	
//
//	int workId = ascmapping[lowerInfos.GetAt(WORKID_POS)] * 16 +
//		ascmapping[lowerInfos.GetAt(WORKID_POS + 1)];
//
//
//	//int cabStat = 0;
//	// strIdx 表示电池的状态采用字符串描述的位置
//
//	for (int idx = startBatId, strIdx =  BAT_DES_POS; idx <= endBatId; ++idx)
//	{
//
//		CString batStr = lowerInfos.Mid(strIdx, BAT_DES_LENGTH);
//		CBattery battery(batStr, cabStat);
//		
//		if (cabBatterys[cabId - 1] == NULL)
//		{
//			cabBatterys[cabId - 1] = new CabBattery(cabId, workId, stepId, cycleId);
//		}
//		
//		cabBatterys[cabId - 1]->cabId = cabId;
//		cabBatterys[cabId - 1]->cabState = cabStat;
//		cabBatterys[cabId - 1]->workId = workId;
//		cabBatterys[cabId - 1]->stepId = stepId;
//		cabBatterys[cabId - 1]->cycleId = cycleId;
//		//cabBatterys[cabId - 1]->cycleId = 0;
//
//		(cabBatterys[cabId - 1]->batterys)[idx] = battery;
//
//		strIdx += BAT_DES_LENGTH;	
//		
//	}
//
//	if (91 > startBatId && 91 < endBatId)
//	{
//		std::ofstream   outfile;
//		outfile.open("logs.txt", ios::out|ios::app);
//		outfile << "startBatId:" << startBatId << endl;
//		outfile << "endBatId:" << endBatId << endl;
//		outfile << CT2A(lowerInfos.GetBuffer()) << endl;
//	}
//
//}
/*
有参数时命令返回

序号	工艺指令结构	数值（HEX）	长度（字节）	注
1	前导码	FCFF	2	通信起始标志
2	机柜号	01		1	机柜地址编号
3	数据长度	XXXX	2	后面的字节数
4	通信命令	0x06	1	通信命令字
5	工艺码	0x06	1	一个阶段
6	工步号	0x00 - 0xff	1	工步第几次作业
7	循环	0x00 - 0x0FF	1	第几次循环
8	ID点号	XXXX	2	00 - 511
9	停止原因	XX 	1	点状态
10	电压		2	采样的电压
11	电流		2	采样电流
12	时间		2
13	容量		2
14	电量		4
......
ID点号	XXXX	2	00 - 511
停止原因	XX 	1	点状态
电压		2	采样的电压
电流		2	采样电流
时间		2
容量		2
电量		4
校验位	XX	1	加总异或
结束位	0xAB	1

*/

/*
	无参数时命令返回
	参数返回
	序号	工艺指令结构	数值（HEX）	长度（字节）	注
	1	前导码	FCFF	2	通信起始标志
	2	机柜号	01	1	机柜地址编号
	3	数据长度	XXXX	2	后面的字节数
	4	通信命令	0x06	1	通信命令字
	5	工艺码	0x06	1	一个阶段
	6	工步号	0x00-0xff	1	工步第几次作业
	7	循环	0x00-0x0FF	1	第几次循环
	8	校验位	XX	1	加总异或
	9	结束位	0xAB	1
*/
void CLowerCabs::CreateLowerCabs(CString lowerInfos)
{
	// 1 根据lowerInfos字符串获取cabId
	// 2 根据lowerInfos字符串获取电池初始编号
	// 3 根据字符串中固定的长度初始化电池
	
	// 无有效下位机电池信息的均被忽略
	int lowerInfoLength = lowerInfos.GetLength();

	if (lowerInfoLength <= MIN_LOWERBATINFO_LENGTH)
		return;
	if (!((lowerInfos[0] == 'F') && lowerInfos[1] == 'C' && lowerInfos[2] == 'F' && lowerInfos[3] == 'F'))
		return;
	// 校验下位机信息
	if (!CheckLowerInfos(lowerInfos))
		return;

	int cabId = ascmapping[lowerInfos.GetAt(CABID_POS)] * 16 +
		ascmapping[lowerInfos.GetAt(CABID_POS + 1)];
	int dataLength = ascmapping[lowerInfos.GetAt(DATA_LENGTH_POS)] * 4096 + ascmapping[lowerInfos.GetAt(DATA_LENGTH_POS+1)] * 256 
		+ ascmapping[lowerInfos.GetAt(DATA_LENGTH_POS + 2)] * 16 + ascmapping[lowerInfos.GetAt(DATA_LENGTH_POS + 3)];
	
	int stepId = ascmapping[lowerInfos.GetAt(STEPID_POS2)] * 16 +
		ascmapping[lowerInfos.GetAt(STEPID_POS2 + 1)];

	int cycleId = ascmapping[lowerInfos.GetAt(CYCLEID_POS2)] * 16 +
		ascmapping[lowerInfos.GetAt(CYCLEID_POS2 + 1)];

	int batIdx = ascmapping[lowerInfos.GetAt(BAT_DES_POS)] * 4096 + ascmapping[lowerInfos.GetAt(BAT_DES_POS + 1)] * 256
		+ ascmapping[lowerInfos.GetAt(BAT_DES_POS + 2)] * 16 + ascmapping[lowerInfos.GetAt(BAT_DES_POS + 3)];

	int batNum = (lowerInfoLength - LOWERBATINFO_OTHER_LENGTH) / BAT_DES_LENGTH;
	
	int cabStat = ascmapping[lowerInfos.GetAt(WORKID_POS)] * 16 +
		ascmapping[lowerInfos.GetAt(WORKID_POS + 1)];
	int workId = cabStat;

	// strIdx 表示电池的状态采用字符串描述的位置

	for (int idx = 0, strIdx = BAT_DES_POS; idx < batNum; ++idx)
	{
		CString batStr = lowerInfos.Mid(strIdx, BAT_DES_LENGTH);
		CBattery battery(batStr, cabStat);
		CString batIdStr = batStr.Left(4);
		int batId = ascmapping[batIdStr[0]] * 4096 + ascmapping[batIdStr[1]] * 256
			+ ascmapping[batIdStr[2]] * 16 + ascmapping[batIdStr[3]];

		if (cabBatterys[cabId - 1] == NULL)
		{
			cabBatterys[cabId - 1] = new CabBattery(cabId, workId, stepId, cycleId);
		}

		cabBatterys[cabId - 1]->cabId = cabId;
		cabBatterys[cabId - 1]->cabState = cabStat;
		cabBatterys[cabId - 1]->workId = workId;
		cabBatterys[cabId - 1]->stepId = stepId;
		cabBatterys[cabId - 1]->cycleId = cycleId;
		(cabBatterys[cabId - 1]->batterys)[batId] = battery;

		strIdx += BAT_DES_LENGTH;
	}

	//if (91 > startBatId && 91 < endBatId)
	//{
	//	std::ofstream   outfile;
	//	outfile.open("logs.txt", ios::out | ios::app);
	//	outfile << "startBatId:" << startBatId << endl;
	//	outfile << "endBatId:" << endBatId << endl;
	//	outfile << CT2A(lowerInfos.GetBuffer()) << endl;
	//}
}


void CLowerCabs::CheckConInfo(CString lowerInfos, BOOL* cabConFlags, int pieceLen)
{
	//BOOL obtainModelFlag[MAX_CAB_NUM];

	if (lowerInfos.GetLength() < (CABID_POS + 2) || lowerInfos.GetLength() != pieceLen)
	{
		return;
	}

	int cabId = ascmapping[lowerInfos.GetAt(CABID_POS)] * 16 +
		ascmapping[lowerInfos.GetAt(CABID_POS + 1)];

	if (cabId > 0 && cabId <= MAX_CAB_NUM)
	{
		cabConFlags[cabId - 1] = TRUE;
	}
}

void CLowerCabs::CheckSascInfo(CString lowerInfos, BOOL(*cabStepFlags)[MAX_STEP_NUM], int pieceLen)
{
	//BOOL obtainModelFlag[MAX_CAB_NUM];
	// 如果lowerInfos信息不足,则忽略这条信息
	if (lowerInfos.GetLength() < (STEPID_POS + 2) || lowerInfos.GetLength() != pieceLen)
	{
		return;
	}

	int cabId = ascmapping[lowerInfos.GetAt(CABID_POS)] * 16 +
		ascmapping[lowerInfos.GetAt(CABID_POS + 1)];
	int stepId = ascmapping[lowerInfos.GetAt(STEPID_POS)] * 16 +
		ascmapping[lowerInfos.GetAt(STEPID_POS + 1)];

	if (cabId > 0 && cabId <= MAX_CAB_NUM)
	{
		(cabStepFlags)[cabId - 1][stepId-1] = TRUE;
	}
}

void CLowerCabs::CheckSaDisInfo(CString lowerInfos, BOOL(*cabStepFlags)[MAX_STEP_NUM], int pieceLen)
{
	if (lowerInfos.GetLength() < (STEPID_POS + 2) || lowerInfos.GetLength() != pieceLen)
	{
		return;
	}

	int cabId = ascmapping[lowerInfos.GetAt(CABID_POS)] * 16 +
		ascmapping[lowerInfos.GetAt(CABID_POS + 1)];
	int stepId = ascmapping[lowerInfos.GetAt(STEPID_POS)] * 16 +
		ascmapping[lowerInfos.GetAt(STEPID_POS + 1)];

	if (cabId > 0 && cabId <= MAX_CAB_NUM)
	{
		(cabStepFlags)[cabId - 1][stepId - 1] = TRUE;
	}
}

void CLowerCabs::CheckLayInfo(CString lowerInfos, BOOL(*cabStepFlags)[MAX_STEP_NUM], int pieceLen)
{
	if (lowerInfos.GetLength() < (STEPID_POS + 2) || lowerInfos.GetLength() != pieceLen)
	{
		return;
	}

	int cabId = ascmapping[lowerInfos.GetAt(CABID_POS)] * 16 +
		ascmapping[lowerInfos.GetAt(CABID_POS + 1)];
	int stepId = ascmapping[lowerInfos.GetAt(STEPID_POS)] * 16 +
		ascmapping[lowerInfos.GetAt(STEPID_POS + 1)];

	if (cabId > 0 && cabId <= MAX_CAB_NUM)
	{
		(cabStepFlags)[cabId - 1][stepId - 1] = TRUE;
	}
}

void CLowerCabs::CheckLoopInfo(CString lowerInfos, BOOL(*cabStepFlags)[MAX_STEP_NUM], int pieceLen)
{
	if (lowerInfos.GetLength() < (STEPID_POS + 2) || lowerInfos.GetLength() != pieceLen)
	{
		return;
	}

	int cabId = ascmapping[lowerInfos.GetAt(CABID_POS)] * 16 +
		ascmapping[lowerInfos.GetAt(CABID_POS + 1)];
	int stepId = ascmapping[lowerInfos.GetAt(STEPID_POS)] * 16 +
		ascmapping[lowerInfos.GetAt(STEPID_POS + 1)];

	if (cabId > 0 && cabId <= MAX_CAB_NUM)
	{
		(cabStepFlags)[cabId - 1][stepId - 1] = TRUE;
	}
}

void CLowerCabs::CheckBatInfo(CString lowerInfos)
{

}

void CLowerCabs::CheckSaInfo(CString lowerInfos, BOOL(*cabStepFlags)[MAX_STEP_NUM], int pieceLen)
{
	if (lowerInfos.GetLength() < (STEPID_POS + 2) || lowerInfos.GetLength() != pieceLen)
	{
		return;
	}

	int cabId = ascmapping[lowerInfos.GetAt(CABID_POS)] * 16 +
		ascmapping[lowerInfos.GetAt(CABID_POS + 1)];
	int stepId = ascmapping[lowerInfos.GetAt(STEPID_POS)] * 16 +
		ascmapping[lowerInfos.GetAt(STEPID_POS + 1)];

	if (cabId > 0 && cabId <= MAX_CAB_NUM)
	{
		(cabStepFlags)[cabId - 1][stepId - 1] = TRUE;
	}
}

void CLowerCabs::CreateLowerCabBeat(CString lowerInfos, int* beatStatus)
{
	int cabId = ascmapping[lowerInfos.GetAt(CABID_POS)] * 16 +
		ascmapping[lowerInfos.GetAt(CABID_POS + 1)];

	int cabStatus = ascmapping[lowerInfos.GetAt(BEAT_POS)] * 16 +
		ascmapping[lowerInfos.GetAt(BEAT_POS + 1)];

	if (cabId >= MIN_CAB_NUM && cabId <= MAX_CAB_NUM)
	{
		beatStatus[cabId - 1] = cabStatus;
	}
}

// 对下位机信息进行校验
bool CLowerCabs::CheckLowerInfos(CString lowerInfos)
{
	return TRUE;
}
