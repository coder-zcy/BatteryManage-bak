#pragma once


// CExcepRemoveDlg 对话框

class CExcepRemoveDlg : public CDialog
{
	DECLARE_DYNAMIC(CExcepRemoveDlg)

public:
	CExcepRemoveDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CExcepRemoveDlg();

// 对话框数据
	enum { IDD = IDD_EXCEP_REMOVE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
