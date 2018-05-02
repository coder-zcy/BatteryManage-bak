#pragma once


// COpLoginDlg 对话框

class COpLoginDlg : public CDialog
{
	DECLARE_DYNAMIC(COpLoginDlg)

public:
	COpLoginDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COpLoginDlg();

// 对话框数据
	enum { IDD = IDD_OP_LOGIN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
