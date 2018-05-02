#pragma once
#include "CommConf.h"
#include "afxwin.h"


// CCommDlg �Ի���

class CCommDlg : public CDialog
{
	DECLARE_DYNAMIC(CCommDlg)

public:
	CCommDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCommDlg();

	// �Ի�������
	enum { IDD = IDD_COMM_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	CComboBox commPortBox;
	CComboBox commBaudBox;
	CComboBox commTimeBox;
	CButton chkChk;
	CButton needLoginChk;
	CButton forbdModifyChk;
	CButton onlineReadChk;
	CButton exitReadChk;
	CButton forbdOtherChk;
	

	CommConf *commConf;

	virtual BOOL OnInitDialog();

	void SaveCommSet();
};
