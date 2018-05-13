// CompDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "CompDlg.h"
#include "WorkProcInfo.h"
#include "afxdialogex.h"
#include "WorkStateStr.h"


// CCompDlg 对话框

const int CACV_COL_NUM = 10;
const int CA_COL_NUM = 7;
const int LAY_COL_NUM = 4;
const int CADIS_COL_NUM = 15;


IMPLEMENT_DYNAMIC(CCompDlg, CDialog)

CCompDlg::CCompDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCompDlg::IDD, pParent)
{


}

CCompDlg::CCompDlg(CWnd* pParent, CFileCabData &fileCabData) : CDialog(CCompDlg::IDD, pParent)
{
	this->fileCabData = fileCabData;
	defColWidth = 100;
	defRowHeight = 24;
}


CCompDlg::~CCompDlg()
{
}

void CCompDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_COMP_LIST, compList);
	//DDX_Control(pDX, IDC_COMP_GRID, compGrid);
	DDX_Control(pDX, IDC_COMP_GRID, compGrid);

	DDX_Control(pDX, IDC_ATTR_COMBO, attrCom);
	DDX_Control(pDX, IDC_STEP_COMBO, stepCom);
	DDX_Control(pDX, IDC_DATETIME_COMBO, datatimeCom);
}


BEGIN_MESSAGE_MAP(CCompDlg, CDialog)
	ON_WM_SIZE()
	//ON_MESSAGE(WM_HORZ_MSG, &CCompDlg::OnGirdHScroll)
	ON_CBN_SELCHANGE(IDC_STEP_COMBO, &CCompDlg::OnCbnSelchangeStepCombo)
	ON_CBN_SELCHANGE(IDC_DATETIME_COMBO, &CCompDlg::OnCbnSelchangeDatetimeCombo)
END_MESSAGE_MAP()


// CCompDlg 消息处理程序


void CCompDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	
	if (this->m_hWnd) {
		CRect rect(0, 0, cx, cy);
		this->MoveWindow(rect.left + MARGIN_LEFT_BATPANE, rect.top + MARGIN_TOP_BATPANE-28, rect.Width(), rect.Height(), TRUE);
		//this->MoveWindow(rect.left + MARGIN_LEFT_BATPANE, rect.top, rect.Width(), rect.Height(), TRUE);
		//this->MoveWindow(rect.left + MARGIN_LEFT_BATPANE, rect.top, rect.Width(), rect.Height(), TRUE);
		if (compGrid.m_hWnd)
		{
			compGrid.MoveWindow(CRect(rect.left, rect.top + 28, rect.right, rect.bottom), true);
			compGrid.Invalidate();
		}
	}
	// TODO:  在此处添加消息处理程序代码
}


BOOL CCompDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CRect rect;
	GetWindowRect(&rect);  //获取窗口rect，

	CRect headRect = CRect(rect.left, rect.top, rect.right, rect.top + defRowHeight);
	CRect bodyRect = CRect(rect.left, rect.top + defRowHeight, rect.right, rect.bottom);
	//excepList.GetClientRect(&rect);
	//compGrid.MoveWindow(&bodyRect, true);

	// 为列表视图控件添加全行选中和栅格风格   
	//compGrid.SetExtendedStyle(compGrid.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	InitCombox();
	InitGridContent();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}



void CCompDlg::InitGridContent()
{
	//0 获取电池编号


	int groupNumPerCol = fileCabData.groupNumPerCol;
	int colShowNum = fileCabData.colShowNum;
	int numPerGroup = fileCabData.numPerGroup;
	int subGroupBatNum = 8;	//	表示八个电池一组

	//1 获取最大工步值
	
	//2 根据工步值进行判断所需显示信息列数,并生成相应的信息
	int colNum = 3;
	int headColNum = 2 + fileCabData.workProcInfos.size();


	GV_ITEM headBlankItem, headContentItem;
	headBlankItem = CGridUtils::CreateGridItem(0, 0, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"");
	headContentItem = CGridUtils::CreateGridItem(0, 1, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"数据内容");

	compGrid.SetItem(&headBlankItem);
	compGrid.SetItem(&headContentItem);


	//3 逐个工步插入相关数据
	int batCount = groupNumPerCol * colShowNum * numPerGroup;
	int groupId, subGroupId, subGroupBatId;
	CString groupIdCstr, subGroupIdCstr, subGroupBatIdCstr, str, rowIdxCstr;

	//增加表头
	int subHeadRowId = 1;
	int subHeadColId = 1;

	compGrid.SetRowCount(batCount + 2);
	compGrid.SetFixedRowCount(2);
	compGrid.SetFixedColumnCount(1); //表头为一列

	for (int idx = 0; idx < fileCabData.workProcInfos.size(); ++idx)
	{
		if (fileCabData.workProcInfos[idx].workStepName == CACV_WORKNAME_STR)
		{
			colNum += CACV_COL_NUM;
		}
		else if (fileCabData.workProcInfos[idx].workStepName == CA_WORKNAME_STR)
		{
			colNum += CA_COL_NUM;
		}
		else if (fileCabData.workProcInfos[idx].workStepName == CADIS_WORKNAME_STR)
		{
			colNum += CADIS_COL_NUM;
		}
		else if (fileCabData.workProcInfos[idx].workStepName == LAY_WORKNAME_STR)
		{
			colNum += LAY_COL_NUM;
		}
	}
	compGrid.SetColumnCount(colNum);
	compGrid.SetColumnWidth(0, defColWidth);
	compGrid.SetColumnWidth(1, defColWidth);
	GV_ITEM dataContentItem = CGridUtils::CreateGridItem(0, 1, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"数据内容");
	compGrid.SetItem(&dataContentItem);
	for (int idx = 0; idx < colNum; ++ idx)
	{
		compGrid.SetColumnWidth(idx, defColWidth);
	}
	int scrollPos = 0;
	for (int idx = 0; idx < fileCabData.workProcInfos.size(); ++idx)
	{
		str.Format(_T("%d"), idx + 1);
		str = str + L":";
		GV_ITEM titem;

		if (fileCabData.workProcInfos[idx].workStepName == CACV_WORKNAME_STR)
		{
			str += (fileCabData.workProcInfos[idx].workStepName).c_str();
			compGrid.MergeCells(0, subHeadColId+1, 0, subHeadColId + CACV_COL_NUM);
			titem = CGridUtils::CreateGridItem(0, subHeadColId + 1, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
			compGrid.SetItem(&titem);
			subHeadColId += CACV_COL_NUM;
			scrollPoss.push_back(scrollPos + CACV_COL_NUM * defColWidth);
			scrollPos += CACV_COL_NUM * defColWidth;
		}
		else if (fileCabData.workProcInfos[idx].workStepName == CA_WORKNAME_STR)
		{
			str += (fileCabData.workProcInfos[idx].workStepName).c_str();
			compGrid.MergeCells(0, subHeadColId+1, 0, subHeadColId + CA_COL_NUM);
			titem = CGridUtils::CreateGridItem(0, subHeadColId + 1, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
			compGrid.SetItem(&titem);
			subHeadColId += CA_COL_NUM;
			scrollPoss.push_back(scrollPos + CA_COL_NUM * defColWidth);
			scrollPos += CA_COL_NUM * defColWidth;
		}
		else if (fileCabData.workProcInfos[idx].workStepName == CADIS_WORKNAME_STR)
		{
			str += (fileCabData.workProcInfos[idx].workStepName).c_str();
			compGrid.MergeCells(0, subHeadColId+1, 0, subHeadColId + CADIS_COL_NUM);
			titem = CGridUtils::CreateGridItem(0, subHeadColId + 1, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
			compGrid.SetItem(&titem);
			subHeadColId += CADIS_COL_NUM;
			scrollPoss.push_back(scrollPos + CADIS_COL_NUM*defColWidth);
			scrollPos += CADIS_COL_NUM*defColWidth;
		}
		else if (fileCabData.workProcInfos[idx].workStepName == LAY_WORKNAME_STR)
		{
			str += (fileCabData.workProcInfos[idx].workStepName).c_str();
			compGrid.MergeCells(0, subHeadColId+1, 0, subHeadColId + LAY_COL_NUM);
			titem = CGridUtils::CreateGridItem(0, subHeadColId + 1, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
			compGrid.SetItem(&titem);
			subHeadColId += LAY_COL_NUM;
			scrollPoss.push_back(scrollPos + LAY_COL_NUM*defColWidth);
			scrollPos += LAY_COL_NUM*defColWidth;
		}
	}

	GV_ITEM headItem = CGridUtils::CreateGridItem(subHeadRowId, 0, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"电池工位");
	compGrid.SetItem(&headItem);

	GV_ITEM seqItem = CGridUtils::CreateGridItem(subHeadRowId, 1, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"电芯编号");
	compGrid.SetItem(&seqItem);

	for (int idx = 0; idx < colNum; ++idx)
	{
		compGrid.SetColumnWidth(idx, defColWidth);
	}
	int workProcsLength = fileCabData.workProcInfos.size();
	if (fileCabData.workProcInfos.size() > 0 && fileCabData.workProcInfos[workProcsLength - 1].workStepName == END_STR)
		workProcsLength -= 1;
	subHeadColId = 1;
	for (int idx = 0; idx < workProcsLength; ++idx)
	{
		str.Format(_T("%d"), idx);

		if (fileCabData.workProcInfos[idx].workStepName == CACV_WORKNAME_STR)
		{
			// 开路电压

			GV_ITEM openVoltItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"开路电压(mV)");
			compGrid.SetItem(&openVoltItem);
			// 平均电压
			GV_ITEM avgVoltItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"平均电压(mV)");
			compGrid.SetItem(&avgVoltItem);
			// 终止电压
			GV_ITEM endVoltItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"终止电压(mV)");
			compGrid.SetItem(&endVoltItem);
			// 时间
			GV_ITEM timeItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"时间(min)");
			compGrid.SetItem(&timeItem);
			// 容量
			GV_ITEM quantityItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"容量(mAh)");
			compGrid.SetItem(&quantityItem);
			// 电量
			GV_ITEM capacityItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"电量(mAh)");
			compGrid.SetItem(&capacityItem);
			// 结束电流
			GV_ITEM endCurrentItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"终止电流(mAh)");
			compGrid.SetItem(&endCurrentItem);

			// 恒流时间
			GV_ITEM constCrntTimeItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"恒流时间(min)");
			compGrid.SetItem(&constCrntTimeItem);
			// 恒流容量
			GV_ITEM constQuantItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"恒流容量(mAh)");
			compGrid.SetItem(&constQuantItem);
			// 所占比例
			GV_ITEM ratioItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"所占比例(%)");
			compGrid.SetItem(&ratioItem);
		}
		else if (fileCabData.workProcInfos[idx].workStepName == CA_WORKNAME_STR)
		{
			// 开路电压
			GV_ITEM openVoltItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"开路电压(mV)");
			compGrid.SetItem(&openVoltItem);
			// 平均电压
			GV_ITEM avgVoltItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"平均电压(mV)");
			compGrid.SetItem(&avgVoltItem);
			// 终止电压
			GV_ITEM endVoltItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"终止电压(mV)");
			compGrid.SetItem(&endVoltItem);
			// 时间
			GV_ITEM timeItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"时间(min)");
			compGrid.SetItem(&timeItem);
			// 容量
			GV_ITEM quantityItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"容量(mAh)");
			compGrid.SetItem(&quantityItem);
			// 电量
			GV_ITEM capacityItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"电量(mAh)");
			compGrid.SetItem(&capacityItem);
			// 结束电流
			GV_ITEM endCurrentItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"终止电流(mAh)");
			compGrid.SetItem(&endCurrentItem);
		}
		else if (fileCabData.workProcInfos[idx].workStepName == CADIS_WORKNAME_STR)
		{
			// 开路电压
			GV_ITEM openVoltItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"开路电压(mV)");
			compGrid.SetItem(&openVoltItem);
			// 平均电压
			GV_ITEM avgVoltItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"平均电压(mV)");
			compGrid.SetItem(&avgVoltItem);
			// 终止电压
			GV_ITEM endVoltItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"终止电压(mV)");
			compGrid.SetItem(&endVoltItem);
			// 时间
			GV_ITEM timeItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"时间(min)");
			compGrid.SetItem(&timeItem);
			// 容量
			GV_ITEM quantityItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"容量(mAh)");
			compGrid.SetItem(&quantityItem);
			// 电量
			GV_ITEM capacityItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"电量(mAh)");
			compGrid.SetItem(&capacityItem);
			// 终止电流
			GV_ITEM endCurrentItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"终止电流(mAh)");
			compGrid.SetItem(&endCurrentItem);

			// 容量耗损(mAh)
			GV_ITEM quantLessItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"容量耗损(mAh)");
			compGrid.SetItem(&quantLessItem);
			// 放电效率(%)
			GV_ITEM disEffItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"放电效率(%)");
			compGrid.SetItem(&disEffItem);
			// 损失比(%)
			GV_ITEM lessRatioItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"损失比(%)");
			compGrid.SetItem(&lessRatioItem);
			// 放电比率(%)
			GV_ITEM disRatioItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"放电比率(%)");
			compGrid.SetItem(&disRatioItem);
			// SD (%)
			GV_ITEM sdItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"SD (%)");
			compGrid.SetItem(&sdItem);
			// 中值电压(mV)
			GV_ITEM midValItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"中值电压(mV)");
			compGrid.SetItem(&midValItem);
			// #3600mV(min)
			GV_ITEM flagMinItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"#3600mV(min)");
			compGrid.SetItem(&flagMinItem);
			// #3600mV(mAh)
			GV_ITEM flagMahItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"#3600mV(mAh)");
			compGrid.SetItem(&flagMahItem);

		}
		else if (fileCabData.workProcInfos[idx].workStepName == LAY_WORKNAME_STR)
		{
			// 开路电压
			GV_ITEM openVoltItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"开路电压(mV)");
			compGrid.SetItem(&openVoltItem);
			// 平均电压
			GV_ITEM avgVoltItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"平均电压(mV)");
			compGrid.SetItem(&avgVoltItem);
			// 终止电压
			GV_ITEM endVoltItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"终止电压(mV)");
			compGrid.SetItem(&endVoltItem);
			// 时间
			GV_ITEM timeItem = CGridUtils::CreateGridItem(subHeadRowId, ++subHeadColId, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, L"时间(min)");
			compGrid.SetItem(&timeItem);
		}
	}
	int colIdx = 2;
	for (int rowIdx = 0; rowIdx < batCount; ++rowIdx)
	{
		groupId = rowIdx / numPerGroup + 1;
		subGroupId = (rowIdx % numPerGroup) / subGroupBatNum + 1;
		subGroupBatId = (rowIdx % numPerGroup) % subGroupBatNum + 1;

		groupIdCstr.Format(_T("%d"), groupId);
		groupIdCstr = groupId < 10 ? L"0" + groupIdCstr : groupIdCstr;

		subGroupIdCstr.Format(_T("%d"), subGroupId);


		subGroupBatIdCstr.Format(_T("%d"), subGroupBatId);


		rowIdxCstr.Format(_T("%d"), rowIdx + 1);

		str = groupIdCstr + L"-" + subGroupIdCstr + L"-" + subGroupBatIdCstr;

		GV_ITEM seqItem = CGridUtils::CreateGridItem(rowIdx + 2, 0, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
		compGrid.SetItem(&seqItem);
		GV_ITEM numItem = CGridUtils::CreateGridItem(rowIdx + 2, 1, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, rowIdxCstr);
		compGrid.SetItem(&numItem);
	}

	colIdx = FillGridContentByBatData(colIdx, workProcsLength, fileCabData.workProcInfos, str);

	compGrid.Invalidate();
}



int CCompDlg::FillGridContentByBatData(int colIdx, int workProcsLength, vector<WorkProcInfo> &workProcInfos, CString &str)
{
	colIdx = 2;
	int idx, preCoIdx = colIdx = 1;

	vector<vector<int> > preDisCapacitys; // 记录每一块电池每一个工步所有充电工步的容量和
	int preDisIdx = 0;
	vector<int> preDisBatCapacity;
	int cacvIdx = 0;	//标记CACV所对应的cacvStepInfos的游标	
	double cacvRatio = 0;

	for (int jdx = 0; jdx < workProcsLength; ++jdx)
	{
		int stepId = jdx + 1;
		vector<CBatStepInfo> batStepInfos = fileCabData.batStepInfos[jdx];
		if (batStepInfos.size() < 0)
			continue;
		
		int rowContentDis = 1;

		preDisCapacitys.push_back(preDisBatCapacity);

		for (int idx = 0; idx < batStepInfos.size(); ++ idx)
		{
			preDisCapacitys[preDisIdx].push_back(0); //为每一块电池设置初始的充电电量累积值

			colIdx = preCoIdx;
			int rowIdx = batStepInfos[idx].startStepInfo.batId + rowContentDis;
			if (fileCabData.workProcInfos[jdx].workStepName == CACV_WORKNAME_STR)
			{
				// 开路电压
				str.Format(_T("%d"), int(batStepInfos[idx].startStepInfo.voltage));
				GV_ITEM openVoltItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&openVoltItem);
				// 平均电压
				str.Format(_T("%d"), int(batStepInfos[idx].avgVolt));
				GV_ITEM avgVoltItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&avgVoltItem);
				// 终止电压
				str.Format(_T("%d"), int(batStepInfos[idx].endStepInfo.voltage + 0.5));
				GV_ITEM endVoltItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&endVoltItem);
				// 时间
				str.Format(_T("%d"), int(batStepInfos[idx].endStepInfo.atime));
				GV_ITEM timeItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&timeItem);
				// 容量
				str.Format(_T("%d"), int(batStepInfos[idx].endStepInfo.capacity));
				GV_ITEM quantityItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&quantityItem);
				// 累计放电工步前的容量和
				preDisCapacitys[preDisIdx][idx] += batStepInfos[idx].endStepInfo.capacity;

				// 电量
				str.Format(_T("%d"), int(batStepInfos[idx].endStepInfo.energy));
				GV_ITEM capacityItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&capacityItem);
				// 结束电流
				str.Format(_T("%d"), int(batStepInfos[idx].endStepInfo.curnt));
				GV_ITEM endCurrentItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&endCurrentItem);

				// 恒流时间
				str.Format(_T("%d"), int(fileCabData.cacvStepInfos[cacvIdx][idx].atime));
				GV_ITEM constCrntTimeItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&constCrntTimeItem);
				// 恒流容量
				str.Format(_T("%d"), int(fileCabData.cacvStepInfos[cacvIdx][idx].capacity));
				GV_ITEM constQuantItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&constQuantItem);
				// 所占比例
				cacvRatio = (fileCabData.cacvStepInfos[cacvIdx][idx].capacity) / (double)(batStepInfos[idx].endStepInfo.capacity);
				str.Format(_T("%.2f"), cacvRatio*100);
				GV_ITEM ratioItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&ratioItem);



			}
			else if (fileCabData.workProcInfos[jdx].workStepName == CA_WORKNAME_STR)
			{
				// 开路电压
				str.Format(_T("%d"), (int)batStepInfos[idx].startStepInfo.voltage);
				GV_ITEM openVoltItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&openVoltItem);
				// 平均电压
				str.Format(_T("%d"), (int)batStepInfos[idx].avgVolt);
				GV_ITEM avgVoltItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&avgVoltItem);
				// 终止电压
				str.Format(_T("%d"), (int)batStepInfos[idx].endStepInfo.voltage);
				GV_ITEM endVoltItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&endVoltItem);
				// 时间
				str.Format(_T("%d"), (int)batStepInfos[idx].endStepInfo.atime);
				GV_ITEM timeItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&timeItem);
				// 容量
				str.Format(_T("%d"), (int)batStepInfos[idx].endStepInfo.capacity);
				GV_ITEM quantityItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&quantityItem);
				// 累计放电工步前的容量和
				preDisCapacitys[preDisIdx][idx] += batStepInfos[idx].endStepInfo.capacity;
				// 电量
				str.Format(_T("%d"), (int)batStepInfos[idx].endStepInfo.energy);
				GV_ITEM capacityItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&capacityItem);
				// 结束电流
				str.Format(_T("%d"), (int)batStepInfos[idx].endStepInfo.curnt);
				GV_ITEM endCurrentItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&endCurrentItem);
			}
			else if (fileCabData.workProcInfos[jdx].workStepName == CADIS_WORKNAME_STR)
			{
				// 开路电压
				str.Format(_T("%d"), int(batStepInfos[idx].startStepInfo.voltage));
				GV_ITEM openVoltItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&openVoltItem);
				// 平均电压
				str.Format(_T("%d"), int(batStepInfos[idx].avgVolt + 0.5));
				GV_ITEM avgVoltItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&avgVoltItem);
				// 终止电压
				str.Format(_T("%d"), int(batStepInfos[idx].endStepInfo.voltage));
				GV_ITEM endVoltItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&endVoltItem);
				// 时间
				str.Format(_T("%d"), int(batStepInfos[idx].endStepInfo.atime));
				GV_ITEM timeItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&timeItem);
				// 容量
				str.Format(_T("%d"), int(batStepInfos[idx].endStepInfo.capacity));
				GV_ITEM quantityItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&quantityItem);
								
				// 电量
				str.Format(_T("%d"), int(batStepInfos[idx].endStepInfo.energy));
				GV_ITEM capacityItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&capacityItem);
				// 终止电流
				str.Format(_T("%d"), int(abs(batStepInfos[idx].endStepInfo.curnt)));
				GV_ITEM endCurrentItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&endCurrentItem);

				// 容量耗损(mAh)
				str.Format(_T("%d"), (int)(preDisCapacitys[preDisIdx][idx] - batStepInfos[idx].endStepInfo.capacity));
				GV_ITEM quantLessItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&quantLessItem);
				// 放电效率(%)
				double disEffVal = (preDisCapacitys[preDisIdx][idx] - batStepInfos[idx].endStepInfo.capacity) / (double)preDisCapacitys[preDisIdx][idx] * 100;
				str.Format(_T("%.2f"), disEffVal);
				GV_ITEM disEffItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&disEffItem);
				// 损失比(%)
				str.Format(_T("%.2f"), 100 - disEffVal);
				GV_ITEM lessRatioItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&lessRatioItem);
				// 放电比率(%)
				str.Format(_T("%.2f"), (double)0);
				GV_ITEM disRatioItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&disRatioItem);
				// SD (%)
				str.Format(_T("%.2f"), (double)0);
				GV_ITEM sdItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&sdItem);
				// 中值电压(mV)
				str.Format(_T("%d"), int(batStepInfos[idx].startStepInfo.voltage + batStepInfos[idx].endStepInfo.voltage) / 2.0 + 0.5);
				GV_ITEM midValItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&midValItem);
				// #3600mV(min)
				str.Format(_T("%.2f"), (double)0);
				GV_ITEM flagMinItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&flagMinItem);
				// #3600mV(mAh)
				str.Format(_T("%.2f"), (double)0);
				GV_ITEM flagMahItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&flagMahItem);

			}
			else if (fileCabData.workProcInfos[jdx].workStepName == LAY_WORKNAME_STR)
			{
				// 开路电压
				str.Format(_T("%d"), int(batStepInfos[idx].startStepInfo.voltage));
				GV_ITEM openVoltItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&openVoltItem);
				// 平均电压
				str.Format(_T("%d"), int(batStepInfos[idx].avgVolt + 0.5));
				GV_ITEM avgVoltItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&avgVoltItem);
				// 终止电压
				str.Format(_T("%d"), int(batStepInfos[idx].endStepInfo.voltage));
				GV_ITEM endVoltItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&endVoltItem);
				// 时间
				str.Format(_T("%d"), int(batStepInfos[idx].endStepInfo.atime));
				GV_ITEM timeItem = CGridUtils::CreateGridItem(rowIdx, ++colIdx, GVIF_TEXT | GVIF_FORMAT, DT_CENTER | DT_WORDBREAK, str);
				compGrid.SetItem(&timeItem);
			}
		}

		if (fileCabData.workProcInfos[jdx].workStepName == CADIS_WORKNAME_STR)
		{
			// 增加新一轮的放电工步电量累计
			preDisCapacitys.push_back(preDisBatCapacity);
			preDisIdx++;
		}
		else if (fileCabData.workProcInfos[jdx].workStepName == CACV_WORKNAME_STR)
		{
			cacvIdx++;
		}
		preCoIdx = colIdx;
	}
	return colIdx;
}	

void CCompDlg::InitCombox()
{
	CString attrArrays[ATTR_COUNT] = { L"容量", L"时间", L"开路电压", L"平均电压", L"终止电压", L"电量", L"终止电流" };

	for (int idx = 0; idx < ATTR_COUNT; ++idx)
	{
		attrCom.AddString(attrArrays[idx]);
	}

	CString str, str2;
	int length = fileCabData.workProcInfos.size();
	if (length > 0 && fileCabData.workProcInfos[length - 1].workStepName == END_STR)
	{
		length--;
	}
	for (int idx = 0; idx < length; ++idx)
	{
		str.Format(_T("%d"), idx+1);
		//str2.Format(_T("%d"), fileCabData.workProcInfos[idx].loopId == 0 ? 1 : fileCabData.workProcInfos[idx].loopId);
		//str += L": (" + str2 + L")";
		str2 = (fileCabData.workProcInfos[idx].workStepName).c_str();

		str += L":(1) " + str2;

		stepCom.AddString(str);
	}
	str = (fileCabData.testInfo.startTime).c_str();
	datatimeCom.AddString(str);

	attrCom.SetCurSel(0);
	stepCom.SetCurSel(0);
	datatimeCom.SetCurSel(0);


}


void CCompDlg::OnCbnSelchangeStepCombo()
{
	int scrollIdx = stepCom.GetCurSel();

	SCROLLINFO scrollInfo;
	compGrid.GetScrollInfo(SB_HORZ, &scrollInfo);
	
	int scrollPos = scrollIdx == 0 ? 0 : scrollPoss[scrollIdx-1];


#ifndef GRIDCONTROL_NO_TITLETIPS
	compGrid.m_TitleTip.Hide();  // hide any titletips
#endif

	//int scrollPos = compGrid.GetScrollPos32(SB_HORZ);

	CCellID idTopLeft = compGrid.GetTopleftNonFixedCell();

	CRect rect;
	GetClientRect(rect);


	//compGrid.SetScrollPos32(SB_HORZ, compGrid.GetScrollPos32(SB_HORZ, TRUE));
	compGrid.SetScrollPos32(SB_HORZ, scrollPos);
	compGrid.m_idTopLeftCell.row = -1;
	CCellID idNewTopLeft = compGrid.GetTopleftNonFixedCell();
	if (idNewTopLeft != idTopLeft)
	{
		rect.left = compGrid.GetFixedColumnWidth();
		InvalidateRect(rect);
	}

	compGrid.Invalidate();
}


void CCompDlg::OnCbnSelchangeDatetimeCombo()
{
	// TODO:  在此添加控件通知处理程序代码
}
