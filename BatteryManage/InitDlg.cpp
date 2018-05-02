// InitDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "InitDlg.h"
#include "afxdialogex.h"


// CInitDlg 对话框

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


// CInitDlg 消息处理程序
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
	CRect tabRect;   // 标签控件客户区的位置和大小   

	initTab.InsertItem(0, _T("屏号参数"));         // 插入标签  
	initTab.InsertItem(1, _T("通讯设置"));
	initTab.InsertItem(2, _T("其它设置"));
	initTab.InsertItem(3, _T("用户设置"));
	initTab.InsertItem(4, _T("颜色设置"));

	screenDlg.Create(IDD_SCREEN_DLG, &initTab);    // 创建第一个标签页   
	commDlg.Create(IDD_COMM_DLG, &initTab);
	otherDlg.Create(IDD_OTHER_DLG, &initTab);    // 创建第一个标签页   
	colorDlg.Create(IDD_COLOR_DLG, &initTab);    // 创建第一个标签页   
	userDlg.Create(IDD_USER_DLG, &initTab);    // 创建第一个标签页   

	initTab.GetClientRect(&tabRect);    // 获取标签控件客户区Rect   
	// 调整tabRect，使其覆盖范围适合放置标签页   
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;
	// 根据调整好的tabRect放置m_jzmDlg子对话框，并设置为显示   
	screenDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
	// 根据调整好的tabRect放置m_androidDlg子对话框，并设置为隐藏   
	commDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

	otherDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

	userDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

	colorDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

	return TRUE;  // return TRUE  unless you set the focus to a control   

}


void CInitDlg::OnTcnSelchangeInittab(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	CRect tabRect;    // 标签控件客户区的Rect   

	// 获取标签控件客户区Rect，并对其调整，以适合放置标签页   
	initTab.GetClientRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;

	switch (initTab.GetCurSel())
	{
		// 如果标签控件当前选择标签为“鸡啄米”，则显示m_jzmDlg对话框，隐藏m_androidDlg对话框   
	case 0:
		screenDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		commDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		otherDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		userDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		colorDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
		// 如果标签控件当前选择标签为“Android开发网”，则隐藏m_jzmDlg对话框，显示m_androidDlg对话框   
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


