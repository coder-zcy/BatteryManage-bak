#pragma once


// CAdminLoginDlg �Ի���

class CAdminLoginDlg : public CDialog
{
	DECLARE_DYNAMIC(CAdminLoginDlg)

public:
	CAdminLoginDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAdminLoginDlg();

// �Ի�������
	enum { IDD = IDD_ADMIN_LOGIN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
