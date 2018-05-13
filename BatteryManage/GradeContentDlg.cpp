// GradeContentDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "GradeContentDlg.h"
#include "afxdialogex.h"
#include "WorkStateStr.h"


// CGradeContentDlg 对话框

IMPLEMENT_DYNAMIC(CGradeContentDlg, CDialog)

CGradeContentDlg::CGradeContentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGradeContentDlg::IDD, pParent)
{

}

CGradeContentDlg::CGradeContentDlg(CWnd* pParent, CFileStepData &fileStepData)
:CDialog(CGradeContentDlg::IDD, pParent)
{
	openSelIdx = -1;
	capSelIdx = -1;

	this->fileStepData = fileStepData;
}

CGradeContentDlg::~CGradeContentDlg()
{
}

void CGradeContentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FILEPATH_STATIC, filePathStatic);
	
}


BEGIN_MESSAGE_MAP(CGradeContentDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CGradeContentDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_OPEN_RADIO, &CGradeContentDlg::OnBnClickedOpenRadio)
	ON_BN_CLICKED(IDC_CAP_RADIO, &CGradeContentDlg::OnBnClickedCapRadio)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CGradeContentDlg 消息处理程序


void CGradeContentDlg::OnBnClickedOk()
{
	//发送信息给BatCapGrade
	CString flag = L"";
	for (int idx = 0; idx < fileStepData.stepNum; ++idx)
	{
		if (stepList.GetCheck(idx))
		{
			flag += L"1";
		}
		else
		{
			flag += L"0";
		}
	}
	::SendNotifyMessage(theApp.capacityGradingDlg->m_hWnd, WM_UPDATE_BAT_CAP_GRID_MSG, WPARAM(flag.AllocSysString()), NULL);

	MessageBox(_T("分容条件设置成功!"));
	CDialog::OnOK();
}

void CGradeContentDlg::InitStepListBox()
{
	stepList.SubclassDlgItem(IDC_STEP_LIST, this);
	stepList.SetCheckStyle(BS_AUTOCHECKBOX);

	CString str, str2;
	CString astr, tstr, uvstr, ecstr, workDesStr;


	for (int idx = 0; idx < fileStepData.stepNum; ++idx)
	{
		str = L"";
		workDesStr = L"";
		WorkProcInfo workProcInfo = fileStepData.workProcInfos[idx];
		str2.Format(_T("%d"), idx+1);
		if (workProcInfo.workStepName == CA_WORKNAME_STR)
		{
			astr.Format(_T("%d"), workProcInfo.current);
			tstr.Format(_T("%d"), workProcInfo.workTime);
			uvstr.Format(_T("%d"), workProcInfo.maxVolt);

			str += CA_WORKNAME_CSTR + L"  CI: " + astr + L"  T: " + tstr + L"min  UV: " + uvstr + L"mV\r\n";
		}
		else if (workProcInfo.workStepName == CACV_WORKNAME_STR)
		{
			astr.Format(_T("%d"), workProcInfo.current);
			tstr.Format(_T("%d"), workProcInfo.workTime);
			uvstr.Format(_T("%d"), workProcInfo.maxVolt);
			ecstr.Format(_T("%d"), workProcInfo.endCurrent);

			str += CACV_WORKNAME_CSTR + L"  CI: " + astr + L"  T: " + tstr + L"min  CV: "
				+ uvstr + L"mV   EC: " + ecstr + L"mA\r\n";
		}
		else if (workProcInfo.workStepName == CADIS_WORKNAME_STR)
		{
			capSelIdx = idx;
			astr.Format(_T("%d"), workProcInfo.current);
			tstr.Format(_T("%d"), workProcInfo.workTime);
			uvstr.Format(_T("%d"), workProcInfo.minVolt);

			str += CADIS_WORKNAME_CSTR + L"  CI: " + astr + L"  T: " + tstr + L"min  DV: "
				+ uvstr + L"mV\r\n";
			str2 = L"&   " + str2 + L" : (1) ";
		}
		else if (workProcInfo.workStepName == LAY_WORKNAME_STR)
		{
			tstr.Format(_T("%d"), workProcInfo.workTime);

			str += LAY_WORKNAME_CSTR + L"  T: " + tstr + L"min\r\n";
		}
		else if (workProcInfo.workStepName == END_STR)
		{
			str += END_CSTR + L"\r\n\r\n";
		}
		workDesStr += str;
		
		if (idx == 0){
			str2 = L"*   " + str2 + L" : (1) " + workDesStr;
			openSelIdx = idx;
		}
		else if (str2[0] != '&')
		{
			str2 = str2 = L"     " + str2 + L" : (1) " + workDesStr;
		}
		else 
		{
			str2 = str2 + workDesStr;
		}
		stepList.AddString(str2);
	}

	if (capSelIdx >= 0)
	{
		stepList.SetCheck(capSelIdx, TRUE);
	}

}



BOOL CGradeContentDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitStatic();
	InitRatios();
	InitStepListBox();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CGradeContentDlg::InitStatic()
{
	filePathStatic.SetWindowTextW(fileStepData.filePath);
}

void CGradeContentDlg::InitRatios()
{
	((CButton *)this->GetDlgItem(IDC_OPEN_RADIO))->SetCheck(FALSE);
	((CButton *)this->GetDlgItem(IDC_CAP_RADIO))->SetCheck(TRUE);
}


void CGradeContentDlg::OnBnClickedOpenRadio()
{
	int check = ((CButton *)this->GetDlgItem(IDC_OPEN_RADIO))->GetCheck();

	((CButton *)this->GetDlgItem(IDC_OPEN_RADIO))->SetCheck(check);
	((CButton *)this->GetDlgItem(IDC_CAP_RADIO))->SetCheck(!check);

	if (check && openSelIdx >= 0)
	{
		for (int idx = 0; idx < fileStepData.stepNum; ++idx)
		{
			stepList.SetCheck(idx, FALSE);
		}
		stepList.SetCheck(openSelIdx, TRUE);
	}
}


void CGradeContentDlg::OnBnClickedCapRadio()
{
	int check = ((CButton *)this->GetDlgItem(IDC_CAP_RADIO))->GetCheck();
	

	((CButton *)this->GetDlgItem(IDC_CAP_RADIO))->SetCheck(check);
	((CButton *)this->GetDlgItem(IDC_OPEN_RADIO))->SetCheck(!check);

	if (check && capSelIdx >= 0)
	{
		for (int idx = 0; idx < fileStepData.stepNum; ++idx)
		{
			stepList.SetCheck(idx, FALSE);
		}
		stepList.SetCheck(capSelIdx, TRUE);
	}
}


void CGradeContentDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (this->m_hWnd)
	{
		audoAdaptHelper.ReSize(this->m_hWnd);
	}
	// TODO:  在此处添加消息处理程序代码
}
