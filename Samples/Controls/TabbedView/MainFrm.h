// MainFrm.h 
//
// (c)1998-2018 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO 
// BE RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED 
// WRITTEN CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS 
// OUTLINED IN THE XTREME TOOLKIT LICENSE AGREEMENT.  CODEJOCK SOFTWARE 
// GRANTS TO YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE 
// THIS SOFTWARE ON A SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__D80166BE_BC10_4CEF_9938_0DFD5C6D2B40__INCLUDED_)
#define AFX_MAINFRM_H__D80166BE_BC10_4CEF_9938_0DFD5C6D2B40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#ifdef _XTP_INCLUDE_COMMANDBARS
#define CMainFrameBase CXTPMDIFrameWnd
#else
#ifdef _XTP_INCLUDE_CONTROLBARS
#define CMainFrameBase CXTMDIFrameWnd
#else
#define CMainFrameBase CMDIFrameWnd
#define CXTStatusBar   CStatusBar
#define CXTToolBar     CToolBar
#endif
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
	void SetTheme(int iTheme);

#ifdef _XTP_INCLUDE_COMMANDBARS
	CXTPStatusBar   m_wndStatusBar;
#else
	CXTStatusBar   m_wndStatusBar;
	CXTToolBar     m_wndToolBar;
#endif
	CXTPRegistryManager m_regMgr;

public:
	int            m_iTheme;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewThemeOfficeXP();
	afx_msg void OnUpdateViewThemeOfficeXP(CCmdUI* pCmdUI);
	//}}AFX_MSG
#ifdef _XTP_INCLUDE_COMMANDBARS
	afx_msg void OnClose() ;
	afx_msg void OnCustomize();
#endif
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__D80166BE_BC10_4CEF_9938_0DFD5C6D2B40__INCLUDED_)

