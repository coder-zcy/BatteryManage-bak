// TestEqual.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <string>
using namespace std;

class A
{
public:
	int id;
	int batId;
	int cabId;
	string str1;
	string str2;
	string str3;
	string str4;
	string str5;
	string str6;
	string str7;
	string str8;
	string str9;

	A& operator=(const A& b)
	{
		this->id = id;
		this->batId = batId;
		this->cabId = cabId;
		this->str1 = str1;
		this->str2 = str2;
		this->str3 = str3;
		this->str4 = str4;
		this->str5 = str5;
		this->str6 = str6;
		this->str7 = str7;
		this->str8 = str8;
		this->str9 = str9;

		return *this;
	}
protected:
private:
};
int _tmain(int argc, _TCHAR* argv[])
{
	int count = 10000;
	int idx;
	A a;
	for (idx = 0; idx < count; ++idx)
	{
		A b;
		a = b;
	}
	cout << "结束" <<endl;
	return 0;
}

