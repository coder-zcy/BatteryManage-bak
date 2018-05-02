#pragma once
#include "afxwin.h"

//#include "LowerCabs.h"

#include <fstream>

using namespace std;



// CSW_CopyParameterDlg 对话框

class CSW_CopyParameterDlg : public CDialog
{
	DECLARE_DYNAMIC(CSW_CopyParameterDlg)

public:
	CSW_CopyParameterDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSW_CopyParameterDlg();
	virtual BOOL OnInitDialog();
// 对话框数据
	enum { IDD = IDD_SW_CPPARAMETER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	CButton BtnFullCheck;
	CButton BtnDelFullCheck;
	afx_msg void OnBnClickedSwFullcheck();
	afx_msg void OnBnClickedSwCancelFullcheck();
	CCheckListBox m_ctCheckList;
	afx_msg void OnBnClickedOk();
};
