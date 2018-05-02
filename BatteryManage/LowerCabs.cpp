#include "stdafx.h"
#include <iostream>
#include <fstream>

#include "LowerCabs.h"
#include "BatteryUtils.h"
#include "StringUtils.h"
#include "BatteryMainView.h"


const int CABID_POS = 4;		//	lowerInfos �����������ŵ��ַ����е��ַ�λ��
const int CMDTYPE_POS = 8;		//	lowerInfos ������/�����ֶ��ַ�λ��
const int CMDTYPE_POS2 = 10;	//	lowerInfos ������/�����ֶ��ַ�λ��
const int CMDTYPE_RECV_POS = 6;	//	lowerInfos ������/�����ֶ�λ��
const int STATE_POS = 8;		//	�û���Ŀǰ������״̬
//const int STEPID_POS = 6;		//	�û���Ŀǰ�Ĺ������

const int CYCLEID_POS = 14;		//	ѭ�����
const int BEAT_POS = 14;		//	��������λ��
const int STEPID_POS = 10;		//	�û���Ŀǰ�Ĺ������
const int STEPID_POS2 = 14;		//	�������
const int CYCLEID_POS2 = 16;		//	�������

const int WORKID_POS = 12;		//	�����룬��ʾ�ǳ�硢�ŵ绹�������ı��
const int CHUNK_POS2 = 16;		//	lowerInfos ���������ŵ��ַ����е��ַ�λ��
const int CHUNBK_POS = 12;
const int BAT_DES_POS = 18;		//	lowerInfos ��������һ������Ϣ����ʵλ��


// ��ʾƽ������һ���ص�״̬������ַ���Ϊ44
const int BAT_DES_LENGTH = 30;	//	���������Ϣ�ĳ���

const int LOWERBATINFO_OTHER_LENGTH = 22;	//	��λ������������Ч�����Ϣ�У�������cabId��У������������Ϣ�ĳ���

const int INVALIDE_BEAT_STATE = 0;	//	��ʾ��λ������״̬δ֪
const int STANDBY_BEAT_STATE = 1;	//	����״̬
const int WORKING_BEAT_STATE = 2;	//	����
const int WORKED_BEAT_STATE = 3;	//	��������
const int PAUSE_BEAT_STATE = 4;		//	��ͣ

const int MIN_LOWERBATINFO_LENGTH = 11;	// ��ȡ��λ�������Ϣ��̵ĳ���

#define SUBGROUP_NUM 8
/*----------------------------------------------------------------------------
���÷����ַ�������

----------------------------------------------------------------------------*/

const CString  FRONT_CODE = L"FCFF";	//	ǰ����
const int  DATA_LENGTH_POS = 6;		//	���ݳ���λ��

const CString workStateStrs[16] = {
	L"", L"������ѹ���", L"����", L"�����ŵ�", L"�������", L"ѭ��"
};

BOOL CanConnFlag = FALSE;
BOOL PortOpenFlag = FALSE;
BOOL WorkFlag = TRUE;							//	������ǰ��λ����ͨ�Ž��̵Ĺ���״̬
BOOL SendStepFlags[MAX_CAB_NUM] = { FALSE };	//	��ʾ���͹����ı��
BOOL PreSendStepFlags[MAX_CAB_NUM] = { FALSE };	//	��һ�η��͹����ı��
BOOL IntteruptSendFlag = FALSE;					//	��ʾ��λ�����ڹ���ʱ���͹���



CLowerCabs::CLowerCabs()
{

	// ��ʼ��ָ���������ĵ��״̬��ָ��ΪNULL
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

// У����λ������������λ���ͺ���Ϣ
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
	���ݻ���ID�͵�ذ��Ż�ȡ����λ����Ϣ
*/

//void CLowerCabs::CreateLowerCabs(CString lowerInfos)
//{
//	// 1 ����lowerInfos�ַ�����ȡcabId
//	// 2 ����lowerInfos�ַ�����ȡ��س�ʼ���
//	// 3 �����ַ����й̶��ĳ��ȳ�ʼ�����
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
//	int endBatId = startBatId + 7;	// ��ʾһ����8����	
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
//	// strIdx ��ʾ��ص�״̬�����ַ���������λ��
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
�в���ʱ�����

���	����ָ��ṹ	��ֵ��HEX��	���ȣ��ֽڣ�	ע
1	ǰ����	FCFF	2	ͨ����ʼ��־
2	�����	01		1	�����ַ���
3	���ݳ���	XXXX	2	������ֽ���
4	ͨ������	0x06	1	ͨ��������
5	������	0x06	1	һ���׶�
6	������	0x00 - 0xff	1	�����ڼ�����ҵ
7	ѭ��	0x00 - 0x0FF	1	�ڼ���ѭ��
8	ID���	XXXX	2	00 - 511
9	ֹͣԭ��	XX 	1	��״̬
10	��ѹ		2	�����ĵ�ѹ
11	����		2	��������
12	ʱ��		2
13	����		2
14	����		4
......
ID���	XXXX	2	00 - 511
ֹͣԭ��	XX 	1	��״̬
��ѹ		2	�����ĵ�ѹ
����		2	��������
ʱ��		2
����		2
����		4
У��λ	XX	1	�������
����λ	0xAB	1

*/

/*
	�޲���ʱ�����
	��������
	���	����ָ��ṹ	��ֵ��HEX��	���ȣ��ֽڣ�	ע
	1	ǰ����	FCFF	2	ͨ����ʼ��־
	2	�����	01	1	�����ַ���
	3	���ݳ���	XXXX	2	������ֽ���
	4	ͨ������	0x06	1	ͨ��������
	5	������	0x06	1	һ���׶�
	6	������	0x00-0xff	1	�����ڼ�����ҵ
	7	ѭ��	0x00-0x0FF	1	�ڼ���ѭ��
	8	У��λ	XX	1	�������
	9	����λ	0xAB	1
*/
void CLowerCabs::CreateLowerCabs(CString lowerInfos)
{
	// 1 ����lowerInfos�ַ�����ȡcabId
	// 2 ����lowerInfos�ַ�����ȡ��س�ʼ���
	// 3 �����ַ����й̶��ĳ��ȳ�ʼ�����
	
	// ����Ч��λ�������Ϣ�ľ�������
	int lowerInfoLength = lowerInfos.GetLength();

	if (lowerInfoLength <= MIN_LOWERBATINFO_LENGTH)
		return;
	if (!((lowerInfos[0] == 'F') && lowerInfos[1] == 'C' && lowerInfos[2] == 'F' && lowerInfos[3] == 'F'))
		return;
	// У����λ����Ϣ
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

	// strIdx ��ʾ��ص�״̬�����ַ���������λ��

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
	// ���lowerInfos��Ϣ����,�����������Ϣ
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

// ����λ����Ϣ����У��
bool CLowerCabs::CheckLowerInfos(CString lowerInfos)
{
	return TRUE;
}
