// BatteryCheckView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "BatteryCheckView.h"

#include "MainFrm.h"


// CBatteryCheckView

IMPLEMENT_DYNCREATE(CBatteryCheckView, CFormView)

CBatteryCheckView::CBatteryCheckView()
	: CFormView(CBatteryCheckView::IDD)
{
	links.push_back(&setInfoStatic);
	links.push_back(&preDataStatic);
	links.push_back(&showStyleStatic);
	links.push_back(&leftMouseStatic);
	links.push_back(&specCtlStatic);

	rects.push_back(setRect);
	rects.push_back(preRect);
	rects.push_back(showRect);
	rects.push_back(leftRect);
	rects.push_back(specRect);

	linkNames.push_back(_T("�趨��Ϣ"));
	linkNames.push_back(_T("��ʷ����"));
	linkNames.push_back(_T("��ʾ��ʽ"));
	linkNames.push_back(_T("������"));
	linkNames.push_back(_T("�������"));

	hoverLinkNames.push_back(_T("<a>�趨��Ϣ</a>"));
	hoverLinkNames.push_back(_T("<a>��ʷ����</a>"));
	hoverLinkNames.push_back(_T("<a>��ʾ��ʽ</a>"));
	hoverLinkNames.push_back(_T("<a>������</a>"));
	hoverLinkNames.push_back(_T("<a>�������</a>"));

	deviceSetInfoDlg = NULL;
	pbatterysDlg = NULL;
	tbatterysDlg = NULL;
	fbatterysDlg = NULL;
	ebatterysDlg = NULL;
}

CBatteryCheckView::~CBatteryCheckView()
{
	if (deviceSetInfoDlg != NULL) delete deviceSetInfoDlg;
	if (pbatterysDlg != NULL) delete pbatterysDlg;
	if (tbatterysDlg != NULL) delete tbatterysDlg;
	if (fbatterysDlg != NULL) delete fbatterysDlg;
	if (ebatterysDlg != NULL) delete ebatterysDlg;
}

void CBatteryCheckView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);

	//DDX_Control(pDX, IDC_PRE_DATA_STATIC, preDataStatic);
	//DDX_Control(pDX, IDC_SET_INFO_STATIC, setInfoStatic);
	//DDX_Control(pDX, IDC_SHOW_STYLE_STATIC, showStyleStatic);
	//DDX_Control(pDX, IDC_LEFT_MOUSE_STATIC, leftMouseStatic);
	//DDX_Control(pDX, IDC_SPEC_CTL_STATIC, specCtlStatic);
	//DDX_Control(pDX, IDC_BATTERYS_PANE, batterysPanePic);
	DDX_Control(pDX, IDC_SET_INFO_STATIC, setInfoStatic);
	DDX_Control(pDX, IDC_PRE_DATA_STATIC, preDataStatic);
	DDX_Control(pDX, IDC_SHOW_STYLE_STATIC, showStyleStatic);
	DDX_Control(pDX, IDC_LEFT_MOUSE_STATIC, leftMouseStatic);
	DDX_Control(pDX, IDC_SPEC_CTL_STATIC, specCtlStatic);
}

BEGIN_MESSAGE_MAP(CBatteryCheckView, CFormView)
	ON_WM_CLOSE()
	//ON_NOTIFY(NM_CLICK, IDC_SET_INFO_STATIC, &CBatteryCheckView::OnNMClickSetInfoStatic)
	//ON_NOTIFY(NM_CLICK, IDC_PRE_DATA_STATIC, &CBatteryCheckView::OnNMClickPreDataStatic)
	//ON_NOTIFY(NM_CLICK, IDC_SHOW_STYLE_STATIC, &CBatteryCheckView::OnNMClickShowStyleStatic)
	//ON_NOTIFY(NM_CLICK, IDC_LEFT_MOUSE_STATIC, &CBatteryCheckView::OnNMClickLeftMouseStatic)
	//ON_NOTIFY(NM_CLICK, IDC_SPEC_CTL_STATIC, &CBatteryCheckView::OnNMClickSpecCtlStatic)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_MOUSEHOVER()
	//ON_NOTIFY(NM_RCLICK, IDC_SHOW_STYLE_STATIC, &CBatteryCheckView::OnNMRClickShowStyleStatic)
	//ON_NOTIFY(NM_RCLICK, IDC_LEFT_MOUSE_STATIC, &CBatteryCheckView::OnNMRClickLeftMouseStatic)
	//ON_NOTIFY(NM_RCLICK, IDC_SPEC_CTL_STATIC, &CBatteryCheckView::OnNMRClickSpecCtlStatic)
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
	//ON_COMMAND(ID_BATTERY_SELECT, &CBatteryCheckView::OnBatterySelect)
	ON_WM_MOVE()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CBatteryCheckView ���

#ifdef _DEBUG
void CBatteryCheckView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CBatteryCheckView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBatteryCheckView ��Ϣ�������


BOOL CBatteryCheckView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO:  �ڴ����ר�ô����/����û���

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CBatteryCheckView::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CFormView::OnClose();
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->batteryCheckFrame = NULL;
}


//void CBatteryCheckView::OnNMClickSetInfoStatic(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	*pResult = 0;
//	if (deviceSetInfoDlg == NULL)
//	{
//		deviceSetInfoDlg = new CDeviceSetInfoDlg();
//	}
//	deviceSetInfoDlg->DoModal();
//}


//void CBatteryCheckView::OnNMClickPreDataStatic(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	*pResult = 0;
//}


//void CBatteryCheckView::OnNMClickShowStyleStatic(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	*pResult = 0;
//	CMenu menu;
//	CMenu *pSubMenu;
//	menu.LoadMenuW(IDR_BATTERY_SHOW_STYLE);
//	pSubMenu = menu.GetSubMenu(0);
//	CRect rect;
//	showStyleStatic.GetWindowRect(&rect);
//	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN, rect.left + rect.Width(), rect.top, this);
//
//}


//void CBatteryCheckView::OnNMClickLeftMouseStatic(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	*pResult = 0;
//
//	CMenu menu;
//	CMenu *pSubMenu;
//	menu.LoadMenuW(IDR_LEFT_MOUSE_MENU);
//	pSubMenu = menu.GetSubMenu(0);
//	CRect rect;
//	leftMouseStatic.GetWindowRect(&rect);
//	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN, rect.left + rect.Width(), rect.top, this);
//}


//void CBatteryCheckView::OnNMClickSpecCtlStatic(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	*pResult = 0;
//
//	CMenu menu;
//	CMenu *pSubMenu;
//	menu.LoadMenuW(IDR_SPEC_CONTROL_MENU);
//	pSubMenu = menu.GetSubMenu(0);
//	CRect rect;
//	leftMouseStatic.GetWindowRect(&rect);
//	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN, rect.left + rect.Width(), rect.top, this);
//}


//void CBatteryCheckView::OnMouseMove(UINT nFlags, CPoint point)
//{
//	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	int idx;
//	CString str;
//	for (idx = 0; idx < links.size(); ++idx)
//	{
//		links[idx]->GetWindowTextW(str);
//		if (point.x > rects[idx].left && point.x < rects[idx].right &&
//			point.y > rects[idx].top && point.y < rects[idx].bottom)
//		{
//			if (str != hoverLinkNames[idx]) {
//				links[idx]->SetWindowTextW(hoverLinkNames[idx]);
//			}
//		}
//		else
//		{
//			if (str != linkNames[idx]) {
//				links[idx]->SetWindowTextW(linkNames[idx]);
//			}
//			//(*links[idx]).SetWindowTextW(linkNames[idx]);
//		}
//	}
//	CFormView::OnMouseMove(nFlags, point);
//}


//void CBatteryCheckView::OnInitialUpdate()
//{
//	CFormView::OnInitialUpdate();
//
//	//(1) ʵʱ��ȡ��syslink��λ��
//	for (int idx = 0; idx < links.size(); ++idx)
//	{
//		links[idx]->GetWindowRect(&rects[idx]);
//		ScreenToClient(&rects[idx]);
//	}
//
//	//(2) ����ذ�
//	CRect batPaneRect;
//	batterysPanePic.GetClientRect(&batPaneRect);
//	ScreenToClient(batPaneRect);
//
//	pbatterysDlg = new CPbatterysDlg();
//	pbatterysDlg->Create(IDD_PBATTERYS_DLG, this);
//	pbatterysDlg->MoveWindow(135, 30, batPaneRect.Width(), batPaneRect.Height(), TRUE);
//	pbatterysDlg->ShowWindow(SW_NORMAL);
//
//	if (pbatterysDlg != NULL) {
//		pbatterysDlg->MoveWindow(135, 30, batPaneRect.Width(), batPaneRect.Height(), TRUE);
//	}
//
//	// �쳣:  OCX ����ҳӦ���� FALSE
//}


void CBatteryCheckView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	CRect dlgRect;
	this->GetClientRect(dlgRect);

	if (batterysPanePic.m_hWnd) {
		batterysPanePic.MoveWindow(MARGIN_LEFT_BATPANE, MARGIN_TOP_BATPANE, dlgRect.Width(), dlgRect.Height(), TRUE);
		if (pbatterysDlg != NULL)
			pbatterysDlg->OnSize(0, dlgRect.Width() - MARGIN_LEFT_BATPANE, dlgRect.Height() - MARGIN_TOP_BATPANE);
		if (tbatterysDlg != NULL)
			tbatterysDlg->OnSize(0, dlgRect.Width() - MARGIN_LEFT_BATPANE, dlgRect.Height() - MARGIN_TOP_BATPANE);
		if (fbatterysDlg != NULL)
			fbatterysDlg->OnSize(0, dlgRect.Width() - MARGIN_LEFT_BATPANE, dlgRect.Height() - MARGIN_TOP_BATPANE);
		if (ebatterysDlg != NULL)
			ebatterysDlg->OnSize(0, dlgRect.Width() - MARGIN_LEFT_BATPANE, dlgRect.Height() - MARGIN_TOP_BATPANE);

	}
}


//void CBatteryCheckView::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
//{
//	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	lpMMI->ptMinTrackSize.x = 720;
//
//	lpMMI->ptMinTrackSize.y = 480;
//
//	CFormView::OnGetMinMaxInfo(lpMMI);
//}


//void CBatteryCheckView::OnMouseHover(UINT nFlags, CPoint point)
//{
//	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	CRect batPaneRect;
//	batterysPanePic.GetClientRect(&batPaneRect);
//	ScreenToClient(batPaneRect);
//
//	CFormView::OnMouseHover(nFlags, point);
//}


//void CBatteryCheckView::OnNMRClickShowStyleStatic(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	CMenu   menu;   //��������Ҫ�õ���cmenu����
//	menu.LoadMenu(IDR_BATTERY_SHOW_STYLE); //װ���Զ�����Ҽ��˵� 
//	CMenu   *pContextMenu = menu.GetSubMenu(0); //��ȡ��һ�������˵������Ե�һ���˵��������Ӳ˵� 
//
//
//
//	CPoint point;//����һ������ȷ�����λ�õ�λ��  
//	GetCursorPos(&point);//��ȡ��ǰ����λ�ã��Ա�ʹ�ò˵����Ը�����  
//	pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd()); //��ָ��λ����ʾ�����˵�
//
//	*pResult = 0;
//}


//void CBatteryCheckView::OnNMRClickLeftMouseStatic(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	*pResult = 0;
//}


//void CBatteryCheckView::OnNMRClickSpecCtlStatic(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	*pResult = 0;
//}


//void CBatteryCheckView::OnRButtonUp(UINT nFlags, CPoint point)
//{
//	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//	CFormView::OnRButtonUp(nFlags, point);
//
//
//}


//void CBatteryCheckView::OnRButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//	CFormView::OnRButtonDown(nFlags, point);
//
//	int b = 0;
//}


//void CBatteryCheckView::OnBatterySelect()
//{
//	// TODO:  �ڴ���������������
//}


//void CBatteryCheckDlg::OnMove(int x, int y)
//{
//	CDialog::OnMove(x, y);
//
//	// TODO:  �ڴ˴������Ϣ����������
//}


//void CBatteryCheckView::OnMove(int x, int y)
//{
//	CFormView::OnMove(x, y);
//	int a = 0;
//	// TODO:  �ڴ˴������Ϣ����������
//}


//void CBatteryCheckView::OnWindowPosChanging(WINDOWPOS* lpwndpos)
//{
//	CFormView::OnWindowPosChanging(lpwndpos);
//	//int a = 0;
//	this->UpdateWindow();
//	//CView *view = NULL;
//	//CDocument *doc = ((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveDocument();
//
//	//view = ((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveView();
//	//
//	//if (view != NULL)
//	//{
//	//	this->UpdateWindow();
//	//	//view->UpdateData(TRUE);
//	//	//view->UpdateWindow();
//	//}
//	// TODO:  �ڴ˴������Ϣ����������
//}


void CBatteryCheckView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int idx;
	CString str;
	if (links[0]->m_hWnd != NULL) {
		for (idx = 0; idx < links.size(); ++idx)
		{
			links[idx]->GetWindowTextW(str);
			if (point.x > rects[idx].left && point.x < rects[idx].right &&
				point.y > rects[idx].top && point.y < rects[idx].bottom)
			{
				if (str != hoverLinkNames[idx]) {
					links[idx]->SetWindowTextW(hoverLinkNames[idx]);
				}
			}
			else
			{
				if (str != linkNames[idx]) {
					links[idx]->SetWindowTextW(linkNames[idx]);
				}
				//(*links[idx]).SetWindowTextW(linkNames[idx]);
			}
		}
	}
	CFormView::OnMouseMove(nFlags, point);
}


void CBatteryCheckView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	
	//(1) ʵʱ��ȡ��syslink��λ��
	for (int idx = 0; idx < links.size(); ++idx)
	{
		links[idx]->GetWindowRect(&rects[idx]);
		ScreenToClient(&rects[idx]);
	}
	
	//(2) ����ذ�
	CRect batPaneRect;
	batterysPanePic.GetClientRect(&batPaneRect);
	ScreenToClient(batPaneRect);
	
	pbatterysDlg = new CPbatterysDlg();
	pbatterysDlg->Create(IDD_PBATTERYS_DLG, this);
	pbatterysDlg->MoveWindow(135, 30, batPaneRect.Width(), batPaneRect.Height(), TRUE);
	pbatterysDlg->ShowWindow(SW_NORMAL);
	
	if (pbatterysDlg != NULL) {
		pbatterysDlg->MoveWindow(135, 30, batPaneRect.Width(), batPaneRect.Height(), TRUE);
	}
	
}
