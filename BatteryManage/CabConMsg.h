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

	BYTE dataLen;	//	数据长度
	BYTE obligate;	//	预留字段
	BYTE machine;	//	机器类型: 主机/丛机

	void serialization(CByteArray &result);
};

