#pragma once
#include "FileCabData.h"
#include "LowerUtils.h"
#include "afxwin.h"

// CBatWorkDetailDlg 对话框




class CBatWorkDetailDlg : public CDialog
{
	DECLARE_DYNAMIC(CBatWorkDetailDlg)

public:
	CBatWorkDetailDlg(CWnd* pParent = NULL);   // 标准构造函数
	CBatWorkDetailDlg(CWnd* pParent, CFileCabData fileCabData, int windowFlag);
	virtual ~CBatWorkDetailDlg();

// 对话框数据
	enum { IDD = IDD_BATWORK_DETAIL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void InitDialogByWorkingInfo();
	void InitDialogByDataFile();
	void InitDialogBySingleBat();
	CEdit workDetailEdit;
	CFileCabData fileCabData;
	int windowFlag;
};
