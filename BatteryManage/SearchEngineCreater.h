#pragma once


// CSearchEngineCreater �Ի���

class CSearchEngineCreater : public CDialog
{
	DECLARE_DYNAMIC(CSearchEngineCreater)

public:
	CSearchEngineCreater(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSearchEngineCreater();

// �Ի�������
	enum { IDD = IDD_SEARCH_ENGINE_CREATER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
