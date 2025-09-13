// TargetVer.h : Target version configuration
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

#if !defined(__TARGETVER_H__)
#define __TARGETVER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#endif

#ifndef _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS  // some CString constructors will be explicit
#endif

#ifndef _AFX_ALL_WARNINGS
#define _AFX_ALL_WARNINGS // turns off MFC's hiding of some common and often safely ignored warning messages
#endif

// disable MBCS warning for Visual Studio 2013 and later
#if _MSC_VER >= 1800 && !defined(NO_WARN_MBCS_MFC_DEPRECATION)
#define NO_WARN_MBCS_MFC_DEPRECATION
#endif

#if _MSC_VER > 1200

#if _MSC_VER > 1600 
#include <sdkddkver.h>
#else

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER              // Allow use of features specific to Windows 95 and Windows NT 4 or later.
#if _MSC_VER >= 1800
#define WINVER 0x0502
#elif _MSC_VER > 1500
#define WINVER 0x0500
#else
#define WINVER 0x0400       // Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#endif
#endif // WINVER

#ifndef _WIN32_WINNT        // Allow use of features specific to Windows NT 4 or later.
#if _MSC_VER >= 1800
#define _WIN32_WINNT 0x0502
#elif _MSC_VER > 1500
#define _WIN32_WINNT 0x0500
#else
#define _WIN32_WINNT 0x0400     // Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#endif
#endif // _WIN32_WINNT

#ifndef _WIN32_WINDOWS      // Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE           // Allow use of features specific to IE 4.0 or later.
#if _MSC_VER >= 1800
#define _WIN32_IE 0x0603
#else
#define _WIN32_IE 0x0500    // Change this to the appropriate value to target IE 5.0 or later.
#endif
#endif // _WIN32_IE

#endif // !(_MSC_VER > 1600)
#endif // _MSC_VER > 1200 

#endif // __TARGETVER_H__
