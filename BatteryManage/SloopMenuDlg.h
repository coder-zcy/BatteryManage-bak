#pragma once
#include "afxwin.h"
#include "CapShowType.h"

// CSloopMenuDlg �Ի���

class CSloopMenuDlg : public CDialog
{
	DECLARE_DYNAMIC(CSloopMenuDlg)

public:
	CSloopMenuDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSloopMenuDlg();

// �Ի�������
	enum { IDD = IDD_SLOOP_MENU_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDataChk();
	CButton dataCheck;
	afx_msg void OnBnClickedRefreshBtn();
};
