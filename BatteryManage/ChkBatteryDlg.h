#pragma once


// CChkBatteryDlg �Ի���

class CChkBatteryDlg : public CDialog
{
	DECLARE_DYNAMIC(CChkBatteryDlg)

public:
	CChkBatteryDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChkBatteryDlg();

// �Ի�������
	enum { IDD = IDD_CHK_BATTERY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
