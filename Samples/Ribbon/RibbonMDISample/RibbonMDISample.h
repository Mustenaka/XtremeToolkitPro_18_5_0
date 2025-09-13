// RibbonMDISample.h
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

#if !defined(AFX_RIBBONMDISAMPLE_H__20064B00_7EA6_449F_A9E1_EA9D707C34CD__INCLUDED_)
#define AFX_RIBBONMDISAMPLE_H__20064B00_7EA6_449F_A9E1_EA9D707C34CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRibbonMDISampleApp:
// See RibbonMDISample.cpp for the implementation of this class
//

class CRibbonMDISampleApp : public CXTPWinApp
{
public:

	CXTPModuleHandle m_hModule2007;
	CXTPModuleHandle m_hModule2010;
	CXTPModuleHandle m_hModule2013;
	CXTPModuleHandle m_hModule2016;
	CXTPModuleHandle m_hModuleWin7;

	HINSTANCE hRichEditDll;

	CRibbonMDISampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRibbonMDISampleApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CRibbonMDISampleApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CRibbonMDISampleApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RIBBONMDISAMPLE_H__20064B00_7EA6_449F_A9E1_EA9D707C34CD__INCLUDED_)
