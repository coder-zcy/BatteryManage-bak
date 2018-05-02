// BCG_PairDLG.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "BCG_PairDLG.h"
#include "afxdialogex.h"


// CBCG_PairDLG 对话框

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


// CBCG_PairDLG 消息处理程序

BOOL CBCG_PairDLG::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	for (int i = 0; i < 999; ++i){
		CString str;
		str.Format(_T("%d"), i + 2);
		pairBatteryNum.InsertString(i, str);
	}
	std::vector<CString> tmp;
	CString str;
	str.Format(_T("容量"));
	tmp.push_back(str);

	str.Format(_T("时间")); tmp.push_back(str);
	str.Format(_T("开路电压")); tmp.push_back(str);
	str.Format(_T("平均电压"));	tmp.push_back(str);
	str.Format(_T("定点数据1")); tmp.push_back(str);
	str.Format(_T("定点数据2")); tmp.push_back(str);
	str.Format(_T("定点数据3")); tmp.push_back(str);
	str.Format(_T("定点数据4")); tmp.push_back(str);
	str.Format(_T("定点数据5")); tmp.push_back(str);
	str.Format(_T("最后电压")); tmp.push_back(str);
	str.Format(_T("内阻")); tmp.push_back(str);
	str.Format(_T("终止电流")); tmp.push_back(str);
	str.Format(_T("恒流比例")); tmp.push_back(str);
	str.Format(_T("恒流时间")); tmp.push_back(str);

	for (int i = 0; i < tmp.size(); ++i)
	{
		MainSortPara.InsertString(i, tmp[i]);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
