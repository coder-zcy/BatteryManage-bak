#pragma once


// CCurveDataDlg �Ի���

class CCurveDataDlg : public CDialog
{
	DECLARE_DYNAMIC(CCurveDataDlg)

public:
	CCurveDataDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCurveDataDlg();

// �Ի�������
	enum { IDD = IDD_CURVE_DATA_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
