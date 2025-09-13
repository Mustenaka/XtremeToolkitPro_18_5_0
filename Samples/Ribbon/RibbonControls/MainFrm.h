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

#if !defined(AFX_MAINFRM_H__C5D27100_EA55_4DC1_9F25_A3913E16E73D__INCLUDED_)
#define AFX_MAINFRM_H__C5D27100_EA55_4DC1_9F25_A3913E16E73D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CXTPFrameWnd
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
	CXTPStatusBar  m_wndStatusBar;

	int CalculateColorGalleryHeight(CXTPControlGallery *pGallery, int iWidth);

	BOOL CreateRibbonBar();
	BOOL CreateStatusBar();



// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	afx_msg int OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl);
	afx_msg void OnEnableButton(CCmdUI* pCmdUI);

	afx_msg void OnCheckbox(UINT nID);
	afx_msg void OnRadioButton(UINT nID);
	afx_msg void OnUpdateCheckbox(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRadioButton(CCmdUI* pCmdUI);
	afx_msg void OnToggleButton();
	afx_msg void OnUpdateToggleButton(CCmdUI* pCmdUI);
	
	
	afx_msg void OnOptionsRighttoleft();
	afx_msg void OnUpdateOptionsRighttoleft(CCmdUI* pCmdUI);
	afx_msg void OnOptionsStyle(UINT nStyle);
	afx_msg void OnUpdateOptionsStyle(CCmdUI* pCmdUI);
	afx_msg void OnStyleOffice2007(UINT nStyle);
	afx_msg void OnStyleOffice2010(UINT nStyle);
	afx_msg void OnOptionsStyleOffice2013(UINT nStyle);
	afx_msg void OnOptionsFont(UINT nID);
	afx_msg void OnUpdateOptionsFont(CCmdUI* pCmdUI);
	afx_msg void OnAutoResizeIcons();
	afx_msg void OnUpdateAutoResizeIcons(CCmdUI* pCmdUI);
	afx_msg void OnDpiIconsScalling();
	afx_msg void OnUpdateDpiIconsScalling(CCmdUI* pCmdUI);

	UINT m_nRibbonStyle;

	CXTPControlGalleryItems* m_pItemsFontFace;
	CXTPControlGalleryItems* m_pItemsStyles;
	CXTPControlGalleryItems* m_pItemsTable;
	CXTPControlGalleryItems* m_pItemsFontTextColor;
	CXTPControlGalleryItems* m_pItemsUndo;

	void OnUpdateEditUndo(CCmdUI* pCmd);
	void OnEditUndo(NMHDR* pNMHDR, LRESULT* pResult);
	void OnSelectorText(NMHDR* pNMHDR, LRESULT* pResult);
	void OnUpdateSelectorText(CCmdUI* pCmdUI);

	void SetCommandBarsTheme(XTPPaintTheme paintTheme, HMODULE hModule=NULL, LPCTSTR lpszINI=NULL);
	
	void CreateBackstage();
	void CreateSystemMenuPopup();
	void Load2013Icons();
	void LoadDefaultIcons();
	BOOL m_bCheckbox[3];
	int m_nRadioButton;
	COLORREF m_clr;
	BOOL m_bToggleButton;

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__C5D27100_EA55_4DC1_9F25_A3913E16E73D__INCLUDED_)
