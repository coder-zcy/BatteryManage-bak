// SW_SendDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "SW_SendDlg.h"
#include "afxdialogex.h"

#include "LowerCabs.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


#define SW_SEND_MAXNUM 20
// CSW_SendDlg 对话框

IMPLEMENT_DYNAMIC(CSW_SendDlg, CDialog)

CSW_SendDlg::CSW_SendDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSW_SendDlg::IDD, pParent)
{

}

CSW_SendDlg::~CSW_SendDlg()
{

}

void CSW_SendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SW_SEND_LISTCHECKBOX, m_ctCheckList);
	DDX_Control(pDX, IDC_SW_SEND_FULLCHECK, BtnFullCheck);
	DDX_Control(pDX, IDC_SW_SEND_CANFULLCHECK, BtnCanFullCheck);
}

BOOL CSW_SendDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_ctCheckList.ResetContent();
	//   m_ctlCheckList.SetCheckStyle( BS_3STATE );
	for (int i = 0; i < SW_SEND_MAXNUM; ++i)
	{
		CString cstr;
		cstr.Format(_T("%d"), i+1);
		m_ctCheckList.SetCheckStyle(BS_AUTO3STATE);
		m_ctCheckList.AddString(cstr);
		m_ctCheckList.SetCheck(i, 0);
	}
	curCabId = curCabId == 0 ? defCabId : curCabId;
	m_ctCheckList.SetCheck(curCabId - 1, 1);
	return TRUE;
}

BEGIN_MESSAGE_MAP(CSW_SendDlg, CDialog)
	ON_BN_CLICKED(IDC_SW_SEND_FULLCHECK, &CSW_SendDlg::OnBnClickedSwSendFullcheck)
	ON_BN_CLICKED(IDC_SW_SEND_CANFULLCHECK, &CSW_SendDlg::OnBnClickedSwSendCanfullcheck)
	ON_BN_CLICKED(IDOK, &CSW_SendDlg::OnBnClickedOk)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CSW_SendDlg 消息处理程序


void CSW_SendDlg::OnBnClickedSwSendFullcheck()
{
	// TODO:  在此添加控件通知处理程序代码
	for (int i = 0; i < SW_SEND_MAXNUM; ++i)
	{
		m_ctCheckList.SetCheck(i, 1);
	}
}


void CSW_SendDlg::OnBnClickedSwSendCanfullcheck()
{
	// TODO:  在此添加控件通知处理程序代码
	for (int i = 0; i < SW_SEND_MAXNUM; ++i)
	{
		m_ctCheckList.SetCheck(i, 0);
	}
}


/*
(1) 分别获取所选中机柜的所需要保存工步的文件路径
(2)	将工步文件根据工步路径进行保存
*/
void CSW_SendDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CString checkResult = theApp.startWorkDlg->CheckGrid();

	if (checkResult != L"")
	{
		AfxMessageBox(checkResult);
		return;
	}

	if (MessageBox(_T("确定要发送工步么"), _T("提示"), MB_OKCANCEL | MB_ICONWARNING) == IDOK)
	{
		CString stepConfigPath;
		CString stepPath;
		wchar_t str[MAX_PATH_LENGTH];
		BOOL flag = true;
		CString workProcVal;
		CString modelVal;
		for (int idx = 0; idx < SW_SEND_MAXNUM; ++idx)
		{
			SendStepFlags[idx] = FALSE;

			if (!m_ctCheckList.GetCheck(idx))
			{
				//if(!PreSendStepFlags[idx])
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
				//int nRow = theApp.startWorkDlg->m_GridCtrl.GetRowCount();
				//int nCol = theApp.startWorkDlg->m_GridCtrl.GetColumnCount();
				//CWorkProc* workProc = theApp.startWorkDlg->workProcs[idx];
				CWorkProc* workProc = workProcs[idx];
				int nRow = workProc->stepNum + 1;
				int nCol = STEP_COL_NUM;
				

				CString str;
				GV_ITEM Item;
				Item.mask = GVIF_TEXT | GVIF_FORMAT;

				//theApp.startWorkDlg->workProcEdit.GetWindowTextW(workProcVal);
				//theApp.startWorkDlg->modelEdit.GetWindowTextW(modelVal);

				out << CT2A(workProc->workProcName) << std::endl;
				out << CT2A(workProc->model) << std::endl;
				out << nRow << std::endl;
				out << nCol << std::endl;
				for (int i = 1; i < nRow; ++i)
				{
					//for (int j = 1; j < nCol - 1; ++j)
					//{
					//	str = theApp.startWorkDlg->m_GridCtrl.GetItemText(i, j);
					//	//http://stackoverflow.com/questions/5550838/how-to-convert-cstring-to-ofstream
					//	str = str == L"" ? DEFAULT_PATA_STR : str;
					//	out << CT2A(str) << " ";
					//}
					//str = theApp.startWorkDlg->m_GridCtrl.GetItemText(i, nCol - 1);
					//str = str == L"" ? DEFAULT_PATA_STR : str;
					//out << CT2A(str) << endl;
					str = workProc->workSteps[i - 1].workStepName;
					str = str == L"" ? DEFAULT_PATA_STR : str;
					out << CT2A(str) << " ";

					str = workProc->workSteps[i - 1].workTime;
					str = str == L"" ? DEFAULT_PATA_STR : str;
					out << CT2A(str) << " ";

					str = workProc->workSteps[i - 1].current;
					str = str == L"" ? DEFAULT_PATA_STR : str;
					out << CT2A(str) << " ";

					str = workProc->workSteps[i - 1].maxVolt;
					str = str == L"" ? DEFAULT_PATA_STR : str;
					out << CT2A(str) << " ";

					str = workProc->workSteps[i - 1].minVolt;
					str = str == L"" ? DEFAULT_PATA_STR : str;
					out << CT2A(str) << " ";

					str = workProc->workSteps[i - 1].deltaVolt;
					str = str == L"" ? DEFAULT_PATA_STR : str;
					out << CT2A(str) << " ";

					str = workProc->workSteps[i - 1].endCurrent;
					str = str == L"" ? DEFAULT_PATA_STR : str;
					out << CT2A(str) << " ";

					str = workProc->workSteps[i - 1].endCapacity;
					str = str == L"" ? DEFAULT_PATA_STR : str;
					out << CT2A(str) << endl;

					workProc->workSteps[i - 1].stepId = i;
				}
				out.close();
			}

			//	已向某设备发送工步,并且该设备已经被选中,则表示可以进行联机,但联机的目标是被选中且被发送工步的机柜
			SendStepFlags[idx] = TRUE;
			PreSendStepFlags[idx] = TRUE;

			if (cabSelStr[idx] == '1')
			{
				CanConnFlag = TRUE;
				IntteruptSendFlag = TRUE;
			}
		}
		if (flag)
		{
			MessageBox(_T("发送工步成功!"));
			// 获得父窗口的句柄  
			HWND hWnd = this->GetParent()->GetSafeHwnd();

			// 向父窗口发送消息  
			if (hWnd == NULL) return (void)MessageBox(_T("获得父窗口句柄失败！"));
			CString flag = L"1";
			::SendNotifyMessage(hWnd, WM_CLOSE_START_DLG, WPARAM(&flag), NULL);
		}
		else
		{
			MessageBox(_T("发送工步失败,请检查相关的工步配置文件!"));
		}
	}
	CDialog::OnOK();
}


void CSW_SendDlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CDialog::OnClose();

}
