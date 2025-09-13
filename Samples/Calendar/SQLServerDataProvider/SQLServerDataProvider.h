// SQLServerDataProvider.h
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

#if !defined(AFX_SQLSERVERDATAPROVIDER_H__984C5863_6D59_486D_AE44_BF9EB40F74DE__INCLUDED_)
#define AFX_SQLSERVERDATAPROVIDER_H__984C5863_6D59_486D_AE44_BF9EB40F74DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

static const LPCTSTR csOptProfileSection		= _T("CalendarSQLServerDataProviderSample");
static const LPCTSTR csOptDataSourceSQLsrvProp	= _T("DataSource_SQLsrv");
	static const LPCTSTR csOptDataSourceSQLsrvProp_default	= _T("Provider=SQLOLEDB.1;...");

/////////////////////////////////////////////////////////////////////////////
// CSQLServerDataProviderApp:
// See SQLServerDataProvider.cpp for the implementation of this class
//

class CSQLServerDataProviderApp : public CXTPWinApp
{
public:
	CSQLServerDataProviderApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSQLServerDataProviderApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSQLServerDataProviderApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SQLSERVERDATAPROVIDER_H__984C5863_6D59_486D_AE44_BF9EB40F74DE__INCLUDED_)
