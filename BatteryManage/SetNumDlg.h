#pragma once


// CSetNODlg �Ի���

class CSetNumDlg : public CDialog
{
	DECLARE_DYNAMIC(CSetNumDlg)

public:
	CSetNumDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetNumDlg();

	// �Ի�������
	enum { IDD = IDD_SET_NUM_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit invalidNOEdit;
	CComboBox opNOCombo;
	CEdit invalidSetEdit;
	CComboBox fromNOCombo;
	CButton noMMBtn;
	CButton noMPBtn;
	CButton applyBtn;
	CListCtrl opNOList;
	CButton opNOSetOK;
	CButton opNOSetCancel;
};
