// SearchEngine.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "SearchEngine.h"
#include "afxdialogex.h"


// CSearchEngine �Ի���

IMPLEMENT_DYNAMIC(CSearchEngine, CDialog)

CSearchEngine::CSearchEngine(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchEngine::IDD, pParent)
{

}

CSearchEngine::~CSearchEngine()
{
}

void CSearchEngine::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSearchEngine, CDialog)
END_MESSAGE_MAP()


// CSearchEngine ��Ϣ�������
