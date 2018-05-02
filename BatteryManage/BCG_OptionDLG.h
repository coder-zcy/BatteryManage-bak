#pragma once
#include"GridCtrl_src\GridCtrl.h"
#include <vector>
#include <map>
#include "afxwin.h"
#include "CapGradeConf.h"
#include "FileStepData.h"

// CBCG_OptionDLG 对话框

#define WM_CAL_GRADE_MSG WM_USER+0x01008		//	计算等级

class CBCG_OptionDLG : public CDialog
{
	DECLARE_DYNAMIC(CBCG_OptionDLG)

public:
	CBCG_OptionDLG(CWnd* pParent, CFileStepData &fileStepData);// 标准构造函数
	virtual ~CBCG_OptionDLG();
	virtual BOOL OnInitDialog();

	void InitCondGrid();

	void reDrawGrid();
	void InitDlgAssembly();

// 对话框数据
	enum { IDD = IDD_BCG_OptionDlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CGridCtrl condGrid;
	CComboBox levelComb;
	CButton capCheck;
	CButton timeCheck;
	CButton openCheck;
	CButton avgCheck;
	CButton point1Check;
	CButton point2Check;
	CButton point3Check;
	CButton point4Check;
	CButton point5Check;
	CButton endCheck;
	CButton resistCheck;
	CButton sdCheck;
	CButton midCheck;
	std::vector<CString> record_col2idx;
	std::map<CString, bool> record_col2show;

	vector <CButton *> disChecks;
	CFileStepData fileStepData;

	vector<CButton *> cabChecks;

	void InitChecks();

private:
	int level;

public:
	afx_msg void OnCbnSelchangeBcgOdlgCombo2();
	afx_msg void OnBnClickedCapCheck();
	afx_msg void OnBnClickedTimeCheck();
	afx_msg void OnBnClickedOpenCheck();
	afx_msg void OnBnClickedAvgCheck();
	afx_msg void OnBnClickedPointCheck1();
	afx_msg void OnBnClickedPointCheck2();
	afx_msg void OnBnClickedPointCheck3();
	afx_msg void OnBnClickedPointCheck4();
	afx_msg void OnBnClickedPointCheck5();
	afx_msg void OnBnClickedEndCheck();
	afx_msg void OnBnClickedInnerCheck();
	afx_msg void OnBnClickedSdCheck();
	afx_msg void OnBnClickedMidCheck();
	CComboBox codeComb;
	afx_msg void OnBnClickedOk();
	CEdit remarksEdit;
	CEdit filenameEdit;
	afx_msg void OnBnClickedBcgBrowseBtn();
	afx_msg void OnBnClickedBcgSaveBtn();
	afx_msg void OnBnClickedBcgDelBtn();
	afx_msg void OnBnClickedBcgPointCheck1();
	afx_msg void OnBnClickedBcgPointCheck2();
	CButton cab1Check;
	CButton cab2Check;
	CButton cab3Check;
	CButton cab4Check;
	CButton cab5Check;
	CButton cab6Check;
	CButton cab7Check;
	CButton cab8Check;
	CButton cab9Check;
	CButton cab10Check;
	CButton cab11Check;
	CButton cab12Check;
	CButton cab13Check;
	CButton cab14Check;
	CButton cab15Check;
	CButton cab16Check;
	CButton cab17Check;
	CButton cab18Check;
	CButton cab19Check;
	CButton cab20Check;
	afx_msg void OnCbnSelchangeBcgCodeCombo();
	virtual BOOL DestroyWindow();

	// 主要针对GridCell中的修改
	afx_msg void OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult);
};
