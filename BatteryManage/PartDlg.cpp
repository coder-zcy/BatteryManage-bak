// PartDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "PartDlg.h"
#include "afxdialogex.h"
#include "GridUtils.h"


// CPartDlg 对话框

IMPLEMENT_DYNAMIC(CPartDlg, CDialog)

CPartDlg::CPartDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPartDlg::IDD, pParent)
{
	
}

CPartDlg::CPartDlg(CWnd* pParent, CFileCabData &fileCabData) : CDialog(CPartDlg::IDD, pParent)
{
	this->fileCabData = fileCabData;

	defColWidth = 180;
	defRowHeight = 24;
}

CPartDlg::~CPartDlg()
{

}

void CPartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PART_CUSTOM, partGrid);
	DDX_Control(pDX, IDC_ATTR_COMBO, attrCom);
	DDX_Control(pDX, IDC_STEP_COMBO, stepCombo);
	DDX_Control(pDX, IDC_DATETIME_COMBO, datatimeCom);
}


BEGIN_MESSAGE_MAP(CPartDlg, CDialog)
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_ATTR_COMBO, &CPartDlg::OnCbnSelchangeAttrCombo)
	ON_CBN_SELCHANGE(IDC_STEP_COMBO, &CPartDlg::OnCbnSelchangeStepCombo)
	ON_NOTIFY(NM_RCLICK, IDC_PART_CUSTOM, &CPartDlg::OnGridRClick)
END_MESSAGE_MAP()


// CPartDlg 消息处理程序


void CPartDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (this->m_hWnd) {
		CRect rect(0, 0, cx, cy);
		this->MoveWindow(rect.left + MARGIN_LEFT_BATPANE, rect.top + MARGIN_TOP_BATPANE - 28, rect.Width(), rect.Height(), TRUE);

		if (partGrid.m_hWnd)
		{
			partGrid.MoveWindow(CRect(rect.left, rect.top + 28, rect.right, rect.bottom), true);
			partGrid.Invalidate();
		}
	}
	// TODO:  在此处添加消息处理程序代码
}

void CPartDlg::InitGrid()
{
	
	
	InitTestInfo(fileCabData.testInfo);
	SetGridRowColSize(rowCount, colNum, 1, 1);
	InitGridRowHead();
	InitGridColHead();
	InitGridContent();


	partGrid.Invalidate();

}

void CPartDlg::MoveWindowToPos(int left, int top, int right, int bottom)
{
	if (partGrid.m_hWnd) 
	{
		partGrid.MoveWindow(left, top, right, bottom, true);
		partGrid.Invalidate();
	}
}

void CPartDlg::InitTestInfo(const TestInfo &testInfo)
{
	colNum = fileCabData.subGroupBatNum + 1;
	rowCount = (fileCabData.numPerGroup + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum * fileCabData.groupNumPerCol * fileCabData.colShowNum + 1;
}

void CPartDlg::SetGridRowColSize(int rowNum, int colNum, int fixRowNum, int fixColNUm)
{
	partGrid.SetRowCount(rowNum);
	partGrid.SetColumnCount(colNum);
	partGrid.SetFixedRowCount(fixRowNum);
	partGrid.SetFixedColumnCount(fixColNUm);

	for (int idx = 0; idx < rowNum; ++idx)
	{
		partGrid.SetRowHeight(idx, defRowHeight);
	}
	
	for (int idx = 0; idx < colNum; ++idx)
	{
		partGrid.SetColumnWidth(idx, defColWidth);
	}
	
}

BOOL CPartDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitCombox();
	InitGrid();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CPartDlg::InitGridRowHead()
{
	CString str;
	GV_ITEM markItem = CGridUtils::CreateGridItem(0, 0, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"(mAh)");
	partGrid.SetItem(&markItem);

	for (int idx = 1; idx <= fileCabData.subGroupBatNum; ++idx)
	{
		str.Format(L"%d", idx);
		str = L"第" + str + L"个";
		GV_ITEM item = CGridUtils::CreateGridItem(0, idx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
		partGrid.SetItem(&item);
	}
}

void CPartDlg::InitGridColHead()
{
	int groupNum = fileCabData.groupNumPerCol * fileCabData.colShowNum;
	int rowGroupNum = (fileCabData.numPerGroup + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
	CString str, str1, str2;

	for (int idx = 1; idx <= groupNum; ++idx)
	{
		for (int jdx = 1; jdx <= rowGroupNum; ++jdx)
		{
			str1.Format(_T("%d"), idx);
			str2.Format(_T("%d"), jdx);
			str = L"组 " + (idx < 10 ? L"0" + str1 : str1) + L"-" + str2;
			
			GV_ITEM item = CGridUtils::CreateGridItem((idx - 1) * rowGroupNum + jdx, 0, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
			partGrid.SetItem(&item);
		}
	}
}

void CPartDlg::InitGridContent()
{

	/*
	
	*/
	for (int idx = 1; idx < rowCount; ++idx)
	{
		for (int jdx = 1; jdx < colNum; ++jdx)
		{
			GV_ITEM item = CGridUtils::CreateGridItem(idx, jdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"");
		}
	}

	//CreatePartBatData();

	// 将电池数据填充至DataGrid
	CapShowType *capShowType = CapShowType::GetInstance();
	int batIdCheck = capShowType->GetPartShowBatidChk();
	int autoCheck = capShowType->GetAutoPartCapChk();
	FillPartDataToGrid(autoCheck,batIdCheck);
	

}

void CPartDlg::CreatePartBatData()
{
	//for (int idx = 0; idx < workProcInfos.size(); ++idx)
	//{
	//	if (workProcInfos[idx].workStepName != "结束"){
	//		vector<CPartBattery> tmp = CDbUtils::GetStepPartBatData(dataFilePath, idx + 1);
	//		for (int jdx = 0; jdx < tmp.size(); ++jdx)
	//		{
	//			stepPartbatterys[idx][tmp[jdx].batId - 1] = new CPartBattery();
	//			*(stepPartbatterys[idx][tmp[jdx].batId - 1]) = tmp[jdx];
	//		}
	//	}
	//}
}

void CPartDlg::InitCombox()
{
	CString attrArrays[ATTR_COUNT] = { L"容量", L"时间", L"开路电压", L"平均电压", L"终止电压", L"容量", L"终止电流" };

	for (int idx = 0; idx < ATTR_COUNT; ++idx)
	{
		attrCom.AddString(attrArrays[idx]);
	}

	CString str;
	int length = fileCabData.workProcInfos.size();
	if (length > 0 && fileCabData.workProcInfos[length - 1].workStepName == "结束")
	{
		length--;
	}
	for (int idx = 0; idx < length; ++idx)
	{
		str = (fileCabData.workProcInfos[idx].workStepName).c_str();
		
		stepCombo.AddString(str);
	}
	str = (fileCabData.testInfo.startTime).c_str();
	datatimeCom.AddString(str);

	attrCom.SetCurSel(0);
	stepCombo.SetCurSel(0);
	datatimeCom.SetCurSel(0);


}

void CPartDlg::FillPartDataToGrid(int autoCheck, int batIdCheck)
{
	int attrId = attrCom.GetCurSel();
	int stepId = stepCombo.GetCurSel() + 1;
	int dataTimeId = datatimeCom.GetCurSel();

	vector<CPartBattery *> partBatterys = fileCabData.stepPartbatterys[stepId - 1];
	
	switch (attrId)
	{
	case CAPACITY_SEL2:{
						   FillCapDetailData(partBatterys, autoCheck, batIdCheck);
						   break;
	}
	case TIME_SEL2:{
					   FillCapDetailData(partBatterys, autoCheck, batIdCheck);
						break;
	}
	case OPEN_VOLT_SEL2:{
							FillCapDetailData(partBatterys, autoCheck, batIdCheck);
						   break;
	}
	case AVG_VOLT_SEL2:{
						   FillCapDetailData(partBatterys, autoCheck, batIdCheck);
						   break;
	}
	case END_VOLT_SEL2:{
						   FillCapDetailData(partBatterys, autoCheck, batIdCheck);
						   break;
	}
	case ENERGY_SEL2:{
						FillCapDetailData(partBatterys, autoCheck, batIdCheck);
						break;
	}
	case END_CURRENT_SEL2:{
						FillCapDetailData(partBatterys, autoCheck, batIdCheck);
						break;
	}
	default:
		break;
	}
	partGrid.Invalidate();
}


void CPartDlg::FillCapDetailData(vector<CPartBattery *> &partBatterys, int autoCheck, int batIdCheck)
{
	CapShowType *capShowType = CapShowType::GetInstance();

	if (batIdCheck == MF_CHECKED)
	{
		CString str;
		if (autoCheck == MF_CHECKED)
		{
			for (int idx = 0; idx < partBatterys.size(); ++idx)
			{
				if (partBatterys[idx] != NULL)
				{
					int batId = partBatterys[idx]->batId;
					int rowIdx = (batId + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
					int colIdx = (batId % fileCabData.subGroupBatNum == 0 ? fileCabData.subGroupBatNum : batId % fileCabData.subGroupBatNum);

					str.Format(_T("%d"), batId);

					partGrid.SetItemText(rowIdx, colIdx, capShowType->flagVals[partBatterys[idx]->capFlag] + L"  " +
						partBatterys[idx]->capacity + L"  [" + str + L"]");
					partGrid.SetItemFgColour(rowIdx, colIdx,capShowType->colorVals[partBatterys[idx]->capFlag]);
				}
			}
		}
		else
		{
			for (int idx = 0; idx < partBatterys.size(); ++idx)
			{
				if (partBatterys[idx] != NULL)
				{
					int batId = partBatterys[idx]->batId;
					int rowIdx = (batId + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
					int colIdx = (batId % fileCabData.subGroupBatNum == 0 ? fileCabData.subGroupBatNum : batId % fileCabData.subGroupBatNum);

					str.Format(_T("%d"), batId);
					partGrid.SetItemText(rowIdx, colIdx, partBatterys[idx]->capacity + L"  [" + str + L"]");
					partGrid.SetItemFgColour(rowIdx, colIdx, RGB(0,0,0));

				}
			}
		}
	}
	else
	{
		if (autoCheck == MF_CHECKED)
		{
			for (int idx = 0; idx < partBatterys.size(); ++idx)
			{
				if (partBatterys[idx] != NULL)
				{
					int batId = partBatterys[idx]->batId;
					int rowIdx = (batId + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
					int colIdx = (batId % fileCabData.subGroupBatNum == 0 ? fileCabData.subGroupBatNum : batId % fileCabData.subGroupBatNum);

					partGrid.SetItemText(rowIdx, colIdx, capShowType->flagVals[partBatterys[idx]->capFlag] + L"  " + partBatterys[idx]->capacity);
					partGrid.SetItemFgColour(rowIdx, colIdx, capShowType->colorVals[partBatterys[idx]->capFlag]);

				}
			}
		}
		else
		{
			for (int idx = 0; idx < partBatterys.size(); ++idx)
			{
				if (partBatterys[idx] != NULL)
				{
					int batId = partBatterys[idx]->batId;
					int rowIdx = (batId + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
					int colIdx = (batId % fileCabData.subGroupBatNum == 0 ? fileCabData.subGroupBatNum : batId % fileCabData.subGroupBatNum);

					partGrid.SetItemText(rowIdx, colIdx, partBatterys[idx]->capacity);
					partGrid.SetItemFgColour(rowIdx, colIdx, RGB(0,0,0));
				}
			}
		}
	}
}

void CPartDlg::FillTimeDetailData(vector<CPartBattery *> &partBatterys, int autoCheck, int batIdCheck)
{
	CapShowType *capShowType = CapShowType::GetInstance();

	if (batIdCheck == MF_CHECKED)
	{
		CString str;
		if (autoCheck == MF_CHECKED)
		{
			for (int idx = 0; idx < partBatterys.size(); ++idx)
			{
				if (partBatterys[idx] != NULL)
				{
					int batId = partBatterys[idx]->batId;
					int rowIdx = (batId + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
					int colIdx = (batId % fileCabData.subGroupBatNum == 0 ? fileCabData.subGroupBatNum : batId % fileCabData.subGroupBatNum);

					str.Format(_T("%d"), batId);

					partGrid.SetItemText(rowIdx, colIdx, capShowType->flagVals[partBatterys[idx]->capFlag] + L"  " +
						partBatterys[idx]->atime + L"  [" + str + L"]");
					partGrid.SetItemFgColour(rowIdx, colIdx, capShowType->colorVals[partBatterys[idx]->capFlag]);
				}
			}
		}
		else
		{
			for (int idx = 0; idx < partBatterys.size(); ++idx)
			{
				if (partBatterys[idx] != NULL)
				{
					int batId = partBatterys[idx]->batId;
					int rowIdx = (batId + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
					int colIdx = (batId % fileCabData.subGroupBatNum == 0 ? fileCabData.subGroupBatNum : batId % fileCabData.subGroupBatNum);

					str.Format(_T("%d"), batId);
					partGrid.SetItemText(rowIdx, colIdx, partBatterys[idx]->atime + L"  [" + str + L"]");
					partGrid.SetItemFgColour(rowIdx, colIdx, RGB(0, 0, 0));

				}
			}
		}
	}
	else
	{
		if (autoCheck == MF_CHECKED)
		{
			for (int idx = 0; idx < partBatterys.size(); ++idx)
			{
				if (partBatterys[idx] != NULL)
				{
					int batId = partBatterys[idx]->batId;
					int rowIdx = (batId + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
					int colIdx = (batId % fileCabData.subGroupBatNum == 0 ? fileCabData.subGroupBatNum : batId % fileCabData.subGroupBatNum);

					partGrid.SetItemText(rowIdx, colIdx, capShowType->flagVals[partBatterys[idx]->capFlag] + L"  " + partBatterys[idx]->atime);
					partGrid.SetItemFgColour(rowIdx, colIdx, capShowType->colorVals[partBatterys[idx]->capFlag]);

				}
			}
		}
		else
		{
			for (int idx = 0; idx < partBatterys.size(); ++idx)
			{
				if (partBatterys[idx] != NULL)
				{
					int batId = partBatterys[idx]->batId;
					int rowIdx = (batId + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
					int colIdx = (batId % fileCabData.subGroupBatNum == 0 ? fileCabData.subGroupBatNum : batId % fileCabData.subGroupBatNum);

					partGrid.SetItemText(rowIdx, colIdx, partBatterys[idx]->atime);
					partGrid.SetItemFgColour(rowIdx, colIdx, RGB(0, 0, 0));
				}
			}
		}
	}
	
}

void CPartDlg::FillOvDetailData(vector<CPartBattery *> &partBatterys, int autoCheck, int batIdCheck)
{
	CapShowType *capShowType = CapShowType::GetInstance();

	if (batIdCheck == MF_CHECKED)
	{
		CString str;
		if (autoCheck == MF_CHECKED)
		{
			for (int idx = 0; idx < partBatterys.size(); ++idx)
			{
				if (partBatterys[idx] != NULL)
				{
					int batId = partBatterys[idx]->batId;
					int rowIdx = (batId + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
					int colIdx = (batId % fileCabData.subGroupBatNum == 0 ? fileCabData.subGroupBatNum : batId % fileCabData.subGroupBatNum);

					str.Format(_T("%d"), batId);

					partGrid.SetItemText(rowIdx, colIdx, capShowType->flagVals[partBatterys[idx]->capFlag] + L"  " +
						partBatterys[idx]->openVolt + L"  [" + str + L"]");
					partGrid.SetItemFgColour(rowIdx, colIdx, capShowType->colorVals[partBatterys[idx]->capFlag]);
				}
			}
		}
		else
		{
			for (int idx = 0; idx < partBatterys.size(); ++idx)
			{
				if (partBatterys[idx] != NULL)
				{
					int batId = partBatterys[idx]->batId;
					int rowIdx = (batId + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
					int colIdx = (batId % fileCabData.subGroupBatNum == 0 ? fileCabData.subGroupBatNum : batId % fileCabData.subGroupBatNum);

					str.Format(_T("%d"), batId);
					partGrid.SetItemText(rowIdx, colIdx, partBatterys[idx]->openVolt + L"  [" + str + L"]");
					partGrid.SetItemFgColour(rowIdx, colIdx, RGB(0, 0, 0));

				}
			}
		}
	}
	else
	{
		if (autoCheck == MF_CHECKED)
		{
			for (int idx = 0; idx < partBatterys.size(); ++idx)
			{
				if (partBatterys[idx] != NULL)
				{
					int batId = partBatterys[idx]->batId;
					int rowIdx = (batId + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
					int colIdx = (batId % fileCabData.subGroupBatNum == 0 ? fileCabData.subGroupBatNum : batId % fileCabData.subGroupBatNum);

					partGrid.SetItemText(rowIdx, colIdx, capShowType->flagVals[partBatterys[idx]->capFlag] + L"  " + partBatterys[idx]->openVolt);
					partGrid.SetItemFgColour(rowIdx, colIdx, capShowType->colorVals[partBatterys[idx]->capFlag]);

				}
			}
		}
		else
		{
			for (int idx = 0; idx < partBatterys.size(); ++idx)
			{
				if (partBatterys[idx] != NULL)
				{
					int batId = partBatterys[idx]->batId;
					int rowIdx = (batId + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
					int colIdx = (batId % fileCabData.subGroupBatNum == 0 ? fileCabData.subGroupBatNum : batId % fileCabData.subGroupBatNum);

					partGrid.SetItemText(rowIdx, colIdx, partBatterys[idx]->openVolt);
					partGrid.SetItemFgColour(rowIdx, colIdx, RGB(0, 0, 0));
				}
			}
		}
	}
	
}

void CPartDlg::FillAvDetailData(vector<CPartBattery *> &partBatterys, int autoCheck, int batIdCheck)
{
	CapShowType *capShowType = CapShowType::GetInstance();

	if (batIdCheck == MF_CHECKED)
	{
		CString str;
		if (autoCheck == MF_CHECKED)
		{
			for (int idx = 0; idx < partBatterys.size(); ++idx)
			{
				if (partBatterys[idx] != NULL)
				{
					int batId = partBatterys[idx]->batId;
					int rowIdx = (batId + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
					int colIdx = (batId % fileCabData.subGroupBatNum == 0 ? fileCabData.subGroupBatNum : batId % fileCabData.subGroupBatNum);

					str.Format(_T("%d"), batId);

					partGrid.SetItemText(rowIdx, colIdx, capShowType->flagVals[partBatterys[idx]->capFlag] + L"  " +
						partBatterys[idx]->avgVolt + L"  [" + str + L"]");
					partGrid.SetItemFgColour(rowIdx, colIdx, capShowType->colorVals[partBatterys[idx]->capFlag]);
				}
			}
		}
		else
		{
			for (int idx = 0; idx < partBatterys.size(); ++idx)
			{
				if (partBatterys[idx] != NULL)
				{
					int batId = partBatterys[idx]->batId;
					int rowIdx = (batId + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
					int colIdx = (batId % fileCabData.subGroupBatNum == 0 ? fileCabData.subGroupBatNum : batId % fileCabData.subGroupBatNum);

					str.Format(_T("%d"), batId);
					partGrid.SetItemText(rowIdx, colIdx, partBatterys[idx]->avgVolt + L"  [" + str + L"]");
					partGrid.SetItemFgColour(rowIdx, colIdx, RGB(0, 0, 0));

				}
			}
		}
	}
	else
	{
		if (autoCheck == MF_CHECKED)
		{
			for (int idx = 0; idx < partBatterys.size(); ++idx)
			{
				if (partBatterys[idx] != NULL)
				{
					int batId = partBatterys[idx]->batId;
					int rowIdx = (batId + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
					int colIdx = (batId % fileCabData.subGroupBatNum == 0 ? fileCabData.subGroupBatNum : batId % fileCabData.subGroupBatNum);

					partGrid.SetItemText(rowIdx, colIdx, capShowType->flagVals[partBatterys[idx]->capFlag] + L"  " + partBatterys[idx]->avgVolt);
					partGrid.SetItemFgColour(rowIdx, colIdx, capShowType->colorVals[partBatterys[idx]->capFlag]);

				}
			}
		}
		else
		{
			for (int idx = 0; idx < partBatterys.size(); ++idx)
			{
				if (partBatterys[idx] != NULL)
				{
					int batId = partBatterys[idx]->batId;
					int rowIdx = (batId + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
					int colIdx = (batId % fileCabData.subGroupBatNum == 0 ? fileCabData.subGroupBatNum : batId % fileCabData.subGroupBatNum);

					partGrid.SetItemText(rowIdx, colIdx, partBatterys[idx]->avgVolt);
					partGrid.SetItemFgColour(rowIdx, colIdx, RGB(0, 0, 0));
				}
			}
		}
	}
	
}

void CPartDlg::FillEvDetailData(vector<CPartBattery *> &partBatterys, int autoCheck, int batIdCheck)
{
	CapShowType *capShowType = CapShowType::GetInstance();

	if (batIdCheck == MF_CHECKED)
	{
		CString str;
		if (autoCheck == MF_CHECKED)
		{
			for (int idx = 0; idx < partBatterys.size(); ++idx)
			{
				if (partBatterys[idx] != NULL)
				{
					int batId = partBatterys[idx]->batId;
					int rowIdx = (batId + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
					int colIdx = (batId % fileCabData.subGroupBatNum == 0 ? fileCabData.subGroupBatNum : batId % fileCabData.subGroupBatNum);

					str.Format(_T("%d"), batId);

					partGrid.SetItemText(rowIdx, colIdx, capShowType->flagVals[partBatterys[idx]->capFlag] + L"  " +
						partBatterys[idx]->endVolt + L"  [" + str + L"]");
					partGrid.SetItemFgColour(rowIdx, colIdx, capShowType->colorVals[partBatterys[idx]->capFlag]);
				}
			}
		}
		else
		{
			for (int idx = 0; idx < partBatterys.size(); ++idx)
			{
				if (partBatterys[idx] != NULL)
				{
					int batId = partBatterys[idx]->batId;
					int rowIdx = (batId + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
					int colIdx = (batId % fileCabData.subGroupBatNum == 0 ? fileCabData.subGroupBatNum : batId % fileCabData.subGroupBatNum);

					str.Format(_T("%d"), batId);
					partGrid.SetItemText(rowIdx, colIdx, partBatterys[idx]->endVolt + L"  [" + str + L"]");
					partGrid.SetItemFgColour(rowIdx, colIdx, RGB(0, 0, 0));

				}
			}
		}
	}
	else
	{
		if (autoCheck == MF_CHECKED)
		{
			for (int idx = 0; idx < partBatterys.size(); ++idx)
			{
				if (partBatterys[idx] != NULL)
				{
					int batId = partBatterys[idx]->batId;
					int rowIdx = (batId + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
					int colIdx = (batId % fileCabData.subGroupBatNum == 0 ? fileCabData.subGroupBatNum : batId % fileCabData.subGroupBatNum);

					partGrid.SetItemText(rowIdx, colIdx, capShowType->flagVals[partBatterys[idx]->capFlag] + L"  " + partBatterys[idx]->endVolt);
					partGrid.SetItemFgColour(rowIdx, colIdx, capShowType->colorVals[partBatterys[idx]->capFlag]);

				}
			}
		}
		else
		{
			for (int idx = 0; idx < partBatterys.size(); ++idx)
			{
				if (partBatterys[idx] != NULL)
				{
					int batId = partBatterys[idx]->batId;
					int rowIdx = (batId + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
					int colIdx = (batId % fileCabData.subGroupBatNum == 0 ? fileCabData.subGroupBatNum : batId % fileCabData.subGroupBatNum);

					partGrid.SetItemText(rowIdx, colIdx, partBatterys[idx]->endVolt);
					partGrid.SetItemFgColour(rowIdx, colIdx, RGB(0, 0, 0));
				}
			}
		}
	}
}

void CPartDlg::FillEnergyDetailData(vector<CPartBattery *> &partBatterys, int autoCheck, int batIdCheck)
{
	CapShowType *capShowType = CapShowType::GetInstance();

	if (batIdCheck == MF_CHECKED)
	{
		CString str;
		if (autoCheck == MF_CHECKED)
		{
			for (int idx = 0; idx < partBatterys.size(); ++idx)
			{
				if (partBatterys[idx] != NULL)
				{
					int batId = partBatterys[idx]->batId;
					int rowIdx = (batId + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
					int colIdx = (batId % fileCabData.subGroupBatNum == 0 ? fileCabData.subGroupBatNum : batId % fileCabData.subGroupBatNum);

					str.Format(_T("%d"), batId);

					partGrid.SetItemText(rowIdx, colIdx, capShowType->flagVals[partBatterys[idx]->capFlag] + L"  " +
						partBatterys[idx]->energy + L"  [" + str + L"]");
					partGrid.SetItemFgColour(rowIdx, colIdx, capShowType->colorVals[partBatterys[idx]->capFlag]);
				}
			}
		}
		else
		{
			for (int idx = 0; idx < partBatterys.size(); ++idx)
			{
				if (partBatterys[idx] != NULL)
				{
					int batId = partBatterys[idx]->batId;
					int rowIdx = (batId + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
					int colIdx = (batId % fileCabData.subGroupBatNum == 0 ? fileCabData.subGroupBatNum : batId % fileCabData.subGroupBatNum);

					str.Format(_T("%d"), batId);
					partGrid.SetItemText(rowIdx, colIdx, partBatterys[idx]->energy + L"  [" + str + L"]");
					partGrid.SetItemFgColour(rowIdx, colIdx, RGB(0, 0, 0));

				}
			}
		}
	}
	else
	{
		if (autoCheck == MF_CHECKED)
		{
			for (int idx = 0; idx < partBatterys.size(); ++idx)
			{
				if (partBatterys[idx] != NULL)
				{
					int batId = partBatterys[idx]->batId;
					int rowIdx = (batId + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
					int colIdx = (batId % fileCabData.subGroupBatNum == 0 ? fileCabData.subGroupBatNum : batId % fileCabData.subGroupBatNum);

					partGrid.SetItemText(rowIdx, colIdx, capShowType->flagVals[partBatterys[idx]->capFlag] + L"  " + partBatterys[idx]->energy);
					partGrid.SetItemFgColour(rowIdx, colIdx, capShowType->colorVals[partBatterys[idx]->capFlag]);

				}
			}
		}
		else
		{
			for (int idx = 0; idx < partBatterys.size(); ++idx)
			{
				if (partBatterys[idx] != NULL)
				{
					int batId = partBatterys[idx]->batId;
					int rowIdx = (batId + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
					int colIdx = (batId % fileCabData.subGroupBatNum == 0 ? fileCabData.subGroupBatNum : batId % fileCabData.subGroupBatNum);

					partGrid.SetItemText(rowIdx, colIdx, partBatterys[idx]->energy);
					partGrid.SetItemFgColour(rowIdx, colIdx, RGB(0, 0, 0));
				}
			}
		}
	}
	
}

void CPartDlg::FillEcDetailData(vector<CPartBattery *> &partBatterys, int autoCheck, int batIdCheck)
{
	CapShowType *capShowType = CapShowType::GetInstance();

	if (batIdCheck == MF_CHECKED)
	{
		CString str;
		if (autoCheck == MF_CHECKED)
		{
			for (int idx = 0; idx < partBatterys.size(); ++idx)
			{
				if (partBatterys[idx] != NULL)
				{
					int batId = partBatterys[idx]->batId;
					int rowIdx = (batId + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
					int colIdx = (batId % fileCabData.subGroupBatNum == 0 ? fileCabData.subGroupBatNum : batId % fileCabData.subGroupBatNum);

					str.Format(_T("%d"), batId);

					partGrid.SetItemText(rowIdx, colIdx, capShowType->flagVals[partBatterys[idx]->capFlag] + L"  " +
						partBatterys[idx]->endCurrent + L"  [" + str + L"]");
					partGrid.SetItemFgColour(rowIdx, colIdx, capShowType->colorVals[partBatterys[idx]->capFlag]);
				}
			}
		}
		else
		{
			for (int idx = 0; idx < partBatterys.size(); ++idx)
			{
				if (partBatterys[idx] != NULL)
				{
					int batId = partBatterys[idx]->batId;
					int rowIdx = (batId + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
					int colIdx = (batId % fileCabData.subGroupBatNum == 0 ? fileCabData.subGroupBatNum : batId % fileCabData.subGroupBatNum);

					str.Format(_T("%d"), batId);
					partGrid.SetItemText(rowIdx, colIdx, partBatterys[idx]->endCurrent + L"  [" + str + L"]");
					partGrid.SetItemFgColour(rowIdx, colIdx, RGB(0, 0, 0));

				}
			}
		}
	}
	else
	{
		if (autoCheck == MF_CHECKED)
		{
			for (int idx = 0; idx < partBatterys.size(); ++idx)
			{
				if (partBatterys[idx] != NULL)
				{
					int batId = partBatterys[idx]->batId;
					int rowIdx = (batId + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
					int colIdx = (batId % fileCabData.subGroupBatNum == 0 ? fileCabData.subGroupBatNum : batId % fileCabData.subGroupBatNum);

					partGrid.SetItemText(rowIdx, colIdx, capShowType->flagVals[partBatterys[idx]->capFlag] + L"  " + partBatterys[idx]->endCurrent);
					partGrid.SetItemFgColour(rowIdx, colIdx, capShowType->colorVals[partBatterys[idx]->capFlag]);

				}
			}
		}
		else
		{
			for (int idx = 0; idx < partBatterys.size(); ++idx)
			{
				if (partBatterys[idx] != NULL)
				{
					int batId = partBatterys[idx]->batId;
					int rowIdx = (batId + fileCabData.subGroupBatNum - 1) / fileCabData.subGroupBatNum;
					int colIdx = (batId % fileCabData.subGroupBatNum == 0 ? fileCabData.subGroupBatNum : batId % fileCabData.subGroupBatNum);

					partGrid.SetItemText(rowIdx, colIdx, partBatterys[idx]->endCurrent);
					partGrid.SetItemFgColour(rowIdx, colIdx, RGB(0, 0, 0));
				}
			}
		}
	}
}

void CPartDlg::OnCbnSelchangeAttrCombo()
{
	CapShowType *capShowType = CapShowType::GetInstance();
	int autoCheck = capShowType->GetAutoPartCapChk();
	int batIdCheck = capShowType->GetPartShowBatidChk();

	FillPartDataToGrid(autoCheck, batIdCheck);
}


void CPartDlg::OnCbnSelchangeStepCombo()
{
	CapShowType *capShowType = CapShowType::GetInstance();
	int autoCheck = capShowType->GetAutoPartCapChk();
	int batIdCheck = capShowType->GetPartShowBatidChk();
	
	FillPartDataToGrid(autoCheck,batIdCheck);
}

void CPartDlg::UpdatePartData(int autoCheck, int batIdCheck)
{
	FillPartDataToGrid(autoCheck,batIdCheck);
}

void CPartDlg::OnGridRClick(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	CapShowType *capShowType = CapShowType::GetInstance();

	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*)pNotifyStruct;
	if (pItem->iRow == -1) return;

	CMenu   menu;   //定义下面要用到的cmenu对象
	menu.LoadMenu(IDR_PART_MENU); //装载自定义的右键菜单 
	CMenu   *pContextMenu = menu.GetSubMenu(0); //获取第一个弹出菜单，所以第一个菜单必须有子菜单 

	if (pContextMenu != NULL)
	{
		pContextMenu->CheckMenuItem(ID_AUTO_PART_CAP, capShowType->GetAutoPartCapChk());

		//pContextMenu->CheckMenuItem(ID_PART_CAP_COND, capShowType->GetPartCapCondChk());

		pContextMenu->CheckMenuItem(ID_PART_SHOW_BATID, capShowType->GetPartShowBatidChk());
	}


	CPoint point1;//定义一个用于确定光标位置的位置  
	GetCursorPos(&point1);//获取当前光标的位置，以便使得菜单可以跟随光标  
	pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point1.x, point1.y, AfxGetMainWnd()); //在指定位置显示弹出菜单

}