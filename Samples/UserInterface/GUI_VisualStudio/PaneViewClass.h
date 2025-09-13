// PaneViewClass.h 
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

#if !defined(AFX_CLASSVIEWPANE_H__59998B87_79B4_4ED1_811C_77DA0EB311DA__INCLUDED_)
#define AFX_CLASSVIEWPANE_H__59998B87_79B4_4ED1_811C_77DA0EB311DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPaneViewClass window

class CPaneViewClass : public CPaneWnd
{
// Construction
public:
	CPaneViewClass();
	virtual ~CPaneViewClass();

	CXTPTreeCtrl m_wndClassView;
	CXTPImageList m_ilClassView;
	CXTPToolBar  m_wndToolBar;

	//{{AFX_VIRTUAL(CPaneViewClass)
	//}}AFX_VIRTUAL

protected:
	virtual void RefreshMetrics(AppTheme nTheme);

	//{{AFX_MSG(CPaneViewClass)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnProjectAddexistingitem();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSetFocus(CWnd* pOldWnd);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLASSVIEWPANE_H__59998B87_79B4_4ED1_811C_77DA0EB311DA__INCLUDED_)
