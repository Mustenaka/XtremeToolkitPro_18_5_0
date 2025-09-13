// BackstagePageSaveEmail.cpp
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
#include "BackstagePageSaveEmail.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBackstagePageSaveEmail property page

IMPLEMENT_DYNCREATE(CBackstagePageSaveEmail, CXTPRibbonBackstagePage)

CBackstagePageSaveEmail::CBackstagePageSaveEmail() : CXTPRibbonBackstagePage(CBackstagePageSaveEmail::IDD)
{
	//{{AFX_DATA_INIT(CBackstagePageSaveEmail)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CBackstagePageSaveEmail::~CBackstagePageSaveEmail()
{
}

void CBackstagePageSaveEmail::DoDataExchange(CDataExchange* pDX)
{
	CXTPRibbonBackstagePage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBackstagePageSaveEmail)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_SEPARATOR_1, m_lblSeparator);
	DDX_Control(pDX, IDC_LABEL_CAPTION, m_lblCaption);
	DDX_Control(pDX, IDC_BUTTON_SEND, m_btnSend);

}


BEGIN_MESSAGE_MAP(CBackstagePageSaveEmail, CXTPRibbonBackstagePage)
	//{{AFX_MSG_MAP(CBackstagePageSaveEmail)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBackstagePageSaveEmail message handlers

BOOL CBackstagePageSaveEmail::OnInitDialog() 
{
	CXTPRibbonBackstagePage::OnInitDialog();

	ModifyStyleEx(0, WS_EX_CONTROLPARENT);
	
	m_lblCaption.SetFont(&m_xtpFontCaption);

	m_btnSend.ShowShadow(TRUE);

	SetResize(IDC_SEPARATOR_1, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);	
	
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBackstagePageSaveEmail::SetTheme(XTPControlTheme nTheme)
{
	CXTPRibbonBackstagePage::SetTheme(nTheme);
	
	m_lblCaption.SetTheme(nTheme);
	m_lblSeparator.SetTheme(nTheme);
	m_btnSend.SetTheme(nTheme);
}
