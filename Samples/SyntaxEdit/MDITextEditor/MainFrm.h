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

#if !defined(AFX_MAINFRM_H__BCFEE602_5709_48B9_AC44_2E9330095000__INCLUDED_)
#define AFX_MAINFRM_H__BCFEE602_5709_48B9_AC44_2E9330095000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _XTP_INCLUDE_COMMANDBARS
#define CMainFrameBase CMDIFrameWnd
#define CXTPMDIFrameWnd CMDIFrameWnd
#else
#define CMainFrameBase CXTPMDIFrameWnd, CXTPOffice2007FrameHook
#endif

class CMainFrame : public CMainFrameBase
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:
	void SetRowCol(int nRow, int nCol);
	void UpdateMenuPopups(int nIndex);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
#ifdef _XTP_INCLUDE_COMMANDBARS
	virtual void OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState);
#endif

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members

#ifdef _XTP_INCLUDE_COMMANDBARS

	CXTPTabClientWnd m_MTIClientWnd;

	CXTPStatusBar    m_wndStatusBar;
#else
	CToolBar    m_wndToolBar;
	CStatusBar  m_wndStatusBar;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnAppInstance(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUpdateRowColIndicator(CCmdUI* pCmdUI);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//}}AFX_MSG
#ifdef _XTP_INCLUDE_COMMANDBARS
	afx_msg void OnCustomize();
	afx_msg void OnClose();
#endif
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__BCFEE602_5709_48B9_AC44_2E9330095000__INCLUDED_)
