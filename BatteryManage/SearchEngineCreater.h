#pragma once


// CSearchEngineCreater 对话框

class CSearchEngineCreater : public CDialog
{
	DECLARE_DYNAMIC(CSearchEngineCreater)

public:
	CSearchEngineCreater(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSearchEngineCreater();

// 对话框数据
	enum { IDD = IDD_SEARCH_ENGINE_CREATER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
