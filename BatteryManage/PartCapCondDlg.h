#pragma once
#include "afxwin.h"
#include <iostream>
#include <vector>

using namespace std;

// CPartCapCondDlg 对话框
const int DEF_ROW_GAP = 32;
const int DEF_TOP_MARGIN = 64;
const int ASSEMBLY_NUM = 16;

class CPartCapCondDlg : public CDialog
{
	DECLARE_DYNAMIC(CPartCapCondDlg)

public:
	CPartCapCondDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPartCapCondDlg();

// 对话框数据
	enum { IDD = IDD_PART_CAP_COND_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit minEdit1;
	CEdit minEdit2;
	CEdit minEdit3;
	CEdit minEdit4;
	CEdit minEdit5;
	CEdit minEdit6;
	CEdit minEdit7;
	CEdit minEdit8;
	CEdit minEdit9;
	CEdit minEdit10;
	CEdit minEdit11;
	CEdit minEdit12;
	CEdit minEdit13;
	CEdit minEdit14;
	CEdit minEdit15;
	CEdit minEdit16;
	CEdit maxEdit1;
	CEdit maxEdit2;
	CEdit maxEdit3;
	CEdit maxEdit4;
	CEdit maxEdit5;
	CEdit maxEdit6;
	CEdit maxEdit7;
	CEdit maxEdit8;
	CEdit maxEdit9;
	CEdit maxEdit10;
	CEdit maxEdit11;
	CEdit maxEdit12;
	CEdit maxEdit13;
	CEdit maxEdit14;
	CEdit maxEdit15;
	CEdit maxEdit16;
	CEdit flagEdit1;
	CEdit flagEdit2;
	CEdit flagEdit3;
	CEdit flagEdit4;
	CEdit flagEdit5;
	CEdit flagEdit6;
	CEdit flagEdit7;
	CEdit flagEdit8;
	CEdit flagEdit9;
	CEdit flagEdit10;
	CEdit flagEdit11;
	CEdit flagEdit12;
	CEdit flagEdit13;
	CEdit flagEdit14;
	CEdit flagEdit15;
	CEdit flagEdit16;
	CStatic colorPic1;
	CStatic colorPic2;
	CStatic colorPic3;
	CStatic colorPic4;
	CStatic colorPic5;
	CStatic colorPic6;
	CStatic colorPic7;
	CStatic colorPic8;
	CStatic colorPic9;
	CStatic colorPic10;
	CStatic colorPic11;
	CStatic colorPic12;
	CStatic colorPic13;
	CStatic colorPic14;
	CStatic colorPic15;
	CStatic colorPic16;

	vector<CEdit *> minEdits;
	vector<CEdit *> maxEdits;
	vector<CEdit *> flagEdits;
	vector<CStatic *> colorPics;
	vector<CStatic *> seqStatics;
	
	virtual BOOL OnInitDialog();
	void InitAssembly();
	CStatic seqStatic;
	CStatic minStatic;
	CStatic maxStatic;
	CStatic colorStatic;
	CStatic flagStatic;
	CStatic seqStatic1;
	CStatic seqStatic2;
	CStatic seqStatic3;
	CStatic seqStatic4;
	CStatic seqStatic5;
	CStatic seqStatic6;
	CStatic seqStatic7;
	CStatic seqStatic8;
	CStatic seqStatic9;
	CStatic seqStatic10;
	CStatic seqStatic11;
	CStatic seqStatic12;
	CStatic seqStatic13;
	CStatic seqStatic14;
	CStatic seqStatic15;
	CStatic seqStatic16;
	afx_msg void OnBnClickedOk();
	afx_msg void OnPaint();
	CComboBox partCodeCom;
	afx_msg void OnStnClickedColorPic1();
	afx_msg void OnStnClickedColorPic2();
	afx_msg void OnStnClickedColorPic3();
	afx_msg void OnStnClickedColorPic4();
	afx_msg void OnStnClickedColorPic5();
	afx_msg void OnStnClickedColorPic6();
	afx_msg void OnStnClickedColorPic7();
	afx_msg void OnStnClickedColorPic8();
	afx_msg void OnStnClickedColorPic9();
	afx_msg void OnStnClickedColorPic10();
	afx_msg void OnStnClickedColorPic11();
	afx_msg void OnStnClickedColorPic12();
	afx_msg void OnStnClickedColorPic13();
	afx_msg void OnStnClickedColorPic14();
	afx_msg void OnStnClickedColorPic15();
	afx_msg void OnStnClickedColorPic16();

	void SetColor(CapShowType *capShowType, int idx, COLORREF color);
	void UpdateSegData();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void UpdateRelativeEditsByDown(CWnd *focus);
	void UpdateRelativeEdits(CWnd* focus);

};
