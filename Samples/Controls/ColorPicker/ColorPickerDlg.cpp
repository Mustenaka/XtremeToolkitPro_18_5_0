// ColorPickerDlg.cpp 
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
#include "ColorPicker.h"
#include "ColorPickerDlg.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorPickerDlg dialog

CColorPickerDlg::CColorPickerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CColorPickerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CColorPickerDlg)
	m_bNoFill = FALSE;
	m_3DBorder = TRUE;
	m_bDisable = FALSE;
	m_bDisplayHex = TRUE;
	m_bColorText = FALSE;
	m_bShowText = FALSE;
	m_bEyeDropper = TRUE;
	m_bRecent = FALSE;
	m_nStyle = 3;
	m_bMoreColors = TRUE;
	m_nTheme = 2;
	m_bCaptions = TRUE;
	//}}AFX_DATA_INIT

	m_clrText = RGB(217,226,243);
	m_clrBack = RGB( 47, 84,150);

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CColorPickerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorPickerDlg)
	DDX_Control(pDX, IDC_CHECK_RECENT, m_chkRecent);
	DDX_Control(pDX, IDC_CHK_COLORTEXT, m_chkColorText);
	DDX_Control(pDX, IDC_GBOX_BUTTON, m_gboxButton);
	DDX_Control(pDX, IDC_GBOX_POPUP, m_gboxPopup);
	DDX_Control(pDX, IDC_GBOX_DIALOG, m_gboxDialog);
	DDX_Control(pDX, IDC_CLR_TEXT, m_cpTextColor);
	DDX_Control(pDX, IDC_CLR_BACK, m_cpBackColor);
	DDX_Control(pDX, IDC_COLOR_STATIC, m_wndSample);
	DDX_Check(pDX, IDC_CHK_NOFILL, m_bNoFill);
	DDX_Check(pDX, IDC_CHK_3DBORDER, m_3DBorder);
	DDX_Check(pDX, IDC_CHK_DISABLE, m_bDisable);
	DDX_Check(pDX, IDC_CHK_DISPLAY_HEX, m_bDisplayHex);
	DDX_Check(pDX, IDC_CHK_COLORTEXT, m_bColorText);
	DDX_Check(pDX, IDC_CHK_NOTEXT, m_bShowText);
	DDX_Check(pDX, IDC_CHK_EYEDROPPER, m_bEyeDropper);
	DDX_Check(pDX, IDC_CHECK_RECENT, m_bRecent);
	DDX_CBIndex(pDX, IDC_COMBO_STYLE, m_nStyle);
	DDX_Check(pDX, IDC_CHK_MORECOLORS, m_bMoreColors);
	DDX_CBIndex(pDX, IDC_COMBO_THEME, m_nTheme);
	DDX_Check(pDX, IDC_CHK_CAPTIONS, m_bCaptions);
	//}}AFX_DATA_MAP
	DDX_XTPColorPicker(pDX, IDC_CLR_TEXT, m_clrText);
	DDX_XTPColorPicker(pDX, IDC_CLR_BACK, m_clrBack);
}

BEGIN_MESSAGE_MAP(CColorPickerDlg, CDialog)
	//{{AFX_MSG_MAP(CColorPickerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CHK_NOFILL, OnChkNoFill)
	ON_BN_CLICKED(IDC_CHK_MORECOLORS, OnChkMoreColors)
	ON_BN_CLICKED(IDC_CHK_3DBORDER, OnChk3dBorder)
	ON_BN_CLICKED(IDC_CHK_DISPLAY_HEX, OnChkDisplayHex)
	ON_BN_CLICKED(IDC_CHK_DISABLE, OnChkDisable)
	ON_BN_CLICKED(IDC_CHK_NOTEXT, OnChkNoText)
	ON_BN_CLICKED(IDC_CHK_COLORTEXT, OnChkColorText)
	ON_CBN_SELENDOK(IDC_COMBO_STYLE, OnSelEndOkComboStyle)
	ON_CBN_SELENDOK(IDC_COMBO_THEME, OnSelEndOkComboTheme)
	ON_BN_CLICKED(IDC_CHECK_RECENT, OnChkRecent)
	ON_BN_CLICKED(IDC_CHK_EYEDROPPER, OnChkEyeDropper)
	ON_BN_CLICKED(IDC_CHK_CAPTIONS, OnChkCaptions)
	//}}AFX_MSG_MAP
	ON_CPN_XTP_SELENDOK(IDC_CLR_TEXT, OnSelEndOkTextClr)
	ON_CPN_XTP_SELNOFILL(IDC_CLR_TEXT, OnSelEndOkTextClr)
	ON_CPN_XTP_SELENDOK(IDC_CLR_BACK, OnSelEndOkBackClr)
	ON_CPN_XTP_SELNOFILL(IDC_CLR_BACK, OnSelEndOkBackClr)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorPickerDlg message handlers

BOOL CColorPickerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	//------------------------------------
	// TODO: Add extra initialization here
	//------------------------------------

	// add recent colors.
	CUIntArray arRecentColors;
	arRecentColors.Add(RGB(150,0,0));
	arRecentColors.Add(RGB(0,150,0));
	arRecentColors.Add(RGB(0,0,150));
	CXTPColorSelectorCtrl::SetRecentColors(arRecentColors);

	m_cpBackColor.SetColor(m_clrBack);
	m_cpBackColor.SetDefaultColor(m_clrBack);
	m_cpBackColor.ShowText(m_bShowText);
	m_cpBackColor.ShowTextInColor(m_bColorText);

	m_cpTextColor.SetColor(m_clrText);
	m_cpTextColor.SetDefaultColor(m_clrText);
	m_cpTextColor.ShowText(m_bShowText);
	m_cpTextColor.ShowTextInColor(m_bColorText);

	OnSelEndOkComboStyle();
	OnSelEndOkComboTheme();
	OnChkRecent();
	OnChkMoreColors();
	OnChk3dBorder();
	OnChkDisplayHex();
	OnChkEyeDropper();

	// set the default font for all dialog controls.
	SendMessageToDescendants(WM_SETFONT,
		(WPARAM)(HFONT)XTPFontManager()->GetFont());

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CColorPickerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CColorPickerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CColorPickerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

HBRUSH CColorPickerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_COLOR_STATIC)
	{
		COLORREF clrText = (m_clrText == COLORREF_NULL) ? ::GetSysColor(COLOR_BTNFACE) : m_clrText;
		COLORREF clrBack = (m_clrBack == COLORREF_NULL) ? ::GetSysColor(COLOR_BTNFACE) : m_clrBack;
		
		pDC->SetTextColor(clrText);
		pDC->SetBkColor(clrBack);
		
		if (m_brBack.GetSafeHandle())
			m_brBack.DeleteObject();
		
		m_brBack.CreateSolidBrush(clrBack);
		return (HBRUSH)m_brBack;
	}

	return hbr;
}

void CColorPickerDlg::OnSelEndOkTextClr()
{
	UpdateData();
	m_wndSample.RedrawWindow();
}

void CColorPickerDlg::OnSelEndOkBackClr()
{
	UpdateData();
	m_wndSample.RedrawWindow();
}

void CColorPickerDlg::OnChkNoFill()
{
	UpdateData();

	DWORD dwRem = m_bNoFill ? 0 : CPS_XTP_NOFILL;
	DWORD dwAdd = m_bNoFill ? CPS_XTP_NOFILL : 0;

	m_cpBackColor.ModifyCPStyle(dwRem, dwAdd);
	m_cpTextColor.ModifyCPStyle(dwRem, dwAdd);
}

void CColorPickerDlg::OnChkMoreColors()
{
	UpdateData();

	DWORD dwRem = m_bMoreColors ? 0 : CPS_XTP_MORECOLORS;
	DWORD dwAdd = m_bMoreColors ? CPS_XTP_MORECOLORS : 0;

	m_cpBackColor.ModifyCPStyle(dwRem, dwAdd);
	m_cpTextColor.ModifyCPStyle(dwRem, dwAdd);

	m_chkRecent.EnableWindow(m_bMoreColors);

	if (m_bMoreColors == FALSE)
	{
		m_bRecent = FALSE;
		m_chkRecent.SetCheck(m_bRecent);
		OnChkRecent();
	}
}

void CColorPickerDlg::OnChk3dBorder()
{
	UpdateData();

	DWORD dwRem = m_3DBorder ? 0 : CPS_XTP_SHOW3DSELECTION;
	DWORD dwAdd = m_3DBorder ? CPS_XTP_SHOW3DSELECTION : 0;

	m_cpBackColor.ModifyCPStyle(dwRem, dwAdd);
	m_cpTextColor.ModifyCPStyle(dwRem, dwAdd);
}

void CColorPickerDlg::OnChkDisplayHex()
{
	UpdateData();

	DWORD dwRem = m_bDisplayHex ? 0 : CPS_XTP_SHOWHEXVALUE;
	DWORD dwAdd = m_bDisplayHex ? CPS_XTP_SHOWHEXVALUE : 0;

	m_cpBackColor.ModifyCPStyle(dwRem, dwAdd);
	m_cpTextColor.ModifyCPStyle(dwRem, dwAdd);
}

void CColorPickerDlg::OnChkEyeDropper() 
{
	UpdateData();

	DWORD dwRem = m_bEyeDropper ? 0 : CPS_XTP_SHOWEYEDROPPER;
	DWORD dwAdd = m_bEyeDropper ? CPS_XTP_SHOWEYEDROPPER : 0;

	m_cpBackColor.ModifyCPStyle(dwRem, dwAdd);
	m_cpTextColor.ModifyCPStyle(dwRem, dwAdd);
}

void CColorPickerDlg::OnChkDisable()
{
	UpdateData();
	m_cpBackColor.EnableWindow(!m_bDisable);
	m_cpTextColor.EnableWindow(!m_bDisable);
}

void CColorPickerDlg::OnChkNoText()
{
	UpdateData();
	m_cpBackColor.ShowText(m_bShowText);
	m_cpTextColor.ShowText(m_bShowText);
	m_chkColorText.EnableWindow(m_bShowText);

	if (m_bShowText == FALSE && m_bColorText == TRUE)
	{
		m_bColorText = FALSE;
		m_chkColorText.SetCheck(m_bColorText);
		OnChkColorText();
	}
}

void CColorPickerDlg::OnChkColorText()
{
	UpdateData();
	m_cpBackColor.ShowTextInColor(m_bColorText);
	m_cpTextColor.ShowTextInColor(m_bColorText);
}

void CColorPickerDlg::OnSelEndOkComboStyle() 
{
	UpdateData();

	switch (m_nStyle)
	{
	case 0: // 16 colors
		{
			m_cpBackColor.SetColors(NULL, 0, 8);
			m_cpBackColor.GetThemeColors().RemoveAll();
			m_cpBackColor.GetStandardColors().RemoveAll();
			m_cpBackColor.ModifyCPStyle(CPS_XTP_EXTENDED, 0);

			m_cpTextColor.SetColors(NULL, 0, 8);
			m_cpTextColor.GetThemeColors().RemoveAll();
			m_cpTextColor.GetStandardColors().RemoveAll();
			m_cpTextColor.ModifyCPStyle(CPS_XTP_EXTENDED, 0);
		}
		break;

	case 1: // 40 colors
		{
			m_cpBackColor.SetColors(NULL, 0, 8, _T("Extended Colors"));
			m_cpBackColor.GetThemeColors().RemoveAll();
			m_cpBackColor.GetStandardColors().RemoveAll();
			m_cpBackColor.ModifyCPStyle(0, CPS_XTP_EXTENDED);

			m_cpTextColor.SetColors(NULL, 0, 8, _T("Extended Colors"));
			m_cpTextColor.GetThemeColors().RemoveAll();
			m_cpTextColor.GetStandardColors().RemoveAll();
			m_cpTextColor.ModifyCPStyle(0, CPS_XTP_EXTENDED);
		}
		break;

	case 2: // custom
		{
			XTP_PICK_BUTTON _CustomColors[] =
			{
				{ RGB(0x10,0xA2,0x84), 0, _T("Sea Green")     },
				{ RGB(0x21,0xAE,0x63), 0, _T("Emerald")       },
				{ RGB(0x29,0x82,0xBD), 0, _T("Peter River")   },
				{ RGB(0x8C,0x45,0xAD), 0, _T("Amethyst")      },
				{ RGB(0x29,0x3C,0x52), 0, _T("Midnight Blue") },
				{ RGB(0xF7,0x9E,0x10), 0, _T("Orange")        },
				{ RGB(0xD6,0x55,0x00), 0, _T("Pumpkin")       },
				{ RGB(0xC6,0x38,0x29), 0, _T("Pomegranate")   },
				{ RGB(0xBD,0xC3,0xC6), 0, _T("Silver")        },
				{ RGB(0x7B,0x8E,0x8C), 0, _T("Asbestos")      },
			};

			LPCTSTR _ColorDesc[10] = 
			{
				_T("Accent 1"),
				_T("Accent 2"),
				_T("Accent 3"),
				_T("Accent 4"),
				_T("Accent 5"),
				_T("Accent 6"),
				_T("Accent 7"),
				_T("Accent 8"),
				_T("Accent 9"),
				_T("Accent 10"),
			};

			int _ShadeMatrix[6][10] = 
			{
				{   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
				{ +80, +80, +80, +80, +80, +80, +80, +80, +80, +80 },
				{ +60, +60, +60, +60, +60, +60, +60, +60, +60, +60 },
				{ +20, +20, +20, +20, +20, +20, +20, +20, +20, +20 },
				{ -25, -25, -25, -25, -25, -25, -25, -25, -25, -25 },
				{ -50, -50, -50, -50, -50, -50, -50, -50, -50, -50 },
			};

			m_cpBackColor.SetColors(NULL, 0, 8);
			m_cpBackColor.SetThemeColors(_CustomColors, _countof(_CustomColors), _T("Custom Colors"), _ColorDesc, _ShadeMatrix);
			m_cpBackColor.GetStandardColors().RemoveAll();

			m_cpTextColor.SetColors(NULL, 0, 8);
			m_cpTextColor.SetThemeColors(_CustomColors, _countof(_CustomColors), _T("Custom Colors"), _ColorDesc, _ShadeMatrix);
			m_cpTextColor.GetStandardColors().RemoveAll();
		}
		break;

	case 3: // default theme
		{
			m_cpBackColor.SetColors(NULL, 0, 8);
			m_cpBackColor.SetThemeColors();
			m_cpBackColor.SetStandardColors();

			m_cpTextColor.SetColors(NULL, 0, 8);
			m_cpTextColor.SetThemeColors();
			m_cpTextColor.SetStandardColors();
		}
		break;
	}
}

void CColorPickerDlg::OnSelEndOkComboTheme()
{
	UpdateData();

	switch (m_nTheme)
	{
	case 0:
		{
			m_cpBackColor.SetTheme(xtpControlThemeOffice2000);
			m_cpTextColor.SetTheme(xtpControlThemeOffice2000);
		}
		break;
	case 1:
		{
			m_cpBackColor.SetTheme(xtpControlThemeOfficeXP);
			m_cpTextColor.SetTheme(xtpControlThemeOfficeXP);
		}
		break;
	case 2:
		{
			XTPThemeDLL()->SetHandle(xtpIniOffice2013Word);
			m_cpBackColor.SetTheme(xtpControlThemeOffice2013);
			m_cpTextColor.SetTheme(xtpControlThemeOffice2013);
		}
		break;
	case 3:
		{
			XTPThemeDLL()->SetHandle(xtpIniVisualStudio2015Dark);
			m_cpBackColor.SetTheme(xtpControlThemeVisualStudio2015);
			m_cpTextColor.SetTheme(xtpControlThemeVisualStudio2015);
		}
		break;
	}
}

void CColorPickerDlg::OnChkRecent() 
{
	UpdateData();

	if (m_bRecent)
	{
		m_cpBackColor.ModifyCPStyle(0, CPS_XTP_RECENTCOLORS);
		m_cpTextColor.ModifyCPStyle(0, CPS_XTP_RECENTCOLORS);
	}
	else
	{
		m_cpBackColor.ModifyCPStyle(CPS_XTP_RECENTCOLORS, 0);
		m_cpTextColor.ModifyCPStyle(CPS_XTP_RECENTCOLORS, 0);
	}
}

void CColorPickerDlg::OnChkCaptions() 
{
	UpdateData();
	m_cpBackColor.ShowCaptions(m_bCaptions);
	m_cpTextColor.ShowCaptions(m_bCaptions);
}

/////////////////////////////////////////////////////////////////////////////
// CPreviewText message handlers

BEGIN_MESSAGE_MAP(CPreviewText, CStatic)
	//{{AFX_MSG_MAP(CPreviewText)
	ON_WM_NCPAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPreviewText message handlers

void CPreviewText::OnNcPaint() 
{
	CXTPWindowRect rcWindow(this);
	rcWindow.OffsetRect(-rcWindow.TopLeft());

	CWindowDC dc(this);
	dc.Draw3dRect(&rcWindow, RGB(0,0,0), RGB(0,0,0));
}
