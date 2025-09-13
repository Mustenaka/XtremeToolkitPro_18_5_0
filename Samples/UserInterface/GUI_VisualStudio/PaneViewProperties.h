// PaneViewProperties.h 
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

#if !defined(AFX_PROPERTIESPANE_H__9A60EAC5_EB5B_4C96_BE70_C9A972B10CDC__INCLUDED_)
#define AFX_PROPERTIESPANE_H__9A60EAC5_EB5B_4C96_BE70_C9A972B10CDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPaneViewProperties window

class CPaneViewProperties : public CPaneWnd
{
public:
	CPaneViewProperties();
	virtual ~CPaneViewProperties();

	CXTPPropertyGrid m_wndPropertyGrid;
	CXTPToolBar      m_wndToolBar;

	//{{AFX_VIRTUAL(CPaneViewProperties)
	//}}AFX_VIRTUAL

protected:
	virtual void RefreshMetrics(AppTheme nTheme);

	//{{AFX_MSG(CPaneViewProperties)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	afx_msg void OnPanePropertiesCategorized();
	afx_msg void OnUpdatePanePropertiesCategorized(CCmdUI* pCmdUI);
	afx_msg void OnPanePropertiesAlphabetic();
	afx_msg void OnUpdatePanePropertiesAlphabetic(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTIESPANE_H__9A60EAC5_EB5B_4C96_BE70_C9A972B10CDC__INCLUDED_)
