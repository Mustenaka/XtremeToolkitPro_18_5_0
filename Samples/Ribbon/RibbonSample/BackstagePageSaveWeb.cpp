// BackstagePageSaveWeb.cpp
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
#include "MainFrm.h"
#include "BackstagePageSaveWeb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBackstagePageSaveWeb property page

IMPLEMENT_DYNCREATE(CBackstagePageSaveWeb, CXTPRibbonBackstagePage)

CBackstagePageSaveWeb::CBackstagePageSaveWeb() : CXTPRibbonBackstagePage(CBackstagePageSaveWeb::IDD)
{
	//{{AFX_DATA_INIT(CBackstagePageSaveWeb)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CBackstagePageSaveWeb::~CBackstagePageSaveWeb()
{
}

void CBackstagePageSaveWeb::DoDataExchange(CDataExchange* pDX)
{
	CXTPRibbonBackstagePage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBackstagePageSaveWeb)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_SEPARATOR_1, m_lblSeparator);
	DDX_Control(pDX, IDC_LABEL_CAPTION, m_lblCaption);
	DDX_Control(pDX, IDC_BUTTON_SIGNIN, m_btnSignIn);
}


BEGIN_MESSAGE_MAP(CBackstagePageSaveWeb, CXTPRibbonBackstagePage)
	//{{AFX_MSG_MAP(CBackstagePageSaveWeb)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBackstagePageSaveWeb message handlers

BOOL CBackstagePageSaveWeb::OnInitDialog() 
{
	CXTPRibbonBackstagePage::OnInitDialog();
	
	ModifyStyleEx(0, WS_EX_CONTROLPARENT);
	
	m_lblCaption.SetFont(&m_xtpFontCaption);
	
	m_btnSignIn.ShowShadow(TRUE);
	
	SetResize(IDC_SEPARATOR_1, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);	
	
	return FALSE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CBackstagePageSaveWeb::SetTheme(XTPControlTheme nTheme)
{
	CXTPRibbonBackstagePage::SetTheme(nTheme);
	
	m_lblCaption.SetTheme(nTheme);
	m_lblSeparator.SetTheme(nTheme);
	m_btnSignIn.SetTheme(nTheme);
}
