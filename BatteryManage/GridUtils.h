#pragma once
#include "GridCtrl_src/GridCtrl.h"

class CGridUtils
{
public:
	CGridUtils();
	~CGridUtils();
	static GV_ITEM CreateGridItem(int row, int col, UINT mask, DWORD format, CString txt);
};

