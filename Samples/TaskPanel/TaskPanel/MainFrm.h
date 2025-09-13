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

#if !defined(AFX_MAINFRM_H__23C539D4_D35C_4487_A4DE_CF7DEACA0909__INCLUDED_)
#define AFX_MAINFRM_H__23C539D4_D35C_4487_A4DE_CF7DEACA0909__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef _XTP_INCLUDE_CONTROLS
#define CSplitterWnd CXTPSplitterWnd
#endif
#ifndef _XTP_INCLUDE_COMMANDBARS
class CMainFrame : public CFrameWnd
#else
#define CFrameWnd    CXTPFrameWnd
#define CStatusBar   CXTPStatusBar

class CMainFrame : public CFrameWnd, CXTPCommandBarsFrameHook
#endif
{

protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

public:
	CSplitterWnd  m_wndSplitter;
	CXTPTaskPanel m_wndTaskPanel;

	BOOL CreateTaskPanel();

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
	CThemeDlg  m_dlgTheme;

	void SetTheme(int nTheme, LPCTSTR lpszINI = NULL, CXTPTaskPanelPaintManager* pPaintManager = NULL);
	void CreateTaskPanelItems();

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTaskpanelAnimation();
	afx_msg void OnUpdateTaskpanelAnimation(CCmdUI* pCmdUI);
	afx_msg void OnViewSearch();
	afx_msg void OnClose();
	afx_msg void OnTaskPanelSelectTheme();
	//}}AFX_MSG
#if defined(_XTP_INCLUDE_COMMANDBARS) && defined(_XTP_INCLUDE_CONTROLS)
	afx_msg void OnCustomize();
#endif
	afx_msg LRESULT OnTaskPanelNotify(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnThemeChanged(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__23C539D4_D35C_4487_A4DE_CF7DEACA0909__INCLUDED_)
