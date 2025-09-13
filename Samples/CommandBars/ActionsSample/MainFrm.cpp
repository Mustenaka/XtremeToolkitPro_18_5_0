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
#include "ActionsSample.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_MENUPOPUP_FILE 2000
#define ID_MENUPOPUP_ABOUT 2004
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
	ON_UPDATE_COMMAND_UI_RANGE(ID_MENUPOPUP_FILE, ID_MENUPOPUP_ABOUT, OnUpdatePopupMenu)
	
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
	//XTPResourceImages()->SetHandle(AfxGetInstanceHandle(), _T("OFFICE2010SILVER.INI"));
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	

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

	// Get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if(pCommandBars == NULL)
	{
		TRACE0("Failed to create command bars object.\n");
		return -1;      // fail to create
	}

	EnableActions();

	// Add the menu bar
	CXTPToolBar* pMenuBar = pCommandBars->SetMenu(
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
	pToolBar->EnableAnimation();

	CXTPDialogBar* pBar = (CXTPDialogBar*)pCommandBars->Add(_T("Actions"), xtpBarRight, RUNTIME_CLASS(CXTPDialogBar));
	pBar->SetBarID(200);
	pBar->EnableDocking(xtpFlagAlignLeft | xtpFlagAlignRight | xtpFlagFloating | xtpFlagStretched);
	pBar->ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS);

	m_wndActions.Create(CDialogActions::IDD, pBar);
	m_wndActions.ShowWindow(SW_SHOW);

	CXTPClientRect rcActions(m_wndActions);
	pBar->SetWidth(rcActions.Width());
	pBar->SetChild(&m_wndActions);

	SetTheme(xtpThemeOffice2013, theApp.m_hModule2013, _T("OFFICE2013WHITE.INI"));
	
	//pCommandBars->EnableToolbarComposition();

	LoadCommandBars(_T("CommandBars"));

	return 0;
}


void CMainFrame::EnableActions()
{
	CXTPCommandBars* pCommandBars = GetCommandBars();
	pCommandBars->EnableActions();

	// Optional:
	// Add standard actions, if you going to localize them.
	pCommandBars->GetActions()->Add(XTP_ID_CUSTOMIZE);
	pCommandBars->GetActions()->Add(XTP_ID_CUSTOMIZE_RESET);
	pCommandBars->GetActions()->Add(XTP_ID_CUSTOMIZE_ADDORREMOVE);
	pCommandBars->GetActions()->Add(XTP_ID_TOOLBAR_EXPAND);
	pCommandBars->GetActions()->Add(XTP_ID_TOOLBAR_HIDE);
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



void CMainFrame::OnCustomize()
{
	// Get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if (pCommandBars == NULL)
		return;

	// Instantiate the customize dialog.
	CXTPCustomizeSheet dlg(pCommandBars);

	// Add the options page to the customize dialog.
	CXTPCustomizeOptionsPage pageOptions(&dlg);
	dlg.AddPage(&pageOptions);

	// Add the commands page to the customize dialog.
	CXTPCustomizeCommandsPage* pPageCommands = dlg.GetCommandsPage();
	pPageCommands->AddCategories(IDR_MAINFRAME, TRUE);

	// Initialize the commands page page.
	pPageCommands->InsertAllCommandsCategory();
	pPageCommands->InsertBuiltInMenus(IDR_MAINFRAME);
	pPageCommands->InsertNewMenuCategory();

	// Display the customize dialog.
	dlg.DoModal();
}

void CMainFrame::OnClose()
{
	SaveCommandBars(_T("CommandBars"));

	CXTPFrameWnd::OnClose();
}

void CMainFrame::OnUpdatePopupMenu(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(1);
}

void CMainFrame::SetTheme(XTPPaintTheme paintTheme, HMODULE hModule/*=NULL*/, LPCTSTR lpszINI/*=NULL*/)
{
#ifdef _XTP_INCLUDE_COMMANDBARS

	switch(paintTheme)
	{
		case xtpThemeVisualStudio2012Dark:
		case xtpThemeVisualStudio2012Light:
		case xtpThemeVisualStudio2015:
		case xtpThemeOffice2013:
			m_bAllowDwm = FALSE;
			break;
		default:
			m_bAllowDwm = TRUE;
			break;
	}

	EnableFrameTheme(FALSE);

	CXTPCommandBars* pCommandBars = GetCommandBars();
	if (pCommandBars != NULL)
	{
		pCommandBars->GetImageManager()->RemoveAll();

		UINT uiSystemMenu[] = {ID_FILE_NEW,ID_FILE_OPEN,ID_FILE_SAVE,ID_EDIT_CUT,ID_EDIT_COPY,ID_EDIT_PASTE,ID_FILE_PRINT,ID_APP_ABOUT,0,0,
							   ID_CHAR_BOLD,ID_CHAR_ITALIC,ID_CHAR_UNDERLINE,ID_PARA_LEFT,ID_PARA_CENTER,ID_PARA_RIGHT,0};
		UINT uiMainFrameIcons = IDR_MAINFRAME;

		switch(paintTheme)
		{
			case xtpThemeVisualStudio2012Dark:
				uiMainFrameIcons = IDR_MAINFRAME2012DARK_CB;
				break;
			case xtpThemeVisualStudio2012Light:
				uiMainFrameIcons = IDR_MAINFRAME2012LIGHT_CB;
				break;
			case xtpThemeOffice2013:
				uiMainFrameIcons = IDR_MAINFRAME2013_CB_16;
				pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME2013_CB_24, uiSystemMenu, _countof(uiSystemMenu), CSize(24, 24));
				pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME2013_CB_32, uiSystemMenu, _countof(uiSystemMenu), CSize(32, 32));
				pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME2013_CB_40, uiSystemMenu, _countof(uiSystemMenu), CSize(40, 40));
				pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME2013_CB_48, uiSystemMenu, _countof(uiSystemMenu), CSize(48, 48));
				pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME2013_CB_64, uiSystemMenu, _countof(uiSystemMenu), CSize(64, 64));
				break;
			case xtpThemeVisualStudio2015:
				if (NULL != lpszINI)
				{
					if (0 == _tcscmp(lpszINI, xtpIniVisualStudio2015Light)
						|| 0 == _tcscmp(lpszINI, xtpIniVisualStudio2015Light))
					{
						uiMainFrameIcons = IDR_MAINFRAME2012LIGHT_CB;
					}
					else if (0 == _tcscmp(lpszINI, xtpIniVisualStudio2015Dark))
					{
						uiMainFrameIcons = IDR_MAINFRAME2012DARK_CB;
					}
				}
				break;
		}

		// Update tooltip styles.
		CXTPToolTipContext* pToolTipContext = m_wndStatusBar.GetToolTipContext();
		if(NULL != pToolTipContext)
		{
			pToolTipContext->SetStyle(GetToolTipStyle());
		}

		pToolTipContext = GetCommandBars()->GetToolTipContext();
		if(NULL != pToolTipContext)
		{
			pToolTipContext->SetStyle(GetToolTipStyle());
		}

		pCommandBars->GetImageManager()->SetIcons(uiMainFrameIcons, uiSystemMenu, _countof(uiSystemMenu), CSize(16, 16)); 

		if (hModule != NULL && lpszINI != NULL)
		{
			XTPResourceImages()->SetHandle(hModule, lpszINI);
			XTPPaintManager()->SetTheme(paintTheme);
		}
		else
		{
			XTPPaintManager()->SetTheme(paintTheme);
		}

		switch(paintTheme)
		{
			case xtpThemeOffice2013:
			case xtpThemeResource:
			case xtpThemeRibbon:
			case xtpThemeVisualStudio2012:
			case xtpThemeVisualStudio2012Light:
			case xtpThemeVisualStudio2012Dark:
			case xtpThemeVisualStudio2015:
				CXTPCommandBarsFrameHook::m_bAllowDwm = FALSE;
				GetCommandBars()->EnableFrameTheme(TRUE);
				break;

			default:
				CXTPCommandBarsFrameHook::m_bAllowDwm = TRUE;
				GetCommandBars()->EnableFrameTheme(NULL);
				break;
		}

		switch(paintTheme)
		{
			case xtpThemeVisualStudio2012Dark:
			case xtpThemeVisualStudio2012Light:
			case xtpThemeOffice2013:
			case xtpThemeVisualStudio2015:
			{
				pCommandBars->SetAllCaps(TRUE);
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

			}
			break;

			default:
				pCommandBars->SetAllCaps(FALSE);
				for (int i=0; i<pCommandBars->GetCount(); i++)
				{
					CXTPToolBar *pToolBar = pCommandBars->GetAt(i);
					pToolBar->SetFlags(xtpFlagAlignTop | xtpFlagAlignBottom | xtpFlagAlignLeft | xtpFlagAlignRight | xtpFlagFloating, 0);
					pToolBar->SetShowGripper(TRUE);
				}

			break;
		}
		
		switch(paintTheme)
		{
			case xtpThemeVisualStudio2012Dark:
				SetFrameIcon(IDI_WHITE, CSize(20,20));
				break;

			case xtpThemeVisualStudio2012Light:
				SetFrameIcon(IDI_BLACK, CSize(20,20));
				break;

			case xtpThemeVisualStudio2015:
				if (NULL != lpszINI)
				{
					if (0 == _tcscmp(lpszINI, xtpIniVisualStudio2015Light)
						|| 0 == _tcscmp(lpszINI, xtpIniVisualStudio2015Light))
					{
						SetFrameIcon(IDI_BLACK, CSize(20, 20));
					}
					else if (0 == _tcscmp(lpszINI, xtpIniVisualStudio2015Dark))
					{
						SetFrameIcon(IDI_WHITE, CSize(20, 20));
					}
				}
				break;

			case xtpThemeOffice2013:
				SetFrameIcon(IDR_MAINFRAME, CSize(20,20));
				break;

			default:
				SetFrameIcon(IDR_MAINFRAME, CSize(16,16));
				break;
		}

		pCommandBars->GetPaintManager()->m_bAutoResizeIcons = TRUE;
		pCommandBars->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE, paintTheme != xtpThemeOffice2013);
		pCommandBars->GetPaintManager()->RefreshMetrics();
		pCommandBars->RedrawCommandBars();
	}
#else
	UNREFERENCED_PARAMETER(paintTheme);

	if (hModule != NULL && lpszINI != NULL)
	{
		XTPResourceImages()->SetHandle(hModule, lpszINI);
	}
#endif
}

#ifdef _XTP_INCLUDE_COMMANDBARS

BOOL CMainFrame::SetFrameIcon(UINT nID, CSize szIcon)
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
				
	if (nID > 0)
	{
		hIcon = (HICON)::LoadImage(theApp.m_hInstance,
			MAKEINTRESOURCE(nID), IMAGE_ICON, szIcon.cx, szIcon.cy, LR_SHARED);
	}
	
	pFramePaintManager->SetIcon(hIcon, szIcon);

	return TRUE;
}

XTPToolTipStyle CMainFrame::GetToolTipStyle() const
{
	XTPToolTipStyle style;

	switch(theApp.m_theme)
	{
		case CActionsSampleApp::themeOffice2007Aqua:
		case CActionsSampleApp::themeOffice2007Black:
		case CActionsSampleApp::themeOffice2007Blue:
		case CActionsSampleApp::themeOffice2007Silver:
			style = xtpToolTipOffice2007;
			break;

		case CActionsSampleApp::themeOffice2010Black:
		case CActionsSampleApp::themeOffice2010Blue:
		case CActionsSampleApp::themeOffice2010Silver:
			style = xtpToolTipOffice;
			break;

		case CActionsSampleApp::themeWindows7:
			style = xtpToolTipLuna;
			break;

		case CActionsSampleApp::themeOffice2013Word:
		case CActionsSampleApp::themeOffice2013Excel:
		case CActionsSampleApp::themeOffice2013Access:
		case CActionsSampleApp::themeOffice2013Powerpoint:
		case CActionsSampleApp::themeOffice2013OneNote:
		case CActionsSampleApp::themeOffice2013Outlook:
			style = xtpToolTipOffice2013;
			break;

		default:
			style = xtpToolTipStandard;
			break;
	}

	return style;
}

#endif

