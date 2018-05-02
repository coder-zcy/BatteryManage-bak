// SW_CopyParameterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "SW_CopyParameterDlg.h"
#include "afxdialogex.h"

#include "LowerCabs.h"

#define SW_CP_MAXNUM 20
// CSW_CopyParameterDlg 对话框

IMPLEMENT_DYNAMIC(CSW_CopyParameterDlg, CDialog)

CSW_CopyParameterDlg::CSW_CopyParameterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSW_CopyParameterDlg::IDD, pParent)
{

}

CSW_CopyParameterDlg::~CSW_CopyParameterDlg()
{
}

void CSW_CopyParameterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SW_CP_LISTBOX, m_ctCheckList);
	DDX_Control(pDX, IDC_SW_FULLCHECK, BtnFullCheck);
	DDX_Control(pDX, IDC_SW_CANCEL_FULLCHECK, BtnDelFullCheck);
	DDX_Control(pDX, IDC_SW_CP_LISTBOX, m_ctCheckList);
}

BOOL CSW_CopyParameterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_ctCheckList.ResetContent();
	//   m_ctlCheckList.SetCheckStyle( BS_3STATE );
	for (int i = 0; i < SW_CP_MAXNUM; ++i)
	{
		CString cstr;
		cstr.Format(_T("%d"), i+1);
		m_ctCheckList.SetCheckStyle(BS_AUTO3STATE);
		m_ctCheckList.AddString(cstr);

		m_ctCheckList.SetCheck(i, cabSelStr[i] == '1');
	}

	return TRUE;
}

BEGIN_MESSAGE_MAP(CSW_CopyParameterDlg, CDialog)
	ON_BN_CLICKED(IDC_SW_FULLCHECK, &CSW_CopyParameterDlg::OnBnClickedSwFullcheck)
	ON_BN_CLICKED(IDC_SW_CANCEL_FULLCHECK, &CSW_CopyParameterDlg::OnBnClickedSwCancelFullcheck)
	ON_BN_CLICKED(IDOK, &CSW_CopyParameterDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSW_CopyParameterDlg 消息处理程序


void CSW_CopyParameterDlg::OnBnClickedSwFullcheck()
{
	// TODO:  在此添加控件通知处理程序代码
	for (int i = 0; i < SW_CP_MAXNUM; ++i)
	{
		m_ctCheckList.SetCheck(i, 1);
	}

}


void CSW_CopyParameterDlg::OnBnClickedSwCancelFullcheck()
{
	// TODO:  在此添加控件通知处理程序代码
	for (int i = 0; i < SW_CP_MAXNUM; ++i)
	{
		m_ctCheckList.SetCheck(i, 0);
	}
}


void CSW_CopyParameterDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CString checkResult = theApp.startWorkDlg->CheckGrid();
	if (checkResult != L"")
	{
		AfxMessageBox(checkResult);
		return;
	}

	if (MessageBox(_T("确定要拷贝工序么"), _T("提示"), MB_OKCANCEL | MB_ICONWARNING) == IDOK)
	{
		CString stepConfigPath;
		CString stepPath;
		wchar_t str[MAX_PATH_LENGTH];
		BOOL flag = true;
		CString workProcVal;
		CString modelVal;
		for (int idx = 0; idx < MAX_CAB_NUM; ++idx)
		{
			if (!m_ctCheckList.GetCheck(idx))
			{
				continue;
			}
			// 获取路径
			stepConfigPath = CBatteryUtils::GetConfigPath(_T("\\config\\step\\")
				+ cabIdsCstr[idx] + _T("\\preStepPath.ini"));
			GetPrivateProfileString(_T("stepFilePath"),
				_T("path"), _T("error"), str, MAX_PATH_LENGTH, stepConfigPath);
			stepPath = str;

			if (stepPath == _T("error"))
			{
				flag = FALSE;
				break;
			}
			ofstream out(stepPath);
			if (out.is_open())
			{
				int nRow = theApp.startWorkDlg->m_GridCtrl.GetRowCount();
				int nCol = theApp.startWorkDlg->m_GridCtrl.GetColumnCount();

				CString str;
				GV_ITEM Item;
				Item.mask = GVIF_TEXT | GVIF_FORMAT;

				theApp.startWorkDlg->workProcEdit.GetWindowTextW(workProcVal);
				theApp.startWorkDlg->modelEdit.GetWindowTextW(modelVal);

				out << CT2A(workProcVal) << std::endl;
				out << CT2A(modelVal) << std::endl;
				out << nRow << std::endl;
				out << nCol << std::endl;
				for (int i = 1; i < nRow; ++i)
				{
					for (int j = 1; j < nCol - 1; ++j)
					{
						str = theApp.startWorkDlg->m_GridCtrl.GetItemText(i, j);
						//http://stackoverflow.com/questions/5550838/how-to-convert-cstring-to-ofstream
						str = str == L"" ? DEFAULT_PATA_STR : str;
						out << CT2A(str) << " ";
					}
					str = theApp.startWorkDlg->m_GridCtrl.GetItemText(i, nCol - 1);
					str = str == L"" ? DEFAULT_PATA_STR : str;
					out << CT2A(str) << endl;
				}
				out.close();
			}
			// 清空内存参数,重新加载
			//delete theApp.startWorkDlg->workProcs[idx];
			//theApp.startWorkDlg->workProcs[idx] = NULL;
			delete workProcs[idx];
			workProcs[idx] = NULL;
		}

		AfxMessageBox(L"工序拷贝完成!");
	}
	CDialog::OnOK();
}
