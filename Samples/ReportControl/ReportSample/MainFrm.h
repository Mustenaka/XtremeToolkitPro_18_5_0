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

#if !defined(AFX_MAINFRM_H__1889C309_E868_436B_B21D_B8A8DCED019D__INCLUDED_)
#define AFX_MAINFRM_H__1889C309_E868_436B_B21D_B8A8DCED019D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef _XTP_INCLUDE_COMMANDBARS
	#define CMainFrameBase CXTPFrameWnd, CXTPCommandBarsFrameHook
#else
	#define CMainFrameBase CFrameWnd
	#define CXTPStatusBar  CStatusBar

enum XTPPaintTheme
{
	xtpThemeNone                  = -1, // No theme selected.
	xtpThemeOffice2000            =  0, // Office 2000 theme.
	xtpThemeOfficeXP              =  1, // Office XP theme.
	xtpThemeOffice2003            =  2, // Office 2003 theme.
	xtpThemeOffice2007System      = 11, // Office 2007 theme with system colors
	xtpThemeOffice2013            = 12, // Office 2013 theme
	xtpThemeNativeWinXP           =  3, // Windows XP and later native theme support.
	xtpThemeResource              =  5, // Office 2007 theme.
	xtpThemeRibbon                =  6, // Office 2007 style ribbon theme
	xtpThemeVisualStudio6         =  8, // Visual Studio 6 theme
	xtpThemeVisualStudio2005      =  4, // Visual Studio 2005 theme
	xtpThemeVisualStudio2008      =  7, // Visual Studio 2008 theme
	xtpThemeVisualStudio2010      =  9, // Visual Studio 2010 theme
	xtpThemeVisualStudio2015      = 16, // Visual Studio 2015 theme, uses INI file
	xtpThemeCustom                = 10, // Custom theme.
};
#endif

class CFolderView;

class CMainFrame : public CMainFrameBase
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CDialogBar m_wndFieldChooser;   // Sample Field chooser window
	CDialogBar m_wndFilterEdit;     // Sample Filter editing window

// Operations
public:

	void SetTheme(XTPPaintTheme paintTheme, LPCTSTR lpszINI = NULL);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
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
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	afx_msg void OnCustomize();
	DECLARE_MESSAGE_MAP()

#ifdef _XTP_INCLUDE_COMMANDBARS
	BOOL SetFrameIcon(CSize szIcon);
#endif

protected:
#ifdef _XTP_INCLUDE_DOCKINGPANE
	LRESULT OnDockingPaneNotify(WPARAM wParam, LPARAM lParam);
	CXTPDockingPaneManager m_paneManager;
	CFolderView *m_pFolderView;
#endif

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__1889C309_E868_436B_B21D_B8A8DCED019D__INCLUDED_)
