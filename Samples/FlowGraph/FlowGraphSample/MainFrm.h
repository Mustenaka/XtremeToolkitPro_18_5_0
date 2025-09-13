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

#if !defined(AFX_MAINFRM_H__5F1EF821_79D6_4C6F_B81F_622341F9472A__INCLUDED_)
#define AFX_MAINFRM_H__5F1EF821_79D6_4C6F_B81F_622341F9472A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#ifndef _XTP_INCLUDE_COMMANDBARS
#define CXTPFrameWnd CFrameWnd
#define  CXTPStatusBar CStatusBar
#endif



#ifdef _XTP_INCLUDE_COMMANDBARS
class CMainFrame : public CXTPFrameWnd, CXTPOffice2007FrameHook
#else
class CMainFrame : public CFrameWnd
#endif
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CImageList m_ilToolbarIcons;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

protected:

#ifdef _XTP_INCLUDE_DOCKINGPANE

	CXTPDockingPaneManager m_paneManager;

	void SetDockingPaneTheme(XTPDockingPanePaintTheme theme);
	afx_msg LRESULT OnDockingPaneNotify(WPARAM wParam, LPARAM lParam);
#endif

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

#ifdef _XTP_INCLUDE_TASKPANEL
	CXTPTaskPanelGroup* CreateToolboxGroup(UINT nID, LPCTSTR szGroupCaption);

	CXTPTaskPanelGroupItem* AddToolboxGroupItem(CXTPTaskPanelGroup* pGroup, UINT nID, UINT nImageID, UINT uResShapeID, const CString sCaption = CString());

	CXTPTaskPanelGroupItem* AddToolboxGroupItem(CXTPTaskPanelGroup* pGroup, UINT nID, UINT nImageID, const CString sCaption);

	CXTPOfficeBorder<CXTPTaskPanel> m_wndTaskPanel;

	CWnd* CreateToolBox();
#endif

#ifdef _XTP_INCLUDE_PROPERTYGRID

	CXTPOfficeBorder<CXTPPropertyGrid> m_wndPropertyGrid;

	CWnd* CreateGrid();

#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTestGraphwith500nodes();
	afx_msg void OnTestNodeswithcontrols();
	afx_msg void OnTestPagetransition();
	
	afx_msg LRESULT OnTaskPanelNotify(WPARAM wParam, LPARAM lParam);

	afx_msg void OnUpdateContextTests(CCmdUI *pCmdUi);

#ifdef _XTP_INCLUDE_COMMANDBARS
	void OnInitCommandsPopup(CXTPPopupBar* pComandBar);

	void OnGraphChanged(NMHDR* pNMHDR, LRESULT* pResult);
	void OnGraphChanged_Update(CCmdUI *pUi);

	BOOL SetFrameIcon(CSize szIcon);
#endif
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__5F1EF821_79D6_4C6F_B81F_622341F9472A__INCLUDED_)
