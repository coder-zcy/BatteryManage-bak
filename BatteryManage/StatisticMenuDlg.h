#pragma once
#include "CapShowType.h"

// CStatisticMenuDlg �Ի���

class CStatisticMenuDlg : public CDialog
{
	DECLARE_DYNAMIC(CStatisticMenuDlg)

public:
	CStatisticMenuDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStatisticMenuDlg();

// �Ի�������
	enum { IDD = IDD_STATISTIC_MENU_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnBnClickedDataSrcBtn();
	afx_msg void OnBnClickedLoadSegBtn();
	afx_msg void OnBnClickedSaveSegBtn();
};
