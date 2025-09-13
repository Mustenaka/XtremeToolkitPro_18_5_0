// StdAfx.h
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

#if !defined(AFX_STDAFX_H__B19F6AB3_5FCB_4C31_8C37_6462389F4E54__INCLUDED_)
#define AFX_STDAFX_H__B19F6AB3_5FCB_4C31_8C37_6462389F4E54__INCLUDED_

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

// Lets help compiler to skip some headers
#define _XTP_EXCLUDE_CALENDAR
#define _XTP_EXCLUDE_SYNTAXEDIT
#define _XTP_EXCLUDE_REPORTCONTROL
#define _XTP_EXCLUDE_FLOWGRAPH


#define ENABLE_MANIFESTEDITOR

#include <XTToolkitPro.h>   // Codejock Software Components
#include <AboutDlg.h>       // Sample About Dialog

 
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__B19F6AB3_5FCB_4C31_8C37_6462389F4E54__INCLUDED_)
