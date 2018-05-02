#pragma once


// CCurveDataDlg 对话框

class CCurveDataDlg : public CDialog
{
	DECLARE_DYNAMIC(CCurveDataDlg)

public:
	CCurveDataDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCurveDataDlg();

// 对话框数据
	enum { IDD = IDD_CURVE_DATA_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
