// EbatterysDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "EbatterysDlg.h"
#include "afxdialogex.h"

// CEbatterysDlg �Ի���

IMPLEMENT_DYNAMIC(CEbatterysDlg, CDialog)

CEbatterysDlg::CEbatterysDlg(CWnd* pParent /*=NULL*/)
: CDialog(CEbatterysDlg::IDD, pParent)
{
	ColNum = 7;
}

CEbatterysDlg::~CEbatterysDlg()
{
}

void CEbatterysDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXCEP_LIST, excepList);
}


BEGIN_MESSAGE_MAP(CEbatterysDlg, CDialog)
	ON_WM_RBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CEbatterysDlg ��Ϣ�������


void CEbatterysDlg::OnRButtonDown(UINT nFlags, CPoint point)
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


void CEbatterysDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (this->m_hWnd) {
		CRect rect(0, 0, cx, cy);
		this->MoveWindow(rect.left + MARGIN_LEFT_BATPANE, rect.top + MARGIN_TOP_BATPANE, rect.Width(), rect.Height(), TRUE);
		
		if (excepList.m_hWnd)
		{
			excepList.MoveWindow(&rect, true);

			colWidth = rect.Width() / ColNum;

			excepList.SetColumnWidth(0, (rect.Width() - (ColNum - 1) * colWidth));
			for (int idx = 1; idx < ColNum; ++idx)
			{
				excepList.SetColumnWidth(idx, colWidth);
			}

		}
	}
}


BOOL CEbatterysDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rect;
	GetWindowRect(&rect);  //��ȡ����rect��

	//excepList.GetClientRect(&rect);
	excepList.MoveWindow(&rect, true);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	excepList.SetExtendedStyle(excepList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	colWidth = rect.Width() / ColNum;

	excepList.InsertColumn(0, L"���", LVCFMT_LEFT, rect.Width() - (ColNum - 1)*colWidth);
	excepList.InsertColumn(1, L"���", LVCFMT_LEFT, colWidth);
	excepList.InsertColumn(2, L"��ع�λ", LVCFMT_LEFT, colWidth);
	excepList.InsertColumn(3, L"��Ʒ����", LVCFMT_LEFT, colWidth);
	excepList.InsertColumn(4, L"��о���", LVCFMT_LEFT, colWidth);
	excepList.InsertColumn(5, L"����״̬", LVCFMT_LEFT, colWidth);
	excepList.InsertColumn(6, L"�쳣���", LVCFMT_LEFT, colWidth);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CEbatterysDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}
