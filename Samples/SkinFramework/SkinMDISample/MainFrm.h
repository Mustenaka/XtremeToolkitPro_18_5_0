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

#if !defined(AFX_MAINFRM_H__784BE6B5_03A9_40F9_8DB7_58DF56AD001D__INCLUDED_)
#define AFX_MAINFRM_H__784BE6B5_03A9_40F9_8DB7_58DF56AD001D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _XTP_INCLUDE_COMMANDBARS
#define CXTPMDIFrameWnd CMDIFrameWnd
#define CXTPStatusBar CStatusBar
#endif

class CMainFrame : public CXTPMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:
	CSkinPropertySheet m_dlgThemes;

// Operations
public:
	void OnSkinChanged();
	void RedrawFrame(CWnd* pWnd);

	void OnSchemaChanged(int nSchema);

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

	void SetTheme(int nTheme);


public:  // control bar embedded members
	CXTPStatusBar  m_wndStatusBar;
	CToolBar m_wndToolBar;

	void ShowThemesDialog();
	static CString GetStylesPath();

#ifdef _XTP_INCLUDE_COMMANDBARS
	CXTPTabClientWnd m_MTIClientWnd;	
#endif

#ifdef _XTP_INCLUDE_DOCKINGPANE
	CXTPDockingPaneManager m_paneManager;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose(); 
	afx_msg void OnViewThemeDialog();
	afx_msg void OnViewTheme();
	afx_msg void OnUpdateViewTheme(CCmdUI* pCmdUI);
	//}}AFX_MSG
	
#ifdef _XTP_INCLUDE_COMMANDBARS
	afx_msg int OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl);
#endif
	afx_msg void OnCustomize();
	afx_msg void OnViewThemePopup(UINT nCommand);
	afx_msg LRESULT OnDockingPaneNotify(WPARAM wParam, LPARAM lParam);
	
	DECLARE_MESSAGE_MAP()

	void OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState);

	int m_nTheme;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__784BE6B5_03A9_40F9_8DB7_58DF56AD001D__INCLUDED_)
