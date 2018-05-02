#pragma once


// CInitCopyDlg 对话框

class CInitCopyDlg : public CDialog
{
	DECLARE_DYNAMIC(CInitCopyDlg)

public:
	CInitCopyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInitCopyDlg();

	// 对话框数据
	enum { IDD = IDD_INIT_COPYDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	CCheckListBox lowerCheckList;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSelall();
	afx_msg void OnBnClickedDelall();
	afx_msg void OnBnClickedOk();
};
