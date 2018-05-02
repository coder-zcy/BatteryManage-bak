#pragma once
#include <iostream>
#include <string>
#include "BatteryColor.h"

using namespace std;

// CColorDlg 对话框

class CColorDlg : public CDialog
{
	DECLARE_DYNAMIC(CColorDlg)

public:
	CColorDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CColorDlg();

	// 对话框数据
	enum { IDD = IDD_COLOR_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedChargePic();
	afx_msg void OnStnClickedRecyclePic();

	CStatic chargePic;
	CStatic recyclePic;
	CStatic storPic;
	CStatic unstorPic;
	CStatic stopPic;
	CStatic dischargePic;
	CStatic layPic;
	CStatic vaChargePic;
	CStatic vErrorPic;
	CStatic aErrorPic;
	CStatic overAlarmPic;
	CStatic leakAlarmPic;
	CStatic badContPic;
	CStatic vOverPic;
	CStatic batteryWinPic;

	//CCustomBtn myPic1;
	CButton defaultBtn;
	afx_msg void OnStnClickedVaChargePic();
	afx_msg void OnStnClickedLayPic();
	afx_msg void OnStnClickedDischargePic();
	afx_msg void OnStnClickedUnstorPic();
	afx_msg void OnStnClickedStopPic();
	afx_msg void OnStnClickedStorPic();
	afx_msg void OnStnClickedVErrorPic();
	afx_msg void OnStnClickedAErrorPic();
	afx_msg void OnStnClickedOverAlarmPic();
	afx_msg void OnStnClickedLeakAlarmPic();
	afx_msg void OnStnClickedBadContPic();
	afx_msg void OnStnClickedVOverPic();
	afx_msg void OnStnClickedBactteryWinPic();
	afx_msg void OnBnClickedDefaultBtn();
	//afx_msg void OnPaint();
	afx_msg void OnStnClickedPic();

	virtual BOOL OnInitDialog();

	CString colorPath;
	void ReadIniColor();
	void SetColor(CStatic &pic, COLORREF color);

	void SetDefColor(CStatic &pic, COLORREF color);
	void SaveColorSet();

	afx_msg void OnPaint();
};

