#pragma once
#include "afxwin.h"


// CExcludeExceptionDLG �Ի���

class CExcludeExceptionDLG : public CDialog
{
	DECLARE_DYNAMIC(CExcludeExceptionDLG)

public:
	CExcludeExceptionDLG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CExcludeExceptionDLG();	
// �Ի�������
	enum { IDD = IDD_BCG_ExcludeExceptionDlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CButton current_exption;
	CButton charge_delterI_warning;
	CButton leak_current_warning;
	CButton voltage_exception;
	CButton open_voltage_outofrange;
	CButton charge_deltaV_warning;
	CButton discharge_deltaV_warning;
	CButton OCV_exception;
	CButton voltage_high_warning;
	CButton capacity_over_warning;
	CButton poor_contact;
	afx_msg void OnBnClickedBcgEedlgRadio1();
	afx_msg void OnBnClickedBcgEedlgRadio2();
	afx_msg void OnBnClickedBcgEedlgRadio3();
	afx_msg void OnBnClickedBcgEedlgRadio4();
};
