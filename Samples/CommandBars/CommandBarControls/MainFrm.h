// MainFrm.h
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

#if !defined(AFX_MAINFRM_H__0A52D7FB_EC1D_4E45_B2B9_A7AC6F440BC3__INCLUDED_)
#define AFX_MAINFRM_H__0A52D7FB_EC1D_4E45_B2B9_A7AC6F440BC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CXTPMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra,
		AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CXTPStatusBar  m_wndStatusBar;
	CXTPTabClientWnd m_wndClient;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	afx_msg void OnOptionsRighttoleft();
	afx_msg void OnUpdateOptionsRighttoleft(CCmdUI* pCmdUI);

	afx_msg void OnOptionsStyle(UINT nStyle);
	afx_msg void OnUpdateOptionsStyle(CCmdUI* pCmdUI);
	afx_msg void OnOptionsStyleOffice2007(UINT nStyle);
	afx_msg void OnOptionsStyleOffice2010(UINT nStyle);
	afx_msg void OnOptionsStyleOffice2013(UINT nStyle);

	UINT m_nRibbonStyle;
	BOOL m_bCreated;

	void OnCustomize();
	int OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl);
	
	void SetCommandBarsTheme(XTPPaintTheme paintTheme, HMODULE hModule=NULL, LPCTSTR lpszINI=NULL);
	XTPToolTipStyle GetToolTipStyle() const;

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__0A52D7FB_EC1D_4E45_B2B9_A7AC6F440BC3__INCLUDED_)
