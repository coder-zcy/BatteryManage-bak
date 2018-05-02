#pragma once


// CChkBatteryDlg 对话框

class CChkBatteryDlg : public CDialog
{
	DECLARE_DYNAMIC(CChkBatteryDlg)

public:
	CChkBatteryDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChkBatteryDlg();

// 对话框数据
	enum { IDD = IDD_CHK_BATTERY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
