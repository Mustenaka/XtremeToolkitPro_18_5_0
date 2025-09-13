// ScrollBarDlg.cpp 
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

#include "ScrollBar.h"
#include "ViewFrame.h"
#include "ScrollBarDlg.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

enum XTPScrollBarThemeExtended
{
	XTPScrollBarThemeExtendedFirst = 1000,
	xtpScrollBarThemeOffice_2007_AquaLight = XTPScrollBarThemeExtendedFirst,
	xtpScrollBarThemeOffice_2007_AquaDark,
	xtpScrollBarThemeOffice_2007_BlackLight,
	xtpScrollBarThemeOffice_2007_BlackDark,
	xtpScrollBarThemeOffice_2007_BlueLight,
	xtpScrollBarThemeOffice_2007_BlueDark,
	xtpScrollBarThemeOffice_2007_SilverLight,
	xtpScrollBarThemeOffice_2007_SilverDark,

	//// Disabled due to a bug in VC6 resource compiler - too much data.
	//xtpScrollBarThemeOffice_2010_BlackLight,
	//xtpScrollBarThemeOffice_2010_BlackDark,
	//xtpScrollBarThemeOffice_2010_BlueLight,
	//xtpScrollBarThemeOffice_2010_BlueDark,
	//xtpScrollBarThemeOffice_2010_SilverLight,
	//xtpScrollBarThemeOffice_2010_SilverDark,
	//xtpScrollBarThemeWindows7_BlueLight,
	//xtpScrollBarThemeWindows7_BlueDark,
};

/////////////////////////////////////////////////////////////////////////////
// CScrollBarDlg dialog

CScrollBarDlg::CScrollBarDlg(CWnd* pParent /*=NULL*/)
	: CXTPDialogScrollBarContainer<CDialog>(CScrollBarDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScrollBarDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_btnSet[SB_HORZ].m_pBtnUseScrollBar = &m_btnHUseHScroll;
	m_btnSet[SB_HORZ].m_pBtnVisible = &m_btnHVisible;
	m_btnSet[SB_HORZ].m_pBtnEnabled = &m_btnHEnabled;

	m_btnSet[SB_VERT].m_pBtnUseScrollBar = &m_btnVUseVScroll;
	m_btnSet[SB_VERT].m_pBtnVisible = &m_btnVVisible;
	m_btnSet[SB_VERT].m_pBtnEnabled = &m_btnVEnabled;
}

void CScrollBarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScrollBarDlg)
	DDX_Control(pDX, IDC_COMBO_THEMES, m_cboxTheme);
	DDX_Control(pDX, IDC_H_HSCROLL_ENABLED, m_btnHUseHScroll);
	DDX_Control(pDX, IDC_H_VISIBLE, m_btnHVisible);
	DDX_Control(pDX, IDC_H_ENABLED, m_btnHEnabled);
	DDX_Control(pDX, IDC_V_VSCROLL_ENABLED, m_btnVUseVScroll);
	DDX_Control(pDX, IDC_V_VISIBLE, m_btnVVisible);
	DDX_Control(pDX, IDC_V_ENABLED, m_btnVEnabled);
	//}}AFX_DATA_MAP
}

void CScrollBarDlg::SetScrollBarTheme(XTPScrollBarTheme theme)
{
	CXTPDialogScrollBarContainer<CDialog>::SetScrollBarTheme(theme);
	m_dlgView.SetScrollBarTheme(theme);

	RedrawWindow(NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

BEGIN_MESSAGE_MAP(CScrollBarDlg, CDialog)
	//{{AFX_MSG_MAP(CScrollBarDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO_THEMES, CScrollBarDlg::OnCbnSelchangeComboThemes)
	ON_BN_CLICKED(IDC_H_HSCROLL_ENABLED, CScrollBarDlg::OnHScrollChanged)
	ON_BN_CLICKED(IDC_H_VISIBLE, CScrollBarDlg::OnHScrollChanged)
	ON_BN_CLICKED(IDC_H_ENABLE, CScrollBarDlg::OnHScrollChanged)
	ON_BN_CLICKED(IDC_V_VSCROLL_ENABLED, CScrollBarDlg::OnVScrollChanged)
	ON_BN_CLICKED(IDC_V_VISIBLE, CScrollBarDlg::OnVScrollChanged)
	ON_BN_CLICKED(IDC_V_ENABLE, CScrollBarDlg::OnVScrollChanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScrollBarDlg message handlers

BOOL CScrollBarDlg::OnInitDialog()
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

	OptimizeChildrenClipping();
	FillThemeScrollbar();
	CreateViewDlg();

	m_btnHUseHScroll.SetCheck(BST_CHECKED);
	m_btnHVisible.SetCheck(BST_CHECKED);
	m_btnHEnabled.SetCheck(BST_CHECKED);
	m_btnVUseVScroll.SetCheck(BST_CHECKED);
	m_btnVVisible.SetCheck(BST_CHECKED);
	m_btnVEnabled.SetCheck(BST_CHECKED);

	SyncScrollbarState(SB_HORZ);
	SyncScrollbarState(SB_VERT);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CScrollBarDlg::FillThemeScrollbar()
{
	m_cboxTheme.ResetContent();
	static const struct
	{
		LPCTSTR name;
		int theme;
	}
	entries[] =
	{
#define THEMEBOX_ENTRY(theme) { _T(#theme), theme }
		THEMEBOX_ENTRY(xtpScrollBarThemeWindowsDefault),
		THEMEBOX_ENTRY(xtpScrollBarThemeWindowsClassic),

		//// Disabled due to a bug in VC6 resource compiler - too much data.
		//THEMEBOX_ENTRY(xtpScrollBarThemeWindows7_BlueLight),
		//THEMEBOX_ENTRY(xtpScrollBarThemeWindows7_BlueDark),

		THEMEBOX_ENTRY(xtpScrollBarThemeFlat),
		THEMEBOX_ENTRY(xtpScrollBarThemeUltraFlat),
		THEMEBOX_ENTRY(xtpScrollBarThemeOffice2000),
		THEMEBOX_ENTRY(xtpScrollBarThemeOfficeXP),
		THEMEBOX_ENTRY(xtpScrollBarThemeOffice2003),
		THEMEBOX_ENTRY(xtpScrollBarThemeOffice_2007_AquaLight),
		THEMEBOX_ENTRY(xtpScrollBarThemeOffice_2007_AquaDark),
		THEMEBOX_ENTRY(xtpScrollBarThemeOffice_2007_BlackLight),
		THEMEBOX_ENTRY(xtpScrollBarThemeOffice_2007_BlackDark),
		THEMEBOX_ENTRY(xtpScrollBarThemeOffice_2007_BlueLight),
		THEMEBOX_ENTRY(xtpScrollBarThemeOffice_2007_BlueDark),
		THEMEBOX_ENTRY(xtpScrollBarThemeOffice_2007_SilverLight),
		THEMEBOX_ENTRY(xtpScrollBarThemeOffice_2007_SilverDark),

		//// Disabled due to a bug in VC6 resource compiler - too much data.
		//THEMEBOX_ENTRY(xtpScrollBarThemeOffice_2010_BlackLight),
		//THEMEBOX_ENTRY(xtpScrollBarThemeOffice_2010_BlackDark),
		//THEMEBOX_ENTRY(xtpScrollBarThemeOffice_2010_BlueLight),
		//THEMEBOX_ENTRY(xtpScrollBarThemeOffice_2010_BlueDark),
		//THEMEBOX_ENTRY(xtpScrollBarThemeOffice_2010_SilverLight),
		//THEMEBOX_ENTRY(xtpScrollBarThemeOffice_2010_SilverDark),

		THEMEBOX_ENTRY(xtpScrollBarThemeOffice2010),
		THEMEBOX_ENTRY(xtpScrollBarThemeOffice2013),
		THEMEBOX_ENTRY(xtpScrollBarThemeVisualStudio6),
		THEMEBOX_ENTRY(xtpScrollBarThemeVisualStudio2002),
		THEMEBOX_ENTRY(xtpScrollBarThemeVisualStudio2003),
		THEMEBOX_ENTRY(xtpScrollBarThemeVisualStudio2005),
		THEMEBOX_ENTRY(xtpScrollBarThemeVisualStudio2008),
		THEMEBOX_ENTRY(xtpScrollBarThemeVisualStudio2010),
		THEMEBOX_ENTRY(xtpScrollBarThemeVisualStudio2012Light),
		THEMEBOX_ENTRY(xtpScrollBarThemeVisualStudio2012Dark),
	};

	for(int i = 0; i < _countof(entries); ++i)
	{
		LPCTSTR name = entries[i].name + sizeof("xtpScrollBarTheme") - 1;
		int index = m_cboxTheme.InsertString(-1, name);
		if(CB_ERR != index)
		{
			m_cboxTheme.SetItemData(index, entries[i].theme);
		}
	}

	m_cboxTheme.SetCurSel(0);
}

void CScrollBarDlg::CreateViewDlg()
{
	ASSERT(!::IsWindow(m_dlgView));

	CRect rcSeparator;
	GetDlgItem(IDC_STATIC_SEPARATOR)->GetWindowRect(&rcSeparator);
	ScreenToClient(&rcSeparator);

	CRect rcClient;
	GetClientRect(&rcClient);

	int cyHScroll = ::GetSystemMetrics(SM_CYHSCROLL);
	int cxVScroll = ::GetSystemMetrics(SM_CXVSCROLL);

	CRect rcView = rcClient;
	rcView.left = rcSeparator.right;
	rcView.DeflateRect(10, 10, 10 + cxVScroll, 10 + cyHScroll);

	LPCTSTR lpClassName = AfxRegisterWndClass(CS_OWNDC, LoadCursor(NULL, IDC_ARROW));
	if(m_dlgView.Create(lpClassName, _T("Picture View"), 
		WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN 
		| WS_CLIPSIBLINGS | WS_CAPTION | WS_THICKFRAME,
		rcView, this))
	{
		m_dlgView.SetWindowPos(
			&CWnd::wndBottom,
			0, 0, 0, 0,
			SWP_NOMOVE | SWP_NOSIZE);
	}
	else
	{
		TRACE0("Failed to create CViewFrame window");
	}
}

void CScrollBarDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CScrollBarDlg::OnPaint()
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
HCURSOR CScrollBarDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CScrollBarDlg::OnCbnSelchangeComboThemes()
{
	int selection = m_cboxTheme.GetCurSel();
	if(CB_ERR != selection)
	{
		DWORD_PTR nTheme = m_cboxTheme.GetItemData(selection);
		if(XTPScrollBarThemeExtendedFirst <= nTheme)
		{
			switch(nTheme)
			{
			case xtpScrollBarThemeOffice_2007_AquaLight:
				XTPResourceImages()->SetHandle(AfxGetResourceHandle(), _T("OFFICE2007AQUA.INI"));
				nTheme = xtpScrollBarThemeOffice2007Light;
				break;
			case xtpScrollBarThemeOffice_2007_AquaDark:
				XTPResourceImages()->SetHandle(AfxGetResourceHandle(), _T("OFFICE2007AQUA.INI"));
				nTheme = xtpScrollBarThemeOffice2007Dark;
				break;
			case xtpScrollBarThemeOffice_2007_BlackLight:
				XTPResourceImages()->SetHandle(AfxGetResourceHandle(), _T("OFFICE2007BLACK.INI"));
				nTheme = xtpScrollBarThemeOffice2007Light;
				break;
			case xtpScrollBarThemeOffice_2007_BlackDark:
				XTPResourceImages()->SetHandle(AfxGetResourceHandle(), _T("OFFICE2007BLACK.INI"));
				nTheme = xtpScrollBarThemeOffice2007Dark;
				break;
			case xtpScrollBarThemeOffice_2007_BlueLight:
				XTPResourceImages()->SetHandle(AfxGetResourceHandle(), _T("OFFICE2007BLUE.INI"));
				nTheme = xtpScrollBarThemeOffice2007Light;
				break;
			case xtpScrollBarThemeOffice_2007_BlueDark:
				XTPResourceImages()->SetHandle(AfxGetResourceHandle(), _T("OFFICE2007BLUE.INI"));
				nTheme = xtpScrollBarThemeOffice2007Dark;
				break;
			case xtpScrollBarThemeOffice_2007_SilverLight:
				XTPResourceImages()->SetHandle(AfxGetResourceHandle(), _T("OFFICE2007SILVER.INI"));
				nTheme = xtpScrollBarThemeOffice2007Light;
				break;
			case xtpScrollBarThemeOffice_2007_SilverDark:
				XTPResourceImages()->SetHandle(AfxGetResourceHandle(), _T("OFFICE2007SILVER.INI"));
				nTheme = xtpScrollBarThemeOffice2007Dark;
				break;

			//// Disabled due to a bug in VC6 resource compiler - too much data.
			//case xtpScrollBarThemeOffice_2010_BlackLight:
			//	XTPResourceImages()->SetHandle(AfxGetResourceHandle(), _T("OFFICE2010BLACK.INI"));
			//	nTheme = xtpScrollBarThemeOffice2007Light;
			//	break;
			//case xtpScrollBarThemeOffice_2010_BlackDark:
			//	XTPResourceImages()->SetHandle(AfxGetResourceHandle(), _T("OFFICE2010BLACK.INI"));
			//	nTheme = xtpScrollBarThemeOffice2007Dark;
			//	break;
			//case xtpScrollBarThemeOffice_2010_BlueLight:
			//	XTPResourceImages()->SetHandle(AfxGetResourceHandle(), _T("OFFICE2010BLUE.INI"));
			//	nTheme = xtpScrollBarThemeOffice2007Light;
			//	break;
			//case xtpScrollBarThemeOffice_2010_BlueDark:
			//	XTPResourceImages()->SetHandle(AfxGetResourceHandle(), _T("OFFICE2010BLUE.INI"));
			//	nTheme = xtpScrollBarThemeOffice2007Dark;
			//	break;
			//case xtpScrollBarThemeOffice_2010_SilverLight:
			//	XTPResourceImages()->SetHandle(AfxGetResourceHandle(), _T("OFFICE2010SILVER.INI"));
			//	nTheme = xtpScrollBarThemeOffice2007Light;
			//	break;
			//case xtpScrollBarThemeOffice_2010_SilverDark:
			//	XTPResourceImages()->SetHandle(AfxGetResourceHandle(), _T("OFFICE2010SILVER.INI"));
			//	nTheme = xtpScrollBarThemeOffice2007Dark;
			//	break;
			//case xtpScrollBarThemeWindows7_BlueLight:
			//	XTPResourceImages()->SetHandle(AfxGetResourceHandle(), _T("WINDOWS7BLUE.INI"));
			//	nTheme = xtpScrollBarThemeOffice2007Light;
			//	break;
			//case xtpScrollBarThemeWindows7_BlueDark:
			//	XTPResourceImages()->SetHandle(AfxGetResourceHandle(), _T("WINDOWS7BLUE.INI"));
			//	nTheme = xtpScrollBarThemeOffice2007Dark;
			//	break;
			default:
				ASSERT(!"Unexpected extended theme ID");
				break;
			}
		}
		else
		{
			XTPResourceImages()->SetHandle(AfxGetResourceHandle());
		}

		SetScrollBarTheme(static_cast<XTPScrollBarTheme>(nTheme));
	}
}

void CScrollBarDlg::OnHScrollChanged()
{
	SyncScrollbarState(SB_HORZ);
}

void CScrollBarDlg::OnVScrollChanged()
{
	SyncScrollbarState(SB_VERT);
}

void CScrollBarDlg::SyncScrollbarState(int nBar)
{
	ASSERT(SB_HORZ == nBar || SB_VERT == nBar);

	UINT sbStyle[] = { WS_HSCROLL, WS_VSCROLL };

	// Turn scroll bar on/off
	BOOL bUseScrollBar = (m_btnSet[nBar].m_pBtnUseScrollBar->GetCheck() & BST_CHECKED) != 0;
	if(bUseScrollBar)
	{
		ModifyStyle(0, sbStyle[nBar]);
	}
	else
	{
		ModifyStyle(sbStyle[nBar], 0);
	}

	if(bUseScrollBar)
	{
		// Show/hide scroll bar
		BOOL bVisible = (m_btnSet[nBar].m_pBtnVisible->GetCheck() & BST_CHECKED) != 0;
		ShowScrollBar(nBar, bVisible);

		// Enable/disable scroll bar
		BOOL bEnabled = (m_btnSet[nBar].m_pBtnEnabled->GetCheck() & BST_CHECKED) != 0;
		EnableScrollBar(nBar, bEnabled ? ESB_ENABLE_BOTH : ESB_DISABLE_BOTH);
	}
}