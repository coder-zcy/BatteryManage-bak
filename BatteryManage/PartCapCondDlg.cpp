// PartCapCondDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatteryManage.h"
#include "PartCapCondDlg.h"
#include "afxdialogex.h"


// CPartCapCondDlg 对话框

IMPLEMENT_DYNAMIC(CPartCapCondDlg, CDialog)

// CColorDlg 消息处理程序
CArray <COLORREF> colorArray;

void InitColor2(CStatic &pic, COLORREF color)
{
	colorArray.Add(color);
	CRect prect;
	CBrush initBrush(color);
	pic.GetClientRect(&prect);   //获取区域
	FillRect(pic.GetDC()->GetSafeHdc(), &prect, initBrush);

	initBrush.DeleteObject();
}

CPartCapCondDlg::CPartCapCondDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPartCapCondDlg::IDD, pParent)
{
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

	minEdits.push_back(&minEdit1);
	minEdits.push_back(&minEdit2);
	minEdits.push_back(&minEdit3);
	minEdits.push_back(&minEdit4);
	minEdits.push_back(&minEdit5);
	minEdits.push_back(&minEdit6);
	minEdits.push_back(&minEdit7);
	minEdits.push_back(&minEdit8);
	minEdits.push_back(&minEdit9);
	minEdits.push_back(&minEdit10);
	minEdits.push_back(&minEdit11);
	minEdits.push_back(&minEdit12);
	minEdits.push_back(&minEdit13);
	minEdits.push_back(&minEdit14);
	minEdits.push_back(&minEdit15);
	minEdits.push_back(&minEdit16);

	maxEdits.push_back(&maxEdit1);
	maxEdits.push_back(&maxEdit2);
	maxEdits.push_back(&maxEdit3);
	maxEdits.push_back(&maxEdit4);
	maxEdits.push_back(&maxEdit5);
	maxEdits.push_back(&maxEdit6);
	maxEdits.push_back(&maxEdit7);
	maxEdits.push_back(&maxEdit8);
	maxEdits.push_back(&maxEdit9);
	maxEdits.push_back(&maxEdit10);
	maxEdits.push_back(&maxEdit11);
	maxEdits.push_back(&maxEdit12);
	maxEdits.push_back(&maxEdit13);
	maxEdits.push_back(&maxEdit14);
	maxEdits.push_back(&maxEdit15);
	maxEdits.push_back(&maxEdit16);

	flagEdits.push_back(&flagEdit1);
	flagEdits.push_back(&flagEdit2);
	flagEdits.push_back(&flagEdit3);
	flagEdits.push_back(&flagEdit4);
	flagEdits.push_back(&flagEdit5);
	flagEdits.push_back(&flagEdit6);
	flagEdits.push_back(&flagEdit7);
	flagEdits.push_back(&flagEdit8);
	flagEdits.push_back(&flagEdit9);
	flagEdits.push_back(&flagEdit10);
	flagEdits.push_back(&flagEdit11);
	flagEdits.push_back(&flagEdit12);
	flagEdits.push_back(&flagEdit13);
	flagEdits.push_back(&flagEdit14);
	flagEdits.push_back(&flagEdit15);
	flagEdits.push_back(&flagEdit16);
}

CPartCapCondDlg::~CPartCapCondDlg()
{
}

void CPartCapCondDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MIN_EDIT1, minEdit1);
	DDX_Control(pDX, IDC_MIN_EDIT2, minEdit2);
	DDX_Control(pDX, IDC_MIN_EDIT3, minEdit3);
	DDX_Control(pDX, IDC_MIN_EDIT4, minEdit4);
	DDX_Control(pDX, IDC_MIN_EDIT5, minEdit5);
	DDX_Control(pDX, IDC_MIN_EDIT6, minEdit6);
	DDX_Control(pDX, IDC_MIN_EDIT7, minEdit7);
	DDX_Control(pDX, IDC_MIN_EDIT8, minEdit8);
	DDX_Control(pDX, IDC_MIN_EDIT9, minEdit9);
	DDX_Control(pDX, IDC_MIN_EDIT10, minEdit10);
	DDX_Control(pDX, IDC_MIN_EDIT11, minEdit11);
	DDX_Control(pDX, IDC_MIN_EDIT12, minEdit12);
	DDX_Control(pDX, IDC_MIN_EDIT13, minEdit13);
	DDX_Control(pDX, IDC_MIN_EDIT14, minEdit14);
	DDX_Control(pDX, IDC_MIN_EDIT15, minEdit15);
	DDX_Control(pDX, IDC_MIN_EDIT16, minEdit16);
	DDX_Control(pDX, IDC_MAX_EDIT1, maxEdit1);
	DDX_Control(pDX, IDC_MAX_EDIT2, maxEdit2);
	DDX_Control(pDX, IDC_MAX_EDIT3, maxEdit3);
	DDX_Control(pDX, IDC_MAX_EDIT4, maxEdit4);
	DDX_Control(pDX, IDC_MAX_EDIT5, maxEdit5);
	DDX_Control(pDX, IDC_MAX_EDIT6, maxEdit6);
	DDX_Control(pDX, IDC_MAX_EDIT7, maxEdit7);
	DDX_Control(pDX, IDC_MAX_EDIT8, maxEdit8);
	DDX_Control(pDX, IDC_MAX_EDIT9, maxEdit9);
	DDX_Control(pDX, IDC_MAX_EDIT10, maxEdit10);
	DDX_Control(pDX, IDC_MAX_EDIT11, maxEdit11);
	DDX_Control(pDX, IDC_MAX_EDIT12, maxEdit12);
	DDX_Control(pDX, IDC_MAX_EDIT13, maxEdit13);
	DDX_Control(pDX, IDC_MAX_EDIT14, maxEdit14);
	DDX_Control(pDX, IDC_MAX_EDIT15, maxEdit15);
	DDX_Control(pDX, IDC_MAX_EDIT16, maxEdit16);
	DDX_Control(pDX, IDC_FLAG_EDIT1, flagEdit1);
	DDX_Control(pDX, IDC_FLAG_EDIT2, flagEdit2);
	DDX_Control(pDX, IDC_FLAG_EDIT3, flagEdit3);
	DDX_Control(pDX, IDC_FLAG_EDIT4, flagEdit4);
	DDX_Control(pDX, IDC_FLAG_EDIT5, flagEdit5);
	DDX_Control(pDX, IDC_FLAG_EDIT6, flagEdit6);
	DDX_Control(pDX, IDC_FLAG_EDIT7, flagEdit7);
	DDX_Control(pDX, IDC_FLAG_EDIT8, flagEdit8);
	DDX_Control(pDX, IDC_FLAG_EDIT9, flagEdit9);
	DDX_Control(pDX, IDC_FLAG_EDIT10, flagEdit10);
	DDX_Control(pDX, IDC_FLAG_EDIT11, flagEdit11);
	DDX_Control(pDX, IDC_FLAG_EDIT12, flagEdit12);
	DDX_Control(pDX, IDC_FLAG_EDIT13, flagEdit13);
	DDX_Control(pDX, IDC_FLAG_EDIT14, flagEdit14);
	DDX_Control(pDX, IDC_FLAG_EDIT15, flagEdit15);
	DDX_Control(pDX, IDC_FLAG_EDIT16, flagEdit16);
	DDX_Control(pDX, IDC_COLOR_PIC1, colorPic1);
	DDX_Control(pDX, IDC_COLOR_PIC2, colorPic2);
	DDX_Control(pDX, IDC_COLOR_PIC3, colorPic3);
	DDX_Control(pDX, IDC_COLOR_PIC4, colorPic4);
	DDX_Control(pDX, IDC_COLOR_PIC5, colorPic5);
	DDX_Control(pDX, IDC_COLOR_PIC6, colorPic6);
	DDX_Control(pDX, IDC_COLOR_PIC7, colorPic7);
	DDX_Control(pDX, IDC_COLOR_PIC8, colorPic8);
	DDX_Control(pDX, IDC_COLOR_PIC9, colorPic9);
	DDX_Control(pDX, IDC_COLOR_PIC10, colorPic10);
	DDX_Control(pDX, IDC_COLOR_PIC11, colorPic11);
	DDX_Control(pDX, IDC_COLOR_PIC12, colorPic12);
	DDX_Control(pDX, IDC_COLOR_PIC13, colorPic13);
	DDX_Control(pDX, IDC_COLOR_PIC14, colorPic14);
	DDX_Control(pDX, IDC_COLOR_PIC15, colorPic15);
	DDX_Control(pDX, IDC_COLOR_PIC16, colorPic16);
	DDX_Control(pDX, IDC_SEQ_STATIC, seqStatic);
	DDX_Control(pDX, IDC_MIN_STATIC, minStatic);
	DDX_Control(pDX, IDC_MAX_STATIC, maxStatic);
	DDX_Control(pDX, IDC_COLOR_STATIC, colorStatic);
	DDX_Control(pDX, IDC_FLAG_STATIC, flagStatic);
	DDX_Control(pDX, IDC_SEQ_ID1, seqStatic1);
	DDX_Control(pDX, IDC_SEQ_ID2, seqStatic2);
	DDX_Control(pDX, IDC_SEQ_ID3, seqStatic3);
	DDX_Control(pDX, IDC_SEQ_ID4, seqStatic4);
	DDX_Control(pDX, IDC_SEQ_ID5, seqStatic5);
	DDX_Control(pDX, IDC_SEQ_ID6, seqStatic6);
	DDX_Control(pDX, IDC_SEQ_ID7, seqStatic7);
	DDX_Control(pDX, IDC_SEQ_ID8, seqStatic8);
	DDX_Control(pDX, IDC_SEQ_ID9, seqStatic9);
	DDX_Control(pDX, IDC_SEQ_ID10, seqStatic10);
	DDX_Control(pDX, IDC_SEQ_ID11, seqStatic11);
	DDX_Control(pDX, IDC_SEQ_ID12, seqStatic12);
	DDX_Control(pDX, IDC_SEQ_ID13, seqStatic13);
	DDX_Control(pDX, IDC_SEQ_ID14, seqStatic14);
	DDX_Control(pDX, IDC_SEQ_ID15, seqStatic15);
	DDX_Control(pDX, IDC_SEQ_ID16, seqStatic16);
	DDX_Control(pDX, IDC_PART_CODE_COMBO, partCodeCom);
}


BEGIN_MESSAGE_MAP(CPartCapCondDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CPartCapCondDlg::OnBnClickedOk)
	ON_WM_PAINT()
	ON_STN_CLICKED(IDC_COLOR_PIC1, &CPartCapCondDlg::OnStnClickedColorPic1)
	ON_STN_CLICKED(IDC_COLOR_PIC2, &CPartCapCondDlg::OnStnClickedColorPic2)
	ON_STN_CLICKED(IDC_COLOR_PIC3, &CPartCapCondDlg::OnStnClickedColorPic3)
	ON_STN_CLICKED(IDC_COLOR_PIC4, &CPartCapCondDlg::OnStnClickedColorPic4)
	ON_STN_CLICKED(IDC_COLOR_PIC5, &CPartCapCondDlg::OnStnClickedColorPic5)
	ON_STN_CLICKED(IDC_COLOR_PIC6, &CPartCapCondDlg::OnStnClickedColorPic6)
	ON_STN_CLICKED(IDC_COLOR_PIC7, &CPartCapCondDlg::OnStnClickedColorPic7)
	ON_STN_CLICKED(IDC_COLOR_PIC8, &CPartCapCondDlg::OnStnClickedColorPic8)
	ON_STN_CLICKED(IDC_COLOR_PIC9, &CPartCapCondDlg::OnStnClickedColorPic9)
	ON_STN_CLICKED(IDC_COLOR_PIC10, &CPartCapCondDlg::OnStnClickedColorPic10)
	ON_STN_CLICKED(IDC_COLOR_PIC11, &CPartCapCondDlg::OnStnClickedColorPic11)
	ON_STN_CLICKED(IDC_COLOR_PIC12, &CPartCapCondDlg::OnStnClickedColorPic12)
	ON_STN_CLICKED(IDC_COLOR_PIC13, &CPartCapCondDlg::OnStnClickedColorPic13)
	ON_STN_CLICKED(IDC_COLOR_PIC14, &CPartCapCondDlg::OnStnClickedColorPic14)
	ON_STN_CLICKED(IDC_COLOR_PIC15, &CPartCapCondDlg::OnStnClickedColorPic15)
	ON_STN_CLICKED(IDC_COLOR_PIC16, &CPartCapCondDlg::OnStnClickedColorPic16)
END_MESSAGE_MAP()


// CPartCapCondDlg 消息处理程序


BOOL CPartCapCondDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitAssembly();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CPartCapCondDlg::InitAssembly()
{
	CapShowType *capShowType = CapShowType::GetInstance();

	CRect seqRect, minRect, maxRect, colorRect, flagRect;
	vector<CRect> seqRects, minRects, maxRects, colorRects, flagRects;

	seqStatic1.GetWindowRect(seqRect);
	minEdit1.GetWindowRect(minRect);
	maxEdit1.GetWindowRect(maxRect);
	colorPic1.GetWindowRect(colorRect);
	flagEdit1.GetWindowRect(flagRect);
	
	
	colorPics.clear();
	colorPics.push_back(&colorPic1);
	colorPics.push_back(&colorPic2);
	colorPics.push_back(&colorPic3);
	colorPics.push_back(&colorPic4);
	colorPics.push_back(&colorPic5);
	colorPics.push_back(&colorPic6);
	colorPics.push_back(&colorPic7);
	colorPics.push_back(&colorPic8);
	colorPics.push_back(&colorPic9);
	colorPics.push_back(&colorPic10);
	colorPics.push_back(&colorPic11);
	colorPics.push_back(&colorPic12);
	colorPics.push_back(&colorPic13);
	colorPics.push_back(&colorPic14);
	colorPics.push_back(&colorPic15);
	colorPics.push_back(&colorPic16);

	partCodeCom.AddString(L"当前");

	seqRect.top -= DEF_TOP_MARGIN;
	seqRect.bottom -= DEF_TOP_MARGIN;
	minRect.top -= DEF_TOP_MARGIN;
	minRect.bottom -= DEF_TOP_MARGIN;
	maxRect.top -= DEF_TOP_MARGIN;
	maxRect.bottom -= DEF_TOP_MARGIN;
	colorRect.top -= DEF_TOP_MARGIN;
	colorRect.bottom -= DEF_TOP_MARGIN;
	flagRect.top -= DEF_TOP_MARGIN;
	flagRect.bottom -= DEF_TOP_MARGIN;

	seqRects.push_back(seqRect);
	minRects.push_back(minRect);
	maxRects.push_back(maxRect);
	colorRects.push_back(colorRect);
	flagRects.push_back(flagRect);


	for (int idx = 0; idx < ASSEMBLY_NUM-1; ++idx)
	{
		seqRects.push_back(CRect(seqRects[idx].left, seqRects[idx].top + DEF_ROW_GAP, 
			seqRects[idx].right, seqRects[idx].bottom + DEF_ROW_GAP));
		minRects.push_back(CRect(minRects[idx].left, minRects[idx].top + DEF_ROW_GAP,
			minRects[idx].right, minRects[idx].bottom + DEF_ROW_GAP));
		maxRects.push_back(CRect(maxRects[idx].left, maxRects[idx].top + DEF_ROW_GAP,
			maxRects[idx].right, maxRects[idx].bottom + DEF_ROW_GAP));
		colorRects.push_back(CRect(colorRects[idx].left, colorRects[idx].top + DEF_ROW_GAP,
			colorRects[idx].right, colorRects[idx].bottom + DEF_ROW_GAP));
		flagRects.push_back(CRect(flagRects[idx].left, flagRects[idx].top + DEF_ROW_GAP,
			flagRects[idx].right, flagRects[idx].bottom + DEF_ROW_GAP));
	}
		

	for (int idx = 0; idx < ASSEMBLY_NUM; ++idx)
	{
		seqStatics[idx]->MoveWindow(seqRects[idx]);
		minEdits[idx]->MoveWindow(minRects[idx]);
		maxEdits[idx]->MoveWindow(maxRects[idx]);
		colorPics[idx]->MoveWindow(colorRects[idx]);
		flagEdits[idx]->MoveWindow(flagRects[idx]);
		
	}
}


void CPartCapCondDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CapShowType *capShowType = CapShowType::GetInstance();

	CString str;

	minEdit1.GetWindowTextW(str); capShowType->minVal1 = _ttoi(str);
	minEdit2.GetWindowTextW(str); capShowType->minVal2 = _ttoi(str);
	minEdit3.GetWindowTextW(str); capShowType->minVal3 = _ttoi(str);
	minEdit4.GetWindowTextW(str); capShowType->minVal4 = _ttoi(str);
	minEdit5.GetWindowTextW(str); capShowType->minVal5 = _ttoi(str);
	minEdit6.GetWindowTextW(str); capShowType->minVal6 = _ttoi(str);
	minEdit7.GetWindowTextW(str); capShowType->minVal7 = _ttoi(str);
	minEdit8.GetWindowTextW(str); capShowType->minVal8 = _ttoi(str);
	minEdit9.GetWindowTextW(str); capShowType->minVal9 = _ttoi(str);
	minEdit10.GetWindowTextW(str); capShowType->minVal10 = _ttoi(str);
	minEdit11.GetWindowTextW(str); capShowType->minVal11 = _ttoi(str);
	minEdit12.GetWindowTextW(str); capShowType->minVal12 = _ttoi(str);
	minEdit13.GetWindowTextW(str); capShowType->minVal13 = _ttoi(str);
	minEdit14.GetWindowTextW(str); capShowType->minVal14 = _ttoi(str);
	minEdit15.GetWindowTextW(str); capShowType->minVal15 = _ttoi(str);
	minEdit16.GetWindowTextW(str); capShowType->minVal16 = _ttoi(str);

	maxEdit1.GetWindowTextW(str); capShowType->maxVal1 = _ttoi(str);
	maxEdit2.GetWindowTextW(str); capShowType->maxVal2 = _ttoi(str);
	maxEdit3.GetWindowTextW(str); capShowType->maxVal3 = _ttoi(str);
	maxEdit4.GetWindowTextW(str); capShowType->maxVal4 = _ttoi(str);
	maxEdit5.GetWindowTextW(str); capShowType->maxVal5 = _ttoi(str);
	maxEdit6.GetWindowTextW(str); capShowType->maxVal6 = _ttoi(str);
	maxEdit7.GetWindowTextW(str); capShowType->maxVal7 = _ttoi(str);
	maxEdit8.GetWindowTextW(str); capShowType->maxVal8 = _ttoi(str);
	maxEdit9.GetWindowTextW(str); capShowType->maxVal9 = _ttoi(str);
	maxEdit10.GetWindowTextW(str); capShowType->maxVal10 = _ttoi(str);
	maxEdit11.GetWindowTextW(str); capShowType->maxVal11 = _ttoi(str);
	maxEdit12.GetWindowTextW(str); capShowType->maxVal12 = _ttoi(str);
	maxEdit13.GetWindowTextW(str); capShowType->maxVal13 = _ttoi(str);
	maxEdit14.GetWindowTextW(str); capShowType->maxVal14 = _ttoi(str);
	maxEdit15.GetWindowTextW(str); capShowType->maxVal15 = _ttoi(str);
	maxEdit16.GetWindowTextW(str); capShowType->maxVal16 = _ttoi(str);

	flagEdit1.GetWindowTextW(str); capShowType->flagVal1 = str;
	flagEdit2.GetWindowTextW(str); capShowType->flagVal2 = str;
	flagEdit3.GetWindowTextW(str); capShowType->flagVal3 = str;
	flagEdit4.GetWindowTextW(str); capShowType->flagVal4 = str;
	flagEdit5.GetWindowTextW(str); capShowType->flagVal5 = str;
	flagEdit6.GetWindowTextW(str); capShowType->flagVal6 = str;
	flagEdit7.GetWindowTextW(str); capShowType->flagVal7 = str;
	flagEdit8.GetWindowTextW(str); capShowType->flagVal8 = str;
	flagEdit9.GetWindowTextW(str); capShowType->flagVal9 = str;
	flagEdit10.GetWindowTextW(str); capShowType->flagVal10 = str;
	flagEdit11.GetWindowTextW(str); capShowType->flagVal11 = str;
	flagEdit12.GetWindowTextW(str); capShowType->flagVal12 = str;
	flagEdit13.GetWindowTextW(str); capShowType->flagVal13 = str;
	flagEdit14.GetWindowTextW(str); capShowType->flagVal14 = str;
	flagEdit15.GetWindowTextW(str); capShowType->flagVal15 = str;
	flagEdit16.GetWindowTextW(str); capShowType->flagVal16 = str;

	capShowType->colorVal1 = GetRValue(capShowType->colorVals[0]) * 1000000 + GetGValue(capShowType->colorVals[0]) * 1000 + GetBValue(capShowType->colorVals[0]);
	capShowType->colorVal2 = GetRValue(capShowType->colorVals[1]) * 1000000 + GetGValue(capShowType->colorVals[1]) * 1000 + GetBValue(capShowType->colorVals[1]);
	capShowType->colorVal3 = GetRValue(capShowType->colorVals[2]) * 1000000 + GetGValue(capShowType->colorVals[2]) * 1000 + GetBValue(capShowType->colorVals[2]);
	capShowType->colorVal4 = GetRValue(capShowType->colorVals[3]) * 1000000 + GetGValue(capShowType->colorVals[3]) * 1000 + GetBValue(capShowType->colorVals[3]);
	capShowType->colorVal5 = GetRValue(capShowType->colorVals[4]) * 1000000 + GetGValue(capShowType->colorVals[4]) * 1000 + GetBValue(capShowType->colorVals[4]);
	capShowType->colorVal6 = GetRValue(capShowType->colorVals[5]) * 1000000 + GetGValue(capShowType->colorVals[5]) * 1000 + GetBValue(capShowType->colorVals[5]);
	capShowType->colorVal7 = GetRValue(capShowType->colorVals[6]) * 1000000 + GetGValue(capShowType->colorVals[6]) * 1000 + GetBValue(capShowType->colorVals[6]);
	capShowType->colorVal8 = GetRValue(capShowType->colorVals[7]) * 1000000 + GetGValue(capShowType->colorVals[7]) * 1000 + GetBValue(capShowType->colorVals[7]);
	capShowType->colorVal9 = GetRValue(capShowType->colorVals[8]) * 1000000 + GetGValue(capShowType->colorVals[8]) * 1000 + GetBValue(capShowType->colorVals[8]);
	capShowType->colorVal10 = GetRValue(capShowType->colorVals[9]) * 1000000 + GetGValue(capShowType->colorVals[9]) * 1000 + GetBValue(capShowType->colorVals[9]);
	capShowType->colorVal11 = GetRValue(capShowType->colorVals[10]) * 1000000 + GetGValue(capShowType->colorVals[10]) * 1000 + GetBValue(capShowType->colorVals[10]);
	capShowType->colorVal12 = GetRValue(capShowType->colorVals[11]) * 1000000 + GetGValue(capShowType->colorVals[11]) * 1000 + GetBValue(capShowType->colorVals[11]);
	capShowType->colorVal13 = GetRValue(capShowType->colorVals[12]) * 1000000 + GetGValue(capShowType->colorVals[12]) * 1000 + GetBValue(capShowType->colorVals[12]);
	capShowType->colorVal14 = GetRValue(capShowType->colorVals[13]) * 1000000 + GetGValue(capShowType->colorVals[13]) * 1000 + GetBValue(capShowType->colorVals[13]);
	capShowType->colorVal15 = GetRValue(capShowType->colorVals[14]) * 1000000 + GetGValue(capShowType->colorVals[14]) * 1000 + GetBValue(capShowType->colorVals[14]);
	capShowType->colorVal16 = GetRValue(capShowType->colorVals[15]) * 1000000 + GetGValue(capShowType->colorVals[15]) * 1000 + GetBValue(capShowType->colorVals[15]);

	capShowType->validenum = 0;
	for (int idx = 0; idx < ASSEMBLY_NUM; ++idx)
	{
		if (capShowType->flagVals[idx] != L"0")
		{
			capShowType->validenum++;
		}
		else
		{
			break;
		}
	}

	if (MessageBox(_T("确定要保存分容条件显示设置么"), _T("提示"), MB_OKCANCEL | MB_ICONWARNING) == IDOK)
	{
		UpdateSegData();
		capShowType->SavePartCapCond();

		//HWND hWnd = this->GetSafeHwnd();
		CMDIFrameWnd* hMainFrame = (CMDIFrameWnd*)AfxGetMainWnd();
		CMDIChildWnd *hChild = (CMDIChildWnd *)hMainFrame->MDIGetActive();
		CView *hView = (CView *)hChild->GetActiveView();
		if (hView->IsKindOf(RUNTIME_CLASS(CDataFileView)))
		{
			HWND hWnd = hView->m_hWnd;
			// 向父窗口发送消息  
			if (hWnd == NULL) return (void)MessageBox(_T("获得父窗口句柄失败！"));
			CString flag = NULL_FLAG_STR;


			::SendNotifyMessage(hWnd, WM_UPDATE_PART_BAT_MSG, WPARAM(flag.AllocSysString()), NULL);
			
			
			MessageBox(_T("分容条件设置成功!"));
		}
		
	}
	CDialog::OnOK();
}


void CPartCapCondDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	CapShowType *capShowType = CapShowType::GetInstance();

	CString str;

	for (int idx = 0; idx < ASSEMBLY_NUM; ++idx)
	{
		InitColor2(*(colorPics[idx]), capShowType->colorVals[idx]);
	}
	
	for (int idx = 0; idx < capShowType->colorVals.size(); ++idx)
	{
		str.Format(_T("%d"), capShowType->minVals[idx]);
		minEdits[idx]->SetWindowTextW(str);

		str.Format(_T("%d"), capShowType->maxVals[idx]);
		maxEdits[idx]->SetWindowTextW(str);

		flagEdits[idx]->SetWindowTextW(capShowType->flagVals[idx]);

		CRect rect;
		CBrush brush(capShowType->colorVals[idx]);
		//CBrush brush(RGB(255, 0, 0));
		colorPics[idx]->GetClientRect(&rect);   //获取区域
		FillRect(colorPics[idx]->GetDC()->GetSafeHdc(), &rect, brush);
		//colorPic1.GetClientRect(&rect);   //获取区域
		//FillRect(colorPic1.GetDC()->GetSafeHdc(), &rect, brush);

		brush.DeleteObject();
	}
}


void CPartCapCondDlg::OnStnClickedColorPic1()
{
	CapShowType *capShowType = CapShowType::GetInstance();
	COLORREF color = colorArray.GetAt(1);
	SetColor(capShowType, 0, color);
}

void CPartCapCondDlg::SetColor(CapShowType *capShowType,int idx, COLORREF color)
{
	
	CColorDialog colorDlg(color);         // 构造颜色对话框，传入初始颜色值   

	if (IDOK == colorDlg.DoModal())       // 显示颜色对话框，并判断是否点击了“确定”   
	{
		color = colorDlg.GetColor();      // 获取颜色对话框中选择的颜色值  
		CRect prect;
		CBrush selBrush(color);
		colorPics[idx]->GetClientRect(&prect);   //获取区域
		FillRect(colorPics[idx]->GetDC()->GetSafeHdc(),
			CRect(prect.left + 1, prect.top + 1, prect.right - 1, prect.bottom - 1), selBrush);     //填充颜色

		capShowType->colorVals[idx] = color;
		selBrush.DeleteObject();
	}
}

void CPartCapCondDlg::UpdateSegData()
{
	CapShowType *capShowType = CapShowType::GetInstance();
	CString str;
	for (int idx = 0; idx < MAX_FLAG_NUM; ++idx)
	{
		minEdits[idx]->GetWindowText(str);
		capShowType->minVals[idx] = _ttoi(str);

		maxEdits[idx]->GetWindowText(str);
		capShowType->maxVals[idx] = _ttoi(str);

		flagEdits[idx]->GetWindowText(capShowType->flagVals[idx]);
	}
}

void CPartCapCondDlg::OnStnClickedColorPic2()
{
	CapShowType *capShowType = CapShowType::GetInstance();
	COLORREF color = colorArray.GetAt(1);
	SetColor(capShowType, 1, color);
}


void CPartCapCondDlg::OnStnClickedColorPic3()
{
	CapShowType *capShowType = CapShowType::GetInstance();
	COLORREF color = colorArray.GetAt(1);
	SetColor(capShowType, 2, color);
}


void CPartCapCondDlg::OnStnClickedColorPic4()
{
	CapShowType *capShowType = CapShowType::GetInstance();
	COLORREF color = colorArray.GetAt(1);
	SetColor(capShowType, 3, color);
}


void CPartCapCondDlg::OnStnClickedColorPic5()
{
	CapShowType *capShowType = CapShowType::GetInstance();
	COLORREF color = colorArray.GetAt(1);
	SetColor(capShowType, 4, color);
}


void CPartCapCondDlg::OnStnClickedColorPic6()
{
	CapShowType *capShowType = CapShowType::GetInstance();
	COLORREF color = colorArray.GetAt(1);
	SetColor(capShowType, 5, color);
}


void CPartCapCondDlg::OnStnClickedColorPic7()
{
	CapShowType *capShowType = CapShowType::GetInstance();
	COLORREF color = colorArray.GetAt(1);
	SetColor(capShowType, 6, color);
}


void CPartCapCondDlg::OnStnClickedColorPic8()
{
	CapShowType *capShowType = CapShowType::GetInstance();
	COLORREF color = colorArray.GetAt(1);
	SetColor(capShowType, 7, color);
}


void CPartCapCondDlg::OnStnClickedColorPic9()
{
	CapShowType *capShowType = CapShowType::GetInstance();
	COLORREF color = colorArray.GetAt(1);
	SetColor(capShowType, 8, color);
}


void CPartCapCondDlg::OnStnClickedColorPic10()
{
	CapShowType *capShowType = CapShowType::GetInstance();
	COLORREF color = colorArray.GetAt(1);
	SetColor(capShowType, 9, color);
}


void CPartCapCondDlg::OnStnClickedColorPic11()
{
	CapShowType *capShowType = CapShowType::GetInstance();
	COLORREF color = colorArray.GetAt(1);
	SetColor(capShowType, 10, color);
}


void CPartCapCondDlg::OnStnClickedColorPic12()
{
	CapShowType *capShowType = CapShowType::GetInstance();
	COLORREF color = colorArray.GetAt(1);
	SetColor(capShowType, 11, color);
}


void CPartCapCondDlg::OnStnClickedColorPic13()
{
	CapShowType *capShowType = CapShowType::GetInstance();
	COLORREF color = colorArray.GetAt(1);
	SetColor(capShowType, 12, color);
}


void CPartCapCondDlg::OnStnClickedColorPic14()
{
	CapShowType *capShowType = CapShowType::GetInstance();
	COLORREF color = colorArray.GetAt(1);
	SetColor(capShowType, 13, color);
}


void CPartCapCondDlg::OnStnClickedColorPic15()
{
	CapShowType *capShowType = CapShowType::GetInstance();
	COLORREF color = colorArray.GetAt(1);
	SetColor(capShowType, 14, color);
}


void CPartCapCondDlg::OnStnClickedColorPic16()
{
	CapShowType *capShowType = CapShowType::GetInstance();
	COLORREF color = colorArray.GetAt(1);
	SetColor(capShowType, 15, color);
}


BOOL CPartCapCondDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类

	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		CWnd* focus = GetFocus();

		if (focus == GetDlgItem(IDC_MIN_EDIT1) || focus == GetDlgItem(IDC_MIN_EDIT2) || focus == GetDlgItem(IDC_MIN_EDIT3) || focus == GetDlgItem(IDC_MIN_EDIT4)
			|| focus == GetDlgItem(IDC_MIN_EDIT5) || focus == GetDlgItem(IDC_MIN_EDIT6) || focus == GetDlgItem(IDC_MIN_EDIT7) || focus == GetDlgItem(IDC_MIN_EDIT8)
			|| focus == GetDlgItem(IDC_MIN_EDIT9) || focus == GetDlgItem(IDC_MIN_EDIT10) || focus == GetDlgItem(IDC_MIN_EDIT11) || focus == GetDlgItem(IDC_MIN_EDIT12)
			|| focus == GetDlgItem(IDC_MIN_EDIT13) || focus == GetDlgItem(IDC_MIN_EDIT14) || focus == GetDlgItem(IDC_MIN_EDIT15) || focus == GetDlgItem(IDC_MIN_EDIT16)
			|| focus == GetDlgItem(IDC_MAX_EDIT1) || focus == GetDlgItem(IDC_MAX_EDIT2) || focus == GetDlgItem(IDC_MAX_EDIT3) || focus == GetDlgItem(IDC_MAX_EDIT4)
			|| focus == GetDlgItem(IDC_MAX_EDIT5) || focus == GetDlgItem(IDC_MAX_EDIT6) || focus == GetDlgItem(IDC_MAX_EDIT7) || focus == GetDlgItem(IDC_MAX_EDIT8)
			|| focus == GetDlgItem(IDC_MAX_EDIT9) || focus == GetDlgItem(IDC_MAX_EDIT10) || focus == GetDlgItem(IDC_MAX_EDIT11) || focus == GetDlgItem(IDC_MAX_EDIT12)
			|| focus == GetDlgItem(IDC_MAX_EDIT13) || focus == GetDlgItem(IDC_MAX_EDIT14) || focus == GetDlgItem(IDC_MAX_EDIT15) || focus == GetDlgItem(IDC_MAX_EDIT16))
		{
			UpdateRelativeEdits(focus);
		}
		return TRUE;
	}
	else
	{
		return CDialog::PreTranslateMessage(pMsg);
	}
}

void CPartCapCondDlg::UpdateRelativeEditsByDown(CWnd *focus)
{

}

void CPartCapCondDlg::UpdateRelativeEdits(CWnd* focus)
{
	CapShowType *capShowType = CapShowType::GetInstance();
	int idx = 0;
	int editId = 0;
	for (idx = 0; idx < minEdits.size(); ++idx)
	{
		if (focus == minEdits[idx] || focus == maxEdits[idx])
		{
			editId = idx;
			break;
		}
	}
	CString startStr, endStr;
	int startVal, endVal, disVal;

	if (editId >= 0 && editId < 16)
	{
		minEdits[editId]->GetWindowTextW(startStr);
		maxEdits[editId]->GetWindowTextW(endStr);
		startVal = _ttoi(startStr);
		endVal = _ttoi(endStr);
		disVal = endVal - startVal;
		
		for (idx = editId + 1; idx < capShowType->validenum; ++idx)
		{
			startVal = endVal+1;
			endVal += startVal + disVal;
			startStr.Format(_T("%d"), startVal);
			endStr.Format(_T("%d"), endVal);

			minEdits[idx]->SetWindowText(startStr);
			maxEdits[idx]->SetWindowTextW(endStr);
		}
	}
}
