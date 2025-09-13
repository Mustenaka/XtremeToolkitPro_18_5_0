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
#include "RibbonMDISample.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_FULLSCREEN, OnViewFullscreen)
	ON_COMMAND(ID_VIEW_NORMAL, OnViewNormal)
	ON_UPDATE_COMMAND_UI(ID_VIEW_NORMAL, OnUpdateViewNormal)
	ON_COMMAND(ID_WINDOW_TILE_VERT, OnWindowTileV)
	ON_COMMAND(ID_WINDOW_CASCADE, OnWindowCascade)
	ON_COMMAND(ID_WINDOW_TILE_HORZ, OnWindowTileH)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_SWITCH, OnUpdateWindowSwitch)

	ON_COMMAND(ID_VIEW_WORKSPACE, OnViewWorkspace)
	ON_UPDATE_COMMAND_UI(ID_VIEW_WORKSPACE, OnUpdateViewWorkspace)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(XTP_ID_RIBBONCONTROLTAB, OnUpdateRibbonTab)

	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
	ON_COMMAND(XTP_ID_RIBBONCUSTOMIZE, OnCustomizeQuickAccess)

	ON_UPDATE_COMMAND_UI(ID_OPTIONS_RIGHTTOLEFT, OnUpdateOptionsRighttoleft)
	ON_COMMAND(ID_OPTIONS_RIGHTTOLEFT, OnOptionsRightToLeft)

	ON_COMMAND(ID_OPTIONS_FRAMETHEME, OnFrameTheme)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FRAMETHEME, OnUpdateFrameTheme)

	// Styles
	ON_COMMAND_RANGE(ID_OPTIONS_STYLE_OFFICE2007BLUE, ID_OPTIONS_STYLE_WINDOWS7SCENIC, OnOptionsStyle)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OPTIONS_STYLE_OFFICE2007BLUE, ID_OPTIONS_STYLE_WINDOWS7SCENIC,  OnUpdateOptionsStyle)

	// Font
	ON_COMMAND_RANGE(ID_OPTIONS_FONT_SYSTEM, ID_OPTIONS_FONT_EXTRALARGE, OnOptionsFont)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OPTIONS_FONT_SYSTEM, ID_OPTIONS_FONT_EXTRALARGE, OnUpdateOptionsFont)
	
	ON_COMMAND(ID_OPTIONS_FONT_AUTORESIZEICONS, OnAutoResizeIcons)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FONT_AUTORESIZEICONS, OnUpdateAutoResizeIcons)

	ON_COMMAND(ID_OPTIONS_FONT_DPI_ICON_SCALING, OnDpiIconsScalling)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FONT_DPI_ICON_SCALING, OnUpdateDpiIconsScalling)


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
	: m_bCreated(FALSE)
{
	m_nRibbonStyle = ID_OPTIONS_STYLE_OFFICE2016WORD;	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	
	if (!InitCommandBars())
		return -1;

	CXTPCommandBars* pCommandBars = GetCommandBars();

	XTPPaintManager()->SetTheme(xtpThemeRibbon);
	
	m_wndStatusBar.SetDrawDisabledText(FALSE);
	m_wndStatusBar.SetCommandBars(pCommandBars);
	m_wndStatusBar.GetStatusBarCtrl().SetMinHeight(XTP_DPI_Y(22));
	m_wndStatusBar.GetPane(0)->SetMargins(XTP_DPI_X(8), XTP_DPI_Y(1), XTP_DPI_X(2), XTP_DPI_Y(1));

	//////////////////////////////////////////////////////////////////////////	
	// IMPORTANT:
	// Ribbon bitmaps resources by default located in application executable. 
	//
	// You also can specify handle to find ribbon resources:
	//((CXTPOffice2007Theme*)XTPPaintManager())->SetImageHandle(hHandle);

	//HMODULE hModule = LoadLibrary(m_csStylesPath + _T("Office2007.dll"));
	//((CXTPOffice2007Theme*)pCommandBars->GetPaintManager())->SetImageHandle(hModule);

	CXTPToolTipContext* pToolTipContext = GetCommandBars()->GetToolTipContext();
	pToolTipContext->SetStyle(GetToolTipStyle());
	pToolTipContext->ShowTitleAndDescription();
	pToolTipContext->SetMargin(XTP_DPI(CRect(2, 2, 2, 2)));
	pToolTipContext->SetMaxTipWidth(XTP_DPI_X(180));
	pToolTipContext->SetFont(pCommandBars->GetPaintManager()->GetIconFont());
	pToolTipContext->ShowImage(TRUE);
	pToolTipContext->EnableImageDPIScaling(FALSE);

	pCommandBars->GetCommandBarsOptions()->ShowKeyboardCues(xtpKeyboardCuesShowWindowsDefault);
	pCommandBars->GetCommandBarsOptions()->bToolBarAccelTips = TRUE;

	pCommandBars->GetShortcutManager()->SetAccelerators(IDR_MAINFRAME);

	LoadIcons();

	if (!CreateRibbonBar())
	{
		TRACE0("Failed to create ribbon\n");
		return -1;
	}

	m_wndClient.Attach(this, FALSE);
	m_wndClient.GetToolTipContext()->SetStyle(xtpToolTipResource);

	m_bShowWorkspace = TRUE;

	//LoadCommandBars(_T("CommandBars"));

	OnOptionsStyle(ID_OPTIONS_STYLE_OFFICE2016WORD);
	
	// Enable DPI-awareness for icons
	pCommandBars->GetPaintManager()->m_bAutoResizeIcons = TRUE;

	m_bCreated = TRUE;

	return 0;
}

void CMainFrame::CreateBackstage()
{
	CXTPRibbonBar* pRibbonBar = DYNAMIC_DOWNCAST(CXTPRibbonBar, GetCommandBars()->GetMenuBar());
	ASSERT (pRibbonBar);

	CXTPRibbonControlSystemButton* pButton = pRibbonBar->GetSystemButton();

	CXTPRibbonBackstageView* pView = CXTPRibbonBackstageView::CreateBackstageView(GetCommandBars());

	pView->AddCommand(ID_FILE_SAVE);
	pView->AddCommand(ID_FILE_OPEN);
	pView->AddCommand(ID_FILE_PRINT_SETUP);
	pView->AddCommand(ID_FILE_PRINT_PREVIEW);
	pView->AddCommand(ID_FILE_PRINT);

	pView->AddCommand(ID_APP_EXIT);

	pButton->SetCommandBar(pView);
	
	pView->InternalRelease();
}

//#define CREATE_FROM_XML

BOOL CMainFrame::CreateRibbonBar()
{
	CXTPCommandBars* pCommandBars = GetCommandBars();

	CMenu menu;
	menu.Attach(::GetMenu(m_hWnd));
	SetMenu(NULL);

#ifndef CREATE_FROM_XML
	pRibbonBar = (CXTPRibbonBar*)pCommandBars->Add(_T("The Ribbon"), xtpBarTop, RUNTIME_CLASS(CXTPRibbonBar));
	if (!pRibbonBar)
	{
		return FALSE;
	}
	pRibbonBar->EnableDocking(0);

	CXTPControlPopup* pControlFile = (CXTPControlPopup*)pRibbonBar->AddSystemButton(ID_MENU_FILE);
	pControlFile->SetIconId(IDB_GEAR);

	CreateBackstage();

	CXTPRibbonTab* pTabHome = pRibbonBar->AddTab(ID_TAB_HOME);

	CXTPRibbonGroup* pGroupFile = pTabHome->AddGroup(ID_GROUP_FILE);
	pGroupFile->Add(xtpControlButton, ID_FILE_NEW);
	pGroupFile->Add(xtpControlButton, ID_FILE_OPEN);
	pGroupFile->Add(xtpControlButton, ID_FILE_CLOSE);
	CXTPControlPopup* pControlSave = (CXTPControlPopup*)pGroupFile->Add(xtpControlSplitButtonPopup, ID_FILE_SAVE);
	pControlSave->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_FILE_SAVE);
	pControlSave->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_FILE_SAVE_AS);

	CXTPControlPopup* pControlPrint = (CXTPControlPopup*)pGroupFile->Add(xtpControlSplitButtonPopup, ID_FILE_PRINT);
	pControlPrint->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_FILE_PRINT);
	pControlPrint->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_FILE_PRINT_SETUP);
	pControlPrint->SetBeginGroup(TRUE);

	CXTPRibbonTab* pTabEdit = pRibbonBar->AddTab(ID_TAB_EDIT);

	CXTPRibbonGroup* pGroupClipborad = pTabEdit->AddGroup(ID_GROUP_CLIPBOARD);
	pGroupClipborad->ShowOptionButton();
	
	CXTPControlPopup* pControlPaste = (CXTPControlPopup*)pGroupClipborad->Add(xtpControlSplitButtonPopup, ID_EDIT_PASTE);
	pControlPaste->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_EDIT_PASTE);
	pControlPaste->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_EDIT_PASTE_SPECIAL);
	pGroupClipborad->Add(xtpControlButton, ID_EDIT_CUT);
	pGroupClipborad->Add(xtpControlButton, ID_EDIT_COPY);	
	pGroupClipborad->Add(xtpControlButton, ID_FORMAT_PAINTER);

	CXTPRibbonGroup* pGroupEditing = pTabEdit->AddGroup(ID_GROUP_EDITING);
	pGroupEditing->Add(xtpControlButton, ID_EDIT_FIND);
	pGroupEditing->Add(xtpControlButton, ID_EDIT_REPLACE);
	pGroupEditing->Add(xtpControlButton, ID_EDIT_GOTO);
	CXTPControlPopup* pControlSelect = (CXTPControlPopup*)pGroupEditing->Add(xtpControlPopup, ID_EDIT_SELECT);
	pControlSelect->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_EDIT_SELECT_ALL);
	pControlSelect->SetFlags(xtpFlagManualUpdate);
	
	CXTPRibbonTab* pTabView = pRibbonBar->AddTab(ID_TAB_VIEW);

	CXTPRibbonGroup* pGroupDocumentView = pTabView->AddGroup(ID_GROUP_DOCUMENTVIEWS);
	pGroupDocumentView->Add(xtpControlButton, ID_VIEW_NORMAL);
	pGroupDocumentView->Add(xtpControlButton, ID_FILE_PRINT_PREVIEW);
	pGroupDocumentView->Add(xtpControlButton, ID_VIEW_FULLSCREEN);

	CXTPRibbonGroup* pGroupShowHide = pTabView->AddGroup(ID_GROUP_SHOWHIDE);
	pGroupShowHide->Add(xtpControlCheckBox, ID_VIEW_STATUS_BAR);
	pGroupShowHide->Add(xtpControlCheckBox, ID_VIEW_WORKSPACE);

	CXTPRibbonGroup* pGroupWindow = pTabView->AddGroup(ID_GROUP_WINDOW);
	pGroupWindow->Add(xtpControlButton, ID_WINDOW_NEW);
	pGroupWindow->Add(xtpControlButton, ID_WINDOW_TILE_VERT);
	pGroupWindow->Add(xtpControlButton, ID_WINDOW_CASCADE);
	pGroupWindow->Add(xtpControlButton, ID_WINDOW_TILE_HORZ);
	CXTPControlPopup* pControlSwitchWindows = (CXTPControlPopup*)pGroupWindow->Add(xtpControlPopup, ID_WINDOW_SWITCH);
	pControlSwitchWindows->GetCommandBar()->GetControls()->Add(xtpControlButton, XTP_ID_WINDOWLIST);


	CXTPControlPopup* pControlOptions = (CXTPControlPopup*)pRibbonBar->GetControls()->Add(xtpControlPopup, -1);
	pControlOptions->SetFlags(xtpFlagRightAlign);
	CMenu mnuOptions;
	mnuOptions.LoadMenu(IDR_MENU_OPTIONS);
	pControlOptions->SetCommandBar(mnuOptions.GetSubMenu(0));
	pControlOptions->SetCaption(_T("Options"));

	CXTPControl* pControlAbout = pRibbonBar->GetControls()->Add(xtpControlButton, ID_APP_ABOUT);
	pControlAbout->SetFlags(xtpFlagRightAlign);

	pRibbonBar->GetQuickAccessControls()->Add(xtpControlButton, ID_FILE_SAVE);
	pRibbonBar->GetQuickAccessControls()->Add(xtpControlButton, ID_EDIT_UNDO);
	pRibbonBar->GetQuickAccessControls()->Add(xtpControlButton, ID_FILE_PRINT);
	pRibbonBar->GetQuickAccessControls()->CreateOriginalControls();

#else
	CXTPPropExchangeXMLNode px(TRUE, 0, _T("Settings"));

	if (px.LoadFromResource(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_LAYOUT), RT_HTML))
	{
		CXTPPropExchangeSection pxCommandBars(px.GetSection(_T("CommandBars")));
		XTP_COMMANDBARS_PROPEXCHANGE_PARAM param; 
		param.bSerializeControls = TRUE;
		GetCommandBars()->DoPropExchange(&pxCommandBars, &param);
	}
	else
	{
		AfxMessageBox(_T("Can't load Layout"));
		return FALSE;
	}
	CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)GetCommandBars()->GetMenuBar();
	pRibbonBar->EnableCustomization(FALSE);

	pRibbonBar->GetQuickAccessControls()->SetOriginalControls(new CXTPOriginalControls());
	pRibbonBar->GetQuickAccessControls()->GetOriginalControls()->Add(xtpControlButton, ID_FILE_SAVE);
	pRibbonBar->GetQuickAccessControls()->GetOriginalControls()->Add(xtpControlButton, ID_EDIT_UNDO);
	pRibbonBar->GetQuickAccessControls()->GetOriginalControls()->Add(xtpControlButton, ID_FILE_PRINT);

#endif


	pRibbonBar->SetCloseable(FALSE);

	pRibbonBar->EnableFrameTheme();

	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
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
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnUpdateRibbonTab(CCmdUI* pCmdUI)
{
	CXTPRibbonControlTab* pControl = DYNAMIC_DOWNCAST(CXTPRibbonControlTab, CXTPControl::FromUI(pCmdUI));
	if (!pControl)
		return;

	CXTPRibbonTab* pTab = pControl->FindTab(ID_TAB_EDIT);
	if (!pTab)
		return;

	pTab->SetVisible(MDIGetActive() != NULL);
}

void CMainFrame::OnViewFullscreen() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnViewNormal() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnUpdateViewNormal(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(1);	
}

void CMainFrame::OnWindowTileV() 
{
	MDITile(MDITILE_VERTICAL);
}

void CMainFrame::OnWindowCascade() 
{
	MDICascade();
}

void CMainFrame::OnWindowTileH() 
{
	MDITile(MDITILE_HORIZONTAL);
}


void CMainFrame::OnUpdateWindowSwitch(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(MDIGetActive() != NULL ? TRUE : FALSE);
	
}

void CMainFrame::OnViewWorkspace()
{
	m_bShowWorkspace ^= 1;
	m_wndClient.ShowWorkspace(m_bShowWorkspace);
}

void CMainFrame::OnUpdateViewWorkspace(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bShowWorkspace);
}

void CMainFrame::OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState)
{
// Toggle CommandBars
	GetCommandBars()->OnSetPreviewMode(bPreview);

// Toggle Tab Client
	m_wndClient.ShowWorkspace(!bPreview);

	CMDIFrameWnd::OnSetPreviewMode(bPreview, pState);
}

void CMainFrame::OnClose() 
{	
/*	CXTPPropExchangeXMLNode px(FALSE, 0, _T("Settings"));

	if (px.OnBeforeExchange()) 
	{
		CXTPPropExchangeSection pxCommandBars(px.GetSection(_T("CommandBars")));
		XTP_COMMANDBARS_PROPEXCHANGE_PARAM param; 
		param.bSerializeControls = TRUE; 
		param.bSaveOriginalControls = FALSE;
		param.bSerializeOptions = TRUE;
		GetCommandBars()->DoPropExchange(&pxCommandBars, &param);

		px.SaveToFile(_T("C:\\save.xml"));
	}*/

	SaveCommandBars(_T("CommandBars"));

	
	CXTPMDIFrameWnd::OnClose();
}

void CMainFrame::ShowCustomizeDialog(int nSelectedPage)
{
	CXTPCustomizeSheet cs(GetCommandBars());

	CXTPRibbonCustomizeQuickAccessPage pageQuickAccess(&cs);
	cs.AddPage(&pageQuickAccess);
	pageQuickAccess.AddCategories(IDR_MAINFRAME);

	CXTPCustomizeKeyboardPage pageKeyboard(&cs);
	cs.AddPage(&pageKeyboard);
	pageKeyboard.AddCategories(IDR_MAINFRAME);

	CXTPCustomizeOptionsPage pageOptions(&cs);
	cs.AddPage(&pageOptions);

	CXTPCustomizeCommandsPage* pCommands = cs.GetCommandsPage();
	pCommands->AddCategories(IDR_MAINFRAME);

	cs.SetActivePage(nSelectedPage);

	cs.DoModal();
}

void CMainFrame::OnCustomize()
{
	ShowCustomizeDialog(0);
}

void CMainFrame::OnCustomizeQuickAccess()
{
	ShowCustomizeDialog(2);
}

void CMainFrame::OnOptionsRightToLeft() 
{
	if (GetExStyle() & WS_EX_LAYOUTRTL)
	{
		GetCommandBars()->SetLayoutRTL(FALSE);
		ModifyStyleEx(WS_EX_LAYOUTRTL, 0);
		m_wndClient.SetLayoutRTL(FALSE);
	}
	else
	{
		GetCommandBars()->SetLayoutRTL(TRUE);
		ModifyStyleEx(0, WS_EX_LAYOUTRTL);
		m_wndClient.SetLayoutRTL(TRUE);
	}	

}

void CMainFrame::OnUpdateOptionsRighttoleft(CCmdUI* pCmdUI) 
{
	if (XTPSystemVersion()->IsLayoutRTLSupported())
	{
		pCmdUI->SetCheck(GetExStyle() & WS_EX_LAYOUTRTL ? TRUE : FALSE);	
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CMainFrame::OnUpdateOptionsStyle(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nRibbonStyle ? 1 : 0);

}

void CMainFrame::OnOptionsStyle(UINT nStyle)
{
	m_nRibbonStyle = nStyle;

	GetCommandBars()->SetAllCaps(nStyle == ID_OPTIONS_STYLE_OFFICE2013WORD);
	GetCommandBars()->GetPaintManager()->RefreshMetrics();

	switch (nStyle)
	{
		case ID_OPTIONS_STYLE_OFFICE2007SYSTEM:

			SetCommandBarsTheme(xtpThemeOffice2007System, NULL, _T(""));

			GetCommandBars()->GetPaintManager()->GetIconsInfo()->bUseFadedIcons = FALSE;
			GetCommandBars()->GetPaintManager()->GetIconsInfo()->bIconsWithShadow = FALSE;
			GetCommandBars()->GetPaintManager()->GetIconsInfo()->bUseDisabledIcons = TRUE;

			if (XTPSystemVersion()->IsWinVistaOrGreater())
			{
				GetCommandBars()->GetPaintManager()->m_bUseOfficeFont = TRUE;
				GetCommandBars()->GetPaintManager()->m_strOfficeFont = _T("Segoe UI");
				GetCommandBars()->GetPaintManager()->SetFontHeight(XTP_DPI_Y(12));
			}

			break;

		// Office 2007
		case ID_OPTIONS_STYLE_OFFICE2007BLUE:
			SetCommandBarsTheme(xtpThemeRibbon, theApp.m_hModule2007, xtpIniOffice2007Blue);
			break;

		case ID_OPTIONS_STYLE_OFFICE2007SILVER:
			SetCommandBarsTheme(xtpThemeRibbon, theApp.m_hModule2007, xtpIniOffice2007Silver);
			break;
		
		case ID_OPTIONS_STYLE_OFFICE2007BLACK:
			SetCommandBarsTheme(xtpThemeRibbon, theApp.m_hModule2007, xtpIniOffice2007Black);
			break;

		case ID_OPTIONS_STYLE_OFFICE2007AQUA:
			SetCommandBarsTheme(xtpThemeRibbon, theApp.m_hModule2007, xtpIniOffice2007Aqua);
			break;

		// Office 2010 styles
		case ID_OPTIONS_STYLE_OFFICE2010BLUE:
			SetCommandBarsTheme(xtpThemeRibbon, theApp.m_hModule2010, xtpIniOffice2010Blue);
			break;

		case ID_OPTIONS_STYLE_OFFICE2010SILVER:
			SetCommandBarsTheme(xtpThemeRibbon, theApp.m_hModule2010, xtpIniOffice2010Silver);
			break;

		case ID_OPTIONS_STYLE_OFFICE2010BLACK:
			SetCommandBarsTheme(xtpThemeRibbon, theApp.m_hModule2010, xtpIniOffice2010Black);
			break;

		// Office 2013 styles
		case ID_OPTIONS_STYLE_OFFICE2013WORD:
			SetCommandBarsTheme(xtpThemeOffice2013, theApp.m_hModule2013, xtpIniOffice2013Word);
			break;

		case ID_OPTIONS_STYLE_OFFICE2016WORD:
			SetCommandBarsTheme(xtpThemeOffice2013, theApp.m_hModule2016, xtpIniOffice2016WordColorful);
			break;
			
		// Windows 7 styles
		case ID_OPTIONS_STYLE_WINDOWS7SCENIC:
			SetCommandBarsTheme(xtpThemeRibbon, theApp.m_hModuleWin7, xtpIniWindows7Blue);
			break;
	}

	if(m_bCreated)
	{
		UpdateMDIChildrenTheme();
	}

	CXTPRibbonBar *pRibbonBar = (CXTPRibbonBar*)GetCommandBars()->GetMenuBar();

	if ( nStyle >= ID_OPTIONS_STYLE_OFFICE2010BLUE)
	{
		pRibbonBar->GetSystemButton()->SetStyle(xtpButtonCaption);
		CreateBackstage();
	}
	else
	{
		pRibbonBar->GetSystemButton()->SetStyle(xtpButtonAutomatic);
		CreateSystemMenuPopup();
	}

	LoadIcons();

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

	GetCommandBars()->GetPaintManager()->m_bAutoResizeIcons = TRUE;
	BOOL bDPIIconsScalsing = nStyle != ID_OPTIONS_STYLE_OFFICE2013WORD && nStyle != ID_OPTIONS_STYLE_OFFICE2016WORD;
	GetCommandBars()->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE, bDPIIconsScalsing);

	GetCommandBars()->GetImageManager()->RefreshAll();
	GetCommandBars()->RedrawCommandBars();
	SendMessage(WM_NCPAINT);

	RedrawWindow(0, 0, RDW_ALLCHILDREN|RDW_INVALIDATE);
}

void CMainFrame::SetCommandBarsTheme(XTPPaintTheme paintTheme, HMODULE hModule/*=NULL*/, LPCTSTR lpszINI/*=NULL*/)
{
	if (lpszINI != NULL)
	{
		XTPThemeDLL()->SetHandle(lpszINI);
		XTPPaintManager()->SetTheme(paintTheme);
	}

	CXTPCommandBarsFrameHook::m_bAllowDwm = (XTPSystemVersion()->IsWin10OrGreater() ? FALSE
		: !(CXTPWinDwmWrapper().IsCompositionEnabled()
			&& (xtpThemeOffice2013 == paintTheme)));
}

XTPToolTipStyle CMainFrame::GetToolTipStyle() const
{
	XTPToolTipStyle style;

	switch(m_nRibbonStyle)
	{
		// Office 2007
		case ID_OPTIONS_STYLE_OFFICE2007BLUE:
		case ID_OPTIONS_STYLE_OFFICE2007SILVER:
		case ID_OPTIONS_STYLE_OFFICE2007BLACK:
		case ID_OPTIONS_STYLE_OFFICE2007AQUA:
			style = xtpToolTipOffice2007;
			break;

		// Office 2010 styles
		case ID_OPTIONS_STYLE_OFFICE2010BLUE:
		case ID_OPTIONS_STYLE_OFFICE2010SILVER:
		case ID_OPTIONS_STYLE_OFFICE2010BLACK:
			style = xtpToolTipOffice;
			break;

		case ID_OPTIONS_STYLE_OFFICE2013WORD:
		case ID_OPTIONS_STYLE_OFFICE2016WORD:
			style = xtpToolTipOffice;	//xtpToolTipOffice2013;
			break;

		// Windows styles
		case ID_OPTIONS_STYLE_WINDOWS7SCENIC:
			style = xtpToolTipLuna;
			break;

		default:
			style = xtpToolTipStandard;
			break;
	}

	return style;
}

void CMainFrame::CreateSystemMenuPopup()
{
	CXTPRibbonBar* pRibbonBar = DYNAMIC_DOWNCAST(CXTPRibbonBar, GetCommandBars()->GetMenuBar());
	ASSERT (pRibbonBar);
	
	
	CXTPRibbonControlSystemButton* pControlFile = pRibbonBar->GetSystemButton();

	CMenu menu;
	menu.LoadMenu(IDR_MAINFRAME);
	
	CXTPPopupBar* pCommandBar = new CXTPRibbonSystemPopupBar();
	pCommandBar->SetCommandBars(GetCommandBars());
	
	pControlFile->SetCommandBar(pCommandBar);
	pCommandBar->InternalRelease();


	pCommandBar->LoadMenu(menu.GetSubMenu(0));

	pCommandBar->SetIconSize(CSize(36, 36));
}

int nFonts[] = { 0, 11, 13, 16 };

void CMainFrame::OnOptionsFont(UINT nID)
{
	int nFontHeight = XTP_DPI_Y(nFonts[nID - ID_OPTIONS_FONT_SYSTEM]);

	CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)GetCommandBars()->GetAt(0);

	pRibbonBar->SetFontHeight(nFontHeight);

}

void CMainFrame::OnUpdateOptionsFont(CCmdUI* pCmdUI)
{
	int nFontHeight = XTP_DPI_Y(nFonts[pCmdUI->m_nID - ID_OPTIONS_FONT_SYSTEM]);

	CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)GetCommandBars()->GetAt(0);

	pCmdUI->SetCheck(pRibbonBar->GetFontHeight() == nFontHeight ? TRUE : FALSE);

}

void CMainFrame::OnFrameTheme()
{
	ShowWindow(SW_NORMAL);
	CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)GetCommandBars()->GetAt(0);

	CXTPWindowRect rc(this);
	rc.top += (pRibbonBar->IsFrameThemeEnabled() ? -1 : +1) * GetSystemMetrics(SM_CYCAPTION);
	MoveWindow(rc);
	
	pRibbonBar->EnableFrameTheme(!pRibbonBar->IsFrameThemeEnabled());

}

void CMainFrame::OnUpdateFrameTheme(CCmdUI* pCmdUI)
{
	CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)GetCommandBars()->GetAt(0);

	pCmdUI->SetCheck(pRibbonBar->IsFrameThemeEnabled() ? TRUE : FALSE);
}

void CMainFrame::LoadIcons()
{
	switch(m_nRibbonStyle)
	{
		// Office 2013 styles
		case ID_OPTIONS_STYLE_OFFICE2013WORD:
		case ID_OPTIONS_STYLE_OFFICE2016WORD:
			LoadOfficeIcons();
			break;

		default:
			LoadDefaultIcons();
			break;
	}
}

void CMainFrame::LoadDefaultIcons()
{
	CXTPCommandBars* pCommandBars = GetCommandBars();
	CXTPCommandBarsOptions* pOptions = pCommandBars->GetCommandBarsOptions();

	pCommandBars->GetImageManager()->RemoveAll();

	pCommandBars->GetImageManager()->SetIcons(IDR_SMALLICONS);
	pCommandBars->GetImageManager()->SetIcons(IDR_LARGEICONS);

	UINT uiGroupClipboard[] = {ID_EDIT_PASTE, ID_EDIT_CUT, ID_EDIT_COPY, ID_FORMAT_PAINTER};
	pCommandBars->GetImageManager()->SetIcons(ID_GROUP_CLIPBOARD, uiGroupClipboard, _countof(uiGroupClipboard), CSize(16, 16));

	UINT uiGroupFind[] = {ID_EDIT_FIND, ID_EDIT_REPLACE, ID_EDIT_GOTO, ID_EDIT_SELECT};
	pCommandBars->GetImageManager()->SetIcons(ID_GROUP_EDITING, uiGroupFind, _countof(uiGroupFind), CSize(16, 16));

	UINT uCommand = {IDB_GEAR};
	pCommandBars->GetImageManager()->SetIcons(IDB_GEAR, &uCommand, 1, CSize(0, 0), xtpImageNormal);
}

void CMainFrame::LoadOfficeIcons()
{
	CXTPCommandBars* pCommandBars = GetCommandBars();
	CXTPCommandBarsOptions* pOptions = pCommandBars->GetCommandBarsOptions();

	pCommandBars->GetImageManager()->RemoveAll();
	
	UINT uicons[] = {ID_EDIT_UNDO,ID_EDIT_PASTE,ID_EDIT_CUT,ID_EDIT_COPY,ID_FILE_OPEN
					,ID_EDIT_SELECT,ID_EDIT_REPLACE,ID_EDIT_FIND,ID_FORMAT_PAINTER,ID_APP_ABOUT
					,ID_FILE_SAVE,ID_FILE_PRINT,ID_EDIT_GOTO,ID_FILE_PRINT_PREVIEW,ID_FILE_NEW
					,ID_VIEW_NORMAL,ID_FILE_CLOSE,ID_WINDOW_NEW,ID_VIEW_FULLSCREEN,ID_WINDOW_TILE_VERT
					,ID_WINDOW_TILE_HORZ,ID_WINDOW_CASCADE,ID_WINDOW_SWITCH,ID_GROUP_SHOWHIDE,ID_FILE_PRINT_SETUP};
	
	pCommandBars->GetImageManager()->SetIcons(ID_OFFICE2013_16, uicons, _countof(uicons), CSize(16, 16));
	pCommandBars->GetImageManager()->SetIcons(ID_OFFICE2013_24, uicons, _countof(uicons), CSize(24, 24));
	pCommandBars->GetImageManager()->SetIcons(ID_OFFICE2013_32, uicons, _countof(uicons), CSize(32, 32));
	pCommandBars->GetImageManager()->SetIcons(ID_OFFICE2013_40, uicons, _countof(uicons), CSize(40, 40));
	pCommandBars->GetImageManager()->SetIcons(ID_OFFICE2013_48, uicons, _countof(uicons), CSize(48, 48));
	pCommandBars->GetImageManager()->SetIcons(ID_OFFICE2013_64, uicons, _countof(uicons), CSize(64, 64));

	//reuse icons
	ZeroMemory(uicons, _countof(uicons));
	
	uicons[15] = ID_GROUP_DOCUMENTVIEWS;	//ID_VIEW_NORMAL
	uicons[22] = ID_GROUP_WINDOW;			//ID_WINDOW_SWITCH

	pCommandBars->GetImageManager()->SetIcons(ID_OFFICE2013_16, uicons, _countof(uicons), CSize(16, 16));
	pCommandBars->GetImageManager()->SetIcons(ID_OFFICE2013_24, uicons, _countof(uicons), CSize(24, 24));
	pCommandBars->GetImageManager()->SetIcons(ID_OFFICE2013_32, uicons, _countof(uicons), CSize(32, 32));
	pCommandBars->GetImageManager()->SetIcons(ID_OFFICE2013_40, uicons, _countof(uicons), CSize(40, 40));
	pCommandBars->GetImageManager()->SetIcons(ID_OFFICE2013_48, uicons, _countof(uicons), CSize(48, 48));
	pCommandBars->GetImageManager()->SetIcons(ID_OFFICE2013_64, uicons, _countof(uicons), CSize(64, 64));
}

void CMainFrame::OnAutoResizeIcons()
{
	GetCommandBars()->GetPaintManager()->m_bAutoResizeIcons ^= 1;
	GetCommandBars()->RedrawCommandBars();
}

void CMainFrame::OnUpdateAutoResizeIcons(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetCommandBars()->GetPaintManager()->m_bAutoResizeIcons);
}

void CMainFrame::OnDpiIconsScalling()
{
	GetCommandBars()->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE, !GetCommandBars()->GetCommandBarsOptions()->GetToolbarsIconsScalling());
	GetCommandBars()->RedrawCommandBars();
}

void CMainFrame::OnUpdateDpiIconsScalling(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetCommandBars()->GetCommandBarsOptions()->GetToolbarsIconsScalling());
}
