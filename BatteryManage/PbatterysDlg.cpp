// PbatterysDlg.cpp : 实现文件
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

// CPbatterysDlg 对话框
IMPLEMENT_DYNAMIC(CPbatterysDlg, CDialog)

CPbatterysDlg::CPbatterysDlg(CWnd* pParent /*=NULL*/)
: CDialog(CPbatterysDlg::IDD, pParent)
{

	batteryTrack = true;	//设置追踪鼠标踪迹为true
	initFlag = false;
	//  根据CabId从数据库中获取相关数据

	cabinetInfo = GetCabInfoByCurId(defCabId);

	batteryPane = new CBatteryPane(cabinetInfo);
	
	batIdFont.CreateFontW(
		14,
		0, //以逻辑单位方式指定字体中字符的平均宽度
		0, //指定偏离垂线和X轴在显示面上的夹角（单位：0.1度）
		0, //指定字符串基线和X轴之间的夹角（单位：0.1度）
		FW_BOLD, //指定字体磅数
		FALSE, //是不是斜体
		FALSE, //加不加下划线
		0, //指定是否是字体字符突出
		ANSI_CHARSET, //指定字体的字符集
		OUT_DEFAULT_PRECIS, //指定所需的输出精度
		CLIP_DEFAULT_PRECIS, //指定所需的剪贴精度
		DEFAULT_QUALITY, //指示字体的输出质量
		0 | FF_SWISS, //指定字体的间距和家族
		_T("Fixedsys") //指定字体的字样名称
		);

	batStateFont.CreateFontW(
		16,
		0, //以逻辑单位方式指定字体中字符的平均宽度
		0, //指定偏离垂线和X轴在显示面上的夹角（单位：0.1度）
		0, //指定字符串基线和X轴之间的夹角（单位：0.1度）
		FW_BOLD, //指定字体磅数
		FALSE, //是不是斜体
		FALSE, //加不加下划线
		0, //指定是否是字体字符突出
		ANSI_CHARSET, //指定字体的字符集
		OUT_DEFAULT_PRECIS, //指定所需的输出精度
		CLIP_DEFAULT_PRECIS, //指定所需的剪贴精度
		DEFAULT_QUALITY, //指示字体的输出质量
		-2 | 0, //指定字体的间距和家族
		_T("Fixedsys") //指定字体的字样名称
		);

	batteryPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	batBackBrush.CreateSolidBrush(RGB(0, 128, 192));
	batBrush.CreateSolidBrush(RGB(128, 128, 128));
	vaChargeBrush.CreateSolidBrush(initColor.vaChargeCol);
	chargeBrush.CreateSolidBrush(initColor.chargeCol);
	dischargeBrush.CreateSolidBrush(initColor.dischargeCol);
	layBrush.CreateSolidBrush(initColor.layCol);

	regiditBrush.CreateSolidBrush(initColor.storCol);				//	寄存颜色
	currentErrorBrush.CreateSolidBrush(initColor.aerrorCol);		//	电流异常
	voltErrorBrush.CreateSolidBrush(initColor.verrorCol);			//	电压异常
	capacityErrorBrush.CreateSolidBrush(initColor.overAlarmCol);	//	容量异常
	noneBatBrush.CreateSolidBrush(initColor.badContCol);			//	无电池或者电池接触不良
	badBatBrush.CreateSolidBrush(initColor.badBatCol);				//	不良电池
	offVoltBrush.CreateSolidBrush(initColor.offVoltCol);			//	偏离电压异常

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

	//1 画笔
	if (selBrush) delete selBrush;

	batBackBrush.DeleteObject();
	batBrush.DeleteObject();
	vaChargeBrush.DeleteObject();
	chargeBrush.DeleteObject();
	dischargeBrush.DeleteObject();
	layBrush.DeleteObject();

	regiditBrush.DeleteObject();			//	寄存颜色
	currentErrorBrush.DeleteObject();		//	电流异常
	voltErrorBrush.DeleteObject();			//	电压异常
	capacityErrorBrush.DeleteObject();		//	容量异常
	noneBatBrush.DeleteObject();			//	无电池或者电池接触不良
	badBatBrush.DeleteObject();				//	不良电池
	offVoltBrush.DeleteObject();			//	偏离电压异常

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


// CPbatterysDlg 消息处理程序

/*-----------------------------------------------------------------------------
画电池算法
(1) 根据每行来画
-----------------------------------------------------------------------------*/

void CPbatterysDlg::InitPaint(CDC &memDC)
{
	cabinetInfo = cabInfos[curCabId-1];

	this->GetClientRect(&batPicRect);
	
	HDC hdc = memDC.GetSafeHdc();
	//HDC hdc = this->GetDC()->GetSafeHdc();
	//LPTEXTMETRICW fontMetrica;
	//GetTextMetrics(hdc, fontMetrica);
	//fontMetrica->tmExternalLeading = 0;	// 行间距设置为0

	memDC.SetTextCharacterExtra(0);

	FillRect(hdc, batPicRect, batBackBrush);

	//0.2 设置字体 
	//CBrush textBrush(RGB(192, 0, 0));
	memDC.SetTextColor(RGB(0, 255, 0));
	memDC.SetBkMode(TRANSPARENT);
	
	memDC.SelectObject(batIdFont);

	int textMarginTop = 2;
	CString batIdStr;
	int colId;
	//(1) 初始化颜料,pen等工具

	
	CPen *oldPen = memDC.SelectObject(&batteryPen);
	
	//(2) 获取计算每一行的高度、电池的宽度等信息
	this->GetClientRect(batPicRect);

	CRect batPicMainRect = batPicRect;
	batPicMainRect.right -= BATMAIN_MARGIN_RIGHT;

	batteryPane->CalParamter(batPicMainRect);


	//ScreenToClient(batteryPane->paneRect);
	//(3) 初始化电池体和电池帽的位置
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
				memDC.Rectangle(&batteryBodyRect);//绘制矩形
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
				batSeqId++;	// 记录每个cab的bat序列(由1++至N)

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
计算编号 rowId-groupId-subGroupId所在的位置
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
//	// 防止线程长时间占用死掉
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
//	CDC memDC;			//	定义一个显示设备对象
//	CBitmap memBitMap;	//	定义一个位图对象
//
//	// 建立一个与屏幕显示兼容的位图,位图的大小与窗口大小相一致
//	this->GetClientRect(&batPicRect);
//
//	// 建立与屏幕显示兼容的内存显示设备
//	if (memDC.CreateCompatibleDC(&dc)) {
//
//		if (memBitMap.CreateCompatibleBitmap(&dc, batPicRect.Width(), batPicRect.Height()))
//		{
//			// 将位图选入到内存显示设备中
//			if (HGDIOBJ oldBit = memDC.SelectObject(&memBitMap)) {
//				// 拷贝背景图,以处理透明色
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
	// TODO:  在此添加消息处理程序代码和/或调用默认值

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

	// TODO:  在此添加额外的初始化


	// 初始化画笔
	selBatColor = RGB(255, 0, 0);
	selBrush = new CBrush(selBatColor);
	batStateColors.push_back(RGB(128, 128, 128));

	// 初始化BatteryDetailDlg
	//3 电池曲线窗口
	batteryDetailDlg = NULL;


	batPicWnd = CWnd::FromHandle(this->GetSafeHwnd());
	EnableToolTips(TRUE);
	toolTip.Create(this);
	toolTip.Activate(TRUE);
	toolTip.SetTipTextColor(RGB(0, 0, 0));
	toolTip.AddTool(batPicWnd);
	toolTip.SetDelayTime(2111);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

/*
点击电池面板时,选中当前电池,并加以标记,然后弹出相应的框
*/
void CPbatterysDlg::OnStnClickedBatterysPic()
{

}


void CPbatterysDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CMenu   controlMenu;   //定义下面要用到的cmenu对象
	controlMenu.LoadMenu(IDR_CONTROL_MENU); //装载自定义的右键菜单 
	CMenu   *controlContextMenu = controlMenu.GetSubMenu(0); //获取第一个弹出菜单，所以第一个菜单必须有子菜单 
	CRect rect;
	this->GetClientRect(&rect);
	ClientToScreen(&rect);

	POINT point1;
	::GetCursorPos(&point1);

	if (point1.x >= rect.left && point1.x <= rect.right
		&& point1.y >= rect.top && point1.y <= rect.bottom)
	{
		controlContextMenu->TrackPopupMenu(TPM_LEFTALIGN, point1.x, point1.y, AfxGetMainWnd()); //在指定位置显示弹出菜单
	}

	CDialog::OnRButtonDown(nFlags, point);
}


void CPbatterysDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	
	// 防止线程长时间占用死掉
	MSG msg;
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			return;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	//1.0 计算当前编号
	if (!CanConnFlag || !PortOpenFlag)
	{
		AfxMessageBox(L"端口未打开或者未发送工序信息，请确认后重试！");
		return;
	}

	int x = point.x;
	int y = point.y;

	int rowId = (y + batteryPane->GetBatteryRowHeight() - 1) / batteryPane->GetBatteryRowHeight();
	int groupId = (x + batteryPane->GetGroupWidth() - 1) / batteryPane->GetGroupWidth();
	int subGroupId = (x - (groupId - 1)*batteryPane->GetGroupWidth() -
		batteryPane->GetGroupBlankWidth() + batteryPane->GetBatteryWidth() - 1) / batteryPane->GetBatteryWidth();

	// 计算电池编号,供电池细节使用
	curRowId = rowId;
	curGroupId = groupId;
	curGroupInnerId = subGroupId;
	if (paneId == _T(BACK_PANE))
		curRowId += cabinetInfo.groupNumPerCol;
	curBatteryId = (curRowId - 1)*cabinetInfo.numPerGroup + (curGroupId - 1)*SUBGROUP_NUM + curGroupInnerId;


	CRect preCapRect;
	CRect curCapRect;
	HDC hdc = this->GetDC()->GetSafeHdc();
	//1.1 清除当前页面上的矩形(电池帽)
	if (!(preSelRowId == rowId && preSelGroupId == groupId && preSelSubGroupId == subGroupId)
		&& subGroupId > 0 && subGroupId <= batteryPane->GetSubGroupBatNum())
	{
		if (!(preSelRowId == 0 && preSelGroupId == 0 && preSelSubGroupId == 0))
		{
			//1.1 清除当前页面上的矩形(电池帽
			preCapRect = CalSpecBatteryCap(preSelRowId, preSelGroupId, preSelSubGroupId);
			FillRect(hdc, preCapRect, CBrush(batStateColors[0]));
		}
		//1.2 画当前选中的电池所在的矩形
		curCapRect = CalSpecBatteryCap(rowId, groupId, subGroupId);
		FillRect(hdc, curCapRect, *selBrush);

		preSelRowId = rowId;
		preSelGroupId = groupId;
		preSelSubGroupId = subGroupId;
	}
	//2 弹出框
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
	// TODO:  在此添加命令处理程序代码
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
	// TODO:  在此添加专用代码和/或调用基类

	return CDialog::accDoDefaultAction(varChild);
}

void CPbatterysDlg::DoPaint()
{
	CDC *dc = GetDC();

	CDC memDC;			//	定义一个显示设备对象
	CBitmap memBitMap;	//	定义一个位图对象

	// 建立一个与屏幕显示兼容的位图,位图的大小与窗口大小相一致
	this->GetClientRect(&batPicRect);

	// 建立与屏幕显示兼容的内存显示设备
	if (memDC.CreateCompatibleDC(dc)) {

		if (memBitMap.CreateCompatibleBitmap(dc, batPicRect.Width(), batPicRect.Height()))
		{
			// 将位图选入到内存显示设备中
			if (HGDIOBJ oldBit = memDC.SelectObject(&memBitMap)) {
				// 拷贝背景图,以处理透明色
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


