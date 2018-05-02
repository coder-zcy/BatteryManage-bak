#pragma once
#include "LowerCabs.h"


extern CLowerCabs lowerCabs;
extern const CString BATSTATE_CSTR[];


#define SASC_CHARGE_CODE	1	//	������ѹ������
#define LAY_CODE			2	//	���ñ���
#define SA_DISCHARGE_CODE	3	//	�����ŵ����
#define SA_CHARGE_CODE		4	//	����������
#define LOOP_CODE			5	//	ѭ������
#define OBTAIN_BAT_CODE		6	//	��ȡ������ݱ���
#define OBTAIN_MODEL_CODE	7	//	��ȡ��λ����Ϣ����
#define HEART_BEAT_CODE		8	//	������
#define CAB_CON_CODE		10	//	��������

#define MIN_BAT_STATE			0	//	��С״̬
#define UNOVER_CODE				0	//  δ����
#define TIME_COME_CODE			1	//	ʱ�䵽
#define MAX_VOLT_COME_CODE	    2	//	���޵�ѹ��
#define END_CURRENT_COME_CODE	3	//	��ֹ������
#define DELTA_COME_CODE			4	//	-��V��
#define CURRENT_ERROR_CODE		5	//	�����쳣
#define VOLT_ERROR_CODE			6	//	��ѹ�쳣
#define CAPACITY_ERROE_CODE		7	//	�����쳣
#define OFF_VOLT_CODE			8	//	ƫ��ƽ����ѹ�쳣(�Ⱥ���)
#define HAND_REGIDIT_CODE		9	//	�ֶ��Ĵ棨�Ĵ���ɫ��
#define NONE_BAT_CODE			10	//	�޵�ػ��ؽӴ�����
#define BAD_BAT_CODE			11	//	�������
#define MIN_VOLT_COME_CODE		12	//	���޵�ѹ�����Ĵ���ɫ��
#define MAX_BAT_STATE			16	//	���״̬




class CLowerUtils
{
public:
	CLowerUtils();
	~CLowerUtils();
};

