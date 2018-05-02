// ColorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "ColorDlg.h"
#include "afxdialogex.h"

#include <stdlib.h>
using std::wstring;
// CColorDlg 对话框

IMPLEMENT_DYNAMIC(CColorDlg, CDialog)

CColorDlg::CColorDlg(CWnd* pParent /*=NULL*/)
: CDialog(CColorDlg::IDD, pParent)
{
	colorPath = CBatteryUtils::GetConfigPath(_T("\\config\\init\\color.ini"));
}

CColorDlg::~CColorDlg()
{
}

void CColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHARGE_PIC, chargePic);
	DDX_Control(pDX, IDC_RECYCLE_PIC, recyclePic);
	DDX_Control(pDX, IDC_STOR_PIC, storPic);
	DDX_Control(pDX, IDC_UNSTOR_PIC, unstorPic);
	DDX_Control(pDX, IDC_STOP_PIC, stopPic);
	DDX_Control(pDX, IDC_DISCHARGE_PIC, dischargePic);
	DDX_Control(pDX, IDC_LAY_PIC, layPic);
	DDX_Control(pDX, IDC_VA_CHARGE_PIC, vaChargePic);
	DDX_Control(pDX, IDC_V_ERROR_PIC, vErrorPic);
	DDX_Control(pDX, IDC_A_ERROR_PIC, aErrorPic);
	DDX_Control(pDX, IDC_OVER_ALARM_PIC, overAlarmPic);
	DDX_Control(pDX, IDC_LEAK_ALARM_PIC, leakAlarmPic);
	DDX_Control(pDX, IDC_BAD_CONT_PIC, badContPic);
	DDX_Control(pDX, IDC_V_OVER_PIC, vOverPic);
	DDX_Control(pDX, IDC_BACTTERY_WIN_PIC, batteryWinPic);
	DDX_Control(pDX, IDC_DEFAULT_BTN, defaultBtn);
	//DDX_Control(pDX, IDC_PIC, myPic1);
}


BEGIN_MESSAGE_MAP(CColorDlg, CDialog)
	ON_STN_CLICKED(IDC_CHARGE_PIC, &CColorDlg::OnStnClickedChargePic)
	//	ON_WM_RBUTTONUP()
	ON_STN_CLICKED(IDC_RECYCLE_PIC, &CColorDlg::OnStnClickedRecyclePic)
	ON_STN_CLICKED(IDC_VA_CHARGE_PIC, &CColorDlg::OnStnClickedVaChargePic)
	ON_STN_CLICKED(IDC_LAY_PIC, &CColorDlg::OnStnClickedLayPic)
	ON_STN_CLICKED(IDC_DISCHARGE_PIC, &CColorDlg::OnStnClickedDischargePic)
	ON_STN_CLICKED(IDC_UNSTOR_PIC, &CColorDlg::OnStnClickedUnstorPic)
	ON_STN_CLICKED(IDC_STOP_PIC, &CColorDlg::OnStnClickedStopPic)
	ON_STN_CLICKED(IDC_STOR_PIC, &CColorDlg::OnStnClickedStorPic)
	ON_STN_CLICKED(IDC_V_ERROR_PIC, &CColorDlg::OnStnClickedVErrorPic)
	ON_STN_CLICKED(IDC_A_ERROR_PIC, &CColorDlg::OnStnClickedAErrorPic)
	ON_STN_CLICKED(IDC_OVER_ALARM_PIC, &CColorDlg::OnStnClickedOverAlarmPic)
	ON_STN_CLICKED(IDC_LEAK_ALARM_PIC, &CColorDlg::OnStnClickedLeakAlarmPic)
	ON_STN_CLICKED(IDC_BAD_CONT_PIC, &CColorDlg::OnStnClickedBadContPic)
	ON_STN_CLICKED(IDC_V_OVER_PIC, &CColorDlg::OnStnClickedVOverPic)
	ON_STN_CLICKED(IDC_BACTTERY_WIN_PIC, &CColorDlg::OnStnClickedBactteryWinPic)
	ON_BN_CLICKED(IDC_DEFAULT_BTN, &CColorDlg::OnBnClickedDefaultBtn)
	//ON_COMMAND(ID_INIT_DIALOG, &CColorDlg::OnInitDialog)
	//ON_COMMAND(ID_INIT_DIALOG, &CColorDlg::OnInitDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CColorDlg 消息处理程序
CArray <COLORREF> mColorArray;

void InitColor(CStatic &pic, COLORREF color)
{
	mColorArray.Add(color);
	CRect prect;
	CBrush initBrush(color);
	pic.GetClientRect(&prect);   //获取区域
	FillRect(pic.GetDC()->GetSafeHdc(), &prect, initBrush);

	initBrush.DeleteObject();
}


void CColorDlg::SetColor(CStatic &pic, COLORREF color)
{
	//COLORREF color = RGB(255, 0, 0);      // 颜色对话框的初始颜色为红色  
	CColorDialog colorDlg(color);         // 构造颜色对话框，传入初始颜色值   

	if (IDOK == colorDlg.DoModal())       // 显示颜色对话框，并判断是否点击了“确定”   
	{
		color = colorDlg.GetColor();      // 获取颜色对话框中选择的颜色值  
		CRect prect;
		CBrush selBrush(color);
		pic.GetClientRect(&prect);   //获取区域
		FillRect(pic.GetDC()->GetSafeHdc(), 
			CRect(prect.left + 1, prect.top + 1, prect.right - 1, prect.bottom - 1), selBrush);     //填充颜色
		
		if (pic == chargePic) initColor.chargeCol = color;
		else if (pic == recyclePic) initColor.recycleCol = color;
		else if (pic == storPic){
			initColor.storCol = color;
		}
		else if (pic == unstorPic) initColor.unstorCol = color;
		else if (pic == stopPic) initColor.stopCol = color;
		else if (pic == dischargePic) initColor.dischargeCol = color;
		else if (pic == layPic) initColor.layCol = color;
		else if (pic == vaChargePic) initColor.vaChargeCol = color;
		else if (pic == vErrorPic) initColor.verrorCol = color;
		else if (pic == aErrorPic) initColor.aerrorCol = color;
		else if (pic == overAlarmPic) initColor.overAlarmCol = color;
		else if (pic == leakAlarmPic) initColor.leakAlarmCol = color;
		else if (pic == badContPic) initColor.badContCol = color;
		else if (pic == vOverPic) initColor.voverCol = color;
		else if (pic == batteryWinPic) initColor.batteryWinCol = color;

		selBrush.DeleteObject();
	}
}


void CColorDlg::SetDefColor(CStatic &pic, COLORREF color)
{
	CBrush selBrush(color);
	CRect prect;
	pic.GetClientRect(&prect);   //获取区域
	FillRect(pic.GetDC()->GetSafeHdc(), 
		CRect(prect.left + 1, prect.top + 1, prect.right - 1, prect.bottom - 1), selBrush);     //填充颜色

	if (pic == chargePic) defColor.chargeCol = color;
	else if (pic == recyclePic) defColor.recycleCol = color;
	else if (pic == storPic) defColor.storCol = color;
	else if (pic == unstorPic) defColor.unstorCol = color;
	else if (pic == stopPic) defColor.stopCol = color;
	else if (pic == dischargePic) defColor.dischargeCol = color;
	else if (pic == layPic) defColor.layCol = color;
	else if (pic == vaChargePic) defColor.vaChargeCol = color;
	else if (pic == vErrorPic) defColor.verrorCol = color;
	else if (pic == aErrorPic) defColor.aerrorCol = color;
	else if (pic == overAlarmPic) defColor.overAlarmCol = color;
	else if (pic == leakAlarmPic) defColor.leakAlarmCol = color;
	else if (pic == badContPic) defColor.badContCol = color;
	else if (pic == vOverPic) defColor.voverCol = color;
	else if (pic == batteryWinPic) defColor.batteryWinCol = color;

	selBrush.DeleteObject();
}



BOOL CColorDlg::OnInitDialog()
{
	// TODO:  在此添加命令处理程序代码
	CDialog::OnInitDialog();

	return TRUE;
}


void CColorDlg::OnStnClickedChargePic()
{

	COLORREF color = mColorArray.GetAt(1);
	SetColor(chargePic, color);

}






void CColorDlg::OnStnClickedRecyclePic()
{
	//COLORREF color = mColorArray.GetAt(1);
	//int r = GetRValue(color);
	//int g = GetGValue(color);
	//int b = GetBValue(color);

	//SetColor(recyclePic, color);
	//wchar_t str[10];
	//_itow_s(r * 1000000 + g * 1000 + b, str, 10, 10);

	//WritePrivateProfileString(_T("iniColor"), _T("iniCharge"), str, colorPath);

	COLORREF color = mColorArray.GetAt(1);
	SetColor(recyclePic, color);
}


void CColorDlg::OnStnClickedVaChargePic()
{
	COLORREF color = mColorArray.GetAt(1);
	SetColor(vaChargePic, color);
}


void CColorDlg::OnStnClickedLayPic()
{
	COLORREF color = mColorArray.GetAt(1);
	SetColor(layPic, color);
}



void CColorDlg::OnStnClickedDischargePic()
{
	COLORREF color = mColorArray.GetAt(1);
	SetColor(dischargePic, color);
}


void CColorDlg::OnStnClickedUnstorPic()
{
	COLORREF color = mColorArray.GetAt(1);
	SetColor(unstorPic, color);
}


void CColorDlg::OnStnClickedStopPic()
{
	COLORREF color = mColorArray.GetAt(1);
	SetColor(stopPic, color);
}


void CColorDlg::OnStnClickedStorPic()
{
	COLORREF color = mColorArray.GetAt(1);
	SetColor(storPic, color);
}


void CColorDlg::OnStnClickedVErrorPic()
{
	COLORREF color = mColorArray.GetAt(1);
	SetColor(vErrorPic, color);
}


void CColorDlg::OnStnClickedAErrorPic()
{
	COLORREF color = mColorArray.GetAt(1);
	SetColor(aErrorPic, color);
}


void CColorDlg::OnStnClickedOverAlarmPic()
{
	COLORREF color = mColorArray.GetAt(1);
	SetColor(overAlarmPic, color);
}


void CColorDlg::OnStnClickedLeakAlarmPic()
{
	COLORREF color = mColorArray.GetAt(1);
	SetColor(leakAlarmPic, color);
}


void CColorDlg::OnStnClickedBadContPic()
{
	COLORREF color = mColorArray.GetAt(1);
	SetColor(badContPic, color);
}


void CColorDlg::OnStnClickedVOverPic()
{
	COLORREF color = mColorArray.GetAt(1);
	SetColor(vOverPic, color);
}


void CColorDlg::OnStnClickedBactteryWinPic()
{
	COLORREF color = mColorArray.GetAt(1);
	SetColor(batteryWinPic, color);
}


void CColorDlg::OnBnClickedDefaultBtn()
{
	// TODO:  在此添加控件通知处理程序代码
	if (MessageBox(_T("确定要恢复默认颜色设置么"), _T("提示"), MB_OKCANCEL | MB_ICONWARNING) == IDOK)
	{
		SetDefColor(chargePic, defColor.chargeCol);
		SetDefColor(recyclePic, defColor.recycleCol);
		SetDefColor(storPic, defColor.storCol);
		SetDefColor(unstorPic, defColor.unstorCol);
		SetDefColor(stopPic, defColor.stopCol);
		SetDefColor(dischargePic, defColor.dischargeCol);
		SetDefColor(layPic, defColor.layCol);
		SetDefColor(vaChargePic, defColor.vaChargeCol);
		SetDefColor(vErrorPic, defColor.verrorCol);
		SetDefColor(aErrorPic, defColor.aerrorCol);
		SetDefColor(overAlarmPic, defColor.overAlarmCol);
		SetDefColor(leakAlarmPic, defColor.leakAlarmCol);
		SetDefColor(badContPic, defColor.badContCol);
		SetDefColor(vOverPic, defColor.voverCol);
		SetDefColor(batteryWinPic, defColor.batteryWinCol);
		initColor.chargeCol = defColor.chargeCol;
		initColor.recycleCol = defColor.recycleCol;
		initColor.storCol = defColor.storCol;
		initColor.unstorCol = defColor.unstorCol;
		initColor.stopCol = defColor.stopCol;
		initColor.dischargeCol = defColor.dischargeCol;
		initColor.layCol = defColor.layCol;
		initColor.vaChargeCol = defColor.vaChargeCol;
		initColor.verrorCol = defColor.verrorCol;
		initColor.aerrorCol = defColor.aerrorCol;
		initColor.overAlarmCol = defColor.overAlarmCol;
		initColor.leakAlarmCol = defColor.leakAlarmCol;
		initColor.badContCol = defColor.badContCol;
		initColor.voverCol = defColor.voverCol;
		initColor.batteryWinCol = defColor.batteryWinCol;


		MessageBox(_T("恢复默认设置成功!"));
	}
}

void CColorDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	InitColor(chargePic, initColor.chargeCol);
	InitColor(recyclePic, initColor.recycleCol);
	InitColor(storPic, initColor.storCol);
	InitColor(unstorPic, initColor.unstorCol);
	InitColor(stopPic, initColor.stopCol);
	InitColor(dischargePic, initColor.dischargeCol);
	InitColor(layPic, initColor.layCol);
	InitColor(vaChargePic, initColor.vaChargeCol);
	InitColor(vErrorPic, initColor.verrorCol);
	InitColor(aErrorPic, initColor.aerrorCol);
	InitColor(overAlarmPic, initColor.overAlarmCol);
	InitColor(leakAlarmPic, initColor.leakAlarmCol);
	InitColor(badContPic, initColor.badContCol);
	InitColor(vOverPic, initColor.voverCol);
	InitColor(batteryWinPic, initColor.batteryWinCol);

}

void SaveColor(COLORREF color, CString catStr, CString keyStr, CString colorPath)
{
	int r, g, b;
	wchar_t str[10];
	r = GetRValue(color);
	g = GetGValue(color);
	b = GetBValue(color);
	_itow_s(r * 1000000 + g * 1000 + b, str, 10, 10);
	//	WritePrivateProfileString(_T("iniColor", _T("iniCharge"), str, colorDlg.colorPath);
	WritePrivateProfileString(catStr, keyStr, str, colorPath);
}

void CColorDlg::SaveColorSet()
{
	if (MessageBox(_T("确定要修改颜色么"), _T("提示"), MB_OKCANCEL | MB_ICONWARNING) == IDOK)
	{
		SaveColor(initColor.chargeCol, _T("iniColor"), _T("iniCharge"), colorPath);
		SaveColor(initColor.recycleCol, _T("iniColor"), _T("iniRecycle"), colorPath);
		SaveColor(initColor.storCol, _T("iniColor"), _T("iniStor"), colorPath);
		SaveColor(initColor.unstorCol, _T("iniColor"), _T("iniUnstor"), colorPath);
		SaveColor(initColor.stopCol, _T("iniColor"), _T("iniStop"), colorPath);
		SaveColor(initColor.dischargeCol, _T("iniColor"), _T("iniDischarge"), colorPath);
		SaveColor(initColor.layCol, _T("iniColor"), _T("iniLay"), colorPath);
		SaveColor(initColor.vaChargeCol, _T("iniColor"), _T("iniVaCharge"), colorPath);
		SaveColor(initColor.verrorCol, _T("iniColor"), _T("iniVerror"), colorPath);
		SaveColor(initColor.aerrorCol, _T("iniColor"), _T("iniAerror"), colorPath);
		SaveColor(initColor.overAlarmCol, _T("iniColor"), _T("iniOverAlarm"), colorPath);
		SaveColor(initColor.leakAlarmCol, _T("iniColor"), _T("iniLeakAlarm"), colorPath);
		SaveColor(initColor.badContCol, _T("iniColor"), _T("iniBadCont"), colorPath);
		SaveColor(initColor.voverCol, _T("iniColor"), _T("iniVover"), colorPath);
		SaveColor(initColor.batteryWinCol, _T("iniColor"), _T("iniBatteryWin"), colorPath);

		//ofstream file;

		//file.open("C:\\log.txt", ios::app);
		//file << CT2A(colorPath.GetBuffer()) << endl;
		//file.close();
		MessageBox(_T("修改颜色设置成功"));
	}
}


