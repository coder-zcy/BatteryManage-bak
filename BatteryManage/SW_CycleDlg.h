#pragma once
#include "afxwin.h"


// CSW_CycleDlg 对话框

class CSW_CycleDlg : public CDialog
{
	DECLARE_DYNAMIC(CSW_CycleDlg)

public:
	CSW_CycleDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSW_CycleDlg();
	virtual BOOL OnInitDialog();
// 对话框数据
	enum { IDD = IDD_SW_CYCLE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int startStep;
	int cycleTime;
	CEdit endStep;
};
