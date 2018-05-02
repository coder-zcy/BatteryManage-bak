#pragma once
#include "afxwin.h"
#include "FileStepData.h"
#include "AutoAdapt.h"

// CGradeContentDlg �Ի���

#define WM_UPDATE_BAT_CAP_GRID_MSG	WM_USER+0x01006		//	���·��ݴ��ڵ���Ϣ

class CGradeContentDlg : public CDialog
{
	DECLARE_DYNAMIC(CGradeContentDlg)

public:
	CGradeContentDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CGradeContentDlg(CWnd* pParent, CFileStepData &fileStepData);
	virtual ~CGradeContentDlg();

// �Ի�������
	enum { IDD = IDD_GRADE_CONTENT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CStatic filePathStatic;
	CCheckListBox stepList;
	int openSelIdx;
	int capSelIdx;
	
	CFileStepData fileStepData;
	CAutoAdapt audoAdaptHelper;

	void InitStepListBox();	//��ʼ��WorkStepInfo-ListBox
	virtual BOOL OnInitDialog();
	void InitStatic();
	void InitRatios();
	afx_msg void OnBnClickedOpenRadio();
	afx_msg void OnBnClickedCapRadio();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
