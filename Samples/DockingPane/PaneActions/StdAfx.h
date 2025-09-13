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

#if !defined(AFX_STDAFX_H__3710A7DA_8809_4F98_B93B_E77A171DC636__INCLUDED_)
#define AFX_STDAFX_H__3710A7DA_8809_4F98_B93B_E77A171DC636__INCLUDED_

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

const LPCTSTR lpszActions[] =
{
	_T("xtpPaneActionFloating"),
	_T("xtpPaneActionFloated"),
	_T("xtpPaneActionClosing"),
	_T("xtpPaneActionClosed"),
	_T("xtpPaneActionDocking"),
	_T("xtpPaneActionDocked"),
	_T("xtpPaneActionAttaching"),
	_T("xtpPaneActionAttached"),
	_T("xtpPaneActionPinning"),
	_T("xtpPaneActionPinned"),
	_T("xtpPaneActionCollapsing"),
	_T("xtpPaneActionCollapsed"),
	_T("xtpPaneActionExpanding"),
	_T("xtpPaneActionExpanded"),
	_T("xtpPaneActionActivated"),
	_T("xtpPaneActionDeactivated"),
	_T("xtpPaneActionDetaching"),
	_T("xtpPaneActionDragging"),
	_T("xtpPaneActionUnpinning"),
	_T("xtpPaneActionUnpinned"),
	_T("xtpPaneActionSplitterResizing"),
	_T("xtpPaneActionSplitterResized")
};




#include <XTToolkitPro.h>   // Codejock Software Components
#include <AboutDlg.h>       // Sample About Dialog

 

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__3710A7DA_8809_4F98_B93B_E77A171DC636__INCLUDED_)
