
// CamileDataToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CamileDataTool.h"
#include "CamileDataToolDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCamileDataToolDlg 对话框



CCamileDataToolDlg::CCamileDataToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CAMILEDATATOOL_DLG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCamileDataToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TRACK, m_CListCtrl);
	DDX_Control(pDX, IDC_TAB, m_CTabShow);
	DDX_Control(pDX, IDC_CUSTOM_SPD_DST, m_ChartCtrlSpdDst);
	DDX_Control(pDX, IDC_CUSTOM_ALT_DST, m_ChartCtrlAltDst);
	DDX_Control(pDX, IDC_CUSTOM_TEMP_DST, m_ChartCtrlTempDst);
	DDX_Control(pDX, IDC_CUSTOM_CAD_DST, m_ChartCtrlCadDst);
	DDX_Control(pDX, IDC_CUSTOM_HR_DST, m_ChartCtrlHrDst);
	DDX_Control(pDX, IDC_CUSTOM_PWR_DST, m_ChartCtrlPwrDst);
	DDX_Control(pDX, IDC_LIST_LAP, m_CListCtrlLap);
}

BEGIN_MESSAGE_MAP(CCamileDataToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(IDC_OPEN, &CCamileDataToolDlg::OnOpenFile)
	ON_COMMAND(ID_MENU_GOTO, &CCamileDataToolDlg::OnOpenLink)
	ON_COMMAND(ID_MENU_ABOUT, &CCamileDataToolDlg::OnShowAboutInfo)
	ON_NOTIFY(NM_CLICK, IDC_LIST_TRACK, &CCamileDataToolDlg::OnClickList)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_TRACK, &CCamileDataToolDlg::OnRclickList)
	ON_COMMAND(ID_UPLOADSTRAVA, &CCamileDataToolDlg::OnStravaUpload)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CCamileDataToolDlg::OnTcnSelchangeTab)
END_MESSAGE_MAP()


// CCamileDataToolDlg 消息处理程序

BOOL CCamileDataToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

#if 0
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
#endif
	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	// 窗口最大化
	ShowWindow(SW_SHOWMAXIMIZED);

	// 轨迹信息
	CListCtrl *ListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST_TRACK);
	DWORD dwStyle = GetWindowLong(ListCtrl->m_hWnd, GWL_STYLE);
	DWORD styles = ListCtrl->GetExtendedStyle();
	SetWindowLong(ListCtrl->m_hWnd, GWL_STYLE, dwStyle | LVS_REPORT);
	ListCtrl->SetExtendedStyle(styles | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_CListCtrl.InsertColumn(IDX_TRIP_ID, _T("轨迹ID"), LVCFMT_CENTER, 256);
	m_CListCtrl.InsertColumn(IDX_POINTS, _T("轨迹点数"), LVCFMT_CENTER, 60);
	m_CListCtrl.InsertColumn(IDX_RIDE_DATE, _T("骑行日期"), LVCFMT_CENTER, 130);
	m_CListCtrl.InsertColumn(IDX_SPORT_TIME, _T("运动时间"), LVCFMT_CENTER, 80);
	m_CListCtrl.InsertColumn(IDX_TOTAL_TIME, _T("全程时间"), LVCFMT_CENTER, 80);
	m_CListCtrl.InsertColumn(IDX_DISTANCE, _T("里程(KM)"), LVCFMT_CENTER, 80);
	m_CListCtrl.InsertColumn(IDX_DISTANCE_UP, _T("上坡里程(KM)"), LVCFMT_CENTER, 100);
	m_CListCtrl.InsertColumn(IDX_DISTANCE_DOWN, _T("下坡里程(KM)"), LVCFMT_CENTER, 100);
	m_CListCtrl.InsertColumn(IDX_CALORIE, _T("卡路里(Kcal)"), LVCFMT_CENTER, 80);
	m_CListCtrl.InsertColumn(IDX_MAX_SPEED, _T("最大速度(KM/H)"), LVCFMT_CENTER, 100);
	m_CListCtrl.InsertColumn(IDX_SPORT_AVG_SPEED, _T("骑行均速(KM/H)"), LVCFMT_CENTER, 100);
	m_CListCtrl.InsertColumn(IDX_TOTAL_AVG_SPEED, _T("全程均速(KM/H)"), LVCFMT_CENTER, 100);
	m_CListCtrl.InsertColumn(IDX_MAX_ALTITUDE, _T("最大高度(M)"), LVCFMT_CENTER, 100);
	m_CListCtrl.InsertColumn(IDX_MIN_ALTITUDE, _T("最低高度(M)"), LVCFMT_CENTER, 100);
	m_CListCtrl.InsertColumn(IDX_AVG_ALTITUDE, _T("平均高度(M)"), LVCFMT_CENTER, 100);
	m_CListCtrl.InsertColumn(IDX_ALTITUDE_UP, _T("总升高度(M)"), LVCFMT_CENTER, 100);
	m_CListCtrl.InsertColumn(IDX_ALTITUDE_DOWN, _T("总降高度(M)"), LVCFMT_CENTER, 100);
	m_CListCtrl.InsertColumn(IDX_MAX_GRADE_UP, _T("最大上坡坡度(%)"), LVCFMT_CENTER, 125);
	m_CListCtrl.InsertColumn(IDX_MAX_GRADE_DOWN, _T("最大下坡坡度(%)"), LVCFMT_CENTER, 125);
	m_CListCtrl.InsertColumn(IDX_MAX_TEMPERATURE, _T("最高温度(℃)"), LVCFMT_CENTER, 125);
	m_CListCtrl.InsertColumn(IDX_MIN_TEMPERATURE, _T("最低温度(℃)"), LVCFMT_CENTER, 125);
	m_CListCtrl.InsertColumn(IDX_AVG_TEMPERATURE, _T("平均温度(℃)"), LVCFMT_CENTER, 125);
	m_CListCtrl.InsertColumn(IDX_MAX_CADENCE, _T("最大踏频(RPM)"), LVCFMT_CENTER, 125);
	m_CListCtrl.InsertColumn(IDX_AVG_CADENCE, _T("平均踏频(RPM)"), LVCFMT_CENTER, 125);
	m_CListCtrl.InsertColumn(IDX_MAX_HEARTRATE, _T("最大心率(BPM)"), LVCFMT_CENTER, 125);
	m_CListCtrl.InsertColumn(IDX_AVG_HEARTRATE, _T("平均心率(BPM)"), LVCFMT_CENTER, 125);
	m_CListCtrl.InsertColumn(IDX_MAX_POWER, _T("最大功率(W)"), LVCFMT_CENTER, 125);
	m_CListCtrl.InsertColumn(IDX_AVG_POWER, _T("平均功率(W)"), LVCFMT_CENTER, 125);
	m_CListCtrl.DeleteAllItems();

	// 计圈信息
	ListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST_LAP);
	dwStyle = GetWindowLong(ListCtrl->m_hWnd, GWL_STYLE);
	styles = ListCtrl->GetExtendedStyle();
	SetWindowLong(ListCtrl->m_hWnd, GWL_STYLE, dwStyle | LVS_REPORT);
	ListCtrl->SetExtendedStyle(styles | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_CListCtrlLap.InsertColumn(LAP_ID, _T("计圈"), LVCFMT_CENTER, 60);
	m_CListCtrlLap.InsertColumn(LAP_SPORT_TIME, _T("运动时间"), LVCFMT_CENTER, 125);
	m_CListCtrlLap.InsertColumn(LAP_SPORT_DISTANCE, _T("骑行里程(KM)"), LVCFMT_CENTER, 125);
	m_CListCtrlLap.InsertColumn(LAP_SPORT_AVG_SPEED, _T("运动均速(KM/H)"), LVCFMT_CENTER, 125);
	m_CListCtrlLap.InsertColumn(LAP_MAX_SPEED, _T("最大速度(KM/H)"), LVCFMT_CENTER, 125);
	m_CListCtrlLap.InsertColumn(LAP_MAX_TEMPERATURE, _T("最高温度(℃)"), LVCFMT_CENTER, 125);
	m_CListCtrlLap.InsertColumn(LAP_MIN_TEMPERATURE, _T("最低温度(℃)"), LVCFMT_CENTER, 125);
	m_CListCtrlLap.InsertColumn(LAP_AVG_TEMPERATURE, _T("平均温度(℃)"), LVCFMT_CENTER, 125);
	m_CListCtrlLap.InsertColumn(LAP_MAX_ALTITUDE, _T("最大高度(M)"), LVCFMT_CENTER, 125);
	m_CListCtrlLap.InsertColumn(LAP_MIN_ALTITUDE, _T("最低高度(M)"), LVCFMT_CENTER, 125);
	m_CListCtrlLap.InsertColumn(LAP_AVG_ALTITUDE, _T("平均高度(M)"), LVCFMT_CENTER, 125);
	m_CListCtrlLap.InsertColumn(LAP_ALTITUDE_UP, _T("总升高度(M)"), LVCFMT_CENTER, 125);
	m_CListCtrlLap.InsertColumn(LAP_ALTITUDE_DOWN, _T("总降高度(M)"), LVCFMT_CENTER, 125);
	m_CListCtrlLap.InsertColumn(LAP_MAX_GRADE_UP, _T("最大上坡坡度(%)"), LVCFMT_CENTER, 150);
	m_CListCtrlLap.InsertColumn(LAP_MAX_GRADE_DOWN, _T("最大下坡坡度(%)"), LVCFMT_CENTER, 150);
	m_CListCtrlLap.InsertColumn(LAP_CALORIE, _T("卡路里(Kcal)"), LVCFMT_CENTER, 125);
	m_CListCtrlLap.InsertColumn(LAP_MAX_CADENCE, _T("最大踏频(RPM)"), LVCFMT_CENTER, 125);
	m_CListCtrlLap.InsertColumn(LAP_AVG_CADENCE, _T("平均踏频(RPM)"), LVCFMT_CENTER, 125);
	m_CListCtrlLap.InsertColumn(LAP_MAX_HEARTRATE, _T("最大心率(BPM)"), LVCFMT_CENTER, 125);
	m_CListCtrlLap.InsertColumn(LAP_AVG_HEARTRATE, _T("平均心率(BPM)"), LVCFMT_CENTER, 125);
	m_CListCtrlLap.InsertColumn(LAP_MAX_POWER, _T("最大功率(W)"), LVCFMT_CENTER, 125);
	m_CListCtrlLap.InsertColumn(LAP_AVG_POWER, _T("平均功率(W)"), LVCFMT_CENTER, 125);
	m_CListCtrlLap.DeleteAllItems();
	
	m_CTabShow.InsertItem(0, _T("速度曲线"));
	m_CTabShow.InsertItem(1, _T("高度曲线"));
	m_CTabShow.InsertItem(2, _T("温度曲线"));
	m_CTabShow.InsertItem(3, _T("踏频曲线"));
	m_CTabShow.InsertItem(4, _T("心率曲线"));
	m_CTabShow.InsertItem(5, _T("功率曲线"));
	m_CTabShow.InsertItem(6, _T("计圈信息"));

	CChartAxis *pBottomAxis = NULL, *pLeftAxis = NULL;
	pLeftAxis = m_ChartCtrlSpdDst.CreateStandardAxis(CChartCtrl::LeftAxis);
	pLeftAxis->SetAutomatic(true);
	pLeftAxis->SetDiscrete(false);
	m_ChartCtrlSpdDst.GetLeftAxis()->GetLabel()->SetText(_T("速度(KM/H)"));
	m_ChartCtrlSpdDst.GetLeftAxis()->GetLabel()->SetColor(0xFF0000);
	pBottomAxis = m_ChartCtrlSpdDst.CreateStandardAxis(CChartCtrl::BottomAxis);
	pBottomAxis->SetAutomatic(true);
	pBottomAxis->SetDiscrete(false);
	m_ChartCtrlSpdDst.GetBottomAxis()->GetLabel()->SetText(_T("里程(KM)"));
	m_ChartCtrlSpdDst.GetBottomAxis()->GetLabel()->SetColor(0x000000);
	m_ChartCtrlSpdDst.SetBackGradient(RGB(255, 255, 255), RGB(128, 128, 255), gtVertical);

	pLeftAxis = m_ChartCtrlAltDst.CreateStandardAxis(CChartCtrl::LeftAxis);
	pLeftAxis->SetAutomatic(true);
	pLeftAxis->SetDiscrete(false);
	m_ChartCtrlAltDst.GetLeftAxis()->GetLabel()->SetText(_T("高度(M)"));
	m_ChartCtrlAltDst.GetLeftAxis()->GetLabel()->SetColor(0x00AA00);
	pBottomAxis = m_ChartCtrlAltDst.CreateStandardAxis(CChartCtrl::BottomAxis);
	pBottomAxis->SetAutomatic(true);
	pBottomAxis->SetDiscrete(false);
	m_ChartCtrlAltDst.GetBottomAxis()->GetLabel()->SetText(_T("里程(KM)"));
	m_ChartCtrlAltDst.GetBottomAxis()->GetLabel()->SetColor(0x000000);
	m_ChartCtrlAltDst.SetBackGradient(RGB(255, 255, 255), RGB(128, 255, 128), gtVertical);

	pLeftAxis = m_ChartCtrlTempDst.CreateStandardAxis(CChartCtrl::LeftAxis);
	pLeftAxis->SetAutomatic(true);
	pLeftAxis->SetDiscrete(false);
	m_ChartCtrlTempDst.GetLeftAxis()->GetLabel()->SetText(_T("温度(℃)"));
	m_ChartCtrlTempDst.GetLeftAxis()->GetLabel()->SetColor(0x0000FF);
	pBottomAxis = m_ChartCtrlTempDst.CreateStandardAxis(CChartCtrl::BottomAxis);
	pBottomAxis->SetAutomatic(true);
	pBottomAxis->SetDiscrete(false);
	m_ChartCtrlTempDst.GetBottomAxis()->GetLabel()->SetText(_T("里程(KM)"));
	m_ChartCtrlTempDst.GetBottomAxis()->GetLabel()->SetColor(0x000000);
	m_ChartCtrlTempDst.SetBackGradient(RGB(255, 255, 255), RGB(255, 128, 128), gtVertical);

	pLeftAxis = m_ChartCtrlCadDst.CreateStandardAxis(CChartCtrl::LeftAxis);
	pLeftAxis->SetAutomatic(true);
	pLeftAxis->SetDiscrete(false);
	m_ChartCtrlCadDst.GetLeftAxis()->GetLabel()->SetText(_T("踏频(RPM)"));
	m_ChartCtrlCadDst.GetLeftAxis()->GetLabel()->SetColor(0xFF0000);
	pBottomAxis = m_ChartCtrlCadDst.CreateStandardAxis(CChartCtrl::BottomAxis);
	pBottomAxis->SetAutomatic(true);
	pBottomAxis->SetDiscrete(false);
	m_ChartCtrlCadDst.GetBottomAxis()->GetLabel()->SetText(_T("里程(KM)"));
	m_ChartCtrlCadDst.GetBottomAxis()->GetLabel()->SetColor(0x000000);
	m_ChartCtrlCadDst.SetBackGradient(RGB(255, 255, 255), RGB(128, 128, 255), gtVertical);

	pLeftAxis = m_ChartCtrlHrDst.CreateStandardAxis(CChartCtrl::LeftAxis);
	pLeftAxis->SetAutomatic(true);
	pLeftAxis->SetDiscrete(false);
	m_ChartCtrlHrDst.GetLeftAxis()->GetLabel()->SetText(_T("心率(BPM)"));
	m_ChartCtrlHrDst.GetLeftAxis()->GetLabel()->SetColor(0x00AA00);
	pBottomAxis = m_ChartCtrlHrDst.CreateStandardAxis(CChartCtrl::BottomAxis);
	pBottomAxis->SetAutomatic(true);
	pBottomAxis->SetDiscrete(false);
	m_ChartCtrlHrDst.GetBottomAxis()->GetLabel()->SetText(_T("里程(KM)"));
	m_ChartCtrlHrDst.GetBottomAxis()->GetLabel()->SetColor(0x000000);
	m_ChartCtrlHrDst.SetBackGradient(RGB(255, 255, 255), RGB(128, 255, 128), gtVertical);

	pLeftAxis = m_ChartCtrlPwrDst.CreateStandardAxis(CChartCtrl::LeftAxis);
	pLeftAxis->SetAutomatic(true);
	pLeftAxis->SetDiscrete(false);
	m_ChartCtrlPwrDst.GetLeftAxis()->GetLabel()->SetText(_T("功率(W)"));
	m_ChartCtrlPwrDst.GetLeftAxis()->GetLabel()->SetColor(0x0000FF);
	pBottomAxis = m_ChartCtrlPwrDst.CreateStandardAxis(CChartCtrl::BottomAxis);
	pBottomAxis->SetAutomatic(true);
	pBottomAxis->SetDiscrete(false);
	m_ChartCtrlPwrDst.GetBottomAxis()->GetLabel()->SetText(_T("里程(KM)"));
	m_ChartCtrlPwrDst.GetBottomAxis()->GetLabel()->SetColor(0x000000);
	m_ChartCtrlPwrDst.SetBackGradient(RGB(255, 255, 255), RGB(255, 128, 128), gtVertical);

	m_ChartCtrlSpdDst.ShowWindow(SW_SHOW);
	m_CListCtrlLap.ShowWindow(SW_HIDE);
	m_ChartCtrlAltDst.ShowWindow(SW_HIDE);
	m_ChartCtrlTempDst.ShowWindow(SW_HIDE);
	m_ChartCtrlCadDst.ShowWindow(SW_HIDE);
	m_ChartCtrlHrDst.ShowWindow(SW_HIDE);
	m_ChartCtrlPwrDst.ShowWindow(SW_HIDE);

	UpdateData(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCamileDataToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCamileDataToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCamileDataToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCamileDataToolDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// 对话框内的控件尺寸随对话框自动改变大小
	CWnd* pWnd = GetDlgItem(IDC_LIST_TRACK);
	if (pWnd->GetSafeHwnd())
	{
		pWnd->MoveWindow(0, 0, cx, cy / 2);
	}
	pWnd = GetDlgItem(IDC_TAB);
	if (pWnd->GetSafeHwnd())
	{
		pWnd->MoveWindow(0, cy / 2, cx, cy / 2);
	}
	pWnd = GetDlgItem(IDC_CUSTOM_SPD_DST);
	if (pWnd->GetSafeHwnd())
	{
		pWnd->MoveWindow(0, cy / 2 + 24, cx, cy / 2 - 24);
	}
	pWnd = GetDlgItem(IDC_CUSTOM_ALT_DST);
	if (pWnd->GetSafeHwnd())
	{
		pWnd->MoveWindow(0, cy / 2 + 24, cx, cy / 2 - 24);
	}
	pWnd = GetDlgItem(IDC_CUSTOM_TEMP_DST);
	if (pWnd->GetSafeHwnd())
	{
		pWnd->MoveWindow(0, cy / 2 + 24, cx, cy / 2 - 24);
	}
	pWnd = GetDlgItem(IDC_CUSTOM_CAD_DST);
	if (pWnd->GetSafeHwnd())
	{
		pWnd->MoveWindow(0, cy / 2 + 24, cx, cy / 2 - 24);
	}
	pWnd = GetDlgItem(IDC_CUSTOM_HR_DST);
	if (pWnd->GetSafeHwnd())
	{
		pWnd->MoveWindow(0, cy / 2 + 24, cx, cy / 2 - 24);
	}
	pWnd = GetDlgItem(IDC_CUSTOM_PWR_DST);
	if (pWnd->GetSafeHwnd())
	{
		pWnd->MoveWindow(0, cy / 2 + 24, cx, cy / 2 - 24);
	}
	pWnd = GetDlgItem(IDC_LIST_LAP);
	if (pWnd->GetSafeHwnd())
	{
		pWnd->MoveWindow(0, cy / 2 + 24, cx, cy / 2 - 24);
	}

}

void CCamileDataToolDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// 限制对话款的最小尺寸1280*720
	CPoint pt(1280, 720);
	lpMMI->ptMinTrackSize = pt;
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}

void CCamileDataToolDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	// 屏蔽enter关闭窗口
	//CDialogEx::OnOK();
}

void CCamileDataToolDlg::OnOpenFile()
{
	int rc = 0, i = 0, j = 0, k = 0, pnRow = 0, pnColumn = 0, nIndex = 0;
	int trip_num = 0, alt_ref = 0, alt_up = 0, alt_down = 0;
	int *pAltitude = NULL;
	char sql[256] = { 0 };
	char *err_msg = NULL;
	char **pazResult = NULL;
	sqlite3 *sqlite_cycle_database = NULL;
	st_track_statistics_info *ptrack_statistics_info = NULL;
	CString str;
	
	// 选择数据库文件, 获取路径
	CFileDialog dlg(TRUE, NULL, NULL, NULL, _T("数据库文件(*.db)|*.db||"));
	if (dlg.DoModal() == IDOK)
	{
		m_csFilePath = dlg.GetPathName();
		if (m_csFilePath.IsEmpty())
		{
			return;
		}
	}
	else
	{
		return;
	}
	
	// 打开数据库并将轨迹数据显示在控件上
	CT2CA cFilePath(m_csFilePath);
	rc = sqlite3_open(cFilePath, &sqlite_cycle_database);
	if (rc != SQLITE_OK)
	{
		AfxMessageBox(CString(sqlite3_errmsg(sqlite_cycle_database)), MB_OKCANCEL | MB_ICONWARNING);

		return;
	}

	// SELECT name FROM sqlite_master WHERE type='table' ORDER BY name;

	rc = sqlite3_get_table(sqlite_cycle_database,
		"SELECT trip_id, count(*) FROM TRACK GROUP BY trip_id;",
		&pazResult, &pnRow, &pnColumn, &err_msg);
	if (rc != SQLITE_OK)
	{
		AfxMessageBox(CString(err_msg), MB_OKCANCEL | MB_ICONWARNING);

		if (pazResult)
		{
			sqlite3_free_table(pazResult);
			pazResult = NULL;
		}

		if (err_msg)
		{
			sqlite3_free(err_msg);
			err_msg = NULL;
		}

		sqlite3_close(sqlite_cycle_database);

		return;
	}

	ptrack_statistics_info = (st_track_statistics_info *)malloc(sizeof(st_track_statistics_info) * pnRow);
	if (!ptrack_statistics_info)
	{
		AfxMessageBox(_T("malloc@ptrack_statistics_info fail"), MB_OKCANCEL | MB_ICONWARNING);

		if (pazResult)
		{
			sqlite3_free_table(pazResult);
			pazResult = NULL;
		}

		if (err_msg)
		{
			sqlite3_free(err_msg);
			err_msg = NULL;
		}

		sqlite3_close(sqlite_cycle_database);

		return;
	}

	nIndex = pnColumn;
	for (i = 0; i < pnRow; i++)
	{
		for (j = 0; j < pnColumn; j++)
		{
			switch (j)
			{
				case COL_TRIP_ID:
					if (pazResult[nIndex])
					{
						memcpy(ptrack_statistics_info[i].trip_id, pazResult[nIndex], sizeof(ptrack_statistics_info[i].trip_id));
					}
					else
					{
						memcpy(ptrack_statistics_info[i].trip_id, "NULL", sizeof(ptrack_statistics_info[i].trip_id));
					}
					break;
				case COL_POINTS:
					if (pazResult[nIndex])
					{
						ptrack_statistics_info[i].point_count = atoi(pazResult[nIndex]);
					}
					else
					{
						ptrack_statistics_info[i].point_count = 999999;
					}
					break;
				case COL_RIDE_DATE:
					if (pazResult[nIndex])
					{
						ptrack_statistics_info[i].ride_date = atoi(pazResult[nIndex]);
					}
					else
					{
						ptrack_statistics_info[i].ride_date = 999999;
					}
					break;
				case COL_RIDE_TIME:
					if (pazResult[nIndex])
					{
						ptrack_statistics_info[i].sport_time = atoi(pazResult[nIndex]);
					}
					else
					{
						ptrack_statistics_info[i].sport_time = 999999;
					}
					break;
				case COL_TOTAL_TIME:
					if (pazResult[nIndex])
					{
						ptrack_statistics_info[i].total_time = atoi(pazResult[nIndex]);
					}
					else
					{
						ptrack_statistics_info[i].total_time = 999999;
					}
					break;
				case COL_DISTANCE:
					if (pazResult[nIndex])
					{
						ptrack_statistics_info[i].distance = atof(pazResult[nIndex]) / 100;
					}
					else
					{
						ptrack_statistics_info[i].distance = 999.999;
					}
					break;
				case COL_DISTANCE_UP:
					if (pazResult[nIndex])
					{
						ptrack_statistics_info[i].distance_up = atof(pazResult[nIndex]) / 100;
					}
					else
					{
						ptrack_statistics_info[i].distance_up = 999999;
					}
					break;
				case COL_DISTANCE_DOWN:
					if (pazResult[nIndex])
					{
						ptrack_statistics_info[i].distance_down = atof(pazResult[nIndex]) / 100;
					}
					else
					{
						ptrack_statistics_info[i].distance_down = 999999;
					}
					break;
				case COL_CALORIE:
					if (pazResult[nIndex])
					{
						ptrack_statistics_info[i].calorie = atoi(pazResult[nIndex]);
					}
					else
					{
						ptrack_statistics_info[i].calorie = 999999;
					}
					break;
				case COL_MAX_SPEED:
					if (pazResult[nIndex])
					{
						ptrack_statistics_info[i].max_speed = atof(pazResult[nIndex]) / 10;
					}
					else
					{
						ptrack_statistics_info[i].max_speed = 999.999;
					}
					break;
				case COL_SPORT_AVG_SPEED:
					if (pazResult[nIndex])
					{
						ptrack_statistics_info[i].sport_avg_speed = atof(pazResult[nIndex]);
					}
					else
					{
						ptrack_statistics_info[i].sport_avg_speed = 999.999;
					}
					break;
				case COL_TOTAL_AVG_SPEED:
					if (pazResult[nIndex])
					{
						ptrack_statistics_info[i].total_avg_speed = atof(pazResult[nIndex]);
					}
					else
					{
						ptrack_statistics_info[i].total_avg_speed = 999.999;
					}
					break;
				case COL_MAX_ALTITUDE:
					if (pazResult[nIndex])
					{
						ptrack_statistics_info[i].max_altitude = atoi(pazResult[nIndex]);
					}
					else
					{
						ptrack_statistics_info[i].max_altitude = 999999;
					}
					break;
				case COL_MIN_ALTITUDE:
					if (pazResult[nIndex])
					{
						ptrack_statistics_info[i].min_altitude = atoi(pazResult[nIndex]);
					}
					else
					{
						ptrack_statistics_info[i].min_altitude = 999999;
					}
					break;
				case COL_AVG_ALTITUDE:
					if (pazResult[nIndex])
					{
						ptrack_statistics_info[i].avg_altitude = atoi(pazResult[nIndex]);
					}
					else
					{
						ptrack_statistics_info[i].avg_altitude = 999999;
					}
					break;
				case COL_MAX_GRADE_UP:
					if (pazResult[nIndex])
					{
						ptrack_statistics_info[i].max_grade_up = atoi(pazResult[nIndex]);
					}
					else
					{
						ptrack_statistics_info[i].max_grade_up = 999999;
					}
					break;
				case COL_MAX_GRADE_DOWN:
					if (pazResult[nIndex])
					{
						ptrack_statistics_info[i].max_grade_down = atoi(pazResult[nIndex]);
					}
					else
					{
						ptrack_statistics_info[i].max_grade_down = 999999;
					}
					break;
				case COL_MAX_TEMPERATURE:
					if (pazResult[nIndex])
					{
						ptrack_statistics_info[i].max_temperature = atoi(pazResult[nIndex]);
					}
					else
					{
						ptrack_statistics_info[i].max_temperature = 999999;
					}
					break;
				case COL_MIN_TEMPERATURE:
					if (pazResult[nIndex])
					{
						ptrack_statistics_info[i].min_temperature = atoi(pazResult[nIndex]);
					}
					else
					{
						ptrack_statistics_info[i].min_temperature = 999999;
					}
					break;
				case COL_AVG_TEMPERATURE:
					if (pazResult[nIndex])
					{
						ptrack_statistics_info[i].avg_temperature = atoi(pazResult[nIndex]);
					}
					else
					{
						ptrack_statistics_info[i].avg_temperature = 999999;
					}
					break;
				case COL_MAX_CADENCE:
					if (pazResult[nIndex])
					{
						ptrack_statistics_info[i].max_cadence = atoi(pazResult[nIndex]);
					}
					else
					{
						ptrack_statistics_info[i].max_cadence = 999999;
					}
					break;
				case COL_AVG_CADENCE:
					if (pazResult[nIndex])
					{
						ptrack_statistics_info[i].avg_cadence = atoi(pazResult[nIndex]);
					}
					else
					{
						ptrack_statistics_info[i].avg_cadence = 999999;
					}
					break;
				case COL_MAX_HEARTRATE:
					if (pazResult[nIndex])
					{
						ptrack_statistics_info[i].max_heartrate = atoi(pazResult[nIndex]);
					}
					else
					{
						ptrack_statistics_info[i].max_heartrate = 999999;
					}
					break;
				case COL_AVG_HEARTRATE:
					if (pazResult[nIndex])
					{
						ptrack_statistics_info[i].avg_heartrate = atoi(pazResult[nIndex]);
					}
					else
					{
						ptrack_statistics_info[i].avg_heartrate = 999999;
					}
					break;
				case COL_MAX_POWER:
					if (pazResult[nIndex])
					{
						ptrack_statistics_info[i].max_power = atoi(pazResult[nIndex]);
					}
					else
					{
						ptrack_statistics_info[i].max_power = 999999;
					}
					break;
				case COL_AVG_POWER:
					if (pazResult[nIndex])
					{
						ptrack_statistics_info[i].avg_power = atoi(pazResult[nIndex]);
					}
					else
					{
						ptrack_statistics_info[i].avg_power = 999999;
					}
					break;
				default:
					break;
			}
			++nIndex;
		}
	}

	// 清空LIST控件旧的内容
	m_CListCtrl.DeleteAllItems();
	UpdateData(FALSE);

	for (i = 0; i < pnRow; i++)
	{
		m_CListCtrl.InsertItem(i, CString(ptrack_statistics_info[i].trip_id));
		str.Format(_T("%d"), ptrack_statistics_info[i].point_count);
		m_CListCtrl.SetItemText(i, IDX_POINTS, str);
		str.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),
			GET_YEAR(ptrack_statistics_info[i].ride_date),
			GET_MONTH(ptrack_statistics_info[i].ride_date),
			GET_DAY(ptrack_statistics_info[i].ride_date),
			GET_HOUR(ptrack_statistics_info[i].ride_date),
			GET_MINUTE(ptrack_statistics_info[i].ride_date),
			GET_SECOND(ptrack_statistics_info[i].ride_date));
		m_CListCtrl.SetItemText(i, IDX_RIDE_DATE, str);
		str.Format(_T("%02d:%02d:%02d"),
			ptrack_statistics_info[i].sport_time / 3600,
			(ptrack_statistics_info[i].sport_time - (ptrack_statistics_info[i].sport_time / 3600 * 3600)) / 60,
			(ptrack_statistics_info[i].sport_time - (ptrack_statistics_info[i].sport_time / 3600 * 3600)) % 60);
		m_CListCtrl.SetItemText(i, IDX_SPORT_TIME, str);
		str.Format(_T("%02d:%02d:%02d"),
			ptrack_statistics_info[i].total_time / 3600,
			(ptrack_statistics_info[i].total_time - (ptrack_statistics_info[i].total_time / 3600 * 3600)) / 60,
			(ptrack_statistics_info[i].total_time - (ptrack_statistics_info[i].total_time / 3600 * 3600)) % 60);
		m_CListCtrl.SetItemText(i, IDX_TOTAL_TIME, str);
		str.Format(_T("%0.2f"), ptrack_statistics_info[i].distance);
		m_CListCtrl.SetItemText(i, IDX_DISTANCE, str);
		str.Format(_T("%0.2f"), ptrack_statistics_info[i].distance_up);
		m_CListCtrl.SetItemText(i, IDX_DISTANCE_UP, str);
		str.Format(_T("%0.2f"), ptrack_statistics_info[i].distance_down);
		m_CListCtrl.SetItemText(i, IDX_DISTANCE_DOWN, str);
		str.Format(_T("%d"), ptrack_statistics_info[i].calorie);
		m_CListCtrl.SetItemText(i, IDX_CALORIE, str);
		str.Format(_T("%0.1f"), ptrack_statistics_info[i].max_speed);
		m_CListCtrl.SetItemText(i, IDX_MAX_SPEED, str);
		str.Format(_T("%0.2f"), ptrack_statistics_info[i].sport_avg_speed);
		m_CListCtrl.SetItemText(i, IDX_SPORT_AVG_SPEED, str);
		str.Format(_T("%0.2f"), ptrack_statistics_info[i].total_avg_speed);
		m_CListCtrl.SetItemText(i, IDX_TOTAL_AVG_SPEED, str);
		str.Format(_T("%d"), ptrack_statistics_info[i].max_altitude);
		m_CListCtrl.SetItemText(i, IDX_MAX_ALTITUDE, str);
		str.Format(_T("%d"), ptrack_statistics_info[i].min_altitude);
		m_CListCtrl.SetItemText(i, IDX_MIN_ALTITUDE, str);
		str.Format(_T("%d"), ptrack_statistics_info[i].avg_altitude);
		m_CListCtrl.SetItemText(i, IDX_AVG_ALTITUDE, str);
		str.Format(_T("%d"), ptrack_statistics_info[i].max_grade_up);
		m_CListCtrl.SetItemText(i, IDX_MAX_GRADE_UP, str);
		str.Format(_T("%d"), ptrack_statistics_info[i].max_grade_down);
		m_CListCtrl.SetItemText(i, IDX_MAX_GRADE_DOWN, str);
		str.Format(_T("%d"), ptrack_statistics_info[i].max_temperature);
		m_CListCtrl.SetItemText(i, IDX_MAX_TEMPERATURE, str);
		str.Format(_T("%d"), ptrack_statistics_info[i].min_temperature);
		m_CListCtrl.SetItemText(i, IDX_MIN_TEMPERATURE, str);
		str.Format(_T("%d"), ptrack_statistics_info[i].avg_temperature);
		m_CListCtrl.SetItemText(i, IDX_AVG_TEMPERATURE, str);
		str.Format(_T("%d"), ptrack_statistics_info[i].max_cadence);
		m_CListCtrl.SetItemText(i, IDX_MAX_CADENCE, str);
		str.Format(_T("%d"), ptrack_statistics_info[i].avg_cadence);
		m_CListCtrl.SetItemText(i, IDX_AVG_CADENCE, str);
		str.Format(_T("%d"), ptrack_statistics_info[i].max_heartrate);
		m_CListCtrl.SetItemText(i, IDX_MAX_HEARTRATE, str);
		str.Format(_T("%d"), ptrack_statistics_info[i].avg_heartrate);
		m_CListCtrl.SetItemText(i, IDX_AVG_HEARTRATE, str);
		str.Format(_T("%d"), ptrack_statistics_info[i].max_power);
		m_CListCtrl.SetItemText(i, IDX_MAX_POWER, str);
		str.Format(_T("%d"), ptrack_statistics_info[i].avg_power);
		m_CListCtrl.SetItemText(i, IDX_AVG_POWER, str);
	}

	// 以下计算总升高度和总降高度
	trip_num = pnRow;
	for (k = 0; k < trip_num; k++)
	{
		memset(sql, 0, sizeof(sql));
		sprintf_s(sql, "SELECT altitude FROM %s WHERE tripId=\"%s\";", CYCLE_TRIPS_TABLE, ptrack_statistics_info[k].trip_id);
		rc = sqlite3_get_table(sqlite_cycle_database, sql, &pazResult, &pnRow, &pnColumn, &err_msg);
		if (rc != SQLITE_OK)
		{
			AfxMessageBox((CString(err_msg), MB_OKCANCEL | MB_ICONWARNING));

			if (ptrack_statistics_info)
			{
				free(ptrack_statistics_info);
				ptrack_statistics_info = NULL;
			}

			if (pazResult)
			{
				sqlite3_free_table(pazResult);
				pazResult = NULL;
			}

			if (err_msg)
			{
				sqlite3_free(err_msg);
				err_msg = NULL;
			}

			sqlite3_close(sqlite_cycle_database);

			return;
		}

		pAltitude = (int *)malloc(sizeof(int) * pnRow);
		if (!pAltitude)
		{
			AfxMessageBox(_T("malloc@pAltitude fail"), MB_OKCANCEL | MB_ICONWARNING);

			if (ptrack_statistics_info)
			{
				free(ptrack_statistics_info);
				ptrack_statistics_info = NULL;
			}

			if (pazResult)
			{
				sqlite3_free_table(pazResult);
				pazResult = NULL;
			}

			if (err_msg)
			{
				sqlite3_free(err_msg);
				err_msg = NULL;
			}

			sqlite3_close(sqlite_cycle_database);

			return;
		}

		for (i = 0; i < pnRow; i++)
		{
			pAltitude[i] = atoi(pazResult[i + 1]);
		}

		alt_ref = 0;
		alt_up = 0;
		alt_down = 0;
		for (i = 0; i < pnRow; i++)
		{
			if (i == 0)
			{
				alt_ref = pAltitude[i];
			}
			else
			{
				if (pAltitude[i] >= alt_ref)
				{
					alt_up += (pAltitude[i] - alt_ref);
				}
				else
				{
					alt_down += (pAltitude[i] - alt_ref);
				}

				alt_ref = pAltitude[i];
			}
		}
		str.Format(_T("%d"), alt_up);
		m_CListCtrl.SetItemText(k, IDX_ALTITUDE_UP, str);
		str.Format(_T("%d"), alt_down);
		m_CListCtrl.SetItemText(k, IDX_ALTITUDE_DOWN, str);
	}

	if (ptrack_statistics_info)
	{
		free(ptrack_statistics_info);
		ptrack_statistics_info = NULL;
	}

	if (pAltitude)
	{
		free(pAltitude);
		pAltitude = NULL;
	}

	if (pazResult)
	{
		sqlite3_free_table(pazResult);
		pazResult = NULL;
	}

	if (err_msg)
	{
		sqlite3_free(err_msg);
		err_msg = NULL;
	}

	sqlite3_close(sqlite_cycle_database);

	return;
}

void CCamileDataToolDlg::OnClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int select_row = 0, rc = 0, i = 0, j = 0, k = 0, lap_num = 0, nIndex = 0, pnRow = 0, pnColumn = 0, len = 0;
	int lap_sport_time = 0, lap_trip = 0, pre_lap_max_trip = 0, pre_lap_max_calorie = 0;
	int alt_ref = 0, alt_up = 0, alt_down = 0;
	int *pAlt = NULL, *pUpDownAltInfo = NULL;
	char *err_msg = NULL;
	char **pazResult = NULL;
	char sql[512] = { 0 };
	double *pTrip = NULL;
	double *pSpeed = NULL;
	double *pTemperature = NULL;
	double *pAltitude = NULL;
	double *pCadence = NULL;
	double *pHeartrate = NULL;
	double *pPower = NULL;
	CString csTripId, strText;
	sqlite3 *sqlite_cycle_database = NULL;

	if (m_CListCtrl.GetItemCount() == 0)
	{
		return;
	}

	select_row = m_CListCtrl.GetSelectionMark();
	if (select_row < 0)
	{
		return;
	}

	csTripId = m_CListCtrl.GetItemText(select_row, 0);
	if (csTripId.IsEmpty())
	{
		AfxMessageBox(_T("csTripId empty\n"), MB_OKCANCEL | MB_ICONWARNING);
		return;
	}
	
	if (m_csFilePath.IsEmpty())
	{
		AfxMessageBox(_T("m_csFilePath empty\n"), MB_OKCANCEL | MB_ICONWARNING);
		return;
	}

	CT2CA cFilePath(m_csFilePath);
	rc = sqlite3_open(cFilePath, &sqlite_cycle_database);
	if (rc != SQLITE_OK)
	{
		AfxMessageBox(_T("sqlite3_open fail"), MB_OKCANCEL | MB_ICONWARNING);
		return;
	}

	CT2CA cTripId(csTripId);
	sprintf_s(sql, "SELECT speed, temperature, altitude, cadence, heart_rate, power, trip FROM %s WHERE tripId=\"%s\";", CYCLE_TRIPS_TABLE, cTripId.m_psz);
	rc = sqlite3_get_table(sqlite_cycle_database, sql, &pazResult, &pnRow, &pnColumn, &err_msg);
	if (rc != SQLITE_OK)
	{
		AfxMessageBox(CString(err_msg), MB_OKCANCEL | MB_ICONWARNING);
		
		if (pazResult)
		{
			sqlite3_free_table(pazResult);
			pazResult = NULL;
		}
		
		if (err_msg)
		{
			sqlite3_free(err_msg);
			err_msg = NULL;
		}
		
		sqlite3_close(sqlite_cycle_database);

		return;
	}

	pSpeed = (double *)malloc(sizeof(double) * pnRow);
	pTemperature = (double *)malloc(sizeof(double) * pnRow);
	pAltitude = (double *)malloc(sizeof(double) * pnRow);
	pCadence = (double *)malloc(sizeof(double) * pnRow);
	pHeartrate = (double *)malloc(sizeof(double) * pnRow);
	pPower = (double *)malloc(sizeof(double) * pnRow);
	pTrip = (double *)malloc(sizeof(double) * pnRow);

	nIndex = pnColumn;
	for (i = 0; i < pnRow; i++)
	{
		for (j = 0; j < pnColumn; j++)
		{
			switch (j)
			{
				case 0:
					pSpeed[i] = atof(pazResult[nIndex]) / 10;
					break;
				case 1:
					pTemperature[i] = atof(pazResult[nIndex]);
					break;
				case 2:
					pAltitude[i] = atof(pazResult[nIndex]);
					break;
				case 3:
					pCadence[i] = atof(pazResult[nIndex]);
					break;
				case 4:
					pHeartrate[i] = atof(pazResult[nIndex]);
					break;
				case 5:
					pPower[i] = atof(pazResult[nIndex]);
					break;
				case 6:
					pTrip[i] = atof(pazResult[nIndex]) / 100;
					break;
				default:
					break;
			}
			++nIndex;
		}
	}

	// 显示图表
	CChartLineSerie *pLineSerie = NULL;
	m_ChartCtrlSpdDst.EnableRefresh(false);
	m_ChartCtrlSpdDst.RemoveAllSeries();
	pLineSerie = m_ChartCtrlSpdDst.CreateLineSerie();
	pLineSerie->SetSeriesOrdering(poXOrdering);
	pLineSerie->AddPoints(pTrip, pSpeed, pnRow);
	pLineSerie->SetColor(RGB(0, 0, 255));
	pLineSerie->SetWidth(3);
	pLineSerie->SetName(_T("speed-distance"));
	m_ChartCtrlSpdDst.EnableRefresh(true);

	m_ChartCtrlAltDst.EnableRefresh(false);
	m_ChartCtrlAltDst.RemoveAllSeries();
	pLineSerie = m_ChartCtrlAltDst.CreateLineSerie();
	pLineSerie->SetSeriesOrdering(poXOrdering);
	pLineSerie->AddPoints(pTrip, pAltitude, pnRow);
	pLineSerie->SetColor(RGB(0, 170, 0));
	pLineSerie->SetWidth(3);
	pLineSerie->SetName(_T("altitude-distance"));
	m_ChartCtrlAltDst.EnableRefresh(true);

	m_ChartCtrlTempDst.EnableRefresh(false);
	m_ChartCtrlTempDst.RemoveAllSeries();
	pLineSerie = m_ChartCtrlTempDst.CreateLineSerie();
	pLineSerie->SetSeriesOrdering(poXOrdering);
	pLineSerie->AddPoints(pTrip, pTemperature, pnRow);
	pLineSerie->SetColor(RGB(255, 0, 0));
	pLineSerie->SetWidth(3);
	pLineSerie->SetName(_T("temperature-distance"));
	m_ChartCtrlTempDst.EnableRefresh(true);

	m_ChartCtrlCadDst.EnableRefresh(false);
	m_ChartCtrlCadDst.RemoveAllSeries();
	pLineSerie = m_ChartCtrlCadDst.CreateLineSerie();
	pLineSerie->SetSeriesOrdering(poXOrdering);
	pLineSerie->AddPoints(pTrip, pCadence, pnRow);
	pLineSerie->SetColor(RGB(0, 0, 255));
	pLineSerie->SetWidth(3);
	pLineSerie->SetName(_T("cadence-distance"));
	m_ChartCtrlCadDst.EnableRefresh(true);

	m_ChartCtrlHrDst.EnableRefresh(false);
	m_ChartCtrlHrDst.RemoveAllSeries();
	pLineSerie = m_ChartCtrlHrDst.CreateLineSerie();
	pLineSerie->SetSeriesOrdering(poXOrdering);
	pLineSerie->AddPoints(pTrip, pHeartrate, pnRow);
	pLineSerie->SetColor(RGB(0, 170, 0));
	pLineSerie->SetWidth(3);
	pLineSerie->SetName(_T("heartrate-distance"));
	m_ChartCtrlHrDst.EnableRefresh(true);

	m_ChartCtrlPwrDst.EnableRefresh(false);
	m_ChartCtrlPwrDst.RemoveAllSeries();
	pLineSerie = m_ChartCtrlPwrDst.CreateLineSerie();
	pLineSerie->SetSeriesOrdering(poXOrdering);
	pLineSerie->AddPoints(pTrip, pPower, pnRow);
	pLineSerie->SetColor(RGB(255, 0, 0));
	pLineSerie->SetWidth(3);
	pLineSerie->SetName(_T("power-distance"));
	m_ChartCtrlPwrDst.EnableRefresh(true);

	if (pSpeed)
	{
		free(pSpeed);
		pSpeed = NULL;
	}
	
	if (pTemperature)
	{
		free(pTemperature);
		pTemperature = NULL;
	}
	
	if (pAltitude)
	{
		free(pAltitude);
		pAltitude = NULL;
	}
	
	if (pCadence)
	{
		free(pCadence);
		pCadence = NULL;
	}
	
	if (pHeartrate)
	{
		free(pHeartrate);
		pHeartrate = NULL;
	}
	
	if (pPower)
	{
		free(pPower);
		pPower = NULL;
	}
	
	if (pTrip)
	{
		free(pTrip);
		pTrip = NULL;
	}

	// 先计算单圈总升高度和总降高度
	// 统计有几圈
	memset(sql, 0, sizeof(sql));
	sprintf_s(sql, "SELECT lap_id FROM %s WHERE tripId = \"%s\" GROUP BY lap_id;", CYCLE_TRIPS_TABLE, cTripId.m_psz);
	rc = sqlite3_get_table(sqlite_cycle_database, sql, &pazResult, &pnRow, &pnColumn, &err_msg);
	if (rc != SQLITE_OK)
	{
		AfxMessageBox((CString(err_msg), MB_OKCANCEL | MB_ICONWARNING));
		
		if (pazResult)
		{
			sqlite3_free_table(pazResult);
			pazResult = NULL;
		}
		
		if (err_msg)
		{
			sqlite3_free(err_msg);
			err_msg = NULL;
		}
		
		sqlite3_close(sqlite_cycle_database);

		return;
	}
	// 计算每一圈的总升总降高度
	lap_num = pnRow;
	pUpDownAltInfo = (int *)malloc(sizeof(int) * pnRow * 2);
	if (!pUpDownAltInfo)
	{
		AfxMessageBox(_T("malloc@pUpDownAltInfo fail"), MB_OKCANCEL | MB_ICONWARNING);
		
		if (pazResult)
		{
			sqlite3_free_table(pazResult);
			pazResult = NULL;
		}
		
		if (err_msg)
		{
			sqlite3_free(err_msg);
			err_msg = NULL;
		}
		
		sqlite3_close(sqlite_cycle_database);

		return;
	}

	for (k = 0; k < lap_num; k++)
	{
		memset(sql, 0, sizeof(sql));
		sprintf_s(sql, "SELECT altitude FROM %s WHERE tripId=\"%s\" AND lap_id=%d;", CYCLE_TRIPS_TABLE, cTripId.m_psz, k + 1);
		rc = sqlite3_get_table(sqlite_cycle_database, sql, &pazResult, &pnRow, &pnColumn, &err_msg);
		if (rc != SQLITE_OK)
		{
			AfxMessageBox((CString(err_msg), MB_OKCANCEL | MB_ICONWARNING));
			
			if (pUpDownAltInfo)
			{
				free(pUpDownAltInfo);
				pUpDownAltInfo = NULL;
			}
			
			if (pazResult)
			{
				sqlite3_free_table(pazResult);
				pazResult = NULL;
			}
			
			if (err_msg)
			{
				sqlite3_free(err_msg);
				err_msg = NULL;
			}
			
			sqlite3_close(sqlite_cycle_database);

			return;
		}

		pAlt = (int *)malloc(sizeof(int) * pnRow);
		if (!pAlt)
		{
			AfxMessageBox(_T("malloc@pAlt fail"), MB_OKCANCEL | MB_ICONWARNING);
			
			if (pUpDownAltInfo)
			{
				free(pUpDownAltInfo);
				pUpDownAltInfo = NULL;
			}
			
			if (pazResult)
			{
				sqlite3_free_table(pazResult);
				pazResult = NULL;
			}
			
			if (err_msg)
			{
				sqlite3_free(err_msg);
				err_msg = NULL;
			}
			
			sqlite3_close(sqlite_cycle_database);

			return;
		}

		for (i = 0; i < pnRow; i++)
		{
			pAlt[i] = atoi(pazResult[i + 1]);
		}

		alt_ref = 0;
		alt_up = 0;
		alt_down = 0;
		for (i = 0; i < pnRow; i++)
		{
			if (i == 0)
			{
				alt_ref = pAlt[i];
			}
			else
			{
				if (pAlt[i] >= alt_ref)
				{
					alt_up += (pAlt[i] - alt_ref);
				}
				else
				{
					alt_down += (pAlt[i] - alt_ref);
				}

				alt_ref = pAlt[i];
			}
		}
		pUpDownAltInfo[2 * k] = alt_up;
		pUpDownAltInfo[2 * k + 1] = alt_down;
	}

	// 显示计圈数据
	memset(sql, 0, sizeof(sql));
	sprintf_s(sql, "SELECT lap_id, max(sport_time) - min(sport_time), max(trip), "
		"(((max(trip) - min(trip)) * 36.0) / (max(sport_time) - min(sport_time))), max(speed), "
		"max(temperature), min(temperature), avg(temperature), max(altitude), min(altitude), avg(altitude), "
		"max(grade), min(grade), max(calorie), max(cadence), avg(cadence), "
		"max(heart_rate), avg(heart_rate), max(power), avg(power) FROM %s WHERE tripId=\"%s\" GROUP BY lap_id;", CYCLE_TRIPS_TABLE, cTripId.m_psz);
	rc = sqlite3_get_table(sqlite_cycle_database, sql, &pazResult, &pnRow, &pnColumn, &err_msg);
	if (rc != SQLITE_OK)
	{
		AfxMessageBox(CString(err_msg), MB_OKCANCEL | MB_ICONWARNING);
		
		if (pUpDownAltInfo)
		{
			free(pUpDownAltInfo);
			pUpDownAltInfo = NULL;
		}
		
		if (pAlt)
		{
			free(pAlt);
			pAlt = NULL;
		}
		
		if (pazResult)
		{
			sqlite3_free_table(pazResult);
			pazResult = NULL;
		}
		
		if (err_msg)
		{
			sqlite3_free(err_msg);
			err_msg = NULL;
		}
		
		sqlite3_close(sqlite_cycle_database);

		return;
	}

	m_CListCtrlLap.DeleteAllItems();
	UpdateData(FALSE);

	nIndex = pnColumn;
	for (i = 0; i < pnRow; i++)
	{
		for (j = 0; j < pnColumn; j++)
		{
			switch (j)
			{
				case 0:
					strText.Format(_T("%d"), atoi(pazResult[nIndex]));
					m_CListCtrlLap.InsertItem(i, strText);
					break;
				case 1:
					if (i == 0)
					{
						strText.Format(_T("%02d:%02d:%02d"),
							atoi(pazResult[nIndex]) / 3600,
							(atoi(pazResult[nIndex]) - (atoi(pazResult[nIndex]) / 3600 * 3600)) / 60,
							(atoi(pazResult[nIndex]) - (atoi(pazResult[nIndex]) / 3600 * 3600)) % 60);
						lap_sport_time = atoi(pazResult[nIndex]);
					}
					else
					{
						strText.Format(_T("%02d:%02d:%02d"),
							(atoi(pazResult[nIndex]) + 1) / 3600,
							((atoi(pazResult[nIndex]) + 1) - ((atoi(pazResult[nIndex]) + 1) / 3600 * 3600)) / 60,
							((atoi(pazResult[nIndex]) + 1) - ((atoi(pazResult[nIndex]) + 1) / 3600 * 3600)) % 60);
						lap_sport_time = atoi(pazResult[nIndex]) + 1;
					}
					m_CListCtrlLap.SetItemText(i, LAP_SPORT_TIME, strText);
					break;
				case 2:
					if (i == 0)
					{
						strText.Format(_T("%0.2f"), atof(pazResult[nIndex]) / 100);
						lap_trip = atoi(pazResult[nIndex]);
						pre_lap_max_trip = atoi(pazResult[nIndex]);
					}
					else
					{
						strText.Format(_T("%0.2f"), (double)(atoi(pazResult[nIndex]) - pre_lap_max_trip) / 100);
						lap_trip = atoi(pazResult[nIndex]) - pre_lap_max_trip;
						pre_lap_max_trip = atoi(pazResult[nIndex]);
					}
					m_CListCtrlLap.SetItemText(i, LAP_SPORT_DISTANCE, strText);
					break;
				case 3:
					strText.Format(_T("%0.2f"), (lap_trip * 36.0 / lap_sport_time));
					m_CListCtrlLap.SetItemText(i, LAP_SPORT_AVG_SPEED, strText);
					break;
				case 4:
					strText.Format(_T("%0.2f"), atof(pazResult[nIndex]) / 10);
					m_CListCtrlLap.SetItemText(i, LAP_MAX_SPEED, strText);
					break;
				case 5:
					strText.Format(_T("%d"), atoi(pazResult[nIndex]));
					m_CListCtrlLap.SetItemText(i, LAP_MAX_TEMPERATURE, strText);
					break;
				case 6:
					strText.Format(_T("%d"), atoi(pazResult[nIndex]));
					m_CListCtrlLap.SetItemText(i, LAP_MIN_TEMPERATURE, strText);
					break;
				case 7:
					strText.Format(_T("%d"), atoi(pazResult[nIndex]));
					m_CListCtrlLap.SetItemText(i, LAP_AVG_TEMPERATURE, strText);
					break;
				case 8:
					strText.Format(_T("%d"), atoi(pazResult[nIndex]));
					m_CListCtrlLap.SetItemText(i, LAP_MAX_ALTITUDE, strText);
					break;
				case 9:
					strText.Format(_T("%d"), atoi(pazResult[nIndex]));
					m_CListCtrlLap.SetItemText(i, LAP_MIN_ALTITUDE, strText);
					break;
				case 10:
					strText.Format(_T("%d"), atoi(pazResult[nIndex]));
					m_CListCtrlLap.SetItemText(i, LAP_AVG_ALTITUDE, strText);
					strText.Format(_T("%d"), pUpDownAltInfo[2 * i]);
					m_CListCtrlLap.SetItemText(i, LAP_ALTITUDE_UP, strText);
					strText.Format(_T("%d"), pUpDownAltInfo[2 * i + 1]);
					m_CListCtrlLap.SetItemText(i, LAP_ALTITUDE_DOWN, strText);
					break;
				case 11:
					strText.Format(_T("%d"), atoi(pazResult[nIndex]));
					m_CListCtrlLap.SetItemText(i, LAP_MAX_GRADE_UP, strText);
					break;
				case 12:
					strText.Format(_T("%d"), atoi(pazResult[nIndex]));
					m_CListCtrlLap.SetItemText(i, LAP_MAX_GRADE_DOWN, strText);
					break;
				case 13:
					if (i == 0)
					{
						strText.Format(_T("%d"), atoi(pazResult[nIndex]));
						pre_lap_max_calorie = atoi(pazResult[nIndex]);
					}
					else
					{
						strText.Format(_T("%d"), atoi(pazResult[nIndex]) - pre_lap_max_calorie);
						pre_lap_max_calorie = atoi(pazResult[nIndex]);
					}
					m_CListCtrlLap.SetItemText(i, LAP_CALORIE, strText);
					break;
				case 14:
					strText.Format(_T("%d"), atoi(pazResult[nIndex]));
					m_CListCtrlLap.SetItemText(i, LAP_MAX_CADENCE, strText);
					break;
				case 15:
					strText.Format(_T("%d"), atoi(pazResult[nIndex]));
					m_CListCtrlLap.SetItemText(i, LAP_AVG_CADENCE, strText);
					break;
				case 16:
					strText.Format(_T("%d"), atoi(pazResult[nIndex]));
					m_CListCtrlLap.SetItemText(i, LAP_MAX_HEARTRATE, strText);
					break;
				case 17:
					strText.Format(_T("%d"), atoi(pazResult[nIndex]));
					m_CListCtrlLap.SetItemText(i, LAP_AVG_HEARTRATE, strText);
					break;
				case 18:
					strText.Format(_T("%d"), atoi(pazResult[nIndex]));
					m_CListCtrlLap.SetItemText(i, LAP_MAX_POWER, strText);
					break;
				case 19:
					strText.Format(_T("%d"), atoi(pazResult[nIndex]));
					m_CListCtrlLap.SetItemText(i, LAP_AVG_POWER, strText);
					break;
				default:
					break;
			}
			++nIndex;
		}
	}
	UpdateData(FALSE);

	if (pUpDownAltInfo)
	{
		free(pUpDownAltInfo);
		pUpDownAltInfo = NULL;
	}

	if (pAlt)
	{
		free(pAlt);
		pAlt = NULL;
	}

	if (pazResult)
	{
		sqlite3_free_table(pazResult);
		pazResult = NULL;
	}
	
	if (err_msg)
	{
		sqlite3_free(err_msg);
		err_msg = NULL;
	}
	
	sqlite3_close(sqlite_cycle_database);

	*pResult = 0;

	return;
}


void CCamileDataToolDlg::OnOpenLink()
{
	ShellExecute(NULL, _T("open"), _T("http://www.miniwing.com/index.php/camile"), NULL, NULL, SW_SHOWNORMAL);

	return;
}


void CCamileDataToolDlg::OnStravaUpload()
{
	ShellExecute(NULL, _T("open"), _T("https://www.strava.com/upload/select"), NULL, NULL, SW_SHOWNORMAL);

	return;
}


void CCamileDataToolDlg::OnShowAboutInfo()
{
	CAboutDlg dlg;
	dlg.DoModal();

	return;
}


void CCamileDataToolDlg::OnRclickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// 生成GPX文件
	int rc = 0, i = 0, j = 0, select_row = 0, nIndex = 0, pnRow = 0, pnColumn = 0;
	int year = 0, month = 0, day = 0, hour = 0, min = 0, sec = 0;
	int point_count = 0;
	char gpxFileName[256] = { 0 };
	char text[256] = { 0 };
	char sql[256] = { 0 };
	char *err_msg = NULL;
	char **pazResult = NULL;
	UINT len = 0;
	CString str, csTripId;
	sqlite3 *sqlite_cycle_database = NULL;
	st_track_line_info *ptrack_line_info = NULL;

	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	if (pNMLV->iItem == -1)
	{
		return;
	}

	HMENU hMenu = ::CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING, 10001, _T("生成GPX文件"));
	CPoint pt;
	GetCursorPos(&pt);
	UINT Cmd = (UINT)::TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_RETURNCMD, pt.x, pt.y, 0, m_hWnd, NULL);
	switch (Cmd)
	{
		case 10001:
		{
			CT2CA cFilePath(m_csFilePath);
			rc = sqlite3_open(cFilePath, &sqlite_cycle_database);
			if (rc != SQLITE_OK)
			{
				AfxMessageBox(_T("sqlite3_open fail"), MB_OKCANCEL | MB_ICONWARNING);
				return;
			}

			memset(sql, 0, sizeof(sql));
			select_row = m_CListCtrl.GetSelectionMark();
			csTripId = m_CListCtrl.GetItemText(select_row, 0);
			CT2CA cTripId(csTripId);
			sprintf_s(sql, "SELECT time_stamp, longitude, longitude_EW, latitude, latitude_NS, altitude FROM %s WHERE trip_id=\"%s\";", CYCLE_TRIPS_TABLE, cTripId.m_psz);
			rc = sqlite3_get_table(sqlite_cycle_database, sql, &pazResult, &pnRow, &pnColumn, &err_msg);
			if (rc != SQLITE_OK)
			{
				AfxMessageBox(CString(err_msg), MB_OKCANCEL | MB_ICONWARNING);
	
				if (pazResult)
				{
					sqlite3_free_table(pazResult);
					pazResult = NULL;
				}
				
				if (err_msg)
				{
					sqlite3_free(err_msg);
					err_msg = NULL;
				}
				
				sqlite3_close(sqlite_cycle_database);

				return;
			}

			ptrack_line_info = (st_track_line_info *)malloc(sizeof(st_track_line_info) * pnRow);
			if (!ptrack_line_info)
			{
				AfxMessageBox(_T("malloc@ptrack_line_info fail"), MB_OKCANCEL | MB_ICONWARNING);

				if (pazResult)
				{
					sqlite3_free_table(pazResult);
					pazResult = NULL;
				}
				
				if (err_msg)
				{
					sqlite3_free(err_msg);
					err_msg = NULL;
				}
				
				sqlite3_close(sqlite_cycle_database);

				return;
			}

			nIndex = pnColumn;
			for (i = 0; i < pnRow; i++)
			{
				for (j = 0; j < pnColumn; j++)
				{
					switch (j)
					{
						case 0:
							ptrack_line_info[i].time_stamp = atoi(pazResult[nIndex]);
							break;
						case 1:
							ptrack_line_info[i].longitude = atof(pazResult[nIndex]);
							break;
						case 2:
							ptrack_line_info[i].longitude_EW = atoi(pazResult[nIndex]);
							break;
						case 3:
							ptrack_line_info[i].latitude = atof(pazResult[nIndex]);
							break;
						case 4:
							ptrack_line_info[i].latitude_NS = atoi(pazResult[nIndex]);
							break;
						case 5:
							ptrack_line_info[i].altitude = atoi(pazResult[nIndex]);
							break;
						default:
							break;
					}
					++nIndex;
				}
			}
	
			year = (int)GET_YEAR(ptrack_line_info[0].time_stamp);
			month = (int)GET_MONTH(ptrack_line_info[0].time_stamp);
			day = (int)GET_DAY(ptrack_line_info[0].time_stamp);
			hour = (int)GET_HOUR(ptrack_line_info[0].time_stamp);
			min = (int)GET_MINUTE(ptrack_line_info[0].time_stamp);
			sec = (int)GET_SECOND(ptrack_line_info[0].time_stamp);

			if (!PathIsDirectory(_T(".\\GPX")))
			{
				CreateDirectory(_T(".\\GPX"), NULL);
			}

			memset(gpxFileName, 0, sizeof(gpxFileName));
			str.Format(_T(".\\GPX\\%04d%02d%02d%02d%02d%02d.GPX"), year, month, day, hour, min, sec);
			CFile gpxFile(str, CFile::modeCreate | CFile::modeWrite);
			memset(text, 0, sizeof(text));
			snprintf(text, sizeof(text), "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n");
			len = (UINT)strlen(text);
			gpxFile.Write(text, len);
			memset(text, 0, sizeof(text));
			snprintf(text, sizeof(text), "<gpx version=\"1.1\" creator=\"Camile C30\" xmlns=\"http://www.topografix.com/GPX/1/1\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://www.topografix.com/GPX/1/1 http://www.topografix.com/GPX/1/1/gpx.xsd\">\n");
			len = (UINT)strlen(text);
			gpxFile.Write(text, len);
			memset(text, 0, sizeof(text));
			snprintf(text,
				sizeof(text),
				"<metadata>\n"
				"<link href=\"http://www.miniwing.com\">\n"
				"<text>HangZhou MiniWing Technology Co.Ltd</text>\n"
				"</link>\n"
				"<time>%04lu-%02lu-%02luT%02lu:%02lu:%02luZ</time>\n"
				"</metadata>\n",
				year, month, day, hour, min, sec);
			len = (UINT)strlen(text);
			gpxFile.Write(text, len);
			memset(text, 0, sizeof(text));
			snprintf(text,
				sizeof(text),
				"<trk>\n"
				"<name>Camile R20 Track v1.0</name>\n"
				"<trkseg>\n");
			len = (UINT)strlen(text);
			gpxFile.Write(text, len);

			point_count = _ttoi(m_CListCtrl.GetItemText(select_row, 1));
			for (i = 0; i < point_count; i++)
			{
				year = (int)GET_YEAR(ptrack_line_info[i].time_stamp);
				month = (int)GET_MONTH(ptrack_line_info[i].time_stamp);
				day = (int)GET_DAY(ptrack_line_info[i].time_stamp);
				hour = (int)GET_HOUR(ptrack_line_info[i].time_stamp);
				min = (int)GET_MINUTE(ptrack_line_info[i].time_stamp);
				sec = (int)GET_SECOND(ptrack_line_info[i].time_stamp);

				memset(text, 0, sizeof(text));
				snprintf(text,
					sizeof(text),
					"<trkpt lat=\"%0.6f\" lon=\"%0.6f\">\n"
					"<ele>%d</ele>\n"
					"<time>%04lu-%02lu-%02luT%02lu:%02lu:%02luZ</time>\n"
					"</trkpt>\n",
					(ptrack_line_info[i].latitude_NS == 1 ? 1 : (-1)) * ptrack_line_info[i].latitude,
					(ptrack_line_info[i].longitude_EW == 1 ? 1 : (-1)) * ptrack_line_info[i].longitude,
					ptrack_line_info[i].altitude,
					year, month, day, hour, min, sec);
				len = (UINT)strlen(text);
				gpxFile.Write(text, len);
			}
			memset(text, 0, sizeof(text));
			snprintf(text,
				sizeof(text),
				"</trkseg>\n"
				"</trk>\n"
				"</gpx>\n");
			len = (UINT)strlen(text);
			gpxFile.Write(text, len);
			gpxFile.Close();
			AfxMessageBox(str, MB_OKCANCEL | MB_ICONWARNING);

			break;
		}
	}

	if (ptrack_line_info)
	{
		free(ptrack_line_info);
		ptrack_line_info = NULL;
	}

	if (pazResult)
	{
		sqlite3_free_table(pazResult);
		pazResult = NULL;
	}

	if (err_msg)
	{
		sqlite3_free(err_msg);
		err_msg = NULL;
	}

	sqlite3_close(sqlite_cycle_database);

	*pResult = 0;
}


void CCamileDataToolDlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	switch (m_CTabShow.GetCurSel())
	{
		case 0:
		{
			m_ChartCtrlSpdDst.ShowWindow(SW_SHOW);
			m_ChartCtrlAltDst.ShowWindow(SW_HIDE);
			m_ChartCtrlTempDst.ShowWindow(SW_HIDE);
			m_ChartCtrlCadDst.ShowWindow(SW_HIDE);
			m_ChartCtrlHrDst.ShowWindow(SW_HIDE);
			m_ChartCtrlPwrDst.ShowWindow(SW_HIDE);
			m_CListCtrlLap.ShowWindow(SW_HIDE);
			break;
		}
		case 1:
		{
			m_ChartCtrlSpdDst.ShowWindow(SW_HIDE);
			m_ChartCtrlAltDst.ShowWindow(SW_SHOW);
			m_ChartCtrlTempDst.ShowWindow(SW_HIDE);
			m_ChartCtrlCadDst.ShowWindow(SW_HIDE);
			m_ChartCtrlHrDst.ShowWindow(SW_HIDE);
			m_ChartCtrlPwrDst.ShowWindow(SW_HIDE);
			m_CListCtrlLap.ShowWindow(SW_HIDE);
			break;
		}
		case 2:
		{
			m_ChartCtrlSpdDst.ShowWindow(SW_HIDE);
			m_ChartCtrlAltDst.ShowWindow(SW_HIDE);
			m_ChartCtrlTempDst.ShowWindow(SW_SHOW);
			m_ChartCtrlCadDst.ShowWindow(SW_HIDE);
			m_ChartCtrlHrDst.ShowWindow(SW_HIDE);
			m_ChartCtrlPwrDst.ShowWindow(SW_HIDE);
			m_CListCtrlLap.ShowWindow(SW_HIDE);
			break;
		}
		case 3:
		{
			m_ChartCtrlSpdDst.ShowWindow(SW_HIDE);
			m_ChartCtrlAltDst.ShowWindow(SW_HIDE);
			m_ChartCtrlTempDst.ShowWindow(SW_HIDE);
			m_ChartCtrlCadDst.ShowWindow(SW_SHOW);
			m_ChartCtrlHrDst.ShowWindow(SW_HIDE);
			m_ChartCtrlPwrDst.ShowWindow(SW_HIDE);
			m_CListCtrlLap.ShowWindow(SW_HIDE);
			break;
		}
		case 4:
		{
			m_ChartCtrlSpdDst.ShowWindow(SW_HIDE);
			m_ChartCtrlAltDst.ShowWindow(SW_HIDE);
			m_ChartCtrlTempDst.ShowWindow(SW_HIDE);
			m_ChartCtrlCadDst.ShowWindow(SW_HIDE);
			m_ChartCtrlHrDst.ShowWindow(SW_SHOW);
			m_ChartCtrlPwrDst.ShowWindow(SW_HIDE);
			m_CListCtrlLap.ShowWindow(SW_HIDE);
			break;
		}
		case 5:
		{
			m_ChartCtrlSpdDst.ShowWindow(SW_HIDE);
			m_ChartCtrlAltDst.ShowWindow(SW_HIDE);
			m_ChartCtrlTempDst.ShowWindow(SW_HIDE);
			m_ChartCtrlCadDst.ShowWindow(SW_HIDE);
			m_ChartCtrlHrDst.ShowWindow(SW_HIDE);
			m_ChartCtrlPwrDst.ShowWindow(SW_SHOW);
			m_CListCtrlLap.ShowWindow(SW_HIDE);
			break;
		}
		case 6:
		{
			m_ChartCtrlSpdDst.ShowWindow(SW_HIDE);
			m_ChartCtrlAltDst.ShowWindow(SW_HIDE);
			m_ChartCtrlTempDst.ShowWindow(SW_HIDE);
			m_ChartCtrlCadDst.ShowWindow(SW_HIDE);
			m_ChartCtrlHrDst.ShowWindow(SW_HIDE);
			m_ChartCtrlPwrDst.ShowWindow(SW_HIDE);
			m_CListCtrlLap.ShowWindow(SW_SHOW);
			break;
		}
		default:
			break;
	}
	*pResult = 0;
}
