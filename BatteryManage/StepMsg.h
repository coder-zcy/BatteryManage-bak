#pragma once
#include <Windows.h>
#include <afxcoll.h>

#include "StringUtils.h"
#include "CabinetInfo.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*ö�ٷ���ָ��
������ѹ��� voltage_current_charge
����         put_aside
�����ŵ�     current_discharge
�������     current_charge
ѭ��         loop
*/
enum sendCommand_type{
	voltage_current_charge = 1,
	put_aside = 2,
	current_discharge = 3,
	current_charge = 4,
	loop = 5
};

void cstring2Byte(CString para, BYTE &high, BYTE &low);
void cstring2Byte(CString para, BYTE &byte1, BYTE &byte2, BYTE &byte3, BYTE &byte4);

int char2int(char para);



// ����ID
const int STATE_PARAID = 0;
const int TIME_PARAID = 0;
const int CURRENT_PARAID = 1;
const int START_STEP_PARAID = 1;
const int MAX_VOLT_PARAID = 2;
const int MIN_VOLT_PARAID = 3;
const int END_STEP_PARAID = 3;
const int DELTA_VOLT_PARAID = 4;
const int END_CURRENT_PARAID = 5;
const int LOOP_NUM_PARAID = 5;
const int END_CAPACITY_PARAID = 6;

const int STEP_PARAID2 = 1;
const int STATE_PARAID2 = 2;
const int TIME_PARAID2 = 2;
const int CURRENT_PARAID2 = 3;
const int START_STEP_PARAID2 = 3;
const int MAX_VOLT_PARAID2 = 4;
const int MIN_VOLT_PARAID2 = 5;
const int END_STEP_PARAID2 = 5;
const int DELTA_VOLT_PARAID2 = 6;
const int END_CURRENT_PARAID2 = 7;
const int LOOP_NUM_PARAID2 = 7;
const int END_CAPACITY_PARAID2 = 8;

class StepMsg
{
public:
	StepMsg();
	~StepMsg();

	virtual void serialization(CByteArray &result);
public:
	BYTE preCode_high = 0xFE; 
	BYTE preCode_low = 0xFF;
	BYTE cabinetNo;	
	BYTE writeCommand = 0x00; //д����ָ��
	BYTE step;
	BYTE CheckCode;
	BYTE endCode = 0xAB;

};

