// stdafx.h
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

#if !defined(AFX_STDAFX_H__75B714AE_60B3_4FFE_A6F2_1880D09F1563__INCLUDED_)
#define AFX_STDAFX_H__75B714AE_60B3_4FFE_A6F2_1880D09F1563__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <TargetVer.h>

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>         // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

// #define _XTP_SINGLE_PACKAGE

// Required components
#define _XTP_REQUIRE_MARKUP
#define _XTP_REQUIRE_REPORTCONTROL

// Optional components
#ifndef _XTP_SINGLE_PACKAGE
#define _XTP_REQUIRE_COMMANDBARS
#define _XTP_REQUIRE_SKINFRAMEWORK
#define _XTP_REQUIRE_DOCKINGPANE
#endif

#include <Exclude.h>
#include <XTToolkitPro.h>   // Codejock Software Components

#define XTP_INCLUDE_THEMEDIALOG
#include <CodejockSample.h> // Sample About and Theme Dialogs

#ifndef _XTP_INCLUDE_COMMANDBARS
#define CXTPFrameWnd  CFrameWnd
#define CXTPStatusBar CStatusBar
#endif

 

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__75B714AE_60B3_4FFE_A6F2_1880D09F1563__INCLUDED_)
