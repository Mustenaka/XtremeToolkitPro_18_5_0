// PageButton.cpp
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
#include "PageButton.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageButton dialog

CPageButton::CPageButton()
	: CXTPResizePropertyPage(CPageButton::IDD)
{
	//{{AFX_DATA_INIT(CPageButton)
	m_bFlatStyle = FALSE;
	m_bUseVisualStyle = FALSE;
	m_bEnable = TRUE;
	m_bAlphaIcons = FALSE;
	m_bToggleButtons = FALSE;
	m_bShowFocus = TRUE;
	m_nRelation = 1;
	m_nPushButtonStyle = 0;
	m_nImageAlignment = 2;
	m_nTextAlignment = 2;
	//}}AFX_DATA_INIT

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPageButton::DoDataExchange(CDataExchange* pDX)
{
	CXTPResizePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageButton)
	DDX_Check(pDX, IDC_CHECK_FLATSTYLE, m_bFlatStyle);
	DDX_Check(pDX, IDC_CHECK_WINXP_THEMES, m_bUseVisualStyle);
	DDX_Check(pDX, IDC_CHECK_ENABLED, m_bEnable);
	DDX_Check(pDX, IDC_CHECK_ALPHA, m_bAlphaIcons);
	DDX_Check(pDX, IDC_CHECK_TOGGLE, m_bToggleButtons);
	DDX_Check(pDX, IDC_CHECK_FOCUS, m_bShowFocus);
	DDX_CBIndex(pDX, IDC_COMBO_RELATION, m_nRelation);
	DDX_CBIndex(pDX, IDC_COMBO_STYLE, m_nPushButtonStyle);
	DDX_CBIndex(pDX, IDC_COMBO_IMAGEALIGNMENT, m_nImageAlignment);
	DDX_CBIndex(pDX, IDC_COMBO_TEXTALIGNMENT, m_nTextAlignment);
	DDX_Control(pDX, IDC_BUTTON_RUN, m_btnRun);
	DDX_Control(pDX, IDC_BUTTON_SETTINGS, m_btnSettings);
	DDX_Control(pDX, IDC_BUTTON_HELP, m_btnHelp);
	DDX_Control(pDX, IDC_BUTTON_FIND, m_btnFind);
	DDX_Control(pDX, IDC_CHECK_STATE1, m_btnState1);
	DDX_Control(pDX, IDC_CHECK_STATE2, m_btnState2);
	DDX_Control(pDX, IDC_RADIO_OPTION1, m_btnOption1);
	DDX_Control(pDX, IDC_RADIO_OPTION2, m_btnOption2);
	DDX_Control(pDX, IDC_GBOX_REGULAR, m_frmRegular);
	DDX_Control(pDX, IDC_GBOX_TWOROWS, m_frmTwoRows);
	DDX_Control(pDX, IDC_GBOX_JUSTIFICATION, m_frmJustification);
	DDX_Control(pDX, IDC_COMBO_TEXTALIGNMENT, m_cmbTEXTALIGNMENT);
	DDX_Control(pDX, IDC_COMBO_IMAGEALIGNMENT, m_cmbIMAGEALIGNMENT);
	DDX_Control(pDX, IDC_COMBO_STYLE, m_cmbSTYLE);
	DDX_Control(pDX, IDC_COMBO_RELATION, m_cmbRELATION);
	DDX_Control(pDX, IDC_GBOX_CHECKBOXES, m_frmCheckboxes);
	DDX_Control(pDX, IDC_GBOX_RADIO, m_frmRadio);
	DDX_Control(pDX, IDC_GBOX_THEME, m_frmTheme);
	DDX_Control(pDX, IDC_GBOX_OPTIONS, m_frmOptions);
	DDX_Control(pDX, IDC_CHECK_FLATSTYLE, m_btnFLATSTYLE);
	DDX_Control(pDX, IDC_CHECK_WINXP_THEMES, m_btnWINXP_THEMES);
	DDX_Control(pDX, IDC_CHECK_TOGGLE, m_btnTOGGLE);
	DDX_Control(pDX, IDC_CHECK_ENABLED, m_btnENABLED);
	DDX_Control(pDX, IDC_CHECK_ALPHA, m_btnALPHA);
	DDX_Control(pDX, IDC_CHECK_FOCUS, m_btnFOCUS);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPageButton, CXTPResizePropertyPage)
	//{{AFX_MSG_MAP(CPageButton)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHECK_FLATSTYLE, OnCheckFlatstyle)
	ON_BN_CLICKED(IDC_CHECK_WINXP_THEMES, OnCheckWinxpThemes)
	ON_BN_CLICKED(IDC_CHECK_ENABLED, OnCheckEnabled)
	ON_BN_CLICKED(IDC_CHECK_ALPHA, OnCheckAlpha)
	ON_BN_CLICKED(IDC_CHECK_TOGGLE, OnCheckToggle)
	ON_BN_CLICKED(IDC_CHECK_FOCUS, OnCheckFocus)
	ON_CBN_SELCHANGE(IDC_COMBO_RELATION, OnSelchangeComboRelation)
	ON_CBN_SELCHANGE(IDC_COMBO_STYLE, OnSelchangeComboStyle)
	ON_CBN_SELCHANGE(IDC_COMBO_IMAGEALIGNMENT, OnSelchangeComboImagealignment)
	ON_CBN_SELCHANGE(IDC_COMBO_TEXTALIGNMENT, OnSelchangeComboTextalignment)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON_SETTINGS, IDC_BUTTON_RUN, OnButtonClicked)
	ON_CONTROL_RANGE(CBN_DROPDOWN, IDC_BUTTON_SETTINGS, IDC_BUTTON_RUN, OnButtonDropDown)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageButton message handlers

BOOL CPageButton::OnInitDialog()
{
	CXTPResizePropertyPage::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);         // Set big icon
	SetIcon(m_hIcon, FALSE);        // Set small icon


	m_frmCheckboxes.SetBorderStyle(xtpGroupBoxSingleLine);
	m_frmRadio.SetBorderStyle(xtpGroupBoxSingleLine);
	m_frmJustification.SetBorderStyle(xtpGroupBoxSingleLine);

	int i;
	for (i = IDC_GBOX_REGULAR; i <= IDC_COMBO_STYLE; i++)
		SetResize(i, XTP_ANCHOR_TOPLEFT, CXTPResizePoint((float)(1.0/3.0), 0));

	for (i = IDC_GBOX_CHECKBOXES; i <= IDC_COMBO_RELATION; i++)
		SetResize(i, CXTPResizePoint((float)(1.0/3.0), 0), CXTPResizePoint((float)(2.0/3.0), 0));

	SetResize(IDC_GBOX_THEME,         CXTPResizePoint((float)(2.0/3.0), 0), XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_CHECK_FLATSTYLE,    CXTPResizePoint((float)(2.0/3.0), 0), XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_CHECK_WINXP_THEMES, CXTPResizePoint((float)(2.0/3.0), 0), XTP_ANCHOR_TOPRIGHT);

	SetResize(IDC_GBOX_OPTIONS,  CXTPResizePoint((float)(2.0/3.0), 0), XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_CHECK_TOGGLE,  CXTPResizePoint((float)(2.0/3.0), 0), XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_CHECK_ENABLED, CXTPResizePoint((float)(2.0/3.0), 0), XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_CHECK_ALPHA,   CXTPResizePoint((float)(2.0/3.0), 0), XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_CHECK_FOCUS,   CXTPResizePoint((float)(2.0/3.0), 0), XTP_ANCHOR_TOPRIGHT);

	m_bitmap.LoadBitmap(IDB_IMAGELIST);
	m_imageList.Create(24, 24, ILC_COLOR24|ILC_MASK, 4, 1);
	m_imageList.Add(&m_bitmap, RGB(0,255,0));

	UpdateIcons(FALSE);

	OnCheckWinxpThemes();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPageButton::OnPaint()
{
	CXTPResizePropertyPage::OnPaint();
	
	CClientDC dc(this);
	CXTPClientRect rcClient(this);
	dc.Draw3dRect(&rcClient, theApp.m_clrEdge, theApp.m_clrEdge);
}

HBRUSH CPageButton::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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

void CPageButton::UpdateIcons(BOOL bAlpha)
{
	if (!bAlpha)
	{
		HICON hIcon = m_imageList.ExtractIcon(0);
		m_btnSettings.SetIcon(CSize(24,24), hIcon);
		DestroyIcon(hIcon);

		hIcon = m_imageList.ExtractIcon(1); 
		HICON hIconHot = m_imageList.ExtractIcon(2);
		m_btnFind.SetIcon(CSize(24,24), hIcon, hIconHot);
		DestroyIcon(hIcon); DestroyIcon(hIconHot);

		hIcon = m_imageList.ExtractIcon(3); 
		m_btnHelp.SetIcon(CSize(24,24), hIcon);
		DestroyIcon(hIcon);

		hIcon = m_imageList.ExtractIcon(4); 
		m_btnRun.SetIcon(CSize(24,24),hIcon);
		DestroyIcon(hIcon);
	} 
	else
	{
		m_btnSettings.SetBitmap(0, IDB_ALPHA_SETTINGS);
		m_btnFind.SetBitmap(0, IDB_ALPHA_FIND);
		m_btnHelp.SetBitmap(0, IDB_ALPHA_HELP);
		m_btnRun.SetBitmap(0, IDB_ALPHA_RUN);
	}
}

void CPageButton::OnCheckFlatstyle() 
{
	UpdateData();
	
	m_btnSettings.SetFlatStyle(m_bFlatStyle);	
	m_btnFind.SetFlatStyle(m_bFlatStyle);	
	m_btnHelp.SetFlatStyle(m_bFlatStyle);	
	m_btnRun.SetFlatStyle(m_bFlatStyle);	
}

void CPageButton::OnCheckWinxpThemes() 
{
	UpdateData();

	m_btnSettings.SetUseVisualStyle(m_bUseVisualStyle);	
	m_btnFind.SetUseVisualStyle(m_bUseVisualStyle);	
	m_btnHelp.SetUseVisualStyle(m_bUseVisualStyle);	
	m_btnRun.SetUseVisualStyle(m_bUseVisualStyle);		

	m_btnState1.SetUseVisualStyle(m_bUseVisualStyle);		
	m_btnState2.SetUseVisualStyle(m_bUseVisualStyle);		
	m_btnOption1.SetUseVisualStyle(m_bUseVisualStyle);		
	m_btnOption2.SetUseVisualStyle(m_bUseVisualStyle);		

	m_frmRegular.SetUseVisualStyle(m_bUseVisualStyle);		
	m_frmTwoRows.SetUseVisualStyle(m_bUseVisualStyle);		
	m_frmCheckboxes.SetUseVisualStyle(m_bUseVisualStyle);		
	m_frmRadio.SetUseVisualStyle(m_bUseVisualStyle);		
	
	RedrawWindow(0, 0, RDW_ALLCHILDREN|RDW_INVALIDATE|RDW_ERASE);
}

void CPageButton::OnCheckEnabled() 
{
	UpdateData();

	m_btnSettings.EnableWindow(m_bEnable);
	m_btnFind.EnableWindow(m_bEnable);
	m_btnHelp.EnableWindow(m_bEnable);
	m_btnRun.EnableWindow(m_bEnable);
	
	m_btnState1.EnableWindow(m_bEnable);	
	m_btnState2.EnableWindow(m_bEnable);		
	m_btnOption1.EnableWindow(m_bEnable);
	m_btnOption2.EnableWindow(m_bEnable);
}

void CPageButton::OnCheckAlpha() 
{
	UpdateData();
	UpdateIcons(m_bAlphaIcons);	
}

void CPageButton::OnCheckToggle() 
{
	UpdateData();

	if (!m_bToggleButtons)
	{
		m_btnSettings.SetChecked(FALSE);
		m_btnFind.SetChecked(FALSE);
		m_btnHelp.SetChecked(FALSE);
		m_btnRun.SetChecked(FALSE);
	}
}


void CPageButton::OnButtonClicked(UINT nID)
{
	CXTPButton* pButton = DYNAMIC_DOWNCAST(CXTPButton, GetDlgItem(nID));
	ASSERT(pButton);

	if (m_bToggleButtons)
	{
		pButton->SetChecked(!pButton->GetChecked());
	}
}

void CPageButton::OnButtonDropDown(UINT nID)
{
	// loading a user resource.
	CMenu menu;
	menu.LoadMenu(IDR_MENU_DROPDOWN);

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	CXTPButton* pButton = DYNAMIC_DOWNCAST(CXTPButton, GetDlgItem(nID));
	ASSERT(pButton);

	DWORD dwStyle = pButton->GetPushButtonStyle();
	ASSERT(pButton->IsDropDownStyle());

	CXTPWindowRect rect(pButton);

	int nCmd = TrackPopupMenu(pPopup->GetSafeHmenu(), TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERTICAL |TPM_RETURNCMD,
		dwStyle == xtpButtonDropDownRight ? rect.right : rect.left, dwStyle == xtpButtonDropDownRight ? rect.top : rect.bottom, 0, m_hWnd, 0);

	if (nCmd > 0)
	{
	}


}

void CPageButton::OnCheckFocus() 
{
	UpdateData();

	m_btnSettings.SetShowFocus(m_bShowFocus);
	m_btnFind.SetShowFocus(m_bShowFocus);
	m_btnHelp.SetShowFocus(m_bShowFocus);
	m_btnRun.SetShowFocus(m_bShowFocus);
	
	m_btnState1.SetShowFocus(m_bShowFocus);
	m_btnState2.SetShowFocus(m_bShowFocus);		
	m_btnOption1.SetShowFocus(m_bShowFocus);
	m_btnOption2.SetShowFocus(m_bShowFocus);
	
}

void CPageButton::OnSelchangeComboRelation() 
{
	UpdateData();

	m_btnHelp.SetTextImageRelation((XTPButtonTextImageRelation)m_nRelation);
	m_btnRun.SetTextImageRelation((XTPButtonTextImageRelation)m_nRelation);

	if (m_nRelation != xtpButtonTextAboveImage && m_nRelation != xtpButtonImageAboveText)
	{
		m_btnSettings.SetTextImageRelation((XTPButtonTextImageRelation)m_nRelation);
		m_btnFind.SetTextImageRelation((XTPButtonTextImageRelation)m_nRelation);
	}	
}

void CPageButton::OnSelchangeComboStyle() 
{
	UpdateData();	

	m_btnHelp.SetPushButtonStyle((XTPPushButtonStyle)m_nPushButtonStyle);
	m_btnRun.SetPushButtonStyle((XTPPushButtonStyle)m_nPushButtonStyle);
	m_btnSettings.SetPushButtonStyle((XTPPushButtonStyle)m_nPushButtonStyle);
	m_btnFind.SetPushButtonStyle((XTPPushButtonStyle)m_nPushButtonStyle);
}

void CPageButton::OnSelchangeComboTextalignment() 
{
	UpdateData();	

	int nVert = m_nTextAlignment >= 6 ? BS_BOTTOM : m_nTextAlignment >= 3 ? BS_TOP : BS_VCENTER;
	int nHorz = m_nTextAlignment % 3 == 0 ? BS_LEFT : m_nTextAlignment % 3 == 1 ? BS_RIGHT : BS_CENTER;

	m_btnRun.SetTextAlignment(nVert | nHorz);
	m_btnHelp.SetTextAlignment(nVert | nHorz);
	m_btnSettings.SetTextAlignment(nVert | nHorz);
	m_btnFind.SetTextAlignment(nVert | nHorz);
}

void CPageButton::OnSelchangeComboImagealignment() 
{
	UpdateData();	

	int nVert = m_nImageAlignment >= 6 ? BS_BOTTOM : m_nImageAlignment >= 3 ? BS_TOP : BS_VCENTER;
	int nHorz = m_nImageAlignment % 3 == 0 ? BS_LEFT : m_nImageAlignment % 3 == 1 ? BS_RIGHT : BS_CENTER;
	
	m_btnRun.SetImageAlignment(nVert | nHorz);
	m_btnHelp.SetImageAlignment(nVert | nHorz);
	m_btnSettings.SetImageAlignment(nVert | nHorz);
	m_btnFind.SetImageAlignment(nVert | nHorz);
	
}
