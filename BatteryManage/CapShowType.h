#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
	分容显示形式
*/
const int AUTO_PART_CAP_ID = 0;
const int PART_CAP_COND_ID = 1;
const int PART_SHOW_BATID = 2;
const int MAX_FLAG_LENGTH = 10;


const CString NULL_FLAG_STR = L"0";

#define WM_UPDATE_PART_BAT_MSG	WM_USER+0x01003		//	自定义HORZ滑动的message
#define WM_REFRESG_DATAOPENVIEW_MSG WM_USER+0x01004	//	自动义的刷新DataFileOpenView的事件
#define WM_LOOP_MENU_DATA_CHECK_MSG WM_USER+0x01005	//	SLOOPMenu对话框中的Data Check事件

class CapShowType
{
private:
	CapShowType();
	~CapShowType();
	static CapShowType *capShowType;
public:
	int GetPartCapCondChk();
	int GetPartShowBatidChk();
	int GetAutoPartCapChk();

	void SetPartCapCondChk(int check);
	void SetPartShowBatidChk(int check);
	void SetAutoPartCapChk(int check);

	void SavePartCapCond();

	void SavePartCapCond2();

	void SaveByPath(CString filePath);

	static CapShowType * GetInstance();
	void UpdateInstance(CString filePath);

	void CreateCapShowInfos();
	void SavePartCapCondToFile(CString filePath);
private:
	int partCapCondChk;
	int partShowBatidChk;
	int autoPartCapChk;

	CString capShowTypePath;

public:
	int minVal1;
	int minVal2;
	int minVal3;
	int minVal4;
	int minVal5;
	int minVal6;
	int minVal7;
	int minVal8;
	int minVal9;
	int minVal10;
	int minVal11;
	int minVal12;
	int minVal13;
	int minVal14;
	int minVal15;
	int minVal16;

	int maxVal1;
	int maxVal2;
	int maxVal3;
	int maxVal4;
	int maxVal5;
	int maxVal6;
	int maxVal7;
	int maxVal8;
	int maxVal9;
	int maxVal10;
	int maxVal11;
	int maxVal12;
	int maxVal13;
	int maxVal14;
	int maxVal15;
	int maxVal16;

	CString flagVal1;
	CString flagVal2;
	CString flagVal3;
	CString flagVal4;
	CString flagVal5;
	CString flagVal6;
	CString flagVal7;
	CString flagVal8;
	CString flagVal9;
	CString flagVal10;
	CString flagVal11;
	CString flagVal12;
	CString flagVal13;
	CString flagVal14;
	CString flagVal15;
	CString flagVal16;

	int colorVal1;
	int colorVal2;
	int colorVal3;
	int colorVal4;
	int colorVal5;
	int colorVal6;
	int colorVal7;
	int colorVal8;
	int colorVal9;
	int colorVal10;
	int colorVal11;
	int colorVal12;
	int colorVal13;
	int colorVal14;
	int colorVal15;
	int colorVal16;
	
	int validenum;

	vector<int> minVals;
	vector<int> maxVals;
	vector<CString> flagVals;
	vector<COLORREF> colorVals;


};

