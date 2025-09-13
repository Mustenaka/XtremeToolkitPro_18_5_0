// TabTreePage.cpp
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
#include "TabTreePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabTreePage property page

IMPLEMENT_DYNCREATE(CTabTreePage, CXTPPropertyPage)

CTabTreePage::CTabTreePage() : CXTPPropertyPage(CTabTreePage::IDD)
{
	//{{AFX_DATA_INIT(CTabTreePage)
	m_nBorderStyle = 2;
	//}}AFX_DATA_INIT
}

CTabTreePage::~CTabTreePage()
{
}

void CTabTreePage::DoDataExchange(CDataExchange* pDX)
{
	CXTPPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabTreePage)
	DDX_CBIndex(pDX, IDC_COMBO_BORDER, m_nBorderStyle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabTreePage, CXTPPropertyPage)
	//{{AFX_MSG_MAP(CTabTreePage)
	ON_CBN_SELCHANGE(IDC_COMBO_BORDER, OnSelchangeComboBorder)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabTreePage message handlers


void CTabTreePage::OnSelchangeComboBorder() 
{
	UpdateData();
	m_pSheet->SetPageBorderStyle((XTPPropertyPageBorder)m_nBorderStyle);
	m_pSheet->RedrawWindow(0, 0, RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_ERASE);	
}
