#pragma once
#include "LowerUtils.h"
#include "afxcmn.h"


// CTbatterysDlg �Ի���

class CTbatterysDlg : public CDialog
{
	DECLARE_DYNAMIC(CTbatterysDlg)

public:
	CTbatterysDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTbatterysDlg();

	// �Ի�������
	enum { IDD = IDD_TBATTERYS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CListCtrl tableList;
	int ColNum;
	int colWidth;
	int subGroupBatNum;
	virtual BOOL OnInitDialog();

	void FillTable();


	CabinetInfo cabInfo;
	int groupPerCol;	//	ÿ������
	int colShowNum;		//	��ʾ����	
	int numPerGroup;		//	ÿ�����

	int subGroupId;								//	ÿ�����������ɸ�С��subGroup
	int subGroupBatId;							//	ÿ��С���ڵı��

	CRect rect;
	CString str;
	CabBattery* cabBattery;
	CString subGroupIdStr;
	CString subGroupBatIdStr;

	afx_msg void OnPaint();
};
