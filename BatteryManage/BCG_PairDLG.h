#pragma once
#include "afxwin.h"


// CBCG_PairDLG 对话框

class CBCG_PairDLG : public CDialog
{
	DECLARE_DYNAMIC(CBCG_PairDLG)

public:
	CBCG_PairDLG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBCG_PairDLG();
	virtual BOOL OnInitDialog();
// 对话框数据
	enum { IDD = IDD_BCG_PairDlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox pairBatteryNum;
	CComboBox MainSortPara;
};
