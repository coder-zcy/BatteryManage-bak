#pragma once


// CSearchEngine 对话框

class CSearchEngine : public CDialog
{
	DECLARE_DYNAMIC(CSearchEngine)

public:
	CSearchEngine(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSearchEngine();

// 对话框数据
	enum { IDD = IDD_SEARCH_ENGINE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
