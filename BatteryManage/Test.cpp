// Test.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "Test.h"
#include "afxdialogex.h"


// Test �Ի���

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


// Test ��Ϣ�������


void Test::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
}


void Test::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}
