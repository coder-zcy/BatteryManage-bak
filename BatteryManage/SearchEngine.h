#pragma once


// CSearchEngine �Ի���

class CSearchEngine : public CDialog
{
	DECLARE_DYNAMIC(CSearchEngine)

public:
	CSearchEngine(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSearchEngine();

// �Ի�������
	enum { IDD = IDD_SEARCH_ENGINE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
