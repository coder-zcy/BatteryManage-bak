#pragma once
#include "afxcmn.h"
#include "DeviceSetInfoDlg.h"
#include "PbatterysDlg.h"
#include "TbatterysDlg.h"
#include "FbatterysDlg.h"
#include "EbatterysDlg.h"

#include <iostream>
#include <vector>
#include "afxwin.h"

using namespace std;

#define SET_INFO_IDX	0
#define PRE_DATA_IDX	1
#define SHOW_STYLE_IDX	2
#define LEFT_MOUSE_IDX  3
#define SPEC_CTL_IDX    4


// CBatteryCheckView ������ͼ

class CBatteryCheckView : public CFormView
{
	DECLARE_DYNCREATE(CBatteryCheckView)

public:
	CBatteryCheckView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CBatteryCheckView();

public:
	enum { IDD = IDD_BATTERY_CHECK_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg void OnClose();
	
public:
	CDeviceSetInfoDlg *deviceSetInfoDlg;
	//afx_msg void OnStnClickedInfoSetStatic();

	//afx_msg void OnNMClickSetInfoStatic(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnNMClickPreDataStatic(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnNMClickShowStyleStatic(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnNMClickLeftMouseStatic(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnNMClickSpecCtlStatic(NMHDR *pNMHDR, LRESULT *pResult);

	//CLinkCtrl preDataStatic;
	//CLinkCtrl setInfoStatic;
	//CLinkCtrl showStyleStatic;
	//CLinkCtrl leftMouseStatic;
	//CLinkCtrl specCtlStatic;

	CRect setRect;
	CRect preRect;
	CRect showRect;
	CRect leftRect;
	CRect specRect;

	vector<CString> linkNames;
	vector<CString> hoverLinkNames;

	vector<CLinkCtrl *> links;
	vector<CRect> rects;

	//afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//void OnInitialUpdate();

	// ������
public:
	CPbatterysDlg  *pbatterysDlg;	// ͼ�η�ʽDlg
	CTbatterysDlg *tbatterysDlg;	// ���ʽDlg
	CFbatterysDlg *fbatterysDlg;	// �ۺϷ�ʽDlg
	CEbatterysDlg *ebatterysDlg;	// �쳣Dlg

	CStatic batterysPanePic;

	afx_msg void OnSize(UINT nType, int cx, int cy);
	//afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	//afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	//afx_msg void OnNMRClickShowStyleStatic(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnNMRClickLeftMouseStatic(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnNMRClickSpecCtlStatic(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnBatterySelect();
	//afx_msg void OnMove(int x, int y);
	//afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	CLinkCtrl setInfoStatic;
	CLinkCtrl preDataStatic;
	CLinkCtrl showStyleStatic;
	CLinkCtrl leftMouseStatic;
	CLinkCtrl specCtlStatic;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual void OnInitialUpdate();
};


