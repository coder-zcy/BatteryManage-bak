#pragma once
#include "afxwin.h"


// CDeviceSetInfoDlg 对话框
const int STEP_INFO_LENGTH = 8;

class CDeviceSetInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CDeviceSetInfoDlg)

public:
	CDeviceSetInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeviceSetInfoDlg();

// 对话框数据
	enum { IDD = IDD_DEVICE_SETINFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	void InitSpecStepInfo(int cabId, CString str);
	CString GetOtherInfo(int cabId);
	CEdit deviceSetEdit;
};
