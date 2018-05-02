#pragma once
#include "StepMsg.h"

class HeartBeatMsg : public StepMsg
{
public:
	HeartBeatMsg();
	HeartBeatMsg(CString cabIdStr);
	~HeartBeatMsg();

public:
	CString cabIdStr;

	BYTE dataLen;	//	���ݳ���
	BYTE model;	//	Ԥ���ֶ�
	BYTE machine;	//	��������: ����/�Ի�

	void serialization(CByteArray &result);
};

