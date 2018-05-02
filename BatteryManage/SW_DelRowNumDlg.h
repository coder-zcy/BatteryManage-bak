#pragma once


// CSW_DelRowNumDlg 对话框

class CSW_DelRowNumDlg : public CDialog
{
	DECLARE_DYNAMIC(CSW_DelRowNumDlg)

public:
	CSW_DelRowNumDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSW_DelRowNumDlg();

// 对话框数据
	enum { IDD = IDD_SW_DELROWNUM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int deleteRowNum;
};
