#pragma once


// CCapCompareDlg �Ի���

class CCapCompareDlg : public CDialog
{
	DECLARE_DYNAMIC(CCapCompareDlg)

public:
	CCapCompareDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCapCompareDlg();

// �Ի�������
	enum { IDD = IDD_CAP_COMPARE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
