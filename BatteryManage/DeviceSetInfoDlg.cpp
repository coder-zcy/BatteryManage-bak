// DeviceSetInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "DeviceSetInfoDlg.h"
#include "afxdialogex.h"
#include "CabUtils.h"


// CDeviceSetInfoDlg 对话框

IMPLEMENT_DYNAMIC(CDeviceSetInfoDlg, CDialog)

CDeviceSetInfoDlg::CDeviceSetInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeviceSetInfoDlg::IDD, pParent)
{

}

CDeviceSetInfoDlg::~CDeviceSetInfoDlg()
{
}

void CDeviceSetInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DEVICE_INFO_EDIT, deviceSetEdit);
}


BEGIN_MESSAGE_MAP(CDeviceSetInfoDlg, CDialog)
END_MESSAGE_MAP()


// CDeviceSetInfoDlg 消息处理程序


BOOL CDeviceSetInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	int cabId = curCabId;
	
	if (cabId == 0) 
		return FALSE;

	wchar_t str[MAX_PATH_LENGTH];
	CString cabIdStr;
	_itow_s(cabId, str, INT_LENGTH);
	cabIdStr = str;

	CString tmpPath = CBatteryUtils::GetConfigPath(_T("\\config\\step\\")
		+ cabIdStr + _T("\\preStepPath.ini"));
	GetPrivateProfileString(_T("stepFilePath"), _T("path"), _T("error"), str, MAX_PATH_LENGTH, tmpPath);

	InitSpecStepInfo(cabId,str);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CDeviceSetInfoDlg::InitSpecStepInfo(int cabId, CString stepFilePath)
{
	std::ifstream in(stepFilePath);

	if (in.is_open())
	{
		deviceSetEdit.SetWindowTextW(L"");

		string line;
		CString stepLineCstr, str;
		int nRow, nCol;
		// 文件第一行为工步名称
		// 第二行为型号
		//文件第三行为表格行数，第四行为表格列数
		
		getline(in, line);
		str = line.c_str();
		stepLineCstr = L"工序名称:" + str;
	
		getline(in, line);
		str = line.c_str();
		
		stepLineCstr += L"    设备名称:" + str + L"\r\n" + L"\r\n";

		getline(in, line);
		nRow = std::stoi(line);
		getline(in, line);
		nCol = std::stoi(line);


		for (int i = 1; i < nRow; ++i)
		{
			getline(in, line);
			int spaceidx = 0;

			//  如果stepName 有效 则继续，首先寻找StepName
			vector<string> stepInfos = StringUtils::SplitByStr(line, " ");
			if (stepInfos.size() == 0)
				continue;
			str.Format(_T("%d"), i);

			stepLineCstr += str;
			str = stepInfos[0].c_str();
			stepLineCstr += L": " + str;

		
			if (stepInfos.size() == STEP_INFO_LENGTH)
			{
				if (stepInfos[0] == "恒流恒压充电")
				{
					str = stepInfos[TIME_PARAID + 1].c_str();
					stepLineCstr += L", 时间: " + str;
					str = stepInfos[CURRENT_PARAID + 1].c_str();
					stepLineCstr += L"Min, 充电电流:" + str;
					str = stepInfos[MAX_VOLT_PARAID + 1].c_str();
					stepLineCstr += L"mA, 上限电压:" + str;	
					str = stepInfos[DELTA_VOLT_PARAID + 1].c_str();
					stepLineCstr += L"mV, △V:" + str;
					str = stepInfos[END_CURRENT_PARAID + 1].c_str();
					stepLineCstr += L"mV, 终止电流:" + str;
					str = stepInfos[END_CAPACITY_PARAID + 1].c_str();
					stepLineCstr += L"mA, 终止容量:" + str + L"mAh";
				}
				else if (stepInfos[0] == "恒流充电")
				{
					str = stepInfos[TIME_PARAID + 1].c_str();
					stepLineCstr += L", 时间: " + str;
					str = stepInfos[CURRENT_PARAID + 1].c_str();
					stepLineCstr += L"Min, 充电电流:" + str;
					str = stepInfos[MAX_VOLT_PARAID + 1].c_str();
					stepLineCstr += L"mA, 上限电压:" + str;
					str = stepInfos[DELTA_VOLT_PARAID + 1].c_str();
					stepLineCstr += L"mV, △V:" + str;
					str = stepInfos[END_CAPACITY_PARAID + 1].c_str();
					stepLineCstr += L"mV, 终止容量:" + str + L"mAh";
				}
				else if (stepInfos[0] == "恒流放电")
				{
					str = stepInfos[TIME_PARAID + 1].c_str();
					stepLineCstr += L", 时间: " + str;
					str = stepInfos[CURRENT_PARAID + 1].c_str();
					stepLineCstr += L"Min, 放电电流:" + str;
					str = stepInfos[MIN_VOLT_PARAID + 1].c_str();
					stepLineCstr += L"mA, 下限电压:" + str;
					str = stepInfos[END_CAPACITY_PARAID + 1].c_str();
					stepLineCstr += L"mV, 终止容量:" + str + L"mAh";
				}
				else if (stepInfos[0] == "循环")
				{
					str = stepInfos[START_STEP_PARAID + 1].c_str();
					stepLineCstr += L", 起始工步: " + str;
					str = stepInfos[END_STEP_PARAID + 1].c_str();
					stepLineCstr += L", 终止工步:" + str;
					str = stepInfos[LOOP_NUM_PARAID + 1].c_str();
					stepLineCstr += L", 循环次数:" + str;
				}
				else if (stepInfos[0] == "搁置")
				{
					str = stepInfos[TIME_PARAID + 1].c_str();
					stepLineCstr += L", 时间: " + str;
				}
			}
			stepLineCstr += L"\r\n\r\n";
		}
		stepLineCstr += L"\r\n";
		str.Format(_T("%d"), cabInfos[cabId - 1].vdisVal);
		stepLineCstr += L"曲线筛选条件：    电压差: " + str + L" mV；";

		str.Format(_T("%d"), cabInfos[cabId - 1].adisVal);
		stepLineCstr += L"    电流差: " + str + L" mA；";

		str.Format(_T("%d"), cabInfos[cabId - 1].timeDisVal);
		stepLineCstr += L"    时间差: " + str + L" Min\r\n\r\n";

		stepLineCstr += GetOtherInfo(cabId);

		deviceSetEdit.SetWindowTextW(stepLineCstr);
		return;
	}
}

CString CDeviceSetInfoDlg::GetOtherInfo(int cabId)
{
	CString cabIdStr = cabIdsCstr[cabId - 1];
	CString result = L"";
	CString str;
	CString otherInitPath = CBatteryUtils::GetConfigPath(_T("\\config\\step\\") + cabIdStr + _T("\\other.ini"));
	
	int warnCapVal = GetPrivateProfileInt(_T("other"), _T("warnCap"), 0, otherInitPath);
	int vseperateVal = GetPrivateProfileInt(_T("other"), _T("vseperate"), 0, otherInitPath);
	int stopStepNumVal = GetPrivateProfileInt(_T("other"), _T("stopStepNum"), 0, otherInitPath);
	
	int vpointVal = GetPrivateProfileInt(_T("other"), _T("vpoint"), 0, otherInitPath);

	int tpointVal = GetPrivateProfileInt(_T("other"), _T("tpoint"), 0, otherInitPath);

	int featureVal1 = GetPrivateProfileInt(_T("other"), _T("feature1"), 0, otherInitPath);
	int featureVal2 = GetPrivateProfileInt(_T("other"), _T("feature2"), 0, otherInitPath);
	int featureVal3 = GetPrivateProfileInt(_T("other"), _T("feature3"), 0, otherInitPath);
	int featureVal4 = GetPrivateProfileInt(_T("other"), _T("feature4"), 0, otherInitPath);
	int featureVal5 = GetPrivateProfileInt(_T("other"), _T("feature5"), 0, otherInitPath);

	str.Format(_T("%d"), vseperateVal);
	result += L"开路电压分选工步号：" + str + L"\r\n\r\n";

	str.Format(_T("%d"), stopStepNumVal);
	result += L"终止容量分选工步号：" + str + L"\r\n\r\n";
	
	if (vpointVal == 1)
	{
		result += L"放电特征点电压(mV)    点1：";
		
	}
	else
	{
		result += L"放电特征点时间(Min)    点1：";
	}
	str.Format(_T("%d"), featureVal1);
	result += str + L" ； 点2：";
	str.Format(_T("%d"), featureVal2);
	result += str + L" ； 点3：";
	str.Format(_T("%d"), featureVal3);
	result += str + L" ； 点4：";
	str.Format(_T("%d"), featureVal4);
	result += str + L" ； 点5：";
	str.Format(_T("%d"), featureVal5);
	result += str + L"\r\n\r\n";

	str.Format(_T("%d"), warnCapVal);
	result += L"工步报警容量：" + str + L"mAh\r\n\r\n";

	return result;
}
