// SearchEngineCreater.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "SearchEngineCreater.h"
#include "afxdialogex.h"


// CSearchEngineCreater 对话框

IMPLEMENT_DYNAMIC(CSearchEngineCreater, CDialog)

CSearchEngineCreater::CSearchEngineCreater(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchEngineCreater::IDD, pParent)
{

}

CSearchEngineCreater::~CSearchEngineCreater()
{
}

void CSearchEngineCreater::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSearchEngineCreater, CDialog)
END_MESSAGE_MAP()


// CSearchEngineCreater 消息处理程序
