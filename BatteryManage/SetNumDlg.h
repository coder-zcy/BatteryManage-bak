#pragma once


// CSetNODlg 对话框

class CSetNumDlg : public CDialog
{
	DECLARE_DYNAMIC(CSetNumDlg)

public:
	CSetNumDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetNumDlg();

	// 对话框数据
	enum { IDD = IDD_SET_NUM_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
