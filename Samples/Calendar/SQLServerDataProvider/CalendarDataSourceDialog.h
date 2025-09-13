// CalendarDataSourceDialog.h
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

#if !defined(AFX_CALENDARDATASOURCEDIALOG_H__83F36B4A_5206_4724_A924_C84C79D121BD__INCLUDED_)
#define AFX_CALENDARDATASOURCEDIALOG_H__83F36B4A_5206_4724_A924_C84C79D121BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCalendarDataSourceDialog dialog

class CCalendarDataSourceDialog : public CDialog
{
// Construction
public:
	CCalendarDataSourceDialog(CWnd* pParent = NULL);   // standard constructor

	CString	m_strConnectionString;

// Dialog Data
	//{{AFX_DATA(CCalendarDataSourceDialog)
	enum { IDD = IDD_DATA_SOURCE_DIALOG };
	CEdit	m_ctrlConnectionString;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalendarDataSourceDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCalendarDataSourceDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDARDATASOURCEDIALOG_H__83F36B4A_5206_4724_A924_C84C79D121BD__INCLUDED_)
