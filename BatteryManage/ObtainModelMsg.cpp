#include "stdafx.h"
#include "ObtainModelMsg.h"



ObtainModelMsg::ObtainModelMsg()
{
}

ObtainModelMsg::ObtainModelMsg(CString cabIdStr)
{
	this->cabIdStr = cabIdStr;
	this->dataLen = 0x05;
	this->writeCommand = 0x07;
	this->obligate1 = 0x00;
	this->obligate2 = 0x00;
}


ObtainModelMsg::~ObtainModelMsg()
{
}

void ObtainModelMsg::serialization(CByteArray &result)
{

	BYTE tmp;
	cstring2Byte(cabIdStr, tmp, cabinetNo);
	result.SetSize(9);

	result.SetAt(0, preCode_high);
	result.SetAt(1, preCode_low);
	result.SetAt(2, cabinetNo);
	result.SetAt(3, dataLen);
	result.SetAt(4, writeCommand);
	result.SetAt(5, obligate1);
	result.SetAt(6, obligate2);
	result.SetAt(8, endCode);

	//计算校验位
	CheckCode = preCode_high ^ preCode_low;
	for (int i = 2; i < result.GetSize() - 1; ++i)
	{
		CheckCode = CheckCode ^ result.GetAt(i);
	}

	result.SetAt(7, CheckCode);
}
