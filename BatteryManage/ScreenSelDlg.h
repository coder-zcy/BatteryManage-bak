#pragma once


// CScreenSelDlg �Ի���

class CScreenSelDlg : public CDialog
{
	DECLARE_DYNAMIC(CScreenSelDlg)

public:
	CScreenSelDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CScreenSelDlg();

// �Ի�������
	enum { IDD = IDD_SCREEN_SEL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
