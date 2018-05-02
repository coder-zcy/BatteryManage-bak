#pragma once

#define INT_LENGTH 10

class CTimeUtils
{
public:
	CTimeUtils();
	~CTimeUtils();
public:
	static CString CreateTimePath();

	static CString GetCurrentTimeCstr();
};

