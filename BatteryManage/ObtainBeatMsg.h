#pragma once
#include "StepMsg.h"

class ObtainBeatMsg : public StepMsg
{
public:
	ObtainBeatMsg();
	ObtainBeatMsg(CString cabIdStr, CString modelIdStr);
	~ObtainBeatMsg();

public:
	CString cabIdStr;
	CString modelIdStr;

	BYTE dataLen;		//	���ݳ���
	BYTE modeId;		//	�ͺ�
	BYTE obligate1;		//	Ԥ���ֶ�
	BYTE obligate2;		//	Ԥ���ֶ�
	BYTE masterSlave;	//	����

public:
	void serialization(CByteArray &result);
};

