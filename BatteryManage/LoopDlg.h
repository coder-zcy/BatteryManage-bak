#pragma once


// CLoopDlg �Ի���

class CLoopDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoopDlg)

public:
	CLoopDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLoopDlg();

// �Ի�������
	enum { IDD = IDD_LOOP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
