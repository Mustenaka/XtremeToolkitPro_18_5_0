// ShellTreeView.h
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

#if !defined(AFX_SHELLTREEVIEW_H__48775716_74D4_4EBE_8212_0C33AA271BB0__INCLUDED_)
#define AFX_SHELLTREEVIEW_H__48775716_74D4_4EBE_8212_0C33AA271BB0__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// CShellTreeView view

class CShellTreeView : public CXTPShellTreeView
{
protected:
	CShellTreeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CShellTreeView)

// Attributes
public:

// Operations
public:
	void SelectParentItem();
	void SetListView(CXTPShellListView* pView);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShellTreeView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CShellTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	void CShellTreeView::OnInitialUpdate();

	// Generated message map functions
protected:
	int GetHeaderHeight() const;
	
	//{{AFX_MSG(CShellTreeView)
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg void OnNcPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CXTPShellListView* m_pListView;

};

AFX_INLINE void CShellTreeView::SetListView(CXTPShellListView* pView) {
	m_pListView = pView;
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHELLTREEVIEW_H__48775716_74D4_4EBE_8212_0C33AA271BB0__INCLUDED_)
