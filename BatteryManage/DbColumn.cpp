#include "stdafx.h"
#include "DbColumn.h"



CDbColumn::CDbColumn(string colName,string attrType,int attrLength,bool allowNull)
{
	this->colName = colName;
	this->attrType = attrType;
	this->attrLength = attrLength;
	this->allowNull = allowNull;
}

CDbColumn::CDbColumn()
{

}

CDbColumn::~CDbColumn()
{
}
