// InitDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "InitDlg.h"
#include "afxdialogex.h"


// CInitDlg �Ի���

IMPLEMENT_DYNAMIC(CInitDlg, CDialog)

CInitDlg::CInitDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInitDlg::IDD, pParent)
{

}

CInitDlg::~CInitDlg()
{
}

void CInitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INIT_TAB, initTab);
}


BEGIN_MESSAGE_MAP(CInitDlg, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_INIT_TAB, &CInitDlg::OnTcnSelchangeInittab)
	ON_BN_CLICKED(IDC_SAVE_SET, &CInitDlg::OnBnClickedSaveSet)
END_MESSAGE_MAP()


// CInitDlg ��Ϣ�������
BOOL CInitDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//	ASSERT((IDD_ABOUTBOX & 0xFFF0) == IDD_ABOUTBOX);
	//	ASSERT(IDD_ABOUTBOX < 0xF000);

	CMenu* psysMenu = GetSystemMenu(FALSE);
	if (psysMenu != NULL)
	{
		BOOL nameValid;
		CString strAboutMenu;
		nameValid = strAboutMenu.LoadString(IDD_ABOUTBOX);
		ASSERT(nameValid);
		if (!strAboutMenu.IsEmpty())
		{
			psysMenu->AppendMenu(MF_SEPARATOR);
			psysMenu->AppendMenu(MF_STRING, IDD_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically   
	//  when the application's main window is not a dialog   
	//SetIcon(m_hIcon, TRUE);         // Set big icon   
	//SetIcon(m_hIcon, FALSE);        // Set small icon   

	// TODO: Add extra initialization here   
	CRect tabRect;   // ��ǩ�ؼ��ͻ�����λ�úʹ�С   

	initTab.InsertItem(0, _T("���Ų���"));         // �����ǩ  
	initTab.InsertItem(1, _T("ͨѶ����"));
	initTab.InsertItem(2, _T("��������"));
	initTab.InsertItem(3, _T("�û�����"));
	initTab.InsertItem(4, _T("��ɫ����"));

	screenDlg.Create(IDD_SCREEN_DLG, &initTab);    // ������һ����ǩҳ   
	commDlg.Create(IDD_COMM_DLG, &initTab);
	otherDlg.Create(IDD_OTHER_DLG, &initTab);    // ������һ����ǩҳ   
	colorDlg.Create(IDD_COLOR_DLG, &initTab);    // ������һ����ǩҳ   
	userDlg.Create(IDD_USER_DLG, &initTab);    // ������һ����ǩҳ   

	initTab.GetClientRect(&tabRect);    // ��ȡ��ǩ�ؼ��ͻ���Rect   
	// ����tabRect��ʹ�串�Ƿ�Χ�ʺϷ��ñ�ǩҳ   
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;
	// ���ݵ����õ�tabRect����m_jzmDlg�ӶԻ��򣬲�����Ϊ��ʾ   
	screenDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
	// ���ݵ����õ�tabRect����m_androidDlg�ӶԻ��򣬲�����Ϊ����   
	commDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

	otherDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

	userDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

	colorDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

	return TRUE;  // return TRUE  unless you set the focus to a control   

}


void CInitDlg::OnTcnSelchangeInittab(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	CRect tabRect;    // ��ǩ�ؼ��ͻ�����Rect   

	// ��ȡ��ǩ�ؼ��ͻ���Rect����������������ʺϷ��ñ�ǩҳ   
	initTab.GetClientRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;

	switch (initTab.GetCurSel())
	{
		// �����ǩ�ؼ���ǰѡ���ǩΪ�������ס�������ʾm_jzmDlg�Ի�������m_androidDlg�Ի���   
	case 0:
		screenDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		commDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		otherDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		userDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		colorDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
		// �����ǩ�ؼ���ǰѡ���ǩΪ��Android����������������m_jzmDlg�Ի�����ʾm_androidDlg�Ի���   
	case 1:
		screenDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		commDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		otherDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		userDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		colorDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
	case 2:
		screenDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		commDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		otherDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		userDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		colorDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
	case 3:
		screenDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		commDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		otherDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		userDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		colorDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
	case 4:
		screenDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		commDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		otherDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		userDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		colorDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		break;
	default:
		break;
	}
}



void CInitDlg::OnBnClickedSaveSet()
{
	switch (initTab.GetCurSel())
	{
	case 0:
		SaveScreenSet();
		break;
	case 1:
		SaveCommSet();
		break;
	case 2:
		SaveOtherSet();
		break;
	case 3:
		SaveUserSet();
		break;
	case 4:
		SaveColorSet();
		break;
	default: break;
	}
}

void CInitDlg::SaveScreenSet()
{
	screenDlg.SaveScreenSet();
}

void CInitDlg::SaveCommSet()
{
	commDlg.SaveCommSet();
}

void CInitDlg::SaveOtherSet()
{
	otherDlg.SaveOtherSet();
}

void CInitDlg::SaveUserSet()
{
	userDlg.SaveUserSet();
}



void CInitDlg::SaveColorSet()
{
	colorDlg.SaveColorSet();

}


