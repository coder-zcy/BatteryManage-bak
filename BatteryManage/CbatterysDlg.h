#pragma once
#include "LowerUtils.h"
#include "afxcmn.h"


// CbatterysDlg 对话框

class CbatterysDlg : public CDialog
{
	DECLARE_DYNAMIC(CbatterysDlg)

public:
	CbatterysDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CbatterysDlg();

// 对话框数据
	enum { IDD = IDD_CBATTERYS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl compList;
	int ColNum;
	int colWidth;
	int subGroupBatNum;

	CabinetInfo cabInfo;
	int groupPerCol;	//	每列组数
	int colShowNum;		//	显示列数	
	int numPerGroup;		//	每组个数

	int groupId;								//	组号
	int subGroupId;								//	每个大组有若干个小组subGroup
	int subGroupBatId;							//	每个小组内的编号

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
