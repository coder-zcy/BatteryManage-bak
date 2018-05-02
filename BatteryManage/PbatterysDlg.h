#include "BatteryPane.h"
#include "afxwin.h"

#include "BatteryDetailDlg.h"
#include "Battery.h"

#include <iostream>
#include <vector>

using namespace std;

#define BATMAIN_MARGIN_RIGHT 10

// 设置电池状态的个数为16
#define STATE_NUM 16

// CPbatterysDlg 对话框

class CPbatterysDlg : public CDialog
{
	DECLARE_DYNAMIC(CPbatterysDlg)

public:
	CPbatterysDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPbatterysDlg();

	// 对话框数据
	enum { IDD = IDD_PBATTERYS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CBatteryPane *batteryPane;
	// 悬浮窗口
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
	//3 电池曲线窗口
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


	// 连接数据库的东西
	_ConnectionPtr pConnection;
	_CommandPtr pCommand;
	_RecordsetPtr pRecordset;

	HRESULT hr;

	CBrush vaChargeBrush;		//	恒流恒压充电
	CBrush chargeBrush;			//	恒流充电
	CBrush dischargeBrush;		//	恒流放电
	CBrush layBrush;			//	搁置

	CBrush regiditBrush;		//	寄存颜色
	CBrush currentErrorBrush;	//	电流异常
	CBrush voltErrorBrush;		//	电压异常
	CBrush capacityErrorBrush;	//	容量异常
	CBrush noneBatBrush;		//	无电池或者电池接触不良
	CBrush badBatBrush;			//	不良电池
	CBrush offVoltBrush;		//	偏离正常电压异常

	CBrush *batCabBrushs[STATE_NUM];
	CBrush *batBrushs[STATE_NUM];
	CBrush batBrush;
	CBrush batBackBrush;		//	电池背景Brush
	CPen batteryPen;



	virtual HRESULT accDoDefaultAction(VARIANT varChild);

};
