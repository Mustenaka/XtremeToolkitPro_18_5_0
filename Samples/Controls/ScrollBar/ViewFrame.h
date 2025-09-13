// ViewFrame.h 
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

#if !defined(AFX_VIEWDLG_H__693E9CEE_BC86_4FBA_A6CC_A5B3BE7BBFF8__INCLUDED_)
#define AFX_VIEWDLG_H__693E9CEE_BC86_4FBA_A6CC_A5B3BE7BBFF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CViewFrame dialog

class CViewFrame : public CFrameWnd
{
public:
	CViewFrame();

	void SetScrollBarTheme(XTPScrollBarTheme theme);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewFrame)
protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
private:
	BOOL CreateSplitter();
	CXTPSplitterWnd m_wndSplitter;
	BOOL m_bFirstShow;

protected:
	// Generated message map functions
	//{{AFX_MSG(CViewFrame)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWDLG_H__693E9CEE_BC86_4FBA_A6CC_A5B3BE7BBFF8__INCLUDED_)
