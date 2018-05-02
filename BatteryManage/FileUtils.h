#pragma once
#include <iostream>
#include <string>

using namespace std;
class CFileUtils
{
public:
	CFileUtils();
	~CFileUtils();
public:
	static BOOL CFileUtils::FolderExists(CString s);
	static BOOL CFileUtils::CreateMuliteDirectory(CString P);
};

