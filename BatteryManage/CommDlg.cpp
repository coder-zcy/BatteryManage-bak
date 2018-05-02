// CommDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "CommDlg.h"
#include "afxdialogex.h"


// CCommDlg 对话框

IMPLEMENT_DYNAMIC(CCommDlg, CDialog)

CCommDlg::CCommDlg(CWnd* pParent /*=NULL*/)
: CDialog(CCommDlg::IDD, pParent)
{

}

CCommDlg::~CCommDlg()
{
}

void CCommDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMMPORT, commPortBox);
	DDX_Control(pDX, IDC_COMMBAUD, commBaudBox);
	DDX_Control(pDX, IDC_COMM_TIME, commTimeBox);
	DDX_Control(pDX, IDC_CHK, chkChk);
	DDX_Control(pDX, IDC_NEED_LOGIN, needLoginChk);
	DDX_Control(pDX, IDC_FORBD_MODIFY, forbdModifyChk);
	DDX_Control(pDX, IDC_ONLINE_READ, onlineReadChk);
	DDX_Control(pDX, IDC_EXIT_READ, exitReadChk);
	DDX_Control(pDX, IDC_FORBD_OTHER, forbdOtherChk);
}


BEGIN_MESSAGE_MAP(CCommDlg, CDialog)
END_MESSAGE_MAP()


BOOL CCommDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	commConf = CommConf::GetInstance();

	int nportIndex = commPortBox.FindStringExact(0, commConf->commPortStr);
	commPortBox.SetCurSel(nportIndex);
	int nbaudIndex = commBaudBox.FindStringExact(0, commConf->commBaudStr);
	commBaudBox.SetCurSel(nbaudIndex);
	int ntimeIndex = commTimeBox.FindStringExact(0, commConf->commTimeStr);
	commTimeBox.SetCurSel(ntimeIndex);
	chkChk.SetCheck(commConf->chkVal);
	needLoginChk.SetCheck(commConf->needLoginVal);
	forbdModifyChk.SetCheck(commConf->forbdModifyVal);
	onlineReadChk.SetCheck(commConf->onlineReadVal);
	exitReadChk.SetCheck(commConf->exitReadVal);
	forbdOtherChk.SetCheck(commConf->forbdOtherVal);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CCommDlg::SaveCommSet()
{
	if (MessageBox(_T("确定要保存通信设置么"), _T("提示"), MB_OKCANCEL | MB_ICONWARNING) == IDOK)
	{
		wchar_t str[10];

		commPortBox.GetWindowTextW(commConf->commPortStr);
		commBaudBox.GetWindowTextW(commConf->commBaudStr);
		commTimeBox.GetWindowTextW(commConf->commTimeStr);

		commConf->commPortVal = _ttoi(commConf->commPortStr.Right(1));
		commConf->commBaudVal = _ttoi(commConf->commBaudStr);
		commConf->commTimeVal = _ttoi(commConf->commTimeStr);

		commConf->chkVal = chkChk.GetCheck();
		commConf->needLoginVal = needLoginChk.GetCheck();
		commConf->forbdModifyVal = forbdModifyChk.GetCheck();
		commConf->onlineReadVal = onlineReadChk.GetCheck();
		commConf->exitReadVal = exitReadChk.GetCheck();
		commConf->forbdOtherVal = forbdOtherChk.GetCheck();
	
		commConf->SaveCommConf();

		MessageBox(_T("保存通信设置成功!"));
	}
}