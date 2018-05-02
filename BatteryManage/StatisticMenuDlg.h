#pragma once
#include "CapShowType.h"

// CStatisticMenuDlg 对话框

class CStatisticMenuDlg : public CDialog
{
	DECLARE_DYNAMIC(CStatisticMenuDlg)

public:
	CStatisticMenuDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStatisticMenuDlg();

// 对话框数据
	enum { IDD = IDD_STATISTIC_MENU_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnBnClickedDataSrcBtn();
	afx_msg void OnBnClickedLoadSegBtn();
	afx_msg void OnBnClickedSaveSegBtn();
};
