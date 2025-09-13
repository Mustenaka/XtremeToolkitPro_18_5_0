// PageScrollBar.cpp
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
#include "PageScrollBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageScrollBar property page

IMPLEMENT_DYNCREATE(CPageScrollBar, CXTPResizePropertyPage)

CPageScrollBar::CPageScrollBar() : CXTPResizePropertyPage(CPageScrollBar::IDD)
{
	//{{AFX_DATA_INIT(CPageScrollBar)
	m_bEnabled = TRUE;
	//}}AFX_DATA_INIT
}

CPageScrollBar::~CPageScrollBar()
{
}

void CPageScrollBar::DoDataExchange(CDataExchange* pDX)
{
	CXTPResizePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageScrollBar)
	DDX_Control(pDX, IDC_CHECK_ENABLED, m_btnEnabled);
	DDX_Control(pDX, IDC_GBOX_OPTIONS, m_gboxOptions);
	DDX_Check(pDX, IDC_CHECK_ENABLED, m_bEnabled);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_SCROLLBAR9, m_wndScrollBar[8]);
	DDX_Control(pDX, IDC_SCROLLBAR8, m_wndScrollBar[7]);
	DDX_Control(pDX, IDC_SCROLLBAR7, m_wndScrollBar[6]);
	DDX_Control(pDX, IDC_SCROLLBAR6, m_wndScrollBar[5]);
	DDX_Control(pDX, IDC_SCROLLBAR5, m_wndScrollBar[4]);
	DDX_Control(pDX, IDC_SCROLLBAR4, m_wndScrollBar[3]);
	DDX_Control(pDX, IDC_SCROLLBAR3, m_wndScrollBar[2]);
	DDX_Control(pDX, IDC_SCROLLBAR2, m_wndScrollBar[1]);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_wndScrollBar[0]);

	DDX_Control(pDX, IDC_SCROLLBAR_HORIZONTAL9, m_wndScrollBarHorizontal[8]);
	DDX_Control(pDX, IDC_SCROLLBAR_HORIZONTAL8, m_wndScrollBarHorizontal[7]);
	DDX_Control(pDX, IDC_SCROLLBAR_HORIZONTAL7, m_wndScrollBarHorizontal[6]);
	DDX_Control(pDX, IDC_SCROLLBAR_HORIZONTAL6, m_wndScrollBarHorizontal[5]);
	DDX_Control(pDX, IDC_SCROLLBAR_HORIZONTAL5, m_wndScrollBarHorizontal[4]);
	DDX_Control(pDX, IDC_SCROLLBAR_HORIZONTAL4, m_wndScrollBarHorizontal[3]);
	DDX_Control(pDX, IDC_SCROLLBAR_HORIZONTAL3, m_wndScrollBarHorizontal[2]);
	DDX_Control(pDX, IDC_SCROLLBAR_HORIZONTAL2, m_wndScrollBarHorizontal[1]);
	DDX_Control(pDX, IDC_SCROLLBAR_HORIZONTAL1, m_wndScrollBarHorizontal[0]);

}


BEGIN_MESSAGE_MAP(CPageScrollBar, CXTPResizePropertyPage)
	//{{AFX_MSG_MAP(CPageScrollBar)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHECK_ENABLED, OnCheckEnabled)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_XTP_SETCONTROLTHEME, OnSetTheme)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageScrollBar message handlers

BOOL CPageScrollBar::OnInitDialog() 
{
	CXTPResizePropertyPage::OnInitDialog();
	
	SetResize(IDC_GBOX_OPTIONS, CXTPResizePoint((float)(2.0/3.0), 0), XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_CHECK_ENABLED, CXTPResizePoint((float)(2.0/3.0), 0), XTP_ANCHOR_TOPRIGHT);

	SetResize(IDC_SCROLLBAR_HORIZONTAL9, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_SCROLLBAR_HORIZONTAL8, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_SCROLLBAR_HORIZONTAL7, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
/*
	//m_wndScrollBar[0].SetTheme(xtpControlThemeResource);
	m_wndScrollBar[1].SetUseVisualStyle(FALSE);
	m_wndScrollBar[2].SetTheme(xtpControlThemeOffice2000);
	m_wndScrollBar[3].SetTheme(xtpControlThemeFlat);
	m_wndScrollBar[4].SetTheme(xtpControlThemeUltraFlat);
	m_wndScrollBar[5].SetTheme(xtpControlThemeOfficeXP);
	m_wndScrollBar[6].SetTheme(xtpControlThemeResource);
	m_wndScrollBar[7].SetTheme(xtpControlThemeVisualStudio2012Light);
	m_wndScrollBar[8].SetTheme(xtpControlThemeVisualStudio2012Dark);

	//m_wndScrollBarHorizontal[0].SetTheme(xtpControlThemeResource);
	m_wndScrollBarHorizontal[1].SetUseVisualStyle(FALSE);
	m_wndScrollBarHorizontal[2].SetTheme(xtpControlThemeOffice2000);
	m_wndScrollBarHorizontal[3].SetTheme(xtpControlThemeFlat);
	m_wndScrollBarHorizontal[4].SetTheme(xtpControlThemeUltraFlat);
	m_wndScrollBarHorizontal[5].SetTheme(xtpControlThemeOfficeXP);
	m_wndScrollBarHorizontal[6].SetTheme(xtpControlThemeResource);
	m_wndScrollBarHorizontal[7].SetTheme(xtpControlThemeVisualStudio2012Light);
	m_wndScrollBarHorizontal[8].SetTheme(xtpControlThemeVisualStudio2012Dark);
*/

	for (int i = 0; i < 9; i++)
	{
		m_wndScrollBar[i].SetScrollRange(0, 100);
		m_wndScrollBar[i].SetScrollPos(rand() % 100);

		m_wndScrollBarHorizontal[i].SetScrollRange(0, 100);
		m_wndScrollBarHorizontal[i].SetScrollPos(rand() % 100);
	}

	OnCheckEnabled();
	OnSetTheme(theApp.m_nTheme, theApp.m_nCurSel);

	SendMessageToDescendants(WM_XTP_SETCONTROLTHEME, theApp.m_nTheme);
	RedrawWindow(0, 0, RDW_ALLCHILDREN|RDW_INVALIDATE|RDW_ERASE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageScrollBar::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// its horizontal scroll bar
	int nCurPos = pScrollBar->GetScrollPos();
	
	// decide what to do for each diffrent scroll event
	switch (nSBCode)
	{
	case SB_LEFT: nCurPos = 0; break;
	case SB_RIGHT: nCurPos = pScrollBar->GetScrollLimit(); break;
	case SB_LINELEFT: nCurPos = max(nCurPos - 6, 0); break;
	case SB_LINERIGHT: nCurPos = min(nCurPos + 6, pScrollBar->GetScrollLimit()); break;
	case SB_PAGELEFT: nCurPos = max(nCurPos - 20, 0); break;
	case SB_PAGERIGHT: nCurPos = min(nCurPos + 20, pScrollBar->GetScrollLimit()); break;
		
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:  nCurPos = nPos; break;
	}

	pScrollBar->SetScrollPos(nCurPos);
}

void CPageScrollBar::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// its horizontal scroll bar
	int nCurPos = pScrollBar->GetScrollPos();
	
	// decide what to do for each diffrent scroll event
	switch (nSBCode)
	{
	case SB_LEFT: nCurPos = 0; break;
	case SB_RIGHT: nCurPos = pScrollBar->GetScrollLimit(); break;
	case SB_LINELEFT: nCurPos = max(nCurPos - 6, 0); break;
	case SB_LINERIGHT: nCurPos = min(nCurPos + 6, pScrollBar->GetScrollLimit()); break;
	case SB_PAGELEFT: nCurPos = max(nCurPos - 20, 0); break;
	case SB_PAGERIGHT: nCurPos = min(nCurPos + 20, pScrollBar->GetScrollLimit()); break;
		
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:  nCurPos = nPos; break;
	}

	pScrollBar->SetScrollPos(nCurPos);
}


void CPageScrollBar::OnCheckEnabled() 
{
	UpdateData();

	for (int i = 0; i < 9; i++)
	{
		m_wndScrollBar[i].EnableWindow(m_bEnabled);
		m_wndScrollBarHorizontal[i].EnableWindow(m_bEnabled);
	}
}

void CPageScrollBar::OnPaint() 
{
	CXTPResizePropertyPage::OnPaint();
	
	CClientDC dc(this);
	CXTPClientRect rcClient(this);
	dc.Draw3dRect(&rcClient, theApp.m_clrEdge, theApp.m_clrEdge);
}

HBRUSH CPageScrollBar::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CXTPResizePropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_DLG ||
		nCtlColor == CTLCOLOR_BTN ||
		nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkColor(m_clrBack);
		pDC->SetTextColor(theApp.m_clrText);

		return m_brBack;
	}

	return hBrush;
}

LRESULT CPageScrollBar::OnSetTheme(WPARAM wParam, LPARAM lParam)
{
	m_clrBack = theApp.m_clrBack;

	if ((XTPControlTheme)wParam == xtpControlThemeVisualStudio2015 && (int)lParam == 8)
	{
		m_clrBack = RGB(255, 255, 255);
	}

	m_brBack.DeleteObject();
	m_brBack.CreateSolidBrush(m_clrBack);

	return 0;
}
