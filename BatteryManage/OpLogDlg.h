#pragma once


// COpLogDlg 对话框

class COpLogDlg : public CDialog
{
	DECLARE_DYNAMIC(COpLogDlg)

public:
	COpLogDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COpLogDlg();

// 对话框数据
	enum { IDD = IDD_OP_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
