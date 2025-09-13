// TabLongPage.cpp
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
#include "propertysheet.h"
#include "TabLongPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabLongPage property page

IMPLEMENT_DYNCREATE(CTabLongPage, CXTPPropertyPage)

CTabLongPage::CTabLongPage() : CXTPPropertyPage(CTabLongPage::IDD)
{
	//{{AFX_DATA_INIT(CTabLongPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CTabLongPage::~CTabLongPage()
{
}

void CTabLongPage::DoDataExchange(CDataExchange* pDX)
{
	CXTPPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabLongPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabLongPage, CXTPPropertyPage)
	//{{AFX_MSG_MAP(CTabLongPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabLongPage message handlers

BOOL CTabLongPage::OnInitDialog() 
{
	CXTPPropertyPage::OnInitDialog();

	ModifyStyle(0, WS_CLIPCHILDREN | WS_VSCROLL);
	
	for (int i = 0; i < 5; i++)
	{
		m_captions[i].SubclassDlgItem(IDC_STATIC_SUBCAPTION1 + i, this);
		SetResize(IDC_STATIC_SUBCAPTION1 + i, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
