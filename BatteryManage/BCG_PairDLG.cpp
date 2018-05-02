// BCG_PairDLG.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "BCG_PairDLG.h"
#include "afxdialogex.h"


// CBCG_PairDLG �Ի���

IMPLEMENT_DYNAMIC(CBCG_PairDLG, CDialog)

CBCG_PairDLG::CBCG_PairDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CBCG_PairDLG::IDD, pParent)
{

}

CBCG_PairDLG::~CBCG_PairDLG()
{
}

void CBCG_PairDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BCG_PDlg_COMBO1, pairBatteryNum);
	DDX_Control(pDX, IDC_BCG_PDlg_COMBO2, MainSortPara);
}


BEGIN_MESSAGE_MAP(CBCG_PairDLG, CDialog)
END_MESSAGE_MAP()


// CBCG_PairDLG ��Ϣ�������

BOOL CBCG_PairDLG::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	for (int i = 0; i < 999; ++i){
		CString str;
		str.Format(_T("%d"), i + 2);
		pairBatteryNum.InsertString(i, str);
	}
	std::vector<CString> tmp;
	CString str;
	str.Format(_T("����"));
	tmp.push_back(str);

	str.Format(_T("ʱ��")); tmp.push_back(str);
	str.Format(_T("��·��ѹ")); tmp.push_back(str);
	str.Format(_T("ƽ����ѹ"));	tmp.push_back(str);
	str.Format(_T("��������1")); tmp.push_back(str);
	str.Format(_T("��������2")); tmp.push_back(str);
	str.Format(_T("��������3")); tmp.push_back(str);
	str.Format(_T("��������4")); tmp.push_back(str);
	str.Format(_T("��������5")); tmp.push_back(str);
	str.Format(_T("����ѹ")); tmp.push_back(str);
	str.Format(_T("����")); tmp.push_back(str);
	str.Format(_T("��ֹ����")); tmp.push_back(str);
	str.Format(_T("��������")); tmp.push_back(str);
	str.Format(_T("����ʱ��")); tmp.push_back(str);

	for (int i = 0; i < tmp.size(); ++i)
	{
		MainSortPara.InsertString(i, tmp[i]);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
