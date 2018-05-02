#include "stdafx.h"
#include "ObtainBeatMsg.h"


ObtainBeatMsg::ObtainBeatMsg()
{
}

ObtainBeatMsg::ObtainBeatMsg(CString cabIdStr, CString modelIdStr)
{
	this->cabIdStr = cabIdStr;
	this->modelIdStr = modelIdStr;

	this->dataLen = 0x05;
	this->writeCommand = 0x08;
	this->obligate1 = 0x00;
	this->obligate2 = 0x00;
	this->masterSlave = 0x00;
}


ObtainBeatMsg::~ObtainBeatMsg()
{
}

void ObtainBeatMsg::serialization(CByteArray &result)
{
	BYTE tmp;
	cstring2Byte(cabIdStr, tmp, cabinetNo);
	cstring2Byte(modelIdStr, tmp, modeId);

	result.SetSize(9);

	result.SetAt(0, preCode_high);
	result.SetAt(1, preCode_low);
	result.SetAt(2, cabinetNo);
	result.SetAt(3, dataLen);
	result.SetAt(4, writeCommand);
	result.SetAt(5, modeId);
	result.SetAt(6, masterSlave);


	result.SetAt(8, endCode);

	//计算校验位
	CheckCode = preCode_high ^ preCode_low;
	for (int i = 2; i < result.GetSize() - 1; ++i)
	{
		CheckCode = CheckCode ^ result.GetAt(i);
	}

	result.SetAt(7, CheckCode);

	std::ofstream   outfile;
	outfile.open("logs.txt", ios::out | ios::app);
	outfile << "GetBeatCode:" << StringUtils::BytesToStr(result) << endl;
	outfile.close();
}
