#pragma once


// CInitCopyDlg �Ի���

class CInitCopyDlg : public CDialog
{
	DECLARE_DYNAMIC(CInitCopyDlg)

public:
	CInitCopyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInitCopyDlg();

	// �Ի�������
	enum { IDD = IDD_INIT_COPYDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	CCheckListBox lowerCheckList;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSelall();
	afx_msg void OnBnClickedDelall();
	afx_msg void OnBnClickedOk();
};
