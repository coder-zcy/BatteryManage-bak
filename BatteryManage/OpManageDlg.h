#pragma once


// COpManageDlg �Ի���

class COpManageDlg : public CDialog
{
	DECLARE_DYNAMIC(COpManageDlg)

public:
	COpManageDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COpManageDlg();

// �Ի�������
	enum { IDD = IDD_OP_MANAGE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
