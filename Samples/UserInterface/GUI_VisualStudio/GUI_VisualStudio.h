// GUI_VisualStudio.h 
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

#if !defined(AFX_GUI_VISUALSTUDIO_H__43A4C0AC_0369_4063_BC19_7EBCB371EFD9__INCLUDED_)
#define AFX_GUI_VISUALSTUDIO_H__43A4C0AC_0369_4063_BC19_7EBCB371EFD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "PaneColorSet.h"
#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGUI_VisualStudioApp:
// See GUI_VisualStudio.cpp for the implementation of this class
//

class CGUI_VisualStudioApp : public CXTPWinApp
{
public:

	CString strSchema;
	CString strColor;
	AppTheme m_theme;
	CPaneColorSet m_csPane;

public:
	CGUI_VisualStudioApp();

	CMultiDocTemplate*	pDocTemplate;

	void UpdateAllViews(CView* pSender=NULL);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGUI_VisualStudioApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CGUI_VisualStudioApp)
	afx_msg void OnAppAbout();
	afx_msg void OnWindowCloseAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

AFX_INLINE BOOL CreateImageList(CXTPImageList& il, UINT nID)
{
	if (!il.Create(16, 16, ILC_MASK|ILC_COLOR24, 0, 1))
		return FALSE;
	CBitmap bmp;
	VERIFY(bmp.LoadBitmap(nID));

	il.Add(&bmp, CXTPImageManager::GetBitmapMaskColor(bmp, CPoint(0, 0)));

	return TRUE;
}

extern CGUI_VisualStudioApp theApp;

/////////////////////////////////////////////////////////////////////////////

const UINT WM_REFRESHMETRICS = ::RegisterWindowMessage(_T("WM_REFRESHMETRICS"));

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUI_VISUALSTUDIO_H__43A4C0AC_0369_4063_BC19_7EBCB371EFD9__INCLUDED_)
