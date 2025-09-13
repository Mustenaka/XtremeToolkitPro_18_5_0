// ScrollRichEditView.h
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

#if !defined(AFX_SCROLLRICHEDITVIEW_H__119F8543_B51C_4AE6_8593_75DF43572288__INCLUDED_)
#define AFX_SCROLLRICHEDITVIEW_H__119F8543_B51C_4AE6_8593_75DF43572288__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CScrollRichEditView window

class CScrollRichEditView : public CRichEditView
{
// Construction
public:
	CScrollRichEditView();

// Attributes
public:
	int GetPageSize();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScrollRichEditView)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CScrollRichEditView();

public:
	virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	// Generated message map functions
protected:
	//{{AFX_MSG(CScrollRichEditView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNcPaint();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
	void OnRequestResize(NMHDR * pNotifyStruct, LRESULT* result );
	void OnEditScrollChanged();
	void OnInitialUpdate();

	void UpdateScrollInfo();

	virtual CScrollBar* GetScrollBarCtrl(int nBar) const;

	void SetScrollPos(int nScrollPos);
	void UpdatePosition();

	int m_nTextHeight;
	int m_nPageHeight;
	int m_nScrollPos;
	HINSTANCE m_hInstance;

	int m_nTotalHeight;
	BOOL m_bInScrollChanged;

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCROLLRICHEDITVIEW_H__119F8543_B51C_4AE6_8593_75DF43572288__INCLUDED_)
