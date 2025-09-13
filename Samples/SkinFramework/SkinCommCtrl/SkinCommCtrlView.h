// SkinCommCtrlView.h
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

#if !defined(AFX_SKINCOMMCTRLVIEW_H__79799C8B_E6C7_434D_B599_48213FAE35AB__INCLUDED_)
#define AFX_SKINCOMMCTRLVIEW_H__79799C8B_E6C7_434D_B599_48213FAE35AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSkinCommCtrlView : public CEditView
{
protected: // create from serialization only
	CSkinCommCtrlView();
	DECLARE_DYNCREATE(CSkinCommCtrlView)

// Attributes
public:
	CSkinCommCtrlDoc* GetDocument();

public:

	//{{AFX_VIRTUAL(CSkinCommCtrlView)
	public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSkinCommCtrlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	void PrintPoint(LPCTSTR pszText, POINT point);
	void PrintRect(LPCTSTR pszText, RECT rcItem);
	void PrintLine(LPCTSTR pszText);

protected:
	//{{AFX_MSG(CSkinCommCtrlView)
	afx_msg void OnMenuRange(UINT nId) {}
	afx_msg void OnMenuDummy() {}
	afx_msg void OnClearOutput();
	afx_msg void OnGetMenuItemID();
	afx_msg void OnGetMenuItemRect();
	afx_msg void OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnEnterMenuLoop(BOOL bIsTrackPopupMenu);
	afx_msg void OnContextMenu(CWnd *pWnd, CPoint pos);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMenuRButtonUp(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SkinCommCtrlView.cpp
inline CSkinCommCtrlDoc* CSkinCommCtrlView::GetDocument()
   { return (CSkinCommCtrlDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINCOMMCTRLVIEW_H__79799C8B_E6C7_434D_B599_48213FAE35AB__INCLUDED_)
