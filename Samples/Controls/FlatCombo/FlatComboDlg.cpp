// FlatComboDlg.cpp 
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
#include "FlatCombo.h"
#include "FlatComboDlg.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CFlatComboDlg dialog

CFlatComboDlg::CFlatComboDlg(CWnd* pParent /*=NULL*/)
	: CXTPResizeDialog(CFlatComboDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFlatComboDlg)
	m_bAutoComplete = FALSE;
	m_bDropDownDisable = FALSE;
	m_bDropListDisable = FALSE;
	m_bFlatBorders = FALSE;
	m_nTheme = 2;
	//}}AFX_DATA_INIT

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CFlatComboDlg::~CFlatComboDlg()
{
	while (!m_themeList.IsEmpty())
	{
		THEMEDATA* pData = m_themeList.RemoveTail();
		SAFE_DELETE(pData);
	}
}

void CFlatComboDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTPResizeDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFlatComboDlg)
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDC_DROPDOWN_AUTOCOMP, m_chkAutoComplete);
	DDX_Control(pDX, IDC_DROPDOWN_DISABLE, m_chkDropDownDisable);
	DDX_Control(pDX, IDC_DROPDOWN_USE_DEFAULT_COLORS, m_chkDropDownUseDefColors);
	DDX_Control(pDX, IDC_DROPLIST_DISABLE, m_chkDropListDisabled);
	DDX_Control(pDX, IDC_DROPLIST_USE_DEFAULT_COLORS, m_chkDropListUseDefColors);
	DDX_Control(pDX, IDC_LIST_THEME, m_wndListBoxTheme);
	DDX_Control(pDX, IDC_EDIT_THEMED, m_wndEditThemed);
	DDX_Control(pDX, IDC_GBOX_EDIT, m_gboxEdit);
	DDX_Control(pDX, IDC_GBOX_LIST, m_gboxList);
	DDX_Control(pDX, IDC_GBOX_DOWN, m_gboxDown);
	DDX_Control(pDX, IDC_GBOX_THEME, m_gboxAppear);
	DDX_Control(pDX, IDC_DROPLIST_TXT_CLR, m_txtDropListColor);
	DDX_Control(pDX, IDC_DROPLIST_BAK_CLR, m_cpDropList);
	DDX_Control(pDX, IDC_DROPDOWN_TXT_CLR, m_txtDropDownColor);
	DDX_Control(pDX, IDC_DROPDOWN_BAK_CLR, m_cpDropDown);
	DDX_Control(pDX, IDC_DROPDOWN_COMBO, m_wndDropDownCombo);
	DDX_Control(pDX, IDC_DROPLIST_COMBO, m_wndDropListCombo);
	DDX_Check(pDX, IDC_DROPDOWN_AUTOCOMP, m_bAutoComplete);
	DDX_Check(pDX, IDC_DROPDOWN_DISABLE, m_bDropDownDisable);
	DDX_Check(pDX, IDC_DROPLIST_DISABLE, m_bDropListDisable);
	DDX_Check(pDX, IDC_DROPDOWN_USE_DEFAULT_COLORS, m_bDropDownUseDefColors);
	DDX_Check(pDX, IDC_DROPLIST_USE_DEFAULT_COLORS, m_bDropListUseDefColors);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFlatComboDlg, CXTPResizeDialog)
	//{{AFX_MSG_MAP(CFlatComboDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DROPLIST_DISABLE, OnDroplistDisable)
	ON_BN_CLICKED(IDC_DROPDOWN_DISABLE, OnDropdownDisable)
	ON_BN_CLICKED(IDC_DROPDOWN_AUTOCOMP, OnDropdownAutocomp)
	ON_BN_CLICKED(IDC_DROPDOWN_USE_DEFAULT_COLORS, OnBnClickedChkDropDownUseDefColors)
	ON_BN_CLICKED(IDC_DROPLIST_USE_DEFAULT_COLORS, OnBnClickedChkDropListUseDefColors)
	ON_CPN_XTP_SELENDOK(IDC_DROPLIST_TXT_CLR, OnSelEndOKDLTxtClr)
	ON_CPN_XTP_SELENDOK(IDC_DROPLIST_BAK_CLR, OnSelEndOKDLBakClr)
	ON_CPN_XTP_SELENDOK(IDC_DROPDOWN_TXT_CLR, OnSelEndOKDDTxtClr)
	ON_CPN_XTP_SELENDOK(IDC_DROPDOWN_BAK_CLR, OnSelEndOKDDBakClr)
	ON_WM_DESTROY()
	ON_LBN_SELCHANGE(IDC_LIST_THEME, OnSelChangeListTheme)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CFlatComboDlg::UpdateCombo1()
{
	UpdateData();

	CXTPComboBoxTheme* pTheme = m_wndDropDownCombo.GetTheme();
	if(NULL != pTheme)
	{
		if(!m_bDropDownUseDefColors)
		{
			pTheme->SetTextColor(m_txtDropDownColor.GetColor());
			pTheme->SetBackColor(m_cpDropDown.GetColor());
		}
		else
		{
			pTheme->ResetTextColor();
			pTheme->ResetBackColor();
		}
	}

	m_wndDropDownCombo.RefreshMetrics();
	m_wndDropDownCombo.RedrawWindow();
}

void CFlatComboDlg::UpdateCombo2()
{
	UpdateData();

	CXTPComboBoxTheme* pTheme = m_wndDropListCombo.GetTheme();
	if(NULL != pTheme)
	{
		if(!m_bDropListUseDefColors)
		{
			pTheme->SetTextColor(m_txtDropListColor.GetColor());
			pTheme->SetBackColor(m_cpDropList.GetColor());
		}
		else
		{
			pTheme->ResetTextColor();
			pTheme->ResetBackColor();
		}
	}

	m_wndDropListCombo.RefreshMetrics();
	m_wndDropListCombo.RedrawWindow();
}

/////////////////////////////////////////////////////////////////////////////
// CFlatComboDlg message handlers

void CFlatComboDlg::AddTheme(LPCTSTR lpszThemeName, XTPControlTheme themeID, LPCTSTR lpszINI /*=NULL*/, BOOL bSelect /*=FALSE*/)
{
	int nIndex = m_wndListBoxTheme.AddString(lpszThemeName);

	THEMEDATA* pData = new THEMEDATA;
	pData->lpszINI = lpszINI;
	pData->themeID = themeID;
	
	m_wndListBoxTheme.SetItemData(nIndex, reinterpret_cast<DWORD_PTR>(pData));

	if (bSelect)
	{
		m_wndListBoxTheme.SetCurSel(nIndex);
		OnSelChangeListTheme();
	}

	m_themeList.AddTail(pData);
}

BOOL CFlatComboDlg::OnInitDialog()
{
	CXTPResizeDialog::OnInitDialog();

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

	AddTheme(_T("Flat"),                       xtpControlThemeFlat);
	AddTheme(_T("Ultra Flat"),                 xtpControlThemeUltraFlat);
	AddTheme(_T("Native Windows"),             xtpControlThemeNativeWinXP);
	AddTheme(_T("Office 2000"),                xtpControlThemeOffice2000);
	AddTheme(_T("Office XP"),                  xtpControlThemeOfficeXP);
	AddTheme(_T("Office 2003"),                xtpControlThemeOffice2003);
	AddTheme(_T("Office 2007"),                xtpControlThemeResource,   xtpIniOffice2007Blue);
	AddTheme(_T("Office 2013 (Access)"),       xtpControlThemeOffice2013, xtpIniOffice2013Access);
	AddTheme(_T("Office 2013 (Excel)"),        xtpControlThemeOffice2013, xtpIniOffice2013Excel);
	AddTheme(_T("Office 2013 (One Note)"),     xtpControlThemeOffice2013, xtpIniOffice2013OneNote);
	AddTheme(_T("Office 2013 (Outlook)"),      xtpControlThemeOffice2013, xtpIniOffice2013Outlook);
	AddTheme(_T("Office 2013 (Publisher)"),    xtpControlThemeOffice2013, xtpIniOffice2013Publisher);
	AddTheme(_T("Office 2013 (Power Point)"),  xtpControlThemeOffice2013, xtpIniOffice2013PowerPoint);
	AddTheme(_T("Office 2013 (Word)"),         xtpControlThemeOffice2013, xtpIniOffice2013Word, TRUE);
	AddTheme(_T("Visual Studio 2015 (Blue)"),  xtpControlThemeVisualStudio2015, xtpIniVisualStudio2015Blue);
	AddTheme(_T("Visual Studio 2015 (Light)"), xtpControlThemeVisualStudio2015, xtpIniVisualStudio2015Light);

	// Set control resizing.
	SetResize(IDC_GBOX_LIST, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_DROPLIST_COMBO, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_GBOX_DOWN, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_DROPDOWN_COMBO, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_GBOX_EDIT, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_EDIT_THEMED, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_GBOX_THEME, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDOK, XTP_ANCHOR_TOPRIGHT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDCANCEL, XTP_ANCHOR_TOPRIGHT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_LIST_THEME, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_BOTTOMRIGHT);

	// Load window placement
	LoadPlacement(_T("CFlatComboDlg2"));

	// set each combo's index.
	m_wndDropDownCombo.SetCurSel(0);
	m_wndDropListCombo.SetCurSel(1);

	// enable auto completion based on boolean.
	m_wndDropDownCombo.EnableAutoCompletion( m_bAutoComplete );

	// set the text color controls based on current combo theme.
	const CXTPComboBoxTheme* pTheme = m_wndDropListCombo.GetTheme();
	if(NULL != pTheme)
	{
		m_txtDropListColor.SetColor( pTheme->GetTextColor() );
		m_cpDropList.SetColor( pTheme->GetBackColor() );
	}

	pTheme = m_wndDropDownCombo.GetTheme();
	if(NULL != pTheme)
	{
		m_txtDropDownColor.SetColor( pTheme->GetTextColor() );
		m_cpDropDown.SetColor( pTheme->GetBackColor() );
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFlatComboDlg::OnDestroy()
{
	// Save window placement
	SavePlacement(_T("CFlatComboDlg2"));

	CXTPResizeDialog::OnDestroy();
}

void CFlatComboDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CXTPResizeDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFlatComboDlg::OnPaint()
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
		CXTPResizeDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFlatComboDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFlatComboDlg::OnSelEndOKDLTxtClr()
{
	UpdateCombo2();
}

void CFlatComboDlg::OnSelEndOKDLBakClr()
{
	UpdateCombo2();
}

void CFlatComboDlg::OnSelEndOKDDTxtClr()
{
	UpdateCombo1();
}

void CFlatComboDlg::OnSelEndOKDDBakClr()
{
	UpdateCombo1();
}

void CFlatComboDlg::OnDroplistDisable()
{
	UpdateData();
	m_wndDropListCombo.EnableWindow( !m_bDropListDisable );
}

void CFlatComboDlg::OnDropdownDisable()
{
	UpdateData();
	m_wndDropDownCombo.EnableWindow( !m_bDropDownDisable );
}

void CFlatComboDlg::OnDropdownAutocomp()
{
	UpdateData();
	m_wndDropDownCombo.EnableAutoCompletion( m_bAutoComplete );
}

void CFlatComboDlg::OnBnClickedChkDropDownUseDefColors()
{
	UpdateData();

	m_txtDropDownColor.EnableWindow(!m_bDropDownUseDefColors);
	m_cpDropDown.EnableWindow(!m_bDropDownUseDefColors);

	UpdateCombo1();
}

void CFlatComboDlg::OnBnClickedChkDropListUseDefColors()
{
	UpdateData();

	m_txtDropListColor.EnableWindow(!m_bDropListUseDefColors);
	m_cpDropList.EnableWindow(!m_bDropListUseDefColors);

	UpdateCombo2();
}

void CFlatComboDlg::OnSelChangeListTheme() 
{
	THEMEDATA* pData = (THEMEDATA*)m_wndListBoxTheme.GetItemData(m_wndListBoxTheme.GetCurSel());
	if (pData)
	{
		if (pData->lpszINI != NULL)
		{
			XTPThemeDLL()->SetHandle(pData->lpszINI);
		}

		SendMessageToDescendants(WM_XTP_SETCONTROLTHEME, pData->themeID);

		UpdateData(FALSE);

		RedrawWindow(0, 0, RDW_ALLCHILDREN|RDW_INVALIDATE|RDW_ERASE);
	}
}
