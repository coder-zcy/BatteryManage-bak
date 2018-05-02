#include "stdafx.h"
#include "FileUtils.h"


CFileUtils::CFileUtils()
{
}


CFileUtils::~CFileUtils()
{
}

BOOL CFileUtils::FolderExists(CString s)
{
	DWORD attr;
	attr = GetFileAttributes(s);
	return (attr != (DWORD)(-1)) &&
		(attr & FILE_ATTRIBUTE_DIRECTORY);
}

BOOL CFileUtils::CreateMuliteDirectory(CString P)
{
	int len = P.GetLength();
	if (len < 2) return false;
	if ('\\' == P[len - 1])
	{
		P = P.Left(len - 1);
		len = P.GetLength();
	}
	if (len <= 0) return false;
	if (len <= 3)
	{
		if (FolderExists(P))return true;
		else return false;
	}
	if (FolderExists(P))return true;
	CString Parent;
	Parent = P.Left(P.ReverseFind('\\'));
	if (Parent.GetLength() <= 0)return false;
	BOOL Ret = CreateMuliteDirectory(Parent);
	if (Ret)
	{
		SECURITY_ATTRIBUTES sa;
		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.lpSecurityDescriptor = NULL;
		sa.bInheritHandle = 0;
		Ret = (CreateDirectory(P, &sa) == TRUE);
		return Ret;
	}
	else
		return FALSE;
}