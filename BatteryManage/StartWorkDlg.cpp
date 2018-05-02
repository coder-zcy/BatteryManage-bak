// StartWorkDlg.cpp : 实现文件
//
#pragma once

#include "stdafx.h"
#include "BatteryManage.h"
#include "StartWorkDlg.h"
#include "afxdialogex.h"
#include "NewCellTypes/GridCellCombo.h"

#include "DbSql.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// CStartWorkDlg 对话框

//	占位符
//const int INVALIDE_PARA_DATA = -1;
////	默认字工步数据的值
//const int DEFAULT_PARA_DATA = 0;
//const CString DEFAULT_PATA_STR = L"0";

const CString MAX_GRID_ITEM_CSTR = L"0";

CWorkProc* workProcs[MAX_CAB_NUM];

IMPLEMENT_DYNAMIC(CStartWorkDlg, CDialog)

CStartWorkDlg::CStartWorkDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStartWorkDlg::IDD, pParent)
{
	addrowNumDlg = NULL;
	delrowNumDlg = NULL;
	cpDlg = NULL;
	sendDlg = NULL;
	numberingDlg = NULL;
	cycleDlg = NULL;

	cabLinks.clear();
	cabLinks.push_back(&cabLink1);
	cabLinks.push_back(&cabLink2);
	cabLinks.push_back(&cabLink3);
	cabLinks.push_back(&cabLink4);
	cabLinks.push_back(&cabLink5);

	cabLinks.push_back(&cabLink6);
	cabLinks.push_back(&cabLink7);
	cabLinks.push_back(&cabLink8);
	cabLinks.push_back(&cabLink9);
	cabLinks.push_back(&cabLink10);

	cabLinks.push_back(&cabLink11);
	cabLinks.push_back(&cabLink12);
	cabLinks.push_back(&cabLink13);
	cabLinks.push_back(&cabLink14);
	cabLinks.push_back(&cabLink15);

	cabLinks.push_back(&cabLink16);
	cabLinks.push_back(&cabLink17);
	cabLinks.push_back(&cabLink18);
	cabLinks.push_back(&cabLink19);
	cabLinks.push_back(&cabLink20);

	cabRects.clear();


	// 初始化状态值
	stepNames.clear();
	stepNames.push_back(_T("恒流恒压充电"));
	stepNames.push_back(_T("恒流充电"));
	stepNames.push_back(_T("恒流放电"));
	stepNames.push_back(_T("搁置"));
	stepNames.push_back(_T("结束"));
	stepNames.push_back(_T("循环"));

	int idx;
	linkNames.clear();
	hoverLinkNames.clear();
	CString str;

	// color
	defaultStepColor = RGB(0xFF, 0xFF, 0xE0);

	for (idx = 0; idx < MAX_CAB_NUM; ++idx)
	{
		str.Format(_T("%d"), idx + 1);
		linkNames.push_back(_T("# ") + str);
		hoverLinkNames.push_back(_T("<a># ") + str +_T("</a>"));

		workProcs[idx] = NULL;
	}
	BOOL GridCopyFlag = FALSE;							//	表格的复制粘贴标记
	BOOL GridCutFlag = FALSE;

}

CStartWorkDlg::~CStartWorkDlg()
{
	if (addrowNumDlg != NULL) delete addrowNumDlg;
	if (delrowNumDlg != NULL) delete delrowNumDlg;
	if (cpDlg != NULL) delete cpDlg;
	if (sendDlg != NULL) delete sendDlg;
	if (numberingDlg != NULL) delete numberingDlg;
	if (cycleDlg != NULL) delete cycleDlg;


}

void CStartWorkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SW_GIRD, m_GridCtrl);
	DDX_Control(pDX, IDC_CAB_LINK1, cabLink1);
	DDX_Control(pDX, IDC_CAB_LINK2, cabLink2);
	DDX_Control(pDX, IDC_CAB_LINK3, cabLink3);
	DDX_Control(pDX, IDC_CAB_LINK4, cabLink4);
	DDX_Control(pDX, IDC_CAB_LINK5, cabLink5);
	DDX_Control(pDX, IDC_CAB_LINK6, cabLink6);
	DDX_Control(pDX, IDC_CAB_LINK7, cabLink7);
	DDX_Control(pDX, IDC_CAB_LINK8, cabLink8);
	DDX_Control(pDX, IDC_CAB_LINK9, cabLink9);
	DDX_Control(pDX, IDC_CAB_LINK10, cabLink10);
	DDX_Control(pDX, IDC_CAB_LINK11, cabLink11);
	DDX_Control(pDX, IDC_CAB_LINK12, cabLink12);
	DDX_Control(pDX, IDC_CAB_LINK13, cabLink13);
	DDX_Control(pDX, IDC_CAB_LINK14, cabLink14);
	DDX_Control(pDX, IDC_CAB_LINK15, cabLink15);
	DDX_Control(pDX, IDC_CAB_LINK16, cabLink16);
	DDX_Control(pDX, IDC_CAB_LINK17, cabLink17);
	DDX_Control(pDX, IDC_CAB_LINK18, cabLink18);
	DDX_Control(pDX, IDC_CAB_LINK19, cabLink19);
	DDX_Control(pDX, IDC_CAB_LINK20, cabLink20);
    DDX_Control(pDX, IDC_CAB_SEL, cabSel);
	DDX_Control(pDX, IDC_EDIT_SW_BATCAP, batCapEdit);
	DDX_Control(pDX, IDC_EDIT_SW_WARNCAP, warnCapEdit);
	DDX_Control(pDX, IDC_EDIT_SW_VOLTSEPERATION, vseperateEdit);
	DDX_Control(pDX, IDC_EDIT_SW_CAPSEPERATION, stopStepNumEdit);
	DDX_Control(pDX, IDC_EDIT_SW_FEATURE1, featureEdit1);
	DDX_Control(pDX, IDC_EDIT_SW_FEATURE2, featureEdit2);
	DDX_Control(pDX, IDC_EDIT_SW_FEATURE3, featureEdit3);
	DDX_Control(pDX, IDC_EDIT_SW_FEATURE4, featureEdit4);
	DDX_Control(pDX, IDC_EDIT_SW_FEATURE5, featureEdit5);
	DDX_Control(pDX, IDC_EDIT_SW_DATAFILE_NAME, dataFileEdit);
	DDX_Control(pDX, IDC_EDIT_SW_FILEREMARKS, fileRemarkEdit);
	DDX_Control(pDX, IDC_STOP_CYCLE_EDIT, stopCycleEdit);
	DDX_Control(pDX, IDC_EDIT_SW_CYCLE_VOLT, vcycleEdit);
	DDX_Control(pDX, IDC_EDIT_SW_WORKPROCNAME, workProcEdit);
	DDX_Control(pDX, IDC_EDIT_SW_MODEL, modelEdit);
}

BOOL CStartWorkDlg::OnInitDialog(){
	CDialog::OnInitDialog();

	//m_ImageList.Create(MAKEINTRESOURCE(IDB_IMAGES), 16, 1, RGB(255, 255, 255));
	//m_GridCtrl.SetImageList(&m_ImageList);
	CreateTimePath();

	InitColorSet();
	InitCabLinks();
	InitOtherInfo();
	InitGrid();
	//InitSpecCabInfo(defaultCabId);
	InitSpecCabInfoByFile(stepCabId);

	InitOtherCabInfo(stepCabId);

	// 为了解决有时会加载不出工步的问题，对工步进行二次加载。
	InitSpecStepInfoByPara(stepCabId);

	return TRUE;
}

void CStartWorkDlg::updateAllRow()
{
	
	CString str;
	GV_ITEM Item;
	Item.mask = GVIF_TEXT | GVIF_FORMAT;
	Item.col = 0;
	Item.nFormat = DT_CENTER | DT_WORDBREAK;

	CWorkProc* workProc = workProcs[stepCabId - 1];
	for (int row = 1; row < m_GridCtrl.GetRowCount(); row++){
		Item.row = row;
		str.Format(_T("%d"), row);
		Item.strText.Format(str);
		m_GridCtrl.SetItem(&Item);
	}
	//UpdateWorkProcs(stepCabId);
	m_GridCtrl.Invalidate();
}

void CStartWorkDlg::CreateTimePath()
{
	wchar_t str[INT_LENGTH];
	
	time(&nowTimeInfo);
	localtime_s(&nowTime, &nowTimeInfo);

	int year = nowTime.tm_year + 1900;
	int month = nowTime.tm_mon + 1;
	int day = nowTime.tm_mday;
	int hour = nowTime.tm_hour;
	int minute = nowTime.tm_min;
	int second = nowTime.tm_sec;

	CString yearStr, monthStr, dayStr, hourStr, minuteStr, secondStr;


	_itow_s(year, str, INT_LENGTH); yearStr = str;
	_itow_s(month, str, INT_LENGTH); monthStr = str; monthStr = month < 10 ? _T("0") + monthStr : monthStr;
	_itow_s(day, str, INT_LENGTH); dayStr = str; dayStr = day < 10 ? _T("0") + dayStr : dayStr;
	_itow_s(hour, str, INT_LENGTH); hourStr = str; hourStr = hour < 10 ? _T("0") + hourStr : hourStr;
	_itow_s(minute, str, INT_LENGTH); minuteStr = str; minuteStr = minute < 10 ? _T("0") + minuteStr : minuteStr;
	_itow_s(second, str, INT_LENGTH); secondStr = str; secondStr = second < 10 ? _T("0") + secondStr : secondStr;

	timePath = yearStr + _T("_") + monthStr + "\\"
		+ dayStr + _T("_") + hourStr + minuteStr + secondStr + _T("_");

}

void CStartWorkDlg::InitColorSet()
{
	colorPath = CBatteryUtils::GetConfigPath(_T("\\config\\init\\color.ini"));
	
	int constAvVal = GetPrivateProfileInt(_T("iniColor"), _T("iniVaCharge"), 0, colorPath);
	int constAVal = GetPrivateProfileInt(_T("iniColor"), _T("iniCharge"), 0, colorPath);
	int constADisVal = GetPrivateProfileInt(_T("iniColor"), _T("iniDischarge"), 0, colorPath);
	int layVal = GetPrivateProfileInt(_T("iniColor"), _T("iniLay"), 0, colorPath);
	int overVal = GetPrivateProfileInt(_T("iniColor"), _T("iniStop"), 0, colorPath);
	int cycleVal = GetPrivateProfileInt(_T("iniColor"), _T("iniRecycle"), 0, colorPath);
	int storVal = GetPrivateProfileInt(_T("iniColor"), _T("iniStor"), 0, colorPath);
	int unstorVal = GetPrivateProfileInt(_T("iniColor"), _T("iniUnstor"), 0, colorPath);

	stepColors.clear();
	stepColors.push_back(RGB(constAvVal / 1000000, (constAvVal / 1000) % 1000, constAvVal % 1000));
	stepColors.push_back(RGB(constAVal / 1000000, (constAVal / 1000) % 1000, constAVal % 1000));
	stepColors.push_back(RGB(constADisVal / 1000000, (constADisVal / 1000) % 1000, constADisVal % 1000));
	stepColors.push_back(RGB(layVal / 1000000, (layVal / 1000) % 1000, layVal % 1000));
	
	stepColors.push_back(RGB(overVal / 1000000, (overVal / 1000) % 1000, overVal % 1000));
	stepColors.push_back(RGB(cycleVal / 1000000, (cycleVal / 1000) % 1000, cycleVal % 1000));
	stepColors.push_back(RGB(storVal / 1000000, (storVal / 1000) % 1000, storVal % 1000));
	stepColors.push_back(RGB(unstorVal / 1000000, (unstorVal / 1000) % 1000, unstorVal % 1000));

}

//  初始化 机柜选项标签
void CStartWorkDlg::InitCabLinks()
{
	cabInitPath = CBatteryUtils::GetConfigPath(_T("\\config\\init\\cabinet.ini"));
	//cabInitPath = _T("E:\\项目\\番禺电池\\BatteryManage\\Debug\\config\\init\\cabinet.ini");
	wchar_t str[MAX_PATH_LENGTH];


	GetPrivateProfileString(_T("cabDbPath"), _T("basepath"), _T("E:\battery"), str, MAX_PATH_LENGTH, cabInitPath);
	defaultBasePath = str;

	GetPrivateProfileString(_T("cabs"), _T("cabSels"), _T("0"), str, MAX_PATH_LENGTH,
		cabInitPath);

	//defaultCabId = -1;
	CRect rect;
	CRect rect1;
	cabLink1.GetWindowRect(rect);
	ScreenToClient(rect);

	for (int idx = 0; idx < MAX_CAB_NUM; ++idx)
	{
		
		cabLinks[idx]->ShowWindow(str[idx] == '1' ? SW_NORMAL : SW_HIDE);
		if (str[idx] == '1')
			curCabId = curCabId == 0 ? idx + 1 : curCabId;
		stepCabId = curCabId;
		if (idx >= 1)
		{
			rect.left += 40;
			rect.right += 40;
		}
		cabLinks[idx]->MoveWindow(rect,TRUE);
		CString str;
		cabLinks[idx]->GetWindowTextW(str);
		//MessageBox(str);
		rect1 = rect;
		rect1.top += 16;
		rect1.bottom = rect1.top + 16;
		rect1.left += 0;
		rect1.right = rect1.left + 16;

		cabRects.push_back(rect1);
	}
	str[MAX_CAB_NUM] = '\0';

	//if (defaultCabId > 0)
	if (curCabId > 0)
	{
		//stepCabId = defaultCabId;
		stepCabId = curCabId;
		cabSel.SetIcon(theApp.selIcon);
		//cabSel.MoveWindow(cabRects[defaultCabId - 1], TRUE);
		cabSel.MoveWindow(cabRects[curCabId - 1], TRUE);
	}
}

// 初始化CEDIT 标签中的内容
void CStartWorkDlg::InitOtherInfo()
{
	//if (defaultCabId <= 0) return;
	if (curCabId <= 0) return;

	wchar_t str[MAX_PATH_LENGTH];
	//CString defaultCabIdStr;
	//_itow_s(defaultCabId, str, INT_LENGTH);
	//defaultCabIdStr = str;
	
	CString curCabIdStr;
	_itow_s(curCabId, str, INT_LENGTH);
	curCabIdStr = str;

	otherInitPath = CBatteryUtils::GetConfigPath(_T("\\config\\step\\") + curCabIdStr + _T("\\other.ini"));
	
	batCapVal = GetPrivateProfileInt(_T("other"), _T("batCap"), 0, otherInitPath);
	warnCapVal = GetPrivateProfileInt(_T("other"), _T("warnCap"), 0, otherInitPath);
	vseperateVal = GetPrivateProfileInt(_T("other"), _T("vseperate"), 0, otherInitPath);
	vcycleVal = GetPrivateProfileInt(_T("other"), _T("vcycleNum"), 0, otherInitPath);
	stopStepNumVal = GetPrivateProfileInt(_T("other"), _T("stopStepNum"), 0, otherInitPath);
	stopCycleVal = GetPrivateProfileInt(_T("other"), _T("stopCycle"), 0, otherInitPath);
	vpointVal = GetPrivateProfileInt(_T("other"), _T("vpoint"), 0, otherInitPath);

	tpointVal = GetPrivateProfileInt(_T("other"), _T("tpoint"), 0, otherInitPath);
	featureVal1 = GetPrivateProfileInt(_T("other"), _T("feature1"), 0, otherInitPath);
	featureVal2 = GetPrivateProfileInt(_T("other"), _T("feature2"), 0, otherInitPath);
	featureVal3 = GetPrivateProfileInt(_T("other"), _T("feature3"), 0, otherInitPath);
	featureVal4 = GetPrivateProfileInt(_T("other"), _T("feature4"), 0, otherInitPath);
	featureVal5 = GetPrivateProfileInt(_T("other"), _T("feature5"), 0, otherInitPath);

	GetPrivateProfileString(_T("basepath"), _T("defBasePath"), _T("D:\battery"), str, MAX_PATH_LENGTH, cabInitPath);
	defaultBasePath = str;

	//defaultCabIdStr = defaultCabId < 10 ? _T("0") + defaultCabIdStr : defaultCabIdStr;
	curCabIdStr = curCabId < 10 ? _T("0") + curCabIdStr : curCabIdStr;
	defaultDbPath = defaultBasePath + _T("\\") + timePath + curCabIdStr;


	// 初始化相关标签
	((CButton *)GetDlgItem(IDC_RADIO_SW_VOLT))->SetCheck(vpointVal == 1 ? TRUE : FALSE);
	((CButton *)GetDlgItem(IDC_RADIO_SW_TIME))->SetCheck(tpointVal == 1 ? TRUE : FALSE);
	
	_itow_s(batCapVal, str, INT_LENGTH);
	batCapEdit.SetWindowTextW(str);
	
	_itow_s(warnCapVal, str, INT_LENGTH);
	warnCapEdit.SetWindowTextW(str);

	_itow_s(vseperateVal, str, INT_LENGTH);
	vseperateEdit.SetWindowTextW(str);

	_itow_s(vcycleVal, str, INT_LENGTH);
	vcycleEdit.SetWindowTextW(str);

	_itow_s(stopStepNumVal, str, INT_LENGTH);
	stopStepNumEdit.SetWindowTextW(str);

	_itow_s(stopCycleVal, str, INT_LENGTH);
	stopCycleEdit.SetWindowTextW(str);
	
	_itow_s(featureVal1, str, INT_LENGTH);
	featureEdit1.SetWindowTextW(str);

	_itow_s(featureVal2, str, INT_LENGTH);
	featureEdit2.SetWindowTextW(str);
	
	_itow_s(featureVal3, str, INT_LENGTH);
	featureEdit3.SetWindowTextW(str);
	
	_itow_s(featureVal4, str, INT_LENGTH);
	featureEdit4.SetWindowTextW(str);

	_itow_s(featureVal5, str, INT_LENGTH);
	featureEdit5.SetWindowTextW(str);
	
	dataFileEdit.SetWindowTextW(defaultDbPath);
	fileRemarkEdit.SetWindowTextW(fileRemarkVal);
}


void CStartWorkDlg::m_InsertRow(int nRow)
{
	CString str;
	str.Format(_T("%d"), nRow);
	m_GridCtrl.InsertRow(str, nRow);
	m_GridCtrl.Invalidate();
	//对每一行第一个Cell设置为Combo控件
	//m_GridCtrl.SetCellType(nRow, 1, RUNTIME_CLASS(CGridCell));
	//m_GridCtrl.Invalidate();
	m_GridCtrl.SetCellType(nRow, 1, RUNTIME_CLASS(CGridCellCombo));
	CStringArray options;
	options.Add(_T("恒流恒压充电"));
	options.Add(_T("恒流充电"));
	options.Add(_T("恒流放电"));
	options.Add(_T("搁置"));
	options.Add(_T("结束"));
	options.Add(_T("循环"));
	CGridCellCombo *pCell = (CGridCellCombo*)m_GridCtrl.GetCell(nRow, 1);
	pCell->SetOptions(options);
	pCell->SetStyle(CBS_DROPDOWN);


	updateAllRow();
	
}

void CStartWorkDlg::AddOneRow()
{
	// TODO:  在此添加控件通知处理程序代码
	int focusRow = m_GridCtrl.GetFocusCell().row;
	//防止出现获取不到focus的行
	focusRow = (focusRow > 0) ? focusRow : 1;
	if (m_GridCtrl.GetRowCount() <= 1)
	{
		m_GridCtrl.SetRowCount(2); //表格小于1行的时候，增加一行
		for (int col = 0; col < m_GridCtrl.GetColumnCount(); col++)
		{
			//设置表格显示属性
			GV_ITEM Item;
			Item.mask = GVIF_TEXT | GVIF_FORMAT;
			Item.row = 1;
			Item.col = col;
			//设置各行高
			m_GridCtrl.SetRowHeight(1, GRID_ROW_HEIGHT);
			//设置列宽 
			if (col == 1)
				m_GridCtrl.SetColumnWidth(col, GRID_SEL_WIDTH);
			else
				m_GridCtrl.SetColumnWidth(col, GRID_COL_WIDTH);

			if (col < 1)
			{
				Item.nFormat = DT_CENTER | DT_WORDBREAK;
				Item.strText.Format(_T("%d"), 1);
			}
			else if (col < 2)
			{
				//m_GridCtrl.SetCellType(1, col, RUNTIME_CLASS(CGridCell));
				//m_GridCtrl.Invalidate();
				m_GridCtrl.SetCellType(1, col, RUNTIME_CLASS(CGridCellCombo));
				CStringArray options;
				options.Add(_T("恒流恒压充电"));
				options.Add(_T("恒流充电"));
				options.Add(_T("恒流放电"));
				options.Add(_T("搁置"));
				options.Add(_T("结束"));
				options.Add(_T("循环"));
				CGridCellCombo *pCell = (CGridCellCombo*)m_GridCtrl.GetCell(1, col);
				pCell->SetOptions(options);
				pCell->SetStyle(CBS_DROPDOWN);

				continue;
			}
			else{
				Item.nFormat = DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;
				Item.strText.Format(_T(""), 2);
			}
			m_GridCtrl.SetItem(&Item);
		}
	}
	else
	{
		m_InsertRow(focusRow);
	}
	//UpdateWorkProcs(stepCabId);
	//updateAllRow();
	m_GridCtrl.Invalidate();

}

void CStartWorkDlg::DelOneRow()
{
	// TODO:  在此添加控件通知处理程序代码
	int focusRow = m_GridCtrl.GetFocusCell().row;
	if (focusRow >= 0)
	{
		m_GridCtrl.DeleteRow(focusRow);
		m_GridCtrl.Invalidate();
	}

	UpdateWorkProcs(stepCabId);
	updateAllRow();
	m_GridCtrl.Invalidate();

}


void CStartWorkDlg::AddMultiRow()
{
	// TODO:  在此添加控件通知处理程序代码
	if (addrowNumDlg == NULL){
		addrowNumDlg = new CSW_AddRowNumDlg();
	}

	int addrow = 0;
	int focusrow = m_GridCtrl.GetFocusCell().row;

	if (addrowNumDlg->DoModal() == IDOK)
	{
		addrow = addrowNumDlg->rowNum;
		focusrow = (focusrow > 0) ? focusrow : 1;
		AddOneRow();

		for (int i = 0; i < addrow - 1; ++i)
		{
			m_InsertRow(focusrow);
		}
	}

	//UpdateWorkProcs(stepCabId);
	updateAllRow();
	m_GridCtrl.Invalidate();
}

void CStartWorkDlg::DelMultiRow()
{
	// TODO:  在此添加控件通知处理程序代码
	if (delrowNumDlg == NULL)
	{
		delrowNumDlg = new CSW_DelRowNumDlg();
	}

	int delRowNum = 0;
	//int focusrow = m_GridCtrl.GetFocusCell().row;
	CCellRange range = m_GridCtrl.GetCellRange();
	int focusrow = range.GetMaxRow();

	if (delrowNumDlg->DoModal() == IDOK)
	{
		if (focusrow < 1) return;
		delRowNum = delrowNumDlg->deleteRowNum;
		if (delRowNum < m_GridCtrl.GetRowCount() - 1)
		{
			//focusrow 以后有大于delRowNum数目的行数则全删
			if ((m_GridCtrl.GetRowCount() - (focusrow + 1)) > delRowNum)
			{
				for (int i = 0; i < delRowNum; ++i)
				{
					m_GridCtrl.DeleteRow(focusrow);
					m_GridCtrl.Invalidate();
					
				}
			}
			else
			{
				focusrow = m_GridCtrl.GetRowCount() - delRowNum;
				for (int i = 0; i < delRowNum; ++i)
				{
					m_GridCtrl.DeleteRow(focusrow);
					m_GridCtrl.Invalidate();
					
				}
			}
		}
		else
		{
			//删除全部行
			focusrow = 1;
			delRowNum = m_GridCtrl.GetRowCount() - 1;
			for (int i = 0; i < delRowNum; ++i)
			{
				m_GridCtrl.DeleteRow(focusrow);
				m_GridCtrl.Invalidate();
			}
		}
	}
	UpdateWorkProcs(stepCabId);
	updateAllRow();
	m_GridCtrl.Invalidate();
	
}



BEGIN_MESSAGE_MAP(CStartWorkDlg, CDialog)
	ON_NOTIFY(NM_RCLICK, IDC_SW_GIRD, OnGridRClick)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_SW_GIRD, OnGridEndEdit)
	ON_NOTIFY(GVN_SELCHANGING, IDC_SW_GIRD, OnGridStartSelChange)
	ON_NOTIFY(GVN_SELCHANGED, IDC_SW_GIRD, OnGridEndSelChange)
//	ON_COMMAND(ID_SW_RC_ADDONEROW, &CStartWorkDlg::OnSwRcAddonerow)
//	ON_COMMAND(ID_SW_RC_ADDMULROW, &CStartWorkDlg::OnSwRcAddmulrow)
//	ON_COMMAND(ID_SW_RC_DELONEROW, &CStartWorkDlg::OnSwRcDelonerow)
//	ON_COMMAND(ID_SW_RC_DELMULROW, &CStartWorkDlg::OnSwRcDelmulrow)
ON_BN_CLICKED(IDC_BTN_SW_OPENPROC, &CStartWorkDlg::OnBnClickedBtnSwOpenproc)
ON_BN_CLICKED(IDC_BTN_SW_SAVEPROC, &CStartWorkDlg::OnBnClickedBtnSwSaveproc)
ON_BN_CLICKED(IDC_BTN_SW_COPYPARAMETER, &CStartWorkDlg::OnBnClickedBtnSwCopyparameter)
ON_BN_CLICKED(IDC_BTN_SW_BATTERY_NUM, &CStartWorkDlg::OnBnClickedBtnSwBatteryNum)
ON_BN_CLICKED(IDC_BTN_SW_SEND, &CStartWorkDlg::OnBnClickedBtnSwSend)
//ON_WM_MOUSEMOVE()
ON_WM_LBUTTONDOWN()
ON_NOTIFY(NM_CLICK, IDC_CAB_LINK1, &CStartWorkDlg::OnNMClickCabLink1)
ON_NOTIFY(NM_CLICK, IDC_CAB_LINK2, &CStartWorkDlg::OnNMClickCabLink2)
ON_NOTIFY(NM_CLICK, IDC_CAB_LINK3, &CStartWorkDlg::OnNMClickCabLink3)
ON_NOTIFY(NM_CLICK, IDC_CAB_LINK4, &CStartWorkDlg::OnNMClickCabLink4)
ON_NOTIFY(NM_CLICK, IDC_CAB_LINK5, &CStartWorkDlg::OnNMClickCabLink5)
ON_NOTIFY(NM_CLICK, IDC_CAB_LINK6, &CStartWorkDlg::OnNMClickCabLink6)
ON_NOTIFY(NM_CLICK, IDC_CAB_LINK7, &CStartWorkDlg::OnNMClickCabLink7)
ON_NOTIFY(NM_CLICK, IDC_CAB_LINK8, &CStartWorkDlg::OnNMClickCabLink8)
ON_NOTIFY(NM_CLICK, IDC_CAB_LINK9, &CStartWorkDlg::OnNMClickCabLink9)
ON_NOTIFY(NM_CLICK, IDC_CAB_LINK10, &CStartWorkDlg::OnNMClickCabLink10)
ON_NOTIFY(NM_CLICK, IDC_CAB_LINK11, &CStartWorkDlg::OnNMClickCabLink11)
ON_NOTIFY(NM_CLICK, IDC_CAB_LINK12, &CStartWorkDlg::OnNMClickCabLink12)
ON_NOTIFY(NM_CLICK, IDC_CAB_LINK13, &CStartWorkDlg::OnNMClickCabLink13)
ON_NOTIFY(NM_CLICK, IDC_CAB_LINK14, &CStartWorkDlg::OnNMClickCabLink14)
ON_NOTIFY(NM_CLICK, IDC_CAB_LINK15, &CStartWorkDlg::OnNMClickCabLink15)
ON_NOTIFY(NM_CLICK, IDC_CAB_LINK16, &CStartWorkDlg::OnNMClickCabLink16)
ON_NOTIFY(NM_CLICK, IDC_CAB_LINK17, &CStartWorkDlg::OnNMClickCabLink17)
ON_NOTIFY(NM_CLICK, IDC_CAB_LINK18, &CStartWorkDlg::OnNMClickCabLink18)
ON_NOTIFY(NM_CLICK, IDC_CAB_LINK19, &CStartWorkDlg::OnNMClickCabLink19)
ON_NOTIFY(NM_CLICK, IDC_CAB_LINK20, &CStartWorkDlg::OnNMClickCabLink20)

ON_BN_CLICKED(IDC_CREATE_DATABASE, &CStartWorkDlg::OnBnClickedCreateDatabase)
ON_BN_CLICKED(IDC_BTN_SW_CLOSE, &CStartWorkDlg::OnBnClickedBtnSwClose)
ON_MESSAGE(WM_CLOSE_START_DLG, &CStartWorkDlg::OnCloseStartDlg)
ON_WM_CLOSE()
END_MESSAGE_MAP()


// CStartWorkDlg 消息处理程序

void CStartWorkDlg::OnGridRClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*)pNotifyStruct;
	if (pItem->iRow == -1) return;

	endSelRow = pItem->iRow;

	CMenu   menu;   //定义下面要用到的cmenu对象
	menu.LoadMenu(IDR_SW_RIGHTCLICK); //装载自定义的右键菜单 
	CMenu   *pContextMenu = menu.GetSubMenu(0); //获取第一个弹出菜单，所以第一个菜单必须有子菜单 
	CPoint point1;//定义一个用于确定光标位置的位置  
	GetCursorPos(&point1);//获取当前光标的位置，以便使得菜单可以跟随光标  
	pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point1.x, point1.y, AfxGetMainWnd()); //在指定位置显示弹出菜单
}


afx_msg void CStartWorkDlg::OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	if (m_GridCtrl.GetRowCount() < 2) return;
	int errorFlag = TRUE;
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*)pNotifyStruct;
	//if (1 != pItem->iColumn) return;
	//处理编辑完单元格之后的逻辑
	//处理combo grid cell选择完以后的逻辑
	//可处理数值的限制
	if (m_GridCtrl.GetItemText(pItem->iRow, pItem->iColumn) == "结束")
	{
		int del_number = m_GridCtrl.GetRowCount() - (pItem->iRow + 1);
		for (int i = 0; i < del_number; ++i)
		{
			m_GridCtrl.DeleteRow(m_GridCtrl.GetRowCount() - 1);
			m_GridCtrl.Invalidate();
		}
		updateAllRow();
		//这一行的所有单元格变不能编辑
		for (int j = 2; j < m_GridCtrl.GetColumnCount(); j++)
		{
			m_GridCtrl.SetItemText(pItem->iRow, j, _T(""));
			//m_GridCtrl.SetItemState(pItem->iRow, j, GVIS_READONLY);
		}
	}

	if (m_GridCtrl.GetItemText(pItem->iRow, pItem->iColumn) == "搁置")
	{
		//这一行的所有单元格变不能编辑，并且清空，保留时间
		for (int j = 3; j < m_GridCtrl.GetColumnCount(); j++)
		{
			m_GridCtrl.SetItemText(pItem->iRow, j, _T(""));
			//m_GridCtrl.SetItemState(pItem->iRow, j, GVIS_READONLY);
		}
	}

	if (m_GridCtrl.GetItemText(pItem->iRow, pItem->iColumn) == "恒流恒压充电")
	{
		for (int j = 2; j < m_GridCtrl.GetColumnCount(); j++)
		{
			m_GridCtrl.SetItemText(pItem->iRow, j, _T("0"));
			//m_GridCtrl.SetItemState(pItem->iRow, j, GVIS_READONLY);
		}

		//m_GridCtrl.SetItemText(pItem->iRow, 5, _T(""));
		//m_GridCtrl.SetItemState(pItem->iRow, 5, GVIS_READONLY);
	}

	if (m_GridCtrl.GetItemText(pItem->iRow, pItem->iColumn) == "恒流充电")
	{
		for (int j = 2; j < m_GridCtrl.GetColumnCount(); j++)
		{
			m_GridCtrl.SetItemText(pItem->iRow, j, _T("0"));
			//m_GridCtrl.SetItemState(pItem->iRow, j, GVIS_READONLY);
		}

		//m_GridCtrl.SetItemText(pItem->iRow, 5, _T(""));
		//m_GridCtrl.SetItemState(pItem->iRow, 5, GVIS_READONLY);
	}

	if (m_GridCtrl.GetItemText(pItem->iRow, pItem->iColumn) == "恒流放电")
	{
		for (int j = 2; j < m_GridCtrl.GetColumnCount(); j++)
		{
			m_GridCtrl.SetItemText(pItem->iRow, j, _T("0"));
			//m_GridCtrl.SetItemState(pItem->iRow, j, GVIS_READONLY);
		}
		//m_GridCtrl.SetItemText(pItem->iRow, 4, _T(""));
		//m_GridCtrl.SetItemState(pItem->iRow, 4, GVIS_READONLY);
	}


	if (m_GridCtrl.GetItemText(pItem->iRow, pItem->iColumn) == "循环")
	{
		cycleLastStep = pItem->iRow - 1;
		
		//int rowIdx = pItem->iRow;
		//CString rowIdxStr;

		//rowIdxStr.Format(_T("%d"), rowIdx);
		//CString startStepParaStr = m_GridCtrl.GetItemText(rowIdx, START_STEP_PARAID2);
		//CString endStepParaStr = m_GridCtrl.GetItemText(rowIdx, END_CAPACITY_PARAID2);

		//int preCycleIdx = 0;
		//int errIdx = 0;
		//CString errIdxStr;
		//CString errStr = L"";

		//// 对第一行是否循环进行判断
		//if (rowIdx == 1)
		//{
		//	errIdxStr.Format(_T("%d"), ++errIdx);
		//	errStr += errIdxStr + L": 第1个工步不能设置为循环";
		//}

		//// 对两次循环过程中是否有交叉进行判断
		//for (int idx = rowIdx - 1; idx >= 1; ++idx)
		//{
		//	if (m_GridCtrl.GetItemText(rowIdx, STEP_PARAID2) == L"循环")
		//		preCycleIdx = idx;
		//}
		//if (!(StringUtils::IsValideInt(startStepParaStr)))
		//{
		//	errIdxStr.Format(_T("%d"), ++errIdx);
		//	errStr += errIdxStr + L": 第" + rowIdxStr + L"行起始工步参数属于必填项且必须为数字!\n";
		//}
		//if (!(StringUtils::IsValideInt(endStepParaStr)))
		//{
		//	errIdxStr.Format(_T("%d"), ++errIdx);
		//	errStr += errIdxStr + L": 第" + rowIdxStr + L"行终止工步参数属于必填项且必须为数字!\n";
		//}
		//int startStepParaVal = _ttoi(startStepParaStr);
		//int endStepParaVal = _ttoi(endStepParaStr);

		//if (preCycleIdx >= startStepParaVal)
		//{	
		//	errIdxStr.Format(_T("%d"), ++errIdx);
		//	errStr += errIdxStr + L"第" + rowIdxStr + L"行循环起始工步必须与上一次循环不产生工步重叠!\n";
		//}
		//// 对起始工步是否先于结束工步进行判断
		//if (startStepParaVal > endStepParaVal)
		//{
		//	errIdxStr.Format(_T("%d"), ++errIdx);
		//	errStr += errIdxStr + L"第" + rowIdxStr + L"行循环起始工步必须小于等于终止工步编码!\n";
		//}

		//if (errStr != L"")
		//{
		//	AfxMessageBox(errStr);
		//	errorFlag = FALSE;
		//	return;
		//}
		//else
		//{
			if (cycleDlg == NULL)
			{
				cycleDlg = new CSW_CycleDlg();
			}
			if (cycleDlg->DoModal() == IDOK)
			{
				int startStep = cycleDlg->startStep;
				int cycleTime = cycleDlg->cycleTime;
				CString tmp;
				m_GridCtrl.SetItemText(pItem->iRow, 2, _T("起始工步"));

				tmp.Format(_T("%d"), startStep);
				m_GridCtrl.SetItemText(pItem->iRow, 3, tmp);

				m_GridCtrl.SetItemText(pItem->iRow, 4, _T("终止工步"));

				tmp.Format(_T("%d"), pItem->iRow - 1);
				m_GridCtrl.SetItemText(pItem->iRow, 5, tmp);

				m_GridCtrl.SetItemText(pItem->iRow, 6, _T("循环次数"));
				tmp.Format(_T("%d"), cycleTime);
				m_GridCtrl.SetItemText(pItem->iRow, 7, tmp);

				m_GridCtrl.SetItemText(pItem->iRow, 8, _T(""));
				//m_GridCtrl.SetItemState(pItem->iRow, 8, GVIS_READONLY);
			}
			CCellID tmpCellID;
			m_GridCtrl.SetFocusCell(tmpCellID);
		}
	//}
	//if (errorFlag)
	UpdateWorkProcs(stepCabId);
	m_GridCtrl.Invalidate();
		

}
// GVN_SELCHANGING
void CStartWorkDlg::OnGridStartSelChange(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*)pNotifyStruct;
	beginSelRow = pItem->iRow;
	//Trace(_T("Start Selection Change on row %d, col %d (%d Selected)\n"),
	//	pItem->iRow, pItem->iColumn, m_Grid.GetSelectedCount());
}

// GVN_SELCHANGED
void CStartWorkDlg::OnGridEndSelChange(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*)pNotifyStruct;
	endSelRow = pItem->iRow;
	if (endSelRow >= 0)
	{
		if (endSelRow < beginSelRow)
		{
			int tmp = beginSelRow;			
			beginSelRow = endSelRow;
			endSelRow = tmp;
		}
	}
	UpdateWorkProcs(stepCabId);
	/*Trace(_T("End Selection Change on row %d, col %d (%d Selected)\n"),
		pItem->iRow, pItem->iColumn, m_Grid.GetSelectedCount());*/
}


//void CStartWorkDlg::OnSwRcAddonerow()
//{
//	// TODO:  在此添加命令处理程序代码
//	AddOneRow();
//}


//void CStartWorkDlg::OnSwRcAddmulrow()
//{
//	// TODO:  在此添加命令处理程序代码
//	AddMultiRow();
//}


//void CStartWorkDlg::OnSwRcDelonerow()
//{
//	// TODO:  在此添加命令处理程序代码
//	DelOneRow();
//}


//void CStartWorkDlg::OnSwRcDelmulrow()
//{
//	// TODO:  在此添加命令处理程序代码
//	DelMultiRow();
//}

void CStartWorkDlg::InitSpecCabInfoByPara()
{
	int cabId = stepCabId;
	wchar_t str[MAX_PATH_LENGTH];
	CString cabIdStr;
	_itow_s(cabId, str, INT_LENGTH);
	cabIdStr = str;

	cabSel.MoveWindow(cabRects[cabId - 1], TRUE);

	otherInitPath = CBatteryUtils::GetConfigPath(_T("\\config\\step\\") + cabIdStr + _T("\\other.ini"));

	//InitSpecStepInfoByFile(cabId,stepInitPath);
	InitSpecStepInfoByPara(cabId);
	InitOtherInfo(cabId, otherInitPath);			// 这个还是要从本地参数文件获取
	
}

void CStartWorkDlg::InitSpecCabInfoByFile(int cabId)
{

	wchar_t str[MAX_PATH_LENGTH];
	CString cabIdStr;
	_itow_s(cabId, str, INT_LENGTH);
	cabIdStr = str;

	cabSel.MoveWindow(cabRects[cabId - 1], TRUE);

	CString tmpPath = CBatteryUtils::GetConfigPath(_T("\\config\\step\\")
		+ cabIdStr + _T("\\preStepPath.ini"));
	GetPrivateProfileString(_T("stepFilePath"), _T("path"), _T("error"), str, MAX_PATH_LENGTH, tmpPath);
	stepInitPath = str;
	otherInitPath = CBatteryUtils::GetConfigPath(_T("\\config\\step\\") + cabIdStr + _T("\\other.ini"));

	InitSpecStepInfoByFile(cabId, stepInitPath);

	InitOtherInfo(cabId, otherInitPath);
}


void CStartWorkDlg::InitOtherInfo(int cabId, CString otherInitPath)
{
	CString cabIdStr;
	wchar_t str[MAX_PATH_LENGTH];

	_itow_s(cabId, str, INT_LENGTH);
	cabIdStr = str;

	batCapVal = GetPrivateProfileInt(_T("other"), _T("batCap"), 0, otherInitPath);
	warnCapVal = GetPrivateProfileInt(_T("other"), _T("warnCap"), 0, otherInitPath);
	vseperateVal = GetPrivateProfileInt(_T("other"), _T("vseperate"), 0, otherInitPath);
	vcycleVal = GetPrivateProfileInt(_T("other"), _T("vcycleNum"), 0, otherInitPath);
	stopStepNumVal = GetPrivateProfileInt(_T("other"), _T("stopStepNum"), 0, otherInitPath);
	stopCycleVal = GetPrivateProfileInt(_T("other"), _T("stopCycle"), 0, otherInitPath);
	vpointVal = GetPrivateProfileInt(_T("other"), _T("vpoint"), 0, otherInitPath);

	tpointVal = GetPrivateProfileInt(_T("other"), _T("tpoint"), 0, otherInitPath);
	featureVal1 = GetPrivateProfileInt(_T("other"), _T("feature1"), 0, otherInitPath);
	featureVal2 = GetPrivateProfileInt(_T("other"), _T("feature2"), 0, otherInitPath);
	featureVal3 = GetPrivateProfileInt(_T("other"), _T("feature3"), 0, otherInitPath);
	featureVal4 = GetPrivateProfileInt(_T("other"), _T("feature4"), 0, otherInitPath);
	featureVal5 = GetPrivateProfileInt(_T("other"), _T("feature5"), 0, otherInitPath);

	GetPrivateProfileString(_T("basepath"), _T("defBasePath"), _T("E:\battery"), str, MAX_PATH_LENGTH, cabInitPath);
	defaultBasePath = str;

	// defaultDbPath = defaultBasePath + _T("\\") + year_month + "\\" + day_time_cabId
	int year = nowTime.tm_year + 1900;
	int month = nowTime.tm_mon + 1;
	int day = nowTime.tm_mday;
	int hour = nowTime.tm_hour;
	int minute = nowTime.tm_min;
	int second = nowTime.tm_sec;

	CString yearStr, monthStr, dayStr, hourStr, minuteStr, secondStr;


	_itow_s(year, str, INT_LENGTH); yearStr = str;
	_itow_s(month, str, INT_LENGTH); monthStr = str; monthStr = month < 10 ? _T("0") + monthStr : monthStr;
	_itow_s(day, str, INT_LENGTH); dayStr = str; dayStr = day < 10 ? _T("0") + dayStr : dayStr;
	_itow_s(hour, str, INT_LENGTH); hourStr = str; hourStr = hour < 10 ? _T("0") + hourStr : hourStr;
	_itow_s(minute, str, INT_LENGTH); minuteStr = str; minuteStr = minute < 10 ? _T("0") + minuteStr : minuteStr;
	_itow_s(second, str, INT_LENGTH); secondStr = str; secondStr = second < 10 ? _T("0") + secondStr : secondStr;

	cabIdStr = cabId < 10 ? _T("0") + cabIdStr : cabIdStr;

	defaultDbPath = defaultBasePath + _T("\\") + timePath + cabIdStr;


	// 初始化相关标签
	((CButton *)GetDlgItem(IDC_RADIO_SW_VOLT))->SetCheck(vpointVal == 1 ? TRUE : FALSE);
	((CButton *)GetDlgItem(IDC_RADIO_SW_TIME))->SetCheck(tpointVal == 1 ? TRUE : FALSE);

	_itow_s(batCapVal, str, INT_LENGTH);
	batCapEdit.SetWindowTextW(str);

	_itow_s(warnCapVal, str, INT_LENGTH);
	warnCapEdit.SetWindowTextW(str);

	_itow_s(vseperateVal, str, INT_LENGTH);
	vseperateEdit.SetWindowTextW(str);

	_itow_s(vcycleVal, str, INT_LENGTH);
	vcycleEdit.SetWindowTextW(str);

	_itow_s(stopStepNumVal, str, INT_LENGTH);
	stopStepNumEdit.SetWindowTextW(str);

	_itow_s(stopCycleVal, str, INT_LENGTH);
	stopCycleEdit.SetWindowTextW(str);

	_itow_s(featureVal1, str, INT_LENGTH);
	featureEdit1.SetWindowTextW(str);

	_itow_s(featureVal2, str, INT_LENGTH);
	featureEdit2.SetWindowTextW(str);

	_itow_s(featureVal3, str, INT_LENGTH);
	featureEdit3.SetWindowTextW(str);

	_itow_s(featureVal4, str, INT_LENGTH);
	featureEdit4.SetWindowTextW(str);

	_itow_s(featureVal5, str, INT_LENGTH);
	featureEdit5.SetWindowTextW(str);

	dataFileEdit.SetWindowTextW(defaultDbPath);
	fileRemarkEdit.SetWindowTextW(fileRemarkVal);
}


void CStartWorkDlg::InitSpecStepInfoByFile(int cabId, CString filePath)
{
	std::ifstream in(filePath);
	
	if (in.is_open())
	{
		// 初始化工序类
		if (workProcs[cabId - 1] == NULL)
			workProcs[cabId - 1] = new CWorkProc();
		else
		{
			delete workProcs[cabId - 1];
			workProcs[cabId - 1] = new CWorkProc();
		}

		string line;
		int nRow, nCol;
		// 文件第一行为工步名称
		// 第二行为型号
		//文件第三行为表格行数，第四行为表格列数
		CWorkProc *workProc = (CWorkProc*)workProcs[cabId - 1];
		getline(in, line);
		workProcVal= line.c_str();
		workProcEdit.SetWindowTextW(workProcVal);
		workProc->workProcName = workProcVal;

		getline(in, line);
		modelVal = line.c_str();
		modelEdit.SetWindowTextW(modelVal);
		workProc->model = modelVal;
		
		getline(in, line);
		nRow = std::stoi(line);
		getline(in, line);
		nCol = std::stoi(line);

		if (nRow - m_GridCtrl.GetRowCount() > 0){
			int tmp_RowCount = m_GridCtrl.GetRowCount();
			for (int i = 0; i < nRow - tmp_RowCount; ++i)
			{
				AddOneRow();
			}
		}

		GV_ITEM Item;
		Item.mask = GVIF_TEXT | GVIF_FORMAT;
		
		CWorkStep workStep;
		for (int i = 1; i < nRow; ++i)
		{
			getline(in, line);
			int spaceidx = 0;

			//  如果stepName 有效 则继续，首先寻找StepName
			CString stepName((line.substr(0, line.find(' '))).c_str());
			BOOL valideStepFlag = FALSE;

			COLORREF stepColor = defaultStepColor;	
			for (int j = 0; j < stepNames.size(); ++j)
			{
				if (stepNames[j] == stepName)
				{
					stepColor = stepColors[j];
					valideStepFlag = TRUE;
					workProc->stepNum++;
					workStep.stepId = i;
					workStep.workStepName = stepName;
					workStep.isValide = TRUE;
					break;
				}
			}
			if (!valideStepFlag)
				break;
			for (int j = 1; j < nCol-1; j++)
			{
				spaceidx = line.find(' ');
				int len = line.length();
				string tmp = line.substr(0, spaceidx);
				CString ctmp(tmp.c_str());
				ctmp = ctmp == DEFAULT_PATA_STR ? L"" : ctmp;
				Item.row = i;
				Item.col = j;
				Item.strText.Format(ctmp);
				Item.crBkClr = stepColor;
				Item.crFgClr = stepColor;
				
				m_GridCtrl.SetItem(&Item);
				m_GridCtrl.SetItemText(i, j, ctmp);
				line = line.substr(spaceidx + 1, len - spaceidx - 1);

				UpdateWorkStep(workStep, ctmp, j);
			}

			CString ctmp(line.c_str());
			ctmp = ctmp == DEFAULT_PATA_STR ? L"" : ctmp;

			Item.row = i;
			Item.col = nCol - 1;
			Item.strText.Format(ctmp);
			m_GridCtrl.SetItem(&Item);
			m_GridCtrl.SetItemText(i, nCol-1, ctmp);
			UpdateWorkStep(workStep, ctmp, nCol-1);

			workProc->workSteps.push_back(workStep);
		}
		updateGridStatus();
		m_GridCtrl.Invalidate();

		return;
	}
}

void CStartWorkDlg::OnBnClickedBtnSwOpenproc()
{
	// TODO:  在此添加控件通知处理程序代码
	BOOL isOpen = TRUE;
	CString defaultDirPath = CBatteryUtils::GetConfigPath(_T("\\config\\step\\procPath.ini"));
	// 从procPath获取默认路径
	wchar_t pathStr[MAX_PATH_LENGTH+1];
	CString defaultDir;
	GetPrivateProfileString(_T("openPath"), _T("path"), _T("D:\\"), pathStr, MAX_PATH_LENGTH, defaultDirPath);
	//sprintf_s(defaultDir.GetBuffer(MAX_PATH_LENGTH), "%ws", pathStr);
	defaultDir = pathStr;

	CString fileName = L"";
	CString filter = L"文件(*.txt)|*.txt||";
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_READONLY, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = defaultDir;
	CString filePath;

	if (openFileDlg.DoModal() == IDOK)
	{
		filePath = openFileDlg.GetPathName();
	}
	else
	{
		return;
	}
	if (workProcs[stepCabId - 1] != NULL)
	{
		delete (CWorkProc *)workProcs[stepCabId - 1];
		workProcs[stepCabId - 1] = NULL;
		workProcs[stepCabId - 1] = new CWorkProc();
	}
	std::ifstream in(filePath);
	if (in.is_open())
	{
		string line;
		int nRow, nCol;
		CWorkProc *workProc = (CWorkProc*)workProcs[stepCabId - 1];
		// 文件第一行为工步名称
		// 第二行为型号
		//文件第三行为表格行数，第四行为表格列数
		getline(in, line);
		workProcVal = line.c_str();
		workProcEdit.SetWindowTextW(workProcVal);
		workProc->workProcName = workProcVal;

		getline(in, line);
		modelVal = line.c_str();
		modelEdit.SetWindowTextW(modelVal);
		workProc->model = modelVal;

		getline(in, line);
		nRow = std::stoi(line);
		getline(in, line);
		nCol = std::stoi(line);

		
		if (nRow - m_GridCtrl.GetRowCount() > 0){
			int tmp_RowCount = m_GridCtrl.GetRowCount();
			for (int i = 0; i < nRow - tmp_RowCount; ++i)
			{
				AddOneRow();
			}
		}
		
		CWorkStep workStep;
		GV_ITEM Item;
		Item.mask = GVIF_TEXT | GVIF_FORMAT;
		for (int i = 1; i < nRow; ++i)
		{
			getline(in, line);
			int spaceidx = 0;
			CString stepName((line.substr(0, line.find(' '))).c_str());
			BOOL valideStepFlag = FALSE;

			for (int j = 0; j < stepNames.size(); ++j)
			{
				if (stepNames[j] == stepName)
				{
					valideStepFlag = TRUE;
					workProc->stepNum++;
					workStep.stepId = i;
					workStep.workStepName = stepName;
					workStep.isValide = TRUE;
					break;
				}
			}
			if (!valideStepFlag)
				break;

			for (int j = 1; j < nCol - 1; j++)
			{
				spaceidx = line.find(' ');
				int len = line.length();

				string tmp = line.substr(0, spaceidx);
				CString ctmp(tmp.c_str());
				ctmp = ctmp == MAX_GRID_ITEM_CSTR ? L"" : ctmp;

				Item.row = i;
				Item.col = j;
				Item.strText.Format(ctmp);
				m_GridCtrl.SetItem(&Item);
				line = line.substr(spaceidx + 1, len - spaceidx - 1);

				UpdateWorkStep(workStep, ctmp, j);
			}

			CString ctmp(line.c_str());
			Item.row = i;
			Item.col = nCol - 1;
			Item.strText.Format(ctmp);
			m_GridCtrl.SetItem(&Item);

			UpdateWorkStep(workStep, ctmp, nCol - 1);
			workProc->workSteps.push_back(workStep);

		}

		updateGridStatus();
		m_GridCtrl.Invalidate();
		return;
	}
}


void CStartWorkDlg::OnBnClickedBtnSwSaveproc()
{
	// TODO:  在此添加控件通知处理程序代码
	//(1) 校验
	CString checkResult = CheckGrid();
	if (checkResult != L"")
	{
		AfxMessageBox(checkResult);
		return;
	}
	
	BOOL isOpen = FALSE;
	CString defaultDir = L"C:\\";
	workProcEdit.GetWindowTextW(workProcVal);
	CString fileName = workProcVal + L".txt";
	CString filter = L"文件(*.txt)|*.txt||";
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = L"C:\\test.txt";
	CString filePath = defaultDir + fileName;
	if (openFileDlg.DoModal() == IDOK)
	{
		filePath = openFileDlg.GetPathName();
	}
	else
	{
		return;
	}
	std::wofstream out(filePath);
	if (out.is_open())
	{
		int nRow = m_GridCtrl.GetRowCount();
		int nCol = m_GridCtrl.GetColumnCount();

		CString str;
		GV_ITEM Item;
		Item.mask = GVIF_TEXT | GVIF_FORMAT;

		workProcEdit.GetWindowTextW(workProcVal);
		modelEdit.GetWindowTextW(modelVal);

		out << CT2A(workProcVal) << std::endl;
		out << CT2A(modelVal) << std::endl;
		out << nRow << std::endl;
		out << nCol << std::endl;
		for (int i = 1; i < nRow; ++i)
		{
			for (int j = 1; j < nCol - 1; ++j)
			{
				str = m_GridCtrl.GetItemText(i, j);
				//http://stackoverflow.com/questions/5550838/how-to-convert-cstring-to-ofstream
				str = str == L"" ? DEFAULT_PATA_STR : str;
				out << CT2A(str) << " ";
			}
			str = m_GridCtrl.GetItemText(i, nCol - 1);
			str = str == L""? DEFAULT_PATA_STR : str;
			out << CT2A(str) << endl;
		}
		out.close();
	}
	CString cabIdStr = (LPCTSTR)cabIds[stepCabId - 1];
	CString preCabPath = CBatteryUtils::GetConfigPath(
		_T("\\config\\step\\") + cabIdStr + _T("\\preStepPath.ini"));
	CString curCabPath;

	WritePrivateProfileString(_T("stepFilePath"), _T("path"), filePath, preCabPath);
}


void CStartWorkDlg::OnBnClickedBtnSwCopyparameter()
{
	// TODO:  在此添加控件通知处理程序代码
	if (NULL == cpDlg)
	{
		cpDlg = new CSW_CopyParameterDlg();
	}
	cpDlg->DoModal();
}


void CStartWorkDlg::OnBnClickedBtnSwBatteryNum()
{

	// TODO:  在此添加控件通知处理程序代码
	if (NULL == numberingDlg)
	{
		numberingDlg = new CSW_NumberingDlg();
	}
	numberingDlg->DoModal();

}


void CStartWorkDlg::OnBnClickedBtnSwSend()
{
	// TODO:  在此添加控件通知处理程序代码
	if (NULL == sendDlg)
	{
		sendDlg = new CSW_SendDlg();
	}
	sendDlg->DoModal();
}



void CStartWorkDlg::OnNMClickCabLink1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	stepCabId = 1;
	InitSpecCabInfoByPara();
}


void CStartWorkDlg::OnNMClickCabLink2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	stepCabId = 2;
	InitSpecCabInfoByPara();
}


void CStartWorkDlg::OnNMClickCabLink3(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	stepCabId = 3;
	InitSpecCabInfoByPara();
}


void CStartWorkDlg::OnNMClickCabLink4(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	stepCabId = 4;
	InitSpecCabInfoByPara();
}


void CStartWorkDlg::OnNMClickCabLink5(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	stepCabId = 5;

	InitSpecCabInfoByPara();

}


void CStartWorkDlg::OnNMClickCabLink6(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	stepCabId = 6;
	InitSpecCabInfoByPara();
}


void CStartWorkDlg::OnNMClickCabLink7(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	stepCabId = 7;
	InitSpecCabInfoByPara();
}


void CStartWorkDlg::OnNMClickCabLink8(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	stepCabId = 8;
	InitSpecCabInfoByPara();
}


void CStartWorkDlg::OnNMClickCabLink9(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	stepCabId = 9;
	InitSpecCabInfoByPara();
}


void CStartWorkDlg::OnNMClickCabLink10(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	stepCabId = 10;
	InitSpecCabInfoByPara();
}


void CStartWorkDlg::OnNMClickCabLink11(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	stepCabId = 11;
	InitSpecCabInfoByPara();
}


void CStartWorkDlg::OnNMClickCabLink12(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	stepCabId = 12;
	InitSpecCabInfoByPara();
}


void CStartWorkDlg::OnNMClickCabLink13(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	stepCabId = 13;
	InitSpecCabInfoByPara();
}


void CStartWorkDlg::OnNMClickCabLink14(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	stepCabId = 14;
	InitSpecCabInfoByPara();
}


void CStartWorkDlg::OnNMClickCabLink15(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	stepCabId = 15;
	InitSpecCabInfoByPara();
}


void CStartWorkDlg::OnNMClickCabLink16(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	stepCabId = 16;
	InitSpecCabInfoByPara();
}


void CStartWorkDlg::OnNMClickCabLink17(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	stepCabId = 17;
	InitSpecCabInfoByPara();
}


void CStartWorkDlg::OnNMClickCabLink18(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	stepCabId = 18;
	InitSpecCabInfoByPara();
}


void CStartWorkDlg::OnNMClickCabLink19(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	stepCabId = 19;
	InitSpecCabInfoByPara();
}


void CStartWorkDlg::OnNMClickCabLink20(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	stepCabId = 20;
	InitSpecCabInfoByPara();
}


BOOL CStartWorkDlg::CreateDatabase(CString dbNameStr)
{
	CString dbCatagory;
	int catagoryIdx = dbNameStr.ReverseFind('\\');
	dbCatagory = dbNameStr.Left(catagoryIdx + 1);

	if (!CFileUtils::CreateMuliteDirectory(dbCatagory))
		return FALSE;

	CString mdbConnStr = _T("Provider='Microsoft.JET.OLEDB.4.0';Data source = ") + dbNameStr;
	
	//CString mdbConnStr = _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=E:\\database\\battery\\BatteryManage2.mdb");
	try
	{
		HRESULT hr = S_OK;
		_CatalogPtr pCatalog = NULL;
		_bstr_t cnnstring(mdbConnStr);

		TESTHR(hr = pCatalog.CreateInstance(__uuidof (Catalog)));
		pCatalog->Create(cnnstring);
	}
	catch (_com_error e)
	{
		_bstr_t bstrDescription(e.Description());
		CString strErro = CString(_T("创建ACCEESS数据库出错: "))
			+ (LPCSTR)e.Description()
			+ CString(_T("Create ACCESS DB error: "))
			+ (LPCSTR)e.Description();
		AfxMessageBox(strErro);
		return FALSE;
	}
	::CoUninitialize();
	return TRUE;
}



BOOL CStartWorkDlg::CreateDbTables(CString dbNameStr)
{
	if (!ConnectToDatabase(dbNameStr))
		return FALSE;
	CDbSql *dbSql = CDbSql::GetInstance();
	if (!CreateTable(dbNameStr, _T("TEST_INFO"), dbSql->createTestInfoStr))
	{
		return FALSE;
	}
	if (!CreateTable(dbNameStr, _T("CHANNEL_STEP"), dbSql->createChlStepStr))
	{
		return FALSE;
	}
	if (!CreateTable(dbNameStr, _T("CHANNEL_INFO"), dbSql->createChlInfoStr))
	{
		return FALSE;
	}
	if (!CreateTable(dbNameStr, _T("CHANNEL_CURVE"), dbSql->createChlCurveStr))
	{
		return FALSE;
	}
	if (!CreateTable(dbNameStr, _T("WORKPROC_INFO"), dbSql->createWorkProcStr))
	{
		return TRUE;
	}
	return TRUE;
}

BOOL CStartWorkDlg::ConnectToDatabase(CString dbNameStr)
{
	_bstr_t sqlStr = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" +
		(_bstr_t)dbNameStr;
	try
	{
		//先创建连接实例
		HRESULT hr = pConnection.CreateInstance(__uuidof(Connection));//创建Connection对象
		if (SUCCEEDED(hr))
		{
			// 打开本地Access库Demo.mdb
			hr = pConnection->Open(sqlStr, "", "", adModeUnknown);
			return TRUE;
		}
	}
	catch (_com_error e)///捕捉异常
	{
		CString strMsg;
		strMsg.Format(_T("错误描述：%s\n错误消息%s"),
			(LPCTSTR)e.Description(),
			(LPCTSTR)e.ErrorMessage());
		AfxMessageBox(strMsg);
		return FALSE;
	}
	return FALSE;
}

BOOL CStartWorkDlg::CreateTable(CString dbNameStr, CString tableNameStr, CString &createTestInfoStr)
{
	CString strConn;
	if (tableNameStr != _T("") && dbNameStr != _T(""))
	{
		_CatalogPtr m_pCatalog = NULL;
		_TablePtr m_pTable = NULL;
		dbNameStr = _T("Provider='Microsoft.JET.OLEDB.4.0';Data source = ") + dbNameStr;

		try
		{
			m_pCatalog.CreateInstance(__uuidof(Catalog));
			m_pCatalog->PutActiveConnection(_bstr_t(dbNameStr));
			int tableCount = m_pCatalog->Tables->Count;
			int i = 0;
			while (i<tableCount)
			{
				m_pTable = (_TablePtr)m_pCatalog->Tables->GetItem((long)i);
				CString tableName = (wchar_t *)_bstr_t(m_pTable->Name);
				if (tableName == tableNameStr)
				{
					AfxMessageBox(_T("该表已经存在!"));
					return FALSE;
				}
				i++;
			}
		}
		catch (_com_error &e)
		{
			return FALSE;
		}

		_ConnectionPtr m_pConnection;
		_variant_t RecordsAffected;
		try
		{
			m_pConnection.CreateInstance(__uuidof(Connection));


			m_pConnection->Open((_bstr_t)dbNameStr, "", "", adModeUnknown);
		}
		catch (_com_error e)
		{
			CString errormessage;
			errormessage.Format(_T("连接数据库失败!\r错误信息:%s"), e.ErrorMessage());
			AfxMessageBox(errormessage);
			return FALSE;
		}
		try
		{
			m_pConnection->Execute(_bstr_t(createTestInfoStr), &RecordsAffected, adCmdText);
			if (m_pConnection->State)
				m_pConnection->Close();
		}
		catch (_com_error &e)
		{
			AfxMessageBox(e.Description());
			return FALSE;
		}
	}
	return TRUE;
}

void CStartWorkDlg::InitGrid()
{
	//初始化参数

	beginSelRow = -1;
	endSelRow = -1;

	m_GridCtrl.SetEditable(true);
	//m_GridCtrl.SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));//黄色背景
	//初始化列表，设定初始行列数，以及冻结的行列数
	m_GridCtrl.SetRowCount(8);
	m_GridCtrl.SetColumnCount(9);
	m_GridCtrl.SetFixedRowCount(1);
	m_GridCtrl.SetFixedColumnCount(1);
	//初始化表头首行
	for (int i_col = 0; i_col < m_GridCtrl.GetColumnCount(); i_col++){
		GV_ITEM Item;
		Item.mask = GVIF_TEXT | GVIF_FORMAT;
		Item.row = 0;
		Item.col = i_col;

		m_GridCtrl.SetRowHeight(0, GRID_ROW_HEIGHT); //设置各行高      
		m_GridCtrl.SetColumnWidth(i_col, 100); //设置各列宽
		Item.nFormat = DT_CENTER | DT_WORDBREAK;
		switch (i_col){
		case 0:
			Item.strText.Format(_T("工步号")); break;
		case 1:
			Item.strText.Format(_T("工作状态")); break;
		case 2:
			Item.strText.Format(_T("时间")); break;
		case 3:
			Item.strText.Format(_T("电流")); break;
		case 4:
			Item.strText.Format(_T("上限电压")); break;
		case 5:
			Item.strText.Format(_T("下限电压")); break;
		case 6:
			Item.strText.Format(_T("△v（mv）")); break;
		case 7:
			Item.strText.Format(_T("终止电流")); break;
		case 8:
			Item.strText.Format(_T("终止容量")); break;
		default:
			Item.strText.Format(_T("ddd")); break;
		}
		m_GridCtrl.SetItem(&Item);
	}
	for (int row = 1; row < m_GridCtrl.GetRowCount(); row++)
	for (int col = 0; col < m_GridCtrl.GetColumnCount(); col++)
	{
		//设置表格显示属性
		GV_ITEM Item;
		Item.mask = GVIF_TEXT | GVIF_FORMAT;
		Item.row = row;
		Item.col = col;

		m_GridCtrl.SetRowHeight(row, GRID_ROW_HEIGHT); //设置各行高   
		if (col == 1)
			m_GridCtrl.SetColumnWidth(col, GRID_SEL_WIDTH); //设置1列宽 
		else
			m_GridCtrl.SetColumnWidth(col, GRID_COL_WIDTH);

		if (col < 1)
		{
			//添加工序号
			Item.nFormat = DT_CENTER | DT_WORDBREAK;
			Item.strText.Format(_T("%d"), row);
		}
		else if (col < 2)
		{
			//添加下拉选项
			//m_GridCtrl.SetCellType(row, col, RUNTIME_CLASS(CGridCell));
			//m_GridCtrl.Invalidate();
			m_GridCtrl.SetCellType(row, col, RUNTIME_CLASS(CGridCellCombo));
			CStringArray options;
			options.Add(_T("恒流恒压充电"));
			options.Add(_T("恒流充电"));
			options.Add(_T("恒流放电"));
			options.Add(_T("搁置"));
			options.Add(_T("结束"));
			options.Add(_T("循环"));
			CGridCellCombo *pCell = (CGridCellCombo*)m_GridCtrl.GetCell(row, col);
			pCell->SetOptions(options);
			pCell->SetStyle(CBS_DROPDOWN);

			continue;
		}
		else{
			//添加普通空项
			Item.nFormat = DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;
			Item.strText.Format(_T(""), 2);
		}
		m_GridCtrl.SetItem(&Item);
	}
	m_GridCtrl.Invalidate();
}

void CStartWorkDlg::updateGridStatus()
{
	CWorkProc *workProc = workProcs[stepCabId - 1];
	if (workProc == NULL) return;

	m_GridCtrl.SetRowCount(workProc->stepNum + 1);
	if (m_GridCtrl.GetRowCount() < 2) return;	

	int idx_col = 1;
	
	for (int i_row = 1; i_row <= workProc->stepNum; ++i_row){
		//MessageBox(m_GridCtrl.GetItemText(i_row, idx_col));
		CString workStepName = m_GridCtrl.GetItemText(i_row, 1);
		//if (workProc->workSteps[i_row-1].workStepName == L"结束")
		if (workStepName == L"结束")
		{
			int del_number = m_GridCtrl.GetRowCount() - (i_row + 1);
			for (int i = 0; i < del_number; ++i)
			{
				m_GridCtrl.DeleteRow(m_GridCtrl.GetRowCount() - 1);
				m_GridCtrl.Invalidate();
			}
			updateAllRow();
			//这一行的所有单元格变不能编辑
			for (int j = 2; j < m_GridCtrl.GetColumnCount(); j++)
			{
				m_GridCtrl.SetItemText(i_row, j, _T(""));
				//m_GridCtrl.SetItemState(i_row, j, GVIS_READONLY);
			}
		}
		else if (workStepName == L"搁置")
		{
			//这一行的所有单元格变不能编辑，并且清空，保留时间
			for (int j = 3; j < m_GridCtrl.GetColumnCount(); j++)
			{
				m_GridCtrl.SetItemText(i_row, j, _T(""));
				//m_GridCtrl.SetItemState(i_row, j, GVIS_READONLY);
			}
		}
		else if (workStepName == L"恒流恒压充电")
		{
			m_GridCtrl.SetItemText(i_row, 5, _T(""));
			//m_GridCtrl.SetItemState(i_row, 5, GVIS_READONLY);
		}
		else if (workStepName == L"恒流充电")
		{
			m_GridCtrl.SetItemText(i_row, 5, _T(""));
			//m_GridCtrl.SetItemState(i_row, 5, GVIS_READONLY);
		}
		else if (workStepName == L"恒流放电")
		{
			m_GridCtrl.SetItemText(i_row, 4, _T(""));
			//m_GridCtrl.SetItemState(i_row, 4, GVIS_READONLY);
		}
		else if (workStepName == L"循环")
		{
			m_GridCtrl.SetItemText(i_row, 8, _T(""));
			//m_GridCtrl.SetItemState(i_row, 8, GVIS_READONLY);
			//m_GridCtrl.Invalidate();	
		}
		else
		{
		}
		
	}
	m_GridCtrl.Invalidate();

}

void CStartWorkDlg::DelRow()
{
	endSelRow = m_GridCtrl.GetCellRange().GetMaxRow() - 1;
	if (endSelRow == -1){
		if (beginSelRow >= 0)
		{
			m_GridCtrl.DeleteRow(beginSelRow);
			m_GridCtrl.Invalidate();
		}
	}
	else{
		int delNum = endSelRow - beginSelRow + 1;
		for (int i = 0; i < delNum; ++i)
		{
			m_GridCtrl.DeleteRow(beginSelRow);
			m_GridCtrl.Invalidate();
		}
	}

	UpdateWorkProcs(stepCabId);

	updateAllRow();

	m_GridCtrl.Invalidate();

}

void CStartWorkDlg::OnBnClickedCreateDatabase()
{
	// TODO:  在此添加控件通知处理程序代码
	CString dbNameStr;
	dataFileEdit.GetWindowTextW(dbNameStr);
	dbNameStr += _T(".mdb");
	CString dbSqlPath = _T("");
	
	if (!CreateDatabase(dbNameStr))
	{
		MessageBox(_T("创建数据库文件") + dbNameStr + _T("失败!"));
		return;
	}
	if (!CreateDbTables(dbNameStr))
	{
		MessageBox(_T("创建数据库表失败!"));
	}
		
	pConnection->Close();
	::CoUninitialize();
	
	return;
}
void CStartWorkDlg::m_GridCopyRow()
{	
	m_GridPasteBoard.clear();//清空剪贴板
	
	if (endSelRow == -1)
	{
		std::vector<CString> in;
		for (int j = 1; j < m_GridCtrl.GetColumnCount(); ++j)
		{
			CString tmp;
			tmp = m_GridCtrl.GetItemText(beginSelRow, j);
			in.push_back(tmp);
		}
		m_GridPasteBoard.push_back(in);
	}
	else
	{
		std::vector<CString> in;
		for (int i = beginSelRow; i <= endSelRow; ++i)
		{
			in.clear();
			for (int j = 1; j < m_GridCtrl.GetColumnCount(); ++j)
			{
				CString tmp;
				tmp = m_GridCtrl.GetItemText(i, j);
				in.push_back(tmp);
			}
			m_GridPasteBoard.push_back(in);
		}
	}
	GridCopyFlag = TRUE;
	GridCutFlag = FALSE;
}

void CStartWorkDlg::m_GridPasteRow()
{	
	int addRowNum = m_GridPasteBoard.size() - (m_GridCtrl.GetRowCount() - beginSelRow);
	
	if (addRowNum > 0)
	{
		for (int i = 0; i < addRowNum; ++i)
		{
			m_InsertRow(m_GridCtrl.GetRowCount() - 1);
		}
	}

	std::vector<CString> out;
	for (int j = 0; j < m_GridPasteBoard.size(); ++j)
	{
		out.clear();
		out = m_GridPasteBoard.at(j);
		for (int idx_col = 0; idx_col < out.size(); idx_col++)
		{
			m_GridCtrl.SetItemText(beginSelRow + j, idx_col + 1, out.at(idx_col));
			//m_GridCtrl.SetItemText(beginSelRow + j, idx_col + 1, L"123");
		}
	}
	updateGridStatus();
	if (GridCutFlag)
	{
		m_GridPasteBoard.clear();//清空剪贴板
		GridCutFlag = FALSE;
	}

}

void CStartWorkDlg::m_GridCutRow()
{
	m_GridPasteBoard.clear();//清空剪贴板

	if (endSelRow == -1)
	{
		std::vector<CString> in;
		for (int j = 1; j < m_GridCtrl.GetColumnCount(); ++j)
		{
			CString tmp;
			tmp = m_GridCtrl.GetItemText(beginSelRow, j);
			in.push_back(tmp);
			m_GridCtrl.SetItemText(beginSelRow, j, _T(""));
		}
		m_GridPasteBoard.push_back(in);
	}
	else
	{
		std::vector<CString> in;

		for (int i = beginSelRow; i <= endSelRow; ++i)
		{
			in.clear();
			for (int j = 1; j < m_GridCtrl.GetColumnCount(); ++j)
			{
				CString tmp;
				tmp = m_GridCtrl.GetItemText(i, j);
				in.push_back(tmp);
				m_GridCtrl.SetItemText(i, j, _T(""));
			}
			m_GridPasteBoard.push_back(in);
		}
		for (int i = beginSelRow; i <= endSelRow; ++i)
		{
			m_GridCtrl.DeleteRow(beginSelRow);
		}
		updateAllRow();
	}


	UpdateWorkProcs(stepCabId);
	m_GridCtrl.Invalidate();

	GridCopyFlag = FALSE;
	GridCutFlag = TRUE;
}


void CStartWorkDlg::OnBnClickedBtnSwClose()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialog::OnOK();
}



afx_msg LRESULT CStartWorkDlg::OnCloseStartDlg(WPARAM wParam, LPARAM lParam)
{
	
	CDialog::OnOK();
	theApp.OnBatteryConn();

	return 0;

}

CString CStartWorkDlg::CheckGrid()
{
	CString checkResultStr = L"";

	int rowIdx, colIdx;
	int errIdx = 0;
	CString errIdxStr, rowIdxStr;
	for (rowIdx = 1; rowIdx < m_GridCtrl.GetRowCount(); ++rowIdx)
	{
		rowIdxStr.Format(_T("%d"), rowIdx);
		CString stepParaStr = m_GridCtrl.GetItemText(rowIdx, STEP_PARAID2);
		CString timeParaStr = m_GridCtrl.GetItemText(rowIdx, TIME_PARAID2);
		CString currentParaStr = m_GridCtrl.GetItemText(rowIdx, CURRENT_PARAID2);
		CString maxVoltParaStr = m_GridCtrl.GetItemText(rowIdx, MAX_VOLT_PARAID2);
		CString minVoltParaStr = m_GridCtrl.GetItemText(rowIdx, MIN_VOLT_PARAID2);
		CString deltaVoltParaStr = m_GridCtrl.GetItemText(rowIdx, DELTA_VOLT_PARAID2);
		CString endCurrentParaStr = m_GridCtrl.GetItemText(rowIdx, END_CURRENT_PARAID2);
		CString endCapacityParaStr = m_GridCtrl.GetItemText(rowIdx, END_CAPACITY_PARAID2);

		if (rowIdx == 1)
		{
			if ( stepParaStr == L"结束")
			{
				errIdx++;
				errIdxStr.Format(_T("%d"), errIdx);
				checkResultStr += errIdxStr + L": 工序不能为空!\n";
			}
			else if (stepParaStr == L"循环")
			{
				errIdx++;
				errIdxStr.Format(_T("%d"), errIdx);
				checkResultStr += errIdxStr + L": 第一个工步不能是循环!\n";
			}
			else if (stepParaStr == L"恒流放电")
			{
				errIdx++;
				errIdxStr.Format(_T("%d"), errIdx);
				checkResultStr += errIdxStr + L": 不是分容工艺是否重新设置!\n";
			}
			else if (stepParaStr == L"恒流恒压充电")
			{
				if (!(StringUtils::IsValideInt(timeParaStr)))
				{
					errIdx++;
					errIdxStr.Format(_T("%d"), errIdx);
					checkResultStr += errIdxStr + L": 第" + rowIdxStr + L"行时间参数属于必填项且必须为数字!\n";
				}
				if (!(StringUtils::IsValideInt(currentParaStr)))
				{
					errIdx++;
					errIdxStr.Format(_T("%d"), errIdx);
					checkResultStr += errIdxStr + L": 第" + rowIdxStr + L"行电流参数属于必填项且必须为数字!\n";
				}
				if (!(StringUtils::IsValideInt(maxVoltParaStr)))
				{
					errIdx++;
					errIdxStr.Format(_T("%d"), errIdx);
					checkResultStr += errIdxStr + L": 第" + rowIdxStr + L"行上限电压参数属于必填项且必须为数字!\n";
				}
				if (!(StringUtils::IsValideInt(endCurrentParaStr)))
				{
					errIdx++;
					errIdxStr.Format(_T("%d"), errIdx);
					checkResultStr += errIdxStr + L": 第" + rowIdxStr + L"行终止电流参数属于必填项且必须为数字!\n";
				}
			}
			else if (stepParaStr == L"搁置")
			{
				if (!(StringUtils::IsValideInt(timeParaStr)))
				{
					errIdx++;
					errIdxStr.Format(_T("%d"), errIdx);
					checkResultStr += errIdxStr + L": 第" + rowIdxStr + L"行时间参数属于必填项且必须为数字!\n";
				}
			}
			else if (stepParaStr == L"恒流充电")
			{
				if (!(StringUtils::IsValideInt(timeParaStr)))
				{
					errIdx++;
					errIdxStr.Format(_T("%d"), errIdx);
					checkResultStr += errIdxStr + L": 第" + rowIdxStr + L"行时间参数属于必填项且必须为数字!\n";
				}
				if (!(StringUtils::IsValideInt(currentParaStr)))
				{
					errIdx++;
					errIdxStr.Format(_T("%d"), errIdx);
					checkResultStr += errIdxStr + L": 第" + rowIdxStr + L"行电流参数属于必填项且必须为数字!\n";
				}
				if (!(StringUtils::IsValideInt(maxVoltParaStr)))
				{
					errIdx++;
					errIdxStr.Format(_T("%d"), errIdx);
					checkResultStr += errIdxStr + L": 第" + rowIdxStr + L"行上限电压参数属于必填项且必须为数字!\n";
				}
			}
			else if (stepParaStr == L"")
			{
				errIdx++;
				errIdxStr.Format(_T("%d"), errIdx);
				checkResultStr += errIdxStr + L": 第" + rowIdxStr + L"行工步类型不能为空!\n";
			}
		}
		else
		{
			if (stepParaStr == L"循环")
			{
				CString startStepParaStr = m_GridCtrl.GetItemText(rowIdx, START_STEP_PARAID2);
				CString endStepParaStr = m_GridCtrl.GetItemText(rowIdx, END_STEP_PARAID2);

				int preCycleIdx = 0;
				
				for (int idx = rowIdx - 1; idx >= 1; --idx)
				{
					if (m_GridCtrl.GetItemText(idx, STEP_PARAID2) == L"循环")
						preCycleIdx = idx;
				}
				
				if (!(StringUtils::IsValideInt(startStepParaStr)))
				{
					errIdx++;
					errIdxStr.Format(_T("%d"), errIdx);
					checkResultStr += errIdxStr + L": 第" + rowIdxStr + L"行起始工步参数属于必填项且必须为数字!\n";
				}
				if (!(StringUtils::IsValideInt(endStepParaStr)))
				{
					errIdx++;
					errIdxStr.Format(_T("%d"), errIdx);
					checkResultStr += errIdxStr + L": 第" + rowIdxStr + L"行终止工步参数属于必填项且必须为数字!\n";
				}
				int startStepParaVal = _ttoi(startStepParaStr);
				int endStepParaVal = _ttoi(endStepParaStr);

				if (preCycleIdx >= startStepParaVal)
				{
					errIdxStr.Format(_T("%d"), ++errIdx);
					checkResultStr += errIdxStr + L": 第" + rowIdxStr + L"行循环起始工步必须与上一次循环不产生工步重叠!\n";
				}

				if (startStepParaVal > endStepParaVal)
				{
					errIdxStr.Format(_T("%d"), ++errIdx);
					checkResultStr += errIdxStr + L": 第" + rowIdxStr + L"行循环起始工步必须小于终止工步编码!\n";
				}
			}
			else if (stepParaStr == L"恒流放电")
			{
				if (!(StringUtils::IsValideInt(timeParaStr)))
				{
					errIdx++;
					errIdxStr.Format(_T("%d"), errIdx);
					checkResultStr += errIdxStr + L": 第" + rowIdxStr + L"行时间参数属于必填项且必须为数字!\n";
				}
				if (!(StringUtils::IsValideInt(currentParaStr)))
				{
					errIdx++;
					errIdxStr.Format(_T("%d"), errIdx);
					checkResultStr += errIdxStr + L": 第" + rowIdxStr + L"行电流参数属于必填项且必须为数字!\n";
				}
				if (!(StringUtils::IsValideInt(minVoltParaStr)))
				{
					errIdx++;
					errIdxStr.Format(_T("%d"), errIdx);
					checkResultStr += errIdxStr + L": 第" + rowIdxStr + L"行下限电压参数属于必填项且必须为数字!\n";
				}
			}
			else if (stepParaStr == L"恒流恒压充电")
			{
				if (!(StringUtils::IsValideInt(timeParaStr)))
				{
					errIdx++;
					errIdxStr.Format(_T("%d"), errIdx);
					checkResultStr += errIdxStr + L": 第" + rowIdxStr + L"行时间参数属于必填项且必须为数字!\n";
				}
				if (!(StringUtils::IsValideInt(currentParaStr)))
				{
					errIdx++;
					errIdxStr.Format(_T("%d"), errIdx);
					checkResultStr += errIdxStr + L": 第" + rowIdxStr + L"行电流参数属于必填项且必须为数字!\n";
				}
				if (!(StringUtils::IsValideInt(maxVoltParaStr)))
				{
					errIdx++;
					errIdxStr.Format(_T("%d"), errIdx);
					checkResultStr += errIdxStr + L": 第" + rowIdxStr + L"行上限电压参数属于必填项且必须为数字!\n";
				}
				if (!(StringUtils::IsValideInt(endCurrentParaStr)))
				{
					errIdx++;
					errIdxStr.Format(_T("%d"), errIdx);
					checkResultStr += errIdxStr + L": 第" + rowIdxStr + L"行终止电流参数属于必填项且必须为数字!\n";
				}
			}
			else if (stepParaStr == L"搁置")
			{
				if (!(StringUtils::IsValideInt(timeParaStr)))
				{
					errIdx++;
					errIdxStr.Format(_T("%d"), errIdx);
					checkResultStr += errIdxStr + L": 第" + rowIdxStr + L"行时间参数属于必填项且必须为数字!\n";
				}
			}
			else if (stepParaStr == L"恒流充电")
			{
				if (!(StringUtils::IsValideInt(timeParaStr)))
				{
					errIdx++;
					errIdxStr.Format(_T("%d"), errIdx);
					checkResultStr += errIdxStr + L": 第" + rowIdxStr + L"行时间参数属于必填项且必须为数字!\n";
				}
				if (!(StringUtils::IsValideInt(currentParaStr)))
				{
					errIdx++;
					errIdxStr.Format(_T("%d"), errIdx);
					checkResultStr += errIdxStr + L": 第" + rowIdxStr + L"行电流参数属于必填项且必须为数字!\n";
				}
				if (!(StringUtils::IsValideInt(maxVoltParaStr)))
				{
					errIdx++;
					errIdxStr.Format(_T("%d"), errIdx);
					checkResultStr += errIdxStr + L": 第" + rowIdxStr + L"行上限电压参数属于必填项且必须为数字!\n";
				}
			}
			else if (stepParaStr == L"")
			{
				errIdx++;
				errIdxStr.Format(_T("%d"), errIdx);
				checkResultStr += errIdxStr + L": 第" + rowIdxStr + L"行工步类型不能为空!\n";
			}
		}
	}
	
	return checkResultStr;
}

void CStartWorkDlg::UpdateWorkProcs(int cabId)
{
	if (workProcs[cabId - 1] != NULL)
	{
		delete (CWorkProc *)workProcs[cabId - 1];
		workProcs[cabId - 1] = NULL;
	}

	if (m_GridCtrl.GetRowCount() < 1) return;

	CString worProcName, modelName;

	workProcs[cabId - 1] = new CWorkProc();
	CWorkProc *workProc = (CWorkProc *)workProcs[cabId-1];
	workProcEdit.GetWindowTextW(workProc->workProcName);
	modelEdit.GetWindowTextW(workProc->model);
	workProc->workSteps.clear();
	
	int idx_col = 1;
	for (int i_row = 1; i_row < m_GridCtrl.GetRowCount(); ++i_row){
		CWorkStep workStep;

		workStep.workStepName = m_GridCtrl.GetItemText(i_row, STEP_PARAID2);
		workStep.workTime = m_GridCtrl.GetItemText(i_row, TIME_PARAID2);
		workStep.current = m_GridCtrl.GetItemText(i_row, CURRENT_PARAID2);
		workStep.maxVolt = m_GridCtrl.GetItemText(i_row, MAX_VOLT_PARAID2);
		workStep.minVolt = m_GridCtrl.GetItemText(i_row, MIN_VOLT_PARAID2);
		workStep.deltaVolt = m_GridCtrl.GetItemText(i_row, DELTA_VOLT_PARAID2);
		workStep.endCurrent = m_GridCtrl.GetItemText(i_row, END_CURRENT_PARAID2);
		workStep.endCapacity = m_GridCtrl.GetItemText(i_row, END_CAPACITY_PARAID2);

		if (m_GridCtrl.GetItemText(i_row, idx_col) == "循环")
		{
			workStep.startStep = m_GridCtrl.GetItemText(i_row, START_STEP_PARAID2);
			workStep.endStep = m_GridCtrl.GetItemText(i_row, END_STEP_PARAID2);
			workStep.loopNum = m_GridCtrl.GetItemText(i_row, LOOP_NUM_PARAID2);
		}
		workProc->stepNum++;
		workProc->workSteps.push_back(workStep);
	}
}

void CStartWorkDlg::UpdateWorkStep(CWorkStep& workStep, CString colStr, int colId)
{
	switch (colId)
	{
		case TIME_PARAID2:{
			workStep.workTime = colStr;
			break;
		}
		case CURRENT_PARAID2:{
			if (workStep.workStepName == L"循环"){
				workStep.startStep = colStr;
			}
			else{
				workStep.current = colStr;
			}
			break;
		}
		case MAX_VOLT_PARAID2:{
			workStep.maxVolt = colStr;
			break;
		}
		case MIN_VOLT_PARAID2: {
			if (workStep.workStepName == L"循环"){
				workStep.endStep = colStr;
			}
			else{
				workStep.minVolt = colStr;
			}
			break;
		}
		case DELTA_VOLT_PARAID2: {
			workStep.deltaVolt = colStr;
			break;
		}
		case END_CURRENT_PARAID2: {
			if (workStep.workStepName == L"循环"){
				workStep.loopNum = colStr;
			}
			else{
				workStep.endCurrent = colStr;
			}
			break;
		}
		case END_CAPACITY_PARAID2: {
			workStep.endCapacity = colStr;
			break;
		}
		default:
		break;
	}
}

void CStartWorkDlg::InitSpecStepInfoByPara(int cabId)
{
	CWorkProc* workProc = (CWorkProc *)workProcs[cabId - 1];
	if (cabId <= 0 || cabId > MAX_CAB_NUM)
		return;

	if (workProc != NULL)
	{

		//if (workProc->stepNum <= 0)
		//	return;

		workProcEdit.SetWindowTextW(workProc->workProcName);

		modelEdit.SetWindowTextW(workProc->model);
		int nRow = workProc->stepNum + 1;
		int nCol = STEP_COL_NUM;

		if (nRow - m_GridCtrl.GetRowCount() > 0){
			int tmp_RowCount = m_GridCtrl.GetRowCount();
			for (int i = 0; i < nRow - tmp_RowCount; ++i)
			{
				AddOneRow();
			}
		}
		GV_ITEM Item;
		Item.mask = GVIF_TEXT | GVIF_FORMAT;

		for (int i = 1; i < nRow; ++i)
		{
			Item.row = i;
			Item.col = STEP_PARAID2;
			Item.strText.Format(workProc->workSteps[i - 1].workStepName);
			m_GridCtrl.SetItem(&Item);
			m_GridCtrl.SetItemText(i, STEP_PARAID2, workProc->workSteps[i - 1].workStepName);

			Item.col = TIME_PARAID2;
			Item.strText.Format(workProc->workSteps[i - 1].workTime);
			m_GridCtrl.SetItem(&Item);
			m_GridCtrl.SetItemText(i, TIME_PARAID2, workProc->workSteps[i - 1].workTime);


			Item.col = CURRENT_PARAID2;
			Item.strText.Format(workProc->workSteps[i - 1].current);
			m_GridCtrl.SetItem(&Item);
			m_GridCtrl.SetItemText(i, CURRENT_PARAID2, workProc->workSteps[i - 1].current);

			Item.col = MAX_VOLT_PARAID2;
			Item.strText.Format(workProc->workSteps[i - 1].maxVolt);
			m_GridCtrl.SetItem(&Item);
			m_GridCtrl.SetItemText(i, MAX_VOLT_PARAID2, workProc->workSteps[i - 1].maxVolt);

			Item.col = MIN_VOLT_PARAID2;
			Item.strText.Format(workProc->workSteps[i - 1].minVolt);
			m_GridCtrl.SetItem(&Item);
			m_GridCtrl.SetItemText(i, MIN_VOLT_PARAID2, workProc->workSteps[i - 1].minVolt);

			Item.col = DELTA_VOLT_PARAID2;
			Item.strText.Format(workProc->workSteps[i - 1].deltaVolt);
			m_GridCtrl.SetItem(&Item);
			m_GridCtrl.SetItemText(i, DELTA_VOLT_PARAID2, workProc->workSteps[i - 1].deltaVolt);

			Item.col = END_CURRENT_PARAID2;
			Item.strText.Format(workProc->workSteps[i - 1].endCurrent);
			m_GridCtrl.SetItem(&Item);
			m_GridCtrl.SetItemText(i, END_CURRENT_PARAID2, workProc->workSteps[i - 1].endCurrent);

			Item.col = END_CAPACITY_PARAID2;
			Item.strText.Format(workProc->workSteps[i - 1].endCapacity);
			m_GridCtrl.SetItem(&Item);
			m_GridCtrl.SetItemText(i, END_CAPACITY_PARAID2, workProc->workSteps[i - 1].endCapacity);

		}
	}
	else
	{
		InitSpecCabInfoByFile(cabId);
	}
	updateGridStatus();
	m_GridCtrl.Invalidate();
	return;
}




void CStartWorkDlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	// 全局工序信息
	for (int idx = 0; idx < MAX_CAB_NUM; ++idx)
	{
		if (workProcs[idx] != NULL)
		{
			CWorkProc *workProc = (CWorkProc*)workProcs[idx];
			delete workProc;
			workProcs[idx] = NULL;
		}
	}
	CDialog::OnClose();
}

void CStartWorkDlg::InitOtherCabInfo(int cabId)
{
	for (int cabIdx = 1; cabIdx <= MAX_CAB_NUM; ++cabIdx)
	{
		if (cabIdx == cabId)
			continue;
		if (cabSelStr[cabIdx - 1] == '0')
			continue;

		wchar_t str[MAX_PATH_LENGTH];
		CString cabIdStr;
		_itow_s(cabIdx, str, INT_LENGTH);
		cabIdStr = str;

		CString tmpPath = CBatteryUtils::GetConfigPath(_T("\\config\\step\\")
			+ cabIdStr + _T("\\preStepPath.ini"));
		GetPrivateProfileString(_T("stepFilePath"), _T("path"), _T("error"), str, MAX_PATH_LENGTH, tmpPath);
		stepInitPath = str;
	
		InitSpecStepInfoByFile2(cabIdx, stepInitPath);
	}

}

void CStartWorkDlg::InitSpecStepInfoByFile2(int cabId, CString filePath)
{
	std::ifstream in(filePath);

	if (in.is_open())
	{
		// 初始化工序类
		if (workProcs[cabId - 1] == NULL)
			workProcs[cabId - 1] = new CWorkProc();
		else
		{
			delete workProcs[cabId - 1];
			workProcs[cabId - 1] = new CWorkProc();
		}

		string line;
		int nRow, nCol;
		// 文件第一行为工步名称
		// 第二行为型号
		//文件第三行为表格行数，第四行为表格列数
		CWorkProc *workProc = (CWorkProc*)workProcs[cabId - 1];
		getline(in, line);
		workProcVal = line.c_str();
		workProc->workProcName = workProcVal;

		getline(in, line);
		modelVal = line.c_str();
		workProc->model = modelVal;

		getline(in, line);
		nRow = std::stoi(line);
		getline(in, line);
		nCol = std::stoi(line);

		CWorkStep workStep;
		for (int i = 1; i < nRow; ++i)
		{
			getline(in, line);
			int spaceidx = 0;

			//  如果stepName 有效 则继续，首先寻找StepName
			CString stepName((line.substr(0, line.find(' '))).c_str());
			BOOL valideStepFlag = FALSE;

			COLORREF stepColor = defaultStepColor;
			for (int j = 0; j < stepNames.size(); ++j)
			{
				if (stepNames[j] == stepName)
				{
					stepColor = stepColors[j];
					valideStepFlag = TRUE;
					workProc->stepNum++;
					workStep.stepId = i;
					workStep.workStepName = stepName;
					workStep.isValide = TRUE;
					break;
				}
			}
			if (!valideStepFlag)
				break;
			for (int j = 1; j < nCol - 1; j++)
			{
				spaceidx = line.find(' ');
				int len = line.length();
				string tmp = line.substr(0, spaceidx);
				CString ctmp(tmp.c_str());
				ctmp = ctmp == DEFAULT_PATA_STR ? L"" : ctmp;

				line = line.substr(spaceidx + 1, len - spaceidx - 1);

				UpdateWorkStep(workStep, ctmp, j);
			}

			CString ctmp(line.c_str());
			ctmp = ctmp == DEFAULT_PATA_STR ? L"" : ctmp;

			UpdateWorkStep(workStep, ctmp, nCol - 1);

			workProc->workSteps.push_back(workStep);
		}
		return;
	}
}
