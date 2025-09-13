// SampleView.h
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

#if !defined(AFX_SAMPLEVIEW_H__8A05B26C_2A39_4658_916B_642343965F16__INCLUDED_)
#define AFX_SAMPLEVIEW_H__8A05B26C_2A39_4658_916B_642343965F16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSampleView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CSampleView : public CFormView
{
protected:
	CSampleView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSampleView)

// Form Data
public:
	//{{AFX_DATA(CSampleView)
	enum { IDD = IDD_VIEW_SAMPLE };
	int		m_nSkin;
	int		m_nTheme;
	CString	m_strFind;
	BOOL	m_bMatchCase;
	BOOL	m_bMatchWord;
	BOOL    m_bFlat;
	BOOL m_bShowGripper;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSampleView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CSampleView)
	afx_msg void OnButtonFind();
	afx_msg void OnButtonColordialog();
	afx_msg void OnButtonFontdialog();
	afx_msg void OnButtonPrintdialog();
	afx_msg void OnButtonOpendialog();
	afx_msg void OnButtonBrowsedialog();
	afx_msg void OnButtonSavedialog();
	afx_msg void OnSkinChanged();
	afx_msg void OnThemeChanged();
	afx_msg void OnChangeEditFind();
	afx_msg void OnCheckGripper();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMPLEVIEW_H__8A05B26C_2A39_4658_916B_642343965F16__INCLUDED_)
