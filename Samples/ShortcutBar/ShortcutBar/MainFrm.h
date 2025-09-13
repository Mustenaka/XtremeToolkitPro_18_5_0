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

#if !defined(AFX_MAINFRM_H__9D907276_5C73_4B62_A824_6E2EF45A3300__INCLUDED_)
#define AFX_MAINFRM_H__9D907276_5C73_4B62_A824_6E2EF45A3300__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef _XTP_INCLUDE_COMMANDBARS
#define CStatusBar CXTPStatusBar
#define CFrameWnd  CXTPFrameWnd
#endif

#include "ShortcutPaneMail.h"
#include "ShortcutPaneCalendar.h"
#include "ShortcutPaneFolders.h"
#include "ShortcutPaneContacts.h"
#include "ShortcutPaneTasks.h"
#include "ShortcutPaneShortcuts.h"
#include "ShortcutPaneNotes.h"
#include "ShortcutPaneJournal.h"

#include "ShortcutBarSplitter.h"

class CMainFrame : public CFrameWnd
#ifdef _XTP_INCLUDE_COMMANDBARS
	, CXTPOffice2007FrameHook
#endif
{

protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CShortcutBarSplitter m_wndSplitter;
	CSplitterWndEx m_wndSplitter2;

	CXTPShortcutBar m_wndShortcutBar;

	CImageList m_ilSmallShortcuts;
	CImageList m_ilLargeShortcuts;

	BOOL m_bClientPane;



	CShortcutPaneMail m_paneMail;
	CShortcutPaneCalendar m_paneCalendar;
	CShortcutPaneFolders m_paneFolders;
	CShortcutPaneContacts m_paneContacts;
	
	CShortcutPaneTasks m_paneTasks;
	CShortcutPaneNotes m_paneNotes;
	CShortcutPaneShortcuts m_paneShortcuts;
	CShortcutPaneJournal m_paneJournal;

// Operations
public:
	void CreateShortcutBar();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar m_wndStatusBar;
	CToolBar   m_wndToolBar;
	CString    m_csStylesPath;
	CThemeDlg  m_dlgTheme;

	void SetTheme(int nTheme, LPCTSTR lpszINI = NULL);

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnThemeClientpane();
	afx_msg void OnUpdateThemeClientpane(CCmdUI* pCmdUI);
	afx_msg void OnThemeShowexpandbutton();
	afx_msg void OnUpdateThemeShowexpandbutton(CCmdUI* pCmdUI);
	afx_msg void OnThemeShowactiveitemontop();
	afx_msg void OnUpdateThemeShowactiveitemontop(CCmdUI* pCmdUI);
	afx_msg void OnThemeAllowfreeresize();
	afx_msg void OnUpdateThemeAllowfreeresize(CCmdUI* pCmdUI);
	afx_msg void OnThemeSelectTheme();
	//}}AFX_MSG
	afx_msg void OnCustomize();
	afx_msg LRESULT OnShortcutBarNotify(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnThemeChanged(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__9D907276_5C73_4B62_A824_6E2EF45A3300__INCLUDED_)
