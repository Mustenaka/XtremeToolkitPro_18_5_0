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

#if !defined(AFX_MAINFRM_H__E1168CEC_BBCF_49A0_BC84_100961D01324__INCLUDED_)
#define AFX_MAINFRM_H__E1168CEC_BBCF_49A0_BC84_100961D01324__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef _XTP_INCLUDE_COMMANDBARS
#define CMainFrameBase CXTPFrameWnd
#else
#ifdef _XTP_INCLUDE_CONTROLBARS
#define CMainFrameBase CXTFrameWnd
#else
#define CMainFrameBase CFrameWnd
#define CXTStatusBar CStatusBar
#define CXTToolBar CToolBar
#endif
#endif

class CMainFrame : public CMainFrameBase
#ifdef _XTP_INCLUDE_COMMANDBARS
	, CXTPCommandBarsFrameHook
#endif
{	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

public:

	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
#ifdef _XTP_INCLUDE_COMMANDBARS
	CXTPStatusBar   m_wndStatusBar;
	int OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl);
#else
	CXTStatusBar   m_wndStatusBar;
	CXTToolBar     m_wndToolBar;
#endif
	CXTPRegistryManager m_regMgr;
	int            m_iTheme;
	void SetTheme(int iTheme);

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewThemeOfficeXP();
	afx_msg void OnUpdateViewThemeOfficeXP(CCmdUI* pCmdUI);
	afx_msg void OnViewDefaultTheme();
	afx_msg void OnUpdateViewDefaultTheme(CCmdUI* pCmdUI);
	afx_msg void OnViewOffice2013Theme();
	afx_msg void OnUpdateViewOffice2013Theme(CCmdUI* pCmdUI);
	afx_msg void OnViewOffice2016Theme();
	afx_msg void OnUpdateViewOffice2016Theme(CCmdUI* pCmdUI);
	//}}AFX_MSG
#ifdef _XTP_INCLUDE_COMMANDBARS
	afx_msg void OnClose();
	afx_msg void OnCustomize();
#endif
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__E1168CEC_BBCF_49A0_BC84_100961D01324__INCLUDED_)
