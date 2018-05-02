#pragma once

#include "CabBattery.h"


#include <iostream>
#include <vector>

using namespace std;

extern const int CABID_POS;
extern const int CMDTYPE_POS;
extern const int CMDTYPE_POS2;
extern const int CMDTYPE_RECV_POS;
extern const int STATE_POS;
extern const int CHUNK_POS;
extern const int BAT_DES_POS;

extern const int CYCLEID_POS;		//	循环编号
extern const int STEPID_POS;		//	该机柜目前的工步编号
extern const int WORKID_POS;		//	工步编号

extern const int INVALIDE_BEAT_STATE;	// 未知的下位机心跳状态
extern const int STANDBY_BEAT_STATE;	//	待机状态
extern const int WORKING_BEAT_STATE;	//	工作
extern const int WORKED_BEAT_STATE;		//	工作结束
extern const int PAUSE_BEAT_STATE;		//	暂停

extern const int BAT_DES_LENGTH;

extern const CString  FRONT_CODE;		//	前导码
extern const int  DATA_LENGTH_POS;		//	数据长度位置

extern BOOL CanConnFlag;				//	是否可以进行连接的标志
extern BOOL PortOpenFlag;				//	串口是否打开的标志
extern BOOL WorkFlag;					//	表明当前上位机的通信进程的工作状态
extern BOOL SendStepFlags[];			//	表示发送下位机工步的状态
extern BOOL PreSendStepFlags[];
extern BOOL IntteruptSendFlag;			//	表示上位机正在工作时发送工步

extern const CString workStateStrs[];			// 描述工作状态的名称

#define MAX_CAB_NUM 20
#define MAX_STEP_NUM 100

//	占位符
const int INVALIDE_PARA_DATA = -1;
//	默认字工步数据的值
const int DEFAULT_PARA_DATA = 0;
const CString DEFAULT_PATA_STR = L"0";


class CLowerCabs
{
public:
	CLowerCabs();
	~CLowerCabs();

void CreateLowerCabs(CString lowerInfos);

void CheckModelInfo(CString lowerInfos, BOOL* obtainModelFlags, int pieceLen);	//	校验下位机的型号

void CheckConInfo(CString lowerInfos, BOOL* cabConFlags, int pieceLen);			//	校验连接结果

void CheckSascInfo(CString lowerInfos, BOOL (*cabStepFlags)[MAX_STEP_NUM], int pieceLen);	//	校验恒流恒压充电工步发送结果

void CheckSaInfo(CString lowerInfos, BOOL(*cabStepFlags)[MAX_STEP_NUM], int pieceLen);		//	校验恒流充电工步发送结果

void CheckSaDisInfo(CString lowerInfos, BOOL(*cabStepFlags)[MAX_STEP_NUM], int pieceLen);	//	校验恒流放电工步发送结果

void CheckLayInfo(CString lowerInfos, BOOL(*cabStepFlags)[MAX_STEP_NUM], int pieceLen);	//	校验搁置工步发送结果

void CheckLoopInfo(CString lowerInfos, BOOL(*cabStepFlags)[MAX_STEP_NUM], int pieceLen);	//	校验循环工步发送结果

void CheckBatInfo(CString lowerInfos);		// 校验收到电池状态的指令
void CreateLowerCabBeat(CString lowerInfos, int* beatStatus);
bool CheckLowerInfos(CString lowerInfos);
public:
	
	vector<CabBattery *> cabBatterys;

};

