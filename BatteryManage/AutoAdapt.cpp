#include "stdafx.h"
#include "AutoAdapt.h"

/*
MFC�ؼ�����Ӧ���ڴ�С
ʹ�÷�����
��Ŀ��������Ӵ����Ա
��Ŀ���ʼ�������е���InitSize����//������Լ�����
��WM_SIZE��Ϣ�������е���ReSize
*/
CAutoAdapt::CAutoAdapt(void)
{

}


CAutoAdapt::~CAutoAdapt(void)
{

}

//�˺���Ҳ���Բ�����,���Լ�����,������Ӵ��� ����tableCtrl�еĴ���,����������� ������tableCtrl��С  
//�ڳ�ʼ����������Ӵ˺���   
void CAutoAdapt::InitSize(HWND m_hWnd)
{
	CRect rect;
	GetClientRect(m_hWnd, &rect);     //ȡ�ͻ�����С    

	old.x = rect.right - rect.left;
	old.y = rect.bottom - rect.top;
	int cx = GetSystemMetrics(SM_CXFULLSCREEN);
	int cy = GetSystemMetrics(SM_CYFULLSCREEN);
	CRect rt;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rt, 0);
	cy = rt.bottom;
	MoveWindow(m_hWnd, 0, 0, cx, cy, TRUE);
}

//��WM_SIZE��Ϣ������������������  
void CAutoAdapt::ReSize(HWND m_hWnd)
{
	float fsp[2];
	POINT Newp; //��ȡ���ڶԻ���Ĵ�С    
	CRect recta;
	GetClientRect(m_hWnd, &recta);     //ȡ�ͻ�����С      
	Newp.x = recta.right - recta.left;
	Newp.y = recta.bottom - recta.top;
	//��ñ���  
	fsp[0] = (float)Newp.x / old.x;
	fsp[1] = (float)Newp.y / old.y;

	CRect Rect;
	int woc;  //�ؼ���ʾ  
	CPoint OldTLPoint, TLPoint; //���Ͻ�    
	CPoint OldBRPoint, BRPoint; //���½�    

	HWND  hwndChild = ::GetWindow(m_hWnd, GW_CHILD);  //�г����пؼ�    

	while (hwndChild)
	{
		woc = ::GetDlgCtrlID(hwndChild);//ȡ��ID
		HWND hCtrl = GetDlgItem(m_hWnd, woc);
		
		//if (woc == IDOK || woc == IDCANCEL)
		//{
		//	hCtrl->unused = TRUE;
		//}
		//else
		//{
			GetWindowRect(hCtrl, &Rect);
			//�������Ͻ�����  
			POINT point;
			point = Rect.TopLeft();
			ScreenToClient(m_hWnd, &point);

			OldTLPoint = point;
			TLPoint.x = long(OldTLPoint.x*fsp[0]);
			TLPoint.y = long(OldTLPoint.y*fsp[1]);

			//�������½�����  
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
