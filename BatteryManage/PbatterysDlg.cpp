// PbatterysDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "PbatterysDlg.h"
#include "BatteryPane.h"
#include "afxdialogex.h"
#include "LowerUtils.h"

#include <string>
#include <iostream>

using namespace std;

// CPbatterysDlg �Ի���
IMPLEMENT_DYNAMIC(CPbatterysDlg, CDialog)

CPbatterysDlg::CPbatterysDlg(CWnd* pParent /*=NULL*/)
: CDialog(CPbatterysDlg::IDD, pParent)
{

	batteryTrack = true;	//����׷������ټ�Ϊtrue
	initFlag = false;
	//  ����CabId�����ݿ��л�ȡ�������

	cabinetInfo = GetCabInfoByCurId(defCabId);

	batteryPane = new CBatteryPane(cabinetInfo);
	
	batIdFont.CreateFontW(
		14,
		0, //���߼���λ��ʽָ���������ַ���ƽ�����
		0, //ָ��ƫ�봹�ߺ�X������ʾ���ϵļнǣ���λ��0.1�ȣ�
		0, //ָ���ַ������ߺ�X��֮��ļнǣ���λ��0.1�ȣ�
		FW_BOLD, //ָ���������
		FALSE, //�ǲ���б��
		FALSE, //�Ӳ����»���
		0, //ָ���Ƿ��������ַ�ͻ��
		ANSI_CHARSET, //ָ��������ַ���
		OUT_DEFAULT_PRECIS, //ָ��������������
		CLIP_DEFAULT_PRECIS, //ָ������ļ�������
		DEFAULT_QUALITY, //ָʾ������������
		0 | FF_SWISS, //ָ������ļ��ͼ���
		_T("Fixedsys") //ָ���������������
		);

	batStateFont.CreateFontW(
		16,
		0, //���߼���λ��ʽָ���������ַ���ƽ�����
		0, //ָ��ƫ�봹�ߺ�X������ʾ���ϵļнǣ���λ��0.1�ȣ�
		0, //ָ���ַ������ߺ�X��֮��ļнǣ���λ��0.1�ȣ�
		FW_BOLD, //ָ���������
		FALSE, //�ǲ���б��
		FALSE, //�Ӳ����»���
		0, //ָ���Ƿ��������ַ�ͻ��
		ANSI_CHARSET, //ָ��������ַ���
		OUT_DEFAULT_PRECIS, //ָ��������������
		CLIP_DEFAULT_PRECIS, //ָ������ļ�������
		DEFAULT_QUALITY, //ָʾ������������
		-2 | 0, //ָ������ļ��ͼ���
		_T("Fixedsys") //ָ���������������
		);

	batteryPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	batBackBrush.CreateSolidBrush(RGB(0, 128, 192));
	batBrush.CreateSolidBrush(RGB(128, 128, 128));
	vaChargeBrush.CreateSolidBrush(initColor.vaChargeCol);
	chargeBrush.CreateSolidBrush(initColor.chargeCol);
	dischargeBrush.CreateSolidBrush(initColor.dischargeCol);
	layBrush.CreateSolidBrush(initColor.layCol);

	regiditBrush.CreateSolidBrush(initColor.storCol);				//	�Ĵ���ɫ
	currentErrorBrush.CreateSolidBrush(initColor.aerrorCol);		//	�����쳣
	voltErrorBrush.CreateSolidBrush(initColor.verrorCol);			//	��ѹ�쳣
	capacityErrorBrush.CreateSolidBrush(initColor.overAlarmCol);	//	�����쳣
	noneBatBrush.CreateSolidBrush(initColor.badContCol);			//	�޵�ػ��ߵ�ؽӴ�����
	badBatBrush.CreateSolidBrush(initColor.badBatCol);				//	�������
	offVoltBrush.CreateSolidBrush(initColor.offVoltCol);			//	ƫ���ѹ�쳣

	batCabBrushs[SASC_CHARGE_CODE] = &vaChargeBrush;
	batCabBrushs[CHARGE_CODE] = &chargeBrush;
	batCabBrushs[DISCHARGE_CODE] = &dischargeBrush;
	batCabBrushs[LAY_CODE] = &layBrush;




	batBrushs[UNOVER_CODE] = &regiditBrush;
	batBrushs[TIME_COME_CODE] = &regiditBrush;
	batBrushs[MAX_VOLT_COME_CODE] = &regiditBrush;
	batBrushs[MIN_VOLT_COME_CODE] = &regiditBrush;
	batBrushs[END_CURRENT_COME_CODE] = &regiditBrush;
	batBrushs[DELTA_COME_CODE] = &regiditBrush;
	batBrushs[CURRENT_ERROR_CODE] = &currentErrorBrush;
	batBrushs[VOLT_ERROR_CODE] = &voltErrorBrush;
	batBrushs[CAPACITY_ERROE_CODE] = &capacityErrorBrush;
	batBrushs[OFF_VOLT_CODE] = &offVoltBrush;
	batBrushs[HAND_REGIDIT_CODE] = &regiditBrush;
	batBrushs[NONE_BAT_CODE] = &noneBatBrush;
	batBrushs[BAD_BAT_CODE] = &badBatBrush;


}

CPbatterysDlg::~CPbatterysDlg()
{

	if (batteryPane != NULL) delete batteryPane;

	//1 ����
	if (selBrush) delete selBrush;

	batBackBrush.DeleteObject();
	batBrush.DeleteObject();
	vaChargeBrush.DeleteObject();
	chargeBrush.DeleteObject();
	dischargeBrush.DeleteObject();
	layBrush.DeleteObject();

	regiditBrush.DeleteObject();			//	�Ĵ���ɫ
	currentErrorBrush.DeleteObject();		//	�����쳣
	voltErrorBrush.DeleteObject();			//	��ѹ�쳣
	capacityErrorBrush.DeleteObject();		//	�����쳣
	noneBatBrush.DeleteObject();			//	�޵�ػ��ߵ�ؽӴ�����
	badBatBrush.DeleteObject();				//	�������
	offVoltBrush.DeleteObject();			//	ƫ���ѹ�쳣

	//3 BatteryDetailDlg

	if (batteryDetailDlg) {
		batteryDetailDlg->DestroyWindow();
		delete batteryDetailDlg;
		batteryDetailDlg = NULL;
	}
}

void CPbatterysDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPbatterysDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_MOUSEMOVE()
	//ON_STN_CLICKED(IDC_BATTERYS_PIC, &CPbatterysDlg::OnStnClickedBatterysPic)
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()

	//ON_COMMAND(ID_SHOW_STEP_DATA, &CPbatterysDlg::OnShowStepData)
END_MESSAGE_MAP()


void DrawMultLineText(CDC *pDC, CRect rect, int nRowDis, UINT nFromat, CString strText)
{

	if (strText.GetLength() <= 0)
		return;

	WCHAR* pText = strText.GetBuffer(strText.GetLength());
	int nCount = strText.GetLength();
	CRect rtChar;
	CSize size = pDC->GetTextExtent(pText + 0, 1);
	int nRowHeight = size.cy + nRowDis;
	rtChar.top = rect.top;
	rtChar.left = rect.left;
	rtChar.bottom = rtChar.top + nRowDis + size.cy;
	rtChar.right = rtChar.left + size.cx;
	CString strChar;
	for (int nCharIndex = 0; nCharIndex < nCount; nCharIndex++)
	{
		if (rtChar.right > rect.right)
		{
			rtChar.top = rtChar.bottom;
			rtChar.bottom += nRowHeight;
			size = pDC->GetTextExtent(pText + nCharIndex, 1);
			rtChar.left = rect.left;
			rtChar.right = rtChar.left + size.cx;
			if (rtChar.bottom > rect.bottom)
				break;
		}
		strChar = pText[nCharIndex];
		pDC->DrawText(strChar, rtChar, nFromat);
		size = pDC->GetTextExtent(pText + nCharIndex + 1, 1);
		rtChar.left = rtChar.right;
		rtChar.right += size.cx;
	}
}


// CPbatterysDlg ��Ϣ�������

/*-----------------------------------------------------------------------------
������㷨
(1) ����ÿ������
-----------------------------------------------------------------------------*/

void CPbatterysDlg::InitPaint(CDC &memDC)
{
	cabinetInfo = cabInfos[curCabId-1];

	this->GetClientRect(&batPicRect);
	
	HDC hdc = memDC.GetSafeHdc();
	//HDC hdc = this->GetDC()->GetSafeHdc();
	//LPTEXTMETRICW fontMetrica;
	//GetTextMetrics(hdc, fontMetrica);
	//fontMetrica->tmExternalLeading = 0;	// �м������Ϊ0

	memDC.SetTextCharacterExtra(0);

	FillRect(hdc, batPicRect, batBackBrush);

	//0.2 �������� 
	//CBrush textBrush(RGB(192, 0, 0));
	memDC.SetTextColor(RGB(0, 255, 0));
	memDC.SetBkMode(TRANSPARENT);
	
	memDC.SelectObject(batIdFont);

	int textMarginTop = 2;
	CString batIdStr;
	int colId;
	//(1) ��ʼ������,pen�ȹ���

	
	CPen *oldPen = memDC.SelectObject(&batteryPen);
	
	//(2) ��ȡ����ÿһ�еĸ߶ȡ���صĿ�ȵ���Ϣ
	this->GetClientRect(batPicRect);

	CRect batPicMainRect = batPicRect;
	batPicMainRect.right -= BATMAIN_MARGIN_RIGHT;

	batteryPane->CalParamter(batPicMainRect);


	//ScreenToClient(batteryPane->paneRect);
	//(3) ��ʼ�������͵��ñ��λ��
	int batteryBodyStartX = (batteryPane->GetGroupBlankWidth());

	int batteryBodyStartY = (1 - batteryPane->GetBodyHeightRowRatio())*(batteryPane->GetBatteryRowHeight());

	int batteryCapStartX = batteryBodyStartX + batteryPane->GetBatteryWidth() / 4;

	int batteryCapStartY = (1 - batteryPane->GetBatHeightRowRatio())*(batteryPane->GetBatteryRowHeight());

	CRect batteryBodyRect(batteryBodyStartX + 1, batteryBodyStartY - 1, batteryBodyStartX + batteryPane->GetBatteryWidth() - 1,
		(batteryPane->GetBatteryRowHeight()));

	CRect batteryCapRect(batteryCapStartX, batteryCapStartY, batteryCapStartX + batteryPane->GetBatteryCapWidth(),
		batteryBodyStartY);

	int frontNum = 1;
	int batSeqId = 0;
	if (cabinetInfo.colShowNum == 2 && paneId == _T(BACK_PANE))
	{
		frontNum += cabinetInfo.groupNumPerCol;
		batSeqId += cabinetInfo.groupNumPerCol * cabinetInfo.numPerGroup;
	}


	for (int idx = 0; idx < batteryPane->GetRowNum(); ++idx)
	{
		colId = idx + frontNum;

		for (int subGroupIdx = 0; subGroupIdx < batteryPane->GetSubGroupNum(); ++subGroupIdx)
		{	
				batIdStr.Format(_T("%d-%d"), colId,subGroupIdx+1);
				memDC.SelectObject(batIdFont);
				memDC.TextOutW(batteryBodyRect.left - batteryPane->GetGroupBlankWidth(),
					idx * batteryPane->GetBatteryRowHeight() + textMarginTop,
					batIdStr);
				memDC.SelectObject(batStateFont);

			for (int groupInnerIdx = 0; groupInnerIdx < batteryPane->GetSubGroupBatNum(); ++groupInnerIdx)
			{
				memDC.SelectObject(batteryPen);
				memDC.Rectangle(&batteryBodyRect);//���ƾ���
				memDC.Rectangle(&batteryCapRect);
				if (lowerCabs.cabBatterys[curCabId - 1] == NULL)
				{
					FillRect(hdc, CRect(batteryBodyRect.left + 1, batteryBodyRect.top + 1,
						batteryBodyRect.right - 1, batteryBodyRect.bottom - 1),batBrush);
				}
				else
				{

					int batState = (lowerCabs.cabBatterys[curCabId - 1])->batterys[batSeqId].batStatVal;
					int cabState = (lowerCabs.cabBatterys[curCabId - 1])->cabState;
					int batDrawState;

					if (batState != INVALIDE_STATE)
					{
						batDrawState = batState ==  UNOVER_CODE ? cabState : batState;
						CRect drawRect(batteryBodyRect.left + 1, batteryBodyRect.top + 1,
							batteryBodyRect.right - 1, batteryBodyRect.bottom - 1);
						CRect drawRect2(batteryBodyRect.left + batteryCapRect.Width()/2 + 1, batteryBodyRect.top - 2,
							batteryBodyRect.left + batteryBodyRect.Width() / 2 + 6, batteryBodyRect.bottom + 2);
						//CRect drawRect2(batteryBodyRect.left + batteryCapRect.Width()/3, batteryBodyRect.top + batteryBodyRect.Height()/4,
						//	batteryBodyRect.right - batteryCapRect.Width()/3, batteryBodyRect.bottom);

						if (batDrawState >= MIN_BAT_STATE && batDrawState <= MAX_BAT_STATE)
						{
							FillRect(hdc, drawRect, batState == UNOVER_CODE ? *batCabBrushs[batDrawState] : *batBrushs[batDrawState]);
							//FillRect(hdc, drawRect, batBrush);
							
						}

						//int batCountId = 1;
						CString stateStr = (lowerCabs.cabBatterys[curCabId - 1])->batterys[batSeqId].GetSpecStateStr(STATE_SEL_CODE);
						memDC.DrawText(stateStr, drawRect2,  DT_CENTER | DT_EDITCONTROL | DT_WORDBREAK | DT_VCENTER);
	
						//DrawMultLineText(&memDC, drawRect2, -2, DT_CENTER | DT_EDITCONTROL | DT_WORDBREAK | DT_VCENTER, stateStr);
						//memDC.TextOutW(batteryBodyRect.left, batteryBodyRect.top + 10,
						//	stateStr);
					}
					else
					{
						FillRect(hdc, CRect(batteryBodyRect.left + 1, batteryBodyRect.top + 1,
							batteryBodyRect.right - 1, batteryBodyRect.bottom - 1), batBrush);
					}
					
				}
				batSeqId++;	// ��¼ÿ��cab��bat����(��1++��N)

				FillRect(hdc, CRect(batteryCapRect.left + 1, batteryCapRect.top + 1,
					batteryCapRect.right - 1, batteryCapRect.bottom - 1), batBrush);
				batteryBodyRect.OffsetRect(batteryPane->GetBatteryWidth(), 0);
				batteryCapRect.OffsetRect(batteryPane->GetBatteryWidth(), 0);

			}
			batteryBodyRect.OffsetRect(batteryPane->GetGroupBlankWidth(), 0);
			batteryCapRect.OffsetRect(batteryPane->GetGroupBlankWidth(), 0);

		}

		if (batSeqId > 89 && batSeqId < 96)
		{
			int a = (lowerCabs.cabBatterys[curCabId - 1])->batterys[batSeqId].batStatVal;
			int b = (lowerCabs.cabBatterys[curCabId - 1])->cabState;
			int c =  a == UNOVER_CODE ? b : a;
			int d = 0;
		}
		batteryBodyRect.SetRect(batteryBodyStartX + 1, batteryBodyStartY - 1, batteryBodyStartX + batteryPane->GetBatteryWidth() - 1,
			(batteryPane->GetBatteryRowHeight()));
		batteryCapRect.SetRect(batteryCapStartX, batteryCapStartY, batteryCapStartX + batteryPane->GetBatteryCapWidth(),
			batteryBodyStartY);

		batteryBodyRect.OffsetRect(0, (batteryPane->GetBatteryRowHeight())*(idx + 1));
		batteryCapRect.OffsetRect(0, (batteryPane->GetBatteryRowHeight())*(idx + 1));
	}
	//dc.SelectObject(oldPen)
	initFlag = TRUE;
}

/*
������ rowId-groupId-subGroupId���ڵ�λ��
*/
CRect CPbatterysDlg::CalSpecBatteryCap(int rowId, int groupId, int subGroupId)
{
	int batteryBodyStartX = (batteryPane->GetGroupBlankWidth());

	int batteryBodyStartY = (1 - batteryPane->GetBodyHeightRowRatio())*(batteryPane->GetBatteryRowHeight());

	int batteryCapStartX = batteryBodyStartX + batteryPane->GetBatteryWidth() / 4;

	int batteryCapStartY = (1 - batteryPane->GetBatHeightRowRatio())*(batteryPane->GetBatteryRowHeight());

	CRect rect;
	int left, top;

	left = (subGroupId - 1)*batteryPane->GetBatteryWidth()
		+ (groupId - 1)*batteryPane->GetGroupWidth();
	top = (rowId - 1) * batteryPane->GetBatteryRowHeight();
	left += batteryCapStartX;
	top += batteryCapStartY;

	rect.left = left + BATTERY_BORDER_WIDTH;
	rect.top = top + BATTERY_BORDER_WIDTH;
	rect.right = left + batteryPane->GetBatteryCapWidth() - BATTERY_BORDER_WIDTH;
	rect.bottom = top + batteryPane->GetBatteryCapHeight() - BATTERY_BORDER_WIDTH;

	return rect;
}

//void CPbatterysDlg::OnPaint()
//{
//	//CDialog::OnPaint();
//
//	// ��ֹ�̳߳�ʱ��ռ������
//	//MSG msg;
//	//if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//	//{
//	//	if (msg.message == WM_QUIT)
//	//		return;
//	//	TranslateMessage(&msg);
//	//	DispatchMessage(&msg);
//	//}
//
//	CPaintDC dc(this);
//
//	CDC memDC;			//	����һ����ʾ�豸����
//	CBitmap memBitMap;	//	����һ��λͼ����
//
//	// ����һ������Ļ��ʾ���ݵ�λͼ,λͼ�Ĵ�С�봰�ڴ�С��һ��
//	this->GetClientRect(&batPicRect);
//
//	// ��������Ļ��ʾ���ݵ��ڴ���ʾ�豸
//	if (memDC.CreateCompatibleDC(&dc)) {
//
//		if (memBitMap.CreateCompatibleBitmap(&dc, batPicRect.Width(), batPicRect.Height()))
//		{
//			// ��λͼѡ�뵽�ڴ���ʾ�豸��
//			if (HGDIOBJ oldBit = memDC.SelectObject(&memBitMap)) {
//				// ��������ͼ,�Դ���͸��ɫ
//				if (memDC.BitBlt(0, 0, batPicRect.Width(), batPicRect.Height(), &dc, 0, 0, SRCCOPY))
//				{
//					Gdiplus::Graphics g(memDC);
//
//					switch (paintFactor)
//					{
//					case INIT_REPAINT:
//					{
//										 InitPaint(memDC);
//										 break;
//					}
//					case TIP_REPAINT:
//					{
//										break;
//					}
//					case STATE_REPAINT:
//					{
//										  break;
//					}
//					default:
//						break;
//					}
//					dc.BitBlt(0, 0, batPicRect.Width(), batPicRect.Height(), &memDC, 0, 0, SRCCOPY);
//				}
//				dc.SelectObject(oldBit);
//			}
//			memBitMap.DeleteObject();
//		}
//		memDC.DeleteDC();
//	}
//}

void CPbatterysDlg::OnPaint()
{
	
	CPaintDC pdc(this);

	DoPaint();

}


void CPbatterysDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (this->m_hWnd) {
		CRect rect(0, 0, cx, cy);

		this->MoveWindow(rect.left + MARGIN_LEFT_BATPANE, rect.top + MARGIN_TOP_BATPANE, rect.Width(), rect.Height(), TRUE);

	}

}


void CPbatterysDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	lpMMI->ptMinTrackSize.x = 640;

	lpMMI->ptMinTrackSize.y = 480;
	CDialog::OnGetMinMaxInfo(lpMMI);
}

void CPbatterysDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CDialog::OnMouseMove(nFlags, point);
}

BOOL CPbatterysDlg::PreTranslateMessage(MSG* pMsg)
{
	//if (pMsg->message == WM_MOUSEMOVE)
	//{

	int frontNum = 0;
	if (cabinetInfo.colShowNum == 2 && paneId == _T(BACK_PANE))
	{
		frontNum += cabinetInfo.groupNumPerCol;
	}
	else if (cabinetInfo.colShowNum == 1 && paneId == _T(BACK_PANE))
	{
		paneId = _T(FRONT_PANE);
	}

	POINT point;
	::GetCursorPos(&point);
	this->GetClientRect(batPicRect);
	ClientToScreen(batPicRect);
	if (point.x < batPicRect.right && point.x > batPicRect.left && point.y > batPicRect.top
		&& point.y < batPicRect.bottom)
	{
		int x = point.x - batPicRect.left;
		int y = point.y - batPicRect.top;

		if (batteryPane->GetGroupWidth() == 0)
		{
			this->GetClientRect(&batPicRect);
			batteryPane->CalParamter(batPicRect);
		}

		int rowId = frontNum + (y + batteryPane->GetBatteryRowHeight() - 1) / batteryPane->GetBatteryRowHeight();
		int groupId = (x + batteryPane->GetGroupWidth() - 1) / batteryPane->GetGroupWidth();
		int subGroupId = (x - (groupId - 1)*batteryPane->GetGroupWidth() -
			batteryPane->GetGroupBlankWidth() + batteryPane->GetBatteryWidth() - 1) / batteryPane->GetBatteryWidth();

		//int subGroupId = (x - (groupId - 1)*batteryPane->GetGroupWidth() -
		//	batteryPane->GetGroupBlankWidth() + batteryPane->GetBatteryWidth()) / batteryPane->GetBatteryWidth();
		CString rowIdStr, groupIdStr, subGroupIdStr;

		if (subGroupId > 0) {

			if (!(rowId == preRowId && groupId == preGroupId && subGroupId == preSubGroupId))
			{
				if (subGroupId <= batteryPane->GetSubGroupBatNum()) {
					rowIdStr.Format(_T("%d"), rowId);
					groupIdStr.Format(_T("%d"), groupId);
					subGroupIdStr.Format(_T("%d"), subGroupId);

					preRowId = rowId;
					preGroupId = groupId;
					preSubGroupId = subGroupId;

					toolTip.RelayEvent(pMsg);
					toolTip.UpdateTipText(rowIdStr + _T("-") + groupIdStr + _T("-") + subGroupIdStr, batPicWnd);
				}
				else
				{
					preRowId = preGroupId = preSubGroupId = 0;
					toolTip.Pop();
				}
			}
		}
		else
		{
			preRowId = preGroupId = preSubGroupId = 0;
			toolTip.Pop();
		}
	}
	//}

	return CDialog::PreTranslateMessage(pMsg);
}


BOOL CPbatterysDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	paintFactor = INIT_REPAINT;

	preRowId = preGroupId = preSubGroupId = 0;
	preSelRowId = preSelGroupId = preSelSubGroupId = 0;

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��


	// ��ʼ������
	selBatColor = RGB(255, 0, 0);
	selBrush = new CBrush(selBatColor);
	batStateColors.push_back(RGB(128, 128, 128));

	// ��ʼ��BatteryDetailDlg
	//3 ������ߴ���
	batteryDetailDlg = NULL;


	batPicWnd = CWnd::FromHandle(this->GetSafeHwnd());
	EnableToolTips(TRUE);
	toolTip.Create(this);
	toolTip.Activate(TRUE);
	toolTip.SetTipTextColor(RGB(0, 0, 0));
	toolTip.AddTool(batPicWnd);
	toolTip.SetDelayTime(2111);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

/*
���������ʱ,ѡ�е�ǰ���,�����Ա��,Ȼ�󵯳���Ӧ�Ŀ�
*/
void CPbatterysDlg::OnStnClickedBatterysPic()
{

}


void CPbatterysDlg::OnRButtonDown(UINT nFlags, CPoint point)
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


void CPbatterysDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	// ��ֹ�̳߳�ʱ��ռ������
	MSG msg;
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			return;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	//1.0 ���㵱ǰ���
	if (!CanConnFlag || !PortOpenFlag)
	{
		AfxMessageBox(L"�˿�δ�򿪻���δ���͹�����Ϣ����ȷ�Ϻ����ԣ�");
		return;
	}

	int x = point.x;
	int y = point.y;

	int rowId = (y + batteryPane->GetBatteryRowHeight() - 1) / batteryPane->GetBatteryRowHeight();
	int groupId = (x + batteryPane->GetGroupWidth() - 1) / batteryPane->GetGroupWidth();
	int subGroupId = (x - (groupId - 1)*batteryPane->GetGroupWidth() -
		batteryPane->GetGroupBlankWidth() + batteryPane->GetBatteryWidth() - 1) / batteryPane->GetBatteryWidth();

	// �����ر��,�����ϸ��ʹ��
	curRowId = rowId;
	curGroupId = groupId;
	curGroupInnerId = subGroupId;
	if (paneId == _T(BACK_PANE))
		curRowId += cabinetInfo.groupNumPerCol;
	curBatteryId = (curRowId - 1)*cabinetInfo.numPerGroup + (curGroupId - 1)*SUBGROUP_NUM + curGroupInnerId;


	CRect preCapRect;
	CRect curCapRect;
	HDC hdc = this->GetDC()->GetSafeHdc();
	//1.1 �����ǰҳ���ϵľ���(���ñ)
	if (!(preSelRowId == rowId && preSelGroupId == groupId && preSelSubGroupId == subGroupId)
		&& subGroupId > 0 && subGroupId <= batteryPane->GetSubGroupBatNum())
	{
		if (!(preSelRowId == 0 && preSelGroupId == 0 && preSelSubGroupId == 0))
		{
			//1.1 �����ǰҳ���ϵľ���(���ñ
			preCapRect = CalSpecBatteryCap(preSelRowId, preSelGroupId, preSelSubGroupId);
			FillRect(hdc, preCapRect, CBrush(batStateColors[0]));
		}
		//1.2 ����ǰѡ�еĵ�����ڵľ���
		curCapRect = CalSpecBatteryCap(rowId, groupId, subGroupId);
		FillRect(hdc, curCapRect, *selBrush);

		preSelRowId = rowId;
		preSelGroupId = groupId;
		preSelSubGroupId = subGroupId;
	}
	//2 ������
	if (subGroupId > 0 && subGroupId <= batteryPane->GetSubGroupBatNum())
	{
		if (batteryDetailDlg == NULL)
		{
			batteryDetailDlg = new CBatteryDetailDlg();
		}
		batteryDetailDlg->DoModal();
	}
	CDialog::OnLButtonDown(nFlags, point);
}





void CPbatterysDlg::OnShowStepData()
{
	// TODO:  �ڴ���������������
}

CabinetInfo CPbatterysDlg::GetCabInfoByCurId(int cabId)
{
	CabinetInfo cabinetInfo;

	if (cabId >= 1 && cabId <= MAX_CAB_NUM)
	{
		cabinetInfo = cabInfos[cabId - 1];
	}
	return cabinetInfo;
}





HRESULT CPbatterysDlg::accDoDefaultAction(VARIANT varChild)
{
	// TODO:  �ڴ����ר�ô����/����û���

	return CDialog::accDoDefaultAction(varChild);
}

void CPbatterysDlg::DoPaint()
{
	CDC *dc = GetDC();

	CDC memDC;			//	����һ����ʾ�豸����
	CBitmap memBitMap;	//	����һ��λͼ����

	// ����һ������Ļ��ʾ���ݵ�λͼ,λͼ�Ĵ�С�봰�ڴ�С��һ��
	this->GetClientRect(&batPicRect);

	// ��������Ļ��ʾ���ݵ��ڴ���ʾ�豸
	if (memDC.CreateCompatibleDC(dc)) {

		if (memBitMap.CreateCompatibleBitmap(dc, batPicRect.Width(), batPicRect.Height()))
		{
			// ��λͼѡ�뵽�ڴ���ʾ�豸��
			if (HGDIOBJ oldBit = memDC.SelectObject(&memBitMap)) {
				// ��������ͼ,�Դ���͸��ɫ
				if (memDC.BitBlt(0, 0, batPicRect.Width(), batPicRect.Height(), dc, 0, 0, SRCCOPY))
				{
					//Gdiplus::Graphics g(memDC);

					switch (paintFactor)
					{
					case INIT_REPAINT:
					{
										 InitPaint(memDC);
										 break;
					}
					case TIP_REPAINT:
					{
										break;
					}
					case STATE_REPAINT:
					{
										  break;
					}
					default:
						break;
					}
					dc->BitBlt(0, 0, batPicRect.Width(), batPicRect.Height(), &memDC, 0, 0, SRCCOPY);
				}
				dc->SelectObject(oldBit);
			}
			memBitMap.DeleteObject();
		}
		memDC.DeleteDC();
	}
	ReleaseDC(dc);
}


