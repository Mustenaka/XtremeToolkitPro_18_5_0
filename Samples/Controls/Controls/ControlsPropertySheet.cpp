// ControlsPropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "controls.h"
#include "ControlsPropertySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CControlsPropertySheet

IMPLEMENT_DYNAMIC(CControlsPropertySheet, CXTPResizePropertySheet)

CControlsPropertySheet::CControlsPropertySheet() // add default constructor, PCVA - Yair 3/6/2003
: CXTPResizePropertySheet()
{

}

CControlsPropertySheet::CControlsPropertySheet(const UINT nCaption, CWnd* pParent, const UINT nSelectPage, const UINT nFlags)
: CXTPResizePropertySheet(nCaption, pParent, nSelectPage, nFlags)
{

}

CControlsPropertySheet::CControlsPropertySheet(LPCTSTR pszCaption, CWnd* pParent, const UINT nSelectPage, const UINT nFlags)
: CXTPResizePropertySheet(pszCaption, pParent, nSelectPage, nFlags)
{

}

BEGIN_MESSAGE_MAP(CControlsPropertySheet, CXTPResizePropertySheet)
	//{{AFX_MSG_MAP(CControlsPropertySheet)
	ON_CBN_SELCHANGE(IDC_COMBO_THEME, OnSelChangeTheme)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CControlsPropertySheet message handlers

BOOL CControlsPropertySheet::OnInitDialog() 
{
	CXTPResizePropertySheet::OnInitDialog();
	
	// get the desktop dc and save the state.
	CWindowDC dc(NULL);
	CXTPDCSaveState dcState(&dc);

	// get the dialog font and select into the dc.
	CFont* pFont = GetFont();
	dc.SelectObject(pFont);

	// get the size of the static text.
	CString strText = _T("Theme:");
	CSize szText = dc.GetTextExtent(strText);

	// calculate the size and position of the static text.
	CXTPWindowRect rcText(GetDlgItem(IDOK));
	ScreenToClient(&rcText);
	rcText.left  = XTP_DPI_X(10);
	rcText.right = rcText.left + szText.cx + XTP_DPI_X(5);

	// create static text.
	m_txtTheme.Create(strText, WS_CHILD | WS_VISIBLE | SS_LEFT | SS_CENTERIMAGE, rcText, this, IDC_STATIC);
	m_txtTheme.SetFont(GetFont());

	// calculate the size of the theme combo.
	CRect rcCombo(rcText);
	rcCombo.left = rcCombo.right;
	rcCombo.right = XTP_DPI_X(200);
	rcCombo.bottom = rcCombo.top + XTP_DPI_Y(200);

	// create the theme combo.
	m_comboTheme.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST | CBS_HASSTRINGS, rcCombo, this, IDC_COMBO_THEME);
	m_comboTheme.SetFont(GetFont());

	SetResize(IDC_COMBO_THEME, XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMRIGHT);

	// add items to the combo.
	m_comboTheme.SetItemData(m_comboTheme.AddString(_T("Default")),                    xtpControlThemeDefault);
	m_comboTheme.SetItemData(m_comboTheme.AddString(_T("Flat")),                       xtpControlThemeFlat);
	m_comboTheme.SetItemData(m_comboTheme.AddString(_T("Ultra Flat")),                 xtpControlThemeUltraFlat);
	m_comboTheme.SetItemData(m_comboTheme.AddString(_T("Office 2000")),                xtpControlThemeOffice2000);
	m_comboTheme.SetItemData(m_comboTheme.AddString(_T("Office XP")),                  xtpControlThemeOfficeXP);
	m_comboTheme.SetItemData(m_comboTheme.AddString(_T("Office 2003")),                xtpControlThemeOffice2003);
	m_comboTheme.SetItemData(m_comboTheme.AddString(_T("Office 2007")),                xtpControlThemeResource);
	m_comboTheme.SetItemData(m_comboTheme.AddString(_T("Office 2013 (Word)")),         xtpControlThemeOffice2013);
	m_comboTheme.SetItemData(m_comboTheme.AddString(_T("Visual Studio 2015 (Light)")), xtpControlThemeVisualStudio2015);
	m_comboTheme.SetItemData(m_comboTheme.AddString(_T("Visual Studio 2015 (Dark)")),  xtpControlThemeVisualStudio2015);
	m_comboTheme.SetItemData(m_comboTheme.AddString(_T("Visual Studio 2015 (Blue)")),  xtpControlThemeVisualStudio2015);
	m_comboTheme.SetItemData(m_comboTheme.AddString(_T("Native Windows")),             xtpControlThemeNativeWinXP);

	m_comboTheme.SetCurSel(8);
	OnSelChangeTheme();

	return TRUE;
}

void CControlsPropertySheet::OnSelChangeTheme()
{
	theApp.m_nCurSel = m_comboTheme.GetCurSel();

	if (theApp.m_nCurSel != CB_ERR)
	{
		theApp.m_nTheme  = (XTPControlTheme)m_comboTheme.GetItemData(theApp.m_nCurSel);
		theApp.m_clrText = ::GetSysColor(COLOR_BTNTEXT);
		theApp.m_clrBack = ::GetSysColor(COLOR_BTNFACE);
		theApp.m_clrEdge = theApp.m_clrBack;

		switch (theApp.m_nCurSel)
		{
		case 6:
			XTPThemeDLL()->SetHandle(xtpIniOffice2007Blue);
			break;
		case 7:
			XTPThemeDLL()->SetHandle(xtpIniOffice2013Word);
			theApp.m_clrText = RGB( 68,  68, 68);
			theApp.m_clrBack = RGB(255, 255, 255);
			theApp.m_clrEdge = RGB(171, 171, 171);
			break;
		case 8:
			XTPThemeDLL()->SetHandle(xtpIniVisualStudio2015Light);
			theApp.m_clrText = RGB( 30,  30,  30);
			theApp.m_clrBack = RGB(245, 245, 245);
			theApp.m_clrEdge = RGB(171, 171, 171);
			break;
		case 9:
			XTPThemeDLL()->SetHandle(xtpIniVisualStudio2015Dark);
			theApp.m_clrText = RGB(241, 241, 241);
			theApp.m_clrBack = RGB( 33,  36,  33);
			theApp.m_clrEdge = RGB( 67,  67,  70);
			break;
		case 10:
			XTPThemeDLL()->SetHandle(xtpIniVisualStudio2015Blue);
			theApp.m_clrText = RGB(241, 241, 241);
			theApp.m_clrBack = RGB( 54,  78, 111);
			theApp.m_clrEdge = RGB(133, 145, 162);
			break;
		}

		theApp.m_brBack.DeleteObject();
		theApp.m_brBack.CreateSolidBrush(theApp.m_clrBack);

		SendMessageToDescendants(WM_XTP_SETCONTROLTHEME, theApp.m_nTheme, theApp.m_nCurSel);
		RedrawWindow(0, 0, RDW_ALLCHILDREN|RDW_INVALIDATE|RDW_ERASE);
	}
}
