#pragma once
#include "afxcmn.h"
#include "GridCtrl_src\GridCtrl.h"
#include "FileCabData.h"
#include "afxwin.h"


// CCompDlg 对话框

class CCompDlg : public CDialog
{
	DECLARE_DYNAMIC(CCompDlg)

public:
	CCompDlg(CWnd* pParent = NULL);   // 标准构造函数
	CCompDlg(CWnd* pParent, CFileCabData &fileCabData);
	virtual ~CCompDlg();

	// 对话框数据
	enum { IDD = IDD_COMP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//afx_msg LRESULT CCompDlg::OnGirdHScroll(WPARAM wParam, LPARAM lParam);
	
	//CListCtrl compList;
	virtual BOOL OnInitDialog();

	//CMSFlexGrid compGrid;
	CGridCtrl compGrid;

	int defColWidth;
	int defRowHeight;

	void InitGridContent();

	int FillGridContentByBatData(int colIdx, int workProcsLength, vector<WorkProcInfo> &workProcInfos, CString &str);

	void InitCombox();

	CFileCabData fileCabData;
	
	CComboBox attrCom;
	CComboBox stepCom;
	CComboBox datatimeCom;
	afx_msg void OnCbnSelchangeStepCombo();
	afx_msg void OnCbnSelchangeDatetimeCombo();

	vector<int> scrollPoss;
};