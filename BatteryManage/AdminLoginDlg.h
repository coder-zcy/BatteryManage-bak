#pragma once


// CAdminLoginDlg 对话框

class CAdminLoginDlg : public CDialog
{
	DECLARE_DYNAMIC(CAdminLoginDlg)

public:
	CAdminLoginDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAdminLoginDlg();

// 对话框数据
	enum { IDD = IDD_ADMIN_LOGIN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
