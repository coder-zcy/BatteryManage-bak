#pragma once


// CSW_DelRowNumDlg �Ի���

class CSW_DelRowNumDlg : public CDialog
{
	DECLARE_DYNAMIC(CSW_DelRowNumDlg)

public:
	CSW_DelRowNumDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSW_DelRowNumDlg();

// �Ի�������
	enum { IDD = IDD_SW_DELROWNUM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int deleteRowNum;
};
