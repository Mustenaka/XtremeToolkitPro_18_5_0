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

#include "StdAfx.h"
#include "ReportSample.h"
#include "FolderView.h"
#include "ReportSampleDoc.h"
#include "ReportSampleView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND_EX(ID_TEST_FIELDCHOOSER, OnBarCheck)
	ON_COMMAND_EX(ID_TEST_FILTERWINDOW, OnBarCheck)
	ON_UPDATE_COMMAND_UI(ID_TEST_FIELDCHOOSER, OnUpdateControlBarMenu)
	ON_UPDATE_COMMAND_UI(ID_TEST_FILTERWINDOW, OnUpdateControlBarMenu)
	//}}AFX_MSG_MAP

#if defined(_XTP_INCLUDE_COMMANDBARS) && defined(XTP_INCLUDE_CONTROLS)
	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
#endif

#ifdef _XTP_INCLUDE_DOCKINGPANE
	ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify)
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
#ifdef _XTP_INCLUDE_DOCKINGPANE
: m_pFolderView(NULL)
#endif
{
#if defined(_XTP_INCLUDE_SKINFRAMEWORK) && !defined(_XTP_EXCLUDE_SKINFRAMEWORK)
	XTPSkinManager()->SetAutoApplyNewWindows(TRUE);
#endif
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

#ifndef _XTP_INCLUDE_COMMANDBARS

	if (!m_wndToolBar.Create(this, TBSTYLE_FLAT| WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
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

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


#else

	if (!m_wndStatusBar.Create(this) ||
		 !m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!InitCommandBars())
		return -1;

	CXTPCommandBars* pCommandBars = GetCommandBars();

	pCommandBars->SetMenu(_T("Menu Bar"), IDR_MAINFRAME);

	CXTPToolBar *pStandardBar = pCommandBars->Add(_T("Standard"), xtpBarTop);
	if (!pStandardBar || !pStandardBar->LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	SetTheme(xtpThemeOffice2013, xtpIniOffice2016OutlookColorful);
	pCommandBars->GetPaintManager()->m_bAutoResizeIcons = TRUE;
	pCommandBars->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE, FALSE);

	// Load the previous state for command bars.
	LoadCommandBars(_T("CommandBars"));

#endif

	EnableDocking(CBRS_ALIGN_ANY);

	// Initialize dialog bar m_wndFieldChooser
	if (!m_wndFieldChooser.Create(this, IDD_FIELDCHOOSER,
		CBRS_LEFT|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_HIDE_INPLACE, ID_TEST_FIELDCHOOSER))
		return -1;      // fail to create

	// Initialize dialog bar m_wndFilterEdit
	if (!m_wndFilterEdit.Create(this, IDD_FILTEREDIT,
		CBRS_LEFT|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_HIDE_INPLACE, ID_TEST_FILTERWINDOW))
		return -1;      // fail to create

	// docking for field chooser
	m_wndFieldChooser.EnableDocking(0);
	m_wndFieldChooser.SetWindowText(_T("Field Chooser"));

	ShowControlBar(&m_wndFieldChooser, FALSE, FALSE);
	FloatControlBar(&m_wndFieldChooser, CPoint(100, GetSystemMetrics(SM_CYSCREEN) / 3));

	// docking for filter editing
	m_wndFilterEdit.EnableDocking(CBRS_ALIGN_TOP);
	m_wndFilterEdit.SetWindowText(_T("Filter text"));

	ShowControlBar(&m_wndFilterEdit, FALSE, FALSE);
	FloatControlBar(&m_wndFilterEdit, CPoint(400, GetSystemMetrics(SM_CYSCREEN) / 3));

// Docking Pane sample, remove && 0 to see the pane
#if defined(_XTP_INCLUDE_DOCKINGPANE) && 0 
	m_paneManager.InstallDockingPanes(this);
	m_paneManager.SetTheme(xtpPaneThemeOffice2013);

	m_paneManager.SetFloatingFrameCaption(_T("Panes"));
	m_paneManager.SetStickyFloatingFrames(TRUE);
	m_paneManager.SetThemedFloatingFrames(TRUE);

	m_paneManager.SetSideDockingMargin(CRect(2, 2, 2, 2));
	m_paneManager.EnableSideDocking();

	m_paneManager.EnableKeyboardNavigate();

	CXTPDockingPane *pPaneFolders = m_paneManager.CreatePane(IDR_PANE_FOLDER, CRect(0, 0, 200, 150), xtpPaneDockLeft);
#endif

	return 0;
}

#if defined(_XTP_INCLUDE_COMMANDBARS) && defined(_XTP_INCLUDE_CONTROLS)

void CMainFrame::OnCustomize()
{
	// Get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if(pCommandBars != NULL)
	{
		// Instantiate the customize dialog object.
		CXTPCustomizeSheet dlg(pCommandBars);

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

		// Display the dialog.
		dlg.DoModal();
	}
}

#endif

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.lpszClass = _T("XTPMainFrame");
	CXTPDrawHelpers::RegisterWndClass(AfxGetInstanceHandle(), cs.lpszClass, 
		CS_DBLCLKS, AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	cs.style |= WS_CLIPCHILDREN|WS_CLIPSIBLINGS;
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

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

#ifdef _XTP_INCLUDE_DOCKINGPANE

LRESULT CMainFrame::OnDockingPaneNotify(WPARAM wParam, LPARAM lParam)
{
	BOOL bHandled = FALSE;
#if 0
	if (XTP_DPN_SHOWWINDOW == wParam)
	{
		bHandled = TRUE;

		CXTPDockingPane *pPane = reinterpret_cast<CXTPDockingPane*>(lParam);

		if (!pPane->IsValid())
		{
			if (NULL == m_pFolderView)
			{
				m_pFolderView = DYNAMIC_DOWNCAST(CFolderView,
					pPane->AttachView(this, RUNTIME_CLASS(CFolderView)));
			}
			else
			{
				pPane->Attach(m_pFolderView->GetParent());
			}
		}
	}
#endif
	return bHandled;
}

#endif

void CMainFrame::SetTheme(XTPPaintTheme paintTheme, LPCTSTR lpszINI /*=NULL*/)
{
#ifdef _XTP_INCLUDE_COMMANDBARS
	EnableFrameTheme(FALSE);
#endif

	XTPThemeDLL()->SetHandle(lpszINI);
	
#ifdef _XTP_INCLUDE_COMMANDBARS

	switch(paintTheme)
	{
	case xtpThemeOffice2013:
	case xtpThemeVisualStudio2015:
		m_bAllowDwm = FALSE;
		break;
	default:
		m_bAllowDwm = TRUE;
		break;
	}

	CXTPCommandBars* pCommandBars = GetCommandBars();
	if (pCommandBars != NULL)
	{
		pCommandBars->GetImageManager()->RemoveAll();

		CString strINI = lpszINI;
		pCommandBars->SetAllCaps((strINI.Find(_T("2013")) != -1) || (strINI.Find(_T("2015")) != -1));

		UINT uiSystemMenu[] = {ID_FILE_NEW,ID_FILE_OPEN,ID_FILE_SAVE,ID_EDIT_CUT,ID_EDIT_COPY,ID_EDIT_PASTE,ID_FILE_PRINT,ID_APP_ABOUT}; 
		UINT uiMainFrameIcons = IDR_MAINFRAME;

		switch(paintTheme)
		{
			case xtpThemeOffice2013:
				uiMainFrameIcons = IDR_MAINFRAME2013_CB_16;
				pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME2013_CB_24, uiSystemMenu, _countof(uiSystemMenu), CSize(24, 24));
				pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME2013_CB_32, uiSystemMenu, _countof(uiSystemMenu), CSize(32, 32));
				pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME2013_CB_40, uiSystemMenu, _countof(uiSystemMenu), CSize(40, 40));
				pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME2013_CB_48, uiSystemMenu, _countof(uiSystemMenu), CSize(48, 48));
				pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME2013_CB_64, uiSystemMenu, _countof(uiSystemMenu), CSize(64, 64));
				break;
			case xtpThemeVisualStudio2015:
				{
					if (XTPResourceImages()->m_strIniFileName == xtpIniVisualStudio2015Dark)
					{
						uiMainFrameIcons = IDR_MAINFRAMEVS2015DARK_CB_16;
						pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAMEVS2015DARK_CB_24, uiSystemMenu, _countof(uiSystemMenu), CSize(24, 24));
						pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAMEVS2015DARK_CB_32, uiSystemMenu, _countof(uiSystemMenu), CSize(32, 32));
						pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAMEVS2015DARK_CB_40, uiSystemMenu, _countof(uiSystemMenu), CSize(40, 40));
						pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAMEVS2015DARK_CB_48, uiSystemMenu, _countof(uiSystemMenu), CSize(48, 48));
						pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAMEVS2015DARK_CB_64, uiSystemMenu, _countof(uiSystemMenu), CSize(64, 64));
					}
					else if (XTPResourceImages()->m_strIniFileName == xtpIniVisualStudio2015Light)
					{
						uiMainFrameIcons = IDR_MAINFRAMEVS2015LIGHT_CB_16;
						pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAMEVS2015LIGHT_CB_24, uiSystemMenu, _countof(uiSystemMenu), CSize(24, 24));
						pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAMEVS2015LIGHT_CB_32, uiSystemMenu, _countof(uiSystemMenu), CSize(32, 32));
						pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAMEVS2015LIGHT_CB_40, uiSystemMenu, _countof(uiSystemMenu), CSize(40, 40));
						pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAMEVS2015LIGHT_CB_48, uiSystemMenu, _countof(uiSystemMenu), CSize(48, 48));
						pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAMEVS2015LIGHT_CB_64, uiSystemMenu, _countof(uiSystemMenu), CSize(64, 64));
					}
					else
					{
						uiMainFrameIcons = IDR_MAINFRAMEVS2015BLUE_CB_16;
						pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAMEVS2015BLUE_CB_24, uiSystemMenu, _countof(uiSystemMenu), CSize(24, 24));
						pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAMEVS2015BLUE_CB_32, uiSystemMenu, _countof(uiSystemMenu), CSize(32, 32));
						pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAMEVS2015BLUE_CB_40, uiSystemMenu, _countof(uiSystemMenu), CSize(40, 40));
						pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAMEVS2015BLUE_CB_48, uiSystemMenu, _countof(uiSystemMenu), CSize(48, 48));
						pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAMEVS2015BLUE_CB_64, uiSystemMenu, _countof(uiSystemMenu), CSize(64, 64));
					}
				}
				break;
			default:
				uiMainFrameIcons = IDR_MAINFRAME;			
				break;
		}

		pCommandBars->GetImageManager()->SetIcons(uiMainFrameIcons, uiSystemMenu, _countof(uiSystemMenu), CSize(16, 16));

		if (lpszINI != NULL)
		{
			CXTPPaintManager::SetTheme(paintTheme);
			EnableFrameTheme(pCommandBars);
		}
		else
		{
			CXTPPaintManager::SetTheme(paintTheme);
			EnableFrameTheme(NULL);
		}

		switch(paintTheme)
		{
			case xtpThemeOffice2013:
			case xtpThemeVisualStudio2015:
			{
				for (int i=0; i < pCommandBars->GetCount(); i++)
				{
					CXTPToolBar *pToolBar = pCommandBars->GetAt(i);
					pToolBar->SetFlags(xtpFlagAlignTop, xtpFlagAlignBottom | xtpFlagAlignLeft | xtpFlagAlignRight | xtpFlagFloating);

					if (xtpBarTypeMenuBar == pToolBar->GetType())
					{
						pToolBar->SetShowGripper(FALSE);
					}
					else
					{
						pToolBar->SetShowGripper(TRUE);
					}
				}

				SetFrameIcon(CSize(20,20));
			}
			break;

			default:
				for (int i=0; i<pCommandBars->GetCount(); i++)
				{
					CXTPToolBar *pToolBar = pCommandBars->GetAt(i);
					pToolBar->SetFlags(xtpFlagAlignTop | xtpFlagAlignBottom | xtpFlagAlignLeft | xtpFlagAlignRight | xtpFlagFloating, 0);
					pToolBar->SetShowGripper(TRUE);
				}

				SetFrameIcon(CSize(16,16));
			break;
		}		

		pCommandBars->GetPaintManager()->m_bAutoResizeIcons = TRUE;
		pCommandBars->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE, paintTheme != xtpThemeOffice2013 && paintTheme != xtpThemeVisualStudio2015);
		pCommandBars->GetPaintManager()->RefreshMetrics();
		pCommandBars->RedrawCommandBars();
	}
#else
	UNREFERENCED_PARAMETER(paintTheme);
#endif
}

#ifdef _XTP_INCLUDE_COMMANDBARS

BOOL CMainFrame::SetFrameIcon(CSize szIcon)
{
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if (!pCommandBars)
		return FALSE;

	CXTPPaintManager* pPaintManager = pCommandBars->GetPaintManager();
	if (!pPaintManager)
		return FALSE;

	CXTPFramePaintManager* pFramePaintManager = pPaintManager->GetFramePaintManager();
	if (!pFramePaintManager)
		return FALSE;

	HICON hIcon = NULL;
				
	hIcon = (HICON)::LoadImage(theApp.m_hInstance,
		MAKEINTRESOURCE(IDR_MAINFRAME), IMAGE_ICON, szIcon.cx, szIcon.cy, LR_SHARED);
	
	if (hIcon)
	{
		pFramePaintManager->SetIcon(hIcon, szIcon);
	}
	
	return TRUE;
}

#endif
