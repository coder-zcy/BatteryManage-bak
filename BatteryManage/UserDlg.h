#pragma once
#include "afxwin.h"


// CUserDlg 对话框

class CUserDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserDlg)

public:
	CUserDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserDlg();

// 对话框数据
	enum { IDD = IDD_USER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
