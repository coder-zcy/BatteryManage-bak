#include "stdafx.h"
#include "ObtainBatMsg.h"



ObtainBatMsg::ObtainBatMsg()
{
}

ObtainBatMsg::ObtainBatMsg(CString cabIdStr, CString groupIdStr)
{
	this->cabIdStr = cabIdStr;
	this->groupIdStr = groupIdStr;

	this->dataLen = 0x05;
	this->writeCommand = 0x06;
	this->obligate = 0x00;

}


ObtainBatMsg::~ObtainBatMsg()
{
}

void ObtainBatMsg::serialization(CByteArray &result)
{
	BYTE tmp;
	cstring2Byte(cabIdStr, tmp, cabinetNo);
	cstring2Byte(groupIdStr, tmp, groupId);

	result.SetSize(9);

	result.SetAt(0, preCode_high);
	result.SetAt(1, preCode_low);
	result.SetAt(2, cabinetNo);
	result.SetAt(3, dataLen);
	result.SetAt(4, writeCommand);
	result.SetAt(5, groupId);
	result.SetAt(6, obligate);
	result.SetAt(8, endCode);

	//计算校验位
	CheckCode = preCode_high ^ preCode_low;
	for (int i = 2; i < result.GetSize() - 1; ++i)
	{
		CheckCode = CheckCode ^ result.GetAt(i);
	}

	result.SetAt(7, CheckCode);

	//FE FF 01 05 06 01 00 02 AB
	std::ofstream   outfile;
	outfile.open("logs.txt", ios::out | ios::app);
	outfile << "GetBatInfoCode:" << StringUtils::BytesToStr(result) << endl;
	outfile.close();
}
