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

#if !defined(AFX_MAINFRM_H__CBFD0AD7_BE56_477B_B837_281F1370F9EE__INCLUDED_)
#define AFX_MAINFRM_H__CBFD0AD7_BE56_477B_B837_281F1370F9EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMDIWndTab : public CXTPMDIWndTab
{
#ifdef _XTP_INCLUDE_COMMANDBARS
protected:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
#endif
};

#ifdef _XTP_INCLUDE_COMMANDBARS
#define CMainFrameBase CXTPMDIFrameWnd
#else
#ifdef _XTP_INCLUDE_CONTROLBARS
#define CMainFrameBase CXTMDIFrameWnd
#else
#define CMainFrameBase CMDIFrameWnd
#define CXTStatusBar CStatusBar
#define CXTToolBar CToolBar
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
    
    CMDIWndTab& GetMDITabWindow() {
        return m_wndMDITabWindow;
    }

    void ToggleMDITabs();
    void HideMDITabs();

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
	CMDIWndTab m_wndMDITabWindow;
	BOOL         m_bAlignment[4];
	BOOL         m_bMDIActive;
	CXTPRegistryManager m_regMgr;
	int            m_iTheme;

	enum ALIGNMENT { left, top, right, bottom };

	void SetMDITabStyle();
	void SetAlignment(ALIGNMENT eAlign);

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnActivate();
	afx_msg void OnClosedocument();
	afx_msg void OnHidetabs();
	afx_msg void OnAligntableft();
	afx_msg void OnAligntabtop();
	afx_msg void OnAligntabright();
	afx_msg void OnAligntabbottom();
	afx_msg void OnUpdateAligntableft(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAligntabtop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAligntabright(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAligntabbottom(CCmdUI* pCmdUI);
	afx_msg void OnShowMditabs();
	afx_msg void OnUpdateShowMditabs(CCmdUI* pCmdUI);
	afx_msg void OnViewThemeOfficeXP();
	afx_msg void OnUpdateViewThemeOfficeXP(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWindowCascade(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWindowTileHorz(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWindowArrange(CCmdUI* pCmdUI);
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

#endif // !defined(AFX_MAINFRM_H__CBFD0AD7_BE56_477B_B837_281F1370F9EE__INCLUDED_)
