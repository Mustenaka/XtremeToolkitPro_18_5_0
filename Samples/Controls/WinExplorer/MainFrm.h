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

#if !defined(AFX_MAINFRM_H__370FD79D_FD3D_4788_8A51_8E4A873FEA51__INCLUDED_)
#define AFX_MAINFRM_H__370FD79D_FD3D_4788_8A51_8E4A873FEA51__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CShellTreeView;
class CShellListView;

#ifdef _XTP_INCLUDE_COMMANDBARS
#define CMainFrameBase CXTPFrameWnd
#else
#define CMainFrameBase CFrameWnd
#define CXTStatusBar CStatusBar
#define CXTToolBar CToolBar
#endif

class CAddressComboBox : public CComboBoxEx
{
	BOOL PreTranslateMessage(MSG* pMsg);
};

class CMainFrame : public CMainFrameBase
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

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
	void UpdateTheme();
#ifdef _XTP_INCLUDE_COMMANDBARS

	CXTPStatusBar   m_wndStatusBar;
#else
	void InitAddressBar();

	CXTStatusBar   m_wndStatusBar;
	CXTToolBar     m_wndToolBar;
#endif
    CXTPSplitterWndEx   m_wndSplitter;
    CAddressComboBox   m_wndAddressCombo;
    CXTPWindowPos       m_wndPosition;
    CShellTreeView*    m_pTreeView;
    CShellListView*    m_pListView;
    CXTPRegistryManager m_regMgr;
    BOOL               m_bOfficeTheme;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewThemeOfficeXP();
	afx_msg void OnUpdateViewThemeOfficeXP(CCmdUI* pCmdUI);
	afx_msg void OnViews();
	afx_msg void OnFolders();
	afx_msg void OnUpdateFolders(CCmdUI* pCmdUI);
	//}}AFX_MSG
#ifdef _XTP_INCLUDE_COMMANDBARS
	afx_msg void OnClose();
	afx_msg void OnCustomize();
	afx_msg int OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl); // Called by the XTK to create the controls on the CommandBars
#endif
	afx_msg void OnViewStyle(UINT nCommandID);
	afx_msg void OnUpdateViewStyles(CCmdUI* pCmdUI);
	afx_msg void OnAddressBarEnter();
	afx_msg void OnSelEndOkAddressBar();
	DECLARE_MESSAGE_MAP()

	friend class CShellTreeView;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__370FD79D_FD3D_4788_8A51_8E4A873FEA51__INCLUDED_)
