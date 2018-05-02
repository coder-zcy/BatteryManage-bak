#pragma once
#include "afxwin.h"
#include "DlgComm.h"	// 对话框之间通信用的辅助类

// CSW_SendDlg 对话框

class CSW_SendDlg : public CDialog
{
	DECLARE_DYNAMIC(CSW_SendDlg)

public:
	CSW_SendDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSW_SendDlg();
	virtual BOOL OnInitDialog();
// 对话框数据
	enum { IDD = IDD_SW_SEND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CCheckListBox m_ctCheckList;
	CButton BtnFullCheck;
	CButton BtnCanFullCheck;
	afx_msg void OnBnClickedSwSendFullcheck();
	afx_msg void OnBnClickedSwSendCanfullcheck();
	afx_msg void OnBnClickedOk();
	afx_msg void OnClose();
};
