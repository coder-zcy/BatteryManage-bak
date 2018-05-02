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

extern const int CYCLEID_POS;		//	ѭ�����
extern const int STEPID_POS;		//	�û���Ŀǰ�Ĺ������
extern const int WORKID_POS;		//	�������

extern const int INVALIDE_BEAT_STATE;	// δ֪����λ������״̬
extern const int STANDBY_BEAT_STATE;	//	����״̬
extern const int WORKING_BEAT_STATE;	//	����
extern const int WORKED_BEAT_STATE;		//	��������
extern const int PAUSE_BEAT_STATE;		//	��ͣ

extern const int BAT_DES_LENGTH;

extern const CString  FRONT_CODE;		//	ǰ����
extern const int  DATA_LENGTH_POS;		//	���ݳ���λ��

extern BOOL CanConnFlag;				//	�Ƿ���Խ������ӵı�־
extern BOOL PortOpenFlag;				//	�����Ƿ�򿪵ı�־
extern BOOL WorkFlag;					//	������ǰ��λ����ͨ�Ž��̵Ĺ���״̬
extern BOOL SendStepFlags[];			//	��ʾ������λ��������״̬
extern BOOL PreSendStepFlags[];
extern BOOL IntteruptSendFlag;			//	��ʾ��λ�����ڹ���ʱ���͹���

extern const CString workStateStrs[];			// ��������״̬������

#define MAX_CAB_NUM 20
#define MAX_STEP_NUM 100

//	ռλ��
const int INVALIDE_PARA_DATA = -1;
//	Ĭ���ֹ������ݵ�ֵ
const int DEFAULT_PARA_DATA = 0;
const CString DEFAULT_PATA_STR = L"0";


class CLowerCabs
{
public:
	CLowerCabs();
	~CLowerCabs();

void CreateLowerCabs(CString lowerInfos);

void CheckModelInfo(CString lowerInfos, BOOL* obtainModelFlags, int pieceLen);	//	У����λ�����ͺ�

void CheckConInfo(CString lowerInfos, BOOL* cabConFlags, int pieceLen);			//	У�����ӽ��

void CheckSascInfo(CString lowerInfos, BOOL (*cabStepFlags)[MAX_STEP_NUM], int pieceLen);	//	У�������ѹ��繤�����ͽ��

void CheckSaInfo(CString lowerInfos, BOOL(*cabStepFlags)[MAX_STEP_NUM], int pieceLen);		//	У�������繤�����ͽ��

void CheckSaDisInfo(CString lowerInfos, BOOL(*cabStepFlags)[MAX_STEP_NUM], int pieceLen);	//	У������ŵ繤�����ͽ��

void CheckLayInfo(CString lowerInfos, BOOL(*cabStepFlags)[MAX_STEP_NUM], int pieceLen);	//	У����ù������ͽ��

void CheckLoopInfo(CString lowerInfos, BOOL(*cabStepFlags)[MAX_STEP_NUM], int pieceLen);	//	У��ѭ���������ͽ��

void CheckBatInfo(CString lowerInfos);		// У���յ����״̬��ָ��
void CreateLowerCabBeat(CString lowerInfos, int* beatStatus);
bool CheckLowerInfos(CString lowerInfos);
public:
	
	vector<CabBattery *> cabBatterys;

};

