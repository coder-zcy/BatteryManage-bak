#pragma once


// CLoopDlg 对话框

class CLoopDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoopDlg)

public:
	CLoopDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoopDlg();

// 对话框数据
	enum { IDD = IDD_LOOP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
