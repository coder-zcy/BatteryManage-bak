#pragma once
#include "StepMsg.h"

class CabConMsg : public StepMsg
{
public:
	CabConMsg(CString cabIdStr);
	CabConMsg();
	~CabConMsg();

public:
	CString cabIdStr;

	BYTE dataLen;	//	���ݳ���
	BYTE obligate;	//	Ԥ���ֶ�
	BYTE machine;	//	��������: ����/�Ի�

	void serialization(CByteArray &result);
};

