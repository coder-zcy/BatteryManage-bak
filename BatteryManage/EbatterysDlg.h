#pragma once
#include "afxcmn.h"


// CEbatterysDlg 对话框

class CEbatterysDlg : public CDialog
{
	DECLARE_DYNAMIC(CEbatterysDlg)

public:
	CEbatterysDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEbatterysDlg();

	// 对话框数据
	enum { IDD = IDD_EBATTERYS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CListCtrl excepList;

	int ColNum;
	int colWidth;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
