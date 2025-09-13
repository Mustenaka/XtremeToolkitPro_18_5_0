// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__5DE12BF4_BD02_41B3_BDB8_4D00A4A2A63A__INCLUDED_)
#define AFX_STDAFX_H__5DE12BF4_BD02_41B3_BDB8_4D00A4A2A63A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <TargetVer.h>

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC OLE automation classes
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>         // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

// Lets help compiler to skip some headers
#define _XTP_EXCLUDE_CALENDAR
#define _XTP_EXCLUDE_SYNTAXEDIT
#define _XTP_EXCLUDE_REPORTCONTROL

#include <XTToolkitPro.h>   // Codejock Software Components
#include <AboutDlg.h>       // Sample About Dialog

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__5DE12BF4_BD02_41B3_BDB8_4D00A4A2A63A__INCLUDED_)
