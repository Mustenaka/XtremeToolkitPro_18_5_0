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

#if !defined(AFX_MAINFRM_H__E6D95F91_FCF6_4C13_A74C_E25D863697E5__INCLUDED_)
#define AFX_MAINFRM_H__E6D95F91_FCF6_4C13_A74C_E25D863697E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PaneStyles.h"

#include "BackstagePageInfo.h"
#include "BackstagePageHelp.h"
#include "BackstagePageSave.h"

class CMainFrame : public CXTPFrameWnd, CXTPOffice2007FrameHook
{
	DECLARE_DYNCREATE(CMainFrame)
	
protected: // create from serialization only
	CMainFrame();
	virtual ~CMainFrame();

// Attributes
public:
	void Reset();

// Operations
public:
	CXTPControlGalleryItems* m_pItemsShapes;
	CXTPControlGalleryItems* m_pItemsStyles;
	CXTPControlGalleryItems* m_pItemsStyleSet;
	CXTPControlGalleryItems* m_pItemsThemeColors;
	CXTPControlGalleryItems* m_pItemsThemeFonts;
	
	CXTPControlGalleryItems* m_pItemsFontTextColor;
	CXTPControlGalleryItems* m_pItemsFontBackColor;
	CXTPControlGalleryItems* m_pItemsFontFace;
	CXTPControlGalleryItems* m_pItemsFontSize;
	CXTPControlGalleryItems* m_pItemsUndo;
	CXTPControlGalleryItems* m_pItemsColumns;

	CXTPRibbonBar* pRibbonBar;

	void SetStyle(int nTheme);
	void SetTheme(int nTheme);
	void SetStateColor();

	void SetCommandBarsTheme(XTPPaintTheme paintTheme, LPCTSTR lpszINI = NULL);
#ifdef _XTP_INCLUDE_DOCKINGPANE
	void SetDockingPaneTheme(XTPDockingPanePaintTheme nTheme, int nMargin = 0);
#endif

	enum EOffice2013Gray
	{
		eGrayNone,
		eGrayDark,
		eGrayLight
	};
	EOffice2013Gray m_eOffice2013Gray;

	enum EStudio2015State
	{
		eStateClosed,
		eStateOpen,
		eStateDebug
	};
	EStudio2015State m_eStudio2015State;

	CRibbonSampleApp::AppTheme m_enumTheme;
	UINT m_nRibbonBackImage;
	int m_nOfficeTheme;

	void CreateGalleries();
	int m_nShape;
	int m_nStyle;
	int m_nColumns;

	int m_nStyleSet;
	int m_nThemeColors;
	int m_nThemeFonts;

	BOOL m_bAnimation;
	BOOL m_bLayoutRTL;

	int m_bShowMiniToolbar;

	CXTPMessageBar m_wndMessageBar;
	UINT m_nRibbonStyle;
	BOOL m_bOverrideAllowDwm;
	BOOL m_bEnableFrameTheme;

	CBackstagePageInfo m_pageInfo;
	CBackstagePageHelp m_pageHelp;
	CBackstagePageSave m_pageSave;
	CXTPRibbonBackstagePageRecent m_pageRecent;
	CXTPRibbonBackstagePageRecent m_pageDisabled;
	CXTPRibbonBackstagePagePrint m_pagePrint;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:

	afx_msg void OnBackstagePageRecentContextMenu(NMHDR* pNMHDR, LRESULT* plResult);


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CXTPStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CThemeDlg   m_dlgTheme;

	BOOL CreateRibbonBar();
	BOOL CreateMiniToolBar();
	BOOL CreateStatusBar();
	BOOL CreateMessageBar();

	void OnGalleryColumns(NMHDR* pNMHDR, LRESULT* pResult);
	void OnUpdateGalleryColumns(CCmdUI* pCmdUI);


	void CreateDockingPane();

#ifdef _XTP_INCLUDE_DOCKINGPANE
	CXTPDockingPaneManager m_paneManager;
	CPaneStyles m_paneStyles;
#endif


	CString m_csStylesPath;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnOptionsAnimation();
	afx_msg void OnUpdateOptionsAnimation(CCmdUI* pCmdUI);
	afx_msg void OnOptionsRightToLeft();
	afx_msg void OnUpdateOptionsRighttoleft(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionsStyle(CCmdUI* pCmdUI);
	afx_msg void OnToggleGroups();
	afx_msg void OnOptionsFont(UINT nID);
	afx_msg void OnUpdateOptionsFont(CCmdUI* pCmdUI);
	// Styles
	afx_msg void OnOptionsStyleOffice2013LtGray();
	afx_msg void OnUpdateOptionsStyleOffice2013LtGray(CCmdUI* pCmdUI);
	afx_msg void OnOptionsStyleOffice2013DkGray();
	afx_msg void OnUpdateOptionsStyleOffice2013DkGray(CCmdUI* pCmdUI);
	afx_msg void OnOptionsStyleVisualStudio2015Closed();
	afx_msg void OnUpdateOptionsStyleVisualStudio2015Closed(CCmdUI* pCmdUI);
	afx_msg void OnOptionsStyleVisualStudio2015Open();
	afx_msg void OnUpdateOptionsStyleVisualStudio2015Open(CCmdUI* pCmdUI);
	afx_msg void OnOptionsStyleVisualStudio2015Debug();
	afx_msg void OnUpdateOptionsStyleVisualStudio2015Debug(CCmdUI* pCmdUI);
	afx_msg void OnOptionsStyle(UINT nStyle);
	afx_msg void OnStyleOffice2007(UINT nStyle);
	afx_msg void OnStyleOffice2010(UINT nStyle);
	afx_msg void OnOptionsStyleOffice2013(UINT nStyle);
	afx_msg void OnOptionsStyleVisualStudio2015(UINT nStyle);
	afx_msg void OnStyleWindows7();
	afx_msg void OnOptionsStyleOffice2013Back(UINT nStyle);
	afx_msg void OnUpdateOptionsStyleOffice2013Back(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAllowDwm(CCmdUI* pCmdUI);
	afx_msg void OnAllowDwm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	void OnEmptyCommandRange(UINT);
	void OnEmptyCommand();

	void OnSwitchCommand();
	void OnUpdateSwitchCommand(CCmdUI* pCmdUI);
	void OnUpdateViewShowHide(CCmdUI* pCmdUI);
	void OnViewShowHide(UINT nID);
	
	void OnRibbonTabChanged(NMHDR* /*pNMHDR*/, LRESULT* /*pRes*/);
	void OnRibbonTabChanging(NMHDR* /*pNMHDR*/, LRESULT* /*pRes*/);

	void OnCustomize();
	void OnCustomizeQuickAccess();
	void ShowCustomizeDialog(int nSelectedPage);
	void OnAutoResizeIcons();
	void OnUpdateAutoResizeIcons(CCmdUI* pCmdUI);
	void OnDpiIconsScalling();
	void OnUpdateDpiIconsScalling(CCmdUI* pCmdUI);

	BOOL m_bChecked;
	BOOL m_bBackstageStyle2013;
	BOOL m_bOptions[6];

	CString m_strIniFileName;

	void OnGalleryShapes(NMHDR* pNMHDR, LRESULT* pResult);
	void OnUpdateGalleryShapes(CCmdUI* pCmdUI);

	void OnGalleryStyles(NMHDR* pNMHDR, LRESULT* pResult);
	void OnUpdateGalleryStyles(CCmdUI* pCmdUI);

	void OnGalleryStyleSet(NMHDR* pNMHDR, LRESULT* pResult);
	void OnUpdateGalleryStyleSet(CCmdUI* pCmdUI);

	void OnGalleryThemeColors(NMHDR* pNMHDR, LRESULT* pResult);
	void OnUpdateGalleryThemeColors(CCmdUI* pCmdUI);

	void OnGalleryTable(NMHDR* pNMHDR, LRESULT* pResult);
	void OnUpdateGalleryTable(CCmdUI* pCmdUI);

	void OnGalleryThemeFonts(NMHDR* pNMHDR, LRESULT* pResult);
	void OnUpdateGalleryThemeFonts(CCmdUI* pCmdUI);

	int OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl);

	void OnFrameTheme();
	void OnUpdateFrameTheme(CCmdUI* pCmdUI);

	void OnStatusBarSwitchView(UINT nID);

	void LoadDefaultIcons();
	void LoadDefaultIcons(BOOL bDark);
	void Load2013Icons();
	void SetBackstageTheme();
	afx_msg void OnUpdateCommands();
	void OnMacroClick();
	void EnableActions();

	void OnUpdateKeyIndicator(CCmdUI* pCmdUI);

	void CreateBackstage();
	void CreateSystemMenuPopup();

	void OnUpdateRibbonMinimize(CCmdUI* pCmdUI);
	void OnUpdateRibbonExpand(CCmdUI* pCmdUI);

	void OnGetMinMaxInfo(MINMAXINFO* lpMMI);

	LRESULT OnMessageBarClosed(WPARAM wParam, LPARAM lParam);

	XTPToolTipStyle GetToolTipStyle() const;

	BOOL SetFrameIcon(CSize szIcon);
	void SetRibbonBackImage(int nBack);
	void SetOffice2016Theme(LPCTSTR lpszINI = NULL);
public:
	afx_msg void OnOptionsBackstageStyle2013();
	afx_msg void OnUpdateOptionsBackstageStyle2013(CCmdUI *pCmdUI);
	afx_msg void OnViewOfficeTheme();
	afx_msg LRESULT OnThemeChanged(WPARAM wParam, LPARAM lParam);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__E6D95F91_FCF6_4C13_A74C_E25D863697E5__INCLUDED_)
