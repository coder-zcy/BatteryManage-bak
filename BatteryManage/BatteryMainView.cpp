// BatteryCheckView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include <sstream>

#include "BatteryManage.h"
#include "BatteryMainView.h"
#include "DbUtils.h"
#include "TimeUtils.h"
#include "MainFrm.h"

using namespace std;

BYTE ByteHigh[] = { 0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0 };
BYTE ByteLow[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F };
char BYTE2CHAR[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
// CBatteryCheckView

const string SCSA_CHARGE_STR = "������ѹ���";
const string SA_CHARGE_STR = "�������";
const string SA_DISCHARGE_STR = "�����ŵ�";
const string LAY_STR = "����";
const string OVER_STR = "����";
const string LOOP_STR = "ѭ��";

const int PIC_STYLE = 0;
const int TABLE_STYLE = 1;
const int COMP_STYLE = 2;
const int EXCEP_STYLE = 3;


// ȫ�ֱ���,����ͨ��ģʽ
int COMM_MODE = 0;
CString lowerInfos = L"";		//	ȫ�ֱ����洢����λ������������Ϣ




UINT SendThread(LPVOID param);
void SaveDbConfs(LPVOID param);


// �����Ƿ���Ҫ�����µ����ݿ����TestInfo
// ��������TestInfo  vector�������ݿ�TestInfo��
void SaveDbTestInfos(LPVOID param);

IMPLEMENT_DYNCREATE(CBatteryMainView, CFormView)

CBatteryMainView::CBatteryMainView()
: CFormView(CBatteryMainView::IDD)
{
	paintFlag = FALSE;

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
	//pbatterysDlg = NULL;
	//tbatterysDlg = NULL;
	//cbatterysDlg = NULL;
	//ebatterysDlg = NULL;

	cabLinks.clear();
	cabLinks.push_back(&cabLink1);
	cabLinks.push_back(&cabLink2);
	cabLinks.push_back(&cabLink3);
	cabLinks.push_back(&cabLink4);
	cabLinks.push_back(&cabLink5);

	cabLinks.push_back(&cabLink6);
	cabLinks.push_back(&cabLink7);
	cabLinks.push_back(&cabLink8);
	cabLinks.push_back(&cabLink9);
	cabLinks.push_back(&cabLink10);

	cabLinks.push_back(&cabLink11);
	cabLinks.push_back(&cabLink12);
	cabLinks.push_back(&cabLink13);
	cabLinks.push_back(&cabLink14);
	cabLinks.push_back(&cabLink15);

	cabLinks.push_back(&cabLink16);
	cabLinks.push_back(&cabLink17);
	cabLinks.push_back(&cabLink18);
	cabLinks.push_back(&cabLink19);
	cabLinks.push_back(&cabLink20);



	curCabId = INVALIDE_CABID;
	count = 0;

	CanConnFlag = FALSE;
	PortOpenFlag = FALSE;

	SendStepFlag = FALSE;

	BatShowStyle = PIC_STYLE;

	for (int idx = 0; idx < MAX_CAB_NUM; ++idx)
	{
		pbatterysDlgs[idx] = NULL;
		tbatterysDlgs[idx] = NULL;
		ebatterysDlgs[idx] = NULL;
		cbatterysDlgs[idx] = NULL;
		workStateDescStrs[idx] = L"";				//ǰһ���Ĺ���״̬����
	}

	OBTAIN_BATDATA_FLAG = FALSE;
}

CBatteryMainView::~CBatteryMainView()
{
	for (int i = 0; i < cabStepMsgs.size(); ++i)
	{
		vector<CByteArray *> stepMsgs = cabStepMsgs[i];

		for (int j = 0; j < stepMsgs.size(); ++j)
		{
			if (stepMsgs[j] != NULL)
			{
				delete stepMsgs[j];
				stepMsgs[j] = NULL;
			}
		}
	}

	// ������¼�������״̬��ȫ�ֱ��� lowerCabs
	for (int idx = 0; idx < lowerCabs.cabBatterys.size(); ++idx)
	{
		if (lowerCabs.cabBatterys[idx] != NULL)
		{
			delete lowerCabs.cabBatterys[idx];
			lowerCabs.cabBatterys[idx] = NULL;
		}
	}

	for (int idx = 0; idx < obtainModelMsgs.size(); ++idx)
	{
		if (obtainModelMsgs[idx] != NULL)
		{
			delete obtainModelMsgs[idx];
			obtainModelMsgs[idx] = NULL;
		}
	}
	for (int idx = 0; idx < cabConMsgs.size(); ++ idx)
	{
		if (cabConMsgs[idx] != NULL)
		{
			delete cabConMsgs[idx];
			cabConMsgs[idx] = NULL;
		}
	}

	if (deviceSetInfoDlg != NULL) delete deviceSetInfoDlg;
	for (int idx = 0; idx < MAX_CAB_NUM; ++idx)
	{
		if (pbatterysDlgs[idx] != NULL)
		{
			pbatterysDlgs[idx]->DestroyWindow();
			delete pbatterysDlgs[idx];
			pbatterysDlgs[idx] = NULL;
		}
		if (tbatterysDlgs[idx] != NULL)
		{
			tbatterysDlgs[idx]->DestroyWindow();
			delete tbatterysDlgs[idx];
			tbatterysDlgs[idx] = NULL;
		}
		if (cbatterysDlgs[idx] != NULL)
		{
			cbatterysDlgs[idx]->DestroyWindow();
			delete cbatterysDlgs[idx];
			cbatterysDlgs[idx] = NULL;
		}
		if (ebatterysDlgs[idx] != NULL)
		{
			ebatterysDlgs[idx]->DestroyWindow();
			delete ebatterysDlgs[idx];
			ebatterysDlgs[idx] = NULL;
		}
	}

	for (int idx = 0; idx < testInfos.size(); ++idx)
	{
		if (testInfos[idx] != NULL)
		{
			delete testInfos[idx];
			testInfos[idx] = NULL;
		}
	}
	//�رմ���
	CloseSerialPort();
	//ǿ�ƹر��߳�
	DWORD exit_code = NULL;
	if (m_hSendThread != NULL)
	{
		GetExitCodeThread(m_hSendThread->m_hThread, &exit_code);
		if (exit_code == STILL_ACTIVE)
		{
			::TerminateThread(m_hSendThread->m_hThread, 0);
			CloseHandle(m_hSendThread->m_hThread);
		}
		m_hSendThread->m_hThread = NULL;
		m_hSendThread = NULL;
	}

	PortOpenFlag = FALSE;
	CanConnFlag = FALSE;

	if (pConnection&&pConnection->State)
	{
		pConnection->Close();
		pConnection = NULL;
		::OleUninitialize();	//һ��Ҫ�ͷ���Դ�� 
	}

	curCabId = 0;
}

void CBatteryMainView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PRE_DATA_STATIC, preDataStatic);
	DDX_Control(pDX, IDC_SET_INFO_STATIC, setInfoStatic);
	DDX_Control(pDX, IDC_SHOW_STYLE_STATIC, showStyleStatic);
	DDX_Control(pDX, IDC_LEFT_MOUSE_STATIC, leftMouseStatic);
	DDX_Control(pDX, IDC_SPEC_CTL_STATIC, specCtlStatic);
	DDX_Control(pDX, IDC_BATTERYS_PANE, batterysPanePic);
	DDX_Control(pDX, IDC_CAB_LINK1, cabLink1);
	DDX_Control(pDX, IDC_CAB_LINK2, cabLink2);
	DDX_Control(pDX, IDC_CAB_LINK3, cabLink3);
	DDX_Control(pDX, IDC_CAB_LINK4, cabLink4);
	DDX_Control(pDX, IDC_CAB_LINK5, cabLink5);
	DDX_Control(pDX, IDC_CAB_LINK6, cabLink6);
	DDX_Control(pDX, IDC_CAB_LINK7, cabLink7);
	DDX_Control(pDX, IDC_CAB_LINK8, cabLink8);
	DDX_Control(pDX, IDC_CAB_LINK9, cabLink9);
	DDX_Control(pDX, IDC_CAB_LINK10, cabLink10);
	DDX_Control(pDX, IDC_CAB_LINK11, cabLink11);
	DDX_Control(pDX, IDC_CAB_LINK12, cabLink12);
	DDX_Control(pDX, IDC_CAB_LINK13, cabLink13);
	DDX_Control(pDX, IDC_CAB_LINK14, cabLink14);
	DDX_Control(pDX, IDC_CAB_LINK15, cabLink15);
	DDX_Control(pDX, IDC_CAB_LINK16, cabLink16);
	DDX_Control(pDX, IDC_CAB_LINK17, cabLink17);
	DDX_Control(pDX, IDC_CAB_LINK18, cabLink18);
	DDX_Control(pDX, IDC_CAB_LINK19, cabLink19);
	DDX_Control(pDX, IDC_CAB_LINK20, cabLink20);

	//	DDX_Control(pDX, IDC_CAB_SEL, cabSel);

	DDX_Control(pDX, IDC_PANE_ID, paneIdLink);
	DDX_Control(pDX, IDC_MSCOMM1, m_ctrlComm);
	DDX_Text(pDX, IDC_EDIT_testRXDATA, m_strEditReceiveMsg);//for test
	DDX_Control(pDX, IDC_PARA_COM, paraCom);
	DDX_Control(pDX, IDC_CAB_SEL, cabSel);
	DDX_Control(pDX, IDC_EDIT_RECV_DATA, recvDataEdit);
	DDX_Control(pDX, IDC_WORK_STATE_DESC, workStateDescStatic);
}

BEGIN_MESSAGE_MAP(CBatteryMainView, CFormView)
	ON_NOTIFY(NM_CLICK, IDC_SET_INFO_STATIC, &CBatteryMainView::OnNMClickSetInfoStatic)
	ON_NOTIFY(NM_CLICK, IDC_PRE_DATA_STATIC, &CBatteryMainView::OnNMClickPreDataStatic)
	ON_NOTIFY(NM_CLICK, IDC_SHOW_STYLE_STATIC, &CBatteryMainView::OnNMClickShowStyleStatic)
	ON_NOTIFY(NM_CLICK, IDC_LEFT_MOUSE_STATIC, &CBatteryMainView::OnNMClickLeftMouseStatic)
	ON_NOTIFY(NM_CLICK, IDC_SPEC_CTL_STATIC, &CBatteryMainView::OnNMClickSpecCtlStatic)
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_MOUSEHOVER()
	ON_NOTIFY(NM_RCLICK, IDC_SHOW_STYLE_STATIC, &CBatteryMainView::OnNMRClickShowStyleStatic)
	ON_NOTIFY(NM_RCLICK, IDC_LEFT_MOUSE_STATIC, &CBatteryMainView::OnNMRClickLeftMouseStatic)
	ON_NOTIFY(NM_RCLICK, IDC_SPEC_CTL_STATIC, &CBatteryMainView::OnNMRClickSpecCtlStatic)
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_BATTERY_SELECT, &CBatteryMainView::OnBatterySelect)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_NOTIFY(NM_CLICK, IDC_CAB_LINK1, &CBatteryMainView::OnNMClickCabLink1)
	ON_NOTIFY(NM_CLICK, IDC_CAB_LINK2, &CBatteryMainView::OnNMClickCabLink2)
	ON_NOTIFY(NM_CLICK, IDC_CAB_LINK3, &CBatteryMainView::OnNMClickCabLink3)
	ON_NOTIFY(NM_CLICK, IDC_CAB_LINK4, &CBatteryMainView::OnNMClickCabLink4)
	ON_NOTIFY(NM_CLICK, IDC_CAB_LINK5, &CBatteryMainView::OnNMClickCabLink5)
	ON_NOTIFY(NM_CLICK, IDC_CAB_LINK6, &CBatteryMainView::OnNMClickCabLink6)
	ON_NOTIFY(NM_CLICK, IDC_CAB_LINK7, &CBatteryMainView::OnNMClickCabLink7)
	ON_NOTIFY(NM_CLICK, IDC_CAB_LINK8, &CBatteryMainView::OnNMClickCabLink8)
	ON_NOTIFY(NM_CLICK, IDC_CAB_LINK9, &CBatteryMainView::OnNMClickCabLink9)
	ON_NOTIFY(NM_CLICK, IDC_CAB_LINK10, &CBatteryMainView::OnNMClickCabLink10)
	ON_NOTIFY(NM_CLICK, IDC_CAB_LINK11, &CBatteryMainView::OnNMClickCabLink11)
	ON_NOTIFY(NM_CLICK, IDC_CAB_LINK12, &CBatteryMainView::OnNMClickCabLink12)
	ON_NOTIFY(NM_CLICK, IDC_CAB_LINK13, &CBatteryMainView::OnNMClickCabLink13)
	ON_NOTIFY(NM_CLICK, IDC_CAB_LINK14, &CBatteryMainView::OnNMClickCabLink14)
	ON_NOTIFY(NM_CLICK, IDC_CAB_LINK15, &CBatteryMainView::OnNMClickCabLink15)
	ON_NOTIFY(NM_CLICK, IDC_CAB_LINK16, &CBatteryMainView::OnNMClickCabLink16)
	ON_NOTIFY(NM_CLICK, IDC_CAB_LINK17, &CBatteryMainView::OnNMClickCabLink17)
	ON_NOTIFY(NM_CLICK, IDC_CAB_LINK18, &CBatteryMainView::OnNMClickCabLink18)
	ON_NOTIFY(NM_CLICK, IDC_CAB_LINK19, &CBatteryMainView::OnNMClickCabLink19)
	ON_NOTIFY(NM_CLICK, IDC_CAB_LINK20, &CBatteryMainView::OnNMClickCabLink20)
	ON_NOTIFY(NM_CLICK, IDC_PANE_ID, &CBatteryMainView::OnNMClickPaneId)
	ON_CBN_SELCHANGE(IDC_PARA_COM, &CBatteryMainView::OnCbnSelchangeParaCom)
	ON_COMMAND(ID_BAT_PIC_STYLE, &CBatteryMainView::OnBatPicStyle)
	ON_COMMAND(ID_BAT_TABLE_STYLE, &CBatteryMainView::OnBatTableStyle)
	ON_COMMAND(ID_BAT_COMP_STYLE, &CBatteryMainView::OnBatCompStyle)
	ON_COMMAND(ID_EXCP_SHOW, &CBatteryMainView::OnExcpShow)
	ON_WM_INPUT_DEVICE_CHANGE()
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CBatteryCheckView ���

#ifdef _DEBUG
void CBatteryMainView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CBatteryMainView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

// CBatteryCheckView ��Ϣ�������

void CBatteryMainView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	
	InitCabLinks();
	if (defCabId > 0)
	{
		CString tmp;
		cabLinks[defCabId - 1]->GetWindowTextW(tmp);
		//cabLinks[defCabId - 1]->SetWindowText(_T("��") + tmp);
	}
	//(0) ��ʼ���˵���

	batShowMenu.LoadMenuW(IDR_BATTERY_SHOW_STYLE);

	//(1) ʵʱ��ȡ��syslink��λ��
	for (int idx = 0; idx < links.size(); ++idx)
	{
		links[idx]->GetWindowRect(&rects[idx]);
		ScreenToClient(&rects[idx]);
	}
	//(2)  ��ʼ��Combox
	paraCom.SetCurSel(VOLT_SEL);
	STATE_SEL_CODE = VOLT_SEL;

	ConnectToDatabase();
	cabinetInfo = GetCabInfoByCurId();

	this->GetDlgItem(IDC_CAB_ID)->SetWindowTextW(_T("����")+ defCabIdStr);
	this->GetDlgItem(IDC_MODEL_STATIC)->SetWindowTextW(_T("��λ���ͺţ�") + cabinetInfo.deviceName);


	if (cabinetInfo.colShowNum == 1)
	{
		paneIdLink.ShowWindow(SW_HIDE);
	}

	LoadBatteryDlg();
	//CreateDatabases();										// ����ʱ����ϵͳ���ô������ݿ�,�����������
	commConf = CommConf::GetInstance();

	PortOpenFlag = FALSE;
	CanConnFlag = FALSE;
	InitilizeConsoleDevice();
	//PortOpenFlag = InitSerialPort(5);
	m_hSendThread = ::AfxBeginThread(SendThread, this);


	return;  // return TRUE unless you set the focus to a control
}

void CBatteryMainView::InitCabLinks()
{
	cabInitPath = CBatteryUtils::GetConfigPath(_T("\\config\\init\\cabinet.ini"));

	wchar_t str[MAX_PATH_LENGTH];

	GetPrivateProfileString(_T("cabs"), _T("cabSels"), _T("0"), str, MAX_PATH_LENGTH,
		cabInitPath);

	for (int idx = 0; idx < MAX_CAB_NUM; ++idx)
	{
		cabLinks[idx]->ShowWindow(str[idx] == '1' ? SW_NORMAL : SW_HIDE);
	}
	str[MAX_CAB_NUM] = '\0';

	CRect rect;
	cabLink1.GetWindowRect(rect);
	ScreenToClient(rect);
	CRect rect1;
	for (int idx = 0; idx < cabLinks.size(); ++idx)
	{
		if (idx >= 1)
		{
			rect.top += 20;
			rect.bottom += 20;
			cabLinks[idx]->MoveWindow(rect, true);
		}

		rect1 = rect;
		rect1.left -= 18;
		rect1.right = rect1.left + 16;
		rect1.top -= 2;
		rect1.bottom = rect1.top + 16;

		cabRects.push_back(rect1);
	}
	
	cabSel.SetBitmap(theApp.selBmp);
	cabSel.MoveWindow(cabRects[defCabId - 1], TRUE);
}

void CBatteryMainView::OnNMClickSetInfoStatic(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	if (deviceSetInfoDlg == NULL)
	{
		deviceSetInfoDlg = new CDeviceSetInfoDlg();
	}
	deviceSetInfoDlg->DoModal();
}


void CBatteryMainView::OnNMClickPreDataStatic(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CBatteryMainView::OnNMClickShowStyleStatic(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
		
	batShowSubMenu = batShowMenu.GetSubMenu(0);

	InitBatShowMenu();
	CRect rect;
	showStyleStatic.GetWindowRect(&rect);
	batShowSubMenu->TrackPopupMenu(TPM_LEFTALIGN, rect.left + rect.Width(), rect.top, this);

}


void CBatteryMainView::OnNMClickLeftMouseStatic(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	CMenu menu;
	CMenu *pSubMenu;
	menu.LoadMenuW(IDR_LEFT_MOUSE_MENU);
	pSubMenu = menu.GetSubMenu(0);
	CRect rect;
	leftMouseStatic.GetWindowRect(&rect);
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN, rect.left + rect.Width(), rect.top, this);
}


void CBatteryMainView::OnNMClickSpecCtlStatic(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	CMenu menu;

	menu.LoadMenuW(IDR_SPEC_CONTROL_MENU);
	batShowSubMenu = menu.GetSubMenu(0);
	CRect rect;
	leftMouseStatic.GetWindowRect(&rect);
	batShowSubMenu->TrackPopupMenu(TPM_LEFTALIGN, rect.left + rect.Width(), rect.top, this);
}


void CBatteryMainView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int idx;
	CString str;
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
	CFormView::OnMouseMove(nFlags, point);
}

void CBatteryMainView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	CRect dlgRect;
	this->GetClientRect(dlgRect);

	if (batterysPanePic.m_hWnd) {
		batterysPanePic.MoveWindow(MARGIN_LEFT_BATPANE, MARGIN_TOP_BATPANE, dlgRect.Width(), dlgRect.Height(), TRUE);
		if (pbatterysDlgs[curCabId-1] != NULL)
			pbatterysDlgs[curCabId - 1]->OnSize(0, dlgRect.Width() - MARGIN_LEFT_BATPANE, dlgRect.Height() - MARGIN_TOP_BATPANE);
		if (tbatterysDlgs[curCabId - 1] != NULL)
			tbatterysDlgs[curCabId - 1]->OnSize(0, dlgRect.Width() - MARGIN_LEFT_BATPANE, dlgRect.Height() - MARGIN_TOP_BATPANE);
		if (cbatterysDlgs[curCabId - 1] != NULL)
			cbatterysDlgs[curCabId - 1]->OnSize(0, dlgRect.Width() - MARGIN_LEFT_BATPANE, dlgRect.Height() - MARGIN_TOP_BATPANE);
		if (ebatterysDlgs[curCabId - 1] != NULL)
			pbatterysDlgs[curCabId - 1]->OnSize(0, dlgRect.Width() - MARGIN_LEFT_BATPANE, dlgRect.Height() - MARGIN_TOP_BATPANE);
	}
}


void CBatteryMainView::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	lpMMI->ptMinTrackSize.x = MIN_FRAME_WIDTH;

	lpMMI->ptMinTrackSize.y = MIN_FRAME_HEIGHT;

	CFormView::OnGetMinMaxInfo(lpMMI);
}


void CBatteryMainView::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect batPaneRect;
	batterysPanePic.GetClientRect(&batPaneRect);
	ScreenToClient(batPaneRect);

	CFormView::OnMouseHover(nFlags, point);
}


void CBatteryMainView::OnNMRClickShowStyleStatic(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CMenu   menu;   //��������Ҫ�õ���cmenu����
	menu.LoadMenu(IDR_BATTERY_SHOW_STYLE); //װ���Զ�����Ҽ��˵� 
	CMenu   *pContextMenu = menu.GetSubMenu(0); //��ȡ��һ�������˵������Ե�һ���˵��������Ӳ˵� 



	CPoint point;//����һ������ȷ�����λ�õ�λ��  
	GetCursorPos(&point);//��ȡ��ǰ����λ�ã��Ա�ʹ�ò˵����Ը�����  
	pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd()); //��ָ��λ����ʾ�����˵�

	*pResult = 0;
}


void CBatteryMainView::OnNMRClickLeftMouseStatic(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CBatteryMainView::OnNMRClickSpecCtlStatic(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CBatteryMainView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CFormView::OnRButtonUp(nFlags, point);


}


void CBatteryMainView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CFormView::OnRButtonDown(nFlags, point);

	int b = 0;
}


void CBatteryMainView::OnBatterySelect()
{
	// TODO:  �ڴ���������������
}


void CBatteryMainView::OnMove(int x, int y)
{
	CFormView::OnMove(x, y);
	int a = 0;
	// TODO:  �ڴ˴������Ϣ����������
}


void CBatteryMainView::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CFormView::OnWindowPosChanging(lpwndpos);
	//int a = 0;
	this->UpdateWindow();
	//CView *view = NULL;
	//CDocument *doc = ((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveDocument();

	//view = ((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveView();
	//
	//if (view != NULL)
	//{
	//	this->UpdateWindow();
	//	//view->UpdateData(TRUE);
	//	//view->UpdateWindow();
	//}
	// TODO:  �ڴ˴������Ϣ����������
}


BOOL CBatteryMainView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//return TRUE;
	return CFormView::OnEraseBkgnd(pDC);
}


void CBatteryMainView::OnPaint()
{
	CDC *cdc = GetDC();
	//DrawIcon(cdc->GetSafeHdc(), 0, 0, selIcon);
	cdc->DrawIcon(0, 0, selIcon);
	CPaintDC dc(this); // device context for painting
	paintFlag = TRUE;
	maxminFlag = FALSE;	// �����ٽ��������ΪFALSE
	////dc.SetBkColor();
	//CRect rect;
	//GetClientRect(&rect);
	//CDC *pdc = GetDC();
	//bmp.CreateCompatibleBitmap(pdc, rect.Width(), rect.Height());
	////bmp.LoadBitmap(IDB_MAINBMP);//�ϴ�λͼ������Ҫ�޸�Ϊ�ı���ͼ��
	//
	//memDC.CreateCompatibleDC(pdc);
	//memDC.SelectObject(&bmp);
	////��ȡ���ڵĴ�С 
	//BITMAP bmInfo;
	//bmp.GetBitmap(&bmInfo);
	//int width = bmInfo.bmWidth;
	//int heigth = bmInfo.bmHeight;
	//CRect rc;
	//GetClientRect(rc);
	//pdc->SetStretchBltMode(COLORONCOLOR);
	//pdc->StretchBlt(0, 0, rc.Width(), rc.Height(), &memDC, 0, 0, width, heigth, SRCCOPY);
	////��ͼ��ɺ������
	//memDC.DeleteDC();
	//bmp.DeleteObject();
}


BOOL CBatteryMainView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ����ר�ô����/����û���
	//cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	return CFormView::PreCreateWindow(cs);
}


int CBatteryMainView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	//ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}

void CBatteryMainView::OnNMClickCabLink1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	SelSpecCabLink(1, cabLink1);
	LoadBatteryDlg();
}


void CBatteryMainView::OnNMClickCabLink2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	
	SelSpecCabLink(2, cabLink2);
	LoadBatteryDlg();
}


void CBatteryMainView::OnNMClickCabLink3(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	
	SelSpecCabLink(3, cabLink3);
	LoadBatteryDlg();
}


void CBatteryMainView::OnNMClickCabLink4(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	
	SelSpecCabLink(4, cabLink4);
	LoadBatteryDlg();
}


void CBatteryMainView::OnNMClickCabLink5(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	
	SelSpecCabLink(5, cabLink5);
	LoadBatteryDlg();
}


void CBatteryMainView::OnNMClickCabLink6(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	
	SelSpecCabLink(6, cabLink6);
	LoadBatteryDlg();
}


void CBatteryMainView::OnNMClickCabLink7(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	
	SelSpecCabLink(7, cabLink7);
	LoadBatteryDlg();
}


void CBatteryMainView::OnNMClickCabLink8(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	
	SelSpecCabLink(8, cabLink8);
	LoadBatteryDlg();
}


void CBatteryMainView::OnNMClickCabLink9(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	
	SelSpecCabLink(9, cabLink9);
	LoadBatteryDlg();
}


void CBatteryMainView::OnNMClickCabLink10(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	
	SelSpecCabLink(10, cabLink10);
	LoadBatteryDlg();
}


void CBatteryMainView::OnNMClickCabLink11(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	
	SelSpecCabLink(11, cabLink11);
	LoadBatteryDlg();
}


void CBatteryMainView::OnNMClickCabLink12(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	
	SelSpecCabLink(12, cabLink12);
	LoadBatteryDlg();
}


void CBatteryMainView::OnNMClickCabLink13(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	
	SelSpecCabLink(13, cabLink13);
	LoadBatteryDlg();
}


void CBatteryMainView::OnNMClickCabLink14(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	
	SelSpecCabLink(14, cabLink14);
	LoadBatteryDlg();
}


void CBatteryMainView::OnNMClickCabLink15(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	
	SelSpecCabLink(15, cabLink15);
	LoadBatteryDlg();
}


void CBatteryMainView::OnNMClickCabLink16(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	
	SelSpecCabLink(16, cabLink16);
	LoadBatteryDlg();
}


void CBatteryMainView::OnNMClickCabLink17(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	
	SelSpecCabLink(17, cabLink17);
	LoadBatteryDlg();
}


void CBatteryMainView::OnNMClickCabLink18(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	
	SelSpecCabLink(18, cabLink18);
	LoadBatteryDlg();
}


void CBatteryMainView::OnNMClickCabLink19(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	SelSpecCabLink(19, cabLink19);
	LoadBatteryDlg();
}



void CBatteryMainView::OnNMClickCabLink20(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	SelSpecCabLink(20, cabLink20);
	LoadBatteryDlg();
}

void CBatteryMainView::SelSpecCabLink(int cabId, CLinkCtrl &cabLink)
{
	curCabId = cabId;
	CString txt, txt2, cabIdStr;

	
	//for (int idx = 0; idx < cabLinks.size(); ++idx)
	//{
	//	cabLinks[idx]->GetWindowText(txt);
	//	if (txt.Find(_T("��")) >= 0)
	//	{
	//		txt2 = txt.Right(txt.GetLength() - 1);
	//		cabLinks[idx]->SetWindowTextW(txt2);
	//	}
	//}
	//cabLink.GetWindowText(txt);
	//cabLink.SetWindowTextW(_T("��") + txt);
	//cabIdStr.Format(_T("%d"), cabId);
	
	cabSel.MoveWindow(cabRects[cabId - 1], TRUE);
	cabinetInfo = GetCabInfoByCurId();

	this->GetDlgItem(IDC_CAB_ID)->SetWindowTextW(_T("����") + cabIdStr);
	this->GetDlgItem(IDC_MODEL_STATIC)->SetWindowTextW(_T("��λ���ͺţ�") + cabinetInfo.deviceName);

	if (cabinetInfo.colShowNum == 1) {
		paneIdLink.ShowWindow(SW_HIDE);
	}
	else
	{
		paneIdLink.ShowWindow(SW_NORMAL);
	}

}

void CBatteryMainView::LoadBatteryDlg()
{
	if (cabinetInfo.colShowNum == 1)
	{
		paneIdLink.SetWindowTextW(_T(FRONT_PANE));
	}

	////(2) ����ذ�
	//if (pbatterysDlg && pbatterysDlg->m_hWnd)
	//{
	//	delete pbatterysDlg;
	//	pbatterysDlg = NULL;
	//}
	

	CRect dlgRect;
	this->GetClientRect(dlgRect);

	if (batterysPanePic.m_hWnd) {
		batterysPanePic.MoveWindow(MARGIN_LEFT_BATPANE, MARGIN_TOP_BATPANE, dlgRect.Width(), dlgRect.Height(), TRUE);
		switch (BatShowStyle)
		{
		case PIC_STYLE:
		{
			if (pbatterysDlgs[curCabId-1] == NULL)
			{
				for (int idx = 0; idx < MAX_CAB_NUM; ++ idx)
				{
					if (pbatterysDlgs[idx] != NULL)
					{
						pbatterysDlgs[idx]->DestroyWindow();
						delete pbatterysDlgs[idx];
						pbatterysDlgs[idx] = NULL;
					}
				}
				pbatterysDlgs[curCabId - 1] = new CPbatterysDlg();
				pbatterysDlgs[curCabId - 1]->Create(IDD_PBATTERYS_DLG, this);
			}
			
			pbatterysDlgs[curCabId - 1]->OnSize(0, dlgRect.Width() - MARGIN_LEFT_BATPANE, dlgRect.Height() - MARGIN_TOP_BATPANE);
			pbatterysDlgs[curCabId - 1]->OnPaint();
			break;
		}
		case TABLE_STYLE:
		{
			if (tbatterysDlgs[curCabId - 1] == NULL)
			{
				for (int idx = 0; idx < MAX_CAB_NUM; ++idx)
				{
					if (tbatterysDlgs[idx] != NULL)
					{
						tbatterysDlgs[idx]->DestroyWindow();
						delete tbatterysDlgs[idx];
						tbatterysDlgs[idx] = NULL;
					}
				}
				tbatterysDlgs[curCabId - 1] = new CTbatterysDlg();
				tbatterysDlgs[curCabId - 1]->Create(IDD_TBATTERYS_DLG, this);
			}
			tbatterysDlgs[curCabId - 1]->OnSize(0, dlgRect.Width() - MARGIN_LEFT_BATPANE, dlgRect.Height() - MARGIN_TOP_BATPANE);
			//tbatterysDlgs[curCabId - 1]->OnPaint();
			break;
		}
		case COMP_STYLE:
		{
			if (cbatterysDlgs[curCabId - 1] == NULL)
			{
				for (int idx = 0; idx < MAX_CAB_NUM; ++idx)
				{
					if (cbatterysDlgs[idx] != NULL)
					{
						cbatterysDlgs[idx]->DestroyWindow();
						delete cbatterysDlgs[idx];
						cbatterysDlgs[idx] = NULL;
					}
				}
				cbatterysDlgs[curCabId - 1] = new CbatterysDlg();
				cbatterysDlgs[curCabId - 1]->Create(IDD_CBATTERYS_DLG, this);
			}
			cbatterysDlgs[curCabId - 1]->OnSize(0, dlgRect.Width() - MARGIN_LEFT_BATPANE, dlgRect.Height() - MARGIN_TOP_BATPANE);
			//cbatterysDlgs[curCabId - 1]->OnPaint();
			break;
		}
		case EXCEP_STYLE:
		{
			if (ebatterysDlgs[curCabId - 1] == NULL)
			{
				for (int idx = 0; idx < MAX_CAB_NUM; ++idx)
				{
					if (ebatterysDlgs[idx] != NULL)
					{
						ebatterysDlgs[idx]->DestroyWindow();
						delete ebatterysDlgs[idx];
						ebatterysDlgs[idx] = NULL;
					}
				}
				ebatterysDlgs[curCabId - 1] = new CEbatterysDlg();
				ebatterysDlgs[curCabId - 1]->Create(IDD_EBATTERYS_DLG, this);
			}
			ebatterysDlgs[curCabId - 1]->OnSize(0, dlgRect.Width() - MARGIN_LEFT_BATPANE, dlgRect.Height() - MARGIN_TOP_BATPANE);
			//ebatterysDlgs[curCabId - 1]->OnPaint();
			break;
		}
		default:
			break;
		}
	}
}

void CBatteryMainView::ConnectToDatabase()
{
	// (1) ��ȡDB�ľ���·��
	dbConfigPath = CBatteryUtils::GetConfigPath(_T("\\config\\init\\cabinet.ini"));
	wchar_t str[MAX_PATH_LENGTH];
	GetPrivateProfileString(_T("dbpath"), _T("dbpath"), _T("D:\\BatteryManage.mdb"), str, MAX_PATH_LENGTH, dbConfigPath);

	CString dbPath = CBatteryUtils::GetConfigPath(str);
	_bstr_t sqlStr = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" +
		(_bstr_t)dbPath;
	try
	{
		//�ȴ�������ʵ��
		hr = pConnection.CreateInstance(__uuidof(Connection));//����Connection����
		if (SUCCEEDED(hr))
		{
			// �򿪱���Access��Demo.mdb
			hr = pConnection->Open(sqlStr, "", "", adModeUnknown);
		}
	}
	catch (_com_error e)///��׽�쳣
	{
		CString strMsg;
		strMsg.Format(_T("����������%s\n������Ϣ%s"),
			(LPCTSTR)e.Description(),
			(LPCTSTR)e.ErrorMessage());
		AfxMessageBox(strMsg);
	}
}

CabinetInfo CBatteryMainView::GetResultSetCabInfo()
{
	_variant_t var;
	CabinetInfo cabinetInfo;

	var = pRecordset->GetCollect(_T("ADIS"));
	if (var.vt != VT_NULL)
		cabinetInfo.adis = int(var);

	var = pRecordset->GetCollect(_T("ADIS_VAL"));
	cabinetInfo.adisVal = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("CABINET_ID"));
	cabinetInfo.cabinetId = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("COL_SHOWNUM"));
	cabinetInfo.colShowNum = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("CONST_VCHG"));
	cabinetInfo.constVchg = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("CONST_AMAX"));
	cabinetInfo.constAmax = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("CONST_AMIN"));
	cabinetInfo.constAmin = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("CONST_VMAX"));
	cabinetInfo.constVmax = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("CONST_VMIN"));
	cabinetInfo.constVmin = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("DEVICE_ID"));
	cabinetInfo.deviceId = var.vt != NULL ? (LPCTSTR)_bstr_t(var) : _T("");

	var = pRecordset->GetCollect(_T("DEVICE_NAME"));
	cabinetInfo.deviceName = var.vt != NULL ? (LPCTSTR)_bstr_t(var) : _T("");

	var = pRecordset->GetCollect(_T("GROUPNUM_PERCOL"));
	cabinetInfo.groupNumPerCol = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("NUM_PERGROUP"));
	cabinetInfo.numPerGroup = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("COL_SHOWNUM"));
	cabinetInfo.colShowNum = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("OM_TEST"));
	cabinetInfo.omTest = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("SASHOW_MAX"));
	cabinetInfo.sashowMax = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("SASHOW_MIN"));
	cabinetInfo.sashowMin = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("SAVETO_FILE"));
	cabinetInfo.saveToFile = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("SRSHOW_MAX"));
	cabinetInfo.srshowMax = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("SRSHOW_MIN"));
	cabinetInfo.srshowMin = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("SVSHOW_MAX"));
	cabinetInfo.svshowMax = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("SVSHOW_MIN"));
	cabinetInfo.svshowMin = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("TIMEDIS"));
	cabinetInfo.timeDis = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("TIMEDIS_VAL"));
	cabinetInfo.timeDisVal = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("VDIS"));
	cabinetInfo.vdis = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("VDIS_VAL"));
	cabinetInfo.vdisVal = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("VSHOW_MAX"));
	cabinetInfo.vshowMax = var.vt != NULL ? int(var) : 0;

	var = pRecordset->GetCollect(_T("VSHOW_MIN"));
	cabinetInfo.vshowMin = var.vt != NULL ? int(var) : 0;

	return cabinetInfo;
}

CabinetInfo CBatteryMainView::GetCabInfoByCurId()
{
	curCabId = curCabId == INVALIDE_CABID ? defCabId : curCabId;

	pRecordset.CreateInstance(__uuidof(Recordset));
	CString querySql;
	querySql.Format(_T("select * from CABINET_INFO where CABINET_ID = %d"), curCabId);
	CabinetInfo cabinetInfo;
	try
	{
		pRecordset->Open(variant_t(querySql),// ��ѯDemoTable���������ֶ�
			pConnection.GetInterfacePtr(),			// ��ȡ�����ӵ�IDispatchָ��
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch (_com_error * e)
	{
		CString errormessage;
		errormessage.Format(_T("������Ϣ:%s", e->ErrorMessage()));
		AfxMessageBox(errormessage);
	}

	try
	{
		if (!pRecordset->ADOBOF)//�����ʱ��¼��ָ��ָ��Ĳ��ǵ�һ����¼
		{
			pRecordset->MoveFirst();//ָ���һ����¼
		}

		//�����û�м�¼�� Recordset ����BOF �� EOF ���Խ�����Ϊ True���� Recordset ����� RecordCount ��������Ϊ�㡣
		if (pRecordset->ADOBOF && pRecordset->ADOEOF)//������жϼ�¼���Ƿ�Ϊ��!!
		{
			//AfxMessageBox(_T("��������Ϊ��"));
			return cabinetInfo;
		}
		//��ȡ���ݿ��е�����
		int j, i = -1;  //��á����������while����ͻ�ÿ�ζ�����ڵ����λ�á�������

		while (!pRecordset->ADOEOF)
		{
			cabinetInfo = GetResultSetCabInfo();
			break;
		}
	}
	catch (_com_error e)
	{
		CString errormessage;
		errormessage.Format(_T("������Ϣ:%s"), e.ErrorMessage());
		AfxMessageBox(errormessage);
	}
	return cabinetInfo;
}

//void CBatteryMainView::OnNMClickPaneId(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	*pResult = 0;
//
//	if (cabinetInfo.colShowNum == 2) {
//
//	}
//}


BEGIN_EVENTSINK_MAP(CBatteryMainView, CFormView)
	ON_EVENT(CBatteryMainView, IDC_MSCOMM1, 1, CBatteryMainView::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()

BOOL CBatteryMainView::InitSerialPort(int portNum)
{
	//����ע�⣬��Ҫ��ȡ����������ͨ�Ų�������
	//��������ֻ���̲߳���
	try
	{
		m_ctrlComm.put_CommPort(portNum);//ѡ�񴮿ں�(������Ϊ�б����������Ǵ�0��ʼ������(nSel+1)��Ӧ�Ĳ���������ѡ�Ĵ��ں�)  
		m_ctrlComm.put_PortOpen(TRUE);//�򿪴���
		m_ctrlComm.put_RThreshold(1);//�յ������ֽ�����OnComm�¼�   
		m_ctrlComm.put_InputMode(1);//����ģʽѡΪ������   
		m_ctrlComm.put_Settings(_T("57600,n,8,1"));//���ô��ڲ����������ʣ�����żУ�飬λֹͣλ��λ����λ  
		//m_ctrlComm.put_Settings(_T("57600,n,8,1"));
		m_ctrlComm.put_InputMode(1);  // �Զ����Ʒ�ʽ��ȡ����   
		m_ctrlComm.put_RThreshold(1); //����1��ʾÿ�����ڽ��ջ��������ж��ڻ����1���ַ�ʱ������һ���������ݵ�OnComm�¼�   
		m_ctrlComm.put_RTSEnable(1);
		m_ctrlComm.put_InputLen(0); //���õ�ǰ���������ݳ���Ϊ0   
		m_ctrlComm.get_Input();//��Ԥ���������������������    
	}
	catch (CException* e)
	{
		return FALSE;
	}
	return TRUE;

}

void CBatteryMainView::CloseSerialPort()
{
	if (m_ctrlComm.m_hWnd && m_ctrlComm.get_PortOpen())
		m_ctrlComm.put_PortOpen(FALSE);
}

void CBatteryMainView::OnCommMscomm1()
{
	// TODO:  �ڴ˴������Ϣ����������
	VARIANT variant_inp;   //Variant ��һ��������������ͣ����˶���String���ݼ��û����������⣬���԰����κ���������ݡ�  
	COleSafeArray safearray_inp;
	LONG len, k;
	BYTE rxdata[20480]; //����BYTE���� An 8-bit integer that is not signed.       
	CString strtemp;
	m_strEditReceiveMsg = "";
	
	CString lowerBufInfos = L"";
	int commEventId = m_ctrlComm.get_CommEvent();

	if (commEventId == EV_RXFLAG) //�¼�ֵΪ2��ʾ���ջ����������ַ�       
	{
		////////��������Ը����Լ���ͨ��Э����봦�����   
		lowerBufInfos = L"";
		variant_inp = m_ctrlComm.get_Input();     //��������    
		safearray_inp = variant_inp;              //VARIANT�ͱ���ת��ΪColeSafeArray�ͱ���  
		len = safearray_inp.GetOneDimSize();      //�õ���Ч���ݳ���          
		for (k = 0; k < len; k++)
			safearray_inp.GetElement(&k, rxdata + k);//ת��ΪBYTE������           
		for (k = 0; k < len; k++)                    //������ת��ΪCstring�ͱ���      
		{
			BYTE bt = *(char*)(rxdata + k);//�ַ���
			BYTE high = 0xF0;
			BYTE low = 0x0F;
			int high_idx = 0;
			int low_idx = 0;

			BYTE tmphigh = bt & high;
			for (int i = 0; i < 16; ++i){
				if (tmphigh == ByteHigh[i])
					high_idx = i;
			}

			BYTE tmplow = bt & low;
			for (int i = 0; i < 16; ++i){
				if (tmplow == ByteLow[i])
					low_idx = i;
			}
			strtemp.Format(_T("%c"), BYTE2CHAR[high_idx]); //���ַ�������ʱ����strtemp���   
			lowerBufInfos += strtemp;
			m_strEditReceiveMsg += strtemp;
			
			strtemp.Format(_T("%c"), BYTE2CHAR[low_idx]); //���ַ�������ʱ����strtemp���
			lowerBufInfos += strtemp;
			m_strEditReceiveMsg += strtemp;

			strtemp.Format(_T("%c"), ' ');
		}
		strtemp.Format(_T("\r\n"));
		m_strEditReceiveMsg += strtemp;


		int frontCodePos = lowerBufInfos.Find(FRONT_CODE);

		if (frontCodePos >= 0)
		{

			if (frontCodePos == 0)
			{
				//(1) ����ַ����������ݳ����ַ���,��ȴ�����֮�󲢽�ȡ��Ч����,����ȡ�����Ч���ݴ��ݸ��ַ�������
				lowerInfos = lowerBufInfos;
				HandleLowerInfos();
			}
			else
			{
				//ǰ�����λ�ò��ǵ�һ���ַ�
				lowerInfos.Append(lowerBufInfos);
				// ƴ��֮���������д���, ֱ��������ϻ���ʣ�����
				HandleLowerInfos();
			}
		}
		else
		{
			// ����Ҳ���ǰ���룬�����ƴ��
			lowerInfos.Append(lowerBufInfos);
			// ƴ��֮���������д���, ֱ��������ϻ���ʣ�����
			HandleLowerInfos();
		}

		UpdateData(FALSE); //���±༭������ 
		//recvDataEdit.SetWindowTextW(lowerInfos);
	
	}
	else if (commEventId == EV_TXEMPTY ||commEventId == 4 || commEventId == 5)
	{
		PortOpenFlag = FALSE;
		return;
	}
	else
	{
		return;
	}
}

void UpdateCabStepMsgs(CBatteryMainView * batteryMainView, int cabIdx, vector<CByteArray*> stepByteArrays)
{
	if (batteryMainView->cabStepMsgs.size() == MAX_CAB_NUM)
	{
		for (int j = 0; j < batteryMainView->cabStepMsgs[cabIdx].size(); ++j)
		{
			delete batteryMainView->cabStepMsgs[cabIdx][j];
			batteryMainView->cabStepMsgs[cabIdx][j] = NULL;
		}
		batteryMainView->cabStepMsgs[cabIdx].clear();
		batteryMainView->cabStepMsgs[cabIdx] = stepByteArrays;
	}
	else
	{
		batteryMainView->cabStepMsgs.push_back(stepByteArrays);
	}
}

void CreateWorkProc(CBatteryMainView *batteryMainView)
{
	CString stepConfPath, stepInitPath;
	wchar_t str[MAX_PATH_LENGTH];

	for (int cabIdx = 0; cabIdx < MAX_CAB_NUM; ++cabIdx)
	{
		vector<CByteArray*> stepByteArrays;

		stepByteArrays.clear();
		if (cabSelStr[cabIdx] == '1' && SendStepFlags[cabIdx])
		{
			stepConfPath = CBatteryUtils::GetConfigPath(_T("\\config\\step\\")
				+ cabIdsCstr[cabIdx] + _T("\\preStepPath.ini"));
			GetPrivateProfileString(_T("stepFilePath"), _T("path"), _T("error"), str, MAX_PATH_LENGTH, stepConfPath);
			stepInitPath = str;
			// ���ݹ���txt��������
			if (stepInitPath != _T("error"))
			{
				std::ifstream in(stepInitPath);
				if (in.is_open())
				{
					string line;
					int nRow, nCol;
					// �ļ���һ��Ϊ��������
					// �ڶ���Ϊ�ͺ�
					//�ļ�������Ϊ���������������Ϊ�������
					getline(in, line);
					getline(in, line);
					getline(in, line);
					nRow = std::stoi(line);
					getline(in, line);
					nCol = std::stoi(line);

					for (int i = 1; i < nRow; ++i)
					{
						CString stepIdStr;
						stepIdStr.Format(_T("%d"), i);
						getline(in, line);
						int spaceidx = 0;
						CByteArray *cmdByteArray = new CByteArray();
						StepMsg *stepMsg = NULL;
						for (int j = 1; j < nCol - 1; j++)
						{
							spaceidx = line.find(' ');
							int len = line.length();

							string tmpStr = line.substr(0, spaceidx);
							line = line.substr(spaceidx + 1, len - spaceidx - 1);
							if (j == 1)
							{
								if (tmpStr == SCSA_CHARGE_STR)
								{
									stepMsg = new VaChargeMsg(stepIdStr, line, cabInfos[cabIdx]);
								}
								else if (tmpStr == SA_CHARGE_STR)
								{
									stepMsg = new AchargeMsg(stepIdStr, line, cabInfos[cabIdx]);
								}
								else if (tmpStr == SA_DISCHARGE_STR)
								{
									stepMsg = new AdischargeMsg(stepIdStr, line, cabInfos[cabIdx]);
								}
								else if (tmpStr == LAY_STR)
								{
									stepMsg = new LayMsg(stepIdStr, line, cabInfos[cabIdx]);
								}
								else if (tmpStr == OVER_STR)
								{
									//stepMsg = new OverMsg(stepIdStr, line, cabInfos[cabIdx]);
								}
								else if (tmpStr == LOOP_STR)
								{
									stepMsg = new LoopMsg(stepIdStr, line, cabInfos[cabIdx]);
								}
								if (stepMsg != NULL)
									stepMsg->serialization(*cmdByteArray);
							}
						}
						stepByteArrays.push_back(cmdByteArray);
					}
				}
				UpdateCabStepMsgs(batteryMainView, cabIdx, stepByteArrays);
			}
			else
			{
				UpdateCabStepMsgs(batteryMainView, cabIdx, stepByteArrays);
				break;
			}
		}
		else //if (cabSelStr[cabIdx] == '0' or '1' )
		{
			UpdateCabStepMsgs(batteryMainView, cabIdx, stepByteArrays);
		}
	}
}

void ObtainLowerCabInfos(CBatteryMainView * batteryMainView)
{
	// ������ȡ��λ��������ϢMsgs

		for (int idx = 0; idx < MAX_CAB_NUM; ++idx)
		{
			try
			{
				CByteArray *obtainModelCmd = NULL;
				if (cabSelStr[idx] == '1' && (SendStepFlags[idx] || PreSendStepFlags[idx]))
				{
					obtainModelCmd = new CByteArray();
					ObtainModelMsg obtainModelMsg(cabIdsCstr[idx]);
					obtainModelMsg.serialization(*obtainModelCmd);
					batteryMainView->m_ctrlComm.put_Output(COleVariant(*obtainModelCmd));
					Sleep(100);
				}
				batteryMainView->obtainModelMsgs.push_back(obtainModelCmd);
			}
			catch (CException* e)
			{
				break;
			}
	}
	batteryMainView->obtainModelFlag = TRUE;
	for (int idx = 0; idx < MAX_CAB_NUM; ++idx)
	{
		if (cabSelStr[idx] == '1' && (SendStepFlags[idx] || PreSendStepFlags[idx]))
		{
			batteryMainView->obtainModelFlag = batteryMainView->obtainModelFlag & batteryMainView->obtainModelFlags[idx];
			if (!batteryMainView->obtainModelFlag)
			{
				break;
			}
		}
	}
	return;
}

BOOL SendWorkProc(CBatteryMainView * batteryMainView)
{
	// �ֱ������λ�����͹���
	for (int idx = 0; idx < MAX_CAB_NUM; ++idx)
	{
		int stepLength = (batteryMainView->cabStepMsgs[idx]).size();
		// �������������,����������ѡ�еķ��͹���
		if (stepLength > 0 && SendStepFlags[idx])
		{
			for (int stepIdx = 0; stepIdx < stepLength; ++stepIdx)
			{
				batteryMainView->m_ctrlComm.put_Output(COleVariant(*(batteryMainView->cabStepMsgs[idx][stepIdx])));
				Sleep(100);
			}
		}
	}
	batteryMainView->SendStepFlag = TRUE;
	for (int idx = 0; idx < MAX_CAB_NUM; ++idx)
	{
		int stepLength = (batteryMainView->cabStepMsgs[idx]).size() - 1;
		
		if (stepLength > 0 && SendStepFlags[idx])
		{
			for (int stepIdx = 0; stepIdx < stepLength; ++stepIdx)
			{
				batteryMainView->SendStepFlag = batteryMainView->SendStepFlag & (batteryMainView->cabStepFlags)[idx][stepIdx];
				if (!batteryMainView->SendStepFlag)
					break;
			}
		}
		if (!batteryMainView->SendStepFlag)
		{
			break;
		}
	}
	return batteryMainView->SendStepFlag;
}

BOOL StartLowerCabs(CBatteryMainView * batteryMainView)
{
	for (int cabIdx = 0; cabIdx < MAX_CAB_NUM; ++cabIdx)
	{
		CByteArray *cabConCmd = NULL;
		if (cabSelStr[cabIdx] == '1' && SendStepFlags[cabIdx])
		{
			cabConCmd = new CByteArray();
			CabConMsg cabConMsg(cabIdsCstr[cabIdx]);
			if (PortOpenFlag)
			{
				cabConMsg.serialization(*cabConCmd);
				batteryMainView->m_ctrlComm.put_Output(COleVariant(*cabConCmd));
				Sleep(100);
			}
		}
		batteryMainView->cabConMsgs.push_back(cabConCmd);
	}

	BOOL cabConFlag = TRUE;
	for (int idx = 0; idx < MAX_CAB_NUM; ++idx)
	{
		if (cabSelStr[idx] == '1' && SendStepFlags[idx])
		{
			cabConFlag = cabConFlag & (batteryMainView->cabConFlags)[idx];
			if (!cabConFlag)
			{
				break;
			}
		}
	}
	return cabConFlag;
}

BOOL SaveBatDataToDb(CabBattery *cabBattery)
{
	return TRUE;
}



void ObtainLowerCabBeat(CBatteryMainView * batteryMainView, int cabId)
{
	int lowerCabBeat = 0;
	CByteArray obtainBeatArray;
	CString modelIdStr = L"1";	// ��ʱΪ�˲����趨���ͺű���
	try
	{
		if (PortOpenFlag)
		{
			ObtainBeatMsg obtainBeatMsg(cabIdsCstr[cabId - 1], modelIdStr);
			obtainBeatMsg.serialization(obtainBeatArray);
			batteryMainView->m_ctrlComm.put_Output(COleVariant(obtainBeatArray));
			Sleep(100);
		}
	}
	catch (CException* e)
	{
		//AfxMessageBox(L"�˿��쳣!");
		return;
	}

}

void ObtainBatData(CBatteryMainView * batteryMainView)
{
	CDbUtils *dbUtils = CDbUtils::GetInstance();

	CString groupIdStr;
	while (TRUE)
	{
		//MSG msg;
		//if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		//{
		//	if (msg.message == WM_QUIT)
		//		break;
		//	TranslateMessage(&msg);
		//	DispatchMessage(&msg);
		//}
		for (int idx = 0; idx < MAX_CAB_NUM; ++idx)
		{
			if (cabSelStr[idx] == '1' && (SendStepFlags[idx] || PreSendStepFlags[idx]))
			{
				CabinetInfo cabInfo = cabInfos[idx];
				// ��ȡ������
				batteryMainView->beatStatus[idx] = INVALIDE_BEAT_STATE;
				ObtainLowerCabBeat(batteryMainView, idx + 1);
				
				if (batteryMainView->beatStatus[idx] == INVALIDE_BEAT_STATE)
				{
					batteryMainView->cabLinks[idx]->SetWindowText(L"<a>״̬δ֪</a>");
				}
				else if (batteryMainView->beatStatus[idx] == STANDBY_BEAT_STATE)
				{
					batteryMainView->cabLinks[idx]->SetWindowText(L"<a>������</a>");
				}
				else if (batteryMainView->beatStatus[idx] == WORKING_BEAT_STATE)
				{
					batteryMainView->cabLinks[idx]->SetWindowText(L"<a>������</a>");
				}
				else if (batteryMainView->beatStatus[idx] == WORKED_BEAT_STATE)
				{
					batteryMainView->cabLinks[idx]->SetWindowText(L"<a>�������</a>");
				}
				else if (batteryMainView->beatStatus[idx] == PAUSE_BEAT_STATE)
				{
					batteryMainView->cabLinks[idx]->SetWindowText(L"<a>��ͣ��</a>");
				}

				if (batteryMainView->beatStatus[idx] != WORKING_BEAT_STATE
					&& batteryMainView->beatStatus[idx] != WORKED_BEAT_STATE)
					continue;
				BOOL workStateDescFlag = FALSE;
				if (PortOpenFlag)
					((CMainFrame*)(batteryMainView->GetParent()))->SetMessageText(L"���ڶ�ȡ��" + cabIdsCstr[idx] + "̨������......");
					//for (int groupIdx = 0; groupIdx < 4; ++groupIdx)
					//for (int groupIdx = 0; groupIdx < cabInfo.groupNum; ++groupIdx)
					//{
						try
						{
						if (PortOpenFlag)
						{
							int groupIdx = 1;
							CByteArray obtainBatArray;
							groupIdStr.Format(_T("%d"), groupIdx);
							ObtainBatMsg obtainBatMsg(cabIdsCstr[idx], groupIdStr);
							batteryMainView->OBTAIN_BATDATA_FLAG = TRUE;
							
							obtainBatMsg.serialization(obtainBatArray);
							batteryMainView->m_ctrlComm.put_Output(COleVariant(obtainBatArray));
							Sleep(5000);
							batteryMainView->OBTAIN_BATDATA_FLAG = FALSE;

							// ���ݵ�һ���ؼ����µ�ǰ����Ĺ���״̬��ʾ
							if (!workStateDescFlag) {

								workStateDescFlag = TRUE;
								if (lowerCabs.cabBatterys[idx] == NULL)
									continue;
								// ��ȡ�����������룬ʱ��
								int stepId = lowerCabs.cabBatterys[idx]->stepId;
								int workId = lowerCabs.cabBatterys[idx]->workId; 
								int timeVal = lowerCabs.cabBatterys[idx]->batterys[0].timeVal;
								
								// ������Ӧ�������ַ���
								CString workStateDescStr = L"";
								CString stepIdStr, workStateStr, timeValStr;
								vector<CWorkStep> workSteps = workProcs[idx]->workSteps;
								stepIdStr.Format(_T("%d"), stepId);
								workStateStr = workStateStrs[workId];
								timeValStr.Format(_T("%d"), timeVal);

								//workStateDescStr = stepIdStr + L" �� " + workProc->workProcName 
								//	+ L" �� ����ʱ�䣺 " + timeValStr + L"Min";
								workStateDescStr = stepIdStr + L":" + workSteps[stepId - 1].workStepName
									+ L";";
								CString workStepName = workSteps[stepId - 1].workStepName;
								if (workStepName == "������ѹ���")
								{
									workStateDescStr += L"ʱ��:" + workSteps[stepId-1].workTime;
									
									workStateDescStr += L"Min,������:" + workSteps[stepId - 1].current;
									
									workStateDescStr += L"mA,���޵�ѹ:" + workSteps[stepId - 1].maxVolt;
									
									workStateDescStr += L"mV,��V:" + workSteps[stepId - 1].deltaVolt;
									
									workStateDescStr += L"mV,��ֹ����:" + workSteps[stepId - 1].endCurrent;
									
									workStateDescStr += L"mA,��ֹ����:" + workSteps[stepId-1].endCapacity + L"mAh";
								}
								else if (workStepName == "�������")
								{
									workStateDescStr += L"ʱ��:" + workSteps[stepId - 1].workTime;
									workStateDescStr += L"Min,������:" + workSteps[stepId - 1].current;
									workStateDescStr += L"mA,���޵�ѹ:" + workSteps[stepId - 1].maxVolt;
									workStateDescStr += L"mV,��V:" + workSteps[stepId - 1].deltaVolt;
									workStateDescStr += L"mV,��ֹ����:" + workSteps[stepId - 1].endCapacity + L"mAh";
								}
								else if (workStepName == "�����ŵ�")
								{
									workStateDescStr += L"ʱ��:" + workSteps[stepId - 1].workTime;
									workStateDescStr += L"Min,�ŵ����:" + workSteps[stepId - 1].current;
									workStateDescStr += L"mA,���޵�ѹ:" + workSteps[stepId - 1].minVolt;
									workStateDescStr += L"mV,��ֹ����:" + workSteps[stepId - 1].endCapacity +L"mAh";
								}
								else if (workStepName == "ѭ��")
								{
									workStateDescStr += L"��ʼ����:" + workSteps[stepId - 1].startStep;
									workStateDescStr += L",��ֹ����:" + workSteps[stepId - 1].endStep;
									workStateDescStr += L",ѭ������:" + workSteps[stepId - 1].loopNum;
								}
								else if (workStepName == "����")
								{
									workStateDescStr += L"ʱ��:" + workSteps[stepId - 1].workTime + L"Min";
								}

								// ����batteryMainView���Ͻǵ�Static
								if (workStateDescStr != batteryMainView->workStateDescStrs[idx])
								{
									batteryMainView->workStateDescStrs[idx] = workStateDescStr;
									
									batteryMainView->workStateDescStatic.SetWindowTextW(batteryMainView->workStateDescStrs[curCabId-1]);
								}
							}
						}
						if (IntteruptSendFlag) break;
					}
					catch (CException* e)
					{
						break;
					}
				//}
				// �������ڹ����е�״̬���������ݿ�
				if (batteryMainView->beatStatus[idx] == WORKING_BEAT_STATE)
				{
					dbUtils->SaveBatDataToDb(lowerCabs.cabBatterys[idx]);
				}
			}
			if (IntteruptSendFlag) break;
		}
		if (IntteruptSendFlag) break;
	}
}

/*
(1) �ж��Ƿ���Է��͹���
	1.1 ���������,�������ѵ�ı�״̬��
		1.1.1�жϴ����Ƿ��,���������д������Ӳ���,���ͨ�����Խ�����ѭ��
		1.1.2������ڹر�,�������ѵ����״̬���и���
	1.2 �������,������ѭ��,���͹���,����ÿ�λ���Ĺ�������ǰ������������,ͨ���������Ը���״̬����
*/

//UINT CBatteryMainView::SendThread(LPVOID param)


UINT SendThread(LPVOID param)
{
	CBatteryMainView *batteryMainView = (CBatteryMainView*)param;
	
	batteryMainView->obtainModelMsgs.clear();
	batteryMainView->cabStepMsgs.clear();
	
	for (int cabIdx = 0; cabIdx < MAX_CAB_NUM; ++cabIdx)
	{
		cabDbPaths[cabIdx] = L"";
	}

	while (WorkFlag)
	{
		// ��ֹ��ʱ��ռ���߳�����
		MSG msg;
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//while (!CanConnFlag || !PortOpenFlag)
		//{
		//	// ����˿�δ�����ڸı�״̬��
		//	if (!PortOpenFlag)
		//	{
		//		if (batteryMainView->m_hWnd)
		//		{
		//			((CMainFrame*)(batteryMainView->GetParent()))->SetMessageText(L"�˿�δ��......");
		//			PortOpenFlag = batteryMainView->InitSerialPort(batteryMainView->commConf->commPortVal);
		//		}
		//		
		//	}
		//	// ���ڷ������������в���
		//	else
		//	{
		//		if (batteryMainView->m_hWnd)
		//		{
		//			((CMainFrame*)(batteryMainView->GetParent()))->SetMessageText(L"�˿��Ѵ򿪣���δ���͹���.....");
		//			
		//		}
		//	}
		//	Sleep(500);
		//}
		while (!CanConnFlag)
		{
			
			if (batteryMainView->m_hWnd)
			{
				if (PortOpenFlag)
				{
					((CMainFrame*)(batteryMainView->GetParent()))->SetMessageText(L"�˿��Ѵ򿪣���δ���͹���......");
				}
				else
				{
					((CMainFrame*)(batteryMainView->GetParent()))->SetMessageText(L"�˿�δ��......");
				}

			}
			Sleep(500);
		}
		IntteruptSendFlag = FALSE;
		
		// ���͹���,�ǵø���״̬Ӵ
		BOOL createDbFlag = batteryMainView->CreateDatabases();
		if (!createDbFlag)
		{
			AfxMessageBox(_T("�������ݿ�ʧ�ܣ�"));
			return 0;
		}
		if (IntteruptSendFlag)
			continue;
		
		// ��ȡ��λ����Ϣ
		ObtainLowerCabInfos(batteryMainView);
		if (!batteryMainView->obtainModelFlag)
		{
			AfxMessageBox(_T("��ȡ��λ����Ϣʧ�ܣ�"));
			return 0;
		}
		if (IntteruptSendFlag) continue;

		//1. ���������ļ���������
		CreateWorkProc(batteryMainView);
		SaveDbConfs(batteryMainView);
		/*if (!dbConfFlag)
		{
			AfxMessageBox(_T("���ݿ�������Ϣ����ʧ�ܣ������ԣ�"));
			return 0;
		}*/

		//2. ����������ԵĻ���������Ϣ
		SaveDbTestInfos(batteryMainView);

		if (IntteruptSendFlag) continue;

		// ���͹�������λ��
		SendWorkProc(batteryMainView);

		if (!batteryMainView->SendStepFlag)
		{
			AfxMessageBox(_T("��λ��������Ϣ����ʧ�ܣ�"));
			return 0;
		}
		if (IntteruptSendFlag) continue;
		
		//	������λ��
		BOOL cabConFlag = StartLowerCabs(batteryMainView);
		if (!cabConFlag)
		{
			AfxMessageBox(_T("��λ������ʧ�ܣ�"));
			return 0;
		}
		if (IntteruptSendFlag) continue;
		Sleep(3000);
		((CMainFrame*)(batteryMainView->GetParent()))->SetMessageText(L"�����ɹ�......");

		// �ֻ���ȡ����
		ObtainBatData(batteryMainView);
	}
	return 0;
}


void CBatteryMainView::OnNMClickPaneId(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	paneIdLink.GetWindowText(paneId);

	if (paneId == _T(FRONT_PANE))
		paneId = _T(BACK_PANE);
	else
		paneId = _T(FRONT_PANE);

	paneIdLink.SetWindowText(paneId);

	LoadBatteryDlg();
}

BOOL CBatteryMainView::CreateDatabases()
{
	CDbUtils *dbUtils = CDbUtils::GetInstance();

	if (dbUtils->CreateDatabases(cabSelStr))
		return true;
	return false;

}

// 1 ������ת����vector<Battery> ����
// 2 ���ݲ�ͬ����ʾ״̬(picture/���/����������ʾ)
// ������һ����Ч����
void CBatteryMainView::HandleLowerInfo(CString lowerInfos, int pieceLen)
{

	string str = CW2A(lowerInfos.GetString());
	std::ofstream   outfile;
	outfile.open("logs.txt", ios::out | ios::app);
	outfile << "LowerInofs:" << str << endl;
	outfile.close();

	CString cmdTypeStr = (OBTAIN_BATDATA_FLAG == TRUE ? lowerInfos.Mid(CMDTYPE_POS2, 2) : lowerInfos.Mid(CMDTYPE_POS, 2));

	int cmdType = StringUtils::XStrToInt(cmdTypeStr);
	int length = lowerInfos.GetLength();


	switch (cmdType)
	{
		case OBTAIN_MODEL_CODE:
		{
			lowerCabs.CheckModelInfo(lowerInfos, obtainModelFlags, pieceLen);
			break;
		}
		case CAB_CON_CODE:
		{
			lowerCabs.CheckConInfo(lowerInfos, cabConFlags, pieceLen);
			break;
		}
		case SASC_CHARGE_CODE:
		{
			lowerCabs.CheckSascInfo(lowerInfos, cabStepFlags, pieceLen);
			break;
		}
		case SA_CHARGE_CODE:
		{
			lowerCabs.CheckSaInfo(lowerInfos, cabStepFlags, pieceLen);
			break;
		}
		case SA_DISCHARGE_CODE:
		{
			lowerCabs.CheckSaDisInfo(lowerInfos, cabStepFlags, pieceLen);
			break;
		}
		case LAY_CODE:
		{
			lowerCabs.CheckLayInfo(lowerInfos, cabStepFlags, pieceLen);
			break;
		}
		case LOOP_CODE:
		{
			lowerCabs.CheckLoopInfo(lowerInfos, cabStepFlags, pieceLen);
			break;
		}
		case OBTAIN_BAT_CODE:
		{
			lowerCabs.CreateLowerCabs(lowerInfos);

			break;
		}
		case HEART_BEAT_CODE:
		{
			lowerCabs.CreateLowerCabBeat(lowerInfos, beatStatus);
			break;
		}

	default:
		break;
	}
	//ConvertToBatteryInfos(lowerInfos);
	CRect dlgRect;
	this->GetClientRect(dlgRect);
	if (batterysPanePic.m_hWnd) {
		batterysPanePic.MoveWindow(MARGIN_LEFT_BATPANE, MARGIN_TOP_BATPANE, dlgRect.Width(), dlgRect.Height(), TRUE);
		if (pbatterysDlgs[curCabId - 1] != NULL)	
			pbatterysDlgs[curCabId - 1]->DoPaint();
		if (tbatterysDlgs[curCabId - 1] != NULL)
			tbatterysDlgs[curCabId - 1]->OnSize(0, dlgRect.Width() - MARGIN_LEFT_BATPANE, dlgRect.Height() - MARGIN_TOP_BATPANE);
		if (cbatterysDlgs[curCabId - 1] != NULL)
			cbatterysDlgs[curCabId - 1]->OnSize(0, dlgRect.Width() - MARGIN_LEFT_BATPANE, dlgRect.Height() - MARGIN_TOP_BATPANE);
		if (ebatterysDlgs[curCabId - 1] != NULL)
			ebatterysDlgs[curCabId - 1]->OnSize(0, dlgRect.Width() - MARGIN_LEFT_BATPANE, dlgRect.Height() - MARGIN_TOP_BATPANE);
	}	
}

void CBatteryMainView::ConvertToBatteryInfos(CString lowerInfos)
{
	lowerCabs.CreateLowerCabs(lowerInfos);
}

void CBatteryMainView::OnCbnSelchangeParaCom()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	STATE_SEL_CODE = paraCom.GetCurSel();	// ��ȡ��ǰ����ѡ��״̬
	CRect dlgRect;
	this->GetClientRect(dlgRect);
	if (batterysPanePic.m_hWnd) {
		batterysPanePic.MoveWindow(MARGIN_LEFT_BATPANE, MARGIN_TOP_BATPANE, dlgRect.Width(), dlgRect.Height(), TRUE);
		if (pbatterysDlgs[curCabId - 1] != NULL)
			pbatterysDlgs[curCabId - 1]->OnPaint();
		if (tbatterysDlgs[curCabId - 1] != NULL) {
			tbatterysDlgs[curCabId - 1]->FillTable();
			tbatterysDlgs[curCabId - 1]->OnPaint();
		}
		if (cbatterysDlgs[curCabId - 1] != NULL){
			cbatterysDlgs[curCabId - 1]->FillTable();
			cbatterysDlgs[curCabId - 1]->OnPaint();
		}
		if (ebatterysDlgs[curCabId - 1] != NULL)
			ebatterysDlgs[curCabId - 1]->OnSize(0, dlgRect.Width() - MARGIN_LEFT_BATPANE, dlgRect.Height() - MARGIN_TOP_BATPANE);
	}
}


void CBatteryMainView::OnBatPicStyle()
{
	if (batShowSubMenu != NULL)
	{
		BatShowStyle = PIC_STYLE;
		InitBatShowMenu();
		
		CRect dlgRect;
		this->GetClientRect(dlgRect);
		if (batterysPanePic.m_hWnd) {
			batterysPanePic.MoveWindow(MARGIN_LEFT_BATPANE, MARGIN_TOP_BATPANE, dlgRect.Width(), dlgRect.Height(), TRUE);
			
			if (tbatterysDlgs[curCabId-1] != NULL) { 
				tbatterysDlgs[curCabId - 1]->DestroyWindow();
				delete tbatterysDlgs[curCabId-1];  
				tbatterysDlgs[curCabId-1] = NULL; 
			}

			if (cbatterysDlgs[curCabId-1] != NULL) { 
				cbatterysDlgs[curCabId - 1]->DestroyWindow();
				delete cbatterysDlgs[curCabId-1]; 
				cbatterysDlgs[curCabId-1] = NULL; 
			}

			if (ebatterysDlgs[curCabId-1] != NULL) { 
				ebatterysDlgs[curCabId - 1]->DestroyWindow();
				delete ebatterysDlgs[curCabId-1]; 
				ebatterysDlgs[curCabId-1] = NULL; 
			}

			if (pbatterysDlgs[curCabId-1] == NULL)
			{
				pbatterysDlgs[curCabId-1] = new CPbatterysDlg();
				pbatterysDlgs[curCabId-1]->Create(IDD_PBATTERYS_DLG, this);
			}
			pbatterysDlgs[curCabId-1]->OnSize(0, dlgRect.Width() - MARGIN_LEFT_BATPANE, dlgRect.Height() - MARGIN_TOP_BATPANE);
		}
	}
}


void CBatteryMainView::OnBatTableStyle()
{
	if (batShowSubMenu != NULL)
	{
		BatShowStyle = TABLE_STYLE;
		InitBatShowMenu();

		CRect dlgRect;
		this->GetClientRect(dlgRect);
		if (batterysPanePic.m_hWnd) {
			batterysPanePic.MoveWindow(MARGIN_LEFT_BATPANE, MARGIN_TOP_BATPANE, dlgRect.Width(), dlgRect.Height(), TRUE);

			if (pbatterysDlgs[curCabId-1] != NULL) { 
				pbatterysDlgs[curCabId - 1]->DestroyWindow();
				delete pbatterysDlgs[curCabId-1];  
				pbatterysDlgs[curCabId-1] = NULL; 
			}

			if (cbatterysDlgs[curCabId-1] != NULL) { 
				cbatterysDlgs[curCabId - 1]->DestroyWindow();
				delete cbatterysDlgs[curCabId-1]; 
				cbatterysDlgs[curCabId-1] = NULL; 
			}

			if (ebatterysDlgs[curCabId-1] != NULL) { 
				ebatterysDlgs[curCabId - 1]->DestroyWindow();
				delete ebatterysDlgs[curCabId-1]; 
				ebatterysDlgs[curCabId-1] = NULL; 
			}

			if (tbatterysDlgs[curCabId-1] == NULL)
			{
				tbatterysDlgs[curCabId-1] = new CTbatterysDlg();
				tbatterysDlgs[curCabId-1]->Create(IDD_TBATTERYS_DLG, this);
			}
			tbatterysDlgs[curCabId-1]->OnSize(0, dlgRect.Width() - MARGIN_LEFT_BATPANE, dlgRect.Height() - MARGIN_TOP_BATPANE);
		}

	}
}


void CBatteryMainView::OnBatCompStyle()
{
	if (batShowSubMenu != NULL)
	{
		BatShowStyle = COMP_STYLE;
		InitBatShowMenu();

		CRect dlgRect;
		this->GetClientRect(dlgRect);
		if (batterysPanePic.m_hWnd) {
			batterysPanePic.MoveWindow(MARGIN_LEFT_BATPANE, MARGIN_TOP_BATPANE, dlgRect.Width(), dlgRect.Height(), TRUE);

			if (pbatterysDlgs[curCabId - 1] != NULL) {
				pbatterysDlgs[curCabId - 1]->DestroyWindow();
				delete pbatterysDlgs[curCabId - 1];  pbatterysDlgs[curCabId - 1] = NULL;
			}
			if (tbatterysDlgs[curCabId - 1] != NULL) { 
				tbatterysDlgs[curCabId - 1]->DestroyWindow();
				delete tbatterysDlgs[curCabId - 1];  
				tbatterysDlgs[curCabId - 1] = NULL; 
			}

			if (ebatterysDlgs[curCabId - 1] != NULL) { 
				ebatterysDlgs[curCabId - 1]->DestroyWindow();
				delete ebatterysDlgs[curCabId - 1];  
				ebatterysDlgs[curCabId - 1] = NULL; 
			}

			if (cbatterysDlgs[curCabId-1] == NULL)
			{
				cbatterysDlgs[curCabId - 1] = new CbatterysDlg();
				cbatterysDlgs[curCabId - 1]->Create(IDD_CBATTERYS_DLG, this);
			}
			cbatterysDlgs[curCabId - 1]->OnSize(0, dlgRect.Width() - MARGIN_LEFT_BATPANE, dlgRect.Height() - MARGIN_TOP_BATPANE);
		}

	}
}


void CBatteryMainView::OnExcpShow()
{
	if (batShowSubMenu != NULL)
	{
		BatShowStyle = EXCEP_STYLE;
		InitBatShowMenu();

		CRect dlgRect;
		this->GetClientRect(dlgRect);
		if (batterysPanePic.m_hWnd) {
			batterysPanePic.MoveWindow(MARGIN_LEFT_BATPANE, MARGIN_TOP_BATPANE, dlgRect.Width(), dlgRect.Height(), TRUE);

			if (pbatterysDlgs[curCabId-1] != NULL) {
				pbatterysDlgs[curCabId - 1]->DestroyWindow();
				delete pbatterysDlgs[curCabId-1];  pbatterysDlgs[curCabId-1] = NULL; 
			}

			if (tbatterysDlgs[curCabId-1] != NULL) {
				tbatterysDlgs[curCabId - 1]->DestroyWindow();
				delete tbatterysDlgs[curCabId-1]; 
				tbatterysDlgs[curCabId-1] = NULL; 
			}

			if (cbatterysDlgs[curCabId-1] != NULL) { 
				cbatterysDlgs[curCabId - 1]->DestroyWindow();
				delete cbatterysDlgs[curCabId-1];
				cbatterysDlgs[curCabId-1] = NULL; 
			}

			if (ebatterysDlgs[curCabId-1] == NULL)
			{
				ebatterysDlgs[curCabId-1] = new CEbatterysDlg();
				ebatterysDlgs[curCabId-1]->Create(IDD_EBATTERYS_DLG, this);
			}
			ebatterysDlgs[curCabId-1]->OnSize(0, dlgRect.Width() - MARGIN_LEFT_BATPANE, dlgRect.Height() - MARGIN_TOP_BATPANE);
		}

	}
}

void CBatteryMainView::InitBatShowMenu()
{
	int checkFlag = MF_CHECKED;

	for (int idx = 0; idx <= EXCEP_STYLE; ++ idx)
	{
		checkFlag = idx == BatShowStyle ? MF_CHECKED : MF_UNCHECKED;
		batShowSubMenu->CheckMenuItem(idx, MF_BYPOSITION | checkFlag );
	}
}

void CBatteryMainView::HandleLowerInfos()
{
	int infoLen = lowerInfos.GetLength();
	int dataLen = 0, pieceLen = 0;
	if (infoLen >= DATA_LENGTH_POS + 2)//�㹻��ȡ���ݵ���Ч������Ϣ
	{
		dataLen = (OBTAIN_BATDATA_FLAG == TRUE ? 2 + StringUtils::XStrToInt(lowerInfos.Mid(DATA_LENGTH_POS, 4)) :
			1 + StringUtils::XStrToInt(lowerInfos.Mid(DATA_LENGTH_POS, 2)));

		pieceLen =  dataLen * 2 + DATA_LENGTH_POS;
		// �������д���
		while (infoLen >= pieceLen)
		{
			CString lowerInfos2 = lowerInfos.Left(pieceLen);

			HandleLowerInfo(lowerInfos2, pieceLen);
			lowerInfos = lowerInfos.Right(infoLen - pieceLen);
			infoLen = lowerInfos.GetLength();

			if (infoLen >= DATA_LENGTH_POS + 2){
				dataLen = (OBTAIN_BATDATA_FLAG == TRUE ? 2 + StringUtils::XStrToInt(lowerInfos.Mid(DATA_LENGTH_POS, 4)) :
					1 + StringUtils::XStrToInt(lowerInfos.Mid(DATA_LENGTH_POS, 2)));
				pieceLen = dataLen * 2 + DATA_LENGTH_POS;
			}
			else
			{
				break;
			}
		}
	}
}



void CBatteryMainView::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int a = 0;
	CFormView::OnSysCommand(nID, lParam);
}

void CBatteryMainView::InitilizeConsoleDevice()
{
	EnumerateSerialPorts(ports,  portse, portsu);
}

void CBatteryMainView::EnumerateSerialPorts(CUIntArray& ports, CUIntArray& portse, CUIntArray& portsu)
{
	//���������������  
	ports.RemoveAll();
	portse.RemoveAll();
	portsu.RemoveAll();
	//��Ϊ������255�����ڣ��������μ��������Ƿ����  
	//����ܴ�ĳһ���ڣ���򿪴��ڲ��ɹ��������ص��� ERROR_ACCESS_DENIED������Ϣ��  
	//����Ϊ���ڴ��ڣ�ֻ�������߱��������Ѿ���ռ��  
	//���򴮿ڲ�����  
	for (int i = 1; i < 256; i++)
	{
		//Form the Raw device name  
		CString sPort;
		sPort.Format(_T("\\\\.\\COM%d"), i);

		//Try to open the port  
		BOOL bSuccess = FALSE;
		HANDLE hPort = CreateFile(sPort, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
		if (hPort == INVALID_HANDLE_VALUE)
		{
			DWORD dwError = GetLastError();

			if (dwError == ERROR_ACCESS_DENIED)
			{
				bSuccess = TRUE;
				portsu.Add(i);       //��ռ�õĴ���  
			}
		}
		else
		{
			
			//The port was opened successfully  
			bSuccess = TRUE;
			portse.Add(i);      ////���õĴ���  
			//PortOpenFlag = InitSerialPort(i);
			//Don't forget to close the port, since we are going to do nothing with it anyway  
			CloseHandle(hPort);
			PortOpenFlag = InitSerialPort(i);
			if (PortOpenFlag)
			{
				((CMainFrame *)(this->GetParent()))->SetWindowTextW(L"�˿�"+ cabIdsCstr[i-1] + L"������......");
			}
		}

		//Add the port number to the array which will be returned  
		if (bSuccess)
			ports.Add(i);   //���д��ڵĴ���  
	}
}

void CBatteryMainView::CloseConsoleDevice()
{
	//::AfxEndThread(SendThread(this));
	//m_hSendThread->SuspendThread();
	PortOpenFlag = FALSE;
	((CMainFrame*)(this->GetParent()))->SetMessageText(L"����δ����......");
	m_ctrlComm.put_PortOpen(FALSE);
}

void SaveDbConfs(LPVOID param)
{

	CBatteryMainView *batteryMainView = (CBatteryMainView*)param;
	CDbUtils *dbUtils = CDbUtils::GetInstance();
	CString stepConfPath, stepInitPath;
	wchar_t str[MAX_PATH_LENGTH];

	for (int cabIdx = 0; cabIdx < MAX_CAB_NUM; ++cabIdx)
	{
		vector<CByteArray*> stepByteArrays;

		stepByteArrays.clear();
		if (cabSelStr[cabIdx] == '1' && SendStepFlags[cabIdx])
		{
			stepConfPath = CBatteryUtils::GetConfigPath(_T("\\config\\step\\")
				+ cabIdsCstr[cabIdx] + _T("\\preStepPath.ini"));
			GetPrivateProfileString(_T("stepFilePath"), _T("path"), _T("error"), str, MAX_PATH_LENGTH, stepConfPath);
			stepInitPath = str;
			// ���ݹ���txt��������
			if (stepInitPath != _T("error"))
			{
				std::ifstream in(stepInitPath);
				if (in.is_open())
				{
					string line;
					int nRow, nCol;
					// �ļ���һ��Ϊ��������
					// �ڶ���Ϊ�ͺ�
					//�ļ�������Ϊ���������������Ϊ�������
					getline(in, line);
					getline(in, line);
					getline(in, line);
					nRow = std::stoi(line);
					getline(in, line);
					nCol = std::stoi(line);
					stringstream ss;
					string stepIdStr;
					// ���ɹ�������
					vector<string> strs;
					vector< vector<string>> strss;
					strss.clear();
					for (int i = 1; i < nRow; ++i)
					{
						ss << i;
						ss >> stepIdStr;
						ss.clear();
						getline(in, line);
						strs.clear(); 
						strs = StringUtils::SplitByStr(line, " ");
						if (strs.size() != STEP_COL_NUM-1)
							continue;
						strs.push_back(stepIdStr);
						strss.push_back(strs);
					}
					// �洢����
					dbUtils->SaveWorkProcToDb(cabIdx, strss);
				}
			}
		}
	}
}

// �����Ƿ���Ҫ�����µ����ݿ����TestInfo
// ��������TestInfo  vector�������ݿ�TestInfo��
void SaveDbTestInfos(LPVOID param)
{	
	CBatteryMainView *batteryMainView = (CBatteryMainView*)param;
	CDbUtils *dbUtils = CDbUtils::GetInstance();
	
	//1 ��ȡʱ��
	CString currentTimeCstr = CTimeUtils::GetCurrentTimeCstr();

	//2 ����TestInfos

	for (int cabIdx = 0; cabIdx < MAX_CAB_NUM; ++cabIdx)
	{
		if (cabSelStr[cabIdx] == '1' && SendStepFlags[cabIdx])
		{
			if (batteryMainView->testInfos.size() < cabIdx + 1)
			{
				TestInfo *testInfo = new TestInfo(cabInfos[cabIdx], currentTimeCstr, cabDbPaths[cabIdx]);
				batteryMainView->testInfos.push_back(testInfo);
				dbUtils->SaveTestInfoToDb(cabIdx, testInfo);
			}
			else
			{
				TestInfo testInfo2 = TestInfo(cabInfos[cabIdx], currentTimeCstr, cabDbPaths[cabIdx]);
				(*batteryMainView->testInfos[cabIdx]) = testInfo2;
				dbUtils->UpdateTestInfoToDb(cabIdx, &testInfo2);
			}
		}
		else
		{
			if (batteryMainView->testInfos.size() < cabIdx + 1)
			{
				batteryMainView->testInfos.push_back(NULL);
			}
		}
	}
}

