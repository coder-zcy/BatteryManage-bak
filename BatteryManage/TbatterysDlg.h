#pragma once
#include "LowerUtils.h"
#include "afxcmn.h"


// CTbatterysDlg 对话框

class CTbatterysDlg : public CDialog
{
	DECLARE_DYNAMIC(CTbatterysDlg)

public:
	CTbatterysDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTbatterysDlg();

	// 对话框数据
	enum { IDD = IDD_TBATTERYS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
	int groupPerCol;	//	每列组数
	int colShowNum;		//	显示列数	
	int numPerGroup;		//	每组个数

	int subGroupId;								//	每个大组有若干个小组subGroup
	int subGroupBatId;							//	每个小组内的编号

	CRect rect;
	CString str;
	CabBattery* cabBattery;
	CString subGroupIdStr;
	CString subGroupBatIdStr;

	afx_msg void OnPaint();
};
