// CustomizePageQuickAccessToolbar.cpp
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

#include "stdafx.h"
#include "ribbonsample.h"
#include "CustomizePageQuickAccessToolbar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomizePageQuickAccessToolbar property page

CCustomizePageQuickAccessToolbar::CCustomizePageQuickAccessToolbar(CXTPCommandBars* pCommandBars)
	: CXTPRibbonCustomizeQuickAccessPage(pCommandBars)
{
	//{{AFX_DATA_INIT(CCustomizePageQuickAccessToolbar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CCustomizePageQuickAccessToolbar::~CCustomizePageQuickAccessToolbar()
{
}

void CCustomizePageQuickAccessToolbar::DoDataExchange(CDataExchange* pDX)
{
	CXTPRibbonCustomizeQuickAccessPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomizePageQuickAccessToolbar)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustomizePageQuickAccessToolbar, CXTPRibbonCustomizeQuickAccessPage)
	//{{AFX_MSG_MAP(CCustomizePageQuickAccessToolbar)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomizePageQuickAccessToolbar message handlers

BOOL CCustomizePageQuickAccessToolbar::OnInitDialog() 
{
	CXTPRibbonCustomizeQuickAccessPage::OnInitDialog();
	

	return TRUE;
}