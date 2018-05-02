#pragma once
#include <vector>
#include "afxwin.h"
using namespace std;

// CBCG_DrawingCircleDlg 对话框

class battery_info
{
public:
	CRect select_area;
	CRect circle_area;
	bool isSel;
public:
	battery_info(){
		isSel = false;
	}
};

class CBCG_DrawingCircleDlg : public CDialog
{
	DECLARE_DYNAMIC(CBCG_DrawingCircleDlg)

public:
	CBCG_DrawingCircleDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBCG_DrawingCircleDlg();
	virtual BOOL OnInitDialog();

	void DrawCycle();

	// 对话框数据
	enum { IDD = IDD_BCG_DrawingCircleDlg };
public:
	vector<vector<battery_info>> draw_matrix;
	//保存之前选中的目标坐标
	int oldsel_row;
	int oldsel_col;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	void LightPane(int *batLevelStats, int batCount, int gradeId);
	CStatic seqStatic1;
	CStatic seqStatic2;
	CStatic seqStatic3;
	CStatic seqStatic4;
	CStatic seqStatic5;
	CStatic seqStatic6;
	CStatic seqStatic7;
	CStatic seqStatic8;
	CStatic seqStatic9;
	CStatic seqStatic10;
	CStatic seqStatic11;
	CStatic seqStatic12;
	CStatic seqStatic13;
	CStatic seqStatic14;
	CStatic seqStatic15;
	CStatic seqStatic16;

	vector<CStatic*> seqStatics;

	const COLORREF selLightColor = RGB(255, 255, 255);
	const COLORREF defLightColor = RGB(255, 0, 255);
};
