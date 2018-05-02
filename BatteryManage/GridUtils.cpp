#include "stdafx.h"
#include "GridUtils.h"


CGridUtils::CGridUtils()
{
}


CGridUtils::~CGridUtils()
{
}

GV_ITEM CGridUtils::CreateGridItem(int row, int col, UINT mask, DWORD format, CString txt)
{
	GV_ITEM item;
	item.row = row;
	item.col = col;
	item.mask = mask;
	item.nFormat = format;
	item.strText = txt;
	//item.mask = GVIF_TEXT | GVIF_FORMAT;
	//item.nFormat = DT_CENTER | DT_WORDBREAK;

	return item;
}
