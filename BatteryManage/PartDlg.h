#pragma once
#include "GridCtrl_src\GridCtrl.h"
#include "PartBattery.h"
#include "afxwin.h"
#include "FileCabData.h"

// CPartDlg 对话框

class CPartDlg : public CDialog
{
	DECLARE_DYNAMIC(CPartDlg)

public:
	CPartDlg(CWnd* pParent = NULL);   // 标准构造函数
	CPartDlg(CWnd* pParent, CFileCabData &fileCabData);
	virtual ~CPartDlg();

// 对话框数据
	enum { IDD = IDD_PART_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);

	int defColWidth;
	int defRowHeight;

	void InitGrid();
	GV_ITEM CreateGridItem(int row, int col, UINT mask, DWORD format, CString txt);
	void MoveWindowToPos(int left, int top, int right, int bottom);
	void InitTestInfo(const TestInfo &testInfo);
	void SetGridRowColSize(int rowNum, int colNum, int fixRowNum, int fixColNUm);
	


	CFileCabData fileCabData;
	int colNum;
	int rowCount;
	int groupId, subGroupId, subGroupBatId;
	int batCount;
	CString groupIdCstr, subGroupIdCstr, subGroupBatIdCstr, rowIdxCstr;

	//vector<vector<CPartBattery *>> stepPartbatterys;

	virtual BOOL OnInitDialog();
	void InitGridRowHead();
	void InitGridColHead();
	void InitGridContent();
	void CreatePartBatData();
	void InitCombox();
	void FillPartDataToGrid(int autoCheck, int batIdCheck);

	void FillCapDetailData(vector<CPartBattery *> &partBatterys, int autoCheck, int batIdCheck);
	void FillTimeDetailData(vector<CPartBattery *> &partBatterys, int autoCheck, int batIdCheck);
	void FillOvDetailData(vector<CPartBattery *> &partBatterys, int autoCheck, int batIdCheck);
	void FillAvDetailData(vector<CPartBattery *> &partBatterys, int autoCheck, int batIdCheck);
	void FillEvDetailData(vector<CPartBattery *> &partBatterys, int autoCheck, int batIdCheck);
	void FillEnergyDetailData(vector<CPartBattery *> &partBatterys, int autoCheck, int batIdCheck);
	void FillEcDetailData(vector<CPartBattery *> &partBatterys, int autoCheck, int batIdCheck);

	CGridCtrl partGrid;
	CComboBox attrCom;
	CComboBox stepCombo;
	CComboBox datatimeCom;
	afx_msg void OnCbnSelchangeAttrCombo();
	afx_msg void OnCbnSelchangeStepCombo();
	afx_msg void OnGridRClick(NMHDR *pNotifyStruct, LRESULT* pResult);
	void UpdatePartData(int autoCheck, int batIdCheck);


};
