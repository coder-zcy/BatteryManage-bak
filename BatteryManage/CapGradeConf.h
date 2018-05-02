#pragma once
#include "GradeDetailInfo.h"


class CapGradeConf
{

private:
	CapGradeConf();
	~CapGradeConf();
	static CapGradeConf* capGradeConf;
public:
	int codeSel;
	int codeSelCount;
	vector<CString> codeNames;
	vector<CGradeDetailInfo> gradeDetailInfos;

	static CapGradeConf *GetInstance() {
		return capGradeConf;
	}
	void SaveToFile();
	void SetCodeSel(int codeSel);
	void SetCodeSelCount(int codeSelCount);

};



