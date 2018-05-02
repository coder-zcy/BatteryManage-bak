
// GridControl0010Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GridControl0010.h"
#include "GridControl0010Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGridControl0010Dlg �Ի���



CGridControl0010Dlg::CGridControl0010Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGridControl0010Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGridControl0010Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);


	DDX_Control(pDX, IDC_CUSTOM2, m_pGrid);
}

BEGIN_MESSAGE_MAP(CGridControl0010Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CGridControl0010Dlg ��Ϣ�������

BOOL CGridControl0010Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	GridCtrlInit();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CGridControl0010Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGridControl0010Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CGridControl0010Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGridControl0010Dlg::GridCtrlInit()
{
	m_pGrid.SetEditable(false);
	m_pGrid.SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));//��ɫ����
	m_pGrid.SetRowCount(8); //��ʼΪ10��
	m_pGrid.SetColumnCount(8); //��ʼ��Ϊ11��
	m_pGrid.SetFixedRowCount(1); //��ͷΪһ��
	m_pGrid.SetFixedColumnCount(1); //��ͷΪһ��
	
	for (int row = 0; row < m_pGrid.GetRowCount(); row++)
	for (int col = 0; col < m_pGrid.GetColumnCount(); col++)
	{
		//���ñ����ʾ����
		GV_ITEM Item;
		Item.mask = GVIF_TEXT | GVIF_FORMAT;
		Item.row = row;
		Item.col = col;
		m_pGrid.SetRowHeight(row, 25); //���ø��и�          
		m_pGrid.SetColumnWidth(0, 64); //����0�п� 
		m_pGrid.SetColumnWidth(col, 64); //���ø��п�
		if (row == 0 && col == 0) //��(0��0)��
		{
			Item.nFormat = DT_CENTER | DT_WORDBREAK;
			Item.strText.Format(_T("������ʾ"), col);
		}
		else if (row < 1) //����0�б�ͷ��ʾ
		{
			Item.nFormat = DT_CENTER | DT_WORDBREAK;
			Item.strText.Format(_T(" ��Ŀ%d"), col);
		}
		else if (col < 1) //����0�б�ͷ��ʾ
		{
			if (row < m_pGrid.GetRowCount())
			{
				Item.nFormat = DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;
				Item.strText.Format(_T("��%d��"), row);
			}
		}
		else
		{
			Item.nFormat = DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;
			Item.strText.Format(_T(""), 2);
		}
		m_pGrid.SetItem(&Item);
	}

}

