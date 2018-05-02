#pragma once
#include "DataFileView.h"

// CDataFileFrame 框架

class CDataFileFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CDataFileFrame)
public:
	CDataFileFrame();           // 动态创建所使用的受保护的构造函数
	virtual ~CDataFileFrame();

public:
	CDataFileView *dataFileView;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	virtual void ActivateFrame(int nCmdShow = -1);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
	afx_msg void OnClose();
	virtual void PostNcDestroy();
	afx_msg void OnDestroy();
	afx_msg void OnDestroyClipboard();
	afx_msg void OnNcDestroy();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
};


