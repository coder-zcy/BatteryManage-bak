#include "stdafx.h"
#include "AutoAdapt.h"

/*
MFC控件自适应窗口大小
使用方法：
在目标类中添加此类成员
在目标初始化函数中调用InitSize函数//这个看自己需求
在WM_SIZE消息处理函数中调用ReSize
*/
CAutoAdapt::CAutoAdapt(void)
{

}


CAutoAdapt::~CAutoAdapt(void)
{

}

//此函数也可以不调用,看自己需求,如果是子窗口 比如tableCtrl中的窗口,调用这个函数 就填满tableCtrl大小  
//在初始化函数中添加此函数   
void CAutoAdapt::InitSize(HWND m_hWnd)
{
	CRect rect;
	GetClientRect(m_hWnd, &rect);     //取客户区大小    

	old.x = rect.right - rect.left;
	old.y = rect.bottom - rect.top;
	int cx = GetSystemMetrics(SM_CXFULLSCREEN);
	int cy = GetSystemMetrics(SM_CYFULLSCREEN);
	CRect rt;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rt, 0);
	cy = rt.bottom;
	MoveWindow(m_hWnd, 0, 0, cx, cy, TRUE);
}

//在WM_SIZE消息处理函数中添加这个函数  
void CAutoAdapt::ReSize(HWND m_hWnd)
{
	float fsp[2];
	POINT Newp; //获取现在对话框的大小    
	CRect recta;
	GetClientRect(m_hWnd, &recta);     //取客户区大小      
	Newp.x = recta.right - recta.left;
	Newp.y = recta.bottom - recta.top;
	//获得倍数  
	fsp[0] = (float)Newp.x / old.x;
	fsp[1] = (float)Newp.y / old.y;

	CRect Rect;
	int woc;  //控件标示  
	CPoint OldTLPoint, TLPoint; //左上角    
	CPoint OldBRPoint, BRPoint; //右下角    

	HWND  hwndChild = ::GetWindow(m_hWnd, GW_CHILD);  //列出所有控件    

	while (hwndChild)
	{
		woc = ::GetDlgCtrlID(hwndChild);//取得ID
		HWND hCtrl = GetDlgItem(m_hWnd, woc);
		
		//if (woc == IDOK || woc == IDCANCEL)
		//{
		//	hCtrl->unused = TRUE;
		//}
		//else
		//{
			GetWindowRect(hCtrl, &Rect);
			//处理左上角坐标  
			POINT point;
			point = Rect.TopLeft();
			ScreenToClient(m_hWnd, &point);

			OldTLPoint = point;
			TLPoint.x = long(OldTLPoint.x*fsp[0]);
			TLPoint.y = long(OldTLPoint.y*fsp[1]);

			//处理右下角坐标  
			point = Rect.BottomRight();
			ScreenToClient(m_hWnd, &point);

			OldBRPoint = point;
			BRPoint.x = long(OldBRPoint.x *fsp[0]);
			BRPoint.y = long(OldBRPoint.y *fsp[1]);

			Rect.SetRect(TLPoint, BRPoint);

			MoveWindow(hCtrl, TLPoint.x, TLPoint.y, BRPoint.x - TLPoint.x, BRPoint.y - TLPoint.y, TRUE);
	/*	}*/

		hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
	}
	old = Newp;
}
