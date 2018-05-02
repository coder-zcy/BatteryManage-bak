#pragma once
#include "BatteryMainView.h"

// CBatteryCheckFrame 框架

class CBatteryMainFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CBatteryMainFrame)
protected:
	CBatteryMainFrame();           // 动态创建所使用的受保护的构造函数
	virtual ~CBatteryMainFrame();

protected:
	DECLARE_MESSAGE_MAP()
public:
	BOOL paintFlag;
	
	CBatteryMainView *batteryCheckView;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void ActivateFrame(int nCmdShow = -1);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnClose();
	afx_msg void OnClipboardUpdate();
	afx_msg void OnSizeClipboard(CWnd* pClipAppWnd, HGLOBAL hRect);
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnInitMenu(CMenu* pMenu);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	LRESULT OnCloseDateFileView(WPARAM wParam, LPARAM lParam);
};


