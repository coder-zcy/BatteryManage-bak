#pragma once
#include "afxwin.h"
#include "CapShowType.h"

// CSloopMenuDlg 对话框

class CSloopMenuDlg : public CDialog
{
	DECLARE_DYNAMIC(CSloopMenuDlg)

public:
	CSloopMenuDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSloopMenuDlg();

// 对话框数据
	enum { IDD = IDD_SLOOP_MENU_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDataChk();
	CButton dataCheck;
	afx_msg void OnBnClickedRefreshBtn();
};
