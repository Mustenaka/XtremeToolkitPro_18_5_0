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

//#define CONVERTERS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxcmn.h>
#include <afxrich.h>
#include <afxpriv.h>

#define HORZ_TEXTOFFSET 15
#define VERT_TEXTOFFSET 5


#if (_MSC_VER < 1300)
#define ULONGLONG DWORD
#else
#define PARAFORMAT PARAFORMAT2
#define _paraformat PARAFORMAT2
#endif


class CDisplayIC : public CDC
{
public:
	CDisplayIC() { CreateIC(_T("DISPLAY"), NULL, NULL, NULL); }
};

struct CCharFormat : public CHARFORMAT
{
	CCharFormat() {cbSize = sizeof(CHARFORMAT);}
	BOOL operator==(CCharFormat& cf);
};

struct CParaFormat : public _paraformat
{
	CParaFormat() {cbSize = sizeof(_paraformat);}
	BOOL operator==(PARAFORMAT& pf);
};

#include "doctype.h"
#include "chicdial.h"


//#define _XTP_STATICLINK

#include <XTToolkitPro.h>   // Codejock Software Components
#include <AboutDlg.h>       // Sample About Dialog
 
#endif // AFX_STDAFX_H__75B714AE_60B3_4FFE_A6F2_1880D09F1563__INCLUDED_
