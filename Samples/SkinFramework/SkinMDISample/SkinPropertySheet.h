// SkinPropertySheet.h
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
 
#ifndef __SKINPROPERTYSHEET_H__
#define __SKINPROPERTYSHEET_H__

#include "SkinPropertyPageControls.h"
#include "SkinPropertyPageThemes.h"

/////////////////////////////////////////////////////////////////////////////
// CSkinPropertySheet

class CSkinPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CSkinPropertySheet)

public:
	CSkinPropertySheet(CWnd* pWndParent = NULL);

public:
	CSkinPropertyPageControls m_Page1;
	CSkinPropertyPageThemes m_Page2;

	//{{AFX_VIRTUAL(CSkinPropertySheet)
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

public:
	virtual ~CSkinPropertySheet();

protected:
	//{{AFX_MSG(CSkinPropertySheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __SKINPROPERTYSHEET_H__
