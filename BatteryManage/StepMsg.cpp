#include "stdafx.h"
#include "StepMsg.h"




void StepMsg::serialization(CByteArray &result)
{

}

int char2int(char para)
{
	if (para >= '0' && para <= '9')
		return (para - '0');
	else if (para >= 'a' && para <= 'f')
		return (para - 'a') + 10;
	else if (para >= 'A' && para <= 'F')
		return (para - 'A') + 10;

	return 0;
}

void cstring2Byte(CString para, BYTE &high, BYTE &low){
	//if (para.GetLength() > 4) MessageBox(_T("请先选择COM口"));
	//假定cstring的长度小于等于4位，则
	if (para.GetLength() == 0) return;
	int itmp = 0;
	itmp = _ttoi(para);

	//求16进制字符串
	CString result = _T("");
	result.Format(_T("%x"), itmp);
	//注意，这里假设result是少于4位的
	int idx = result.GetLength();
	switch (idx)
	{
	case 1:
		low = char2int(result[0]);
		high = 0x00;
		break;
	case 2:
		low = char2int(result[0]) * 16 + char2int(result[1]);
		high = 0x00;
		break;
	case 3:
		high = char2int(result[0]);
		low = char2int(result[1]) * 16 + char2int(result[2]);
		break;
	case 4:
		high = char2int(result[1]) + char2int(result[0]) * 16;
		low = char2int(result[3]) + char2int(result[2]) * 16;
		break;
	}
}

void cstring2Byte(CString para, BYTE &byte1, BYTE &byte2, BYTE &byte3, BYTE &byte4)
{
	//if (para.GetLength() > 4) MessageBox(_T("请先选择COM口"));
	//假定cstring的长度小于等于4位，则
	if (para.GetLength() == 0) return;
	int itmp = 0;
	itmp = _ttoi(para);

	//求16进制字符串
	CString result = _T("");
	result.Format(_T("%x"), itmp);
	//注意，这里假设result是少于4位的
	int idx = result.GetLength();
	switch (idx)
	{
	case 1:
		byte1 = 0x00;
		byte2 = 0x00;
		byte3 = 0x00;
		byte4 = char2int(result[0]);
		break;
	case 2:
		byte1 = 0x00;
		byte2 = 0x00;
		byte3 = 0x00;
		byte4 = char2int(result[1]) + char2int(result[0]) * 16;
		break;
	case 3:
		byte1 = 0x00;
		byte2 = 0x00;
		byte3 = char2int(result[0]);
		byte4 = char2int(result[2]) + char2int(result[1]) * 16;
		break;
	case 4:
		byte1 = 0x00;
		byte2 = 0x00;
		byte3 = char2int(result[1]) + char2int(result[0]) * 16;
		byte4 = char2int(result[3]) + char2int(result[2]) * 16;
		break;
	case 5:
		byte1 = 0x00;
		byte2 = char2int(result[0]);
		byte3 = char2int(result[2]) + char2int(result[1]) * 16;
		byte4 = char2int(result[4]) + char2int(result[3]) * 16;
		break;
	case 6:
		byte1 = 0x00;
		byte2 = char2int(result[1]) + char2int(result[0]) * 16;
		byte3 = char2int(result[3]) + char2int(result[2]) * 16;
		byte4 = char2int(result[5]) + char2int(result[4]) * 16;
		break;
	case 7:
		byte1 = char2int(result[0]);
		byte2 = char2int(result[2]) + char2int(result[1]) * 16;
		byte3 = char2int(result[4]) + char2int(result[3]) * 16;
		byte4 = char2int(result[6]) + char2int(result[5]) * 16;
		break;
	case 8:
		byte1 = char2int(result[1]) + char2int(result[0]) * 16;
		byte2 = char2int(result[3]) + char2int(result[2]) * 16;
		byte3 = char2int(result[5]) + char2int(result[4]) * 16;
		byte4 = char2int(result[7]) + char2int(result[6]) * 16;
		break;
	}
}


StepMsg::StepMsg()
{
}


StepMsg::~StepMsg()
{
}
