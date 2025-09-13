// TabSamplePage.cpp
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
#include "PropertySheet.h"
#include "TabSamplePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabSamplePage property page

IMPLEMENT_DYNCREATE(CTabSamplePage, CXTPPropertyPage)

CTabSamplePage::CTabSamplePage() : CXTPPropertyPage(CTabSamplePage::IDD)
{
	//{{AFX_DATA_INIT(CTabSamplePage)
	m_nValue = 2;
	//}}AFX_DATA_INIT
}

CTabSamplePage::~CTabSamplePage()
{
}

void CTabSamplePage::DoDataExchange(CDataExchange* pDX)
{
	CXTPPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabSamplePage)
	DDX_Text(pDX, IDC_EDIT_VALUE, m_nValue);
	DDV_MinMaxInt(pDX, m_nValue, 1, 10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabSamplePage, CXTPPropertyPage)
	//{{AFX_MSG_MAP(CTabSamplePage)
	ON_EN_CHANGE(IDC_EDIT_VALUE, OnChangeEditValue)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabSamplePage message handlers

void CTabSamplePage::OnChangeEditValue() 
{
	SetModified();
}

void CTabSamplePage::OnCheck() 
{
	SetModified();
	
}
