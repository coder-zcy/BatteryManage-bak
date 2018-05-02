// BCG_OptionDLG.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "BCG_OptionDLG.h"
#include "afxdialogex.h"


// CBCG_OptionDLG �Ի���

IMPLEMENT_DYNAMIC(CBCG_OptionDLG, CDialog)

CBCG_OptionDLG::CBCG_OptionDLG(CWnd* pParent /*=NULL*/, CFileStepData &fileStepData)
	: CDialog(CBCG_OptionDLG::IDD, pParent)
{
	level = 0;
	cabChecks.clear();
	this->fileStepData = fileStepData;
}

CBCG_OptionDLG::~CBCG_OptionDLG()
{

}

void CBCG_OptionDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BCG_CONDITION_GRID, condGrid);
	DDX_Control(pDX, IDC_BCG_GRADE_COMBO, levelComb);
	DDX_Control(pDX, IDC_BCG_CAP_CHECK, capCheck);
	DDX_Control(pDX, IDC_BCG_TIME_CHECK, timeCheck);
	DDX_Control(pDX, IDC_BCG_OPEN_CHECK, openCheck);
	DDX_Control(pDX, IDC_BCG_AVG_CHECK, avgCheck);
	DDX_Control(pDX, IDC_BCG_POINT_CHECK1, point1Check);
	DDX_Control(pDX, IDC_BCG_POINT_CHECK2, point2Check);
	DDX_Control(pDX, IDC_BCG_POINT_CHECK3, point3Check);
	DDX_Control(pDX, IDC_BCG_POINT_CHECK4, point4Check);
	DDX_Control(pDX, IDC_BCG_POINT_CHECK5, point5Check);
	DDX_Control(pDX, IDC_BCG_END_CHECK, endCheck);
	DDX_Control(pDX, IDC_BCG_INNER_CHECK, resistCheck);
	DDX_Control(pDX, IDC_BCG_SD_CHECK, sdCheck);
	DDX_Control(pDX, IDC_BCG_MID_CHECK, midCheck);
	DDX_Control(pDX, IDC_BCG_CODE_COMBO, codeComb);
	DDX_Control(pDX, IDC_BCG_REMARKS_EDIT, remarksEdit);
	DDX_Control(pDX, IDC_BCG_FILENAME_EDIT, filenameEdit);
	DDX_Control(pDX, IDC_CAB1_CHECK, cab1Check);
	DDX_Control(pDX, IDC_CAB2_CHECK, cab2Check);
	DDX_Control(pDX, IDC_CAB3_CHECK, cab3Check);
	DDX_Control(pDX, IDC_CAB4_CHECK, cab4Check);
	DDX_Control(pDX, IDC_CAB5_CHECK, cab5Check);
	DDX_Control(pDX, IDC_CAB6_CHECK, cab6Check);
	DDX_Control(pDX, IDC_CAB7_CHECK, cab7Check);
	DDX_Control(pDX, IDC_CAB8_CHECK, cab8Check);
	DDX_Control(pDX, IDC_CAB9_CHECK, cab9Check);
	DDX_Control(pDX, IDC_CAB10_CHECK, cab10Check);
	DDX_Control(pDX, IDC_CAB11_CHECK, cab11Check);
	DDX_Control(pDX, IDC_CAB12_CHECK, cab12Check);
	DDX_Control(pDX, IDC_CAB13_CHECK, cab13Check);
	DDX_Control(pDX, IDC_CAB14_CHECK, cab14Check);
	DDX_Control(pDX, IDC_CAB15_CHECK, cab15Check);
	DDX_Control(pDX, IDC_CAB16_CHECK, cab16Check);
	DDX_Control(pDX, IDC_CAB17_CHECK, cab17Check);
	DDX_Control(pDX, IDC_CAB18_CHECK, cab18Check);
	DDX_Control(pDX, IDC_CAB19_CHECK, cab19Check);
	DDX_Control(pDX, IDC_CAB20_CHECK, cab20Check);
}


BEGIN_MESSAGE_MAP(CBCG_OptionDLG, CDialog)
	ON_CBN_SELCHANGE(IDC_BCG_GRADE_COMBO, &CBCG_OptionDLG::OnCbnSelchangeBcgOdlgCombo2)
	ON_BN_CLICKED(IDC_BCG_CAP_CHECK, &CBCG_OptionDLG::OnBnClickedCapCheck)
	ON_BN_CLICKED(IDC_BCG_TIME_CHECK, &CBCG_OptionDLG::OnBnClickedTimeCheck)
	ON_BN_CLICKED(IDC_BCG_OPEN_CHECK, &CBCG_OptionDLG::OnBnClickedOpenCheck)
	ON_BN_CLICKED(IDC_BCG_AVG_CHECK, &CBCG_OptionDLG::OnBnClickedAvgCheck)
	//ON_BN_CLICKED(IDC_BCG_ODlg_CHECK25, &CBCG_OptionDLG::OnBnClickedBcgOdlgCheck25)
	//ON_BN_CLICKED(IDC_BCG_ODlg_CHECK26, &CBCG_OptionDLG::OnBnClickedBcgOdlgCheck26)
	ON_BN_CLICKED(IDC_BCG_POINT_CHECK3, &CBCG_OptionDLG::OnBnClickedPointCheck3)
	ON_BN_CLICKED(IDC_BCG_POINT_CHECK4, &CBCG_OptionDLG::OnBnClickedPointCheck4)
	ON_BN_CLICKED(IDC_BCG_POINT_CHECK5, &CBCG_OptionDLG::OnBnClickedPointCheck5)
	ON_BN_CLICKED(IDC_BCG_END_CHECK, &CBCG_OptionDLG::OnBnClickedEndCheck)
	ON_BN_CLICKED(IDC_BCG_INNER_CHECK, &CBCG_OptionDLG::OnBnClickedInnerCheck)
	ON_BN_CLICKED(IDC_BCG_SD_CHECK, &CBCG_OptionDLG::OnBnClickedSdCheck)
	ON_BN_CLICKED(IDC_BCG_MID_CHECK, &CBCG_OptionDLG::OnBnClickedMidCheck)
	ON_BN_CLICKED(IDOK, &CBCG_OptionDLG::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BCG_BROWSE_BTN, &CBCG_OptionDLG::OnBnClickedBcgBrowseBtn)
	ON_BN_CLICKED(IDC_BCG_SAVE_BTN, &CBCG_OptionDLG::OnBnClickedBcgSaveBtn)
	ON_BN_CLICKED(IDC_BCG_DEL_BTN, &CBCG_OptionDLG::OnBnClickedBcgDelBtn)
	ON_BN_CLICKED(IDC_BCG_POINT_CHECK1, &CBCG_OptionDLG::OnBnClickedBcgPointCheck1)
	ON_BN_CLICKED(IDC_BCG_POINT_CHECK2, &CBCG_OptionDLG::OnBnClickedBcgPointCheck2)
	ON_CBN_SELCHANGE(IDC_BCG_CODE_COMBO, &CBCG_OptionDLG::OnCbnSelchangeBcgCodeCombo)

	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_BCG_CONDITION_GRID, OnGridEndEdit)
END_MESSAGE_MAP()

BOOL CBCG_OptionDLG::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitChecks();

	if (fileStepData.testInfo.cabinet > 0)
	{
		cabChecks[fileStepData.testInfo.cabinet - 1]->SetCheck(BST_CHECKED);
	}
	for (int i = 0; i < 100; ++i){
		CString str;
		str.Format(_T("%d"), i + 1);
		levelComb.InsertString(i, str);
	}

	InitCondGrid();

	//m_GridCtrl.SetFixedColumnCount(1);
	InitDlgAssembly();

	return TRUE;
}

void CBCG_OptionDLG::InitCondGrid()
{
	CapGradeConf * capGradeConf = CapGradeConf::GetInstance();

	condGrid.SetEditable(true);
	condGrid.SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));//��ɫ����
	//��ʼ���б��趨��ʼ���������Լ������������
	CGradeDetailInfo gradeDetailInfo = capGradeConf->gradeDetailInfos[capGradeConf->codeSel];
	int colCount = 0, idx = 0, jdx = 0, colIdx = 0;

	for (idx = 0; idx < gradeDetailInfo.para.GetLength(); ++idx)
	{
		if (gradeDetailInfo.para[idx] == '1') colCount++;
	}

	condGrid.SetRowCount(gradeDetailInfo.levelCount + 1);
	condGrid.SetColumnCount(2 + colCount*2);

	condGrid.SetFixedRowCount(1);
	condGrid.SetFixedColumnCount(1);
	
	//��ʼ������е�vector
	record_col2idx.clear();

	record_col2idx.push_back(_T("����"));
	record_col2show[_T("����")] = false;

	record_col2idx.push_back(_T("ʱ��"));
	record_col2show[_T("ʱ��")] = false;

	record_col2idx.push_back(_T("��·��ѹ"));
	record_col2show[_T("��·��ѹ")] = false;

	record_col2idx.push_back(_T("ƽ����ѹ"));
	record_col2show[_T("ƽ����ѹ")] = false;

	record_col2idx.push_back(_T("��������1"));
	record_col2show[_T("��������1")] = false;

	record_col2idx.push_back(_T("��������2"));
	record_col2show[_T("��������2")] = false;

	record_col2idx.push_back(_T("��������3"));
	record_col2show[_T("��������3")] = false;

	record_col2idx.push_back(_T("��������4"));
	record_col2show[_T("��������4")] = false;

	record_col2idx.push_back(_T("��������5"));
	record_col2show[_T("��������5")] = false;

	record_col2idx.push_back(_T("���յ�ѹ"));
	record_col2show[_T("���յ�ѹ")] = false;

	record_col2idx.push_back(_T("����"));
	record_col2show[_T("����")] = false;

	record_col2idx.push_back(_T("SD"));
	record_col2show[_T("SD")] = false;

	record_col2idx.push_back(_T("��ֵ��ѹ"));
	record_col2show[_T("��ֵ��ѹ")] = false;

	int itemMask = GVIF_TEXT | GVIF_FORMAT;
	int itemFormat = DT_CENTER | DT_WORDBREAK;

	// ��ʼ����ͷ
	GV_ITEM seqHeadItem = CGridUtils::CreateGridItem(0, 0, itemMask, itemFormat, L"���");
	GV_ITEM gradeNameHeadItem = CGridUtils::CreateGridItem(0, 1, itemMask, itemFormat, L"�ȼ���");
	condGrid.SetItem(&seqHeadItem);
	condGrid.SetItem(&gradeNameHeadItem);

	for (idx = 0, colIdx = 2; idx < gradeDetailInfo.para.GetLength(); ++idx)
	{
		GV_ITEM startHeadItem, endHeadItem;
		if (gradeDetailInfo.para[idx] == '1') 
		{
			switch (idx)
			{
			case CAP_DIS_IDX:
				startHeadItem = CGridUtils::CreateGridItem(0, colIdx++, itemMask, itemFormat, record_col2idx[idx] + L">= mAh");
				endHeadItem = CGridUtils::CreateGridItem(0, colIdx++, itemMask, itemFormat, record_col2idx[idx] + L"< mAh");
				record_col2show[_T("����")] = TRUE;
				break;
			case TIME_DIS_IDX:
				startHeadItem = CGridUtils::CreateGridItem(0, colIdx++, itemMask, itemFormat, record_col2idx[idx] + L">= min");
				endHeadItem = CGridUtils::CreateGridItem(0, colIdx++, itemMask, itemFormat, record_col2idx[idx] + L"< min");
				record_col2show[_T("ʱ��")] = TRUE;
				break;
			case OPEN_DIS_IDX:
				startHeadItem = CGridUtils::CreateGridItem(0, colIdx++, itemMask, itemFormat, record_col2idx[idx] + L">= mV");
				endHeadItem = CGridUtils::CreateGridItem(0, colIdx++, itemMask, itemFormat, record_col2idx[idx] + L"< mV");
				record_col2show[_T("��·��ѹ")] = TRUE;
				break;
			case AVG_DIS_IDX:
				startHeadItem = CGridUtils::CreateGridItem(0, colIdx++, itemMask, itemFormat, record_col2idx[idx] + L">= mV");
				endHeadItem = CGridUtils::CreateGridItem(0, colIdx++, itemMask, itemFormat, record_col2idx[idx] + L"< mV");
				record_col2show[_T("ƽ����ѹ")] = TRUE;
				break;
			case POINT1_DIS_IDX:
				startHeadItem = CGridUtils::CreateGridItem(0, colIdx++, itemMask, itemFormat, record_col2idx[idx] + L">= ");
				endHeadItem = CGridUtils::CreateGridItem(0, colIdx++, itemMask, itemFormat, record_col2idx[idx] + L"< ");
				record_col2show[_T("��������1")] = TRUE;
				break;
			case POINT2_DIS_IDX:
				startHeadItem = CGridUtils::CreateGridItem(0, colIdx++, itemMask, itemFormat, record_col2idx[idx] + L">= ");
				endHeadItem = CGridUtils::CreateGridItem(0, colIdx++, itemMask, itemFormat, record_col2idx[idx] + L"< ");
				record_col2show[_T("��������2")] = TRUE;
				break;
			case POINT3_DIS_IDX:
				startHeadItem = CGridUtils::CreateGridItem(0, colIdx++, itemMask, itemFormat, record_col2idx[idx] + L">= ");
				endHeadItem = CGridUtils::CreateGridItem(0, colIdx++, itemMask, itemFormat, record_col2idx[idx] + L"< ");
				record_col2show[_T("��������3")] = TRUE;
				break;
			case POINT4_DIS_IDX:
				startHeadItem = CGridUtils::CreateGridItem(0, colIdx++, itemMask, itemFormat, record_col2idx[idx] + L">= ");
				endHeadItem = CGridUtils::CreateGridItem(0, colIdx++, itemMask, itemFormat, record_col2idx[idx] + L"< ");
				record_col2show[_T("��������4")] = TRUE;
				break;
			case POINT5_DIS_IDX:
				startHeadItem = CGridUtils::CreateGridItem(0, colIdx++, itemMask, itemFormat, record_col2idx[idx] + L">= ");
				endHeadItem = CGridUtils::CreateGridItem(0, colIdx++, itemMask, itemFormat, record_col2idx[idx] + L"< ");
				record_col2show[_T("��������5")] = TRUE;
				break;
			case END_DIS_IDX:
				startHeadItem = CGridUtils::CreateGridItem(0, colIdx++, itemMask, itemFormat, record_col2idx[idx] + L">= ");
				endHeadItem = CGridUtils::CreateGridItem(0, colIdx++, itemMask, itemFormat, record_col2idx[idx] + L"< ");
				record_col2show[_T("���յ�ѹ")] = TRUE;
				break;
			case RESIST_DIS_IDX:
				startHeadItem = CGridUtils::CreateGridItem(0, colIdx++, itemMask, itemFormat, record_col2idx[idx] + L">= ");
				endHeadItem = CGridUtils::CreateGridItem(0, colIdx++, itemMask, itemFormat, record_col2idx[idx] + L"< ");
				record_col2show[_T("����")] = TRUE;
				break;
			case SD_DIS_IDX:
				startHeadItem = CGridUtils::CreateGridItem(0, colIdx++, itemMask, itemFormat, record_col2idx[idx] + L">= ");
				endHeadItem = CGridUtils::CreateGridItem(0, colIdx++, itemMask, itemFormat, record_col2idx[idx] + L"< ");
				record_col2show[_T("SD")] = TRUE;
				break;
			case MID_DIS_IDX:
				startHeadItem = CGridUtils::CreateGridItem(0, colIdx++, itemMask, itemFormat, record_col2idx[idx] + L">= ");
				endHeadItem = CGridUtils::CreateGridItem(0, colIdx++, itemMask, itemFormat, record_col2idx[idx] + L"< ");
				record_col2show[_T("��ֵ��ѹ")] = TRUE;
				break;
			}
			condGrid.SetItem(&startHeadItem);
			condGrid.SetItem(&endHeadItem);
		}
	}

	CString seqCstr, gradeNameCstr;
	for (idx = 1; idx < condGrid.GetRowCount(); ++idx)
	{
		seqCstr.Format(_T("%d"), idx);
		GV_ITEM seqItem = CGridUtils::CreateGridItem(idx, 0, itemMask, itemFormat, seqCstr);
		GV_ITEM gradeNameItem = CGridUtils::CreateGridItem(idx, 1, itemMask, itemFormat, gradeDetailInfo.levelNames[idx-1]);
		condGrid.SetItem(&seqItem);
		condGrid.SetItem(&gradeNameItem);
		
		for (jdx = 0, colIdx = 2; jdx < gradeDetailInfo.para.GetLength(); ++jdx)
		{
			GV_ITEM startItem, endItem;
			int startVal, endVal;
			CString startCstr, endCstr;

			if (gradeDetailInfo.para[jdx] == '1')
			{
				startVal = gradeDetailInfo.startArrays[jdx];
				startVal = startVal + (idx - 1)*gradeDetailInfo.disArrays[jdx];
				endVal = startVal + gradeDetailInfo.disArrays[jdx];
				startCstr.Format(_T("%d"), startVal);
				endCstr.Format(_T("%d"), endVal);

				switch (jdx)
				{
				case CAP_DIS_IDX:
					startItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, startCstr);
					endItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, endCstr);
					break;
				case TIME_DIS_IDX:
					startItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, record_col2idx[idx]);
					endItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, endCstr);
					break;
				case OPEN_DIS_IDX:
					startItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, record_col2idx[idx]);
					endItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, endCstr);
					break;
				case AVG_DIS_IDX:
					startItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, record_col2idx[idx]);
					endItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, endCstr);
					break;
				case POINT1_DIS_IDX:
					startItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, record_col2idx[idx]);
					endItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, endCstr);
					break;
				case POINT2_DIS_IDX:
					startItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, record_col2idx[idx]);
					endItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, endCstr);
					break;
				case POINT3_DIS_IDX:
					startItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, record_col2idx[idx]);
					endItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, endCstr);
					break;
				case POINT4_DIS_IDX:
					startItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, record_col2idx[idx]);
					endItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, endCstr);
					break;
				case POINT5_DIS_IDX:
					startItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, record_col2idx[idx]);
					endItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, endCstr);
					break;
				case END_DIS_IDX:
					startItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, record_col2idx[idx]);
					endItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, endCstr);
					break;
				case RESIST_DIS_IDX:
					startItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, record_col2idx[idx]);
					endItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, endCstr);
					break;
				case SD_DIS_IDX:
					startItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, record_col2idx[idx]);
					endItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, endCstr);
					break;
				case MID_DIS_IDX:
					startItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, record_col2idx[idx]);
					endItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, endCstr);
					break;
				default:
					break;
				}
				condGrid.SetItem(&startItem);
				condGrid.SetItem(&endItem);
			}
		}
	}

}

//void CBCG_OptionDLG::reDrawGrid()
//{
//	//�ػ����
//	int grid_oldrowcount = condGrid.GetRowCount();
//	int grid_oldcolcount = condGrid.GetColumnCount();
//	int grid_newcolcount = 2;
//	//m_GridCtrl.DeleteAllItems();
//	condGrid.SetRowCount(level + 1);
//	condGrid.SetColumnCount(2);
//	condGrid.SetFixedRowCount(1);
//
//	for (map<CString, bool>::iterator it = record_col2show.begin(); it != record_col2show.end(); ++it)
//	{
//		if (true == it->second) grid_newcolcount += 2;
//	}
//	condGrid.SetColumnCount(grid_newcolcount);
//
//	int i_col = 2;
//	for (int i = 0; i < record_col2idx.size(); ++i)
//	{
//		if (false == record_col2show[record_col2idx[i]]) continue;
//		CString col_left;
//		CString col_right;
//		if (_T("����") == record_col2idx[i])
//		{
//			col_left = _T("���� >= mAh");
//			col_right = _T("���� < mAh");
//		}
//		if (_T("ʱ��") == record_col2idx[i])
//		{
//			col_left = _T("ʱ�� >= min");
//			col_right = _T("ʱ�� < mAh");
//		}
//		if (_T("��·��ѹ") == record_col2idx[i])
//		{
//			col_left = _T("��·��ѹ >= mV");
//			col_right = _T("��·��ѹ < mV");
//		}
//		if (_T("ƽ����ѹ") == record_col2idx[i])
//		{
//			col_left = _T("ƽ����ѹ >= mV");
//			col_right = _T("ƽ����ѹ < mV");
//		}
//		if (_T("��������1") == record_col2idx[i])
//		{
//			col_left = _T("��������1 >=");
//			col_right = _T("��������1 <");
//		}
//		if (_T("��������2") == record_col2idx[i])
//		{
//			col_left = _T("��������2 >=");
//			col_right = _T("��������2 <");
//		}
//		if (_T("��������3") == record_col2idx[i])
//		{
//			col_left = _T("��������3 >=");
//			col_right = _T("��������3 <");
//		}
//		if (_T("��������4") == record_col2idx[i])
//		{
//			col_left = _T("��������4 >=");
//			col_right = _T("��������4 <");
//		}
//		if (_T("��������5") == record_col2idx[i])
//		{
//			col_left = _T("��������5 >=");
//			col_right = _T("��������5 <");
//		}
//		if (_T("���յ�ѹ") == record_col2idx[i])
//		{
//			col_left = _T("���յ�ѹ >= mV");
//			col_right = _T("���յ�ѹ < mV");
//		}
//		if (_T("����") == record_col2idx[i])
//		{
//			col_left = _T("���� >=");
//			col_right = _T("���� <");
//		}
//		if (_T("SD") == record_col2idx[i])
//		{
//			col_left = _T("SD >= (percentage)");
//			col_right = _T("SD < (percentage)");
//		}
//		if (_T("��ֵ��ѹ") == record_col2idx[i])
//		{
//			col_left = _T("��ֵ��ѹ >= mV");
//			col_right = _T("��ֵ��ѹ < mV");
//		}
//
//		GV_ITEM Item;
//		Item.mask = GVIF_TEXT | GVIF_FORMAT;
//		Item.nFormat = DT_CENTER | DT_WORDBREAK;
//		Item.row = 0;
//		Item.col = i_col++;
//		condGrid.SetRowHeight(0, 25); //���ø��и�      
//		condGrid.SetColumnWidth(Item.col, 100); //���ø��п�
//		Item.strText = col_left;
//		condGrid.SetItem(&Item);
//
//		Item.mask = GVIF_TEXT | GVIF_FORMAT;
//		Item.nFormat = DT_CENTER | DT_WORDBREAK;
//		Item.row = 0;
//		Item.col = i_col++;
//		condGrid.SetRowHeight(0, 25); //���ø��и�      
//		condGrid.SetColumnWidth(Item.col, 100); //���ø��п�
//		Item.strText = col_right;
//		condGrid.SetItem(&Item);
//	}
//
//}
void CBCG_OptionDLG::reDrawGrid()
{
	//�ػ����
	int grid_oldrowcount = condGrid.GetRowCount();
	int grid_oldcolcount = condGrid.GetColumnCount();
	int grid_newcolcount = 2;
	//m_GridCtrl.DeleteAllItems();
	condGrid.SetRowCount(level + 1);
	condGrid.SetColumnCount(2);
	condGrid.SetFixedRowCount(1);

	for (map<CString, bool>::iterator it = record_col2show.begin(); it != record_col2show.end(); ++it)
	{
		if (true == it->second) grid_newcolcount += 2;
	}
	condGrid.SetColumnCount(grid_newcolcount);

	int i_col = 2;
	for (int i = 0; i < record_col2idx.size(); ++i)
	{
		if (false == record_col2show[record_col2idx[i]]) continue;
		CString col_left;
		CString col_right;
		if (_T("����") == record_col2idx[i])
		{
			col_left = _T("���� >= mAh");
			col_right = _T("���� < mAh");
		}
		if (_T("ʱ��") == record_col2idx[i])
		{
			col_left = _T("ʱ�� >= min");
			col_right = _T("ʱ�� < mAh");
		}
		if (_T("��·��ѹ") == record_col2idx[i])
		{
			col_left = _T("��·��ѹ >= mV");
			col_right = _T("��·��ѹ < mV");
		}
		if (_T("ƽ����ѹ") == record_col2idx[i])
		{
			col_left = _T("ƽ����ѹ >= mV");
			col_right = _T("ƽ����ѹ < mV");
		}
		if (_T("��������1") == record_col2idx[i])
		{
			col_left = _T("��������1 >=");
			col_right = _T("��������1 <");
		}
		if (_T("��������2") == record_col2idx[i])
		{
			col_left = _T("��������2 >=");
			col_right = _T("��������2 <");
		}
		if (_T("��������3") == record_col2idx[i])
		{
			col_left = _T("��������3 >=");
			col_right = _T("��������3 <");
		}
		if (_T("��������4") == record_col2idx[i])
		{
			col_left = _T("��������4 >=");
			col_right = _T("��������4 <");
		}
		if (_T("��������5") == record_col2idx[i])
		{
			col_left = _T("��������5 >=");
			col_right = _T("��������5 <");
		}
		if (_T("���յ�ѹ") == record_col2idx[i])
		{
			col_left = _T("���յ�ѹ >= mV");
			col_right = _T("���յ�ѹ < mV");
		}
		if (_T("����") == record_col2idx[i])
		{
			col_left = _T("���� >=");
			col_right = _T("���� <");
		}
		if (_T("SD") == record_col2idx[i])
		{
			col_left = _T("SD >= (percentage)");
			col_right = _T("SD < (percentage)");
		}
		if (_T("��ֵ��ѹ") == record_col2idx[i])
		{
			col_left = _T("��ֵ��ѹ >= mV");
			col_right = _T("��ֵ��ѹ < mV");
		}

		GV_ITEM Item;
		Item.mask = GVIF_TEXT | GVIF_FORMAT;
		Item.nFormat = DT_CENTER | DT_WORDBREAK;
		Item.row = 0;
		Item.col = i_col++;
		condGrid.SetRowHeight(0, 25); //���ø��и�      
		condGrid.SetColumnWidth(Item.col, 100); //���ø��п�
		Item.strText = col_left;
		condGrid.SetItem(&Item);

		Item.mask = GVIF_TEXT | GVIF_FORMAT;
		Item.nFormat = DT_CENTER | DT_WORDBREAK;
		Item.row = 0;
		Item.col = i_col++;
		condGrid.SetRowHeight(0, 25); //���ø��и�      
		condGrid.SetColumnWidth(Item.col, 100); //���ø��п�
		Item.strText = col_right;
		condGrid.SetItem(&Item);
	}

	int idx, jdx, colIdx;
	CString seqCstr;
	int itemMask = GVIF_TEXT | GVIF_FORMAT;
	int itemFormat = DT_CENTER | DT_WORDBREAK;
	CapGradeConf * capGradeConf = CapGradeConf::GetInstance();
	CGradeDetailInfo gradeDetailInfo = capGradeConf->gradeDetailInfos[capGradeConf->codeSel];

	for (idx = 1; idx < condGrid.GetRowCount(); ++idx)
	{
	
		seqCstr.Format(_T("%d"), idx);
		GV_ITEM seqItem = CGridUtils::CreateGridItem(idx, 0, itemMask, itemFormat, seqCstr);
		GV_ITEM gradeNameItem = CGridUtils::CreateGridItem(idx, 1, itemMask, itemFormat, gradeDetailInfo.levelNames[idx - 1]);
		condGrid.SetItem(&seqItem);
		condGrid.SetItem(&gradeNameItem);

		for (jdx = 0, colIdx = 2; jdx < record_col2idx.size(); ++jdx)
		{
			if (false == record_col2show[record_col2idx[jdx]]) continue;
			GV_ITEM startItem, endItem;
			int startVal, endVal;
			CString startCstr, endCstr;
			startVal = gradeDetailInfo.startArrays[jdx];
			startVal = startVal + (idx - 1)*gradeDetailInfo.disArrays[jdx];
			endVal = startVal + gradeDetailInfo.disArrays[jdx];
			startCstr.Format(_T("%d"), startVal);
			endCstr.Format(_T("%d"), endVal);

			switch (jdx)
			{
			case CAP_DIS_IDX:
				startItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, startCstr);
				endItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, endCstr);
				break;
			case TIME_DIS_IDX:
				startItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, startCstr);
				endItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, endCstr);
				break;
			case OPEN_DIS_IDX:
				startItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, startCstr);
				endItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, endCstr);
				break;
			case AVG_DIS_IDX:
				startItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, startCstr);
				endItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, endCstr);
				break;
			case POINT1_DIS_IDX:
				startItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, startCstr);
				endItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, endCstr);
				break;
			case POINT2_DIS_IDX:
				startItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, startCstr);
				endItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, endCstr);
				break;
			case POINT3_DIS_IDX:
				startItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, startCstr);
				endItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, endCstr);
				break;
			case POINT4_DIS_IDX:
				startItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, startCstr);
				endItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, endCstr);
				break;
			case POINT5_DIS_IDX:
				startItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, startCstr);
				endItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, endCstr);
				break;
			case END_DIS_IDX:
				startItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, startCstr);
				endItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, endCstr);
				break;
			case RESIST_DIS_IDX:
				startItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, startCstr);
				endItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, endCstr);
				break;
			case SD_DIS_IDX:
				startItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, startCstr);
				endItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, endCstr);
				break;
			case MID_DIS_IDX:
				startItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, startCstr);
				endItem = CGridUtils::CreateGridItem(idx, colIdx++, itemMask, itemFormat, endCstr);
				break;
			default:
				break;
			}
			condGrid.SetItem(&startItem);
			condGrid.SetItem(&endItem);
		}
	}
}


void CBCG_OptionDLG::InitDlgAssembly()
{
	CapGradeConf *capGradeConf = CapGradeConf::GetInstance();
	int idx;
	
	for (idx = codeComb.GetCount()-1; idx >= 0; --idx)
	{
		codeComb.DeleteString(idx);
	}

	for (idx = 0; idx < capGradeConf->codeSelCount; ++idx)
	{
		codeComb.AddString(capGradeConf->codeNames[idx]);
	}
	codeComb.SetCurSel(capGradeConf->codeSel);

	levelComb.SetCurSel(capGradeConf->gradeDetailInfos[capGradeConf->codeSel].levelCount - 1);
	// ��ʼ��ȫ�ֱ���level
	level = levelComb.GetCurSel() + 1;
	
	CGradeDetailInfo gradeDetailInfo = capGradeConf->gradeDetailInfos[capGradeConf->codeSel];
	CString para = gradeDetailInfo.para;

	for (idx = 0; idx < para.GetLength(); ++idx)
	{
		if (para[idx] == '0')
		{
			disChecks[idx]->SetCheck(FALSE);
		}
		else
		{
			disChecks[idx]->SetCheck(TRUE);
		}
	}
}

void CBCG_OptionDLG::InitChecks()
{
	cabChecks.push_back(&cab1Check);
	cabChecks.push_back(&cab2Check);
	cabChecks.push_back(&cab3Check);
	cabChecks.push_back(&cab4Check);
	cabChecks.push_back(&cab5Check);
	cabChecks.push_back(&cab6Check);
	cabChecks.push_back(&cab7Check);
	cabChecks.push_back(&cab8Check);
	cabChecks.push_back(&cab9Check);
	cabChecks.push_back(&cab10Check);
	cabChecks.push_back(&cab11Check);
	cabChecks.push_back(&cab12Check);
	cabChecks.push_back(&cab13Check);
	cabChecks.push_back(&cab14Check);
	cabChecks.push_back(&cab15Check);
	cabChecks.push_back(&cab16Check);
	cabChecks.push_back(&cab17Check);
	cabChecks.push_back(&cab18Check);
	cabChecks.push_back(&cab19Check);
	cabChecks.push_back(&cab20Check);


	// ��ʼ��DisChecks
	disChecks.push_back(&capCheck);
	disChecks.push_back(&timeCheck);
	disChecks.push_back(&openCheck);
	disChecks.push_back(&avgCheck);
	disChecks.push_back(&point1Check);
	disChecks.push_back(&point2Check);
	disChecks.push_back(&point3Check);
	disChecks.push_back(&point4Check);
	disChecks.push_back(&point5Check);
	disChecks.push_back(&endCheck);
	disChecks.push_back(&resistCheck);
	disChecks.push_back(&sdCheck);
	disChecks.push_back(&midCheck);
}

// CBCG_OptionDLG ��Ϣ�������

void CBCG_OptionDLG::OnCbnSelchangeBcgOdlgCombo2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString tmp;
	int idx = levelComb.GetCurSel();
	if (idx < 0) return;
	level = idx + 1;

	reDrawGrid();
}


void CBCG_OptionDLG::OnBnClickedCapCheck()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int ChkBox = capCheck.GetCheck();
	if (ChkBox == BST_UNCHECKED)
	{
		record_col2show[_T("����")] = false;
	}
	else if (ChkBox == BST_CHECKED)
	{
		record_col2show[_T("����")] = true;
	}
	//�ػ����
	reDrawGrid();
}


void CBCG_OptionDLG::OnBnClickedTimeCheck()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int ChkBox = timeCheck.GetCheck();
	if (ChkBox == BST_UNCHECKED)
	{
		record_col2show[_T("ʱ��")] = false;
	}
	else if (ChkBox == BST_CHECKED)
	{
		record_col2show[_T("ʱ��")] = true;
	}
	//�ػ����
	reDrawGrid();
}


void CBCG_OptionDLG::OnBnClickedOpenCheck()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int ChkBox = openCheck.GetCheck();
	if (ChkBox == BST_UNCHECKED)
	{
		record_col2show[_T("��·��ѹ")] = false;
	}
	else if (ChkBox == BST_CHECKED)
	{
		record_col2show[_T("��·��ѹ")] = true;
	}
	//�ػ����
	reDrawGrid();
}


void CBCG_OptionDLG::OnBnClickedAvgCheck()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int ChkBox = avgCheck.GetCheck();
	if (ChkBox == BST_UNCHECKED)
	{
		record_col2show[_T("ƽ����ѹ")] = false;
	}
	else if (ChkBox == BST_CHECKED)
	{
		record_col2show[_T("ƽ����ѹ")] = true;
	}
	//�ػ����
	reDrawGrid();
}


//void CBCG_OptionDLG::OnBnClickedBcgOdlgCheck25()
//{

//}
//
//
//void CBCG_OptionDLG::OnBnClickedBcgOdlgCheck26()
//{

//}


void CBCG_OptionDLG::OnBnClickedPointCheck3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int ChkBox = point3Check.GetCheck();
	if (ChkBox == BST_UNCHECKED)
	{
		record_col2show[_T("��������3")] = false;
	}
	else if (ChkBox == BST_CHECKED)
	{
		record_col2show[_T("��������3")] = true;
	}
	//�ػ����
	reDrawGrid();
}


void CBCG_OptionDLG::OnBnClickedPointCheck4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int ChkBox = point4Check.GetCheck();
	if (ChkBox == BST_UNCHECKED)
	{
		record_col2show[_T("��������4")] = false;
	}
	else if (ChkBox == BST_CHECKED)
	{
		record_col2show[_T("��������4")] = true;
	}
	//�ػ����
	reDrawGrid();
}


void CBCG_OptionDLG::OnBnClickedPointCheck5()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int ChkBox = point5Check.GetCheck();
	if (ChkBox == BST_UNCHECKED)
	{
		record_col2show[_T("��������5")] = false;
	}
	else if (ChkBox == BST_CHECKED)
	{
		record_col2show[_T("��������5")] = true;
	}
	//�ػ����
	reDrawGrid();
}


void CBCG_OptionDLG::OnBnClickedEndCheck()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int ChkBox = endCheck.GetCheck();
	if (ChkBox == BST_UNCHECKED)
	{
		record_col2show[_T("���յ�ѹ")] = false;
	}
	else if (ChkBox == BST_CHECKED)
	{
		record_col2show[_T("���յ�ѹ")] = true;
	}
	//�ػ����
	reDrawGrid();
}


void CBCG_OptionDLG::OnBnClickedInnerCheck()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int ChkBox = resistCheck.GetCheck();
	if (ChkBox == BST_UNCHECKED)
	{
		record_col2show[_T("����")] = false;
	}
	else if (ChkBox == BST_CHECKED)
	{
		record_col2show[_T("����")] = true;
	}
	//�ػ����
	reDrawGrid();
}


void CBCG_OptionDLG::OnBnClickedSdCheck()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int ChkBox = sdCheck.GetCheck();
	if (ChkBox == BST_UNCHECKED)
	{
		record_col2show[_T("SD")] = false;
	}
	else if (ChkBox == BST_CHECKED)
	{
		record_col2show[_T("SD")] = true;
	}
	//�ػ����
	reDrawGrid();
}


void CBCG_OptionDLG::OnBnClickedMidCheck()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int ChkBox = midCheck.GetCheck();
	if (ChkBox == BST_UNCHECKED)
	{
		record_col2show[_T("��ֵ��ѹ")] = false;
	}
	else if (ChkBox == BST_CHECKED)
	{
		record_col2show[_T("��ֵ��ѹ")] = true;
	}
	//�ػ����
	reDrawGrid();
}


void CBCG_OptionDLG::OnBnClickedOk()
{
	
	CString flag = L"1";
	::SendNotifyMessage(theApp.capacityGradingDlg->m_hWnd, WM_CAL_GRADE_MSG, WPARAM(flag.AllocSysString()), NULL);
	CDialog::OnOK();
}


void CBCG_OptionDLG::OnBnClickedBcgBrowseBtn()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CBCG_OptionDLG::OnBnClickedBcgSaveBtn()
{
	// �����������  �������
	CString curCodeName;
	codeComb.GetWindowTextW(curCodeName);

	CapGradeConf *capGradeConf = CapGradeConf::GetInstance();

	CString str;
	int codeSel = codeComb.GetCurSel();
	int preCodeSel = codeSel;
	BOOL addFlag = FALSE;
	if (codeSel < 0)
	{
		codeSel = codeComb.GetCount();
		addFlag = TRUE;
		codeComb.GetWindowTextW(str);
		codeComb.AddString(str);
		capGradeConf->codeNames.push_back(str);
	}
	

	//codeComb.GetWindowTextW(str);
	//codeComb.AddString(str);

	//int helpSel = codeSel < capGradeConf->codeSelCount ? codeSel : capGradeConf->codeSelCount - 1;

	CGradeDetailInfo gradeDetailInfo;
	CGradeDetailInfo helpDetailInfo;
	helpDetailInfo = codeSel >= capGradeConf->codeSelCount
		? capGradeConf->gradeDetailInfos[codeSel - 1] : helpDetailInfo;

	codeComb.GetWindowTextW(gradeDetailInfo.codeName);
	memcpy(&(gradeDetailInfo.disArrays), &(helpDetailInfo.disArrays), sizeof(int)* MAX_DIS_NUM);
	gradeDetailInfo.disArraysStr = helpDetailInfo.disArraysStr;

	gradeDetailInfo.levelCount = condGrid.GetRowCount() - 1;
	int idx, jdx;

	for (idx = 0; idx < disChecks.size(); ++idx)
	{
		if (disChecks[idx]->GetCheck() == BST_CHECKED)
			gradeDetailInfo.para.SetAt(idx, '1');
		else
			gradeDetailInfo.para.SetAt(idx, '0');
	}
	CString levelNameStr, startStr;
	for (idx = 1; idx < condGrid.GetRowCount(); ++idx)
	{
		str = condGrid.GetItemText(idx, 1);
		gradeDetailInfo.levelNames[idx - 1] = str;
	}

	memcpy(&(gradeDetailInfo.startArrays), &(helpDetailInfo.startArrays), sizeof(int)*MAX_DIS_NUM);
	gradeDetailInfo.startArraysStr = helpDetailInfo.startArraysStr;

	str = L"";

	for (idx = 0, jdx = 2; idx < MAX_DIS_NUM; ++idx)
	{
		str += disChecks[idx] == FALSE ? L"0" : L"1";
		if (disChecks[idx])
		{
			gradeDetailInfo.startArraysStr[idx] = condGrid.GetItemText(1, jdx);
			gradeDetailInfo.startArrays[idx] = _ttoi(gradeDetailInfo.startArraysStr[idx]);

			gradeDetailInfo.disArraysStr[idx] = condGrid.GetItemText(1, jdx + 1);
			gradeDetailInfo.disArrays[idx] = _ttoi(gradeDetailInfo.disArraysStr[idx]);
			gradeDetailInfo.disArrays[idx] -= gradeDetailInfo.startArrays[idx];

			gradeDetailInfo.disArraysStr[idx].Format(_T("%d"), gradeDetailInfo.disArrays[idx]);
			jdx += 2;
		}
	}

	capGradeConf->codeSel = codeSel;
	capGradeConf->codeSelCount = preCodeSel < 0 ? capGradeConf->codeSelCount+1: capGradeConf->codeSelCount;
	if (addFlag) 
	{
		capGradeConf->gradeDetailInfos.push_back(gradeDetailInfo);
		
	}
	else
	{
		capGradeConf->gradeDetailInfos[codeSel] = gradeDetailInfo;
	}
	capGradeConf->SaveToFile();
}


void CBCG_OptionDLG::OnBnClickedBcgDelBtn()
{
	int idx = codeComb.GetCurSel();
	codeComb.DeleteString(idx);

	CapGradeConf * capGradeConf = CapGradeConf::GetInstance();

	capGradeConf->codeSel--;
	capGradeConf->codeSelCount--;

	for (idx = capGradeConf->codeSel + 1; idx < capGradeConf->codeNames.size()-1; ++idx)
	{
		capGradeConf->codeNames[idx] = capGradeConf->codeNames[idx+1];
	}

	for (idx = capGradeConf->codeSel + 1; idx < capGradeConf->codeNames.size() - 1; ++idx)
	{
		capGradeConf->gradeDetailInfos[idx] = capGradeConf->gradeDetailInfos[idx + 1];
	}

	capGradeConf->SaveToFile();
}




void CBCG_OptionDLG::OnBnClickedBcgPointCheck1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int ChkBox = point1Check.GetCheck();
	if (ChkBox == BST_UNCHECKED)
	{
		record_col2show[_T("��������1")] = false;
	}
	else if (ChkBox == BST_CHECKED)
	{
		record_col2show[_T("��������1")] = true;
	}
	//�ػ����
	reDrawGrid();
}


void CBCG_OptionDLG::OnBnClickedBcgPointCheck2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int ChkBox = point2Check.GetCheck();
	if (ChkBox == BST_UNCHECKED)
	{
		record_col2show[_T("��������2")] = false;
	}
	else if (ChkBox == BST_CHECKED)
	{
		record_col2show[_T("��������2")] = true;
	}
	//�ػ����
	reDrawGrid();
}


void CBCG_OptionDLG::OnCbnSelchangeBcgCodeCombo()
{
	int codeSel = codeComb.GetCurSel();
	CapGradeConf *capGradeConf = CapGradeConf::GetInstance();

	capGradeConf->SetCodeSel(codeSel);

	InitCondGrid();
	InitDlgAssembly();
}


BOOL CBCG_OptionDLG::DestroyWindow()
{
	// TODO:  �ڴ����ר�ô����/����û���
	theApp.capacityGradingDlg->OptionDlg = NULL;
	return CDialog::DestroyWindow();
}

void CBCG_OptionDLG::OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	int colCount = this->condGrid.GetColumnCount();
	if (colCount <= 2) return;

	// �����grid ��һ�еĿɱ༭����ʱ������صĲ�ֵ�ͳ�ʼֵ������
	int rowCount = this->condGrid.GetRowCount();
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*)pNotifyStruct;

	int rowIdx = pItem->iRow;
	int colIdx = pItem->iColumn;
	int idx;
	CString startStr, endStr;
	int startVal, endVal, disVal;

	int startColIdx, endColIdx;

	// ����startColIdx��endColIdx;
	if (colIdx % 2 == 0)
	{
		startColIdx = colIdx;
		endColIdx = colIdx + 1;
	}
	else
	{
		startColIdx = colIdx - 1;
		endColIdx = colIdx;
	}

	// �Ȳ������޸�startVal��endVal
	startStr = condGrid.GetItemText(rowIdx, startColIdx);
	endStr = condGrid.GetItemText(rowIdx, endColIdx);
	startVal = _ttoi(startStr);
	endVal = _ttoi(endStr);
	disVal = endVal - startVal;

	startStr = condGrid.GetItemText(1, startColIdx);
	startVal = _ttoi(startStr);
	for (idx = 1; idx < rowCount; ++idx)
	{			
			
		endVal = startVal + disVal;
		endStr.Format(_T("%d"), endVal);
		condGrid.SetItemText(idx, startColIdx, startStr);
		condGrid.SetItemText(idx, endColIdx, endStr);
		startVal = endVal;
		startStr.Format(_T("%d"), startVal);
	}
	
	condGrid.Invalidate();
}
