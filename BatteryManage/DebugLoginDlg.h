#pragma once


// CDebugLoginDlg 对话框

class CDebugLoginDlg : public CDialog
{
	DECLARE_DYNAMIC(CDebugLoginDlg)

public:
	CDebugLoginDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDebugLoginDlg();

// 对话框数据
	enum { IDD = IDD_DEBUG_LOGIN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
