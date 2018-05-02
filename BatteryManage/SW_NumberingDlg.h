#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <vector>
using namespace std;
// CSW_NumberingDlg �Ի���

class CSW_NumberingDlg : public CDialog
{
	DECLARE_DYNAMIC(CSW_NumberingDlg)

public:
	CSW_NumberingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSW_NumberingDlg();
	virtual BOOL OnInitDialog();
// �Ի�������
	enum { IDD = IDD_SW_NUMBERING_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox ComCabinet;
	CButton BtnApply;
	CButton BtnLoad;
	CListCtrl numberingList;
	afx_msg void OnCbnSelchangeSwNumCom();
	afx_msg void OnBnClickedSwNumApply();
	afx_msg void OnBnClickedSwNumLoad();
private:
	std::vector<vector<int>> battery_number;
public:
	afx_msg void OnClose();
};
