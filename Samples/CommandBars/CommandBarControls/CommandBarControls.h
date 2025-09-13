// CommandBarControls.h
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

#if !defined(AFX_COMMANDBARCONTROLS_H__A2386370_01E3_4293_AAEC_9C9DCA4FCFD6__INCLUDED_)
#define AFX_COMMANDBARCONTROLS_H__A2386370_01E3_4293_AAEC_9C9DCA4FCFD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCommandBarControlsApp:
// See CommandBarControls.cpp for the implementation of this class
//

class CCommandBarControlsApp : public CXTPWinApp
{
public:
	CCommandBarControlsApp();

	CXTPModuleHandle m_hModule2007;
	CXTPModuleHandle m_hModule2010;
	CXTPModuleHandle m_hModule2013;
	CXTPModuleHandle m_hModuleWindows7;
	CXTPModuleHandle m_hModuleVisualStudio2012;
	CXTPModuleHandle m_hModuleVisualStudio2015;

	enum AppTheme
	{
		themeDefault,
		themeVS6,
		themeVS2003,
		themeVS2005,
		themeVS2008,
		themeVS2010,
		themeVS2012Light,
		themeVS2012Dark,
		themeVS2015Blue,
		themeVS2015Dark,
		themeVS2015Light,
		themeOfficeXP,
		themeWindowsXP,
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
		themeExplorer
	};
	
	AppTheme m_theme;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommandBarControlsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCommandBarControlsApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CCommandBarControlsApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMANDBARCONTROLS_H__A2386370_01E3_4293_AAEC_9C9DCA4FCFD6__INCLUDED_)
