#pragma once


// Test �Ի���

class Test : public CDialog
{
	DECLARE_DYNAMIC(Test)

public:
	Test(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Test();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
