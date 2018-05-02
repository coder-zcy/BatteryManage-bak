// DataFileView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "DataFileView.h"


// CDataFileView
const int WIN_NUM = 5;

IMPLEMENT_DYNCREATE(CDataFileView, CFormView)

CDataFileView::CDataFileView()
	: CFormView(CDataFileView::IDD)
{
	compDlg = NULL;
	partDlg = NULL;
	curveDlg = NULL;
	loopDlg = NULL;
	statisticDlg = NULL;
	statisticMenuDlg = NULL;
	sloopMenuDlg = NULL;

	dlgArray.clear();
	dlgArray.push_back(compDlg);
	dlgArray.push_back(partDlg);
	dlgArray.push_back(statisticDlg);
	dlgArray.push_back(curveDlg);
	dlgArray.push_back(loopDlg);
	dlgArray.push_back(statisticMenuDlg);
	dlgArray.push_back(sloopMenuDlg);

	links.push_back(&compLink);
	links.push_back(&partLink);
	links.push_back(&statisticLink);
	links.push_back(&curveLink);
	links.push_back(&loopLink);

	linkNames.push_back(_T("�ۺ�����"));
	linkNames.push_back(_T("��������"));
	linkNames.push_back(_T("ͳ�Ʊ���"));
	linkNames.push_back(_T("��������"));
	linkNames.push_back(_T("ѭ��ͼ"));

	hoverLinkNames.push_back(_T("<a>�ۺ�����</a>"));
	hoverLinkNames.push_back(_T("<a>��������</a>"));
	hoverLinkNames.push_back(_T("<a>ͳ�Ʊ���</a>"));
	hoverLinkNames.push_back(_T("<a>��������</a>"));
	hoverLinkNames.push_back(_T("<a>ѭ��ͼ</a>"));

	InitCabDataFlag = FALSE;

	partCapCondDlg = NULL;

	batWorkDetailDlg = NULL;

	windowFlag = COMP_DLG_ID;

}

CDataFileView::~CDataFileView()
{

	for (int idx = 0; idx < fileCabData.stepPartbatterys.size(); ++idx)
	{
		for (int jdx = 0; jdx < fileCabData.stepPartbatterys[idx].size(); ++jdx)
		{
			if (fileCabData.stepPartbatterys[idx][jdx] != NULL)
			{
				delete fileCabData.stepPartbatterys[idx][jdx];
				fileCabData.stepPartbatterys[idx][jdx] = NULL;
			}
		}
	}

	for (int idx = 0; idx < fileCabData.endDisBatterys.size(); ++idx)
	{
		if (fileCabData.endDisBatterys[idx] != NULL)
		{
			delete fileCabData.endDisBatterys[idx];
			fileCabData.endDisBatterys[idx] = NULL;
		}
	}

	if (dlgArray[COMP_DLG_ID] != NULL) {
		((CCompDlg *)dlgArray[COMP_DLG_ID])->DestroyWindow();
		dlgArray[COMP_DLG_ID] = NULL;
	}
	if (dlgArray[PART_DLG_ID] != NULL) {
		((CPartDlg *)dlgArray[PART_DLG_ID])->DestroyWindow();
		dlgArray[PART_DLG_ID] = NULL;
	}
	if (dlgArray[STATISTIC_DLG_ID] != NULL) {
		((CStatisticDlg *)dlgArray[STATISTIC_DLG_ID])->DestroyWindow();
		dlgArray[STATISTIC_DLG_ID] = NULL;
	}
	if (dlgArray[CURVE_DLG_ID] != NULL) {
		((CCurveDlg *)dlgArray[CURVE_DLG_ID])->DestroyWindow();
		dlgArray[CURVE_DLG_ID] = NULL;
	}
	if (dlgArray[LOOP_DLG_ID] != NULL) {
		((CLoopDlg *)dlgArray[LOOP_DLG_ID])->DestroyWindow();
		dlgArray[LOOP_DLG_ID] = NULL;
	}

	if (partCapCondDlg != NULL)
	{
		partCapCondDlg->DestroyWindow();
		delete partCapCondDlg;
	}

	if (batWorkDetailDlg != NULL)
	{
		batWorkDetailDlg->DestroyWindow();
		delete batWorkDetailDlg;
	}
}

void CDataFileView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_DATA_MENU_PIC, menuPic);
	DDX_Control(pDX, IDC_COMP_LINK, compLink);
	DDX_Control(pDX, IDC_PART_LINK, partLink);
	DDX_Control(pDX, IDC_STATISTIC_LINK, statisticLink);
	DDX_Control(pDX, IDC_LOOP_LINK, loopLink);
	DDX_Control(pDX, IDC_CURVE_LINK, curveLink);
	DDX_Control(pDX, IDC_WIN_SEL, winSel);
	DDX_Control(pDX, IDC_DATA_PANE, dataPane);
}

BEGIN_MESSAGE_MAP(CDataFileView, CFormView)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()

	ON_NOTIFY(NM_CLICK, IDC_COMP_LINK, &CDataFileView::OnNMClickCompLink)
	ON_NOTIFY(NM_CLICK, IDC_PART_LINK, &CDataFileView::OnNMClickPartLink)
	ON_NOTIFY(NM_CLICK, IDC_STATISTIC_LINK, &CDataFileView::OnNMClickStatisticLink)
	ON_NOTIFY(NM_CLICK, IDC_CURVE_LINK, &CDataFileView::OnNMClickCurveLink)
	ON_NOTIFY(NM_CLICK, IDC_LOOP_LINK, &CDataFileView::OnNMClickLoopLink)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_PART_CAP_COND, &CDataFileView::OnPartCapCond)
	ON_COMMAND(ID_PART_SHOW_BATID, &CDataFileView::OnPartShowBatid)
	ON_COMMAND(ID_AUTO_PART_CAP, &CDataFileView::OnAutoPartCap)
	ON_MESSAGE(WM_UPDATE_PART_BAT_MSG, &CDataFileView::OnUpdatePartBattery)
	ON_MESSAGE(WM_REFRESG_DATAOPENVIEW_MSG, &CDataFileView::OnRefreshWindow)
	ON_MESSAGE(WM_LOOP_MENU_DATA_CHECK_MSG, &CDataFileView::OnChangeChartPosByCheck)
	ON_BN_CLICKED(IDC_FILE_INFO_BTN, &CDataFileView::OnBnClickedFileInfoBtn)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDataFileView ���

#ifdef _DEBUG
void CDataFileView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDataFileView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDataFileView ��Ϣ�������


void CDataFileView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParent()->SetWindowTextW(openFilePath);
	//this->SetWindowTextW(openFilePath);
	// TODO:  �ڴ����ר�ô����/����û���
	InitWinLinks();
	OpenCompDlg();

}

void CDataFileView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	CRect dlgRect;

	this->GetWindowRect(dlgRect);
	if (dataPane.m_hWnd)
	{
		dataPane.MoveWindow(MARGIN_LEFT_BATPANE, MARGIN_TOP_BATPANE, dlgRect.Width(), dlgRect.Height(), TRUE);
		
		if (dlgArray[COMP_DLG_ID] != NULL)
		{
			((CCompDlg*)dlgArray[COMP_DLG_ID])->OnSize(0, dlgRect.Width() - MARGIN_LEFT_BATPANE -5, dlgRect.Height() - MARGIN_TOP_BATPANE);
		}
		if (dlgArray[PART_DLG_ID])
		{
			((CPartDlg*)dlgArray[PART_DLG_ID])->OnSize(0, dlgRect.Width() - MARGIN_LEFT_BATPANE -5, dlgRect.Height() - MARGIN_TOP_BATPANE);
		}
		if (dlgArray[STATISTIC_DLG_ID] != NULL)
		{
			((CStatisticDlg *)dlgArray[STATISTIC_DLG_ID])->OnSize(0, dlgRect.Width() - MARGIN_LEFT_BATPANE -5, dlgRect.Height() - MARGIN_TOP_BATPANE);
		}
		if (dlgArray[CURVE_DLG_ID] != NULL)
		{
			((CCurveDlg *)dlgArray[CURVE_DLG_ID])->OnSize(0, dlgRect.Width() - MARGIN_LEFT_BATPANE -5, dlgRect.Height() - MARGIN_TOP_BATPANE);
		}
		if (dlgArray[LOOP_DLG_ID] != NULL)
		{
			((CLoopDlg *)dlgArray[LOOP_DLG_ID])->OnSize(0, dlgRect.Width() - MARGIN_LEFT_BATPANE -5, dlgRect.Height() - MARGIN_TOP_BATPANE);
		}
	}

	
	// TODO: �ڴ˴������Ϣ����������
}


void CDataFileView::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	//CRect rect;
	//dataPane.GetClientRect(&rect);
	//FillRect(dataPane.GetDC()->GetSafeHdc(), &rect, CBrush(RGB(255, 0, 0)));
}

void CDataFileView::InitWinLinks()
{
	CRect rect;
	compLink.GetWindowRect(rect);
	ScreenToClient(rect);
	CRect rect1;
	for (int idx = 0; idx < links.size(); ++idx)
	{
		if (idx >= 1)
		{
			rect.top += 24;
			rect.bottom += 24;
			links[idx]->MoveWindow(rect, true);
		}

		rect1 = rect;
		rect1.left -= 20;
		rect1.right = rect1.left + 16;
		rect1.top -= 2;
		rect1.bottom = rect1.top + 16;

		linkRects.push_back(rect);
		winRects.push_back(rect1);
	}

	winSel.SetBitmap(theApp.selBmp);
	winSel.MoveWindow(winRects[0], TRUE);
}




void CDataFileView::OnNMClickCompLink(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	
	windowFlag = COMP_DLG_ID;
	OpenCompDlg();

}

void CDataFileView::OnNMClickPartLink(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	windowFlag = PART_DLG_ID;
	if (links.size() == WIN_NUM)
	{
		winSel.MoveWindow(winRects[PART_DLG_ID], TRUE);
	}
	CRect rect;
	this->GetClientRect(&rect);
	for (size_t idx = 0; idx != dlgArray.size(); ++idx)
	{
		if (idx == PART_DLG_ID)
		{
			if ((dlgArray[idx]) == NULL)
			{
				dlgArray[idx] = new CPartDlg(NULL, fileCabData);
				//dlgArray[idx] = new CPartDlg();
				dlgArray[idx]->Create(IDD_PART_DLG, this);
				//dlgArray[idx]->MoveWindow(rect.left + DATA_LEFT_WIDTH, rect.top, rect.Width() - 20, rect.Height() - 10);
				((CPartDlg*)dlgArray[idx])->OnSize(0, rect.Width() - MARGIN_LEFT_BATPANE, rect.Height());
				((CPartDlg*)dlgArray[idx])->ShowWindow(SW_SHOW);
			}
			else
			{
				((CPartDlg*)dlgArray[idx])->OnSize(0, rect.Width() - MARGIN_LEFT_BATPANE, rect.Height());
				
				CapShowType *capShowType = CapShowType::GetInstance();

				((CPartDlg*)dlgArray[idx])->UpdatePartData(capShowType->GetAutoPartCapChk(),capShowType->GetPartShowBatidChk());
				((CPartDlg*)dlgArray[idx])->ShowWindow(SW_SHOW);

			}
			UpdateRelativeMenus();
		}
		else
		{
			if (dlgArray[idx] != NULL && dlgArray[idx]->m_hWnd != NULL)
				dlgArray[idx]->ShowWindow(SW_HIDE);
		}
	}
	
}


void CDataFileView::OnNMClickStatisticLink(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	windowFlag = STATISTIC_DLG_ID;
	if (links.size() == WIN_NUM)
	{
		winSel.MoveWindow(winRects[STATISTIC_DLG_ID], TRUE);
	}
	CRect rect;
	this->GetClientRect(&rect);
	for (size_t idx = 0; idx != dlgArray.size(); ++idx)
	{
		if (idx == STATISTIC_DLG_ID)
		{
			if ((dlgArray[idx]) == NULL)
			{
				dlgArray[idx] = new CStatisticDlg(NULL, fileCabData);
				//dlgArray[idx] = new CPartDlg();
				dlgArray[idx]->Create(IDD_STATISTIC_DLG, this);
				//dlgArray[idx]->MoveWindow(rect.left + DATA_LEFT_WIDTH, rect.top, rect.Width() - 20, rect.Height() - 10);
			}
			((CStatisticDlg*)dlgArray[idx])->OnSize(0, rect.Width() - MARGIN_LEFT_BATPANE, rect.Height());
			((CStatisticDlg*)dlgArray[idx])->ShowWindow(SW_SHOW);
			UpdateRelativeMenus();
			Invalidate();
		}
		else if (idx == STATISTIC_MENU_DLG_ID)
		{
			if ((dlgArray[idx]) == NULL)
			{
				menuPic.GetClientRect(&rect);
				dlgArray[idx] = new CStatisticMenuDlg();
				dlgArray[idx]->Create(IDD_STATISTIC_MENU_DLG, this);
				
			}
			dlgArray[idx]->MoveWindow(rect.left, rect.top + DATA_TOP_HEIGHT, rect.Width(), rect.Height());
			((CStatisticMenuDlg *)dlgArray[idx])->ShowWindow(SW_SHOW);
			Invalidate();
		}
		else
		{
			if (dlgArray[idx] != NULL && dlgArray[idx]->m_hWnd != NULL)
				dlgArray[idx]->ShowWindow(SW_HIDE);
		}
	}
}


void CDataFileView::OnNMClickCurveLink(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	windowFlag = CURVE_DLG_ID;
	if (links.size() == WIN_NUM)
	{
		winSel.MoveWindow(winRects[3], TRUE);
	}
	CRect rect;
	this->GetClientRect(&rect);
	for (size_t idx = 0; idx != dlgArray.size(); ++idx)
	{
		if (idx == CURVE_DLG_ID)
		{
			if ((dlgArray[idx]) == NULL)
			{
				dlgArray[idx] = new CCurveDlg(NULL, fileCabData);
				//dlgArray[idx] = new CPartDlg();
				dlgArray[idx]->Create(IDD_CURVE_DLG, this);
				//dlgArray[idx]->MoveWindow(rect.left + DATA_LEFT_WIDTH, rect.top, rect.Width() - 20, rect.Height() - 10);
			}
			((CCurveDlg*)dlgArray[idx])->OnSize(0, rect.Width() - MARGIN_LEFT_BATPANE, rect.Height());
			((CCurveDlg*)dlgArray[idx])->ShowWindow(SW_SHOW);
			Invalidate();
		}
		else if (idx == SLOOP_MENU_DLG_ID)
		{
			if ((dlgArray[idx]) == NULL)
			{
				CRect rect;
				menuPic.GetClientRect(&rect);
				dlgArray[idx] = new CSloopMenuDlg();
				dlgArray[idx]->Create(IDD_SLOOP_MENU_DLG, this);
				dlgArray[idx]->MoveWindow(rect.left, rect.top + DATA_TOP_HEIGHT, rect.Width(), rect.Height());
			}
			dlgArray[idx]->ShowWindow(SW_SHOW);
			Invalidate();
		}
		else
		{
			if (dlgArray[idx] != NULL && dlgArray[idx]->m_hWnd != NULL)
				dlgArray[idx]->ShowWindow(SW_HIDE);
		}
	}
}


void CDataFileView::OnNMClickLoopLink(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	windowFlag = LOOP_DLG_ID;
	if (links.size() == WIN_NUM)
	{
		winSel.MoveWindow(winRects[LOOP_DLG_ID], TRUE);
	}
	for (size_t idx = 0; idx != dlgArray.size(); ++idx)
	{
		if (idx == LOOP_DLG_ID)
		{
			if ((dlgArray[idx]) == NULL)
			{
				CRect rect;
				dataPane.GetClientRect(&rect);
				dlgArray[idx] = new CLoopDlg();
				dlgArray[idx]->Create(IDD_LOOP_DLG, this);

				dlgArray[idx]->MoveWindow(rect.left + DATA_LEFT_WIDTH, rect.top, rect.Width() - 10, rect.Height() - 5);
			}
			dlgArray[idx]->ShowWindow(SW_SHOW);
			Invalidate();
		}
		else if (idx == SLOOP_MENU_DLG_ID)
		{
			if ((dlgArray[idx]) == NULL)
			{
				CRect rect;
				menuPic.GetClientRect(&rect);
				dlgArray[idx] = new CSloopMenuDlg();
				dlgArray[idx]->Create(IDD_SLOOP_MENU_DLG, this);
				dlgArray[idx]->MoveWindow(rect.left, rect.top + DATA_TOP_HEIGHT, rect.Width(), rect.Height());
			}
			dlgArray[idx]->ShowWindow(SW_SHOW);
			Invalidate();
		}
		else
		{
			if (dlgArray[idx] != NULL && dlgArray[idx]->m_hWnd != NULL)
				dlgArray[idx]->ShowWindow(SW_HIDE);
		}
	}

}


void CDataFileView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int idx;
	CString str;
	for (idx = 0; idx < links.size(); ++idx)
	{
		links[idx]->GetWindowTextW(str);
		if (point.x > linkRects[idx].left && point.x < linkRects[idx].right &&
			point.y > linkRects[idx].top && point.y < linkRects[idx].bottom)
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
	CFormView::OnMouseMove(nFlags, point);
}

void CDataFileView::InitDataContent(CString openFilePath)
{
	fileCabData = CFileCabData(openFilePath);
}
	

void CDataFileView::OpenCompDlg()
{
	if (links.size() == WIN_NUM)
	{
		winSel.MoveWindow(winRects[COMP_DLG_ID], TRUE);
	}
	CRect rect;
	this->GetWindowRect(&rect);

	if (InitCabDataFlag == FALSE)	{
		InitDataContent(openFilePath);
		InitCabDataFlag = TRUE;
	}
	
	for (size_t idx = 0; idx != dlgArray.size(); ++idx)
	{
		if (idx == COMP_DLG_ID)
		{
			if ((dlgArray[idx]) == NULL)
			{
				dlgArray[idx] = new CCompDlg(NULL,fileCabData);
				dlgArray[idx]->Create(IDD_COMP_DLG, this);
				//dlgArray[idx]->MoveWindow(rect.left + DATA_LEFT_WIDTH, rect.top, rect.Width() - 20, rect.Height() - 10);
			}
			((CCompDlg*)dlgArray[idx])->OnSize(0, rect.Width() - MARGIN_LEFT_BATPANE, rect.Height());
			dlgArray[idx]->ShowWindow(SW_SHOW);

			UpdateRelativeMenus();
			Invalidate();
		}
		else
		{
			if (dlgArray[idx] != NULL && dlgArray[idx]->m_hWnd != NULL)
				dlgArray[idx]->ShowWindow(SW_HIDE);
		}
	}
}


void CDataFileView::OnPartCapCond()
{
	// TODO:  �ڴ���������������

	CapShowType *capShowType = CapShowType::GetInstance();

	CMenu   menu;   //��������Ҫ�õ���cmenu����
	menu.LoadMenu(IDR_PART_MENU); //װ���Զ�����Ҽ��˵� 
	CMenu   *pContextMenu = menu.GetSubMenu(0); //��ȡ��һ�������˵������Ե�һ���˵��������Ӳ˵� 

	if (pContextMenu != NULL)
	{
		int check = (capShowType->GetPartCapCondChk() == MF_CHECKED ? MF_UNCHECKED : MF_CHECKED);
		pContextMenu->CheckMenuItem(ID_PART_CAP_COND, check);
		capShowType->SetPartCapCondChk(check);

		if (partCapCondDlg == NULL)
		{
			partCapCondDlg = new CPartCapCondDlg();
		}
		partCapCondDlg->DoModal();
	}

}


void CDataFileView::OnPartShowBatid()
{
	// TODO:  �ڴ���������������
	CapShowType *capShowType = CapShowType::GetInstance();

	CMenu   menu;   //��������Ҫ�õ���cmenu����
	menu.LoadMenu(IDR_PART_MENU); //װ���Զ�����Ҽ��˵� 
	CMenu   *pContextMenu = menu.GetSubMenu(0); //��ȡ��һ�������˵������Ե�һ���˵��������Ӳ˵� 

	if (pContextMenu != NULL)
	{
		int idCheck = (capShowType->GetPartShowBatidChk() == MF_CHECKED ? MF_UNCHECKED : MF_CHECKED);
		pContextMenu->CheckMenuItem(ID_PART_SHOW_BATID, idCheck);
		capShowType->SetPartShowBatidChk(idCheck);

		int autoCheck = capShowType->GetAutoPartCapChk();
		
		if (dlgArray[PART_DLG_ID] != NULL && dlgArray[PART_DLG_ID]->m_hWnd)
		{
			CPartDlg *pdlg = (CPartDlg*)(dlgArray[PART_DLG_ID]);
			pdlg->UpdatePartData(autoCheck,idCheck);
		}
	}

}


void CDataFileView::OnAutoPartCap()
{
	// TODO:  �ڴ���������������
	CapShowType *capShowType = CapShowType::GetInstance();

	CMenu   menu;   //��������Ҫ�õ���cmenu����
	menu.LoadMenu(IDR_PART_MENU); //װ���Զ�����Ҽ��˵� 
	CMenu   *pContextMenu = menu.GetSubMenu(0); //��ȡ��һ�������˵������Ե�һ���˵��������Ӳ˵� 

	if (pContextMenu != NULL)
	{
		int autoCheck = (capShowType->GetAutoPartCapChk() == MF_CHECKED ? MF_UNCHECKED : MF_CHECKED);
		pContextMenu->CheckMenuItem(ID_AUTO_PART_CAP, autoCheck);
		capShowType->SetAutoPartCapChk(autoCheck);

		int idCheck = capShowType->GetPartShowBatidChk();

		if (dlgArray[PART_DLG_ID] != NULL && dlgArray[PART_DLG_ID]->m_hWnd)
		{
			CPartDlg *pdlg = (CPartDlg*)(dlgArray[PART_DLG_ID]);
			pdlg->UpdatePartData(autoCheck, idCheck);
		}
		if (dlgArray[STATISTIC_DLG_ID] != NULL && dlgArray[STATISTIC_DLG_ID]->m_hWnd)
		{
			CStatisticDlg *statisticDlg = (CStatisticDlg *)(dlgArray[STATISTIC_DLG_ID]);
				
				statisticDlg->UpdateSegData(autoCheck);
				statisticDlg->UpdateCapData(autoCheck);
		}
	}
}

LRESULT CDataFileView::OnUpdatePartBattery(WPARAM wParam, LPARAM lParam)
{

	// ����stepPartBatterys��capFlag
	CapShowType *capShowType = CapShowType::GetInstance();
	
	BSTR b = (BSTR)wParam;
	CString paraStr(b);
	SysFreeString(b);

	if (paraStr != NULL_FLAG_STR)
	{
		capShowType->UpdateInstance(paraStr);
	}
	int capacity, capFlag;

	vector<vector<CPartBattery* >> stepPartbatterys = fileCabData.stepPartbatterys;
	for (int idx = 0; idx < stepPartbatterys.size(); ++idx)
	{
		for (int jdx = 0; jdx < stepPartbatterys[idx].size(); ++jdx)
		{
			if (stepPartbatterys[idx][jdx] != NULL)
			{
				capacity = _ttoi(stepPartbatterys[idx][jdx]->capacity);
				capFlag = 0;

				while (capFlag < capShowType->validenum)
				{
					if (capacity <= capShowType->maxVals[capFlag])
					{
						stepPartbatterys[idx][jdx]->capFlag = capFlag;
						break;
					}
					else capFlag++;
				}
				if (capFlag == capShowType->validenum)
				{
					stepPartbatterys[idx][jdx]->capFlag = capFlag;
				}
			}
		}
	}
	if (dlgArray[PART_DLG_ID] != NULL && dlgArray[PART_DLG_ID]->m_hWnd)
		{
			CPartDlg *pdlg = (CPartDlg*)(dlgArray[PART_DLG_ID]);
			pdlg->UpdatePartData(capShowType->GetAutoPartCapChk(), capShowType->GetPartShowBatidChk());
		}
	if (dlgArray[STATISTIC_DLG_ID] != NULL && dlgArray[STATISTIC_DLG_ID]->m_hWnd)
	{
		CStatisticDlg *statisticDlg = (CStatisticDlg *)(dlgArray[STATISTIC_DLG_ID]);
		statisticDlg->UpdateSegData(capShowType->GetAutoPartCapChk());
		statisticDlg->UpdateCapData(capShowType->GetAutoPartCapChk());
		statisticDlg->UpdateChartData();
	}



	return NULL;
}

LRESULT CDataFileView::OnRefreshWindow(WPARAM wParam, LPARAM lParam)
{
	Invalidate();
	UpdateWindow();
	return NULL;
}



LRESULT CDataFileView::OnChangeChartPosByCheck(WPARAM wParam, LPARAM lParam)
{
	BSTR b = (BSTR)wParam;
	CString paraStr(b);
	SysFreeString(b);

	int check = _ttoi(paraStr);
	if (dlgArray[CURVE_DLG_ID] != NULL && dlgArray[CURVE_DLG_ID]->m_hWnd)
	{
		CCurveDlg *curDlg = (CCurveDlg *)dlgArray[CURVE_DLG_ID];
		curDlg->ChangeChartPosByCheck(check);
	}
	return NULL;
}

void CDataFileView::OnBnClickedFileInfoBtn()
{
	if (batWorkDetailDlg == NULL || !(batWorkDetailDlg->m_hWnd)) {
		
		batWorkDetailDlg = new CBatWorkDetailDlg(NULL, openFilePath, windowFlag);
		batWorkDetailDlg->DoModal();
	}
}

void CDataFileView::UpdateRelativeMenus()
{
	// ����CSLoopMenuDLg
	CSloopMenuDlg *sloopMenuDlg = (CSloopMenuDlg*)dlgArray[SLOOP_MENU_DLG_ID];
	if (sloopMenuDlg != NULL && sloopMenuDlg->m_hWnd)
	{
		sloopMenuDlg->dataCheck.SetCheck(0);
	}
}


void CDataFileView::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	CFormView::OnClose();
}


BOOL CDataFileView::DestroyWindow()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CFormView::DestroyWindow();
	CString flag = L"1";
	//::SendNotifyMessage(((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->m_hWnd, WM_COLSE_DATAFILEVIEW_MSG, WPARAM(flag.AllocSysString()), NULL);
	
	::SendNotifyMessage(theApp.m_pMainWnd->m_hWnd, WM_COLSE_DATAFILEVIEW_MSG, WPARAM(flag.AllocSysString()), NULL);
	return TRUE;
}
