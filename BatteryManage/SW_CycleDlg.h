#pragma once
#include "afxwin.h"


// CSW_CycleDlg �Ի���

class CSW_CycleDlg : public CDialog
{
	DECLARE_DYNAMIC(CSW_CycleDlg)

public:
	CSW_CycleDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSW_CycleDlg();
	virtual BOOL OnInitDialog();
// �Ի�������
	enum { IDD = IDD_SW_CYCLE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int startStep;
	int cycleTime;
	CEdit endStep;
};
