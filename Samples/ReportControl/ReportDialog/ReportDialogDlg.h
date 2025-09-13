// ReportDialogDlg.h
//
// (c)1998-2018 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPORTDIALOGDLG_H__6518CEDC_5B8C_44DD_A813_4B4E67DBB931__INCLUDED_)
#define AFX_REPORTDIALOGDLG_H__6518CEDC_5B8C_44DD_A813_4B4E67DBB931__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CReportDialogDlg dialog

#ifndef _XTP_INCLUDE_CONTROLS
#define CXTPResizeDialog CDialog
#endif

class CReportDialogDlg : public CXTPResizeDialog
{
// Construction
public:
	CReportDialogDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CReportDialogDlg();

// Dialog Data
	//{{AFX_DATA(CReportDialogDlg)
	enum { IDD = IDD_REPORTDIALOG_DIALOG };
	CXTPReportControl m_wndReportCtrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportDialogDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CReportDialogDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTDIALOGDLG_H__6518CEDC_5B8C_44DD_A813_4B4E67DBB931__INCLUDED_)
