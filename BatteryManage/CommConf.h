#pragma once
/*
类说明:	通信配置类, 写成单例模式咯
*/

class CommConf
{
private:
	CommConf();

private:
	static CommConf* commConf;

public:
	static CommConf * GetInstance();
public:
	CString commPath;
	CString commPortStr;
	CString commBaudStr;
	CString commTimeStr;
	int chkVal;
	int needLoginVal;
	int forbdModifyVal;
	int onlineReadVal;
	int exitReadVal;
	int forbdOtherVal;

	int commPortVal;
	int commBaudVal;
	int commTimeVal;


public:
	BOOL SaveCommConf();
	BOOL UpdateCommConf();
	
};

