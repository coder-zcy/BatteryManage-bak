#pragma once


// CExcepRemoveDlg �Ի���

class CExcepRemoveDlg : public CDialog
{
	DECLARE_DYNAMIC(CExcepRemoveDlg)

public:
	CExcepRemoveDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CExcepRemoveDlg();

// �Ի�������
	enum { IDD = IDD_EXCEP_REMOVE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
