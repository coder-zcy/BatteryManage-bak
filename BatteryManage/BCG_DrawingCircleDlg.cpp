// BCG_DrawingCircleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "BCG_DrawingCircleDlg.h"
#include "afxdialogex.h"

//37是每8个电池之间有空隙
#define row_divide 37
#define col_divide 16
#define row_batter_num 32
#define col_batter_num 16
// CBCG_DrawingCircleDlg 对话框

IMPLEMENT_DYNAMIC(CBCG_DrawingCircleDlg, CDialog)

CBCG_DrawingCircleDlg::CBCG_DrawingCircleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBCG_DrawingCircleDlg::IDD, pParent)
{

}

CBCG_DrawingCircleDlg::~CBCG_DrawingCircleDlg()
{
}

void CBCG_DrawingCircleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BCG_StaticNum1, seqStatic1);
	DDX_Control(pDX, IDC_BCG_StaticNum2, seqStatic2);
	DDX_Control(pDX, IDC_BCG_StaticNum3, seqStatic3);
	DDX_Control(pDX, IDC_BCG_StaticNum4, seqStatic4);
	DDX_Control(pDX, IDC_BCG_StaticNum5, seqStatic5);
	DDX_Control(pDX, IDC_BCG_StaticNum6, seqStatic6);
	DDX_Control(pDX, IDC_BCG_StaticNum7, seqStatic7);
	DDX_Control(pDX, IDC_BCG_StaticNum8, seqStatic8);
	DDX_Control(pDX, IDC_BCG_StaticNum9, seqStatic9);
	DDX_Control(pDX, IDC_BCG_StaticNum10, seqStatic10);
	DDX_Control(pDX, IDC_BCG_StaticNum11, seqStatic11);
	DDX_Control(pDX, IDC_BCG_StaticNum12, seqStatic12);
	DDX_Control(pDX, IDC_BCG_StaticNum13, seqStatic13);
	DDX_Control(pDX, IDC_BCG_StaticNum14, seqStatic14);
	DDX_Control(pDX, IDC_BCG_StaticNum15, seqStatic15);
	DDX_Control(pDX, IDC_BCG_StaticNum16, seqStatic16);
}


BEGIN_MESSAGE_MAP(CBCG_DrawingCircleDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CBCG_DrawingCircleDlg 消息处理程序

BOOL CBCG_DrawingCircleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	seqStatics.clear();
	seqStatics.push_back(&seqStatic1);
	seqStatics.push_back(&seqStatic2);
	seqStatics.push_back(&seqStatic3);
	seqStatics.push_back(&seqStatic4);
	seqStatics.push_back(&seqStatic5);
	seqStatics.push_back(&seqStatic6);
	seqStatics.push_back(&seqStatic7);
	seqStatics.push_back(&seqStatic8);
	seqStatics.push_back(&seqStatic9);
	seqStatics.push_back(&seqStatic10);
	seqStatics.push_back(&seqStatic11);
	seqStatics.push_back(&seqStatic12);
	seqStatics.push_back(&seqStatic13);
	seqStatics.push_back(&seqStatic14);
	seqStatics.push_back(&seqStatic15);
	seqStatics.push_back(&seqStatic16);

	oldsel_row = 0;
	oldsel_col = 0;


	DrawCycle();

	//ShowWindow(SW_MAXIMIZE);//对话框默认最大化弹出

	return TRUE;
}


//void CBCG_DrawingCircleDlg::OnSize(UINT nType, int cx, int cy)
//{
//	CDialog::OnSize(nType, cx, cy);
//
//	// TODO:  在此处添加消息处理程序代码
//	//清空全部matrix的圆的信息，重新录入
//	draw_matrix.clear();
//
//	// TODO:  在此处添加消息处理程序代码
//	// 重新画圆，根据改变窗口的大小
//	vector<battery_info> en_queue;
//	int x_step = cx / row_divide;
//	int y_step = cy / col_divide;
//	int cur_left = 0;
//	int cur_top = 0;
//	float ajust_parameter = 0.45;
//	for (int i = 0; i < col_batter_num; ++i)
//	{
//		cur_left = x_step;
//		for (int j = 0; j < row_batter_num; ++j)
//		{
//			if (0 == j) cur_left = 0;
//			else if (0 == j % 8) cur_left += x_step;
//
//			CRect sel_area(cur_left, cur_top, cur_left + x_step, cur_top + y_step);
//			int central_x = (cur_left * 2 + x_step) / 2;
//			int central_y = (cur_top * 2 + y_step) / 2;
//			int cir_step = (x_step > y_step) ? y_step : x_step;
//			CRect circle_area(central_x - ajust_parameter*cir_step, central_y - ajust_parameter*cir_step, central_x + ajust_parameter*cir_step, central_y + ajust_parameter*cir_step);
//
//			battery_info tmp;
//			tmp.circle_area = circle_area;
//			tmp.select_area = sel_area;
//
//			en_queue.push_back(tmp);
//			cur_left += x_step;
//		}
//		draw_matrix.push_back(en_queue);
//		en_queue.clear();
//		cur_top += y_step;
//	}
//
//	Invalidate();
//}

void CBCG_DrawingCircleDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	//清空全部matrix的圆的信息，重新录入
	draw_matrix.clear();

	// TODO:  在此处添加消息处理程序代码
	// 重新画圆，根据改变窗口的大小
	DrawCycle();

	Invalidate();
}

void CBCG_DrawingCircleDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CDialog::OnLButtonDown(nFlags, point);
	draw_matrix[oldsel_row][oldsel_col].isSel = FALSE;

	CRect rect;
	GetClientRect(&rect);
	int x_step = (rect.right - rect.left) / 37;
	int y_step = (rect.bottom - rect.top) / 16;
	//获取行位置是正常的，修改列位置
	int idx_y = point.y / y_step;
	for (int i = 0; i < 32; ++i){
		if (point.x < draw_matrix[idx_y][i].select_area.right && point.x > draw_matrix[idx_y][i].select_area.left)
		{
			draw_matrix[idx_y][i].isSel = TRUE;
			oldsel_row = idx_y;
			oldsel_col = i;
		}
	}
	Invalidate();
}


void CBCG_DrawingCircleDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()


	//CRect   rect;
	//GetWindowRect(&rect);//得到所处窗口的绝对坐标;    
	//GetClientRect(&rect);//得到相对坐标
	for (int i = 0; i < col_batter_num; ++i)
	{
		for (int j = 0; j < row_batter_num; ++j)
		{
			CBrush brush;
			if (false == draw_matrix[i][j].isSel){
				//brush = CBrush(RGB(255, 0, 255));
				//brush.CreateSolidBrush(RGB(255, 0, 255));
				brush.CreateSolidBrush(selLightColor);
				
			}
			else
			{
				//brush = CBrush(RGB(255, 255, 255));
				brush.CreateSolidBrush(defLightColor);
			}

			dc.SelectObject(&brush);//返回的是之前用过的Object
			dc.Ellipse(draw_matrix[i][j].circle_area);
		}
	}
}

void CBCG_DrawingCircleDlg::LightPane(int *batLevelStats, int batCount, int gradeId)
{
	int rowIdx, colIdx;

	for (int idx = 0; idx < batCount; ++idx)
	{
		rowIdx = idx / row_batter_num;
		colIdx = idx % row_batter_num;

		if (batLevelStats[idx] == gradeId)
			draw_matrix[rowIdx][colIdx].isSel = TRUE;
		else
			draw_matrix[rowIdx][colIdx].isSel = FALSE;
	}

	Invalidate();
}

void CBCG_DrawingCircleDlg::DrawCycle()
{
	CRect rect;
	vector<battery_info> en_queue;
	GetClientRect(&rect);//获取该窗口的大小


	int x = 0; int y = 0;
	int draw_y_step = (rect.bottom - rect.top) / 16;
	x = 0; y = (rect.bottom - rect.top) /(2 * col_divide) - 7;
	
	int x_margin = 22;

	for (int idx = 0; idx < seqStatics.size(); ++idx)
	{
		if (seqStatics[idx] && seqStatics[idx]->m_hWnd)
		seqStatics[idx]->MoveWindow(x, y + idx*draw_y_step, 20, 20);
	}

	int x_step = (rect.right - rect.left) / row_divide;
	int y_step = (rect.bottom - rect.top) / col_divide;
	int cur_left = 8;
	int cur_top = 0;
	float ajust_parameter = 0.45;
	for (int i = 0; i < col_batter_num; ++i)
	{
		cur_left = 8;
		for (int j = 0; j < row_batter_num; ++j)
		{
			if (0 == j % 8) cur_left += x_step;
			CRect sel_area(cur_left, cur_top, cur_left + x_step, cur_top + y_step);
			int central_x = (cur_left * 2 + x_step) / 2;
			int central_y = (cur_top * 2 + y_step) / 2;
			int cir_step = (x_step > y_step) ? y_step : x_step;
			CRect circle_area(central_x - ajust_parameter*cir_step,
				central_y - ajust_parameter*cir_step,
				central_x + ajust_parameter*cir_step,
				central_y + ajust_parameter*cir_step);

			battery_info tmp;
			tmp.circle_area = circle_area;
			tmp.select_area = sel_area;

			en_queue.push_back(tmp);
			cur_left += x_step;
		}
		draw_matrix.push_back(en_queue);
		en_queue.clear();
		cur_top += y_step;
	}
}
