#pragma once
#include "CommConf.h"
#include "afxwin.h"


// CCommDlg 对话框

class CCommDlg : public CDialog
{
	DECLARE_DYNAMIC(CCommDlg)

public:
	CCommDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCommDlg();

	// 对话框数据
	enum { IDD = IDD_COMM_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
