#pragma once
#include "afxcmn.h"


// CEbatterysDlg �Ի���

class CEbatterysDlg : public CDialog
{
	DECLARE_DYNAMIC(CEbatterysDlg)

public:
	CEbatterysDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEbatterysDlg();

	// �Ի�������
	enum { IDD = IDD_EBATTERYS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
