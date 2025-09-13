// ActionsSampleView.h
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

#if !defined(AFX_ACTIONSSAMPLEVIEW_H__FA7DE792_002D_4C8A_BA13_F55F88209C7B__INCLUDED_)
#define AFX_ACTIONSSAMPLEVIEW_H__FA7DE792_002D_4C8A_BA13_F55F88209C7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CActionsSampleCntrItem;

class CActionsSampleView : public CRichEditView
{
protected: // create from serialization only
	CActionsSampleView();
	DECLARE_DYNCREATE(CActionsSampleView)

// Attributes
public:
	CActionsSampleDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CActionsSampleView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CActionsSampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CActionsSampleView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg void OnSelChange(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()

	void OnCharUnderline();
	void OnCharItalic();
	void OnCharBold();

	void UpdateActionsState();

#define DECLARE_APPTHEME(Theme)\
	afx_msg void OnViewTheme##Theme();\
	afx_msg void OnUpdateViewTheme##Theme(CCmdUI* pCmdUI);
	
	DECLARE_APPTHEME(Office2000)
	DECLARE_APPTHEME(OfficeXP)
	DECLARE_APPTHEME(Office2003)
	DECLARE_APPTHEME(WindowsXP)
	DECLARE_APPTHEME(Ribbon)
	DECLARE_APPTHEME(Office2007Aqua)
	DECLARE_APPTHEME(Office2007Black)
	DECLARE_APPTHEME(Office2007Blue)
	DECLARE_APPTHEME(Office2007Silver)
	DECLARE_APPTHEME(Office2007System)
	DECLARE_APPTHEME(Office2010Black)
	DECLARE_APPTHEME(Office2010Blue)
	DECLARE_APPTHEME(Office2010Silver)
	DECLARE_APPTHEME(Office2013Word)
	DECLARE_APPTHEME(Office2013Excel)
	DECLARE_APPTHEME(Office2013Access)
	DECLARE_APPTHEME(Office2013Powerpoint)
	DECLARE_APPTHEME(Office2013OneNote)
	DECLARE_APPTHEME(Office2013Outlook)
	DECLARE_APPTHEME(Windows7)
	DECLARE_APPTHEME(VisualStudio6)
	DECLARE_APPTHEME(VisualStudio8)
	DECLARE_APPTHEME(VisualStudio9)
	DECLARE_APPTHEME(VisualStudio10)
	DECLARE_APPTHEME(VisualStudio2012Light)
	DECLARE_APPTHEME(VisualStudio2012Dark)
	DECLARE_APPTHEME(VisualStudio2015Light)
	DECLARE_APPTHEME(VisualStudio2015Blue)
	DECLARE_APPTHEME(VisualStudio2015Dark)

	void SetTheme(CActionsSampleApp::AppTheme theme, BOOL bRedraw=TRUE);
};

#ifndef _DEBUG  // debug version in ActionsSampleView.cpp
inline CActionsSampleDoc* CActionsSampleView::GetDocument()
   { return (CActionsSampleDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACTIONSSAMPLEVIEW_H__FA7DE792_002D_4C8A_BA13_F55F88209C7B__INCLUDED_)
