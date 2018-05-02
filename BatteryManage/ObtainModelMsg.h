#pragma once
#include "StepMsg.h"
class ObtainModelMsg :
	public StepMsg
{
public:
	ObtainModelMsg(CString cabIdStr);
	ObtainModelMsg();
	~ObtainModelMsg();
public:
	CString cabIdStr; 

	BYTE dataLen;	//	���ݳ���
	BYTE obligate1;	//	Ԥ���ֶ�1
	BYTE obligate2; //	Ԥ���ֶ�2

	void serialization(CByteArray &result);
};

