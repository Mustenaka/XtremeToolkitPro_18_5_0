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

#if !defined(AFX_MAINFRM_H__6EF5FD88_874F_4508_B332_F53B60A56122__INCLUDED_)
#define AFX_MAINFRM_H__6EF5FD88_874F_4508_B332_F53B60A56122__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OptionsDialogBar.h"

#ifdef _XTP_INCLUDE_COMMANDBARS
	#define CMainFrameBase CXTPFrameWnd, CXTPOffice2007FrameHook
	#define CStatusBar  CXTPStatusBar
#else
	#define CMainFrameBase CFrameWnd
#endif

class CDatePickerDialogBar : public CDialogBar
{
public:
	CDatePickerDialogBar();   // standard constructor	
	~CDatePickerDialogBar(){};

	CXTPDatePickerControl m_wndDatePicker;

protected:
	afx_msg void OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void ResizeDatePicker();

	DECLARE_MESSAGE_MAP()
};

class CMainFrame : public CMainFrameBase
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CDatePickerDialogBar m_dlgDatePicker;
	COptionsDialogBar m_dlgOptions;	

#ifdef _XTP_INCLUDE_COMMANDBARS
	CXTPRibbonBar* m_pRibbonBar;
	void Load2013Icons();
	BOOL CreateRibbonBar();
	void CreateBackstage();
	void CreateSystemMenuPopup();
#endif
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

//protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CThemeDlg   m_dlgTheme;

	enum EStudio2015State
	{
		eStateClosed,
		eStateOpen,
		eStateDebug
	}
	m_eStudio2015State;

protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewOfficeTheme();
#ifdef _XTP_INCLUDE_COMMANDBARS
	afx_msg void OnOptionsStyleVisualStudio2015Closed();
	afx_msg void OnUpdateOptionsStyleVisualStudio2015Closed(CCmdUI* pCmdUI);
	afx_msg void OnOptionsStyleVisualStudio2015Open();
	afx_msg void OnUpdateOptionsStyleVisualStudio2015Open(CCmdUI* pCmdUI);
	afx_msg void OnOptionsStyleVisualStudio2015Debug();
	afx_msg void OnUpdateOptionsStyleVisualStudio2015Debug(CCmdUI* pCmdUI);
#endif
	//}}AFX_MSG
	afx_msg LRESULT OnThemeChanged(WPARAM wParam, LPARAM lParam);

#ifdef _XTP_INCLUDE_COMMANDBARS
	void OnEmptyCommandRange(UINT);
	void OnEmptyCommand();
	void SetStateColor();
#ifdef _XTP_INCLUDE_RIBBON
	BOOL SetRibbonBackImage(int nBack);
#endif
#endif

	void SetTheme(int nTheme, LPCTSTR lpszINI);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__6EF5FD88_874F_4508_B332_F53B60A56122__INCLUDED_)
