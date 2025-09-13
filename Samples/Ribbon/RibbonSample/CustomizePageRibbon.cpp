// CustomizePageRibbon.cpp
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
#include "CustomizePageRibbon.h"
#include "Mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomizePageRibbon property page


CCustomizePageRibbon::CCustomizePageRibbon(CXTPCommandBars* pCommandBars) : CXTPRibbonCustomizePage(pCommandBars)
{
	//{{AFX_DATA_INIT(CCustomizePageRibbon)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CCustomizePageRibbon::~CCustomizePageRibbon()
{
}

void CCustomizePageRibbon::DoDataExchange(CDataExchange* pDX)
{
	CXTPRibbonCustomizePage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomizePageRibbon)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustomizePageRibbon, CXTPRibbonCustomizePage)
	//{{AFX_MSG_MAP(CCustomizePageRibbon)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomizePageRibbon message handlers

BOOL CCustomizePageRibbon::OnInitDialog() 
{
	CXTPRibbonCustomizePage::OnInitDialog();
	
	return TRUE;
}

