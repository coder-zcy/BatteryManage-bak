// StatisticDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "StatisticDlg.h"
#include "afxdialogex.h"
#include "CSeries.h"
#include "CMarks.h"

// CStatisticDlg 对话框

IMPLEMENT_DYNAMIC(CStatisticDlg, CDialog)

CStatisticDlg::CStatisticDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStatisticDlg::IDD, pParent)
{

}

CStatisticDlg::CStatisticDlg(CWnd* pParent, CFileCabData fileCabData)
{
	

	GAP_WIDTH = 1;
	GAP_HEIGHT = 1;
	TOP_MARGIN = 28;
	LEFT_MARGIN = 0;

	SEG_ROW_COUNT = 17;
	SEG_COL_COUNT = 5;
	SEG_ROW_HEIGHT = 20;
	SEG_COL_WIDTH = 80;

	CAP_ROW_COUNT = 0;
	CAP_COL_COUNT = 2;
	CAP_ROW_HEIGHT = 20;
	CAP_COL_WIDTH = 120;

	subGroupBatNum = 8;
	batCount = 0;
	this->testInfo = fileCabData.testInfo;
	this->workProcInfos = fileCabData.workProcInfos;
	this->endDisBatterys = fileCabData.endDisBatterys;
}

CStatisticDlg::~CStatisticDlg()
{

}

void CStatisticDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BATNUM_STATIC, batNumStatic);
	DDX_Control(pDX, IDC_CHECKOUT_NUM_STATIC, checkOutNumStatic);
	DDX_Control(pDX, IDC_CHECKOUT_RATIO_STATIC, checkoutRatioStatic);
	DDX_Control(pDX, IDC_MAX_STATIC, maxStatic);
	DDX_Control(pDX, IDC_MIN_STATIC, minStatic);
	DDX_Control(pDX, IDC_AVG_STATIC, avgStatic);

	DDX_Control(pDX, IDC_SEG_CUSTOM, segGrid);
	DDX_Control(pDX, IDC_CAP_CUSTOM, capGrid);

	//DDX_Control(pDX, IDC_DIS_STATIC, disStatic);

	DDX_Control(pDX, IDC_CAP_CHART, disChart);
}


BEGIN_MESSAGE_MAP(CStatisticDlg, CDialog)
	ON_WM_SIZE()
	ON_NOTIFY(NM_RCLICK, IDC_SEG_CUSTOM, &CStatisticDlg::OnGridRClick)
	ON_NOTIFY(NM_RCLICK, IDC_CAP_CUSTOM, &CStatisticDlg::OnGridRClick)
	ON_BN_CLICKED(IDC_DIS_STATIC, &CStatisticDlg::OnBnClickedDisStatic)
END_MESSAGE_MAP()


// CStatisticDlg 消息处理程序


void CStatisticDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (this->m_hWnd) {
		CRect rect(0, 0, cx, cy);
		this->MoveWindow(rect.left + MARGIN_LEFT_BATPANE, rect.top + MARGIN_TOP_BATPANE - 28, rect.Width(), rect.Height(), TRUE);

		if (segGrid.m_hWnd)
		{
			InitPartSize(rect);
		}
	}
	
	// TODO:  在此处添加消息处理程序代码
}


void CStatisticDlg::OnGridRClick(NMHDR *pNotifyStruct, LRESULT* pResult)
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

BOOL CStatisticDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitCapChart();
	InitSegGird();
	InitCapGrid();
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CStatisticDlg::InitPartSize(CRect rect)
{
	if (segGrid.m_hWnd)
	{
		segWidth = (rect.Width() - LEFT_MARGIN) / 3 - GAP_WIDTH;
		segHeight = (rect.Height() - TOP_MARGIN) / 2 - GAP_WIDTH;

		capWidth = segWidth;
		capHeight = segHeight;

		disWidth = rect.Width() - LEFT_MARGIN -segWidth -GAP_WIDTH;
		disHeight = rect.Height() - TOP_MARGIN - GAP_HEIGHT;

		CRect segRect(LEFT_MARGIN, TOP_MARGIN, LEFT_MARGIN + segWidth, TOP_MARGIN + segHeight);
		CRect capRect(LEFT_MARGIN, TOP_MARGIN + capHeight + GAP_HEIGHT, LEFT_MARGIN + capWidth, TOP_MARGIN + capHeight + GAP_HEIGHT +capHeight);
		CRect disRect(LEFT_MARGIN + segWidth + GAP_WIDTH, TOP_MARGIN, LEFT_MARGIN + segWidth + disWidth, TOP_MARGIN + disHeight);

		CRect segGridRect(segRect.left + GAP_WIDTH* 2, segRect.top + GAP_HEIGHT*2, segRect.right - GAP_WIDTH * 2, segRect.bottom - GAP_HEIGHT*2);
		CRect capGridRect(capRect.left + GAP_WIDTH * 2, capRect.top + GAP_HEIGHT * 2, capRect.right - GAP_WIDTH * 2, capRect.bottom - GAP_HEIGHT * 2);
		CRect disChartRect(disRect.left + GAP_WIDTH * 2, disRect.top + GAP_HEIGHT * 2, disRect.right - GAP_WIDTH * 2, disRect.bottom - GAP_HEIGHT * 2);


		//disStatic.MoveWindow(disRect);
		

		segGrid.MoveWindow(segRect);
		capGrid.MoveWindow(capRect);
		disChart.MoveWindow(disChartRect);
		// 更新capGrid的列数
		int segGridWidth = segRect.Width() / SEG_COL_COUNT;
		int capGridWidth = capRect.Width() / CAP_COL_COUNT;

		for (int idx = 0; idx < SEG_COL_COUNT; ++idx)
		{
			segGrid.SetColumnWidth(idx, segGridWidth);
		}

		for (int idx = 0; idx < CAP_COL_COUNT; ++idx)
		{
			capGrid.SetColumnWidth(idx, capGridWidth);
		}
		segGrid.Invalidate();
		capGrid.Invalidate();
	}
}

void CStatisticDlg::InitSegGird()
{
	InitSegGridSize();
	InitSegGridHead();
	InitSegGridContent();
}

void CStatisticDlg::InitCapGrid()
{
	InitCapGridSize();
	InitCapGridRowHead();
	InitCapGridColHead();
	InitCapGridContent();
}

void CStatisticDlg::InitSegGridSize()
{
	segGrid.SetRowCount(SEG_ROW_COUNT);
	segGrid.SetColumnCount(SEG_COL_COUNT);
	segGrid.SetFixedRowCount(1);
	segGrid.SetFixedColumnCount(1);
}

void CStatisticDlg::InitSegGridHead()
{
	GV_ITEM seqItem, minItem, maxItem, numItem, ratioItem;

	seqItem = CGridUtils::CreateGridItem(0, 0, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"区段序号");
	minItem = CGridUtils::CreateGridItem(0, 1, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"下限值(mAh)");
	maxItem = CGridUtils::CreateGridItem(0, 2, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"上限值(mAh)");
	numItem = CGridUtils::CreateGridItem(0, 3, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"电池个数(个)");
	ratioItem = CGridUtils::CreateGridItem(0, 4, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"百分比(%)");

	segGrid.SetItem(&seqItem);
	segGrid.SetItem(&minItem);
	segGrid.SetItem(&maxItem);
	segGrid.SetItem(&numItem);
	segGrid.SetItem(&ratioItem);

	CapShowType *capShowType = CapShowType::GetInstance();
	CString str;

	if (capShowType->GetAutoPartCapChk() == MF_CHECKED)
	{
		for (int idx = 1; idx < SEG_ROW_COUNT; ++idx)
		{
			str.Format(_T("%d"), idx);
			str = capShowType->flagVals[idx-1] == L"0" ? str : L"[" + capShowType->flagVals[idx-1] + L"] " + str;
			GV_ITEM item = CGridUtils::CreateGridItem(idx, 0, GVIF_TEXT | GVIF_FORMAT, DT_RIGHT | DT_WORDBREAK, str);
			item.mask |= GVIF_FGCLR;
			item.crFgClr = capShowType->colorVals[idx-1];
			segGrid.SetItem(&item);
		}
	}
	else
	{
		for (int idx = 1; idx < SEG_ROW_COUNT; ++idx)
		{
			str.Format(_T("%d"), idx);
			GV_ITEM item = CGridUtils::CreateGridItem(idx, 0, GVIF_TEXT | GVIF_FORMAT, DT_RIGHT | DT_WORDBREAK, str);
			item.mask |= GVIF_FGCLR;
			item.crFgClr = RGB(0,0,0);
			segGrid.SetItem(&item);
		}
	}
	
	
}

void CStatisticDlg::InitSegGridContent()
{
	if (segGrid.m_hWnd) {
		CapShowType *capShowType = CapShowType::GetInstance();
		CString str;
		
		if (capShowType->GetAutoPartCapChk() == MF_CHECKED)
		{
			for (int idx = 0; idx < capShowType->validenum; ++idx)
			{
				str = L"";
				str.Format(_T("%d"), capShowType->minVals[idx]);
				GV_ITEM minItem = CGridUtils::CreateGridItem(idx + 1, 1, GVIF_TEXT | GVIF_FORMAT, DT_RIGHT | DT_WORDBREAK, str);
				minItem.mask |= GVIF_FGCLR;
				minItem.crFgClr = capShowType->colorVals[idx];
				str.Format(_T("%d"), capShowType->maxVals[idx]);
				GV_ITEM maxItem = CGridUtils::CreateGridItem(idx + 1, 2, GVIF_TEXT | GVIF_FORMAT, DT_RIGHT | DT_WORDBREAK, str);
				maxItem.mask |= GVIF_FGCLR;
				maxItem.crFgClr = capShowType->colorVals[idx];

				str.Format(_T("%d"), distributeVals[idx]);
				GV_ITEM distribItem = CGridUtils::CreateGridItem(idx + 1, 3, GVIF_TEXT | GVIF_FORMAT, DT_RIGHT | DT_WORDBREAK, str);
				distribItem.mask |= GVIF_FGCLR;
				distribItem.crFgClr = capShowType->colorVals[idx];

				str.Format(_T("%.2f"), (distributeVals[idx] / valideBatCount)*100);
				GV_ITEM ratioItem = CGridUtils::CreateGridItem(idx + 1, 4, GVIF_TEXT | GVIF_FORMAT, DT_RIGHT | DT_WORDBREAK, str);
				ratioItem.mask |= GVIF_FGCLR;
				ratioItem.crFgClr = capShowType->colorVals[idx];

				segGrid.SetItem(&minItem);
				segGrid.SetItem(&maxItem);
				segGrid.SetItem(&distribItem);
				segGrid.SetItem(&ratioItem);
			}
		}
		else
		{
			for (int idx = 0; idx < capShowType->validenum; ++idx)
			{
				str = L"";
				str.Format(_T("%d"), capShowType->minVals[idx]);

				GV_ITEM minItem = CGridUtils::CreateGridItem(idx + 1, 1, GVIF_TEXT | GVIF_FORMAT, DT_RIGHT | DT_WORDBREAK, str);
				minItem.mask |= GVIF_FGCLR;
				minItem.crFgClr = RGB(0,0,0);
				str.Format(_T("%d"), capShowType->maxVals[idx]);
				GV_ITEM maxItem = CGridUtils::CreateGridItem(idx + 1, 2, GVIF_TEXT | GVIF_FORMAT, DT_RIGHT | DT_WORDBREAK, str);

				maxItem.mask |= GVIF_FGCLR;
				maxItem.crFgClr = RGB(0,0,0);

				str.Format(_T("%d"), distributeVals[idx]);
				GV_ITEM distribItem = CGridUtils::CreateGridItem(idx + 1, 3, GVIF_TEXT | GVIF_FORMAT, DT_RIGHT | DT_WORDBREAK, str);
				distribItem.mask |= GVIF_FGCLR;
				distribItem.crFgClr = RGB(0, 0, 0);

				str.Format(_T("%.2f"), (distributeVals[idx] / valideBatCount) * 100);
				GV_ITEM ratioItem = CGridUtils::CreateGridItem(idx + 1, 4, GVIF_TEXT | GVIF_FORMAT, DT_RIGHT | DT_WORDBREAK, str);
				ratioItem.mask |= GVIF_FGCLR;
				ratioItem.crFgClr = RGB(0, 0, 0);

				segGrid.SetItem(&minItem);
				segGrid.SetItem(&maxItem);
				segGrid.SetItem(&distribItem);
				segGrid.SetItem(&ratioItem);
			}
		}
		segGrid.Invalidate();
	}
	//if (segGrid.m_hWnd) {
	//	CapShowType *capShowType = CapShowType::GetInstance();
	//	CString str;
	//	for (int idx = 0; idx < SEG_ROW_COUNT - 1; ++idx)
	//	{
	//		str = L"";
	//		str.Format(_T("%d"), capShowType->minVals[idx]);
	//		GV_ITEM minItem = CGridUtils::CreateGridItem(idx + 1, 1, GVIF_TEXT | GVIF_FORMAT, DT_RIGHT | DT_WORDBREAK, str);
	//		if (capShowType->GetAutoPartCapChk() == MF_CHECKED&&str != L"")
	//		{
	//			minItem.mask |= GVIF_FGCLR;

	//			minItem.crFgClr = capShowType->colorVals[idx];
	//		}
	//		str = L"";
	//		str.Format(_T("%d"), capShowType->maxVals[idx]);
	//		GV_ITEM maxItem = CGridUtils::CreateGridItem(idx + 1, 2, GVIF_TEXT | GVIF_FORMAT, DT_RIGHT | DT_WORDBREAK, str);
	//		if (capShowType->GetAutoPartCapChk() == MF_CHECKED &&str != L"")
	//		{
	//			maxItem.mask |= GVIF_FGCLR;
	//			maxItem.crFgClr = capShowType->colorVals[idx];
	//		}

	//		segGrid.SetItem(&minItem);
	//		segGrid.SetItem(&maxItem);
	//	}

	//	segGrid.Invalidate();
	//}
	
}

void CStatisticDlg::InitCapGridSize()
{
	groupNumPerCol = testInfo.groupNumPerCol;
	colShowNum = testInfo.colShowNum;
	numPerGroup = testInfo.numPerGroup;

	batCount = groupNumPerCol * colShowNum * numPerGroup;

	capGrid.SetRowCount(batCount + 1);
	capGrid.SetColumnCount(2);
	capGrid.SetFixedRowCount(1);
	capGrid.SetFixedColumnCount(1);

}

void CStatisticDlg::InitCapGridColHead()
{
	int groupCount = groupNumPerCol * colShowNum;
	int groupCount2 = (numPerGroup + subGroupBatNum - 1) / subGroupBatNum;
	int seqId = 1;
	CString cabIdStr, str, str2, str3;

	cabIdStr.Format(_T("%d"), testInfo.cabinet);

	for (int groupIdx = 1; groupIdx <= groupCount; ++groupIdx)
	{
		str.Format(_T("%d"), groupIdx);
		str = groupIdx < 10 ? L"0" + str : str;

		for (int groupIdx2 = 1; groupIdx2 <= groupCount2; ++groupIdx2)
		{
			str2.Format(_T("%d"), groupIdx2);

			for (int groupIdx3 = 1; groupIdx3 <= subGroupBatNum; ++groupIdx3)
			{
				str3.Format(_T("%d"), groupIdx3);

				GV_ITEM item = CGridUtils::CreateGridItem(seqId++, 0, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"#" + cabIdStr + L": " + str + L"-" + str2 + L"-" + str3);
				
				capGrid.SetItem(&item);
			}
		}
	}
}

void CStatisticDlg::InitCapGridRowHead()
{
	if (capGrid.m_hWnd) {
		GV_ITEM seqHeadItem = CGridUtils::CreateGridItem(0, 0, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"位号");
		GV_ITEM capHeadItem = CGridUtils::CreateGridItem(0, 1, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"容量(mAh)");

		capGrid.SetItem(&seqHeadItem);
		capGrid.SetItem(&capHeadItem);
	}
	
}

void CStatisticDlg::InitCapGridContent()
{
	if (capGrid.m_hWnd)
	{
		CString str;
		CapShowType *capShowType = CapShowType::GetInstance();
		if (capShowType->GetAutoPartCapChk() == MF_CHECKED)
		{
			for (int jdx = 0; jdx < endDisBatterys.size(); ++jdx)
			{
				if (endDisBatterys[jdx] != NULL) {
					str = capShowType->flagVals[endDisBatterys[jdx]->capFlag] + L"  " + endDisBatterys[jdx]->capacity;

					capGrid.SetItemFgColour(endDisBatterys[jdx]->batId, 1, capShowType->colorVals[endDisBatterys[jdx]->capFlag]);
					capGrid.SetItemText(endDisBatterys[jdx]->batId, 1, str);
				}
			}
		}
		else
		{
			for (int jdx = 0; jdx < endDisBatterys.size(); ++jdx)
			{
				if (endDisBatterys[jdx] != NULL) {
					str = endDisBatterys[jdx]->capacity;

					capGrid.SetItemFgColour(endDisBatterys[jdx]->batId, 1, RGB(0, 0, 0));
					capGrid.SetItemText(endDisBatterys[jdx]->batId, 1, str);
				}
			}
		}

	}
	//if (capGrid.m_hWnd)
	//{

	//	for (int jdx = 0; jdx < endDisBatterys.size(); ++jdx)
	//	{
	//		if (endDisBatterys[jdx] != NULL) {
	//			GV_ITEM item = CGridUtils::CreateGridItem(endDisBatterys[jdx]->batId, 1, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, endDisBatterys[jdx]->capacity);
	//			capGrid.SetItem(&item);
	//		}
	//	}
	//}
}

void CStatisticDlg::UpdateSegData(int autoCheck)
{
	if (segGrid.m_hWnd) {
		CapShowType *capShowType = CapShowType::GetInstance();
		CString str;
		CreateDistribData();
		if (capShowType->GetAutoPartCapChk() == MF_CHECKED)
		{
			for (int idx = 0; idx < capShowType->validenum; ++idx)
			{
				str = L"";
				str.Format(_T("%d"), capShowType->minVals[idx]);
				segGrid.SetItemText(idx + 1, 1, str);

				segGrid.SetItemFgColour(idx + 1, 1, capShowType->colorVals[idx]);
				str.Format(_T("%d"), capShowType->maxVals[idx]);

				segGrid.SetItemText(idx + 1, 2, str);
				segGrid.SetItemFgColour(idx + 1, 2, capShowType->colorVals[idx]);
				
				str.Format(_T("%d"), distributeVals[idx]);
				segGrid.SetItemText(idx + 1, 3, str);
				segGrid.SetItemFgColour(idx + 1, 3, capShowType->colorVals[idx]);

				str.Format(_T("%.2f"), (distributeVals[idx] / valideBatCount) * 100);
				segGrid.SetItemText(idx + 1, 4, str);
				segGrid.SetItemFgColour(idx + 1, 4, capShowType->colorVals[idx]);

				str.Format(_T("%d"), idx+1);
				str = capShowType->flagVals[idx] == L"0" ? str : L"[" + capShowType->flagVals[idx] + L"] " + str;
				//segGrid.SetItemText(idx + 1, 0, str);
				segGrid.SetItemFgColour(idx + 1, 0, capShowType->colorVals[idx]);
			}
		}
		else
		{
			for (int idx = 0; idx < capShowType->validenum; ++idx)
			{
				str = L"";
				str.Format(_T("%d"), capShowType->minVals[idx]);
				segGrid.SetItemText(idx + 1, 1, str);
				segGrid.SetItemFgColour(idx + 1, 1, RGB(0, 0, 0));

				str.Format(_T("%d"), capShowType->maxVals[idx]);
				segGrid.SetItemText(idx + 1, 2, str);
				segGrid.SetItemFgColour(idx + 1, 2, RGB(0, 0, 0));

				str.Format(_T("%d"), distributeVals[idx]);
				segGrid.SetItemText(idx + 1, 3, str);
				segGrid.SetItemFgColour(idx + 1, 3, RGB(0, 0, 0));

				str.Format(_T("%.2f"), (distributeVals[idx] / valideBatCount) * 100);
				segGrid.SetItemText(idx + 1, 4, str);
				segGrid.SetItemFgColour(idx + 1, 4, RGB(0, 0, 0));

				str.Format(_T("%d"), idx + 1);
				segGrid.SetItemText(idx + 1, 0, str);
				segGrid.SetItemFgColour(idx + 1, 0, RGB(0, 0, 0));
			}
		}

		segGrid.Invalidate();
	}
}

void CStatisticDlg::UpdateCapData(int autoCheck)
{

	if (capGrid.m_hWnd)
	{
		CString str;
		CapShowType *capShowType = CapShowType::GetInstance();
		if (autoCheck == MF_CHECKED)
		{
			for (int jdx = 0; jdx < endDisBatterys.size(); ++jdx)
			{
				if (endDisBatterys[jdx] != NULL) {
					str = capShowType->flagVals[endDisBatterys[jdx]->capFlag]  + L"  " + endDisBatterys[jdx]->capacity;
						
					capGrid.SetItemFgColour(endDisBatterys[jdx]->batId, 1,capShowType->colorVals[endDisBatterys[jdx]->capFlag]);
					capGrid.SetItemText(endDisBatterys[jdx]->batId, 1, str);
				}
			}
		}
		else
		{
			for (int jdx = 0; jdx < endDisBatterys.size(); ++jdx)
			{
				if (endDisBatterys[jdx] != NULL) {
					str = endDisBatterys[jdx]->capacity;

					capGrid.SetItemFgColour(endDisBatterys[jdx]->batId, 1, RGB(0,0,0));
					capGrid.SetItemText(endDisBatterys[jdx]->batId, 1, str);
				}
			}
		}
		capGrid.Invalidate();
	}
}



void CStatisticDlg::OnBnClickedDisStatic()
{
	// TODO:  在此添加控件通知处理程序代码
}

void CStatisticDlg::InitCapChart()
{
	//SetCapChartPos();
	CreateDistribData();
	DrawDistribChart();
}

void CStatisticDlg::CreateDistribData()
{

	memset(distributeVals, 0, sizeof(int)*MAX_FLAG_NUM);

	CMDIFrameWnd* hMainFrame = (CMDIFrameWnd*)AfxGetMainWnd();
	CMDIChildWnd *hChild = (CMDIChildWnd *)hMainFrame->MDIGetActive();
	CView *hView = (CView *)hChild->GetActiveView();
	
	if (hView->IsKindOf(RUNTIME_CLASS(CDataFileView)))
	{
		CDataFileView *dataFileView = (CDataFileView*)hView;

		endDisBatterys = dataFileView->fileCabData.endDisBatterys;
		
		CapShowType *capShowType = CapShowType::GetInstance();
		int capFlag, capacity;
		valideBatCount = 0;
		for (int idx = 0; idx < endDisBatterys.size(); ++idx)
		{
			if (endDisBatterys[idx] != NULL)
			{
				capFlag = 0;
				capacity = _ttoi(endDisBatterys[idx]->capacity);
				while (capFlag < capShowType->validenum)
				{
					if (capacity <= capShowType->maxVals[capFlag])
					{
						endDisBatterys[idx]->capFlag = capFlag;
						distributeVals[capFlag]++;
						valideBatCount += 1;
						break;
					}
					else capFlag++;
				}
				if (capFlag == capShowType->validenum)
				{
					distributeVals[capFlag]++;
				}
			}
		}
	}
}

void CStatisticDlg::SetCapChartPos()
{
	CRect disRect;
	//disStatic.GetWindowRect(&disRect);

	disRect.left += GAP_WIDTH;
	disRect.right -= GAP_WIDTH;
	disRect.top += GAP_HEIGHT;
	disRect.bottom -= GAP_HEIGHT;

	disChart.MoveWindow(disRect);
}

void CStatisticDlg::DrawDistribChart()
{
	CapShowType *capShowType = CapShowType::GetInstance();

	for (int idx = 0; idx < disChart.get_SeriesCount(); idx++)
	{
		((CSeries)disChart.Series(idx)).Clear();
	}
	CSeries disSeries = (CSeries)disChart.Series(0);

	CString str, str2;
	for (int idx = 0; idx < capShowType->validenum; ++idx)
	{
		str.Format(_T("%d"), capShowType->minVals[idx]);
		str2.Format(_T("%d"), capShowType->maxVals[idx]);

		str = L"[" + str + L" - " + str2 + L"]";
		disSeries.AddXY(idx+1, distributeVals[idx], str, capShowType->colorVals[idx]);
	}

	disChart.Invalidate();
}

void CStatisticDlg::UpdateChartData()
{
	CreateDistribData();
	DrawDistribChart();
}
