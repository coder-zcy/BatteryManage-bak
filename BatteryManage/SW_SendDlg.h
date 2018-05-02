#pragma once
#include "afxwin.h"
#include "DlgComm.h"	// �Ի���֮��ͨ���õĸ�����

// CSW_SendDlg �Ի���

class CSW_SendDlg : public CDialog
{
	DECLARE_DYNAMIC(CSW_SendDlg)

public:
	CSW_SendDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSW_SendDlg();
	virtual BOOL OnInitDialog();
// �Ի�������
	enum { IDD = IDD_SW_SEND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CCheckListBox m_ctCheckList;
	CButton BtnFullCheck;
	CButton BtnCanFullCheck;
	afx_msg void OnBnClickedSwSendFullcheck();
	afx_msg void OnBnClickedSwSendCanfullcheck();
	afx_msg void OnBnClickedOk();
	afx_msg void OnClose();
};
