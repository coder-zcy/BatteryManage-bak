#pragma once
#include "afxwin.h"


// COtherDlg 对话框

class COtherDlg : public CDialog
{
	DECLARE_DYNAMIC(COtherDlg)

public:
	COtherDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COtherDlg();

	// 对话框数据
	enum { IDD = IDD_OTHER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton addPartChk;
	CButton twoPartChk;
	CButton onePartChk;
	CButton stopPartChk;
	CButton constPartChk;
	CButton layPartChk;
	CButton stepExceptChk;
	CButton vavgpmExceptChk;
	CButton vavgExceptChk;
	CButton voverExceptChk;
	CButton alertExceptChk;
	CEdit vavgEdit;
	CButton createByTimeChk;
	CEdit initPathEdit;
	CButton needPartDataChk;
	CButton saveCreateChk;
	CButton mdbPointChk;
	CButton copyToCatalogChk;

	int addPartVal;
	int	twoPartVal;
	int	onePartVal;
	int	stopPartVal;
	int	constPartVal;
	int	layPartVal;
	int	stepExceptVal;
	int	vavgpmExceptVal;
	int	vavgExceptVal;
	int	voverExceptVal;
	int alertExceptVal;
	int	vavgVal;
	int	createByTimeVal;
	CString	initPathVal;
	int	needPartDataVal;
	int	saveCreateVal;
	int	mdbPointVal;
	int	copyToCatalogVal;

	CString otherPath;

	afx_msg void OnBnClickedFileBrowse();
	virtual BOOL OnInitDialog();
	void SaveOtherSet();
};
