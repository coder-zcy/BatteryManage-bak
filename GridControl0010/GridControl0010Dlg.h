
// GridControl0010Dlg.h : ͷ�ļ�
//

#pragma once
//#include"GridCtrl_src\GridCtrl.h"
#include "GridCtrl_src\GridCtrl.h"


// CGridControl0010Dlg �Ի���
class CGridControl0010Dlg : public CDialogEx
{
// ����
public:
	CGridControl0010Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GRIDCONTROL0010_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:


	CGridCtrl m_pGrid;
	void GridCtrlInit();
};
