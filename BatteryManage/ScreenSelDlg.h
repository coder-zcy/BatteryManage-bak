#pragma once


// CScreenSelDlg 对话框

class CScreenSelDlg : public CDialog
{
	DECLARE_DYNAMIC(CScreenSelDlg)

public:
	CScreenSelDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CScreenSelDlg();

// 对话框数据
	enum { IDD = IDD_SCREEN_SEL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
