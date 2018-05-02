// CbatterysDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "CbatterysDlg.h"
#include "afxdialogex.h"


// CbatterysDlg �Ի���

IMPLEMENT_DYNAMIC(CbatterysDlg, CDialog)

CbatterysDlg::CbatterysDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CbatterysDlg::IDD, pParent)
{
	ColNum = 6;
	subGroupBatNum = 8;
	cabBattery = NULL;
}

CbatterysDlg::~CbatterysDlg()
{
}

void CbatterysDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMP_LIST, compList);
}


BEGIN_MESSAGE_MAP(CbatterysDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CbatterysDlg ��Ϣ�������


void CbatterysDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	if (this->m_hWnd) {
		CRect rect(0, 0, cx, cy);
		this->MoveWindow(rect.left + MARGIN_LEFT_BATPANE, rect.top + MARGIN_TOP_BATPANE, rect.Width(), rect.Height(), TRUE);
		//CRect  rect;
		//GetWindowRect(&rect);  //��ȡ����rect��
		//ScreenToClient(rect);  //�Ӵ��ڳߴ�ת�����û���rect
		if (compList.m_hWnd)
		{
			compList.MoveWindow(&rect, true);

			colWidth = rect.Width() / ColNum;

			compList.SetColumnWidth(0, (rect.Width() - (ColNum - 1) * colWidth));
			for (int idx = 1; idx < ColNum; ++idx)
			{
				compList.SetColumnWidth(idx, colWidth);
			}

		}

	}
}


BOOL CbatterysDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//(1) ��ȡ����

	cabInfo = cabInfos[curCabId - 1];
	groupPerCol = cabInfo.groupNumPerCol;	//	ÿ������
	colShowNum = cabInfo.colShowNum;		//	��ʾ����	
	numPerGroup = cabInfo.numPerGroup;		//	ÿ�����

	batCount = groupPerCol * colShowNum * numPerGroup;

	//(lowerCabs.cabBatterys[curCabId - 1])->batterys[batSeqId].GetSpecStateStr(STATE_SEL_CODE);

	//(2) �ƶ�λ��,����ListCtrl

	GetWindowRect(&rect);  //��ȡ����rect��

	//compList.GetClientRect(&rect);
	compList.MoveWindow(&rect, true);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	compList.SetExtendedStyle(compList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	colWidth = rect.Width() / ColNum;

	compList.InsertColumn(0, L"��ع�λ", LVCFMT_LEFT, rect.Width() - (ColNum - 1)*colWidth);
	compList.InsertColumn(1, L"��о���", LVCFMT_LEFT, colWidth);
	compList.InsertColumn(2, L"��ѹ(mV)", LVCFMT_LEFT, colWidth);
	compList.InsertColumn(3, L"����(mA)", LVCFMT_LEFT, colWidth);
	compList.InsertColumn(4, L"ʱ��(Min)", LVCFMT_LEFT, colWidth);
	compList.InsertColumn(5, L"����(mAh)", LVCFMT_LEFT, colWidth);

	FillTable();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CbatterysDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()

	//CDC memDC;			//	����һ����ʾ�豸����
	//CBitmap memBitMap;	//	����һ��λͼ����
	//// ��������Ļ��ʾ���ݵ��ڴ���ʾ�豸
	//memDC.CreateCompatibleDC(NULL);
	//// ����һ������Ļ��ʾ���ݵ�λͼ,λͼ�Ĵ�С�봰�ڴ�С��һ��
	//this->GetClientRect(&rect);
	//memBitMap.CreateCompatibleBitmap(this->GetDC(), rect.Width(), rect.Height());

	//// ��λͼѡ�뵽�ڴ���ʾ�豸��
	//CBitmap *oldBit = memDC.SelectObject(&memBitMap);

	////(3) �����ɵ�������䵽ListCtrl��
	//FillCompTable();
	//CDialog::OnPaint();

	//this->GetDC()->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
	//memBitMap.DeleteObject();
	//memDC.DeleteDC();
}

void CbatterysDlg::FillTable()
{
	cabBattery = lowerCabs.cabBatterys[curCabId - 1];

	for (int rowIdx = 0; rowIdx < batCount; ++rowIdx)
	{
		groupId = rowIdx / numPerGroup + 1;
		subGroupId = (rowIdx % numPerGroup) / subGroupBatNum + 1;
		subGroupBatId = (rowIdx % numPerGroup) % subGroupBatNum + 1;

		groupIdStr.Format(_T("%d"), groupId);
		subGroupIdStr.Format(_T("%d"), subGroupId);
		subGroupBatIdStr.Format(_T("%d"), subGroupBatId);

		str = L"��" + groupIdStr + L"-" + subGroupIdStr + L"-" + subGroupBatIdStr + L"��";

		compList.InsertItem(rowIdx, str);

		int valideDataNum = cabBattery == NULL ? 0 : cabBattery->batterys.size();


		int seqId = rowIdx + 1;
		if (seqId <= valideDataNum)
		{
			str.Format(_T("%d"), cabBattery->batterys[seqId - 1].voltVal);
			compList.SetItemText(rowIdx, 2, str == INVALIDE_STATE_CSTR ? INVALIDE_STATE_CSTR2 : str);
			str.Format(_T("%d"), cabBattery->batterys[seqId - 1].currentVal);
			compList.SetItemText(rowIdx, 3, str == INVALIDE_STATE_CSTR ? INVALIDE_STATE_CSTR2 : str);
			str.Format(_T("%d"), cabBattery->batterys[seqId - 1].timeVal);
			compList.SetItemText(rowIdx, 4, str == INVALIDE_STATE_CSTR ? INVALIDE_STATE_CSTR2 : str);
			str.Format(_T("%d"), cabBattery->batterys[seqId - 1].capacityVal);
			compList.SetItemText(rowIdx, 5, str == INVALIDE_STATE_CSTR ? INVALIDE_STATE_CSTR2 : str);

		}
		else
		{
			str = L"";
			compList.SetItemText(rowIdx, 2, str == INVALIDE_STATE_CSTR ? INVALIDE_STATE_CSTR2 : str);
			compList.SetItemText(rowIdx, 3, str == INVALIDE_STATE_CSTR ? INVALIDE_STATE_CSTR2 : str);
			compList.SetItemText(rowIdx, 4, str == INVALIDE_STATE_CSTR ? INVALIDE_STATE_CSTR2 : str);
			compList.SetItemText(rowIdx, 5, str == INVALIDE_STATE_CSTR ? INVALIDE_STATE_CSTR2 : str);
		}
		str.Format(_T("%d"), rowIdx + 1);
		compList.SetItemText(rowIdx, 1, str == INVALIDE_STATE_CSTR ? INVALIDE_STATE_CSTR2 : str);
	}
}
