
// GridControl0010.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGridControl0010App: 
// �йش����ʵ�֣������ GridControl0010.cpp
//

class CGridControl0010App : public CWinApp
{
public:
	CGridControl0010App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGridControl0010App theApp;