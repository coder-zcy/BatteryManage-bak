#include "stdafx.h"
#include "CapShowType.h"
#include "BatteryUtils.h"

CapShowType* CapShowType::capShowType = NULL;

CapShowType::CapShowType()
{
	capShowTypePath = CBatteryUtils::GetConfigPath(_T("\\config\\init\\capstype.ini"));

	CreateCapShowInfos();

}


CapShowType::~CapShowType()
{
}

int CapShowType::GetPartCapCondChk()
{
	return partCapCondChk;
}

int CapShowType::GetPartShowBatidChk()
{
	return partShowBatidChk;
}

int CapShowType::GetAutoPartCapChk()
{
	return autoPartCapChk;
}

void CapShowType::SetPartCapCondChk(int check)
{
	wchar_t str[10];

	_itow_s(partCapCondChk, str, 10, 10);
	partCapCondChk = check;
	WritePrivateProfileString(_T("showtype"), _T("partCapCond"), str, capShowTypePath);
}

void CapShowType::SetPartShowBatidChk(int check)
{
	wchar_t str[10];

	partShowBatidChk = check;
	_itow_s(partShowBatidChk, str, 10, 10);
	WritePrivateProfileString(_T("showtype"), _T("partShowBatid"), str, capShowTypePath);
}

void CapShowType::SetAutoPartCapChk(int check)
{
	wchar_t str[10];

	autoPartCapChk = check;
	_itow_s(autoPartCapChk, str, 10, 10);
	WritePrivateProfileString(_T("showtype"), _T("autoPartCap"), str, capShowTypePath);
}

void CapShowType::SavePartCapCond()
{
	SaveByPath(capShowTypePath);

}

void CapShowType::SavePartCapCond2()
{
	SaveByPath(capShowTypePath);

}

void CapShowType::SaveByPath(CString filePath)
{
	wchar_t str[MAX_FLAG_LENGTH];

	_itow_s(autoPartCapChk, str, MAX_FLAG_LENGTH, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("showtype"), _T("autoPartCap"), str, filePath);
	_itow_s(partShowBatidChk, str, MAX_FLAG_LENGTH, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("showtype"), _T("partShowBatid"), str, filePath);

	_itow_s(minVal1, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("min"), _T("minVal1"), str, filePath);
	_itow_s(minVal2, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("min"), _T("minVal2"), str, filePath);
	_itow_s(minVal3, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("min"), _T("minVal3"), str, filePath);
	_itow_s(minVal4, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("min"), _T("minVal4"), str, filePath);
	_itow_s(minVal5, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("min"), _T("minVal5"), str, filePath);
	_itow_s(minVal6, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("min"), _T("minVal6"), str, filePath);
	_itow_s(minVal7, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("min"), _T("minVal7"), str, filePath);
	_itow_s(minVal8, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("min"), _T("minVal8"), str, filePath);
	_itow_s(minVal9, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("min"), _T("minVal9"), str, filePath);
	_itow_s(minVal10, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("min"), _T("minVal10"), str, filePath);
	_itow_s(minVal11, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("min"), _T("minVal11"), str, filePath);
	_itow_s(minVal12, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("min"), _T("minVal12"), str, filePath);
	_itow_s(minVal13, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("min"), _T("minVal13"), str, filePath);
	_itow_s(minVal14, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("min"), _T("minVal14"), str, filePath);
	_itow_s(minVal15, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("min"), _T("minVal15"), str, filePath);
	_itow_s(minVal16, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("min"), _T("minVal16"), str, filePath);

	_itow_s(maxVal1, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("max"), _T("maxVal1"), str, filePath);
	_itow_s(maxVal2, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("max"), _T("maxVal2"), str, filePath);
	_itow_s(maxVal3, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("max"), _T("maxVal3"), str, filePath);
	_itow_s(maxVal4, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("max"), _T("maxVal4"), str, filePath);
	_itow_s(maxVal5, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("max"), _T("maxVal5"), str, filePath);
	_itow_s(maxVal6, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("max"), _T("maxVal6"), str, filePath);
	_itow_s(maxVal7, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("max"), _T("maxVal7"), str, filePath);
	_itow_s(maxVal8, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("max"), _T("maxVal8"), str, filePath);
	_itow_s(maxVal9, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("max"), _T("maxVal9"), str, filePath);
	_itow_s(maxVal10, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("max"), _T("maxVal10"), str, filePath);
	_itow_s(maxVal11, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("max"), _T("maxVal11"), str, filePath);
	_itow_s(maxVal12, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("max"), _T("maxVal12"), str, filePath);
	_itow_s(maxVal13, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("max"), _T("maxVal13"), str, filePath);
	_itow_s(maxVal14, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("max"), _T("maxVal14"), str, filePath);
	_itow_s(maxVal15, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("max"), _T("maxVal15"), str, filePath);
	_itow_s(maxVal16, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("max"), _T("maxVal16"), str, filePath);

	_itow_s(colorVal1, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("color"), _T("colorVal1"), str, filePath);
	_itow_s(colorVal2, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("color"), _T("colorVal2"), str, filePath);
	_itow_s(colorVal3, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("color"), _T("colorVal3"), str, filePath);
	_itow_s(colorVal4, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("color"), _T("colorVal4"), str, filePath);
	_itow_s(colorVal5, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("color"), _T("colorVal5"), str, filePath);
	_itow_s(colorVal6, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("color"), _T("colorVal6"), str, filePath);
	_itow_s(colorVal7, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("color"), _T("colorVal7"), str, filePath);
	_itow_s(colorVal8, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("color"), _T("colorVal8"), str, filePath);
	_itow_s(colorVal9, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("color"), _T("colorVal9"), str, filePath);
	_itow_s(colorVal10, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("color"), _T("colorVal10"), str, filePath);
	_itow_s(colorVal11, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("color"), _T("colorVal11"), str, filePath);
	_itow_s(colorVal12, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("color"), _T("colorVal12"), str, filePath);
	_itow_s(colorVal13, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("color"), _T("colorVal13"), str, filePath);
	_itow_s(colorVal14, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("color"), _T("colorVal14"), str, filePath);
	_itow_s(colorVal15, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("color"), _T("colorVal15"), str, filePath);
	_itow_s(colorVal16, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("color"), _T("colorVal16"), str, filePath);


	WritePrivateProfileString(_T("flag"), _T("flagVal1"), flagVal1, filePath);
	WritePrivateProfileString(_T("flag"), _T("flagVal2"), flagVal2, filePath);
	WritePrivateProfileString(_T("flag"), _T("flagVal3"), flagVal3, filePath);
	WritePrivateProfileString(_T("flag"), _T("flagVal4"), flagVal4, filePath);
	WritePrivateProfileString(_T("flag"), _T("flagVal5"), flagVal5, filePath);
	WritePrivateProfileString(_T("flag"), _T("flagVal6"), flagVal6, filePath);
	WritePrivateProfileString(_T("flag"), _T("flagVal7"), flagVal7, filePath);
	WritePrivateProfileString(_T("flag"), _T("flagVal8"), flagVal8, filePath);
	WritePrivateProfileString(_T("flag"), _T("flagVal9"), flagVal9, filePath);
	WritePrivateProfileString(_T("flag"), _T("flagVal10"), flagVal10, filePath);
	WritePrivateProfileString(_T("flag"), _T("flagVal11"), flagVal11, filePath);
	WritePrivateProfileString(_T("flag"), _T("flagVal12"), flagVal12, filePath);
	WritePrivateProfileString(_T("flag"), _T("flagVal13"), flagVal13, filePath);
	WritePrivateProfileString(_T("flag"), _T("flagVal14"), flagVal14, filePath);
	WritePrivateProfileString(_T("flag"), _T("flagVal15"), flagVal15, filePath);
	WritePrivateProfileString(_T("flag"), _T("flagVal16"), flagVal16, filePath);

	_itow_s(capShowType->validenum, str, MAX_FLAG_LENGTH);
	WritePrivateProfileString(_T("validenum"), _T("validenum"), str, filePath);
}

CapShowType * CapShowType::GetInstance()
{
	if (capShowType == NULL)
	{
		capShowType = new CapShowType();
	}

	return capShowType;
}

void CapShowType::UpdateInstance(CString filePath)
{
	capShowTypePath = filePath;

	CreateCapShowInfos();

}

void CapShowType::CreateCapShowInfos()
{
	wchar_t str[MAX_FLAG_LENGTH];

	GetPrivateProfileString(_T("showtype"), _T("partCapCond"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	partCapCondChk = _ttoi(str);

	GetPrivateProfileString(_T("showtype"), _T("partShowBatid"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	partShowBatidChk = _ttoi(str);

	GetPrivateProfileString(_T("showtype"), _T("autoPartCap"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	autoPartCapChk = _ttoi(str);

	GetPrivateProfileString(_T("min"), _T("minVal1"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	minVal1 = _ttoi(str);
	GetPrivateProfileString(_T("min"), _T("minVal2"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	minVal2 = _ttoi(str);
	GetPrivateProfileString(_T("min"), _T("minVal3"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	minVal3 = _ttoi(str);
	GetPrivateProfileString(_T("min"), _T("minVal4"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	minVal4 = _ttoi(str);
	GetPrivateProfileString(_T("min"), _T("minVal5"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	minVal5 = _ttoi(str);
	GetPrivateProfileString(_T("min"), _T("minVal6"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	minVal6 = _ttoi(str);
	GetPrivateProfileString(_T("min"), _T("minVal7"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	minVal7 = _ttoi(str);
	GetPrivateProfileString(_T("min"), _T("minVal8"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	minVal8 = _ttoi(str);
	GetPrivateProfileString(_T("min"), _T("minVal9"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	minVal9 = _ttoi(str);
	GetPrivateProfileString(_T("min"), _T("minVal10"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	minVal10 = _ttoi(str);
	GetPrivateProfileString(_T("min"), _T("minVal11"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	minVal11 = _ttoi(str);
	GetPrivateProfileString(_T("min"), _T("minVal12"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	minVal12 = _ttoi(str);
	GetPrivateProfileString(_T("min"), _T("minVal13"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	minVal13 = _ttoi(str);
	GetPrivateProfileString(_T("min"), _T("minVal14"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	minVal14 = _ttoi(str);
	GetPrivateProfileString(_T("min"), _T("minVal15"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	minVal15 = _ttoi(str);
	GetPrivateProfileString(_T("min"), _T("minVal16"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	minVal16 = _ttoi(str);

	GetPrivateProfileString(_T("max"), _T("maxVal1"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	maxVal1 = _ttoi(str);
	GetPrivateProfileString(_T("max"), _T("maxVal2"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	maxVal2 = _ttoi(str);
	GetPrivateProfileString(_T("max"), _T("maxVal3"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	maxVal3 = _ttoi(str);
	GetPrivateProfileString(_T("max"), _T("maxVal4"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	maxVal4 = _ttoi(str);
	GetPrivateProfileString(_T("max"), _T("maxVal5"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	maxVal5 = _ttoi(str);
	GetPrivateProfileString(_T("max"), _T("maxVal6"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	maxVal6 = _ttoi(str);
	GetPrivateProfileString(_T("max"), _T("maxVal7"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	maxVal7 = _ttoi(str);
	GetPrivateProfileString(_T("max"), _T("maxVal8"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	maxVal8 = _ttoi(str);
	GetPrivateProfileString(_T("max"), _T("maxVal9"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	maxVal9 = _ttoi(str);
	GetPrivateProfileString(_T("max"), _T("maxVal10"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	maxVal10 = _ttoi(str);
	GetPrivateProfileString(_T("max"), _T("maxVal11"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	maxVal11 = _ttoi(str);
	GetPrivateProfileString(_T("max"), _T("maxVal12"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	maxVal12 = _ttoi(str);
	GetPrivateProfileString(_T("max"), _T("maxVal13"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	maxVal13 = _ttoi(str);
	GetPrivateProfileString(_T("max"), _T("maxVal14"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	maxVal14 = _ttoi(str);
	GetPrivateProfileString(_T("max"), _T("maxVal15"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	maxVal15 = _ttoi(str);
	GetPrivateProfileString(_T("max"), _T("maxVal16"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	maxVal16 = _ttoi(str);

	GetPrivateProfileString(_T("flag"), _T("flagVal1"), L"A", str, MAX_FLAG_LENGTH, capShowTypePath);
	flagVal1 = str;
	GetPrivateProfileString(_T("flag"), _T("flagVal2"), L"B", str, MAX_FLAG_LENGTH, capShowTypePath);
	flagVal2 = str;
	GetPrivateProfileString(_T("flag"), _T("flagVal3"), L"C", str, MAX_FLAG_LENGTH, capShowTypePath);
	flagVal3 = str;
	GetPrivateProfileString(_T("flag"), _T("flagVal4"), L"D", str, MAX_FLAG_LENGTH, capShowTypePath);
	flagVal4 = str;
	GetPrivateProfileString(_T("flag"), _T("flagVal5"), L"E", str, MAX_FLAG_LENGTH, capShowTypePath);
	flagVal5 = str;
	GetPrivateProfileString(_T("flag"), _T("flagVal6"), L"F", str, MAX_FLAG_LENGTH, capShowTypePath);
	flagVal6 = str;
	GetPrivateProfileString(_T("flag"), _T("flagVal7"), L"G", str, MAX_FLAG_LENGTH, capShowTypePath);
	flagVal7 = str;
	GetPrivateProfileString(_T("flag"), _T("flagVal8"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	flagVal8 = str;
	GetPrivateProfileString(_T("flag"), _T("flagVal9"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	flagVal9 = str;
	GetPrivateProfileString(_T("flag"), _T("flagVal10"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	flagVal10 = str;
	GetPrivateProfileString(_T("flag"), _T("flagVal11"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	flagVal11 = str;
	GetPrivateProfileString(_T("flag"), _T("flagVal12"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	flagVal12 = str;
	GetPrivateProfileString(_T("flag"), _T("flagVal13"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	flagVal13 = str;
	GetPrivateProfileString(_T("flag"), _T("flagVal14"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	flagVal14 = str;
	GetPrivateProfileString(_T("flag"), _T("flagVal15"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	flagVal15 = str;
	GetPrivateProfileString(_T("flag"), _T("flagVal16"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	flagVal16 = str;


	GetPrivateProfileString(_T("color"), _T("colorVal1"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	colorVal1 = _ttoi(str);
	GetPrivateProfileString(_T("color"), _T("colorVal2"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	colorVal2 = _ttoi(str);
	GetPrivateProfileString(_T("color"), _T("colorVal3"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	colorVal3 = _ttoi(str);
	GetPrivateProfileString(_T("color"), _T("colorVal4"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	colorVal4 = _ttoi(str);
	GetPrivateProfileString(_T("color"), _T("colorVal5"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	colorVal5 = _ttoi(str);
	GetPrivateProfileString(_T("color"), _T("colorVal6"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	colorVal6 = _ttoi(str);
	GetPrivateProfileString(_T("color"), _T("colorVal7"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	colorVal7 = _ttoi(str);
	GetPrivateProfileString(_T("color"), _T("colorVal8"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	colorVal8 = _ttoi(str);
	GetPrivateProfileString(_T("color"), _T("colorVal9"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	colorVal9 = _ttoi(str);
	GetPrivateProfileString(_T("color"), _T("colorVal10"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	colorVal10 = _ttoi(str);
	GetPrivateProfileString(_T("color"), _T("colorVal11"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	colorVal11 = _ttoi(str);
	GetPrivateProfileString(_T("color"), _T("colorVal12"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	colorVal12 = _ttoi(str);
	GetPrivateProfileString(_T("color"), _T("colorVal13"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	colorVal13 = _ttoi(str);
	GetPrivateProfileString(_T("color"), _T("colorVal14"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	colorVal14 = _ttoi(str);
	GetPrivateProfileString(_T("color"), _T("colorVal15"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	colorVal15 = _ttoi(str);
	GetPrivateProfileString(_T("color"), _T("colorVal16"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	colorVal16 = _ttoi(str);

	GetPrivateProfileString(_T("validenum"), _T("validenum"), L"", str, MAX_FLAG_LENGTH, capShowTypePath);
	validenum = _ttoi(str);

	minVals.clear();
	maxVals.clear();
	flagVals.clear();
	colorVals.clear();

	minVals.push_back(minVal1);
	minVals.push_back(minVal2);
	minVals.push_back(minVal3);
	minVals.push_back(minVal4);
	minVals.push_back(minVal5);
	minVals.push_back(minVal6);
	minVals.push_back(minVal7);
	minVals.push_back(minVal8);
	minVals.push_back(minVal9);
	minVals.push_back(minVal10);
	minVals.push_back(minVal11);
	minVals.push_back(minVal12);
	minVals.push_back(minVal13);
	minVals.push_back(minVal14);
	minVals.push_back(minVal15);
	minVals.push_back(minVal16);

	maxVals.push_back(maxVal1);
	maxVals.push_back(maxVal2);
	maxVals.push_back(maxVal3);
	maxVals.push_back(maxVal4);
	maxVals.push_back(maxVal5);
	maxVals.push_back(maxVal6);
	maxVals.push_back(maxVal7);
	maxVals.push_back(maxVal8);
	maxVals.push_back(maxVal9);
	maxVals.push_back(maxVal10);
	maxVals.push_back(maxVal11);
	maxVals.push_back(maxVal12);
	maxVals.push_back(maxVal13);
	maxVals.push_back(maxVal14);
	maxVals.push_back(maxVal15);
	maxVals.push_back(maxVal16);

	flagVals.push_back(flagVal1);
	flagVals.push_back(flagVal2);
	flagVals.push_back(flagVal3);
	flagVals.push_back(flagVal4);
	flagVals.push_back(flagVal5);
	flagVals.push_back(flagVal6);
	flagVals.push_back(flagVal7);
	flagVals.push_back(flagVal8);
	flagVals.push_back(flagVal9);
	flagVals.push_back(flagVal10);
	flagVals.push_back(flagVal11);
	flagVals.push_back(flagVal12);
	flagVals.push_back(flagVal13);
	flagVals.push_back(flagVal14);
	flagVals.push_back(flagVal15);
	flagVals.push_back(flagVal16);


	colorVals.push_back(RGB(colorVal1 / 1000000, (colorVal1 / 1000) % 1000, colorVal1 % 1000));
	colorVals.push_back(RGB(colorVal2 / 1000000, (colorVal2 / 1000) % 1000, colorVal2 % 1000));
	colorVals.push_back(RGB(colorVal3 / 1000000, (colorVal3 / 1000) % 1000, colorVal3 % 1000));
	colorVals.push_back(RGB(colorVal4 / 1000000, (colorVal4 / 1000) % 1000, colorVal4 % 1000));
	colorVals.push_back(RGB(colorVal5 / 1000000, (colorVal5 / 1000) % 1000, colorVal5 % 1000));
	colorVals.push_back(RGB(colorVal6 / 1000000, (colorVal6 / 1000) % 1000, colorVal6 % 1000));
	colorVals.push_back(RGB(colorVal7 / 1000000, (colorVal7 / 1000) % 1000, colorVal7 % 1000));
	colorVals.push_back(RGB(colorVal8 / 1000000, (colorVal8 / 1000) % 1000, colorVal8 % 1000));
	colorVals.push_back(RGB(colorVal9 / 1000000, (colorVal9 / 1000) % 1000, colorVal9 % 1000));
	colorVals.push_back(RGB(colorVal10 / 1000000, (colorVal10 / 1000) % 1000, colorVal10 % 1000));
	colorVals.push_back(RGB(colorVal11 / 1000000, (colorVal11 / 1000) % 1000, colorVal11 % 1000));
	colorVals.push_back(RGB(colorVal12 / 1000000, (colorVal12 / 1000) % 1000, colorVal12 % 1000));
	colorVals.push_back(RGB(colorVal13 / 1000000, (colorVal13 / 1000) % 1000, colorVal13 % 1000));
	colorVals.push_back(RGB(colorVal14 / 1000000, (colorVal14 / 1000) % 1000, colorVal14 % 1000));
	colorVals.push_back(RGB(colorVal15 / 1000000, (colorVal15 / 1000) % 1000, colorVal15 % 1000));
	colorVals.push_back(RGB(colorVal16 / 1000000, (colorVal16 / 1000) % 1000, colorVal16 % 1000));
	

}

void CapShowType::SavePartCapCondToFile(CString filePath)
{
	SaveByPath(filePath);
}
