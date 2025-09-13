// RangeBarView.h
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

#if !defined(AFX_RangeBarView_H__F31A2B31_B7F8_49D2_B748_57B38AF51C5F__INCLUDED_)
#define AFX_RangeBarView_H__F31A2B31_B7F8_49D2_B748_57B38AF51C5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CRangeBarView form view

#include "BaseView.h"

class CRangeBarView : public CBaseView
{
public:
	CRangeBarView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRangeBarView)

// Form Data
public:
	//{{AFX_DATA(CRangeBarView)
	enum { IDD = IDD_VIEW_RANGEBAR };
	//CXTPComboBox	m_cboPosition;
	//CXTPButton	m_chkShowLabels;
	BOOL	m_bShowLabels;
	BOOL	m_bRotated;
	BOOL    m_bSideBySide;
	//}}AFX_DATA

	void CreateChart();

// Attributes
public:
	

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRangeBarView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRangeBarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	void OnCheckSideBySide();

	// Generated message map functions
	//{{AFX_MSG(CRangeBarView)
	afx_msg void OnCheckShowLabels();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheckRotated();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RangeBarView_H__F31A2B31_B7F8_49D2_B748_57B38AF51C5F__INCLUDED_)
