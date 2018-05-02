// DeviceSetInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "DeviceSetInfoDlg.h"
#include "afxdialogex.h"
#include "CabUtils.h"


// CDeviceSetInfoDlg �Ի���

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


// CDeviceSetInfoDlg ��Ϣ�������


BOOL CDeviceSetInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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
	// �쳣:  OCX ����ҳӦ���� FALSE
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
		// �ļ���һ��Ϊ��������
		// �ڶ���Ϊ�ͺ�
		//�ļ�������Ϊ���������������Ϊ�������
		
		getline(in, line);
		str = line.c_str();
		stepLineCstr = L"��������:" + str;
	
		getline(in, line);
		str = line.c_str();
		
		stepLineCstr += L"    �豸����:" + str + L"\r\n" + L"\r\n";

		getline(in, line);
		nRow = std::stoi(line);
		getline(in, line);
		nCol = std::stoi(line);


		for (int i = 1; i < nRow; ++i)
		{
			getline(in, line);
			int spaceidx = 0;

			//  ���stepName ��Ч �����������Ѱ��StepName
			vector<string> stepInfos = StringUtils::SplitByStr(line, " ");
			if (stepInfos.size() == 0)
				continue;
			str.Format(_T("%d"), i);

			stepLineCstr += str;
			str = stepInfos[0].c_str();
			stepLineCstr += L": " + str;

		
			if (stepInfos.size() == STEP_INFO_LENGTH)
			{
				if (stepInfos[0] == "������ѹ���")
				{
					str = stepInfos[TIME_PARAID + 1].c_str();
					stepLineCstr += L", ʱ��: " + str;
					str = stepInfos[CURRENT_PARAID + 1].c_str();
					stepLineCstr += L"Min, ������:" + str;
					str = stepInfos[MAX_VOLT_PARAID + 1].c_str();
					stepLineCstr += L"mA, ���޵�ѹ:" + str;	
					str = stepInfos[DELTA_VOLT_PARAID + 1].c_str();
					stepLineCstr += L"mV, ��V:" + str;
					str = stepInfos[END_CURRENT_PARAID + 1].c_str();
					stepLineCstr += L"mV, ��ֹ����:" + str;
					str = stepInfos[END_CAPACITY_PARAID + 1].c_str();
					stepLineCstr += L"mA, ��ֹ����:" + str + L"mAh";
				}
				else if (stepInfos[0] == "�������")
				{
					str = stepInfos[TIME_PARAID + 1].c_str();
					stepLineCstr += L", ʱ��: " + str;
					str = stepInfos[CURRENT_PARAID + 1].c_str();
					stepLineCstr += L"Min, ������:" + str;
					str = stepInfos[MAX_VOLT_PARAID + 1].c_str();
					stepLineCstr += L"mA, ���޵�ѹ:" + str;
					str = stepInfos[DELTA_VOLT_PARAID + 1].c_str();
					stepLineCstr += L"mV, ��V:" + str;
					str = stepInfos[END_CAPACITY_PARAID + 1].c_str();
					stepLineCstr += L"mV, ��ֹ����:" + str + L"mAh";
				}
				else if (stepInfos[0] == "�����ŵ�")
				{
					str = stepInfos[TIME_PARAID + 1].c_str();
					stepLineCstr += L", ʱ��: " + str;
					str = stepInfos[CURRENT_PARAID + 1].c_str();
					stepLineCstr += L"Min, �ŵ����:" + str;
					str = stepInfos[MIN_VOLT_PARAID + 1].c_str();
					stepLineCstr += L"mA, ���޵�ѹ:" + str;
					str = stepInfos[END_CAPACITY_PARAID + 1].c_str();
					stepLineCstr += L"mV, ��ֹ����:" + str + L"mAh";
				}
				else if (stepInfos[0] == "ѭ��")
				{
					str = stepInfos[START_STEP_PARAID + 1].c_str();
					stepLineCstr += L", ��ʼ����: " + str;
					str = stepInfos[END_STEP_PARAID + 1].c_str();
					stepLineCstr += L", ��ֹ����:" + str;
					str = stepInfos[LOOP_NUM_PARAID + 1].c_str();
					stepLineCstr += L", ѭ������:" + str;
				}
				else if (stepInfos[0] == "����")
				{
					str = stepInfos[TIME_PARAID + 1].c_str();
					stepLineCstr += L", ʱ��: " + str;
				}
			}
			stepLineCstr += L"\r\n\r\n";
		}
		stepLineCstr += L"\r\n";
		str.Format(_T("%d"), cabInfos[cabId - 1].vdisVal);
		stepLineCstr += L"����ɸѡ������    ��ѹ��: " + str + L" mV��";

		str.Format(_T("%d"), cabInfos[cabId - 1].adisVal);
		stepLineCstr += L"    ������: " + str + L" mA��";

		str.Format(_T("%d"), cabInfos[cabId - 1].timeDisVal);
		stepLineCstr += L"    ʱ���: " + str + L" Min\r\n\r\n";

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
	result += L"��·��ѹ��ѡ�����ţ�" + str + L"\r\n\r\n";

	str.Format(_T("%d"), stopStepNumVal);
	result += L"��ֹ������ѡ�����ţ�" + str + L"\r\n\r\n";
	
	if (vpointVal == 1)
	{
		result += L"�ŵ��������ѹ(mV)    ��1��";
		
	}
	else
	{
		result += L"�ŵ�������ʱ��(Min)    ��1��";
	}
	str.Format(_T("%d"), featureVal1);
	result += str + L" �� ��2��";
	str.Format(_T("%d"), featureVal2);
	result += str + L" �� ��3��";
	str.Format(_T("%d"), featureVal3);
	result += str + L" �� ��4��";
	str.Format(_T("%d"), featureVal4);
	result += str + L" �� ��5��";
	str.Format(_T("%d"), featureVal5);
	result += str + L"\r\n\r\n";

	str.Format(_T("%d"), warnCapVal);
	result += L"��������������" + str + L"mAh\r\n\r\n";

	return result;
}
