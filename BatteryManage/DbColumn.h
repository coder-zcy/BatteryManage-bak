#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define NUM_TYPE "id"
#define INT_TYPE "int"
#define STR_TYPE "str"
#define DATETIME_TYPE "datetime"
#define DATE_TYPE "date"
#define TIME_TYPE "time"
#define DOUBLE_TYPE "double"

class CDbColumn
{
public:
	CDbColumn();
	CDbColumn(string colName,string attrType,int attrLength,bool allowNull);
	~CDbColumn();

public:
	string colName;
	string attrType;
	int attrLength;
	bool allowNull;
};

