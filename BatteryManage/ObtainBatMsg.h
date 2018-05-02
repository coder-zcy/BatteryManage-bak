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

	BYTE dataLen;	//	Êý¾Ý³¤¶È
	BYTE groupId;	//	¿éÐòºÅ
	BYTE obligate;	//	Ô¤Áô×Ö¶Î

	void serialization(CByteArray &result);
};

