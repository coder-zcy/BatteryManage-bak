#pragma once


// CDebugLoginDlg �Ի���

class CDebugLoginDlg : public CDialog
{
	DECLARE_DYNAMIC(CDebugLoginDlg)

public:
	CDebugLoginDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDebugLoginDlg();

// �Ի�������
	enum { IDD = IDD_DEBUG_LOGIN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
