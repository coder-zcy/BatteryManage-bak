#include "stdafx.h"
#include "StringUtils.h"


//  初始化映射数组
const int ascmapping[256] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0,
0, 10, 11, 12, 13, 14, 15, 0
};

//	4 字节整数转换时得帮助数组
const LONGLONG oxmapping[8] = { 1, 16, 16 * 16, 16 * 16 * 16, 16 * 16 * 16 * 16,
16 * 16 * 16 * 16 * 16, 16 * 16 * 16 * 16 * 16 * 16,
16 * 16 * 16 * 16 * 16 * 16 * 16,
};

const string xintmapping[16] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
"A", "B", "C", "D", "E", "F"
};


StringUtils::StringUtils()
{
}


StringUtils::~StringUtils()
{
}

vector<string> StringUtils::SplitByStr(const string &s, const string &seperator){
	vector<string> result;
	typedef string::size_type string_size;
	string_size i = 0;

	while (i != s.size()){
		//找到字符串中首个不等于分隔符的字母；
		int flag = 0;
		while (i != s.size() && flag == 0){
			flag = 1;
			for (string_size x = 0; x < seperator.size(); ++x)
			if (s[i] == seperator[x]){
				++i;
				flag = 0;
				break;
			}
		}

		//找到又一个分隔符，将两个分隔符之间的字符串取出；
		flag = 0;
		string_size j = i;
		while (j != s.size() && flag == 0){
			for (string_size x = 0; x < seperator.size(); ++x)
			if (s[j] == seperator[x]){
				flag = 1;
				break;
			}
			if (flag == 0)
				++j;
		}
		if (i != j){
			result.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return result;
}

vector<CString> StringUtils::SplitByCstr(const CString &s, const CString &seperator){
	vector<CString> result;
	int i = 0;

	while (i != s.GetLength()){
		//找到字符串中首个不等于分隔符的字母；
		int flag = 0;
		while (i != s.GetLength() && flag == 0){
			flag = 1;
			for (int x = 0; x < seperator.GetLength(); ++x)
			if (s[i] == seperator[x]){
				++i;
				flag = 0;
				break;
			}
		}

		//找到又一个分隔符，将两个分隔符之间的字符串取出；
		flag = 0;
		int j = i;
		while (j != s.GetLength() && flag == 0){
			for (int x = 0; x < seperator.GetLength(); ++x)
			if (s[j] == seperator[x]){
				flag = 1;
				break;
			}
			if (flag == 0)
				++j;
		}
		if (i != j){
			result.push_back(s.Mid(i, j - i));
			i = j;
		}
	}
	return result;
}

// 将长度小于等于8的表示16位进止的字符串转换为 LongLong
LONGLONG StringUtils::XStrToInt(CString str)
{
	int length = str.GetLength();

	if (length > 8 || length <= 0)
		return 0;

	LONGLONG ans = 0;

	for (int idx = 0; idx < length; ++idx)
	{
		ans += ascmapping[str[idx]] * oxmapping[length - idx - 1];
	}
	
	return ans;
}



BOOL StringUtils::IsValideInt(CString str)
{
	if (str.GetLength() == 0)
		return FALSE;
	int zeroIdx = str.Find('0');
	if (zeroIdx == 0 && str.GetLength() > 1)
		return FALSE;

	if (!(str.SpanIncluding(L"0123456789") == str))
		return FALSE;
	return TRUE;
}

string StringUtils::DatetimeToString(CTime srcTime)
{
	string yearStr, monthStr, dayStr, hourStr, minStr, secondStr;
	
	yearStr= srcTime.GetYear();
	monthStr = srcTime.GetMonth();
	dayStr = srcTime.GetDay();

	hourStr = srcTime.GetHour();
	minStr = srcTime.GetMinute();
	secondStr = srcTime.GetSecond();

	return yearStr + "-" + monthStr + "-" + dayStr
		+ " " + hourStr + ":" + minStr + ":" + secondStr;
}

std::string StringUtils::BytesToStr(CByteArray &bytes)
{
	int length = bytes.GetSize();
	string str="";
	for (int idx = 0; idx < length; idx ++)
	{
		BYTE byte = bytes.GetAt(idx);
		str += xintmapping[(byte / 16)] + xintmapping[byte % 16];
	}
	return str;
}
