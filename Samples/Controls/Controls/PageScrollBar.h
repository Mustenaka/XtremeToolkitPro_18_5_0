// PageScrollBar.h
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

#if !defined(AFX_PAGESCROLLBAR_H__4999D1BF_9F82_4C81_B6EC_9F9215241CF9__INCLUDED_)
#define AFX_PAGESCROLLBAR_H__4999D1BF_9F82_4C81_B6EC_9F9215241CF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CPageScrollBar dialog

class CPageScrollBar : public CXTPResizePropertyPage
{
	DECLARE_DYNCREATE(CPageScrollBar)

// Construction
public:
	CPageScrollBar();
	~CPageScrollBar();

// Dialog Data
	//{{AFX_DATA(CPageScrollBar)
	enum { IDD = IDD_PAGE_SCROLLBAR };
	CXTPButton	m_btnEnabled;
	CXTPButton	m_gboxOptions;
	BOOL	m_bEnabled;
	//}}AFX_DATA

	CBrush m_brBack;
	COLORREF m_clrBack;

	CXTPScrollBar	m_wndScrollBar[9];
	CXTPScrollBar	m_wndScrollBarHorizontal[9];

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageScrollBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageScrollBar)
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCheckEnabled();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	afx_msg LRESULT OnSetTheme(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGESCROLLBAR_H__4999D1BF_9F82_4C81_B6EC_9F9215241CF9__INCLUDED_)
