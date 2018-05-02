#pragma once
#include "LowerUtils.h"
#include "afxcmn.h"


// CbatterysDlg �Ի���

class CbatterysDlg : public CDialog
{
	DECLARE_DYNAMIC(CbatterysDlg)

public:
	CbatterysDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CbatterysDlg();

// �Ի�������
	enum { IDD = IDD_CBATTERYS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl compList;
	int ColNum;
	int colWidth;
	int subGroupBatNum;

	CabinetInfo cabInfo;
	int groupPerCol;	//	ÿ������
	int colShowNum;		//	��ʾ����	
	int numPerGroup;		//	ÿ�����

	int groupId;								//	���
	int subGroupId;								//	ÿ�����������ɸ�С��subGroup
	int subGroupBatId;							//	ÿ��С���ڵı��

	int batCount;

	CRect rect;

	CString groupIdStr; 
	CString subGroupIdStr;
	CString subGroupBatIdStr;
	CString str;
	CabBattery* cabBattery;

	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();

	void FillTable();
	

};
