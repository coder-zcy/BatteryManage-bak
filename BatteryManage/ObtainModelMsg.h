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

	BYTE dataLen;	//	Êý¾Ý³¤¶È
	BYTE obligate1;	//	Ô¤Áô×Ö¶Î1
	BYTE obligate2; //	Ô¤Áô×Ö¶Î2

	void serialization(CByteArray &result);
};

