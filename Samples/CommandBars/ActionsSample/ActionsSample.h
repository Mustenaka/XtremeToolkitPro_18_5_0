// ActionsSample.h
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

#if !defined(AFX_ACTIONSSAMPLE_H__9DF2AE05_1713_4657_AC0E_71DE91D2C7C7__INCLUDED_)
#define AFX_ACTIONSSAMPLE_H__9DF2AE05_1713_4657_AC0E_71DE91D2C7C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CActionsSampleApp:
// See ActionsSample.cpp for the implementation of this class
//

class CActionsSampleApp : public CXTPWinApp
{
public:
	CActionsSampleApp();

	CXTPModuleHandle m_hModule2007;
	CXTPModuleHandle m_hModule2010;
	CXTPModuleHandle m_hModule2013;
	CXTPModuleHandle m_hModule2012;
	CXTPModuleHandle m_hModule2015;
	CXTPModuleHandle m_hModuleWindows7;
	//CXTPModuleHandle m_hModuleWindows8;

	enum AppTheme
	{
		themeOffice2000,
		themeOfficeXP,
		themeOffice2003,
		themeWindowsXP,
		themeRibbon,
		themeOffice2003Luna,
		themeOffice2007Aqua,
		themeOffice2007Black,
		themeOffice2007Blue,
		themeOffice2007Silver,
		themeOffice2007System,
		themeOffice2010Black,
		themeOffice2010Blue,
		themeOffice2010Silver,
		themeOffice2013Word,
		themeOffice2013Excel,
		themeOffice2013Access,
		themeOffice2013Powerpoint,
		themeOffice2013OneNote,
		themeOffice2013Outlook,
		themeWindows7,
		themeVisualStudio6,
		themeVisualStudio7,
		themeVisualStudio8,
		themeVisualStudio9,
		themeVisualStudio10,
		themeVisualStudio2012Light,
		themeVisualStudio2012Dark,
		themeVisualStudio2015Light,
		themeVisualStudio2015Blue,
		themeVisualStudio2015Dark,
	};
	AppTheme m_theme;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CActionsSampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CActionsSampleApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


extern CActionsSampleApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACTIONSSAMPLE_H__9DF2AE05_1713_4657_AC0E_71DE91D2C7C7__INCLUDED_)
