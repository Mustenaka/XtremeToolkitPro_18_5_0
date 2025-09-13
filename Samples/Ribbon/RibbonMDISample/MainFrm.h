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

#if !defined(AFX_MAINFRM_H__80941DC7_4E2C_448D_9EFB_39D39517AF9C__INCLUDED_)
#define AFX_MAINFRM_H__80941DC7_4E2C_448D_9EFB_39D39517AF9C__INCLUDED_

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
	BOOL CreateRibbonBar();

	void OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState);

	void SetCommandBarsTheme(XTPPaintTheme paintTheme, HMODULE hModule=NULL, LPCTSTR lpszINI=NULL);

	CXTPRibbonBar* pRibbonBar;

	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

	CXTPTabClientWnd m_wndClient;

	void LoadIcons();
	void LoadDefaultIcons();
	void LoadOfficeIcons();
	XTPToolTipStyle GetToolTipStyle() const;
	void CreateBackstage();
	void CreateSystemMenuPopup();

	void ShowCustomizeDialog(int nSelectedPage);
	void OnCustomize();
	void OnCustomizeQuickAccess();

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CXTPStatusBar  m_wndStatusBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewFullscreen();
	afx_msg void OnViewNormal();
	afx_msg void OnUpdateViewNormal(CCmdUI* pCmdUI);
	afx_msg void OnWindowTileV();
	afx_msg void OnWindowCascade();
	afx_msg void OnWindowTileH();
	afx_msg void OnUpdateWindowSwitch(CCmdUI* pCmdUI);
	afx_msg void OnClose();
	//}}AFX_MSG
	void OnViewWorkspace();
	void OnUpdateViewWorkspace(CCmdUI* pCmdUI);
	void OnUpdateRibbonTab(CCmdUI* pCmdUI);

	afx_msg void OnOptionsStyle(UINT nStyle);
	afx_msg void OnUpdateOptionsStyle(CCmdUI* pCmdUI);
	afx_msg void OnOptionsRightToLeft();
	afx_msg void OnUpdateOptionsRighttoleft(CCmdUI* pCmdUI);
	afx_msg void OnOptionsFont(UINT nID);
	afx_msg void OnUpdateOptionsFont(CCmdUI* pCmdUI);
	afx_msg void OnAutoResizeIcons();
	afx_msg void OnUpdateAutoResizeIcons(CCmdUI* pCmdUI);
	afx_msg void OnDpiIconsScalling();
	afx_msg void OnUpdateDpiIconsScalling(CCmdUI* pCmdUI);
	afx_msg void OnFrameTheme();
	afx_msg void OnUpdateFrameTheme(CCmdUI* pCmdUI);
	UINT m_nRibbonStyle;

	BOOL m_bCreated;
	BOOL m_bShowWorkspace;

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__80941DC7_4E2C_448D_9EFB_39D39517AF9C__INCLUDED_)
