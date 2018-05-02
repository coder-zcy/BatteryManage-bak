#pragma once


// CSW_AddRowNumDlg 对话框

class CSW_AddRowNumDlg : public CDialog
{
	DECLARE_DYNAMIC(CSW_AddRowNumDlg)

public:
	CSW_AddRowNumDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSW_AddRowNumDlg();

// 对话框数据
	enum { IDD = IDD_SW_ADDROW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int rowNum;
};
