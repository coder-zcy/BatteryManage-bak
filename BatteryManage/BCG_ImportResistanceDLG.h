#pragma once


// CBCG_ImportResistanceDLG 对话框

class CBCG_ImportResistanceDLG : public CDialog
{
	DECLARE_DYNAMIC(CBCG_ImportResistanceDLG)

public:
	CBCG_ImportResistanceDLG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBCG_ImportResistanceDLG();

// 对话框数据
	enum { IDD = IDD_BCG_ImportResistanceDlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
