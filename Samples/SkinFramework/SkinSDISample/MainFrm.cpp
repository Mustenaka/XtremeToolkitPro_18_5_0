// MainFrm.cpp
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
#include "SkinSDISample.h"

#include "MainFrm.h"
#include "SkinManagerExtResourceFile.h"
#include "SampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#ifndef RBBS_USECHEVRON
#define RBBS_USECHEVRON     0x00000200  // display drop-down button for this band if it's sized smaller than ideal width
#endif


/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_MENUCHAR()
	//}}AFX_MSG_MAP
#ifdef _XTP_INCLUDE_COMMANDBARS
	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
#endif
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};
/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	TCHAR szStylesPath[_MAX_PATH];

	VERIFY(::GetModuleFileName(
		AfxGetApp()->m_hInstance, szStylesPath, _MAX_PATH));		
	
	CString csStylesPath(szStylesPath);
	int nIndex  = csStylesPath.ReverseFind(_T('\\'));
	if (nIndex > 0) {
		csStylesPath = csStylesPath.Left(nIndex);
	}
	else {
		csStylesPath.Empty();
	}
	
	m_strStylesPath = csStylesPath + _T("\\Styles\\");

	
	XTPSkinManager()->SetApplyOptions(xtpSkinApplyFrame | xtpSkinApplyColors | xtpSkinApplyMetrics | xtpSkinApplyMenus);

	LoadSkin(0);	
}

CMainFrame::~CMainFrame()
{
	XTPSkinManager()->LoadSkin(NULL);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

#ifndef _XTP_INCLUDE_COMMANDBARS
	if (!m_wndToolBar.Create(this, TBSTYLE_FLAT | WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
#else

	// Create UI font.
	HFONT hDefFont = reinterpret_cast<HFONT>(GetStockObject(DEFAULT_GUI_FONT));
	if(NULL != hDefFont)
	{
		LOGFONT lfDefFont = { 0 };
		if(0 < GetObject(hDefFont, sizeof(lfDefFont), &lfDefFont))
		{
			m_fntUI.CreateFontIndirect(&lfDefFont);
		}
	}

	// Create ReBar.
	if (!m_wndReBar.Create(this, 
		RBS_AUTOSIZE | RBS_FIXEDORDER | RBS_BANDBORDERS | RBS_TOOLTIPS | WS_CHILD | WS_VISIBLE))
	{
		TRACE0("Failed to create ReBar\n");
		return -1;      // fail to create
	}

	// Add Toolbar to ReBar.
	CBitmap bmp;
	if(!bmp.LoadBitmap(IDR_MAINFRAME))
	{
		TRACE0("Failed to load bitmap\n");
		return -1;
	}

	if(!m_imgListReBar.Create(MAKEINTRESOURCE(IDR_MAINFRAME), 0x10, 1, CLR_DEFAULT))
	{
		TRACE0("Failed to create imagelist\n");
		return -1;
	}

	m_imgListReBar.Add(&bmp, RGB(0,0,0));
	m_wndReBar.GetReBarCtrl().SetImageList(&m_imgListReBar);

	//TBSTYLE_FLAT
	if (!m_wndReBarToolBar.Create(&m_wndReBar, 
		TBSTYLE_FLAT | WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndReBarToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	m_wndReBar.AddBar(&m_wndReBarToolBar, _T("Toolbar:"), 0, RBBS_GRIPPERALWAYS | RBBS_USECHEVRON);

	// Add ComboBox to ReBar
	CXTPClientRect rcReBar(&m_wndReBar);
	m_wndComboBox.Create(CBS_DROPDOWN | WS_CHILD | WS_VISIBLE, rcReBar, &m_wndReBar, 0);
	if(NULL != m_fntUI.m_hObject)
	{
		m_wndComboBox.SetFont(&m_fntUI);
	}
	int nUrlIndex = m_wndComboBox.InsertString(-1, _T("http://www.codejock.com"));
	m_wndComboBox.SetCurSel(nUrlIndex);
	m_wndReBar.AddBar(&m_wndComboBox, _T("URL:"), 0, RBBS_GRIPPERALWAYS | RBBS_USECHEVRON);

	REBARBANDINFO rbbi = { 0 };
	rbbi.cbSize = sizeof(rbbi);
	rbbi.fMask = RBBIM_IMAGE;
	rbbi.iImage = 7;
	m_wndReBar.GetReBarCtrl().SetBandInfo(1, &rbbi);

	// Create Status bar.
	// Important: All control bars including the Status Bar
	// must be created before CommandBars....
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// Initialize the command bars
	if (!InitCommandBars())
		return -1;

	XTPPaintManager()->SetTheme(xtpThemeNativeWinXP);
	XTPPaintManager()->GetIconsInfo()->bUseFadedIcons = FALSE;

	// Get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if(pCommandBars == NULL)
	{
		TRACE0("Failed to create command bars object.\n");
		return -1;      // fail to create
	}

	// Add the menu bar
	CXTPCommandBar* pMenuBar = pCommandBars->SetMenu(
		_T("Menu Bar"), IDR_MAINFRAME);
	if(pMenuBar == NULL)
	{
		TRACE0("Failed to create menu bar.\n");
		return -1;      // fail to create
	}

	// Create ToolBar
	CXTPToolBar* pToolBar = (CXTPToolBar*)
		pCommandBars->Add(_T("Standard"), xtpBarTop);
	if (!pToolBar || !pToolBar->LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}
	pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME, IDR_TOOLBAR_ALPHA);

	pCommandBars->GetShortcutManager()->SetAccelerators(IDR_MAINFRAME);

	pCommandBars->GetPaintManager()->m_bAutoResizeIcons = TRUE;
	pCommandBars->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE);

	// Load the previous state for toolbars and menus.
	LoadCommandBars(_T("CommandBars"));

	PostMessage(WM_SYSCOLORCHANGE);

#endif

	return 0;
}

void CMainFrame::OnClose()
{
#ifdef _XTP_INCLUDE_COMMANDBARS
	// Save the current state for toolbars and menus.
	SaveCommandBars(_T("CommandBars"));
#endif

	CFrameWnd::OnClose();
}

LRESULT CMainFrame::OnMenuChar(UINT nChar, UINT nFlags, CMenu *pMenu)
{
	return CFrameWnd::OnMenuChar(nChar, nFlags, pMenu);
}

void CMainFrame::OnCustomize()
{
#ifdef _XTP_INCLUDE_COMMANDBARS
	// Get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if(pCommandBars != NULL)
	{
		// Instanciate the customize dialog object.
		CXTPCustomizeSheet dlg(pCommandBars);

		// Add the keyboard page to the customize dialog.
		CXTPCustomizeKeyboardPage pageKeyboard(&dlg);
		dlg.AddPage(&pageKeyboard);
		pageKeyboard.AddCategories(IDR_MAINFRAME);

		// Add the options page to the customize dialog.
		CXTPCustomizeOptionsPage pageOptions(&dlg);
		dlg.AddPage(&pageOptions);

		// Add the commands page to the customize dialog.
		CXTPCustomizeCommandsPage* pCommands = dlg.GetCommandsPage();
		pCommands->AddCategories(IDR_MAINFRAME);

		// Use the command bar manager to initialize the
		// customize dialog.
		pCommands->InsertAllCommandsCategory();
		pCommands->InsertBuiltInMenus(IDR_MAINFRAME);
		pCommands->InsertNewMenuCategory();

		// Dispaly the dialog.
		dlg.DoModal();
	}
#endif
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.lpszClass = _T("XTPMainFrame");
	CXTPDrawHelpers::RegisterWndClass(AfxGetInstanceHandle(), cs.lpszClass, 
		CS_DBLCLKS, AfxGetApp()->LoadIcon(IDR_MAINFRAME));


	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext) 
{
	m_wndSplitter.CreateStatic(this, 1, 2);

	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CSampleView), CSize(220, 200), NULL);
	m_wndSplitter.CreateView(0, 1, pContext->m_pNewViewClass, CSize(0, 0), pContext);
	
	return TRUE;
}

void CMainFrame::OnSkinChanged()
{
	OnSysColorChange();
	RedrawWindow(0, 0, RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ALLCHILDREN);		
	
#ifdef _XTP_INCLUDE_COMMANDBARS
	XTPPaintManager()->RefreshMetrics();

	GetCommandBars()->GetPaintManager()->RefreshMetrics();

	GetCommandBars()->RedrawCommandBars();	
#endif
}

void CMainFrame::LoadSkin(int nSkin)
{
	switch (nSkin)
	{
	case 1:
		XTPSkinManager()->LoadSkin(m_strStylesPath + _T("iTunes"), _T("Normalitunes.INI"));
		break;

	case 0:
		XTPSkinManager()->LoadSkin(m_strStylesPath + _T("Le5"), _T("NormalBlue.INI"));
		break;

	default:
		XTPSkinManager()->LoadSkin(_T(""), _T(""));
	}

	if (m_hWnd) OnSkinChanged();
}

void CMainFrame::SetTheme(int nTheme, BOOL bFlat)
{
#ifdef _XTP_INCLUDE_COMMANDBARS
	switch (nTheme)
	{
	case 0:
		CXTPPaintManager::SetTheme(xtpThemeOffice2003);
		break;
	
	case 1:
		CXTPPaintManager::SetTheme(xtpThemeNativeWinXP);
		break;
	}
	XTPPaintManager()->GetIconsInfo()->bUseFadedIcons = FALSE;

	if (bFlat)
	{	
		XTPPaintManager()->m_bFlatMenuBar = TRUE;
		XTPPaintManager()->m_bFlatToolBar = TRUE;
	}

	GetCommandBars()->GetPaintManager()->m_bAutoResizeIcons = TRUE;
	GetCommandBars()->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE);
	GetCommandBars()->RedrawCommandBars();	
	RedrawWindow( NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_ALLCHILDREN);  
#endif
}
