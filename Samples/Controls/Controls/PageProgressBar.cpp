// PageProgressBar.cpp
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
#include "controls.h"
#include "PageProgressBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageProgressBar dialog


CPageProgressBar::CPageProgressBar()
	: CXTPResizePropertyPage(CPageProgressBar::IDD)
{
	//{{AFX_DATA_INIT(CPageProgressBar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bPause = FALSE;
}


void CPageProgressBar::DoDataExchange(CDataExchange* pDX)
{
	CXTPResizePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageProgressBar)
	DDX_Control(pDX, IDC_BUTTON_STEP, m_btnStep);
	DDX_Control(pDX, IDC_BUTTON_PAUSE, m_btnPause);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_PROGRESS7, m_wndProgressBar[6]);
	DDX_Control(pDX, IDC_PROGRESS6, m_wndProgressBar[5]);
	DDX_Control(pDX, IDC_PROGRESS5, m_wndProgressBar[4]);
	DDX_Control(pDX, IDC_PROGRESS4, m_wndProgressBar[3]);
	DDX_Control(pDX, IDC_PROGRESS3, m_wndProgressBar[2]);
	DDX_Control(pDX, IDC_PROGRESS2, m_wndProgressBar[1]);
	DDX_Control(pDX, IDC_PROGRESS1, m_wndProgressBar[0]);
}

BEGIN_MESSAGE_MAP(CPageProgressBar, CXTPResizePropertyPage)
	//{{AFX_MSG_MAP(CPageProgressBar)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, OnButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_STEP, OnButtonStep)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageProgressBar message handlers

BOOL CPageProgressBar::OnInitDialog() 
{
	CXTPResizePropertyPage::OnInitDialog();	
/*
	m_wndProgressBar[2].SetTheme(xtpControlThemeUltraFlat);
	m_wndProgressBar[3].SetTheme(xtpControlThemeOffice2003);
	m_wndProgressBar[4].SetTheme(xtpControlThemeOffice2000);
	m_wndProgressBar[5].SetTheme(xtpControlThemeFlat);
	m_wndProgressBar[5].SetBarColor(RGB(255,128,0));
	m_wndProgressBar[5].SetBkColor(RGB(192,255,255));
	m_wndProgressBar[6].SetTheme(xtpControlThemeResource);
*/
	m_wndProgressBar[4].SetWindowText(_T("Loading..."));

	for (int i = 0; i < 7; i++)
	{
		m_wndProgressBar[i].SetPos(rand() % 100);
	}

	m_wndProgressBar[1].ModifyStyle(0, PBS_MARQUEE);
	m_wndProgressBar[1].SetMarquee(1, 100);

	m_wndProgressBar[3].ModifyStyle(0, PBS_MARQUEE);
	m_wndProgressBar[3].SetMarquee(1, 100);

	SetResize(IDC_BUTTON_STEP, XTP_ANCHOR_TOPRIGHT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_BUTTON_PAUSE, XTP_ANCHOR_TOPRIGHT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_PROGRESS7, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_PROGRESS6, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_PROGRESS5, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_PROGRESS4, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_PROGRESS3, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_PROGRESS2, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_PROGRESS1, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);

	SendMessageToDescendants(WM_XTP_SETCONTROLTHEME, theApp.m_nTheme);
	RedrawWindow(0, 0, RDW_ALLCHILDREN|RDW_INVALIDATE|RDW_ERASE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageProgressBar::OnButtonPause() 
{
	m_bPause = !m_bPause;

	if (m_bPause)
	{
		m_wndProgressBar[1].SetMarquee(0, 100);
		m_wndProgressBar[3].SetMarquee(0, 100);
	}
	else
	{
		m_wndProgressBar[1].SetMarquee(1, 100);
		m_wndProgressBar[3].SetMarquee(1, 100);

	}
	
}

void CPageProgressBar::OnButtonStep() 
{
	for (int i = 0; i < 7; i++)
	{
		m_wndProgressBar[i].StepIt();
	}
	
}

void CPageProgressBar::OnPaint() 
{
	CXTPResizePropertyPage::OnPaint();
	
	CClientDC dc(this);
	CXTPClientRect rcClient(this);
	dc.Draw3dRect(&rcClient, theApp.m_clrEdge, theApp.m_clrEdge);
}

HBRUSH CPageProgressBar::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CXTPResizePropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_DLG ||
		nCtlColor == CTLCOLOR_BTN ||
		nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkColor(theApp.m_clrBack);
		pDC->SetTextColor(theApp.m_clrText);
		return theApp.m_brBack;
	}

	return hBrush;
}
