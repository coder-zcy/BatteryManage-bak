#pragma once


// CCapExportDlg 对话框

class CCapExportDlg : public CDialog
{
	DECLARE_DYNAMIC(CCapExportDlg)

public:
	CCapExportDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCapExportDlg();

// 对话框数据
	enum { IDD = IDD_CAP_EXPORT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
