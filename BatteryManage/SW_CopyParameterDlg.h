#pragma once
#include "afxwin.h"

//#include "LowerCabs.h"

#include <fstream>

using namespace std;



// CSW_CopyParameterDlg �Ի���

class CSW_CopyParameterDlg : public CDialog
{
	DECLARE_DYNAMIC(CSW_CopyParameterDlg)

public:
	CSW_CopyParameterDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSW_CopyParameterDlg();
	virtual BOOL OnInitDialog();
// �Ի�������
	enum { IDD = IDD_SW_CPPARAMETER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	
	CButton BtnFullCheck;
	CButton BtnDelFullCheck;
	afx_msg void OnBnClickedSwFullcheck();
	afx_msg void OnBnClickedSwCancelFullcheck();
	CCheckListBox m_ctCheckList;
	afx_msg void OnBnClickedOk();
};
