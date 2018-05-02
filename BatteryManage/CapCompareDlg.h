#pragma once


// CCapCompareDlg 对话框

class CCapCompareDlg : public CDialog
{
	DECLARE_DYNAMIC(CCapCompareDlg)

public:
	CCapCompareDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCapCompareDlg();

// 对话框数据
	enum { IDD = IDD_CAP_COMPARE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
