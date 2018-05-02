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

	BYTE dataLen;		//	数据长度
	BYTE modeId;		//	型号
	BYTE obligate1;		//	预留字段
	BYTE obligate2;		//	预留字段
	BYTE masterSlave;	//	主从

public:
	void serialization(CByteArray &result);
};

