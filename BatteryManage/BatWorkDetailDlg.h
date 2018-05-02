#pragma once
#include "FileCabData.h"
#include "LowerUtils.h"
#include "afxwin.h"

// CBatWorkDetailDlg �Ի���




class CBatWorkDetailDlg : public CDialog
{
	DECLARE_DYNAMIC(CBatWorkDetailDlg)

public:
	CBatWorkDetailDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CBatWorkDetailDlg(CWnd* pParent, CFileCabData fileCabData, int windowFlag);
	virtual ~CBatWorkDetailDlg();

// �Ի�������
	enum { IDD = IDD_BATWORK_DETAIL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void InitDialogByWorkingInfo();
	void InitDialogByDataFile();
	void InitDialogBySingleBat();
	CEdit workDetailEdit;
	CFileCabData fileCabData;
	int windowFlag;
};
