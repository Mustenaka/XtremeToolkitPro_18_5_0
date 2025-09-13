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

#if !defined(AFX_STDAFX_H__B1F4ABBF_7DA1_43C1_A82B_5EB4405A5135__INCLUDED_)
#define AFX_STDAFX_H__B1F4ABBF_7DA1_43C1_A82B_5EB4405A5135__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _XTP_INCLUDE_COMMANDBARS

#define CXTPEdit       CEdit
#define CMainFrameBase CMDIFrameWnd
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
    xtpThemeVisualStudio2012      = 13, // Visual Studio 2012 theme, uses INI file
    xtpThemeVisualStudio2012Light = 14, // Visual Studio 2012 light theme
    xtpThemeVisualStudio2012Dark  = 15, // Visual Studio 2012 dark theme
    xtpThemeVisualStudio2015      = 16, // Visual Studio 2015 theme, uses INI file
    xtpThemeCustom                = 10, // Custom theme.
};

#else

#define CMainFrameBase CXTPMDIFrameWnd, CXTPOffice2007FrameHook

#endif

/////////////////////////////////////////////////////////////////////////////
// CEditPane

class CEditPane : public CEdit
{
public:
	CEditPane();

	void SetOwnerPane(CXTPDockingPane* pPane);

protected:
	CBrush m_brush;
	CXTPDockingPane* m_pPane;

	//{{AFX_VIRTUAL(CEditPane)
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

public:

	//{{AFX_MSG(CEditPane)
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

class CMainFrame : public CMainFrameBase
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:
	CXTPDockingPaneManager m_paneManager;

// Operations
public:
	CXTPDockingPaneManager* GetDockingPaneManager() {
		return &m_paneManager;
	}

public:
	BOOL m_bEditor;

// Operations
public:

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

	void SwitchLayout();
	UINT m_nSelectedTheme;

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
	CThemeDlg  m_dlgTheme;

	CXTPDockingPaneLayout* m_pEditorLayout;
	CXTPDockingPaneLayout* m_pRunLayout;

	COLORREF m_clrText;
	COLORREF m_clrBack;
	COLORREF m_clrBorder;
	COLORREF m_clrBorderDark;

	CEditPane m_wndPanes[11];
	struct CustomPaneTitleBrushes {
		CBrush active;
		CBrush inactive;
	} m_customPaneTitleBrushes;
	BOOL m_fUseCustomPaneTitleBrushes;
	CFont m_fntEdit;

	XTPPaintTheme paintTheme;
	XTPDockingPanePaintTheme paintThemeDP;
	HMODULE hModule;
	LPCTSTR lpszINI;
	
	void AdjustStyle(XTPDockingPanePaintTheme theme);
	void SetDockingPaneTheme(XTPDockingPanePaintTheme nTheme, XTPDockingContextStickerStyle nStyle = xtpPaneStickerStyleVisualStudio2005, int nMargin = 0);
	void OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState);

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLayoutRun();
	afx_msg void OnLayoutEditor();
	afx_msg void OnUpdateLayoutEditor(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLayoutRun(CCmdUI *pCmdUI);
	afx_msg void OnDestroy();
	afx_msg void OnLoadFromFile();
	afx_msg void OnSaveToFile();
	afx_msg void OnLoadFromResource();
	afx_msg void OnHideClient();
	afx_msg void OnUpdateHideClient(CCmdUI *pCmdUI);
	afx_msg void OnUseSplitterTracker();
	afx_msg void OnUpdateUseSplitterTracker(CCmdUI *pCmdUI);
	afx_msg void OnThemedFloatingFrames();
	afx_msg void OnUpdateThemedFloatingFrames(CCmdUI *pCmdUI);
	afx_msg void OnAlphaContext();
	afx_msg void OnUpdateAlphaContext(CCmdUI *pCmdUI);
	afx_msg void OnDockingStickers();
	afx_msg void OnUpdateDockingStickers(CCmdUI *pCmdUI);
	afx_msg void OnMinMaxSample();
	afx_msg void OnUpdateMinMaxSample(CCmdUI *pCmdUI);
	afx_msg void OnGetMinMaxInfo(LPMINMAXINFO pMinMaxInfo);
	afx_msg void OnCaptionButtonClose();
	afx_msg void OnUpdateCaptionButtonClose(CCmdUI* pCmdUI);
	afx_msg void OnCaptionButtonAutoHide();
	afx_msg void OnUpdateCaptionButtonAutoHide(CCmdUI* pCmdUI);
	afx_msg void OnCaptionButtonMenu();
	afx_msg void OnUpdateCaptionButtonMenu(CCmdUI* pCmdUI);
	afx_msg void OnCaptionButtonMaximize();
	afx_msg void OnUpdateCaptionButtonMaximize(CCmdUI* pCmdUI);
	afx_msg void OnCaptionButtonMaximizeFloating();
	afx_msg void OnUpdateCaptionButtonMaximizeFloating(CCmdUI* pCmdUI);
	afx_msg void OnCaptionVisible();
	afx_msg void OnCaptionUseCustomTitles();
	afx_msg void OnCaptionHorizontal();
	afx_msg void OnCaptionVertical();
	afx_msg void OnCaptionAutoBySize();
	afx_msg void OnCaptionAutoByPosition();
	afx_msg void OnUpdateCaptionVisible(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCaptionUseCustomTitles(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCaptionHorizontal(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCaptionVertical(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCaptionAutoBySize(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCaptionAutoByPosition(CCmdUI* pCmdUI);
	afx_msg void OnCloseButtonAffects();
	afx_msg void OnAutoHideButtonAffects();
	afx_msg void OnUpdateCloseButtonAffects(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAutoHideButtonAffects(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShowContentsWhileDragging(CCmdUI* pCmdUI);
	afx_msg void OnShowContentsWhileDragging();
	afx_msg void OnStickyFloatingFrames();
	afx_msg void OnUpdateStickyFloatingFrames(CCmdUI* pCmdUI);
	afx_msg void OnTransparentFloatingFrames();
	afx_msg void OnUpdateTransparentFloatingFrames(CCmdUI* pCmdUI);
	afx_msg void OnEnableSideDocking();
	afx_msg void OnUpdateEnableSideDocking(CCmdUI* pCmdUI);
	afx_msg void OnDockingPaneTheme();
	//}}AFX_MSG

	afx_msg LRESULT OnThemeChanged(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

	afx_msg void OnShowPane(UINT nID);
	afx_msg LRESULT OnDockingPaneNotify(WPARAM wParam, LPARAM lParam);
#ifdef _XTP_INCLUDE_COMMANDBARS
	afx_msg void OnCustomize();
	afx_msg void OnClose();

	void SetCommandBarsTheme(XTPPaintTheme paintTheme, LPCTSTR lpszINI = NULL);
#endif

	void SwitchDefaultPaneOptions(XTPDockingPaneOptions dwOption);
	void SetTheme(XTPPaintTheme nTheme, LPCTSTR lpszINI = NULL);
};

#endif
