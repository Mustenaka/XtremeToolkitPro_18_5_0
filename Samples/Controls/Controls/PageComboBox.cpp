// PageComboBox.cpp
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
#include "Controls.h"
#include "PageComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageComboBox property page

IMPLEMENT_DYNCREATE(CPageComboBox, CXTPResizePropertyPage)

CPageComboBox::CPageComboBox() : CXTPResizePropertyPage(CPageComboBox::IDD)
{
	//{{AFX_DATA_INIT(CPageComboBox)
	m_bEnabled = TRUE;
	m_bFlatStyle = FALSE;
	m_bUseVisualStyle = FALSE;
	m_bAutoComplete = FALSE;
	//}}AFX_DATA_INIT
}

CPageComboBox::~CPageComboBox()
{
}

void CPageComboBox::DoDataExchange(CDataExchange* pDX)
{
	CXTPResizePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageComboBox)
	DDX_Control(pDX, IDC_CHECK_AUTOCOMPLETE, m_chkAutoComplete);
	DDX_Control(pDX, IDC_CHECK_ENABLED, m_chkEnabled);
	DDX_Control(pDX, IDC_CHECK_WINXP_THEMES, m_chkVisualStyle);
	DDX_Control(pDX, IDC_CHECK_FLATSTYLE, m_chkFlatStyle);
	DDX_Control(pDX, IDC_GBOX_OPTIONS, m_gboxOptions);
	DDX_Control(pDX, IDC_GBOX_THEME, m_gboxTheme);
	DDX_Control(pDX, IDC_COMBO_DROPDOWN, m_cmbDropDown);
	DDX_Control(pDX, IDC_COMBO_DROPDOWNLIST, m_cmbDropDownList);
	DDX_Check(pDX, IDC_CHECK_ENABLED, m_bEnabled);
	DDX_Check(pDX, IDC_CHECK_FLATSTYLE, m_bFlatStyle);
	DDX_Check(pDX, IDC_CHECK_WINXP_THEMES, m_bUseVisualStyle);
	DDX_Check(pDX, IDC_CHECK_AUTOCOMPLETE, m_bAutoComplete);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageComboBox, CXTPResizePropertyPage)
	//{{AFX_MSG_MAP(CPageComboBox)
	ON_BN_CLICKED(IDC_CHECK_FLATSTYLE, OnCheckFlatstyle)
	ON_BN_CLICKED(IDC_CHECK_WINXP_THEMES, OnCheckWinxpThemes)
	ON_BN_CLICKED(IDC_CHECK_ENABLED, OnCheckEnabled)
	ON_BN_CLICKED(IDC_CHECK_AUTOCOMPLETE, OnCheckAutocomplete)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageComboBox message handlers

BOOL CPageComboBox::OnInitDialog() 
{
	CXTPResizePropertyPage::OnInitDialog();
	
	SetResize(IDC_GBOX_THEME, CXTPResizePoint((float)(1.0/3.0), 0), CXTPResizePoint((float)(2.0/3.0), 0));
	SetResize(IDC_CHECK_FLATSTYLE, CXTPResizePoint((float)(1.0/3.0), 0), CXTPResizePoint((float)(2.0/3.0), 0));
	SetResize(IDC_CHECK_WINXP_THEMES, CXTPResizePoint((float)(1.0/3.0), 0), CXTPResizePoint((float)(2.0/3.0), 0));
	
	SetResize(IDC_GBOX_OPTIONS, CXTPResizePoint((float)(2.0/3.0), 0), XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_CHECK_ENABLED, CXTPResizePoint((float)(2.0/3.0), 0), XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_CHECK_AUTOCOMPLETE, CXTPResizePoint((float)(2.0/3.0), 0), XTP_ANCHOR_TOPRIGHT);
	
	SetResize(IDC_COMBO_DROPDOWN, XTP_ANCHOR_TOPLEFT, CXTPResizePoint((float)(1.0/3.0), 0));
	SetResize(IDC_COMBO_DROPDOWNLIST, XTP_ANCHOR_TOPLEFT, CXTPResizePoint((float)(1.0/3.0), 0));

	m_cmbDropDown.SetCurSel(0);
	m_cmbDropDownList.SetCurSel(0);

	SendMessageToDescendants(WM_XTP_SETCONTROLTHEME, theApp.m_nTheme);
	RedrawWindow(0, 0, RDW_ALLCHILDREN|RDW_INVALIDATE|RDW_ERASE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageComboBox::OnCheckFlatstyle() 
{
	UpdateData();
	
	m_cmbDropDown.SetFlatStyle(m_bFlatStyle);	
	m_cmbDropDownList.SetFlatStyle(m_bFlatStyle);		
}

void CPageComboBox::OnCheckWinxpThemes() 
{
	UpdateData();
	
	m_cmbDropDown.SetUseVisualStyle(m_bUseVisualStyle);	
	m_cmbDropDownList.SetUseVisualStyle(m_bUseVisualStyle);	
}

void CPageComboBox::OnCheckEnabled() 
{
	UpdateData();
	
	m_cmbDropDown.EnableWindow(m_bEnabled);
	m_cmbDropDownList.EnableWindow(m_bEnabled);
}

void CPageComboBox::OnCheckAutocomplete() 
{
	UpdateData();

	m_cmbDropDown.EnableAutoCompletion(m_bAutoComplete);
	
}

void CPageComboBox::OnPaint() 
{
	CXTPResizePropertyPage::OnPaint();
	
	CClientDC dc(this);
	CXTPClientRect rcClient(this);
	dc.Draw3dRect(&rcClient, theApp.m_clrEdge, theApp.m_clrEdge);
}

HBRUSH CPageComboBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
