#pragma once


// COpLogDlg �Ի���

class COpLogDlg : public CDialog
{
	DECLARE_DYNAMIC(COpLogDlg)

public:
	COpLogDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COpLogDlg();

// �Ի�������
	enum { IDD = IDD_OP_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
