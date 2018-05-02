#pragma once

#include "ScreenDlg.h"
#include "CommDlg.h"
#include "ColorDlg.h"
#include "OtherDlg.h"
#include "UserDlg.h"
#include "afxcmn.h"

// CInitDlg �Ի���

class CInitDlg : public CDialog
{
	DECLARE_DYNAMIC(CInitDlg)

public:
	CInitDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInitDlg();

// �Ի�������
	enum { IDD = IDD_INIT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl initTab;
	// ����л��ĶԻ���
	CScreenDlg screenDlg;
	CCommDlg commDlg;
	CColorDlg colorDlg;
	CUserDlg userDlg;
	COtherDlg otherDlg;

	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeInittab(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedSaveSet();

	void SaveScreenSet();
	void SaveCommSet();
    void SaveOtherSet();
	void SaveUserSet();
	void SaveColorSet();
};
