#include "stdafx.h"
#include "HeartBeatMsg.h"


HeartBeatMsg::HeartBeatMsg()
{
}

HeartBeatMsg::HeartBeatMsg(CString cabIdStr)
{
	this->cabIdStr = cabIdStr;
	this->dataLen = 0x05;
	this->writeCommand = 0x08;
	this->model = 0x01;
	this->machine = 0x02;
}


HeartBeatMsg::~HeartBeatMsg()
{
}

void HeartBeatMsg::serialization(CByteArray &result)
{
	BYTE tmp;
	cstring2Byte(cabIdStr, tmp, cabinetNo);
	result.SetSize(9);

	result.SetAt(0, preCode_high);
	result.SetAt(1, preCode_low);
	result.SetAt(2, cabinetNo);
	result.SetAt(3, dataLen);
	result.SetAt(4, writeCommand);
	result.SetAt(5, model);
	result.SetAt(6, machine);
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
