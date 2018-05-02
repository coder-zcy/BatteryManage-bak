#pragma once


// COpManageDlg 对话框

class COpManageDlg : public CDialog
{
	DECLARE_DYNAMIC(COpManageDlg)

public:
	COpManageDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COpManageDlg();

// 对话框数据
	enum { IDD = IDD_OP_MANAGE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
