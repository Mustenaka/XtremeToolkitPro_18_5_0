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

#if !defined(AFX_STDAFX_H__A50FCB96_2D81_43C9_B2DE_A9F396803EB2__INCLUDED_)
#define AFX_STDAFX_H__A50FCB96_2D81_43C9_B2DE_A9F396803EB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <TargetVer.h>

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


#include <XTToolkitPro.h>   // Codejock Software Components

#include <Calendar\XTPCalendarADO.h>
#include <Calendar\XTPCalendarDatabaseDataProvider.h>

#include <AboutDlg.h>       // Sample About Dialog

//-----------------------------------------------------------------

/*#pragma warning( disable : 4146 )

//#include "Calendar/XTPCalendarADO.h"

#import "C:\Program Files\Common Files\System\ado\msado15.dll" rename("EOF", "bEOF")
no_namespace  \
	rename("EOF", "adoEOF")\
	rename("EditModeEnum", "adoEditModeEnum")\
	rename("LockTypeEnum", "adoLockTypeEnum")\
	rename("FieldAttributeEnum", "adoFieldAttributeEnum")\
	rename("DataTypeEnum", "adoDataTypeEnum")\
	rename("ParameterDirectionEnum", "adoParameterDirectionEnum")\
	rename("RecordStatusEnum", "adoRecordStatusEnum")\
	rename("RecordTypeEnum", "adoRecordTypeEnum")

#pragma warning( default : 4146 )
*/
//-----------------------------------------------------------------

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A50FCB96_2D81_43C9_B2DE_A9F396803EB2__INCLUDED_)
