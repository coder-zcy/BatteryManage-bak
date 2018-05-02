#include "BatteryPane.h"
#include "afxwin.h"

#include "BatteryDetailDlg.h"
#include "Battery.h"

#include <iostream>
#include <vector>

using namespace std;

#define BATMAIN_MARGIN_RIGHT 10

// ���õ��״̬�ĸ���Ϊ16
#define STATE_NUM 16

// CPbatterysDlg �Ի���

class CPbatterysDlg : public CDialog
{
	DECLARE_DYNAMIC(CPbatterysDlg)

public:
	CPbatterysDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPbatterysDlg();

	// �Ի�������
	enum { IDD = IDD_PBATTERYS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CBatteryPane *batteryPane;
	// ��������
	BOOL batteryTrack;
	//CTipDlg *ptipDlg;
	int preRowId;
	int preGroupId;
	int preSubGroupId;

	int preSelRowId;
	int preSelGroupId;
	int preSelSubGroupId;

	int paintFactor;
	//CToolTipCtrl  toolTip;
	CToolTipCtrl toolTip;
	CWnd* batPicWnd;
	COLORREF selBatColor;
	vector<COLORREF> batStateColors;
	CBrush* selBrush;

	//
	CabinetInfo cabinetInfo;
	//3 ������ߴ���
	CBatteryDetailDlg *batteryDetailDlg;


	afx_msg void OnPaint();

	void DoPaint();

	CRect batPicRect;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	BOOL initFlag;
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	//afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//afx_msg       LRESULT     OnMouseLeave(WPARAM, LPARAM);
	//afx_msg       LRESULT     OnMouseHover(WPARAM, LPARAM);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	CabinetInfo GetCabInfoByCurId(int cabId);

	CFont batIdFont;
	CFont batStateFont;

	void InitPaint(CDC &memDC);

	CRect CalSpecBatteryCap(int rowId, int groupId, int subGroupId);

	afx_msg void OnStnClickedBatterysPic();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	
	afx_msg void OnShowStepData();


	// �������ݿ�Ķ���
	_ConnectionPtr pConnection;
	_CommandPtr pCommand;
	_RecordsetPtr pRecordset;

	HRESULT hr;

	CBrush vaChargeBrush;		//	������ѹ���
	CBrush chargeBrush;			//	�������
	CBrush dischargeBrush;		//	�����ŵ�
	CBrush layBrush;			//	����

	CBrush regiditBrush;		//	�Ĵ���ɫ
	CBrush currentErrorBrush;	//	�����쳣
	CBrush voltErrorBrush;		//	��ѹ�쳣
	CBrush capacityErrorBrush;	//	�����쳣
	CBrush noneBatBrush;		//	�޵�ػ��ߵ�ؽӴ�����
	CBrush badBatBrush;			//	�������
	CBrush offVoltBrush;		//	ƫ��������ѹ�쳣

	CBrush *batCabBrushs[STATE_NUM];
	CBrush *batBrushs[STATE_NUM];
	CBrush batBrush;
	CBrush batBackBrush;		//	��ر���Brush
	CPen batteryPen;



	virtual HRESULT accDoDefaultAction(VARIANT varChild);

};
