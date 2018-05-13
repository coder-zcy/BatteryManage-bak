// BatCapGradeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "BatCapGradeDlg.h"
#include "afxdialogex.h"


// CBatCapGradeDlg 对话框

IMPLEMENT_DYNAMIC(CBatCapGradeDlg, CDialog)

CBatCapGradeDlg::CBatCapGradeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBatCapGradeDlg::IDD, pParent)
{
	draw_circleDlg = NULL;
	OptionDlg = NULL;
	pairDLg = NULL;
	excludeExceptiondlg = NULL;
	importResistancedlg = NULL;
	gradeContentDlg = NULL;
	capGridConf = CapGradeConf::GetInstance();
}

CBatCapGradeDlg::~CBatCapGradeDlg()
{
	if (NULL != draw_circleDlg) delete draw_circleDlg;
	if (NULL != OptionDlg) delete OptionDlg;
	if (NULL != pairDLg) delete pairDLg;
	if (NULL != excludeExceptiondlg) delete excludeExceptiondlg;
	if (NULL != importResistancedlg) delete importResistancedlg;
	if (NULL != gradeContentDlg) delete gradeContentDlg;

}

void CBatCapGradeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DrawCircle_Rect, DrawCircle_rect);
	//DDX_Control(pDX, IDC_BCG_List1, LC_BatteryPercent);
	//DDX_Control(pDX, IDC_BCG_List2, LC_BatteryStatus);
	DDX_Control(pDX, IDC_CAB_COMB, cabComb);
	DDX_Control(pDX, IDC_NUM_EDIT, numEdit);
	DDX_Control(pDX, IDC_RATIO_EDIT, ratioEdit);
	DDX_Control(pDX, IDC_GRADE_CUSTOM, gradeGrid);
	DDX_Control(pDX, IDC_STEPDATA_CUSTOM, stepDataGrid);
	DDX_Control(pDX, IDC_GRADENAME_COMB, gradeNameComb);
}

BOOL CBatCapGradeDlg::OnInitDialog(){
	
	
	CDialog::OnInitDialog();
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);

	CRect drawCircle_rect;
	CPoint tmp;
	DrawCircle_rect.GetWindowRect(&drawCircle_rect);
	tmp.x = drawCircle_rect.left;
	tmp.y = drawCircle_rect.top;
	this->ScreenToClient(&tmp);

	if (NULL == draw_circleDlg)
	{
		draw_circleDlg = new CBCG_DrawingCircleDlg();
		
	}	
	draw_circleDlg->Create(IDD_BCG_DrawingCircleDlg, this);
	draw_circleDlg->MoveWindow(tmp.x, tmp.y, drawCircle_rect.Width(), drawCircle_rect.Height());
	//draw_circleDlg->MoveWindow(0, 0, 100, 200);
	draw_circleDlg->ShowWindow(SW_SHOW);

	//LC_BatteryPercent.InsertColumn(0, _T("序号"), LVCFMT_LEFT, 50);
	//LC_BatteryPercent.InsertColumn(1, _T("等级名"), LVCFMT_LEFT, 130);
	//LC_BatteryPercent.InsertColumn(2, _T("电池总数"), LVCFMT_LEFT, 100);
	//LC_BatteryPercent.InsertColumn(2, _T("电池百分比(%)"), LVCFMT_LEFT, 100);

	//LC_BatteryStatus.InsertColumn(0, _T("序号"), LVCFMT_LEFT, 50);
	//LC_BatteryStatus.InsertColumn(1, _T("屏号"), LVCFMT_LEFT, 50);
	//LC_BatteryStatus.InsertColumn(2, _T("电芯编号"), LVCFMT_LEFT, 50);
	//LC_BatteryStatus.InsertColumn(3, _T("等级名"), LVCFMT_LEFT, 50);
	//LC_BatteryStatus.InsertColumn(4, _T("容量(mAh)"), LVCFMT_LEFT, 50);
	//LC_BatteryStatus.InsertColumn(5, _T("时间(min)"), LVCFMT_LEFT, 50);
	//LC_BatteryStatus.InsertColumn(6, _T("开压(mV)"), LVCFMT_LEFT, 50);
	//LC_BatteryStatus.InsertColumn(7, _T("均压(mV)"), LVCFMT_LEFT, 50);
	//LC_BatteryStatus.InsertColumn(8, _T("点#1"), LVCFMT_LEFT, 50);
	//LC_BatteryStatus.InsertColumn(9, _T("点#2"), LVCFMT_LEFT, 50);
	//LC_BatteryStatus.InsertColumn(10, _T("点#3"), LVCFMT_LEFT, 50);
	//LC_BatteryStatus.InsertColumn(11, _T("点#4"), LVCFMT_LEFT, 50);
	//LC_BatteryStatus.InsertColumn(12, _T("点#5"), LVCFMT_LEFT, 50); -
	//LC_BatteryStatus.InsertColumn(13, _T("终压(mV)"), LVCFMT_LEFT, 50);
	//LC_BatteryStatus.InsertColumn(14, _T("SD(%)"), LVCFMT_LEFT, 50);
	//LC_BatteryStatus.InsertColumn(15, _T("中压(mV)"), LVCFMT_LEFT, 50);

	autoAdaptHelper.InitSize(this->m_hWnd);

	SetEditsPos();
	InitEditContent();
	

	if (gradeGrid.m_hWnd) 
	{
		InitGradeBasicSet();
		InitGradeGridHead();
		InitDefCapGradeSet();
	}
	
	if (stepDataGrid.m_hWnd)
	{
		int stepRowCount = stepDataGrid.GetRowCount();
		int stepColCount = stepDataGrid.GetColumnCount();

		CCellRange range(1, 1, stepRowCount - 1, stepColCount - 1);
		InitDataGridBasicSet();
		InitDataGridHead();
		InitDataGridContent();
	}
	InitCabComb();
	InitGradeComb();
	return TRUE;
}

void CBatCapGradeDlg::SetEditsPos()
{
	if (numEdit.m_hWnd) 
	{
		CRect numRect, ratioRect;
		numEdit.GetWindowRect(numRect);
		ratioEdit.GetWindowRect(ratioRect);

		ScreenToClient(numRect);
		ScreenToClient(ratioRect);
		numRect.bottom = numRect.top + 22;
		ratioRect.bottom = ratioRect.top + 22;

		numEdit.MoveWindow(numRect);
		ratioEdit.MoveWindow(ratioRect);
	}
}

void CBatCapGradeDlg::InitGradeComb()
{
	vector<CString> levelNames = capGridConf->gradeDetailInfos[capGridConf->codeSel].levelNames;
	int levelCount = capGridConf->gradeDetailInfos[capGridConf->codeSel].levelCount;

	for (int idx = 0; idx < levelCount; ++idx)
	{
		gradeNameComb.AddString(levelNames[idx]);
	}
	gradeNameComb.SetCurSel(capGridConf->codeSel < 0 || capGridConf->codeSel >= levelCount  ? 0 : capGridConf->codeSel);
}

BEGIN_MESSAGE_MAP(CBatCapGradeDlg, CDialog)
	ON_BN_CLICKED(IDC_BCG_BtnOption, &CBatCapGradeDlg::OnBnClickedBcgBtnoption)
	ON_BN_CLICKED(IDC_BCG_BtnPair, &CBatCapGradeDlg::OnBnClickedBcgBtnpair)
	ON_BN_CLICKED(IDC_BCG_BtnImportResistance, &CBatCapGradeDlg::OnBnClickedBcgBtnimportresistance)
	ON_BN_CLICKED(IDC_BCG_BtnExcludeException, &CBatCapGradeDlg::OnBnClickedBcgBtnexcludeexception)
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_CAB_COMB, &CBatCapGradeDlg::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BCG_BtnColdGrading, &CBatCapGradeDlg::OnBnClickedBcgBtncoldgrading)
	ON_MESSAGE(WM_UPDATE_BAT_CAP_GRID_MSG, &CBatCapGradeDlg::OnUpdateBatCapGrid)
	ON_BN_CLICKED(IDC_BCG_MIN, &CBatCapGradeDlg::OnBnClickedBcgMin)
	ON_BN_CLICKED(IDC_BCG_ADD, &CBatCapGradeDlg::OnBnClickedBcgAdd)
	ON_MESSAGE(WM_CAL_GRADE_MSG, &CBatCapGradeDlg::OnCalCapGrade)
	ON_BN_CLICKED(IDC_BCG_BtnSend, &CBatCapGradeDlg::OnBnClickedBcgBtnsend)
	ON_CBN_SELCHANGE(IDC_GRADENAME_COMB, &CBatCapGradeDlg::OnCbnSelchangeGradenameComb)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CBatCapGradeDlg 消息处理程序


void CBatCapGradeDlg::OnBnClickedBcgBtnoption()
{
	// TODO:  在此添加控件通知处理程序代码
	if (NULL == OptionDlg){
		OptionDlg = new CBCG_OptionDLG(NULL, fileStepData);
	}
	OptionDlg->DoModal();
}


void CBatCapGradeDlg::OnBnClickedBcgBtnpair()
{
	// TODO:  在此添加控件通知处理程序代码
	if (NULL == pairDLg)
	{
		pairDLg = new CBCG_PairDLG();
	}
	pairDLg->DoModal();
}


void CBatCapGradeDlg::OnBnClickedBcgBtnimportresistance()
{
	// TODO:  在此添加控件通知处理程序代码
	if (NULL == importResistancedlg)
	{
		importResistancedlg = new CBCG_ImportResistanceDLG();
	}
	importResistancedlg->DoModal();
}


void CBatCapGradeDlg::OnBnClickedBcgBtnexcludeexception()
{
	// TODO:  在此添加控件通知处理程序代码
	if (NULL == excludeExceptiondlg)
	{
		excludeExceptiondlg = new CExcludeExceptionDLG();
	}
	excludeExceptiondlg->DoModal();
}


void CBatCapGradeDlg::OnSize(UINT nType, int cx, int cy)
{
	
	CDialog::OnSize(nType, cx, cy);
	
	if (draw_circleDlg && draw_circleDlg->m_hWnd) {
		draw_circleDlg->UpdateWindow();
	}
	
	autoAdaptHelper.ReSize(this->m_hWnd);
	SetEditsPos();

	Invalidate();
	// TODO:  在此处添加消息处理程序代码
}



void CBatCapGradeDlg::OnCbnSelchangeCombo2()
{
	// TODO:  在此添加控件通知处理程序代码
}

void CBatCapGradeDlg::InitEditContent()
{
	if (numEdit.m_hWnd) 
	{
		numEdit.SetWindowTextW(_T("0"));
	}
	if (ratioEdit.m_hWnd)
	{
		ratioEdit.SetWindowTextW(_T("0.00%"));
	}
}


void CBatCapGradeDlg::InitFileStepData()
{
	fileStepData = CFileStepData(filePath);
}

void CBatCapGradeDlg::OnBnClickedBcgBtncoldgrading()
{
	TCHAR szFilter[] = _T("文本文件(*.mdb)|*.mdb||");
	CFileDialog fileDlg(TRUE, _T("mdb"), NULL, 0, szFilter, theApp.m_pMainWnd);
	

	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		filePath = fileDlg.GetPathName();
		fileStepData = CFileStepData(filePath);
		InitCabComb();
		if (gradeContentDlg == NULL || gradeContentDlg->m_hWnd == NULL)
		{
			gradeContentDlg = new CGradeContentDlg(NULL, fileStepData);
		}
		gradeContentDlg->DoModal();
	}
}

LRESULT CBatCapGradeDlg::OnUpdateBatCapGrid(WPARAM wParam, LPARAM lParam)
{
	BSTR b = (BSTR)wParam;
	CString paraStr(b);
	SysFreeString(b);

	if (paraStr.GetLength() == fileStepData.stepNum)
	{
		BOOL cmdFlag = TRUE;
		int count = 0;
		
		int stepIds[MAX_STEP_NUM];
		for (int idx = 0; idx < paraStr.GetLength(); ++idx)
		{
			if (paraStr[idx] != '0') 
			{
				count += paraStr[idx] - '0';
				stepId = idx + 1;
			}
		}
		// 只有一个分容条件
		if (count == 1) 
		{
			LoadStepToGrid(stepId);
			CalCapGrade();
		
		}
		else // 根据多个条件进行分容
		{
			LoadStepsToGrid(stepIds);
		}
	}

	return NULL;
}

void CBatCapGradeDlg::LoadStepToGrid(int stepId)
{
	TestInfo testInfo = CDbUtils::GetTestInfo(filePath);
	
	
	int batCount = testInfo.colShowNum * testInfo.groupNumPerCol * testInfo.numPerGroup;

	if (batCount > 0) 
	{
		stepDataGrid.SetRowCount(batCount + 1);
		vector<CBatCapInfo> batCapInfos = CDbUtils::GetBatCapInfoById(filePath, stepId);
		CString idxCstr;

		for (int idx = 1; idx <= batCount; ++idx)
		{	
			idxCstr.Format(_T("%d"), idx);
			GV_ITEM seqIdItem = CGridUtils::CreateGridItem(idx, 0, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, idxCstr);
			
			GV_ITEM cabIdItem, batIdItem, gradeNameItem, capItem, timeItem, openItem, avgItem;
			
			GV_ITEM pointItem1, pointItem2, pointItem3, pointItem4, pointItem5, endItem, sdItem, midItem; 

			cabIdItem = CGridUtils::CreateGridItem(idx, 1, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"");
			batIdItem = CGridUtils::CreateGridItem(idx, 2, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"");
			gradeNameItem = CGridUtils::CreateGridItem(idx, 3, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"");
			capItem = CGridUtils::CreateGridItem(idx, 4, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"");
			timeItem = CGridUtils::CreateGridItem(idx, 5, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"");
			openItem = CGridUtils::CreateGridItem(idx, 6, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"");
			avgItem = CGridUtils::CreateGridItem(idx, 7, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"");
			pointItem1 = CGridUtils::CreateGridItem(idx, 8, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"");
			pointItem2 = CGridUtils::CreateGridItem(idx, 9, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"");
			pointItem3 = CGridUtils::CreateGridItem(idx, 10, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"");
			pointItem4 = CGridUtils::CreateGridItem(idx, 11, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"");
			pointItem5 = CGridUtils::CreateGridItem(idx, 12, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"");
			endItem = CGridUtils::CreateGridItem(idx, 13, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"");
			sdItem = CGridUtils::CreateGridItem(idx, 14, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"");
			midItem = CGridUtils::CreateGridItem(idx, 15, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"");
		
			stepDataGrid.SetItem(&seqIdItem);
			stepDataGrid.SetItem(&cabIdItem);
			stepDataGrid.SetItem(&batIdItem);
			stepDataGrid.SetItem(&gradeNameItem);
			stepDataGrid.SetItem(&capItem);
			stepDataGrid.SetItem(&timeItem);
			stepDataGrid.SetItem(&openItem);
			stepDataGrid.SetItem(&avgItem);
			stepDataGrid.SetItem(&pointItem1);
			stepDataGrid.SetItem(&pointItem2);
			stepDataGrid.SetItem(&pointItem3);
			stepDataGrid.SetItem(&pointItem4);
			stepDataGrid.SetItem(&pointItem5);
			stepDataGrid.SetItem(&endItem);
			stepDataGrid.SetItem(&sdItem);
			stepDataGrid.SetItem(&midItem);

		}

		for (int idx = 0; idx < batCapInfos.size(); ++idx)
		{
			GV_ITEM cabIdItem, batIdItem, gradeNameItem, capItem, timeItem, openItem, avgItem;
			GV_ITEM pointItem1, pointItem2, pointItem3, pointItem4, pointItem5, endItem, sdItem, midItem;

			cabIdItem = CGridUtils::CreateGridItem(batCapInfos[idx].batId, 1, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, batCapInfos[idx].cabIdCstr);
			batIdItem = CGridUtils::CreateGridItem(batCapInfos[idx].batId, 2, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, batCapInfos[idx].batIdCstr);
			gradeNameItem = CGridUtils::CreateGridItem(batCapInfos[idx].batId, 3, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, batCapInfos[idx].gradeName);
			capItem = CGridUtils::CreateGridItem(batCapInfos[idx].batId, 4, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, batCapInfos[idx].capacityCstr);
			timeItem = CGridUtils::CreateGridItem(batCapInfos[idx].batId, 5, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, batCapInfos[idx].timeCstr);
			openItem = CGridUtils::CreateGridItem(batCapInfos[idx].batId, 6, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, batCapInfos[idx].openVoltCstr);
			avgItem = CGridUtils::CreateGridItem(batCapInfos[idx].batId, 7, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, batCapInfos[idx].avgVoltCstr);
			pointItem1 = CGridUtils::CreateGridItem(batCapInfos[idx].batId, 8, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, batCapInfos[idx].point1Cstr);
			pointItem2 = CGridUtils::CreateGridItem(batCapInfos[idx].batId, 9, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, batCapInfos[idx].point2Cstr);
			pointItem3 = CGridUtils::CreateGridItem(batCapInfos[idx].batId, 10, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, batCapInfos[idx].point3Cstr);
			pointItem4 = CGridUtils::CreateGridItem(batCapInfos[idx].batId, 11, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, batCapInfos[idx].point4Cstr);
			pointItem5 = CGridUtils::CreateGridItem(batCapInfos[idx].batId, 12, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, batCapInfos[idx].point5Cstr);
			endItem = CGridUtils::CreateGridItem(batCapInfos[idx].batId, 13, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, batCapInfos[idx].endVoltCstr);
			sdItem = CGridUtils::CreateGridItem(batCapInfos[idx].batId, 14, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, batCapInfos[idx].sdCstr);
			midItem = CGridUtils::CreateGridItem(batCapInfos[idx].batId, 15, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, batCapInfos[idx].midVoltCstr);
		
			stepDataGrid.SetItem(&cabIdItem);
			stepDataGrid.SetItem(&batIdItem);
			stepDataGrid.SetItem(&gradeNameItem);
			stepDataGrid.SetItem(&capItem);
			stepDataGrid.SetItem(&timeItem);
			stepDataGrid.SetItem(&openItem);
			stepDataGrid.SetItem(&avgItem);
			stepDataGrid.SetItem(&pointItem1);
			stepDataGrid.SetItem(&pointItem2);
			stepDataGrid.SetItem(&pointItem3);
			stepDataGrid.SetItem(&pointItem4);
			stepDataGrid.SetItem(&pointItem5);
			stepDataGrid.SetItem(&endItem);
			stepDataGrid.SetItem(&sdItem);
			stepDataGrid.SetItem(&midItem);
		}
	}
	
	stepDataGrid.Invalidate();
	
}

void CBatCapGradeDlg::LoadStepsToGrid(int stepIds[])
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CBatCapGradeDlg::InitGradeBasicSet()
{
	gradeGrid.SetColumnCount(4);
	gradeGrid.SetRowCount(1);
	gradeGrid.SetFixedRowCount(1);
	gradeGrid.SetFixedColumnCount(1);
	for (int idx = 0; idx < 4; ++idx)
	{
		gradeGrid.SetColumnWidth(idx, 100);
	}
}

void CBatCapGradeDlg::InitDataGridBasicSet()
{
	
		int groupNumPerCol = fileStepData.testInfo.groupNumPerCol;
		int colShowNum = fileStepData.testInfo.colShowNum;
		int numPerGroup = fileStepData.testInfo.numPerGroup;

		//3 逐个工步插入相关数据
		int batCount = groupNumPerCol * colShowNum * numPerGroup;
		batCount = batCount < 0 ? 0 : batCount;

		if (fileStepData.testInfo.cabinet < 0)
		{
			batCount = 0;
		}
			
		if (batCount >= 0)
		{
			stepDataGrid.SetColumnCount(16);
			stepDataGrid.SetRowCount(batCount + 1);
			stepDataGrid.SetFixedRowCount(1);
			stepDataGrid.SetFixedColumnCount(1);

			for (int idx = 0; idx < 16; ++idx)
			{
				stepDataGrid.SetColumnWidth(idx, 80);
			}
		}
}

void CBatCapGradeDlg::InitGradeGridHead()
{
	
	CString str;
	GV_ITEM seqIdItem = CGridUtils::CreateGridItem(0, 0, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"序号");
	GV_ITEM gradeNameItem = CGridUtils::CreateGridItem(0, 1, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"等级名");
	GV_ITEM numItem = CGridUtils::CreateGridItem(0, 2, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"电池总数");
	GV_ITEM ratioItem = CGridUtils::CreateGridItem(0, 3, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"电池百分比(%)");

	gradeGrid.SetItem(&seqIdItem);
	gradeGrid.SetItem(&gradeNameItem);
	gradeGrid.SetItem(&numItem);
	gradeGrid.SetItem(&ratioItem);
}

void CBatCapGradeDlg::InitDataGridHead()
{
	CString str;
	GV_ITEM seqIdItem = CGridUtils::CreateGridItem(0, 0, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"序号");
	GV_ITEM cabIdItem = CGridUtils::CreateGridItem(0, 1, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"屏号");
	GV_ITEM batIdItem = CGridUtils::CreateGridItem(0, 2, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"电芯编号");
	GV_ITEM gradeNameItem = CGridUtils::CreateGridItem(0, 3, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"等级名");
	GV_ITEM capItem = CGridUtils::CreateGridItem(0, 4, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"容量(mAh)");
	GV_ITEM timeItem = CGridUtils::CreateGridItem(0, 5, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"时间(min)");
	GV_ITEM openItem = CGridUtils::CreateGridItem(0, 6, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"开压(mV)");
	GV_ITEM avgItem = CGridUtils::CreateGridItem(0, 7, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"均压(mV)");
	GV_ITEM pointItem1 = CGridUtils::CreateGridItem(0, 8, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"点#1");
	GV_ITEM pointItem2 = CGridUtils::CreateGridItem(0, 9, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"点#2");
	GV_ITEM pointItem3 = CGridUtils::CreateGridItem(0, 10, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"点#3");
	GV_ITEM pointItem4 = CGridUtils::CreateGridItem(0, 11, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"点#4");
	GV_ITEM pointItem5 = CGridUtils::CreateGridItem(0, 12, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"点#5");
	GV_ITEM endItem = CGridUtils::CreateGridItem(0, 13, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"终压(mV)");
	GV_ITEM sdItem = CGridUtils::CreateGridItem(0, 14, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"SD(%)");
	GV_ITEM midItem = CGridUtils::CreateGridItem(0, 15, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"中压(mV)");

	stepDataGrid.SetItem(&seqIdItem);
	stepDataGrid.SetItem(&cabIdItem);
	stepDataGrid.SetItem(&batIdItem);
	stepDataGrid.SetItem(&gradeNameItem);
	stepDataGrid.SetItem(&capItem);
	stepDataGrid.SetItem(&timeItem);
	stepDataGrid.SetItem(&openItem);
	stepDataGrid.SetItem(&avgItem);
	stepDataGrid.SetItem(&pointItem1);
	stepDataGrid.SetItem(&pointItem2);
	stepDataGrid.SetItem(&pointItem3);
	stepDataGrid.SetItem(&pointItem4);
	stepDataGrid.SetItem(&pointItem5);
	stepDataGrid.SetItem(&endItem);
	stepDataGrid.SetItem(&sdItem);
	stepDataGrid.SetItem(&midItem);

	for (int idx = 1; idx < stepDataGrid.GetRowCount(); ++idx)
	{
		str.Format(_T("%d"), idx);
		GV_ITEM item = CGridUtils::CreateGridItem(idx, 0, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
		stepDataGrid.SetItem(&item);
	}
}

void CBatCapGradeDlg::InitDataGridContent()
{

}

void CBatCapGradeDlg::InitCabComb()
{
	int num = cabComb.GetCount();
	
	for (int idx = 0; idx < num; ++idx)
	{
		cabComb.DeleteString(0);
	}
	if (fileStepData.testInfo.cabinet > 0) {
		CString str;
		str.Format(_T("%d"), fileStepData.testInfo.cabinet);
		cabComb.AddString(str);
		cabComb.SetCurSel(0);
	}
}

void CBatCapGradeDlg::InitDefCapGradeSet()
{
	int idx;
	// 初始化gradeGrid
	int levelCount = capGridConf->gradeDetailInfos[capGridConf->codeSel].levelCount;
	gradeGrid.SetRowCount(levelCount + 1);
	CString seqStr;
	vector<CString> levelNames = capGridConf->gradeDetailInfos[capGridConf->codeSel].levelNames;

	for (idx = 0; idx < levelCount; idx++)
	{
		seqStr.Format(_T("%d"), idx + 1);
		GV_ITEM seqItem = CGridUtils::CreateGridItem(idx + 1, 0, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, seqStr);
		GV_ITEM nameItem = CGridUtils::CreateGridItem(idx + 1, 1, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, levelNames[idx]);
		GV_ITEM numItem = CGridUtils::CreateGridItem(idx + 1, 2, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"");
		GV_ITEM ratioItem = CGridUtils::CreateGridItem(idx + 1, 3, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"");
		
		gradeGrid.SetItem(&seqItem);
		gradeGrid.SetItem(&nameItem);
		gradeGrid.SetItem(&numItem);
		gradeGrid.SetItem(&ratioItem);
	}
}



void CBatCapGradeDlg::OnBnClickedBcgMin()
{
	int num = gradeNameComb.GetCount();
	int curSel = gradeNameComb.GetCurSel();

	if (num > 0) {
		curSel = (curSel - 1 + num) % num;
		gradeNameComb.SetCurSel(curSel);
	}
}


void CBatCapGradeDlg::OnBnClickedBcgAdd()
{
	int num = gradeNameComb.GetCount();
	int curSel = gradeNameComb.GetCurSel();

	if (num > 0) {
		curSel = (curSel + 1 ) % num;
		gradeNameComb.SetCurSel(curSel);
	}
}

LRESULT CBatCapGradeDlg::OnCalCapGrade(WPARAM wParam, LPARAM lParam)
{
	CalCapGrade();
	return NULL;
}

void CBatCapGradeDlg::CalCapGrade()
{
	if (filePath == L"") return;

	TestInfo testInfo = CDbUtils::GetTestInfo(filePath);


	batCount = testInfo.colShowNum * testInfo.groupNumPerCol * testInfo.numPerGroup;

	if (batCount > 0)
	{
		stepDataGrid.SetRowCount(batCount + 1);
		batCapInfos = CDbUtils::GetBatCapInfoById(filePath, stepId);
		CGradeDetailInfo gradeDetailInfo = capGridConf->gradeDetailInfos[capGridConf->codeSel];

		validBatCount = batCapInfos.size();
		memset(levelNum, 0, sizeof(int)*MAX_LEVEL_NUM);
		memset(batLevelStats, 0, sizeof(int)*MAX_BAT_NUM);

		CString idxCstr, gradeName;
		int gradeNum, capacity;

		for (int idx = 0; idx < batCapInfos.size(); ++idx)
		{
			GV_ITEM gradeNameItem;

			gradeNum = 0;
			capacity = _ttoi(batCapInfos[idx].capacityCstr);
			gradeNum = (capacity - gradeDetailInfo.startArrays[0] + gradeDetailInfo.defDisArrays[0]) / (gradeDetailInfo.defDisArrays[0]);

			if (gradeNum >= 1 && gradeNum <= gradeDetailInfo.levelCount) levelNum[gradeNum - 1] ++;
			batLevelStats[batCapInfos[idx].batId - 1] = gradeNum;

			gradeName = (gradeNum >= 1 && gradeNum <= gradeDetailInfo.levelCount) == TRUE ? gradeDetailInfo.levelNames[gradeNum - 1] : L"";
			gradeNameItem = CGridUtils::CreateGridItem(batCapInfos[idx].batId, 3, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, gradeName);

			stepDataGrid.SetItem(&gradeNameItem);
		}
		CalCapRatio();
		stepDataGrid.Invalidate();
	}
}

void CBatCapGradeDlg::LightPane(int gradeId)
{
	if (this->draw_circleDlg && this->draw_circleDlg->m_hWnd)
	{
		this->draw_circleDlg->LightPane(batLevelStats, batCount, gradeId);
	}
}

void CBatCapGradeDlg::LightGradeGrid(int gradeId)
{
	int rowCount = gradeGrid.GetRowCount();
	int colCount = gradeGrid.GetColumnCount();
	gridDefColor = stepDataGrid.GetItemBkColour(1, 1);
	int idx, jdx;

	for (idx = 1; idx < rowCount; ++idx)
	{
		if (idx == gradeId)
		{
			for (jdx = 0; jdx < colCount; ++jdx)
			{
				gradeGrid.SetItemBkColour(idx, jdx, gridSelColor);
			}
		}
		else
		{
			for (jdx = 0; jdx < colCount; ++jdx)
			{
				gradeGrid.SetItemBkColour(idx, jdx, gridDefColor);
			}
		}
	}
	gradeGrid.Invalidate();
}

void CBatCapGradeDlg::LightStepDataGrid(int gradeId)
{
	int rowCount = stepDataGrid.GetRowCount();
	int colCount = stepDataGrid.GetColumnCount();
	
	gridDefColor = stepDataGrid.GetItemBkColour(1, 1);
	int idx, jdx;

	for (idx = 1; idx < rowCount; ++idx)
	{
		if (batLevelStats[idx - 1] == gradeId)
		{
			for (jdx = 0; jdx < colCount; ++jdx)
			{
				stepDataGrid.SetItemBkColour(idx, jdx, gridSelColor);
			}
		}
		else
		{
			for (jdx = 0; jdx < colCount; ++jdx)
			{
				stepDataGrid.SetItemBkColour(idx, jdx, gridDefColor);
			}
		}
	}
	stepDataGrid.Invalidate();
}

void CBatCapGradeDlg::CalCapRatio()
{
	int idx;
	CString numCstr, ratioCstr;
	CGradeDetailInfo gradeDetailInfo = capGridConf->gradeDetailInfos[capGridConf->codeSel];

	for (idx = 0; idx < gradeDetailInfo.levelCount; ++idx)
	{
		levelRatio[idx] = validBatCount > 0 ? levelNum[idx] / validBatCount : 0;
		
		numCstr.Format(_T("%d"), levelNum[idx]);
		ratioCstr.Format(_T("%.2lf"), levelRatio[idx] * 100);
		ratioCstr += L"%";
	
		GV_ITEM numItem = CGridUtils::CreateGridItem(idx + 1, 2, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, numCstr);
		GV_ITEM rationItem = CGridUtils::CreateGridItem(idx + 1, 3, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, ratioCstr);
		
		gradeGrid.SetItem(&numItem);
		gradeGrid.SetItem(&rationItem);
	}
	gradeGrid.Invalidate();
}


void CBatCapGradeDlg::OnBnClickedBcgBtnsend()
{
	int cabId = cabComb.GetCurSel();
	int gradeId = gradeNameComb.GetCurSel();

	if (cabId < 0 || gradeId < 0)
	{
		MessageBox(_T("请同时选择有效的机柜号和等级标号!"));
		return;
	}

	LightPane(gradeId + 1);
	LightGradeGrid(gradeId + 1);
	LightStepDataGrid(gradeId + 1);
}


void CBatCapGradeDlg::OnCbnSelchangeGradenameComb()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CBatCapGradeDlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	this->fileStepData.DestroyData();
	CDialog::OnClose();
}
