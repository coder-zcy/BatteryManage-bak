#pragma once


// COpLoginDlg �Ի���

class COpLoginDlg : public CDialog
{
	DECLARE_DYNAMIC(COpLoginDlg)

public:
	COpLoginDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COpLoginDlg();

// �Ի�������
	enum { IDD = IDD_OP_LOGIN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
