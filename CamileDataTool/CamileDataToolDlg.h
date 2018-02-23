
// CamileDataToolDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// CCamileDataToolDlg 对话框
class CCamileDataToolDlg : public CDialogEx
{
// 构造
public:
	CCamileDataToolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAMILEDATATOOL_DLG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_csFilePath;
	CTabCtrl m_CTabShow;
	CListCtrl m_CListCtrl;
	CListCtrl m_CListCtrlLap;
	CChartCtrl m_ChartCtrlSpdDst;
	CChartCtrl m_ChartCtrlAltDst;
	CChartCtrl m_ChartCtrlTempDst;
	CChartCtrl m_ChartCtrlCadDst;
	CChartCtrl m_ChartCtrlHrDst;
	CChartCtrl m_ChartCtrlPwrDst;
	virtual void OnOK();
	afx_msg void OnOpenFile();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRclickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnOpenLink();
	afx_msg void OnShowAboutInfo();
	afx_msg void OnStravaUpload();
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
};
