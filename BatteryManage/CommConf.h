#pragma once
/*
��˵��:	ͨ��������, д�ɵ���ģʽ��
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

