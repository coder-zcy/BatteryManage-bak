#pragma once


// CSW_AddRowNumDlg �Ի���

class CSW_AddRowNumDlg : public CDialog
{
	DECLARE_DYNAMIC(CSW_AddRowNumDlg)

public:
	CSW_AddRowNumDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSW_AddRowNumDlg();

// �Ի�������
	enum { IDD = IDD_SW_ADDROW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int rowNum;
};
