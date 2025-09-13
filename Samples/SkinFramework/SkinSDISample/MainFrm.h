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

#if !defined(AFX_MAINFRM_H__FCDA550E_5B06_4B3A_A937_12467FFC5E62__INCLUDED_)
#define AFX_MAINFRM_H__FCDA550E_5B06_4B3A_A937_12467FFC5E62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _XTP_INCLUDE_COMMANDBARS
#define CXTPFrameWnd CFrameWnd
#define CXTPStatusBar CStatusBar
#endif

class CMainFrame : public CXTPFrameWnd
{

protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CSplitterWnd m_wndSplitter;
	CString m_strStylesPath;

	void LoadSkin(int nSkin);
	void SetTheme(int nTheme, BOOL bFlat);
	void OnSkinChanged();

public:

	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CXTPStatusBar  m_wndStatusBar;
	CToolBar m_wndToolBar;
	CToolBar m_wndReBarToolBar;
	CReBar m_wndReBar;
	CComboBox m_wndComboBox;
	CXTPImageList m_imgListReBar;
	CFont m_fntUI;

protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg LRESULT OnMenuChar(UINT nChar, UINT nFlags, CMenu *pMenu);
	//}}AFX_MSG
	afx_msg void OnCustomize();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_MAINFRM_H__FCDA550E_5B06_4B3A_A937_12467FFC5E62__INCLUDED_)
