#pragma once


// CCapExportDlg �Ի���

class CCapExportDlg : public CDialog
{
	DECLARE_DYNAMIC(CCapExportDlg)

public:
	CCapExportDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCapExportDlg();

// �Ի�������
	enum { IDD = IDD_CAP_EXPORT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
