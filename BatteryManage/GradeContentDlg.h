#pragma once
#include "afxwin.h"
#include "FileStepData.h"
#include "AutoAdapt.h"

// CGradeContentDlg 对话框

#define WM_UPDATE_BAT_CAP_GRID_MSG	WM_USER+0x01006		//	更新分容窗口的消息

class CGradeContentDlg : public CDialog
{
	DECLARE_DYNAMIC(CGradeContentDlg)

public:
	CGradeContentDlg(CWnd* pParent = NULL);   // 标准构造函数
	CGradeContentDlg(CWnd* pParent, CFileStepData &fileStepData);
	virtual ~CGradeContentDlg();

// 对话框数据
	enum { IDD = IDD_GRADE_CONTENT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CStatic filePathStatic;
	CCheckListBox stepList;
	int openSelIdx;
	int capSelIdx;
	
	CFileStepData fileStepData;
	CAutoAdapt audoAdaptHelper;

	void InitStepListBox();	//初始化WorkStepInfo-ListBox
	virtual BOOL OnInitDialog();
	void InitStatic();
	void InitRatios();
	afx_msg void OnBnClickedOpenRadio();
	afx_msg void OnBnClickedCapRadio();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
