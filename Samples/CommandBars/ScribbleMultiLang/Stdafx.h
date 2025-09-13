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

#if !defined(AFX_STDAFX_H__B3F0B423_78AE_4B44_93A6_63568D559F70__INCLUDED_)
#define AFX_STDAFX_H__B3F0B423_78AE_4B44_93A6_63568D559F70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <TargetVer.h>

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxtempl.h>       // MFC templates

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>         // MFC support for Windows 95 Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxole.h>         // MFC OLE classes

#ifndef WS_EX_LAYOUTRTL
#define WS_EX_LAYOUTRTL                    0x00400000L
#endif



#define _XTP_REQUIRE_CONTROLS
#define _XTP_REQUIRE_COMMANDBARS
#include <Exclude.h>

#include <XTToolkitPro.h>   // Codejock Software Components
#include <AboutDlg.h>       // Sample About Dialog

#endif // AFX_STDAFX_H__B3F0B423_78AE_4B44_93A6_63568D559F70__INCLUDED_
