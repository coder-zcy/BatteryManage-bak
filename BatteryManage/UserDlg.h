#pragma once
#include "afxwin.h"


// CUserDlg �Ի���

class CUserDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserDlg)

public:
	CUserDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserDlg();

// �Ի�������
	enum { IDD = IDD_USER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	CEdit chartNameEdit;
	CEdit bodyEdit;
	CEdit dataEdit;
	CEdit remarkEdit;
	CButton initRemoveChk;
	CButton overRemoveChk;
	CButton showCapChk;

	int maRadVal;
	int aradVal;
	int chartNameVal;
	int bodyVal;
	int dataVal;
	int remarkVal;
	int initRemoveVal;
	int overRemoveVal;
	int showCapVal;

	CString userSetPath;

	virtual BOOL OnInitDialog();

	void SaveUserSet();

};
