#pragma once
#include "afxwin.h"


// CBCG_PairDLG �Ի���

class CBCG_PairDLG : public CDialog
{
	DECLARE_DYNAMIC(CBCG_PairDLG)

public:
	CBCG_PairDLG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBCG_PairDLG();
	virtual BOOL OnInitDialog();
// �Ի�������
	enum { IDD = IDD_BCG_PairDlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox pairBatteryNum;
	CComboBox MainSortPara;
};
