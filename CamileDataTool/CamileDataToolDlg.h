
// CamileDataToolDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// CCamileDataToolDlg �Ի���
class CCamileDataToolDlg : public CDialogEx
{
// ����
public:
	CCamileDataToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAMILEDATATOOL_DLG };
#endif

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
