// CurveDataDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "CurveDataDlg.h"
#include "afxdialogex.h"


// CCurveDataDlg �Ի���

IMPLEMENT_DYNAMIC(CCurveDataDlg, CDialog)

CCurveDataDlg::CCurveDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCurveDataDlg::IDD, pParent)
{

}

CCurveDataDlg::~CCurveDataDlg()
{
}

void CCurveDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCurveDataDlg, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CCurveDataDlg ��Ϣ�������


void CCurveDataDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
}
