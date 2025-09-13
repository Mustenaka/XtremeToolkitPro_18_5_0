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

#if !defined(AFX_MAINFRM_H__C63DA51E_51DE_421C_B436_0DA0E56E92A3__INCLUDED_)
#define AFX_MAINFRM_H__C63DA51E_51DE_421C_B436_0DA0E56E92A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if 1
#define CXTPFrameWnd CFrameWnd
#endif


enum Menus
{
	mnuFile,
	mnuEdit,
	mnuSkin,
	mnuTest,
	mnuScroll,
	mnuMenuBreak,
	mnuMenuStyles,
	mnuView,
	mnuHelp
};

enum MenuFile
{
	mnuFileNew,
	mnuFileOpen,
	mnuFileSave,
	mnuFileSaveAs
};


class CMainFrame : public CXTPFrameWnd
{
protected:
	CMainFrame();
	virtual ~CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

public:
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSkin(UINT nID);
	afx_msg void OnContextItem(UINT nID);
	afx_msg void OnUpdateSkin(CCmdUI *pCmdUI);
	afx_msg LRESULT OnMenuRButtonUp(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CString GetStylesPath() const;


protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	UINT        m_nSkin;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__C63DA51E_51DE_421C_B436_0DA0E56E92A3__INCLUDED_)
