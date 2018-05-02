// Test.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "Test.h"
#include "afxdialogex.h"


// Test 对话框

IMPLEMENT_DYNAMIC(Test, CDialog)

Test::Test(CWnd* pParent /*=NULL*/)
	: CDialog(Test::IDD, pParent)
{

}

Test::~Test()
{
}

void Test::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Test, CDialog)
	ON_BN_CLICKED(IDOK, &Test::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Test::OnBnClickedCancel)
END_MESSAGE_MAP()


// Test 消息处理程序


void Test::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialog::OnOK();
}


void Test::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialog::OnCancel();
}
