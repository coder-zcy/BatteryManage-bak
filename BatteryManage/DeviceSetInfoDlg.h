#pragma once
#include "afxwin.h"


// CDeviceSetInfoDlg �Ի���
const int STEP_INFO_LENGTH = 8;

class CDeviceSetInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CDeviceSetInfoDlg)

public:
	CDeviceSetInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeviceSetInfoDlg();

// �Ի�������
	enum { IDD = IDD_DEVICE_SETINFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	void InitSpecStepInfo(int cabId, CString str);
	CString GetOtherInfo(int cabId);
	CEdit deviceSetEdit;
};
