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

	BYTE dataLen;	//	数据长度
	BYTE model;	//	预留字段
	BYTE machine;	//	机器类型: 主机/丛机

	void serialization(CByteArray &result);
};

