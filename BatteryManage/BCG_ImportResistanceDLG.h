#pragma once


// CBCG_ImportResistanceDLG �Ի���

class CBCG_ImportResistanceDLG : public CDialog
{
	DECLARE_DYNAMIC(CBCG_ImportResistanceDLG)

public:
	CBCG_ImportResistanceDLG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBCG_ImportResistanceDLG();

// �Ի�������
	enum { IDD = IDD_BCG_ImportResistanceDlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
