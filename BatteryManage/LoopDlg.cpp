// LoopDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "LoopDlg.h"
#include "afxdialogex.h"


// CLoopDlg �Ի���

IMPLEMENT_DYNAMIC(CLoopDlg, CDialog)

CLoopDlg::CLoopDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoopDlg::IDD, pParent)
{

}

CLoopDlg::~CLoopDlg()
{
}

void CLoopDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLoopDlg, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CLoopDlg ��Ϣ�������


void CLoopDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
}
