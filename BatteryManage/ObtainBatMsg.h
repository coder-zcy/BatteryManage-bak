#pragma once
#include "StepMsg.h"

class ObtainBatMsg : public StepMsg
{
public:
	ObtainBatMsg();
	ObtainBatMsg(CString cabIdStr, CString groupIdStr);
	~ObtainBatMsg();
public:
	CString cabIdStr;
	CString groupIdStr;

	BYTE dataLen;	//	���ݳ���
	BYTE groupId;	//	�����
	BYTE obligate;	//	Ԥ���ֶ�

	void serialization(CByteArray &result);
};

