#pragma once

#include "Battery.h"
#include <iostream>
#include <vector>

using namespace std;



class CabBattery
{
public:
	CabBattery(int cabId, int workId, int stepId, int cycleId);// ����cabId ��ȡCabinetInfo, Ȼ���CabinetInfo�е�batterys���г�ʼ��
	CabBattery();	
	~CabBattery();
public:
	int cabId;
	int cabState;
	int stepId;			//	�������
	int cycleId;		//	ѭ�����
	int workId;			//	������

	BOOL wirteToDb;
	vector<CBattery> batterys;
};

