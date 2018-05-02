// TbatterysDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "TbatterysDlg.h"
#include "afxdialogex.h"


// CTbatterysDlg �Ի���

IMPLEMENT_DYNAMIC(CTbatterysDlg, CDialog)

CTbatterysDlg::CTbatterysDlg(CWnd* pParent /*=NULL*/)
: CDialog(CTbatterysDlg::IDD, pParent)
{
	subGroupBatNum = 8;		// ÿ���ж��ٿ��ع���
}

CTbatterysDlg::~CTbatterysDlg()
{

}

void CTbatterysDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TABLE_LIST, tableList);
}


BEGIN_MESSAGE_MAP(CTbatterysDlg, CDialog)
	ON_WM_RBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CTbatterysDlg ��Ϣ�������


void CTbatterysDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CMenu   controlMenu;   //��������Ҫ�õ���cmenu����
	controlMenu.LoadMenu(IDR_CONTROL_MENU); //װ���Զ�����Ҽ��˵� 
	CMenu   *controlContextMenu = controlMenu.GetSubMenu(0); //��ȡ��һ�������˵������Ե�һ���˵��������Ӳ˵� 
	CRect rect;
	this->GetClientRect(&rect);
	ClientToScreen(&rect);

	POINT point1;
	::GetCursorPos(&point1);

	if (point1.x >= rect.left && point1.x <= rect.right
		&& point1.y >= rect.top && point1.y <= rect.bottom)
	{
		controlContextMenu->TrackPopupMenu(TPM_LEFTALIGN, point1.x, point1.y, AfxGetMainWnd()); //��ָ��λ����ʾ�����˵�
	}
	CDialog::OnRButtonDown(nFlags, point);
}


void CTbatterysDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	if (this->m_hWnd) {
		CRect rect(0, 0, cx, cy);
		this->MoveWindow(rect.left + MARGIN_LEFT_BATPANE, rect.top + MARGIN_TOP_BATPANE, rect.Width(), rect.Height(), TRUE);
		//CRect  rect;
		//GetWindowRect(&rect);  //��ȡ����rect��
		//ScreenToClient(rect);  //�Ӵ��ڳߴ�ת�����û���rect
		if (tableList.m_hWnd)
		{
			tableList.MoveWindow(&rect, true);
			
			colWidth = rect.Width() / ColNum;

			tableList.SetColumnWidth(0, (rect.Width() - (ColNum - 1) * colWidth));
			for (int idx = 1; idx < ColNum; ++idx)
			{
				tableList.SetColumnWidth(idx, colWidth);
			}

		}
		
	}
}


BOOL CTbatterysDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//(1) ��ȡ����
	
	//DrawTable();
	cabInfo = cabInfos[curCabId - 1];
	groupPerCol = cabInfo.groupNumPerCol;	//	ÿ������
	colShowNum = cabInfo.colShowNum;		//	��ʾ����	
	numPerGroup = cabInfo.numPerGroup;		//	ÿ�����


	ColNum = groupPerCol * colShowNum + 1;

	//(lowerCabs.cabBatterys[curCabId - 1])->batterys[batSeqId].GetSpecStateStr(STATE_SEL_CODE);

	//(2) �ƶ�λ��,����ListCtrl

	GetWindowRect(&rect);  //��ȡ����rect��

	//tableList.GetClientRect(&rect);
	tableList.MoveWindow(&rect, true);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	tableList.SetExtendedStyle(tableList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	colWidth = rect.Width() / ColNum;

	tableList.InsertColumn(0, L"(mv)", LVCFMT_LEFT, rect.Width() - (ColNum - 1)*colWidth);
	for (int idx = 1; idx < ColNum; ++idx)
	{
		str.Format(_T("%d"), idx);
		tableList.InsertColumn(idx, L"��" + str, LVCFMT_LEFT, colWidth);
	}

	FillTable();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CTbatterysDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}

void CTbatterysDlg::FillTable()
{
	{
		//(3) �����ɵ�������䵽ListCtrl��
		cabBattery = lowerCabs.cabBatterys[curCabId - 1];
		for (int rowIdx = 0; rowIdx < numPerGroup; ++rowIdx)
		{
			subGroupId = rowIdx / subGroupBatNum + 1;
			subGroupBatId = rowIdx % subGroupBatNum + 1;

			subGroupIdStr.Format(_T("%d"), subGroupId);
			subGroupBatIdStr.Format(_T("%d"), subGroupBatId);

			str = L"��" + subGroupIdStr + L"-" + subGroupBatIdStr + L"��";

			tableList.InsertItem(rowIdx, str);

			int valideDataNum = cabBattery == NULL ? 0 : cabBattery->batterys.size();

			if (valideDataNum > 0)
			{
				for (int colIdx = 1; colIdx < ColNum; ++colIdx)
				{
					int seqId = (colIdx - 1) * numPerGroup + rowIdx + 1;
					if (seqId <= valideDataNum)
					{
						tableList.SetItemText(rowIdx, colIdx, cabBattery->batterys[seqId - 1].GetSpecStateStr(STATE_SEL_CODE));
					}
					else
					{
						tableList.SetItemText(rowIdx, colIdx, L"");
					}
				}
			}

		}
	}
}
