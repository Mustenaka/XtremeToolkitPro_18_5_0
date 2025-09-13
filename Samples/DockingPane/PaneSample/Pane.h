// Pane.h 
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

#if !defined(AFX_PANE_H__512CDF02_8B26_4BE3_B704_0BEFA6C646BB__INCLUDED_)
#define AFX_PANE_H__512CDF02_8B26_4BE3_B704_0BEFA6C646BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "PaneColorSet.h"
#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPaneApp:
// See Pane.cpp for the implementation of this class
//

class CPaneApp : public CXTPWinApp
{
public:
	enum AppTheme
	{
		themeDefault,
		themeOfficeXP,
		themeOffice2003,
		themeOffice2003Luna,
		themeOffice2007Aqua,
		themeOffice2007Black,
		themeOffice2007Blue,
		themeOfficeWindows7,
		themeOffice2007Silver,
		themeOffice2010Black,
		themeOffice2010Blue,
		themeOffice2010Silver,
		themeOffice2013,
		themeExplorer,
		themeVisualStudio2012Light,
		themeVisualStudio2012Dark
	};	
	AppTheme m_theme;

	CPaneColorSet m_csPane;

public:
	CPaneApp();

// Overrides
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaneApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	CString GetModulePath();

// Implementation
	//{{AFX_MSG(CPaneApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

extern CPaneApp theApp;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANE_H__512CDF02_8B26_4BE3_B704_0BEFA6C646BB__INCLUDED_)
