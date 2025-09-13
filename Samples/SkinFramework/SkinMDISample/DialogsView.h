// DialogsView.h
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

#if !defined(AFX_DIALOGSVIEW_H__9C7CF842_B011_410C_9A05_B05B8CFEE01A__INCLUDED_)
#define AFX_DIALOGSVIEW_H__9C7CF842_B011_410C_9A05_B05B8CFEE01A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDialogsView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CDialogsView : public CFormView
{
protected:
	CDialogsView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDialogsView)

// Form Data
public:
	//{{AFX_DATA(CDialogsView)
	enum { IDD = IDD_PANE_DIALOGS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogsView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDialogsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDialogsView)
	afx_msg void OnButtonColordialog();
	afx_msg void OnButtonFontdialog();
	afx_msg void OnButtonPrintdialog();
	afx_msg void OnButtonOpendialog();
	afx_msg void OnButtonSavedialog();
	afx_msg void OnButtonBrowsedialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGSVIEW_H__9C7CF842_B011_410C_9A05_B05B8CFEE01A__INCLUDED_)
