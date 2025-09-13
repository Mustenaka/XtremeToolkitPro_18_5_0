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
#include "RibbonSample.h"

#include "MainFrm.h"
#include "Galleryitems.h"
#include "WorkspaceView.h"

#include "CustomizePageGeneral.h"
#include "CustomizePageQuickAccessToolbar.h"
#include "CustomizePageRibbon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CXTPFrameWnd)


BEGIN_MESSAGE_MAP(CMainFrame, CXTPFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_ANIMATION, OnUpdateOptionsAnimation)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_RIGHTTOLEFT, OnUpdateOptionsRighttoleft)

	ON_COMMAND(ID_OPTIONS_ANIMATION,   OnOptionsAnimation)
	ON_COMMAND(ID_OPTIONS_RIGHTTOLEFT, OnOptionsRightToLeft)

	// Styles
	ON_COMMAND(ID_OPTIONS_STYLE_OFFICE2013_LTGRAY, OnOptionsStyleOffice2013LtGray)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_STYLE_OFFICE2013_LTGRAY, OnUpdateOptionsStyleOffice2013LtGray)
	ON_COMMAND(ID_OPTIONS_STYLE_OFFICE2013_DKGRAY, OnOptionsStyleOffice2013DkGray)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_STYLE_OFFICE2013_DKGRAY, OnUpdateOptionsStyleOffice2013DkGray)
	ON_COMMAND(ID_OPTIONS_STYLE_VISUALSTUDIO2015_CLOSED, OnOptionsStyleVisualStudio2015Closed)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_STYLE_VISUALSTUDIO2015_CLOSED, OnUpdateOptionsStyleVisualStudio2015Closed)
	ON_COMMAND(ID_OPTIONS_STYLE_VISUALSTUDIO2015_OPEN, OnOptionsStyleVisualStudio2015Open)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_STYLE_VISUALSTUDIO2015_OPEN, OnUpdateOptionsStyleVisualStudio2015Open)
	ON_COMMAND(ID_OPTIONS_STYLE_VISUALSTUDIO2015_DEBUG, OnOptionsStyleVisualStudio2015Debug)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_STYLE_VISUALSTUDIO2015_DEBUG, OnUpdateOptionsStyleVisualStudio2015Debug)
	ON_COMMAND_RANGE(ID_OPTIONS_STYLE_OFFICE2007BLUE, ID_OPTIONS_STYLE_OFFICE2007SYSTEM, OnStyleOffice2007)
	ON_COMMAND_RANGE(ID_OPTIONS_STYLE_OFFICE2010BLUE, ID_OPTIONS_STYLE_OFFICE2010BLACK, OnStyleOffice2010)
	ON_COMMAND_RANGE(ID_OPTIONS_STYLE_OFFICE2013ACCESS, ID_OPTIONS_STYLE_OFFICE2013WORD, OnOptionsStyleOffice2013)
	ON_COMMAND_RANGE(ID_OPTIONS_STYLE_VISUALSTUDIO2015BLUE, ID_OPTIONS_STYLE_VISUALSTUDIO2015LIGHT, OnOptionsStyleVisualStudio2015)
	ON_COMMAND_RANGE(ID_OPTIONS_STYLE_OFFICE2013_BACK_NONE, ID_OPTIONS_STYLE_OFFICE2013_BACK_UNDERWATER, OnOptionsStyleOffice2013Back)
	ON_COMMAND(ID_OPTIONS_STYLE_WINDOWS7SCENIC, OnStyleWindows7)

	ON_UPDATE_COMMAND_UI_RANGE(ID_OPTIONS_STYLE_OFFICE2007BLUE, ID_OPTIONS_STYLE_OFFICE2007SYSTEM, OnUpdateOptionsStyle)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OPTIONS_STYLE_OFFICE2010BLUE, ID_OPTIONS_STYLE_OFFICE2010BLACK, OnUpdateOptionsStyle)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OPTIONS_STYLE_OFFICE2013ACCESS, ID_OPTIONS_STYLE_OFFICE2013WORD, OnUpdateOptionsStyle)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OPTIONS_STYLE_VISUALSTUDIO2015BLUE, ID_OPTIONS_STYLE_VISUALSTUDIO2015LIGHT, OnUpdateOptionsStyle)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OPTIONS_STYLE_OFFICE2013_BACK_NONE, ID_OPTIONS_STYLE_OFFICE2013_BACK_UNDERWATER, OnUpdateOptionsStyleOffice2013Back)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_STYLE_WINDOWS7SCENIC, OnUpdateOptionsStyle)

	// Font
	ON_COMMAND_RANGE(ID_OPTIONS_FONT_SYSTEM, ID_OPTIONS_FONT_EXTRALARGE, OnOptionsFont)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OPTIONS_FONT_SYSTEM, ID_OPTIONS_FONT_EXTRALARGE, OnUpdateOptionsFont)

	ON_COMMAND(ID_OPTIONS_FONT_AUTORESIZEICONS, OnAutoResizeIcons)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FONT_AUTORESIZEICONS, OnUpdateAutoResizeIcons)
	
	ON_COMMAND(ID_OPTIONS_DPI_ICON_SCALING, OnDpiIconsScalling)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_DPI_ICON_SCALING, OnUpdateDpiIconsScalling)
	
	ON_COMMAND(ID_OPTIONS_FRAMETHEME, OnFrameTheme)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FRAMETHEME, OnUpdateFrameTheme)
	
	ON_COMMAND(ID_TOGGLE_GROUPS, OnToggleGroups)
	ON_COMMAND(XTP_ID_RIBBONCUSTOMIZE_MINIMIZE, OnToggleGroups)
	ON_COMMAND(ID_RIBBON_MINIMIZE, OnToggleGroups)
	ON_COMMAND(ID_RIBBON_EXPAND, OnToggleGroups)
	ON_UPDATE_COMMAND_UI(ID_RIBBON_MINIMIZE, OnUpdateRibbonMinimize)
	ON_UPDATE_COMMAND_UI(ID_RIBBON_EXPAND, OnUpdateRibbonExpand)

	ON_COMMAND(ID_ALLOW_DWM, OnAllowDwm)
	ON_UPDATE_COMMAND_UI(ID_ALLOW_DWM, OnUpdateAllowDwm)

	//}}AFX_MSG_MAP

	ON_COMMAND(ID_THEMES_THEMES, OnSwitchCommand)
	ON_UPDATE_COMMAND_UI(ID_THEMES_THEMES, OnUpdateSwitchCommand)

	ON_COMMAND_RANGE(ID_THEMES_FONTS, ID_ARRANGE_TEXTWRAPPING, OnEmptyCommandRange)
	ON_COMMAND(ID_FILE_SEND_MAIL, OnEmptyCommand)
	ON_COMMAND(ID_FILE_SEND_INTERNETFAX, OnEmptyCommand)
	ON_COMMAND(ID_STYLES_CHANGE, OnEmptyCommand)


	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_RULER, ID_VIEW_THUMBNAILS, OnUpdateViewShowHide)
	ON_COMMAND_RANGE(ID_VIEW_RULER, ID_VIEW_THUMBNAILS, OnViewShowHide)

	ON_COMMAND_EX(ID_VIEW_MESSAGE_BAR, CFrameWnd::OnBarCheck)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MESSAGE_BAR, CFrameWnd::OnUpdateControlBarMenu)

	ON_NOTIFY(TCN_SELCHANGE, XTP_ID_RIBBONCONTROLTAB, OnRibbonTabChanged)
	ON_NOTIFY(TCN_SELCHANGING, XTP_ID_RIBBONCONTROLTAB, OnRibbonTabChanging)

	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
	ON_COMMAND(ID_APP_OPTIONS, OnCustomize)
	ON_COMMAND(XTP_ID_RIBBONCUSTOMIZE, OnCustomizeQuickAccess)

	ON_XTP_EXECUTE(ID_GALLERY_STYLES, OnGalleryStyles)
	ON_UPDATE_COMMAND_UI(ID_GALLERY_STYLES, OnUpdateGalleryStyles)

	ON_XTP_EXECUTE(ID_GALLERY_COLUMNS, OnGalleryColumns)
	ON_UPDATE_COMMAND_UI(ID_GALLERY_COLUMNS, OnUpdateGalleryColumns)


	ON_XTP_EXECUTE(ID_GALLERY_SHAPES, OnGalleryShapes)
	ON_UPDATE_COMMAND_UI(ID_GALLERY_SHAPES, OnUpdateGalleryShapes)

	ON_XTP_EXECUTE(ID_GALLERY_STYLESET, OnGalleryStyleSet)
	ON_UPDATE_COMMAND_UI(ID_GALLERY_STYLESET, OnUpdateGalleryStyleSet)	

	ON_XTP_EXECUTE(ID_GALLERY_COLORS, OnGalleryThemeColors)
	ON_UPDATE_COMMAND_UI(ID_GALLERY_COLORS, OnUpdateGalleryThemeColors)	

	ON_XTP_EXECUTE(ID_GALLERY_FONTS, OnGalleryThemeFonts)
	ON_UPDATE_COMMAND_UI(ID_GALLERY_FONTS, OnUpdateGalleryThemeFonts)	

	ON_XTP_CREATECONTROL()

	ON_COMMAND_RANGE(ID_SWITCH_PRINTLAYOUT, ID_SWITCH_DRAFT, OnStatusBarSwitchView)
	ON_COMMAND(ID_INDICATOR_MACRORECORDING, OnMacroClick)
	
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_CAPSLOCK, OnUpdateKeyIndicator)

	ON_WM_GETMINMAXINFO()

	ON_MESSAGE_VOID(WM_XTP_CUSTOMIZATION_RIBBONRESET, Reset)
	ON_MESSAGE(WM_XTP_MESSAGEBARCLOSED, OnMessageBarClosed)

	ON_NOTIFY(XTP_RRN_CONTEXTMENU, XTP_IDC_RIBBONBACKSTAGEPAGE_RECENT, OnBackstagePageRecentContextMenu)

	ON_COMMAND(ID_OPTIONS_BACKSTAGE_STYLE2013, OnOptionsBackstageStyle2013)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_BACKSTAGE_STYLE2013, OnUpdateOptionsBackstageStyle2013)

	ON_COMMAND(ID_OPTIONS_STYLE_THEMEDIALOG, OnViewOfficeTheme)
	ON_WM_XTP_THEMECHANGED()

	END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

//#define _SAVE_TO_XML

#define _PROFILE_NAME (_T("CommandBars.1610"))


CMainFrame::CMainFrame()
{
	m_bAllowDwm = FALSE;
	m_bChecked = FALSE;
	m_bAnimation = TRUE;
	m_bLayoutRTL = FALSE;
	m_nColumns = 0;

	m_pItemsShapes = 0;
	m_pItemsStyles = 0;
	m_pItemsStyleSet = 0;
	m_pItemsThemeColors = 0;
	m_pItemsThemeFonts = 0;
	m_pItemsFontTextColor = 0;
	m_pItemsFontBackColor = 0;
	m_pItemsFontFace = 0;
	m_pItemsFontSize = 0;
	m_pItemsColumns = 0;

	m_pItemsUndo = NULL;

	m_nRibbonStyle = ID_OPTIONS_STYLE_OFFICE2007BLUE;

	m_bShowMiniToolbar = TRUE;

	m_nOfficeTheme = -1;
	m_eOffice2013Gray = eGrayNone;
	m_eStudio2015State = eStateClosed;
	m_nRibbonBackImage = ID_OPTIONS_STYLE_OFFICE2013_BACK_CIRCUIT;
	m_bOverrideAllowDwm = FALSE;
	m_bEnableFrameTheme = TRUE;

	memset(m_bOptions, 0, sizeof(m_bOptions));
	m_bBackstageStyle2013 = TRUE;
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CXTPFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!InitCommandBars())
		return -1;

	if (!CreateStatusBar())
		return -1;

	CXTPCommandBars* pCommandBars = GetCommandBars();
	m_wndStatusBar.SetCommandBars(pCommandBars);

	EnableActions();

	Load2013Icons();

	CreateGalleries();

	if (!CreateRibbonBar())
	{
		TRACE0("Failed to create ribbon\n");
		return -1;
	}

	CreateMiniToolBar();

	if (!CreateMessageBar())
		return -1;

	pCommandBars->GetCommandBarsOptions()->bToolBarAccelTips = TRUE;
	pCommandBars->GetShortcutManager()->SetAccelerators(IDR_MAINFRAME);

/*
#ifndef _SAVE_TO_XML
	LoadCommandBars(_PROFILE_NAME);
#else
	CXTPPropExchangeXMLNode px(TRUE, 0, _T("Settings"));

	if (px.LoadFromFile(m_strIniFileName))
	{
		CXTPPropExchangeSection pxCommandBars(px.GetSection(_T("CommandBars")));
		XTP_COMMANDBARS_PROPEXCHANGE_PARAM param; 
		param.bSerializeControls = TRUE;
		param.bSerializeOptions = TRUE;
		GetCommandBars()->DoPropExchange(&pxCommandBars, &param);
	}
#endif
*/
	((CWorkspaceView*)GetDlgItem(AFX_IDW_PANE_FIRST))->
		m_wndScrollBar[SB_VERT].SetCommandBars(pCommandBars);

	((CWorkspaceView*)GetDlgItem(AFX_IDW_PANE_FIRST))->
		m_wndScrollBar[SB_HORZ].SetCommandBars(pCommandBars);

	pCommandBars->GetCommandBarsOptions()->bShowKeyboardTips = TRUE;

	CreateDockingPane();

	// Enable DPI-awareness for icons
	CXTPToolTipContext* pToolTipContext = GetCommandBars()->GetToolTipContext();
	pToolTipContext->SetStyle(GetToolTipStyle());
	pToolTipContext->ShowTitleAndDescription();
	pToolTipContext->ShowImage(TRUE, 0);
	pToolTipContext->EnableImageDPIScaling(FALSE);
	pToolTipContext->SetMargin(XTP_DPI(CRect(2, 2, 2, 2)));
	pToolTipContext->SetMaxTipWidth(XTP_DPI_X(180));
	pToolTipContext->SetFont(pCommandBars->GetPaintManager()->GetIconFont());
	pToolTipContext->SetDelayTime(TTDT_INITIAL, 900);

	//OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013WORD);
	SetOffice2016Theme(xtpIniOffice2016WordColorful);

	// exclude unused themes.
	m_dlgTheme.ExcludeTheme(
		XTP_EXCLUDE_THEME_VISUALSTUDIO6    | 
		XTP_EXCLUDE_THEME_VISUALSTUDIO2005 | 
		XTP_EXCLUDE_THEME_VISUALSTUDIO2008 | 
		XTP_EXCLUDE_THEME_VISUALSTUDIO2010 | 
		XTP_EXCLUDE_THEME_VISUALSTUDIO2012 | 
		XTP_EXCLUDE_THEME_OFFICE2000       | 
		XTP_EXCLUDE_THEME_OFFICEXP         | 
		XTP_EXCLUDE_THEME_OFFICE2003       | 
		XTP_EXCLUDE_THEME_NATIVEWINDOWS    | 
		XTP_EXCLUDE_THEME_CUSTOM);

	// set startup theme
	m_dlgTheme.SetTheme(
		xtpThemeDlgOffice2016,
		xtpThemeColor2016Colorful,
#ifdef _XTP_INCLUDE_RIBBON
		xtpThemeAccentWord,
		xtpThemeRibbonBackCircuit);
#else
		xtpThemeAccentWord);
#endif

	// create theme dialog.
	VERIFY(m_dlgTheme.Create(IDD_THEME_DIALOG, this));

	// enable auto preview.
	m_dlgTheme.EnableAutoPreview(TRUE);

	return 0;
}

void CMainFrame::CreateDockingPane()
{
#ifdef _XTP_INCLUDE_DOCKINGPANE
	m_paneManager.InstallDockingPanes(this);
	m_paneManager.SetTheme(xtpPaneThemeOffice2007Word);
	m_paneManager.SetThemedFloatingFrames(TRUE);
	m_paneManager.SetShowContentsWhileDragging(TRUE);
	m_paneManager.UseSplitterTracker(FALSE);
	
	CXTPDockingPaneMiniWnd::m_bShowPinButton = FALSE;
	
	CXTPDockingPane* pwndPane1 = m_paneManager.CreatePane(
		XTP_DPI_X(300), XTP_DPI(CRect(0, 0, 200, 120)), xtpPaneDockLeft);
	pwndPane1->SetTitle(_T("Styles"));
	pwndPane1->SetOptions(/*xtpPaneNoHideable |*/ xtpPaneHasMenuButton);

	m_paneStyles.Create(CPaneStyles::IDD, this);
	pwndPane1->Attach(&m_paneStyles);
	m_paneStyles.SetOwnerPane(pwndPane1);
#endif
}

BOOL CMainFrame::CreateMessageBar()
{
	if (!m_wndMessageBar.Create(GetCommandBars()))
		return FALSE;

	m_wndMessageBar.AddButton(SC_CLOSE, NULL, _T("Close Message Bar"));
	m_wndMessageBar.AddButton(XTP_ID_CUSTOMIZE, _T("Options..."), _T("Show more options"));

#ifndef _XTP_INCLUDE_MARKUP
	m_wndMessageBar.SetMessage(_T("SECURITY WARNING. Certain content has been disabled"));
#else
	m_wndMessageBar.EnableMarkup();
	m_wndMessageBar.SetMessage(
		_T("<StackPanel Orientation='Horizontal'>")
		_T("        <Image Source='22988'/>")
		_T("		<TextBlock Padding='10, 0, 0, 0' VerticalAlignment='Center'><Bold>SECURITY WARNING</Bold></TextBlock>")
		_T("		<TextBlock Padding='10, 0, 0, 0' VerticalAlignment='Center'>Certain content has been disabled.</TextBlock>")
		_T("</StackPanel>"));
#endif

	return TRUE;
}

BOOL CMainFrame::CreateStatusBar()
{
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return FALSE;      // fail to create
	}

	CXTPStatusBarPane* pPane;
	
	pPane = m_wndStatusBar.AddIndicator(ID_INDICATOR_PAGENUMBER);
	pPane->SetButton();
	pPane->SetPadding(XTP_DPI_X(8), 0, XTP_DPI_X(8), 0);
	pPane->SetBeginGroup(TRUE);
	pPane->SetCaption(_T("&Page Number"));
	pPane->SetValue(_T("1 of 1"));
	pPane->SetText(_T("Page: 1 of 1"));
	pPane->SetTooltip(_T("Page number in document"));

	pPane = m_wndStatusBar.AddIndicator(ID_INDICATOR_WORDCOUNT);
	pPane->SetButton();
	pPane->SetPadding(XTP_DPI_X(8), 0, XTP_DPI_X(8), 0);
	pPane->SetBeginGroup(TRUE);
	pPane->SetCaption(_T("&Word Count"));
	pPane->SetValue(_T("1"));
	pPane->SetText(_T("Words: 1"));

	pPane = m_wndStatusBar.AddIndicator(ID_INDICATOR_LANGUAGE);
	pPane->SetButton();
	pPane->SetPadding(XTP_DPI_X(8), 0, XTP_DPI_X(8), 0);
	pPane->SetBeginGroup(TRUE);
	pPane->SetCaption(_T("&Language"));
	pPane->SetValue(_T("English (U.S.)"));
	pPane->SetText(_T("English (U.S.)"));

	pPane = m_wndStatusBar.AddIndicator(ID_INDICATOR_TRACKCHANGES);
	pPane->SetButton();
	pPane->SetPadding(XTP_DPI_X(8), 0, XTP_DPI_X(8), 0);
	pPane->SetBeginGroup(TRUE);
	pPane->SetCaption(_T("&Track Changes"));
	pPane->SetValue(_T("Off"));
	pPane->SetText(_T("Track Changes: Off"));

	pPane = m_wndStatusBar.AddIndicator(ID_INDICATOR_CAPSLOCK);
	pPane->SetPadding(XTP_DPI_X(8), 0, XTP_DPI_X(8), 0);
	pPane->SetBeginGroup(TRUE);
	pPane->ShowBorders(FALSE);
	pPane->SetCaption(_T("&Caps Lock"));
	pPane->SetValue(_T("Off"));
	pPane->SetText(_T("Caps Lock"));

	pPane = m_wndStatusBar.AddIndicator(ID_INDICATOR_OVERTYPE);
	pPane->SetButton();
	pPane->SetPadding(XTP_DPI_X(8), 0, XTP_DPI_X(8), 0);
	pPane->SetBeginGroup(FALSE);
	pPane->SetCaption(_T("&Overtype"));
	pPane->SetValue(_T("Insert"));
	pPane->SetText(_T("Insert"));

	pPane = m_wndStatusBar.AddIndicator(ID_INDICATOR_MACRORECORDING);
	pPane->SetButton();
	pPane->SetPadding(XTP_DPI_X(4), 0, XTP_DPI_X(4), 0);
	pPane->SetBeginGroup(FALSE);
	pPane->SetCaption(_T("&Macro Recording"));
	pPane->SetValue(_T("Not Recording"));

	CXTPStatusBarProgressPane* pProgressPane = (CXTPStatusBarProgressPane*)m_wndStatusBar.AddIndicator(new CXTPStatusBarProgressPane(), ID_INDICATOR_PROGRESS);
	pProgressPane->SetBeginGroup(FALSE);
	pProgressPane->SetCaption(_T("&ProgressBar"));
	pProgressPane->SetWidth(XTP_DPI_X(100));
	pProgressPane->SetPos(30);
	pProgressPane->SetPadding(XTP_DPI_X(3), 0, XTP_DPI_X(3), 0);
	pProgressPane->SetVisible(FALSE);

	pPane = m_wndStatusBar.AddIndicator(0);
	pPane->SetWidth(1);
	pPane->SetStyle(SBPS_STRETCH | SBPS_NOBORDERS);
	pPane->SetBeginGroup(TRUE);

	static UINT switches[] =
	{
		ID_SWITCH_PRINTLAYOUT,
		ID_SWITCH_FULLSCREENREADING,
		ID_SWITCH_WEBLAYOUT,
	};

	CXTPStatusBarSwitchPane* pSwitchPane = (CXTPStatusBarSwitchPane*)m_wndStatusBar.AddIndicator(new CXTPStatusBarSwitchPane(), ID_INDICATOR_VIEWSHORTCUTS);
	pSwitchPane->SetDark();
	pSwitchPane->SetSwitches(switches, sizeof(switches)/sizeof(UINT));
	pSwitchPane->SetChecked(ID_SWITCH_PRINTLAYOUT);
	pSwitchPane->SetBeginGroup(TRUE);
	pSwitchPane->SetCaption(_T("&View Shortcuts"));

	pPane = m_wndStatusBar.AddIndicator(ID_INDICATOR_ZOOM);
	pPane->SetDark();
	pPane->SetText(_T("100%"));
	pPane->SetButton();
	pPane->SetTextAlignment(DT_CENTER);
	pPane->SetPadding(XTP_DPI_X(8), 0, XTP_DPI_X(8), 0);
	pPane->SetWidth(pPane->GetBestFit());
	pPane->SetTooltip(_T("Zoom level. Click to open the Zoom dialog box."));
	pPane->SetCaption(_T("&Zoom"));
	pPane->SetBeginGroup(FALSE);

	CXTPStatusBarSliderPane* pZoomPane = (CXTPStatusBarSliderPane*)m_wndStatusBar.AddIndicator(new CXTPStatusBarSliderPane(), ID_INDICATOR_ZOOMSLIDER);
	pZoomPane->SetDark();
	pZoomPane->SetBeginGroup(FALSE);
	pZoomPane->SetWidth(XTP_DPI_X(130));
	pZoomPane->SetPos(500); // We will convert 0 -> 10%, 500 -> 100 %, 1000 -> 500 %
	pZoomPane->SetRange(0, 1000);
	pZoomPane->SetCaption(_T("&Zoom Slider"));
	pZoomPane->SetTooltip(_T("Zoom"));
	pZoomPane->SetTooltipPart(XTP_HTSCROLLUP, _T("Zoom Out"));
	pZoomPane->SetTooltipPart(XTP_HTSCROLLDOWN, _T("Zoom In"));
	
	m_wndStatusBar.SetDrawDisabledText(FALSE);
	m_wndStatusBar.SetRibbonDividerIndex(pSwitchPane->GetIndex() - 1);
	m_wndStatusBar.EnableCustomization();

	CXTPToolTipContext* pToolTipContext = m_wndStatusBar.GetToolTipContext();
	pToolTipContext->SetStyle(GetToolTipStyle());
	pToolTipContext->SetFont(m_wndStatusBar.GetPaintManager()->GetIconFont());

	return TRUE;
}

void CMainFrame::OnUpdateCommands()
{
	CXTPCommandBars* pCommandBars = GetCommandBars();
	BOOL b2013 = GetCommandBars()->GetPaintManager()->GetCurrentTheme() == xtpThemeOffice2013;

	pCommandBars->GetActions()->FindAction(ID_TEXT_EFFECTS)->SetVisible(b2013);
	pCommandBars->GetActions()->FindAction(ID_ZOOM_100)->SetVisible(b2013);
	pCommandBars->GetActions()->FindAction(ID_ILLUSTRATION_PICTURES)->SetVisible(b2013);
	pCommandBars->GetActions()->FindAction(ID_ILLUSTRATION_ONLINEPICTURES)->SetVisible(b2013);
	pCommandBars->GetActions()->FindAction(ID_ILLUSTRATION_SMARTART)->SetVisible(b2013);
	pCommandBars->GetActions()->FindAction(ID_ILLUSTRATION_SHAPES)->SetVisible(b2013);
	pCommandBars->GetActions()->FindAction(ID_ILLUSTRATION_SCREENSHOT)->SetVisible(b2013);
	pCommandBars->GetActions()->FindAction(ID_ARRANGE_SELECTIONPANE)->SetVisible(b2013);

	// example of disabled checkbox
	CXTPControlAction* pControl = pCommandBars->GetActions()->FindAction(ID_VIEW_GRIDLINES);
	pControl->SetChecked(TRUE);
	pControl->SetEnabled(FALSE);

	pCommandBars->GetActions()->FindAction(ID_FONT_CLEAR)->GetControl(0)->SetBeginGroup(b2013);	

	CXTPRibbonTab* pTab = pRibbonBar->FindTab(ID_TAB_MAILINGS);
	if (pTab != NULL) pTab->SetVisible(b2013);

	CXTPRibbonGroup* pGroup = pRibbonBar->FindGroup(ID_GROUP_LANGUAGE);
	if (pGroup != NULL) pGroup->SetVisible(b2013);
	pGroup = pRibbonBar->FindGroup(ID_GROUP_LANGUAGE);
	if (pGroup != NULL) pGroup->SetVisible(b2013);
	pGroup = pRibbonBar->FindGroup(ID_GROUP_COMMENTS);
	if (pGroup != NULL) pGroup->SetVisible(b2013);
	pGroup = pRibbonBar->FindGroup(ID_GROUP_TRACKING);
	if (pGroup != NULL) pGroup->SetVisible(b2013);
	pGroup = pRibbonBar->FindGroup(ID_GROUP_CHANGES);
	if (pGroup != NULL) pGroup->SetVisible(b2013);
	pGroup = pRibbonBar->FindGroup(ID_GROUP_COMPARE);
	if (pGroup != NULL) pGroup->SetVisible(b2013);
	pGroup = pRibbonBar->FindGroup(ID_GROUP_PROTECT);
	if (pGroup != NULL) pGroup->SetVisible(b2013);
	pGroup = pRibbonBar->FindGroup(ID_GROUP_PROOFING);
	if (pGroup != NULL) pGroup->SetVisible(b2013);

	pCommandBars->GetActions()->FindAction(ID_STYLES_CHANGE)->SetVisible(!b2013);
	pCommandBars->GetActions()->FindAction(ID_ILLUSTRATION_PICTURE)->SetVisible(!b2013);
	pCommandBars->GetActions()->FindAction(ID_ILLUSTRATION_GRAPHIC)->SetVisible(!b2013);
	pCommandBars->GetActions()->FindAction(ID_VIEW_DOCUMENTMAP)->SetVisible(!b2013);
	pCommandBars->GetActions()->FindAction(ID_VIEW_STATUS_BAR)->SetVisible(!b2013);
	pCommandBars->GetActions()->FindAction(ID_VIEW_MESSAGE_BAR)->SetVisible(!b2013);

	pGroup = pRibbonBar->FindGroup(ID_GROUP_THEMES);
	if (pGroup != NULL) pGroup->SetVisible(!b2013);

	pGroup = pRibbonBar->FindGroup(ID_GROUP_MEDIA);
	if (pGroup != NULL) pGroup->SetVisible(b2013);

	pGroup = pRibbonBar->FindGroup(ID_GROUP_SHAPES);
	if (pGroup != NULL) pGroup->SetVisible(!b2013);

	if (b2013)
		Load2013Icons();
	else
		LoadDefaultIcons();

	pCommandBars->UpdateCommandBars();
	pCommandBars->RedrawCommandBars();

	SetBackstageTheme();
}

void CMainFrame::EnableActions()
{
	CXTPCommandBars* pCommandBars = GetCommandBars();
	pCommandBars->EnableActions();

	pCommandBars->GetActions()->Add(ID_TEXT_EFFECTS);
	pCommandBars->GetActions()->Add(ID_ZOOM_100);
	pCommandBars->GetActions()->Add(ID_ILLUSTRATION_PICTURES);
	pCommandBars->GetActions()->Add(ID_ILLUSTRATION_ONLINEPICTURES);
	pCommandBars->GetActions()->Add(ID_ILLUSTRATION_SMARTART);
	pCommandBars->GetActions()->Add(ID_ILLUSTRATION_SHAPES);
	pCommandBars->GetActions()->Add(ID_ILLUSTRATION_SCREENSHOT);
	pCommandBars->GetActions()->Add(ID_STYLES_CHANGE);
	pCommandBars->GetActions()->Add(ID_ILLUSTRATION_SHAPES);
	pCommandBars->GetActions()->Add(ID_ILLUSTRATION_PICTURE);
	pCommandBars->GetActions()->Add(ID_ILLUSTRATION_GRAPHIC);
	pCommandBars->GetActions()->Add(ID_GROUP_THEMES);
	pCommandBars->GetActions()->Add(ID_ARRANGE_SELECTIONPANE);
	pCommandBars->GetActions()->Add(ID_FONT_CLEAR);
	pCommandBars->GetActions()->Add(ID_TEXT_CHANGECASE);
	pCommandBars->GetActions()->Add(ID_VIEW_DOCUMENTMAP);
	pCommandBars->GetActions()->Add(ID_VIEW_STATUS_BAR);
	pCommandBars->GetActions()->Add(ID_VIEW_MESSAGE_BAR);
	//pCommandBars->GetActions()->Add();
	//pCommandBars->GetActions()->Add();
}

void CMainFrame::SetBackstageTheme()
{
	XTPPaintTheme	nPaintTheme = GetCommandBars()->GetPaintManager()->GetCurrentTheme();
	XTPControlTheme nTheme = xtpControlThemeResource;
	switch (nPaintTheme)
	{
	case xtpThemeOffice2013:
		nTheme = xtpControlThemeOffice2013;
		break;
	case xtpThemeVisualStudio2015:	nTheme = xtpControlThemeVisualStudio2015; break;
	default:						nTheme = xtpControlThemeResource;
	}
	
	CXTPRibbonBar *pRibbonBar = (CXTPRibbonBar*)GetCommandBars()->GetMenuBar();
	CXTPRibbonBackstageView *pView = DYNAMIC_DOWNCAST(CXTPRibbonBackstageView, pRibbonBar->GetSystemButton()->GetCommandBar());
	
	if (pView)
	{
		pView->SetTheme(nPaintTheme);
		if (nTheme == xtpControlThemeResource)
			pView->SetBackstageStyle(xtpRibbonBackstageOffice2010Style);
		else
		{
			if (m_bBackstageStyle2013)
				pView->SetBackstageStyle(xtpRibbonBackstageOffice2013Style);
		}
	}

	if (m_pageInfo.GetSafeHwnd())
	{
		m_pageInfo.SetTheme(nTheme);
	}

	if (m_pageHelp.GetSafeHwnd())
	{
		m_pageHelp.SetTheme(nTheme);
	}

	if (m_pageSave.GetSafeHwnd())
	{		
		m_pageSave.SetTheme(nTheme);
	}

	if (m_pageRecent.GetSafeHwnd())
	{
		m_pageRecent.SetTheme(nTheme);
	}

	if (m_pageDisabled.GetSafeHwnd())
	{
		m_pageDisabled.SetTheme(nTheme);
	}

	if (m_pagePrint.GetSafeHwnd())
	{
		m_pagePrint.SetTheme(nTheme);
	}
}

void CMainFrame::LoadDefaultIcons(BOOL bDark)
{
	CXTPCommandBars* pCommandBars = GetCommandBars();

	UINT uiGroupParagraph[] = {ID_INSERT_BULLET, ID_INSERT_NUMBERING, ID_INSERT_LIST, 
		ID_PARA_DECREASEINDENT, ID_PARA_INCREASEINDENT, ID_PARA_SORT, ID_PARA_SHOWMARKS, ID_PARA_LEFT, 
		ID_PARA_CENTER, ID_PARA_RIGHT, ID_PARA_JUSTIFY, ID_PARA_LINESPACING, ID_PARA_SHADING, ID_BORDERS_NOBORDER};

	pCommandBars->GetImageManager()->SetIcons(bDark ? ID_GROUP_PARAGRAPH_DARK : ID_GROUP_PARAGRAPH,
		uiGroupParagraph, _countof(uiGroupParagraph), CSize(16, 16));

	UINT uiGroupFont[] = {ID_FONT_GROW, ID_FONT_SHRINK, ID_FONT_CLEAR, ID_CHAR_BOLD, ID_CHAR_ITALIC, ID_CHAR_UNDERLINE,
		ID_CHAR_STRIKETHROUGH, ID_TEXT_SUBSCRIPT,ID_TEXT_SUPERSCRIPT, ID_TEXT_CHANGECASE, ID_TEXT_COLOR, ID_TEXT_HIGHLIGHTCOLOR};

	pCommandBars->GetImageManager()->SetIcons(bDark ? ID_GROUP_FONT_DARK : ID_GROUP_FONT,
		uiGroupFont, _countof(uiGroupFont), CSize(16, 16));

	XTP_SAFE_CALL2(m_pItemsStyles, GetImageManager(), SetIcons(bDark ? ID_GALLERY_STYLES_DARK : ID_GALLERY_STYLES,
		0, 0, CSize(64, 48)));
}

void CMainFrame::LoadDefaultIcons()
{
	CXTPCommandBars* pCommandBars = GetCommandBars();
	CXTPCommandBarsOptions* pOptions = pCommandBars->GetCommandBarsOptions();

	pCommandBars->GetImageManager()->RemoveAll();
	pCommandBars->GetImageManager()->SetIcons(IDR_SMALLICONS);

	LoadDefaultIcons(m_enumTheme == CRibbonSampleApp::themeVisualStudio2015Dark);

    UINT uiLargeIcons[] = {ID_EDIT_PASTE,1,ID_PAGES_NEW,ID_PAGES_COVER,ID_PAGES_BREAK,ID_TABLE_NEW
	,ID_ILLUSTRATION_PICTURE,ID_ILLUSTRATION_GRAPHIC,ID_ILLUSTRATION_CHART,ID_INSERT_HEADER,ID_INSERT_FOOTER,
	ID_INSERT_PAGENUMBER,ID_TEXT_TEXTBOX,ID_TEXT_PARTS,ID_TEXT_WORDART,ID_TEXT_DROPCAP,ID_SYMBOL_EQUATIONS,ID_SYMBOL_SYMBOL,ID_GALLERY_SHAPES};
	pCommandBars->GetImageManager()->SetIcons(IDB_LARGEICONS, uiLargeIcons, _countof(uiLargeIcons), CSize(32, 32));

	pCommandBars->GetImageManager()->SetIcons(IDR_LAYOUTTABLARGE);
	pCommandBars->GetImageManager()->SetIcons(IDR_LAYOUTTABSMALL);

	UINT uiSystemMenu[] = {ID_FILE_NEW, ID_FILE_OPEN, ID_FILE_SAVE, ID_FILE_SAVE_AS, ID_FILE_PRINT, ID_FILE_PRINT_SETUP, 
	ID_FILE_PRINT_PREVIEW, ID_FILE_PREPARE, ID_FILE_SEND, ID_APP_CLOSE, ID_FILE_SEND_MAIL, ID_FILE_SEND_INTERNETFAX}; 
	pCommandBars->GetImageManager()->SetIcons(IDB_SYSTEMMENULARGE, uiSystemMenu, _countof(uiSystemMenu), CSize(32, 32));

	XTPImageManager()->SetIcon(IDC_MESSAGEBAR_WARNING, IDC_MESSAGEBAR_WARNING);

	UINT switches[] = {ID_SWITCH_PRINTLAYOUT,ID_SWITCH_FULLSCREENREADING,ID_SWITCH_WEBLAYOUT,ID_SWITCH_OUTLINE,ID_SWITCH_DRAFT};
	pCommandBars->GetImageManager()->SetIcons(IDB_STATUSBAR_VIEWSWITCH, switches, sizeof(switches)/sizeof(UINT), 0);

	UINT uiGroupFind[] = {ID_EDIT_FIND, ID_EDIT_REPLACE, ID_EDIT_GOTO, ID_EDIT_SELECT};
	pCommandBars->GetImageManager()->SetIcons(ID_GROUP_FIND, uiGroupFind, _countof(uiGroupFind), CSize(16, 16));

	UINT uiInsertTabIcons[] = {ID_PAGES_NEW, ID_PAGES_COVER, ID_PAGES_BREAK, ID_INSERT_HEADER, ID_INSERT_FOOTER, ID_INSERT_PAGENUMBER, 
		ID_TEXT_PARTS, ID_TEXT_WORDART, ID_TEXT_DROPCAP, 
		ID_ILLUSTRATION_GRAPHIC, ID_ILLUSTRATION_CLIPART, ID_ILLUSTRATION_CLIPART, ID_ILLUSTRATION_CHART, 
		ID_INSERT_HYPERLINK, ID_INSERT_BOOKMARK, ID_INSERT_CROSS_REFERENCE, ID_TEXT_SIGNATURE, ID_TEXT_DATETIME, ID_TEXT_INSERTOBJECT};
	pCommandBars->GetImageManager()->SetIcons(IDB_INSERTTAB, uiInsertTabIcons, _countof(uiInsertTabIcons), CSize(16, 16));
	
	pCommandBars->GetImageManager()->SetIcon(ID_GROUP_BUTTONPOPUP, ID_GROUP_BUTTONPOPUP);

	UINT uiTabReferences[] = {ID_CONTENTS_TABLE, ID_FOOTNOTES_INSERT, 1, ID_CAPTIONS_INSERT, ID_INDEX_MARK };
	pCommandBars->GetImageManager()->SetIcons(ID_TAB_REFERENCES, uiTabReferences, _countof(uiTabReferences), CSize(32, 32));

	UINT uiView[] = {ID_VIEW_PRINTLAYOUT, ID_VIEW_FULLSCREENREADING, ID_VIEW_WEBLAYOUT, ID_VIEW_OUTLINE, ID_VIEW_DRAFT,
		ID_ZOOM_ZOOM, ID_WINDOW_NEW, ID_WINDOW_ARRANGE, ID_WINDOW_SPLIT, ID_WINDOW_SWITCH};
	pCommandBars->GetImageManager()->SetIcons(ID_TAB_VIEW, uiView, _countof(uiView), CSize(32, 32));

	UINT uiPageParagraph[] = {ID_PARAGRAPH_INDENTLEFT, ID_PARAGRAPH_INDENTRIGHT, ID_PARAGRAPH_SPACINGBEFORE, ID_PARAGRAPH_SPACINGAFTER};
	pCommandBars->GetImageManager()->SetIcons(	ID_GROUP_PAGEPARAGRAPH, uiPageParagraph, _countof(uiPageParagraph), CSize(16, 16));

	UINT uiTabPageLayout[] = {ID_ARRANGE_POSITION, ID_ARRANGE_FRONT, ID_ARRANGE_BACK, ID_ARRANGE_TEXTWRAPPING,
		ID_ARRANGE_ALIGN, ID_ARRANGE_GROUP, ID_ARRANGE_ROTATE};
	pCommandBars->GetImageManager()->SetIcons(ID_TAB_PAGELAYOUT, uiTabPageLayout, _countof(uiTabPageLayout), CSize(32, 32));

	UINT uiGroupsTip[] = {ID_GROUP_CLIPBOARD_OPTION, ID_GROUP_FONT_OPTION, ID_GROUP_PARAGRAPH_OPTION, ID_GROUP_STYLES_OPTION, IDB_GEAR};
	pCommandBars->GetImageManager()->SetIcons(IDB_GROUPOPTIONTOOLTIP, uiGroupsTip, _countof(uiGroupsTip), CSize(100, 130));

	UINT uiRibbonMinimize[] = {ID_RIBBON_MINIMIZE, ID_RIBBON_EXPAND};
	pCommandBars->GetImageManager()->SetIcons(IDR_RIBBON_MINIMIZE, uiRibbonMinimize, _countof(uiRibbonMinimize), CSize(16, 16));

	UINT uiTABLEOFCONTENTS[] = {ID_CONTENTS_TABLE,ID_CONTENTS_ADDTEXT,ID_CONTENTS_UPDATE};
	pCommandBars->GetImageManager()->SetIcons(IDB_GROUP_TABLEOFCONTENTS, uiTABLEOFCONTENTS, _countof(uiTABLEOFCONTENTS), CSize(16, 16));

	UINT uiFOOTNOTES[] = {ID_FOOTNOTES_INSERT,ID_FOOTNOTES_INSEREND,ID_FOOTNOTES_NEXT,ID_FOOTNOTES_SHOW,ID_CONTENTS_ADDTEXT,ID_CONTENTS_UPDATE};
	pCommandBars->GetImageManager()->SetIcons(IDB_GROUP_FOOTNOTES, uiFOOTNOTES, _countof(uiFOOTNOTES), CSize(16, 16));

	UINT uiINDEX[] = {ID_INDEX_MARK,ID_INDEX_INSERT,ID_INDEX_UPDATE};
	pCommandBars->GetImageManager()->SetIcons(IDB_GROUP_INDEX, uiINDEX, _countof(uiINDEX), CSize(16, 16));

	UINT uiCAPTIONS[] = {ID_CAPTIONS_INSERT,ID_CAPTIONS_FIGURES,ID_CAPTIONS_UPDATE,IOD_CAPTIONS_CROSSREFERENCE};
	pCommandBars->GetImageManager()->SetIcons(IDB_GROUP_CAPTIONS, uiCAPTIONS, _countof(uiCAPTIONS), CSize(16, 16));

	UINT uiDOCUMENTVIEWS[] = {ID_VIEW_FULLSCREENREADING,ID_VIEW_PRINTLAYOUT,ID_VIEW_WEBLAYOUT,ID_VIEW_OUTLINE,ID_VIEW_DRAFT};
	pCommandBars->GetImageManager()->SetIcons(IDB_GROUP_DOCUMENTVIEWS, uiDOCUMENTVIEWS, _countof(uiDOCUMENTVIEWS), CSize(16, 16));

	UINT uiZOOM[] = {ID_ZOOM_ZOOM,ID_ZOOM_100,ID_ZOOM_ONEPAGE,ID_ZOOM_TWOPAGES,ID_ZOOM_PAGEWIDTH};
	pCommandBars->GetImageManager()->SetIcons(IDB_GROUP_ZOOM, uiZOOM, _countof(uiZOOM), CSize(16, 16));

	UINT uiWINDOW[] = {ID_WINDOW_NEW,ID_WINDOW_ARRANGE,ID_WINDOW_SPLIT,ID_WINDOW_SIDEBYSIDE,ID_WINDOW_SYNCHRONOUSSCROLLING,ID_WINDOW_RESET,ID_WINDOW_SWITCH};
	pCommandBars->GetImageManager()->SetIcons(IDB_GROUP_WINDOW, uiWINDOW, _countof(uiWINDOW), CSize(16, 16));

	UINT uiMacros[] = {ID_INDICATOR_MACRORECORDING};
	pCommandBars->GetImageManager()->SetIcons(IDB_INDICATOR_MACRORECORDING, uiMacros, _countof(uiMacros), CSize(16, 16));

	UINT nIDIcons[] = {ID_BACKSTAGE_SAVE, ID_BACKSTAGE_SAVE_AS, ID_FILE_OPEN, ID_FILE_CLOSE, ID_APP_OPTIONS, ID_APP_EXIT};
	pCommandBars->GetImageManager()->SetIcons(IDB_BACKSTAGEICONS, nIDIcons, _countof(nIDIcons), CSize(16, 16));

	UINT uCommand = {IDB_GEAR};
	pCommandBars->GetImageManager()->SetIcons(IDB_GEAR, &uCommand, 1, CSize(0, 0), xtpImageNormal);
}

void CMainFrame::Load2013Icons()
{
	CXTPCommandBars* pCommandBars = GetCommandBars();
	CXTPCommandBarsOptions* pOptions = pCommandBars->GetCommandBarsOptions();

	pCommandBars->GetImageManager()->RemoveAll();

	UINT uiOffice2013[] = {
		  ID_APP_ABOUT, ID_ARRANGE_ALIGN, ID_ARRANGE_BACK, ID_ARRANGE_FRONT, ID_ARRANGE_GROUP								// 0_
		, ID_ARRANGE_POSITION, ID_ARRANGE_ROTATE, ID_ARRANGE_SELECTIONPANE, ID_ARRANGE_TEXTWRAPPING, ID_BORDERS_NOBORDER
		, ID_CAPTIONS_FIGURES, ID_CAPTIONS_INSERT, ID_CAPTIONS_UPDATE, ID_CHAR_BOLD, ID_CHAR_ITALIC							// 1_
		, ID_CHAR_STRIKETHROUGH, ID_CHAR_UNDERLINE, ID_CONTENTS_ADDTEXT, ID_CONTENTS_TABLE, ID_CONTENTS_UPDATE
		, ID_EDIT_COPY, ID_EDIT_CUT, ID_EDIT_FIND, ID_EDIT_PASTE, ID_EDIT_REPLACE											// 2_
		, ID_EDIT_SELECT, ID_EDIT_UNDO, ID_FILE_PRINT, ID_FILE_SAVE, ID_FONT_CLEAR
		, ID_FONT_GROW, ID_FONT_SHRINK, ID_FOOTNOTES_INSEREND, ID_FOOTNOTES_INSERT, ID_FOOTNOTES_NEXT						// 3_
		, ID_FOOTNOTES_SHOW, ID_FORMAT_PAINTER, ID_GALLERY_STYLES, ID_GROUP_FIND, ID_GROUP_FONT
		, ID_GROUP_HEADERFOOTERS, ID_GROUP_ILLUSTRATIONS, ID_GROUP_LINKS, ID_GROUP_SYMBOLS, ID_GROUP_TEXT					// 4_
		, ID_ILLUSTRATION_CHART, ID_ILLUSTRATION_ONLINEPICTURES, ID_ILLUSTRATION_PICTURES, ID_ILLUSTRATION_SCREENSHOT, ID_ILLUSTRATION_SMARTART
		, ID_INDEX_INSERT, ID_INDEX_MARK, ID_INDEX_UPDATE, ID_INDICATOR_MACRORECORDING, ID_INSERT_BOOKMARK					// 5_
		, ID_INSERT_BULLET, ID_INSERT_CROSS_REFERENCE, ID_INSERT_FOOTER, ID_INSERT_HEADER, ID_INSERT_LIST
		, ID_INSERT_NUMBERING, ID_INSERT_ONLINEVIDEO, ID_INSERT_PAGENUMBER, ID_MAIL_ADDRESSBLOCK, ID_MAIL_CHECKFORERRORS	// 6_
		, ID_MAIL_EDITRECIPIENTLIST, ID_MAIL_ENVELOPES, ID_MAIL_FINDRECIPIENT, ID_MAIL_FINISHANDMERGE, ID_MAIL_FIRSTRECORD
		, ID_MAIL_GREETINGLINE, ID_MAIL_HIGHLIGHT, ID_MAIL_INSERMERGEFIELD, ID_MAIL_LABELS, ID_MAIL_LASTRECORD				// 7_
		, ID_MAIL_MATCHFIELDS, ID_MAIL_NEXTRECORD, ID_MAIL_PREVIEWRESULTS, ID_MAIL_PREVIOUSRECORD, ID_MAIL_RULES
		, ID_MAIL_SELECTRECIPIENTS, ID_MAIL_STARTMAILMERGE, ID_MAIL_UPDATELABELS, ID_PAGE_BORDERS, ID_PAGE_COLOR			// 8_
		, ID_PAGE_COLUMNS, ID_PAGE_HYPHENATATION, ID_PAGE_LINENUMBERS, ID_PAGE_MARGINS, ID_PAGE_ORIENTATION
		, ID_PAGE_SIZE, ID_PAGE_WATERMARK, ID_PAGES_BREAK, ID_PAGES_COVER, ID_PAGES_NEW										// 9_
		, ID_PARA_CENTER, ID_PARA_DECREASEINDENT, ID_PARA_INCREASEINDENT, ID_PARA_JUSTIFY, ID_PARA_LEFT
		, ID_PARA_LINESPACING, ID_PARA_RIGHT, ID_PARA_SHADING, ID_PARA_SHOWMARKS, ID_PARA_SORT								// 10_
		, ID_PARAGRAPH_SPACINGAFTER, ID_REVIEW_ACCEPT, ID_REVIEW_BLOCKAUTHORS, ID_REVIEW_COMPARE, ID_REVIEW_DELETE
		, ID_REVIEW_LANGUAGE, ID_REVIEW_NEWCOMMENT, ID_REVIEW_NEXT, ID_REVIEW_NEXTCOMMENT, ID_REVIEW_PREVIOUS				// 11_
		, ID_REVIEW_PREVIOUSCOMMENT, ID_REVIEW_REJECT, ID_REVIEW_RESTRICTEDITING, ID_REVIEW_REVIEWINGPANE, ID_REVIEW_SHOWCOMMENTS
		, ID_REVIEW_SHOWMARKUP, ID_REVIEW_SIMPLEMARKUP, ID_REVIEW_SPELLING, ID_REVIEW_THESAURUS, ID_REVIEW_TRACKCHANGES		// 12_
		, ID_REVIEW_TRANSLATE, ID_REVIEW_WORDCOUNT, ID_RIBBON_EXPAND, ID_RIBBON_MINIMIZE, ID_STYLES_CHANGE
		, ID_SYMBOL_EQUATIONS, ID_SYMBOL_SYMBOL, ID_TABLE_NEW, ID_TEXT_CHANGECASE, ID_TEXT_COLOR							// 13_
		, ID_TEXT_DATETIME, ID_TEXT_DROPCAP, ID_TEXT_EFFECTS, ID_TEXT_HIGHLIGHTCOLOR, ID_TEXT_INSERTOBJECT
		, ID_TEXT_PARTS, ID_TEXT_SIGNATURE, ID_TEXT_SUBSCRIPT, ID_TEXT_SUPERSCRIPT, ID_TEXT_TEXTBOX							// 14_
		, ID_TEXT_WORDART, ID_VIEW_DRAFT, ID_VIEW_FULLSCREENREADING, ID_VIEW_OUTLINE, ID_VIEW_PRINTLAYOUT
		, ID_VIEW_WEBLAYOUT, ID_WINDOW_ARRANGE, ID_WINDOW_RESET, ID_WINDOW_SIDEBYSIDE, ID_WINDOW_SPLIT						// 15_
		, ID_WINDOW_SWITCH, ID_WINDOW_SYNCHRONOUSSCROLLING, ID_WINDOW_NEW, ID_ZOOM_100, ID_ZOOM_ONEPAGE
		, ID_ZOOM_PAGEWIDTH, ID_ZOOM_TWOPAGES, ID_ZOOM_ZOOM	};																// 16_

	pCommandBars->GetImageManager()->SetIcons(IDB_OFFICE2013_16, uiOffice2013, _countof(uiOffice2013), CSize(16, 16));
	pCommandBars->GetImageManager()->SetIcons(IDB_OFFICE2013_24, uiOffice2013, _countof(uiOffice2013), CSize(24, 24));
	pCommandBars->GetImageManager()->SetIcons(IDB_OFFICE2013_32, uiOffice2013, _countof(uiOffice2013), CSize(32, 32));
	pCommandBars->GetImageManager()->SetIcons(IDB_OFFICE2013_40, uiOffice2013, _countof(uiOffice2013), CSize(40, 40));
	pCommandBars->GetImageManager()->SetIcons(IDB_OFFICE2013_48, uiOffice2013, _countof(uiOffice2013), CSize(48, 48));
	pCommandBars->GetImageManager()->SetIcons(IDB_OFFICE2013_64, uiOffice2013, _countof(uiOffice2013), CSize(64, 64));

	// reuse icons
	
	::ZeroMemory(&uiOffice2013, sizeof(uiOffice2013));
	
	uiOffice2013[41]	= ID_ILLUSTRATION_SHAPES;			//ID_GROUP_ILLUSTRATIONS
	uiOffice2013[42]	= ID_INSERT_HYPERLINK;				//ID_GROUP_LINKS
	uiOffice2013[103]	= ID_GROUP_PARAGRAPH;				//ID_PARA_SHOWMARKS
	uiOffice2013[96]	= ID_PARAGRAPH_INDENTLEFT;			//ID_PARA_DECREASEINDENT   
	uiOffice2013[97]	= ID_PARAGRAPH_INDENTRIGHT;			//ID_PARA_INCREASEINDENT
	uiOffice2013[100]	= ID_PARAGRAPH_SPACINGBEFORE;		//ID_PARA_LINESPACING
	uiOffice2013[56]	= IOD_CAPTIONS_CROSSREFERENCE;		//ID_INSERT_CROSS_REFERENCE
	uiOffice2013[92]	= ID_PAGE_BREAKS;					//ID_PAGES_BREAK

	// add isons for ribbon's group
	
	uiOffice2013[23]	= ID_GROUP_CLIPBOARD;			//ID_EDIT_PASTE
	uiOffice2013[93]	= ID_GROUP_PAGES;				//ID_PAGES_COVER
	uiOffice2013[90]	= ID_GROUP_PAGESETUP;			//ID_PAGE_SIZE
	uiOffice2013[91]	= ID_GROUP_PAGEBACKGROUND;		//ID_PAGE_WATERMARK
	uiOffice2013[ 3]	= ID_GROUP_ARRANGE;				//ID_ARRANGE_FRONT
	uiOffice2013[18]	= ID_GROUP_TABLEOFCONTENTS;		//ID_CONTENTS_TABLE
	uiOffice2013[32]	= ID_GROUP_FOOTNOTES;			//ID_FOOTNOTES_INSEREND
	uiOffice2013[11]	= ID_GROUP_CAPTIONS;			//ID_CAPTIONS_INSERT
	uiOffice2013[51]	= ID_GROUP_INDEX;				//ID_INDEX_MARK
	uiOffice2013[66]	= ID_GROUP_CREATE;				//ID_MAIL_ENVELOPES
	uiOffice2013[81]	= ID_GROUP_STARTMAILMERGE;		//ID_MAIL_STARTMAILMERGE
	uiOffice2013[71]	= ID_GROUP_WRITEINSETFIELDS;	//ID_MAIL_HIGHLIGHT
	uiOffice2013[77]	= ID_GROUP_PREVIEWRESULTS;		//ID_MAIL_PREVIEWRESULTS
	uiOffice2013[122]	= ID_GROUP_PROOFING;			//ID_REVIEW_SPELLING
	uiOffice2013[125]	= ID_GROUP_LANGUAGE;			//ID_REVIEW_TRANSLATE
	uiOffice2013[111]	= ID_GROUP_COMMENTS;			//ID_REVIEW_NEWCOMMENT
	uiOffice2013[124]	= ID_GROUP_TRACKING;			//ID_REVIEW_TRACKCHANGES
	uiOffice2013[116]	= ID_GROUP_CHANGES;				//ID_REVIEW_REJECT
	uiOffice2013[117]	= ID_GROUP_PROTECT;				//ID_REVIEW_RESTRICTEDITING
	uiOffice2013[149]	= ID_GROUP_DOCUMENTVIEWS;		//ID_VIEW_PRINTLAYOUT
	uiOffice2013[162]	= ID_GROUP_ZOOM;				//ID_ZOOM_ZOOM

	pCommandBars->GetImageManager()->SetIcons(IDB_OFFICE2013_16, uiOffice2013, _countof(uiOffice2013), CSize(16, 16));
	pCommandBars->GetImageManager()->SetIcons(IDB_OFFICE2013_24, uiOffice2013, _countof(uiOffice2013), CSize(24, 24));
	pCommandBars->GetImageManager()->SetIcons(IDB_OFFICE2013_32, uiOffice2013, _countof(uiOffice2013), CSize(32, 32));
	pCommandBars->GetImageManager()->SetIcons(IDB_OFFICE2013_40, uiOffice2013, _countof(uiOffice2013), CSize(40, 40));
	pCommandBars->GetImageManager()->SetIcons(IDB_OFFICE2013_48, uiOffice2013, _countof(uiOffice2013), CSize(48, 48));
	pCommandBars->GetImageManager()->SetIcons(IDB_OFFICE2013_64, uiOffice2013, _countof(uiOffice2013), CSize(64, 64));

	UINT uiMessageBar[] = {IDC_MESSAGEBAR_WARNING}; 
	pCommandBars->GetImageManager()->SetIcons(IDB_BITMAP_OFFICE2013_SHIELD_24, uiMessageBar, _countof(uiMessageBar), CSize(24, 24));

	UINT switches[] = {0,ID_SWITCH_PRINTLAYOUT,ID_SWITCH_FULLSCREENREADING,ID_SWITCH_WEBLAYOUT,ID_SWITCH_OUTLINE,ID_SWITCH_DRAFT};
	pCommandBars->GetImageManager()->SetIcons(IDB_BITMAP_OFFICE2013_STATUS_16, switches, sizeof(switches)/sizeof(UINT), 0);

	XTP_SAFE_CALL2(m_pItemsStyles, GetImageManager(), SetIcons(ID_GALLERY_STYLES, 0, 0, CSize(64, 48)));
}

void CMainFrame::CreateGalleries()
{
	m_pItemsShapes = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_SHAPES);
	m_pItemsShapes->SetItemSize(CSize(20, 20));
	
	m_pItemsShapes->GetImageManager()->SetIcons(ID_GALLERY_SHAPES, 0, 0, CSize(20, 20));

	CXTPControlGalleryItem* pItem = m_pItemsShapes->AddLabel(0);
	pItem->SetCaption(_T("Lines"));

	int nShape;
	for (nShape = 0; nShape < 12; nShape++)
		m_pItemsShapes->AddItem(nShape, nShape);

	pItem = m_pItemsShapes->AddLabel(0);
	pItem->SetCaption(_T("Basic Shapes"));

	for (; nShape < 12 + 32; nShape++)
		m_pItemsShapes->AddItem(nShape, nShape);

	pItem = m_pItemsShapes->AddLabel(0);
	pItem->SetCaption(_T("Block Arrows"));

	for (; nShape < 12 + 32 + 27; nShape++)
		m_pItemsShapes->AddItem(nShape, nShape);

	pItem = m_pItemsShapes->AddLabel(0);
	pItem->SetCaption(_T("Flowchart"));

	for (; nShape < 12 + 32 + 27 + 28; nShape++)
		m_pItemsShapes->AddItem(nShape, nShape);

	pItem = m_pItemsShapes->AddLabel(0);
	pItem->SetCaption(_T("Callouts"));

	for (; nShape < 12 + 32 + 27 + 28 + 20; nShape++)
		m_pItemsShapes->AddItem(nShape, nShape);

	pItem = m_pItemsShapes->AddLabel(0);
	pItem->SetCaption(_T("Stars and Banners"));

	for (; nShape < 12 + 32 + 27 + 28 + 20 + 16; nShape++)
		m_pItemsShapes->AddItem(nShape, nShape);

	m_nShape = -1;
	m_nStyle = 0;


	m_pItemsStyles = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_STYLES);

	m_pItemsStyles->GetImageManager()->SetMaskColor(0xFF00FF);
	m_pItemsStyles->GetImageManager()->SetIcons(ID_GALLERY_STYLES, 0, 0, CSize(64, 48));
	m_pItemsStyles->GetImageManager()->SetMaskColor(COLORREF_NULL); // Default TopLeft Pixel.

	m_pItemsStyles->SetItemSize(CSize(72, 56));

	for (int nStyle = 0; nStyle < 16; nStyle++)
		m_pItemsStyles->AddItem(nStyle, nStyle);


	m_nStyleSet = 0;

	m_pItemsStyleSet = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_STYLESET);
	m_pItemsStyleSet->SetItemSize(CSize(0, 22));
	m_pItemsStyleSet->AddItem(new CGalleryItemStyleSet(0, _T("Classic")));
	m_pItemsStyleSet->AddItem(new CGalleryItemStyleSet(1, _T("Default")));
	m_pItemsStyleSet->AddItem(new CGalleryItemStyleSet(2, _T("Distinctive")));
	m_pItemsStyleSet->AddItem(new CGalleryItemStyleSet(3, _T("Elegant")));
	m_pItemsStyleSet->AddItem(new CGalleryItemStyleSet(4, _T("Fancy")));
	m_pItemsStyleSet->AddItem(new CGalleryItemStyleSet(5, _T("Formal")));
	m_pItemsStyleSet->AddItem(new CGalleryItemStyleSet(6, _T("Manuscript")));
	m_pItemsStyleSet->AddItem(new CGalleryItemStyleSet(7, _T("Modern")));
	m_pItemsStyleSet->AddItem(new CGalleryItemStyleSet(8, _T("Simple")));
	m_pItemsStyleSet->AddItem(new CGalleryItemStyleSet(9, _T("Traditional")));

	m_nThemeColors = 0;
	m_pItemsThemeColors = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_COLORS);
	m_pItemsThemeColors->SetItemSize(CSize(0, 20));

	pItem = m_pItemsThemeColors->AddLabel(0);
	pItem->SetCaption(_T("Built-In"));
	m_pItemsThemeColors->AddItem(new CGalleryItemThemeColors(0, _T("Office")));
	m_pItemsThemeColors->AddItem(new CGalleryItemThemeColors(1, _T("Grayscale")));
	m_pItemsThemeColors->AddItem(new CGalleryItemThemeColors(2, _T("Apex")));
	m_pItemsThemeColors->AddItem(new CGalleryItemThemeColors(3, _T("Aspect")));
	m_pItemsThemeColors->AddItem(new CGalleryItemThemeColors(4, _T("Civic")));
	m_pItemsThemeColors->AddItem(new CGalleryItemThemeColors(5, _T("Concourse")));
	m_pItemsThemeColors->AddItem(new CGalleryItemThemeColors(6, _T("Currency")));
	m_pItemsThemeColors->AddItem(new CGalleryItemThemeColors(7, _T("Deluxe")));

	m_nThemeFonts = 0;
	m_pItemsThemeFonts = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_FONTS);
	m_pItemsThemeFonts->SetItemSize(CSize(0, 60));

	pItem = m_pItemsThemeFonts->AddLabel(0);
	pItem->SetCaption(_T("Built-In"));
	m_pItemsThemeFonts->AddItem(new CGalleryItemThemeFonts(0, _T("Office")));
	m_pItemsThemeFonts->AddItem(new CGalleryItemThemeFonts(1, _T("Apex")));
	m_pItemsThemeFonts->AddItem(new CGalleryItemThemeFonts(2, _T("Aspect")));
	m_pItemsThemeFonts->AddItem(new CGalleryItemThemeFonts(3, _T("Civic")));
	m_pItemsThemeFonts->AddItem(new CGalleryItemThemeFonts(4, _T("Concourse")));
	m_pItemsThemeFonts->AddItem(new CGalleryItemThemeFonts(5, _T("Currency")));
	m_pItemsThemeFonts->AddItem(new CGalleryItemThemeFonts(6, _T("Deluxe")));
	m_pItemsThemeFonts->AddItem(new CGalleryItemThemeFonts(7, _T("Equity")));

	m_pItemsFontTextColor = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_FONTTEXTCOLOR);
	m_pItemsFontTextColor->SetItemSize(CSize(17, 17 ));
	
	pItem = m_pItemsFontTextColor->AddLabel(0);
	pItem->SetCaption(_T("Theme Colors"));
	
	CGalleryItemFontColor::AddThemeColors(m_pItemsFontTextColor, 0);

	pItem = m_pItemsFontTextColor->AddLabel(0);
	pItem->SetCaption(_T("Standard Colors"));

	CGalleryItemFontColor::AddStandardColors(m_pItemsFontTextColor);

	m_pItemsFontBackColor = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_FONTBACKCOLOR);
	m_pItemsFontBackColor->SetItemSize(CSize(30, 30));

	CGalleryItemFontColor::AddStandardBackColors(m_pItemsFontBackColor);

	m_pItemsFontFace = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_FONTFACE);
	m_pItemsFontFace->SetItemSize(CSize(0, 26));
	CGalleryItemFontFace::AddFontItems(m_pItemsFontFace);

	m_pItemsFontSize = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_FONTSIZE);
	m_pItemsFontSize->SetItemSize(CSize(0, 17));
	m_pItemsFontSize->AddItem(_T("8"));
	m_pItemsFontSize->AddItem(_T("9"));
	m_pItemsFontSize->AddItem(_T("10"));
	m_pItemsFontSize->AddItem(_T("11"));
	m_pItemsFontSize->AddItem(_T("12"));
	m_pItemsFontSize->AddItem(_T("14"));
	m_pItemsFontSize->AddItem(_T("16"));
	m_pItemsFontSize->AddItem(_T("18"));
	m_pItemsFontSize->AddItem(_T("20"));
	m_pItemsFontSize->AddItem(_T("22"));
	m_pItemsFontSize->AddItem(_T("24"));
	m_pItemsFontSize->AddItem(_T("26"));
	m_pItemsFontSize->AddItem(_T("28"));
	m_pItemsFontSize->AddItem(_T("36"));
	m_pItemsFontSize->AddItem(_T("48"));
	m_pItemsFontSize->AddItem(_T("72"));

	m_pItemsUndo = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_EDIT_UNDO);
	m_pItemsUndo->SetItemSize(CSize(0, 21));
	m_pItemsUndo->ClipItems(FALSE);

	m_pItemsColumns = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_COLUMNS);
	m_pItemsColumns->GetImageManager()->SetIcons(ID_GALLERY_COLUMNS, 0, 0, CSize(32, 32));
	m_pItemsColumns->AddItem(_T("One"), 0, 0);
	m_pItemsColumns->AddItem(_T("Two"), 1, 1);
	m_pItemsColumns->AddItem(_T("Three"), 2, 2);
	m_pItemsColumns->AddItem(_T("Left"), 3, 3);
	m_pItemsColumns->AddItem(_T("Right"), 4, 4);
	m_pItemsColumns->SetItemSize(CSize(0, 44));
}

BOOL CMainFrame::CreateMiniToolBar()
{
	CXTPCommandBars* pCommandBars = GetCommandBars();

	CXTPMiniToolBar* pMiniToolBar = CXTPMiniToolBar::CreateMiniToolBar(pCommandBars);
	pMiniToolBar->SetBarID(IDR_MENU_MINITOOLBAR);
	pMiniToolBar->SetTitle(_T("MiniBar"));

	CXTPControlComboBox* pComboFont = new CXTPControlComboBox();
	pMiniToolBar->GetControls()->Add(pComboFont, ID_FONT_FACE);

	pComboFont->SetDropDownListStyle();
	pComboFont->EnableAutoComplete();
	pComboFont->SetWidth(XTP_DPI_X(64));
	
	CXTPPopupBar* pPopupBarGallery = CXTPControlComboBoxGalleryPopupBar::CreateComboBoxGalleryPopupBar(pCommandBars);
	
	pComboFont->SetCommandBar(pPopupBarGallery);
	
	CXTPControlGallery* pControlGallery = new CXTPControlGallery();
	pControlGallery->SetControlSize(CSize(290, 508));
	pControlGallery->SetResizable(FALSE, TRUE);
	pControlGallery->ShowLabels(TRUE);
	pControlGallery->SetItems(m_pItemsFontFace);
	
	pPopupBarGallery->GetControls()->Add(pControlGallery, ID_GALLERY_FONTFACE);
	
	pPopupBarGallery->InternalRelease();

	pComboFont = new CXTPControlComboBox();
	pMiniToolBar->GetControls()->Add(pComboFont, ID_FONT_SIZE);

	pComboFont->SetDropDownListStyle();
	pComboFont->SetWidth(XTP_DPI_X(45));
	
	pPopupBarGallery = CXTPControlComboBoxGalleryPopupBar::CreateComboBoxGalleryPopupBar(pCommandBars);
	
	pComboFont->SetCommandBar(pPopupBarGallery);
	
	pControlGallery = new CXTPControlGallery();
	pControlGallery->SetControlSize(CSize(42, 16 * 17));
	pControlGallery->SetResizable(FALSE, TRUE);
	pControlGallery->SetItems(m_pItemsFontSize);
	
	pPopupBarGallery->GetControls()->Add(pControlGallery, ID_GALLERY_FONTSIZE);
	
	pPopupBarGallery->InternalRelease();
	

	pMiniToolBar->GetControls()->Add(xtpControlButton, ID_FONT_GROW);
	pMiniToolBar->GetControls()->Add(xtpControlButton, ID_FONT_SHRINK);
	pMiniToolBar->GetControls()->Add(xtpControlButtonPopup, ID_STYLES_CHANGE);

	pMiniToolBar->GetControls()->Add(xtpControlButton, ID_CHAR_BOLD);
	pMiniToolBar->GetControls()->Add(xtpControlButton, ID_CHAR_ITALIC);

	pMiniToolBar->GetControls()->Add(xtpControlButton, ID_PARA_LEFT);
	pMiniToolBar->GetControls()->Add(xtpControlButton, ID_PARA_CENTER);
	pMiniToolBar->GetControls()->Add(xtpControlButton, ID_PARA_RIGHT);

	pMiniToolBar->GetControls()->Add(xtpControlButton, ID_PARA_INCREASEINDENT);
	pMiniToolBar->GetControls()->Add(xtpControlButton, ID_PARA_DECREASEINDENT);
	pMiniToolBar->GetControls()->Add(xtpControlButton, ID_INSERT_BULLET);


	pMiniToolBar->GetControls()->CreateOriginalControls();
	
	pCommandBars->GetContextMenus()->Add(pMiniToolBar);
	pMiniToolBar->SetWidth(XTP_DPI_X(23) * 8);

	// Add Simple context menu
	CMenu mnu;
	mnu.LoadMenu(IDR_MENU_CONTEXT);

	pCommandBars->GetContextMenus()->Add(IDR_MENU_CONTEXT, _T("Context Menu"), mnu.GetSubMenu(0));

	return TRUE;
}

void CMainFrame::Reset()
{
	CXTPCommandBars* pCommandBars = GetCommandBars();
	pCommandBars->Remove(pCommandBars->GetMenuBar());

	CreateRibbonBar();

	OnOptionsStyle(m_nRibbonStyle);
	pCommandBars->UpdateCommandBars();
	pCommandBars->RedrawCommandBars();
}

BOOL CMainFrame::CreateRibbonBar()
{
	CXTPCommandBars* pCommandBars = GetCommandBars();

	CMenu menu;
	menu.Attach(::GetMenu(m_hWnd));
	SetMenu(NULL);

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
	pTabHome->SetCustomizeCaption(_T("(Home)"));

	CXTPRibbonGroup* pGroupClipborad = pTabHome->AddGroup(ID_GROUP_CLIPBOARD);
	pGroupClipborad->ShowOptionButton();
	pGroupClipborad->SetIconId(ID_GROUP_BUTTONPOPUP);
	pGroupClipborad->GetControlGroupOption()->SetID(ID_GROUP_CLIPBOARD_OPTION);
	pGroupClipborad->SetControlsCentering();
	
	CXTPControlPopup* pControlPaste = (CXTPControlPopup*)pGroupClipborad->Add(xtpControlSplitButtonPopup, ID_EDIT_PASTE);
	pControlPaste->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_EDIT_PASTE);
	pControlPaste->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_EDIT_PASTE_SPECIAL);
	CXTPControl* pControlCut = pGroupClipborad->Add(xtpControlButton, ID_EDIT_CUT);
	pControlCut->SetKeyboardTip(_T("X"));

	pGroupClipborad->Add(xtpControlButton, ID_EDIT_COPY);	
	pGroupClipborad->Add(xtpControlButton, ID_FORMAT_PAINTER);
	pControlPaste->SetKeyboardTip(_T("V"));

	CXTPRibbonGroup* pGroupFont = pTabHome->AddGroup(ID_GROUP_FONT);
	pGroupFont->SetControlsGrouping();
	pGroupFont->ShowOptionButton();
	pGroupFont->GetControlGroupOption()->SetID(ID_GROUP_FONT_OPTION);

	CXTPControlComboBox* pComboFont = new CXTPControlComboBox();
	pGroupFont->Add(pComboFont, ID_FONT_FACE);

	pComboFont->SetDropDownListStyle();
	pComboFont->EnableAutoComplete();
	pComboFont->SetWidth(XTP_DPI_X(82));
	
	CXTPPopupBar* pPopupBarGallery = CXTPControlComboBoxGalleryPopupBar::CreateComboBoxGalleryPopupBar(pCommandBars);
	
	pComboFont->SetCommandBar(pPopupBarGallery);
	
	CXTPControlGallery* pControlGallery = new CXTPControlGallery();
	pControlGallery->SetControlSize(CSize(290, 508));
	pControlGallery->SetResizable(FALSE, TRUE);
	pControlGallery->ShowLabels(TRUE);
	pControlGallery->SetItems(m_pItemsFontFace);
	
	pPopupBarGallery->GetControls()->Add(pControlGallery, ID_GALLERY_FONTFACE);
	
	pPopupBarGallery->InternalRelease();

	pComboFont = new CXTPControlComboBox();
	pGroupFont->Add(pComboFont, ID_FONT_SIZE);

	pComboFont->SetDropDownListStyle();
	pComboFont->SetWidth(XTP_DPI_X(43));
	
	pPopupBarGallery = CXTPControlComboBoxGalleryPopupBar::CreateComboBoxGalleryPopupBar(pCommandBars);
	
	pComboFont->SetCommandBar(pPopupBarGallery);
	
	pControlGallery = new CXTPControlGallery();
	pControlGallery->SetControlSize(CSize(42, 16 * 17));
	pControlGallery->SetResizable(FALSE, TRUE);
	pControlGallery->SetItems(m_pItemsFontSize);
	
	pPopupBarGallery->GetControls()->Add(pControlGallery, ID_GALLERY_FONTSIZE);
	
	pPopupBarGallery->InternalRelease();
	

	CXTPControl* pControl = pGroupFont->Add(xtpControlButton, ID_FONT_GROW);
	pGroupFont->Add(xtpControlButton, ID_FONT_SHRINK);

	pControl = pGroupFont->Add(xtpControlPopup, ID_TEXT_CHANGECASE);
	pControl->SetStyle(xtpButtonIcon);
	pControl->SetBeginGroup(TRUE);

	pControl = pGroupFont->Add(xtpControlButton, ID_FONT_CLEAR);
	pControl->SetBeginGroup(TRUE);


	pGroupFont->Add(xtpControlButton, ID_CHAR_BOLD)->SetBeginGroup(TRUE);
	pGroupFont->Add(xtpControlButton, ID_CHAR_ITALIC);
	pGroupFont->Add(xtpControlSplitButtonPopup, ID_CHAR_UNDERLINE);	

	pGroupFont->Add(xtpControlButton, ID_CHAR_STRIKETHROUGH);
	pGroupFont->Add(xtpControlButton, ID_TEXT_SUBSCRIPT)->SetBeginGroup(TRUE);
	pGroupFont->Add(xtpControlButton, ID_TEXT_SUPERSCRIPT);	


	pControl = pGroupFont->Add(xtpControlPopup, ID_TEXT_EFFECTS);
	pControl->SetStyle(xtpButtonIcon);
	pControl->SetBeginGroup(TRUE);
	CXTPControlPopupColor* pPopupColor = (CXTPControlPopupColor*)pGroupFont->Add(new CXTPControlPopupColor(), ID_TEXT_HIGHLIGHTCOLOR);
	CXTPPopupBar* pColorBar = CXTPPopupBar::CreatePopupBar(GetCommandBars());
	CMenu menuColor;
	menuColor.LoadMenu(ID_TEXT_HIGHLIGHTCOLOR);
	pColorBar->LoadMenu(menuColor.GetSubMenu(0));
	pPopupColor->SetCommandBar(pColorBar);
	pColorBar->InternalRelease();


	pPopupColor = (CXTPControlPopupColor*)pGroupFont->Add(new CXTPControlPopupColor, ID_TEXT_COLOR);
	
	pColorBar = CXTPPopupBar::CreatePopupBar(GetCommandBars());
	
	CXTPControlButton *pButton = (CXTPControlButton *)pColorBar->GetControls()->Add(new CXTPControlButton(), XTP_IDS_AUTOMATIC);

	pControlGallery = new CXTPControlGallery();
	pControlGallery->ShowLabels(TRUE);
	pControlGallery->ShowScrollBar(FALSE);
	pControlGallery->SetItems(m_pItemsFontTextColor);
	
	pControlGallery->SetControlSize(7, 10, CSize(17, 15));

	pControlGallery->SetHeight(pControlGallery->GetHeight() + XTP_DPI_Y(2)); // + additional padding

	pColorBar->GetControls()->Add(pControlGallery, ID_GALLERY_FONTTEXTCOLOR);

	pColorBar->GetControls()->Add(new CXTPControlButton(), XTP_IDS_MORE_COLORS);
	
	pPopupColor->SetCommandBar(pColorBar);
	pColorBar->EnableCustomization(FALSE);
	pColorBar->InternalRelease();


	CXTPRibbonGroup* pGroupParagraph = pTabHome->AddGroup(ID_GROUP_PARAGRAPH);
	pGroupParagraph->SetControlsGrouping();
	pGroupParagraph->ShowOptionButton();
	pGroupParagraph->GetControlGroupOption()->SetID(ID_GROUP_PARAGRAPH_OPTION);
	
	pGroupParagraph->Add(xtpControlSplitButtonPopup, ID_INSERT_BULLET);
	pGroupParagraph->Add(xtpControlSplitButtonPopup, ID_INSERT_NUMBERING);
	pGroupParagraph->Add(xtpControlSplitButtonPopup, ID_INSERT_LIST);
	pGroupParagraph->Add(xtpControlButton, ID_PARA_DECREASEINDENT)->SetBeginGroup(TRUE);
	pGroupParagraph->Add(xtpControlButton, ID_PARA_INCREASEINDENT);

	pGroupParagraph->Add(xtpControlButton, ID_PARA_SORT)->SetBeginGroup(TRUE);	
	pGroupParagraph->Add(xtpControlButton, ID_PARA_SHOWMARKS)->SetBeginGroup(TRUE);
	
	pGroupParagraph->Add(xtpControlButton, ID_PARA_LEFT)->SetBeginGroup(TRUE);
	pGroupParagraph->Add(xtpControlButton, ID_PARA_CENTER);
	pGroupParagraph->Add(xtpControlButton, ID_PARA_RIGHT);
	pGroupParagraph->Add(xtpControlButton, ID_PARA_JUSTIFY);

	pGroupParagraph->Add(xtpControlButtonPopup, ID_PARA_LINESPACING)->SetBeginGroup(TRUE);
	pGroupParagraph->Add(xtpControlSplitButtonPopup, ID_PARA_SHADING)->SetBeginGroup(TRUE);
	pGroupParagraph->Add(xtpControlSplitButtonPopup, ID_BORDERS_NOBORDER)->SetBeginGroup(TRUE);

	CXTPRibbonGroup* pGroupStyles = pTabHome->AddGroup(ID_GROUP_STYLES);
	pGroupStyles->SetControlsCentering(TRUE);
	
	pControlGallery = (CXTPControlGallery*)pGroupStyles->Add(new CXTPControlGallery(), ID_GALLERY_STYLES);	

	pControlGallery->SetControlSize(CSize(234, 60));
	pControlGallery->SetResizable();
	pControlGallery->SetItemsMargin(0, XTP_DPI_Y(1), 0, XTP_DPI_Y(1));
	pControlGallery->ShowLabels(FALSE);
	pControlGallery->ShowBorders(TRUE);
	pControlGallery->SetItems(m_pItemsStyles);
	
	CMenu menuQuickStyles;
	menuQuickStyles.LoadMenu(ID_STYLES_QUICKSTYLES);
	
	CXTPPopupBar* pPopupBar = CXTPPopupBar::CreatePopupBar(GetCommandBars());
	pPopupBar->LoadMenu(menuQuickStyles.GetSubMenu(0));
	
	pControlGallery->SetCommandBar(pPopupBar);
	pPopupBar->EnableAnimation();
	pPopupBar->InternalRelease();
	
	pGroupStyles->Add(xtpControlButtonPopup, ID_STYLES_CHANGE);

	CXTPRibbonGroup* pGroupFind = pTabHome->AddGroup(ID_GROUP_FIND);
	
	CXTPControlPopup* pControlFind = (CXTPControlPopup*)pGroupFind->Add(xtpControlSplitButtonPopup, ID_EDIT_FIND);
	pControlFind->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_EDIT_FIND);
	pControlFind->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_EDIT_GOTO);
	pGroupFind->Add(xtpControlButton, ID_EDIT_REPLACE);
	
	CXTPControlPopup* pControlSelect = (CXTPControlPopup*)pGroupFind->Add(xtpControlPopup, ID_EDIT_SELECT);
	pGroupFind->SetIconId(ID_GROUP_BUTTONPOPUP);
	pControlSelect->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_EDIT_SELECT_ALL);
	pControlSelect->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_EDIT_SELECT_OBJECTS);
	pControlSelect->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_EDIT_SELECT_MULTIPLE_OBJECTS);
	pControlSelect->SetFlags(xtpFlagManualUpdate);


	CXTPRibbonTab* pTabInsert = pRibbonBar->AddTab(ID_TAB_INSERT);

	// pre 2013
	CXTPRibbonGroup* pGroupShapes = pTabInsert->AddGroup(ID_GROUP_SHAPES);
	pControlGallery = (CXTPControlGallery*)pGroupShapes->Add(new CXTPControlGallery(), ID_GALLERY_SHAPES);	
	pControlGallery->SetControlSize(CSize(138, 60));
	pControlGallery->SetResizable();
	pControlGallery->ShowBorders(TRUE);
	pControlGallery->SetItemsMargin(0, -XTP_DPI_Y(1), 0, -XTP_DPI_Y(1));
	pControlGallery->ShowLabels(FALSE);
	pControlGallery->SetItems(m_pItemsShapes);

	CMenu menuShapesOld;
	menuShapesOld.LoadMenu(ID_INSERT_SHAPES);
	
	pPopupBar = CXTPPopupBar::CreatePopupBar(GetCommandBars());
	pPopupBar->LoadMenu(menuShapesOld.GetSubMenu(0));
	
	pControlGallery->SetCommandBar(pPopupBar);
	pPopupBar->EnableAnimation();
	pPopupBar->InternalRelease();
	// end pre 2013

	CXTPRibbonGroup* pGroupPages = pTabInsert->AddGroup(ID_GROUP_PAGES);
	pGroupPages->SetIconId(ID_GROUP_BUTTONPOPUP);
	pGroupPages->Add(xtpControlSplitButtonPopup, ID_PAGES_COVER);
	pGroupPages->Add(xtpControlButton, ID_PAGES_NEW);
	pGroupPages->Add(xtpControlButton, ID_PAGES_BREAK);
	pGroupPages->ShowOptionButton();
	
	CXTPRibbonGroup* pGroupTable = pTabInsert->AddGroup(ID_GROUP_TABLE);
	pGroupTable->Add(xtpControlButtonPopup, ID_TABLE_NEW);

	CXTPRibbonGroup* pGroupIllustrations = pTabInsert->AddGroup(ID_GROUP_ILLUSTRATIONS);

	// pre-2013
	pGroupIllustrations->Add(xtpControlSplitButtonPopup, ID_ILLUSTRATION_PICTURE);
	// pre-2013
	pGroupIllustrations->Add(xtpControlButton, ID_ILLUSTRATION_GRAPHIC);

	pGroupIllustrations->Add(xtpControlButton, ID_ILLUSTRATION_PICTURES);
	pGroupIllustrations->Add(xtpControlButton, ID_ILLUSTRATION_ONLINEPICTURES);
	CXTPControlPopup* pControlShapes = (CXTPControlPopup*)pGroupIllustrations->Add(xtpControlSplitButtonPopup, ID_ILLUSTRATION_SHAPES);

	CMenu menuShapes;
	menuShapes.LoadMenu(ID_INSERT_SHAPES);
	
	pPopupBar = CXTPPopupBar::CreatePopupBar(GetCommandBars());
	pPopupBar->LoadMenu(menuShapes.GetSubMenu(0));
	
	pControlShapes->SetCommandBar(pPopupBar);
	pPopupBar->EnableAnimation();
	pPopupBar->InternalRelease();

	pGroupIllustrations->Add(xtpControlButton, ID_ILLUSTRATION_SMARTART);
	pGroupIllustrations->Add(xtpControlButton, ID_ILLUSTRATION_CHART);
	pGroupIllustrations->Add(xtpControlSplitButtonPopup, ID_ILLUSTRATION_SCREENSHOT);

	CXTPRibbonGroup* pGroupLinks = pTabInsert->AddGroup(ID_GROUP_LINKS);
	pGroupLinks->Add(xtpControlButton, ID_INSERT_HYPERLINK);
	pGroupLinks->Add(xtpControlButton, ID_INSERT_BOOKMARK);
	pGroupLinks->Add(xtpControlButton, ID_INSERT_CROSS_REFERENCE);

	CXTPRibbonGroup* pGroupMedia = pTabInsert->AddGroup(ID_GROUP_MEDIA);
	pGroupMedia->Add(xtpControlButton, ID_INSERT_ONLINEVIDEO);

	CXTPRibbonGroup* pGroupHeader = pTabInsert->AddGroup(ID_GROUP_HEADERFOOTERS);
	pGroupHeader->Add(xtpControlButtonPopup, ID_INSERT_HEADER);
	pGroupHeader->Add(xtpControlButtonPopup, ID_INSERT_FOOTER);
	pGroupHeader->Add(xtpControlButtonPopup, ID_INSERT_PAGENUMBER);

	CXTPRibbonGroup* pGroupText = pTabInsert->AddGroup(ID_GROUP_TEXT);
	pGroupText->Add(xtpControlButtonPopup, ID_TEXT_TEXTBOX);
	pGroupText->Add(xtpControlSplitButtonPopup, ID_TEXT_PARTS);
	pGroupText->Add(xtpControlButtonPopup, ID_TEXT_WORDART);
	pGroupText->Add(xtpControlButtonPopup, ID_TEXT_DROPCAP);
	pGroupText->Add(xtpControlSplitButtonPopup, ID_TEXT_SIGNATURE);
	pGroupText->Add(xtpControlButton, ID_TEXT_DATETIME);
	pGroupText->Add(xtpControlSplitButtonPopup, ID_TEXT_INSERTOBJECT);

	CXTPRibbonGroup* pGroupSymbols = pTabInsert->AddGroup(ID_GROUP_SYMBOLS);
	pGroupSymbols->Add(xtpControlButtonPopup, ID_SYMBOL_EQUATIONS);
	pGroupSymbols->Add(xtpControlButtonPopup, ID_SYMBOL_SYMBOL);

	//pGroupSymbols->GetControlGroupPopup()->SetIconId(ID_SYMBOL_SYMBOL);


	CXTPRibbonTab* pTabPageLayout = pRibbonBar->AddTab(ID_TAB_PAGELAYOUT);

	CXTPControlPopup* pControlPopup = NULL;
	CXTPRibbonGroup* pGroupThemes = NULL;

	pGroupThemes = pTabPageLayout->AddGroup(ID_GROUP_THEMES);
	pGroupThemes->SetIconId(ID_GROUP_BUTTONPOPUP);
	pGroupThemes->Add(xtpControlSplitButtonPopup, ID_THEMES_THEMES);
	pGroupThemes->Add(xtpControlPopup, ID_THEMES_COLORS);
	pGroupThemes->Add(xtpControlPopup, ID_THEMES_FONTS);
	pControlPopup = (CXTPControlPopup*)pGroupThemes->Add(xtpControlPopup, ID_THEMES_EFFECTS);
	pControlPopup->GetCommandBar()->GetControls()->Add(new CXTPControlLabel(), ID_THEMES_BUILTIN);
	pControlPopup->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_THEMES_OFFICE);

	CXTPRibbonGroup* pGroupPageSetup = pTabPageLayout->AddGroup(ID_GROUP_PAGESETUP);
	pGroupPageSetup->SetIconId(ID_GROUP_BUTTONPOPUP);
	pGroupPageSetup->Add(xtpControlPopup, ID_PAGE_MARGINS);
	pGroupPageSetup->Add(xtpControlPopup, ID_PAGE_ORIENTATION);
	pGroupPageSetup->Add(xtpControlPopup, ID_PAGE_SIZE);
	pControlPopup = (CXTPControlPopup*)pGroupPageSetup->Add(xtpControlPopup, ID_PAGE_COLUMNS);

	pControlGallery = (CXTPControlGallery*)pControlPopup->GetCommandBar()->GetControls()->Add(new CXTPControlGallery(), ID_GALLERY_COLUMNS);	

	pControlGallery->SetControlSize(CSize(140, 44 * 5));
	pControlGallery->ShowScrollBar(FALSE);
	pControlGallery->SetItems(m_pItemsColumns);
	pControlGallery->SetStyle(xtpButtonIconAndCaption);

	pGroupPageSetup->Add(xtpControlPopup, ID_PAGE_BREAKS);
	pGroupPageSetup->Add(xtpControlPopup, ID_PAGE_LINENUMBERS);
	pGroupPageSetup->Add(xtpControlPopup, ID_PAGE_HYPHENATATION);

	CXTPRibbonGroup* pGroupPageBackground = pTabPageLayout->AddGroup(ID_GROUP_PAGEBACKGROUND);
	pGroupPageBackground->Add(xtpControlPopup, ID_PAGE_WATERMARK);
	pGroupPageBackground->Add(xtpControlPopup, ID_PAGE_COLOR);
	pGroupPageBackground->Add(xtpControlButton, ID_PAGE_BORDERS);

	CXTPRibbonGroup* pGroupPageParagraph = pTabPageLayout->AddGroup(ID_GROUP_PAGEPARAGRAPH);
	pGroupPageParagraph->GetControlGroupPopup()->SetIconId(ID_PARA_INCREASEINDENT);

	pControl = pGroupPageParagraph->Add(xtpControlLabel, ID_PARAGRAPH_INDENT);
	pControl->SetID(0);
	pControl->SetStyle(xtpButtonCaption);

	CXTPControlEdit* pControlEdit = (CXTPControlEdit*)pGroupPageParagraph->Add(xtpControlEdit, ID_PARAGRAPH_INDENTLEFT);
	pControlEdit->SetWidth(XTP_DPI_X(133));
	pControlEdit->ShowSpinButtons();
	pControlEdit->SetStyle(xtpButtonIcon);

	pControlEdit = (CXTPControlEdit*)pGroupPageParagraph->Add(xtpControlEdit, ID_PARAGRAPH_INDENTRIGHT);
	pControlEdit->SetWidth(XTP_DPI_X(133));
	pControlEdit->ShowSpinButtons();
	pControlEdit->SetStyle(xtpButtonIcon);

	pControl = pGroupPageParagraph->Add(xtpControlLabel, ID_PARAGRAPH_SPACING);
	pControl->SetBeginGroup(TRUE);
	pControl->SetID(0);
	pControl->SetStyle(xtpButtonCaption);

	pControlEdit = (CXTPControlEdit*)pGroupPageParagraph->Add(xtpControlEdit, ID_PARAGRAPH_SPACINGBEFORE);
	pControlEdit->SetWidth(XTP_DPI_X(133));
	pControlEdit->ShowSpinButtons();
	pControlEdit->SetStyle(xtpButtonIcon);

	pControlEdit = (CXTPControlEdit*)pGroupPageParagraph->Add(xtpControlEdit, ID_PARAGRAPH_SPACINGAFTER);
	pControlEdit->SetWidth(XTP_DPI_X(133));
	pControlEdit->ShowSpinButtons();
	pControlEdit->SetStyle(xtpButtonIcon);

	CXTPRibbonGroup* pGroupArrange = pTabPageLayout->AddGroup(ID_GROUP_ARRANGE);
	pGroupArrange->Add(xtpControlPopup, ID_ARRANGE_POSITION);
	pGroupArrange->Add(xtpControlPopup, ID_ARRANGE_TEXTWRAPPING);
	pGroupArrange->Add(xtpControlPopup, ID_ARRANGE_FRONT);
	pGroupArrange->Add(xtpControlPopup, ID_ARRANGE_BACK);
	pGroupArrange->Add(xtpControlButton, ID_ARRANGE_SELECTIONPANE);

	pGroupArrange->Add(xtpControlPopup, ID_ARRANGE_ALIGN);
	pControlPopup = (CXTPControlPopup*)pGroupArrange->Add(xtpControlPopup, ID_ARRANGE_GROUP);
	pControlPopup->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_ARRANGE_GROUP);
	pControlPopup->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_ARRANGE_UNGROUP);

	pGroupArrange->Add(xtpControlPopup, ID_ARRANGE_ROTATE);


	CXTPRibbonTab* pTabReferences = pRibbonBar->AddTab(ID_TAB_REFERENCES);

	pTabReferences->AddGroup(ID_GROUP_TABLEOFCONTENTS);
	pTabReferences->AddGroup(ID_GROUP_FOOTNOTES);
	pTabReferences->AddGroup(ID_GROUP_CAPTIONS);
	pTabReferences->AddGroup(ID_GROUP_INDEX);


	CXTPRibbonTab* pTabMailings = pRibbonBar->AddTab(ID_TAB_MAILINGS);

	CXTPRibbonGroup* pGroupCreate = pTabMailings->AddGroup(ID_GROUP_CREATE);
	pGroupCreate->Add(xtpControlButton, ID_MAIL_ENVELOPES);
	pGroupCreate->Add(xtpControlButton, ID_MAIL_LABELS);

	CXTPRibbonGroup* pGroupStartMailMerge = pTabMailings->AddGroup(ID_GROUP_STARTMAILMERGE);
	pGroupStartMailMerge->Add(xtpControlPopup, ID_MAIL_STARTMAILMERGE);
	pGroupStartMailMerge->Add(xtpControlPopup, ID_MAIL_SELECTRECIPIENTS);
	pGroupStartMailMerge->Add(xtpControlButton, ID_MAIL_EDITRECIPIENTLIST);

	CXTPRibbonGroup* pGroupWriteInSetFields = pTabMailings->AddGroup(ID_GROUP_WRITEINSETFIELDS);
	pGroupWriteInSetFields->Add(xtpControlButton, ID_MAIL_HIGHLIGHT);
	pGroupWriteInSetFields->Add(xtpControlButton, ID_MAIL_ADDRESSBLOCK);
	pGroupWriteInSetFields->Add(xtpControlButton, ID_MAIL_GREETINGLINE);
	pGroupWriteInSetFields->Add(xtpControlPopup, ID_MAIL_INSERMERGEFIELD);
	pGroupWriteInSetFields->Add(xtpControlPopup, ID_MAIL_RULES);
	pGroupWriteInSetFields->Add(xtpControlButton, ID_MAIL_MATCHFIELDS);
	pGroupWriteInSetFields->Add(xtpControlButton, ID_MAIL_UPDATELABELS);

	CXTPRibbonGroup* pGroupPreviewReults = pTabMailings->AddGroup(ID_GROUP_PREVIEWRESULTS);
	pGroupPreviewReults->SetControlsGrouping(TRUE);
	pGroupPreviewReults->AllowReduce(0);
	
	pGroupPreviewReults->Add(xtpControlButton, ID_MAIL_PREVIEWRESULTS);

	pControl = pGroupPreviewReults->Add(xtpControlButton, ID_MAIL_FIRSTRECORD);
	pControl->SetStyle(xtpButtonIcon);
	pControl->SetBeginGroup(TRUE);
	pControl = pGroupPreviewReults->Add(xtpControlButton, ID_MAIL_PREVIOUSRECORD);
	pControl->SetStyle(xtpButtonIcon);
	pControlEdit = (CXTPControlEdit*)pGroupPreviewReults->Add(xtpControlEdit, ID_MAIL_RECORD);
	pControlEdit->SetWidth(XTP_DPI_X(40));
	pControl = pGroupPreviewReults->Add(xtpControlButton, ID_MAIL_NEXTRECORD);
	pControl->SetStyle(xtpButtonIcon);
	pControl = pGroupPreviewReults->Add(xtpControlButton, ID_MAIL_LASTRECORD);
	pControl->SetStyle(xtpButtonIcon);

	pControl = pGroupPreviewReults->Add(xtpControlButton, ID_MAIL_FINDRECIPIENT);
	pControl->SetBeginGroup(TRUE);
	pControl = pGroupPreviewReults->Add(xtpControlButton, ID_MAIL_CHECKFORERRORS);
	pControl->SetBeginGroup(TRUE);

	CXTPRibbonGroup* pGroupFinish = pTabMailings->AddGroup(ID_GROUP_FINISH);
	pGroupFinish->Add(xtpControlPopup, ID_MAIL_FINISHANDMERGE);


	CXTPRibbonTab* pTabReview = pRibbonBar->AddTab(ID_TAB_REVIEW);
	pTabReview->SetContextTab(xtpRibbonTabContextColorPurple);

	CXTPRibbonGroup* pGroupProofing = pTabReview->AddGroup(ID_GROUP_PROOFING);
	pGroupProofing->Add(xtpControlButton, ID_REVIEW_SPELLING);
	//pGroupProofing->Add(xtpControlButton, ID_REVIEW_DEFINE);
	pGroupProofing->Add(xtpControlButton, ID_REVIEW_THESAURUS);
	pGroupProofing->Add(xtpControlButton, ID_REVIEW_WORDCOUNT);
	
	CXTPRibbonGroup* pGroupLanguage = pTabReview->AddGroup(ID_GROUP_LANGUAGE);
	pGroupLanguage->Add(xtpControlPopup, ID_REVIEW_TRANSLATE);
	pGroupLanguage->Add(xtpControlPopup, ID_REVIEW_LANGUAGE);

	CXTPRibbonGroup* pGroupComments = pTabReview->AddGroup(ID_GROUP_COMMENTS);
	pGroupComments->Add(xtpControlButton, ID_REVIEW_NEWCOMMENT);
	pGroupComments->Add(xtpControlPopup, ID_REVIEW_DELETE);
	pGroupComments->Add(xtpControlButton, ID_REVIEW_PREVIOUSCOMMENT);
	pGroupComments->Add(xtpControlButton, ID_REVIEW_NEXTCOMMENT);
	pGroupComments->Add(xtpControlButton, ID_REVIEW_SHOWCOMMENTS);

	CXTPRibbonGroup* pGroupTracking = pTabReview->AddGroup(ID_GROUP_TRACKING);
	pGroupTracking->Add(xtpControlPopup, ID_REVIEW_TRACKCHANGES);
	pGroupTracking->Add(xtpControlPopup, ID_REVIEW_SIMPLEMARKUP);
	pGroupTracking->Add(xtpControlPopup, ID_REVIEW_SHOWMARKUP);
	pGroupTracking->Add(xtpControlPopup, ID_REVIEW_REVIEWINGPANE);

	CXTPRibbonGroup* pGroupChanges = pTabReview->AddGroup(ID_GROUP_CHANGES);
	pGroupChanges->Add(xtpControlPopup, ID_REVIEW_ACCEPT);
	pGroupChanges->Add(xtpControlPopup, ID_REVIEW_REJECT);
	pGroupChanges->Add(xtpControlButton, ID_REVIEW_PREVIOUS);
	pGroupChanges->Add(xtpControlButton, ID_REVIEW_NEXT);

	CXTPRibbonGroup* pGroupCompare = pTabReview->AddGroup(ID_GROUP_COMPARE);
	pGroupCompare->Add(xtpControlPopup, ID_REVIEW_COMPARE);

	CXTPRibbonGroup* pGroupProtect = pTabReview->AddGroup(ID_GROUP_PROTECT);
	pGroupProtect->Add(xtpControlPopup, ID_REVIEW_BLOCKAUTHORS);
	pGroupProtect->Add(xtpControlButton, ID_REVIEW_RESTRICTEDITING);

	CXTPRibbonTab* pTabView = pRibbonBar->AddTab(ID_TAB_VIEW);

	pTabView->AddGroup(ID_GROUP_DOCUMENTVIEWS);


	CXTPRibbonGroup* pGroupShowHide = pTabView->AddGroup(ID_GROUP_SHOWHIDE);
	pGroupShowHide->Add(xtpControlCheckBox, ID_VIEW_RULER);
	pGroupShowHide->Add(xtpControlCheckBox, ID_VIEW_GRIDLINES);
	pGroupShowHide->Add(xtpControlCheckBox, ID_VIEW_PROPERTIES);
	pGroupShowHide->Add(xtpControlCheckBox, ID_VIEW_DOCUMENTMAP);
	pGroupShowHide->Add(xtpControlCheckBox, ID_VIEW_STATUS_BAR);
	pGroupShowHide->Add(xtpControlCheckBox, ID_VIEW_MESSAGE_BAR);

	pTabView->AddGroup(ID_GROUP_ZOOM);
	CXTPRibbonGroup* pGroup = pTabView->AddGroup(ID_GROUP_WINDOW);
	pGroup->GetControlGroupPopup()->SetIconId(ID_WINDOW_NEW);

	CXTPRibbonTab* pTab;

	pTab = pRibbonBar->AddTab(ID_TAB_TABLEDESIGN);
	pTab->SetContextTab(xtpRibbonTabContextColorYellow, _T("Table Tools"));
	pTab = pRibbonBar->AddTab(ID_TAB_TABLELAYOUT);
	pTab->SetContextTab(xtpRibbonTabContextColorYellow, _T("Table Tools"));
	
	pTab = pRibbonBar->AddTab(ID_TAB_CHARTDESIGN);
	pTab->SetContextTab(xtpRibbonTabContextColorGreen, ID_TAB_CONTEXTCHART);
	//pTab = pRibbonBar->AddTab(ID_TAB_CHARTLAYOUT);
	//pTab->SetContextTab(xtpRibbonTabContextColorGreen, ID_TAB_CONTEXTCHART);
	pTab = pRibbonBar->AddTab(ID_TAB_CHARTFORMAT);
	pTab->SetContextTab(xtpRibbonTabContextColorGreen, ID_TAB_CONTEXTCHART);

	pGroupShapes = pTab->AddGroup(ID_GROUP_SHAPES);
	pControlGallery = (CXTPControlGallery*)pGroupShapes->Add(new CXTPControlGallery(), ID_GALLERY_SHAPES);	
	pControlGallery->SetControlSize(CSize(138, 60));
	pControlGallery->SetResizable();
	pControlGallery->ShowBorders(TRUE);
	pControlGallery->SetItemsMargin(0, -XTP_DPI_Y(1), 0, -XTP_DPI_Y(1));
	pControlGallery->ShowLabels(FALSE);
	pControlGallery->SetItems(m_pItemsShapes);

	CMenu menuShapesOld2;
	menuShapesOld2.LoadMenu(ID_INSERT_SHAPES);
	
	pPopupBar = CXTPPopupBar::CreatePopupBar(GetCommandBars());
	pPopupBar->LoadMenu(menuShapesOld2.GetSubMenu(0));
	
	pControlGallery->SetCommandBar(pPopupBar);
	pPopupBar->EnableAnimation();
	pPopupBar->InternalRelease();

	pControlShapes = (CXTPControlPopup*)pGroupShapes->Add(xtpControlSplitButtonPopup, ID_ILLUSTRATION_SHAPES);

	CMenu menuShapes3;
	menuShapes3.LoadMenu(ID_INSERT_SHAPES);
	
	pPopupBar = CXTPPopupBar::CreatePopupBar(GetCommandBars());
	pPopupBar->LoadMenu(menuShapes3.GetSubMenu(0));	
	pControlShapes->SetCommandBar(pPopupBar);
	pPopupBar->EnableAnimation();
	pPopupBar->InternalRelease();

	pTab = pRibbonBar->AddTab(ID_TAB_PICTUREFORMAT);
	pTab->SetContextTab(xtpRibbonTabContextColorPurple, _T("Picture Tools"));
	CXTPRibbonGroup* pGroupFormatArrange = pTab->AddGroup(ID_GROUP_ARRANGE);
	pGroupFormatArrange->Add(xtpControlPopup, ID_ARRANGE_POSITION);
	pGroupFormatArrange->Add(xtpControlPopup, ID_ARRANGE_TEXTWRAPPING);
	pGroupFormatArrange->Add(xtpControlPopup, ID_ARRANGE_FRONT);
	pGroupFormatArrange->Add(xtpControlPopup, ID_ARRANGE_BACK);
	pGroupFormatArrange->Add(xtpControlButton, ID_ARRANGE_SELECTIONPANE);

	pGroupFormatArrange->Add(xtpControlPopup, ID_ARRANGE_ALIGN);
	pControlPopup = (CXTPControlPopup*)pGroupFormatArrange->Add(xtpControlPopup, ID_ARRANGE_GROUP);
	pControlPopup->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_ARRANGE_GROUP);
	pControlPopup->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_ARRANGE_UNGROUP);

	pGroupFormatArrange->Add(xtpControlPopup, ID_ARRANGE_ROTATE);

	CXTPControl* pControlExpand = pRibbonBar->GetControls()->Add(xtpControlButton, ID_RIBBON_EXPAND);
	pControlExpand->SetFlags(xtpFlagRightAlign);

	CXTPControl* pControlMinimize = pRibbonBar->GetControls()->Add(xtpControlButton, ID_RIBBON_MINIMIZE);
	pControlMinimize->SetFlags(xtpFlagRightAlign);

	
	CXTPControlPopup* pControlOptions = (CXTPControlPopup*)pRibbonBar->GetControls()->Add(xtpControlPopup, -1);
	pControlOptions->SetFlags(xtpFlagRightAlign);
	CMenu mnuOptions;
	mnuOptions.LoadMenu(IDR_MENU_OPTIONS);
	pControlOptions->SetCommandBar(mnuOptions.GetSubMenu(0));
	pControlOptions->SetCaption(_T("Options"));
	

	CXTPControl* pControlAbout = pRibbonBar->GetControls()->Add(xtpControlButton, ID_APP_ABOUT);
	pControlAbout->SetFlags(xtpFlagRightAlign | xtpFlagManualUpdate);

	pRibbonBar->GetQuickAccessControls()->Add(xtpControlButton, ID_FILE_NEW)->SetHideFlag(xtpHideCustomize, TRUE);
	pRibbonBar->GetQuickAccessControls()->Add(xtpControlButton, ID_FILE_OPEN)->SetHideFlag(xtpHideCustomize, TRUE);
	pRibbonBar->GetQuickAccessControls()->Add(xtpControlButton, ID_FILE_SAVE);
	CXTPControlPopup* pControlUndo = (CXTPControlPopup*)pRibbonBar->GetQuickAccessControls()->Add(xtpControlSplitButtonPopup, ID_EDIT_UNDO);

	pPopupBar = CXTPPopupBar::CreatePopupBar(GetCommandBars());
	pPopupBar->SetShowGripper(FALSE);
	
	pControlUndo->SetCommandBar(pPopupBar);
	
	pControlGallery = new CControlGalleryUndo();
	pControlGallery->SetItems(m_pItemsUndo);
	pControlGallery->SetWidth(XTP_DPI_X(120));
	pControlGallery->ShowScrollBar(FALSE);
	pPopupBar->GetControls()->Add(pControlGallery, ID_EDIT_UNDO);
	
	CXTPControlStatic* pControlListBoxInfo = (CXTPControlStatic*)pPopupBar->GetControls()->Add(new CXTPControlStatic(), ID_EDIT_UNDO);
	pControlListBoxInfo->SetWidth(XTP_DPI_X(120));
	pControlListBoxInfo->SetFlags(xtpFlagSkipFocus);
	
	pPopupBar->InternalRelease();

	pRibbonBar->GetQuickAccessControls()->Add(xtpControlButton, ID_FILE_PRINT);
	pRibbonBar->GetQuickAccessControls()->CreateOriginalControls();


	pRibbonBar->SetCloseable(FALSE);

	pRibbonBar->EnableFrameTheme();

	
	// Call it only if your Ribbon is support customization using Ribbon Customization page.
	pRibbonBar->EnableCustomization(TRUE);

	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CXTPFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.lpszClass = _T("XTPMainFrame");
	CXTPDrawHelpers::RegisterWndClass(AfxGetInstanceHandle(), cs.lpszClass, 
		CS_DBLCLKS, AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CXTPFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CXTPFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers



void CMainFrame::OnEmptyCommandRange(UINT)
{

}

void CMainFrame::OnEmptyCommand()
{

}

void CMainFrame::OnSwitchCommand()
{
	m_bChecked = !m_bChecked;
}

void CMainFrame::OnUpdateSwitchCommand(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bChecked);
}

void CMainFrame::OnViewShowHide(UINT nID)
{
	m_bOptions[nID - ID_VIEW_RULER] ^= 1;
}

void CMainFrame::OnUpdateViewShowHide(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bOptions[pCmdUI->m_nID - ID_VIEW_RULER] ? TRUE : FALSE);

}

void CMainFrame::OnRibbonTabChanged(NMHDR* pNMHDR, LRESULT* pRes) 
{
	NMXTPTABCHANGE* pNMTabChanged = (NMXTPTABCHANGE*)pNMHDR;

	if (pNMTabChanged->pTab)
	{
		TRACE(_T("Tab Changed, Caption = %s\n"), (LPCTSTR)pNMTabChanged->pTab->GetCaption());
	}
	
	*pRes = 0;
}

void CMainFrame::OnRibbonTabChanging(NMHDR* /*pNMHDR*/, LRESULT* pRes) 
{

	*pRes = 0;	
}


void CMainFrame::ShowCustomizeDialog(int nSelectedPage)
{
#if 0
	// Classic Office Customize dialog
	CXTPCustomizeSheet cs(GetCommandBars());

	CXTPRibbonCustomizeQuickAccessPage pageQuickAccess(&cs);
	cs.AddPage(&pageQuickAccess);
	pageQuickAccess.AddCategories(IDR_MAINFRAME);

	CXTPCustomizeKeyboardPage pageKeyboard(&cs);
	cs.AddPage(&pageKeyboard);
	pageKeyboard.AddCategories(IDR_MAINFRAME);

	CXTPCustomizeMenusPage pageMenus(&cs);
	cs.AddPage(&pageMenus);

	CXTPCustomizeOptionsPage pageOptions(&cs);
	cs.AddPage(&pageOptions);

	CXTPCustomizeCommandsPage* pCommands = cs.GetCommandsPage();
	pCommands->AddCategories(IDR_MAINFRAME);

	cs.SetActivePage(nSelectedPage);

	cs.SetResizable();
	cs.DoModal();

#else
	CXTPPropertySheet cs(_T("Options"));
	cs.m_psh.dwFlags |= PSH_NOAPPLYNOW;

	CXTPPropertyPageListNavigator* pList = new CXTPPropertyPageListNavigator();

	XTPListBoxStyle nTheme;
	
	nTheme = xtpListBoxStandard;
	
	switch(XTPPaintManager()->GetCurrentTheme())
	{
	case xtpThemeOffice2013:
		nTheme = xtpListBoxOffice2013;
		break;
	case xtpThemeResource:
	case xtpThemeRibbon:
	case xtpThemeOffice2007System:
		nTheme = xtpListBoxOffice2007;
		break;
	case xtpThemeOfficeXP:
		nTheme = xtpListBoxOfficeXP;
		break;
	default:
		nTheme = xtpListBoxStandard;
		break;								
	}
	
	pList->SetListStyle(nTheme);
	
	cs.SetNavigator(pList);


	CCustomizePageGeneral pageGeneral;
	cs.AddPage(&pageGeneral);

	CCustomizePageRibbon pageCustomizeRibbon(GetCommandBars());;
	cs.AddPage(&pageCustomizeRibbon);
	pageCustomizeRibbon.AddCategories(IDR_MAINFRAME);
	
	CCustomizePageQuickAccessToolbar pageQuickAccess(GetCommandBars());
	cs.AddPage(&pageQuickAccess);
	pageQuickAccess.AddCategories(IDR_MAINFRAME);

	cs.SetResizable();
	cs.DoModal();

#endif
}

void CMainFrame::OnCustomize()
{
	ShowCustomizeDialog(0);
}

void CMainFrame::OnCustomizeQuickAccess()
{
	ShowCustomizeDialog(2);
}


void CMainFrame::OnClose() 
{
#ifndef _SAVE_TO_XML
	SaveCommandBars(_PROFILE_NAME);
#else

	CXTPPropExchangeXMLNode px(FALSE, 0, _T("Settings"));

	if (px.OnBeforeExchange()) 
	{
		CXTPPropExchangeSection pxCommandBars(px.GetSection(_T("CommandBars")));
		XTP_COMMANDBARS_PROPEXCHANGE_PARAM param; 
		param.bSerializeControls = TRUE; 
		param.bSaveOriginalControls = FALSE;
		param.bSerializeOptions = TRUE;
		GetCommandBars()->DoPropExchange(&pxCommandBars, &param);

		px.SaveToFile(m_strIniFileName);
	}
#endif

	
	CXTPFrameWnd::OnClose();
}

int CMainFrame::OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl)
{
	if (lpCreateControl->nID == ID_GALLERY_STYLESET)
	{
		CXTPControlGallery* pControlGallery = new CXTPControlGallery();
		pControlGallery->SetControlSize(CSize(200, 22 * 7 + 2));
		pControlGallery->SetResizable();
		pControlGallery->ShowLabels(TRUE);
		pControlGallery->SetItems(m_pItemsStyleSet);

		lpCreateControl->pControl = pControlGallery;
		return TRUE;
	}

	if (lpCreateControl->nID == ID_GALLERY_COLORS)
	{
		CXTPControlGallery* pControlGallery = new CXTPControlGallery();
		pControlGallery->SetControlSize(CSize(300, 30 * 9 + 2));
		pControlGallery->ShowLabels(TRUE);
		pControlGallery->SetItems(m_pItemsThemeColors);

		lpCreateControl->pControl = pControlGallery;
		return TRUE;
	}
	if (lpCreateControl->nID == ID_GALLERY_FONTBACKCOLOR)
	{
		CXTPControlGallery* pControlGallery = new CXTPControlGallery();
		pControlGallery->SetControlSize(CSize(30 * 5, 30 * 3 + 2));
		pControlGallery->ShowScrollBar(FALSE);
		pControlGallery->SetItems(m_pItemsFontBackColor);

		lpCreateControl->pControl = pControlGallery;
		return TRUE;
	}
	if (lpCreateControl->nID == ID_GALLERY_FONTS)
	{
		CXTPControlGallery* pControlGallery = new CXTPControlGallery();
		pControlGallery->SetControlSize(CSize(250, 60 * 5 + 2 + 20));
		pControlGallery->ShowLabels(TRUE);
		pControlGallery->SetItems(m_pItemsThemeFonts);

		lpCreateControl->pCommandBar->EnableAnimation();

		lpCreateControl->pControl = pControlGallery;
		return TRUE;
	}

	if (lpCreateControl->nID == ID_GALLERY_STYLES)
	{
		CXTPControlGallery* pControlGallery = new CXTPControlGallery();
		pControlGallery->SetControlSize(CSize(235 + 72, 56 * 3 + 2));
		pControlGallery->SetResizable();
		pControlGallery->SetItems(m_pItemsStyles);

		lpCreateControl->pControl = pControlGallery;
		return TRUE;
	}

	if (lpCreateControl->nID == ID_GALLERY_SHAPES)
	{
		CXTPControlGallery* pControlGallery = new CXTPControlGallery();
		pControlGallery->SetControlSize(CSize(200, 200));
		pControlGallery->SetResizable();
		pControlGallery->ShowLabels(TRUE);
		pControlGallery->SetItems(m_pItemsShapes);
		
		lpCreateControl->pControl = pControlGallery;
		return TRUE;
	}

	if (lpCreateControl->nID == ID_CONTENTS_TABLE)
	{		
		lpCreateControl->controlType = xtpControlButtonPopup;
		return TRUE;
	}

	if (lpCreateControl->nID >= ID_OPTIONS_STYLE_OFFICE2007BLUE && lpCreateControl->nID <= ID_OPTIONS_STYLE_OFFICE2007SYSTEM)
	{		
		lpCreateControl->controlType = xtpControlRadioButton;
		return TRUE;
	}

	if (lpCreateControl->nID >= ID_OPTIONS_STYLE_OFFICE2010BLUE && lpCreateControl->nID <= ID_OPTIONS_STYLE_OFFICE2010BLACK)
	{		
		lpCreateControl->controlType = xtpControlRadioButton;
		return TRUE;
	}

	if (lpCreateControl->nID >= ID_OPTIONS_FONT_SYSTEM && lpCreateControl->nID <= ID_OPTIONS_FONT_EXTRALARGE)
	{		
		lpCreateControl->controlType = xtpControlRadioButton;
		return TRUE;
	}

	if (lpCreateControl->nID == ID_FOOTNOTES_NEXT)
	{		
		lpCreateControl->controlType = xtpControlSplitButtonPopup;
		return TRUE;
	}

	if (lpCreateControl->nID == ID_FILE_RECENTDOCUMENTS)
	{		
		lpCreateControl->pControl = new CXTPRibbonControlSystemRecentFileList();
		return TRUE;
	}

	if (lpCreateControl->nID == ID_APP_EXIT || lpCreateControl->nID == ID_APP_OPTIONS)
	{		
		lpCreateControl->pControl = new CXTPRibbonControlSystemPopupBarButton();

		return TRUE;
	}
	if (lpCreateControl->nID == ID_FILE_PRINT && lpCreateControl->nIndex == 5)
	{		
		CXTPControlPopup* pControl = CXTPControlPopup::CreateControlPopup(xtpControlSplitButtonPopup);

		CMenu menu;
		menu.LoadMenu(IDR_MENU_PRINT);

		CXTPRibbonSystemPopupBarPage* pPopupBar = new CXTPRibbonSystemPopupBarPage();
		pPopupBar->SetCommandBars(GetCommandBars());

		pPopupBar->LoadMenu(menu.GetSubMenu(0));

		CXTPControl* pControlLabel = pPopupBar->GetControls()->Add(xtpControlLabel, ID_FILE_PRINT_LABEL, NULL, 0);
		pControlLabel->SetWidth(XTP_DPI_X(296));
		pControlLabel->SetItemDefault(TRUE);
		pControlLabel->SetStyle(xtpButtonCaption);

		pPopupBar->SetShowGripper(FALSE);
		pPopupBar->SetDefaultButtonStyle(xtpButtonCaptionAndDescription);
		pPopupBar->SetIconSize(CSize(32, 32));

		pControl->SetCommandBar(pPopupBar);

		pPopupBar->InternalRelease();

		lpCreateControl->pControl = pControl;
		return TRUE;
	}
	if (lpCreateControl->nID == ID_FILE_SEND)
	{		
		CXTPControlPopup* pControl = CXTPControlPopup::CreateControlPopup(xtpControlButtonPopup);

		CMenu menu;
		menu.LoadMenu(IDR_MENU_SEND);

		CXTPRibbonSystemPopupBarPage* pPopupBar = new CXTPRibbonSystemPopupBarPage();
		pPopupBar->SetCommandBars(GetCommandBars());

		pPopupBar->LoadMenu(menu.GetSubMenu(0));

		CXTPControl* pControlLabel = pPopupBar->GetControls()->Add(xtpControlLabel, ID_FILE_SEND_LABEL, NULL, 0);
		pControlLabel->SetWidth(XTP_DPI_X(296));
		pControlLabel->SetItemDefault(TRUE);
		pControlLabel->SetStyle(xtpButtonCaption);

		pPopupBar->SetShowGripper(FALSE);
		pPopupBar->SetDefaultButtonStyle(xtpButtonCaptionAndDescription);
		pPopupBar->SetIconSize(CSize(32, 32));

		pControl->SetCommandBar(pPopupBar);

		pPopupBar->InternalRelease();

		pControl->SetFlags(xtpFlagManualUpdate);

		lpCreateControl->pControl = pControl;
		return TRUE;
	}
	return FALSE;
}

void CMainFrame::OnGalleryShapes(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMXTPCONTROL *tagNMCONTROL = reinterpret_cast<NMXTPCONTROL*>(pNMHDR);

	CXTPControlGallery* pGallery = DYNAMIC_DOWNCAST(CXTPControlGallery, tagNMCONTROL->pControl);
	
	if (pGallery)
	{
		CXTPControlGalleryItem* pItem = pGallery->GetItem(pGallery->GetSelectedItem());
		if (pItem)
		{
			m_nShape = pItem->GetID();
		}

		*pResult = TRUE; // Handled
	}
}

void CMainFrame::OnUpdateGalleryShapes(CCmdUI* pCmdUI)
{
	CXTPControlGallery* pGallery = 	DYNAMIC_DOWNCAST(CXTPControlGallery, CXTPControl::FromUI(pCmdUI));
	
	if (pGallery)
	{
		pGallery->SetCheckedItem(m_nShape);
	}
	pCmdUI->Enable(TRUE);
}



void CMainFrame::OnGalleryStyles(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CXTPControlGallery* pGallery = DYNAMIC_DOWNCAST(CXTPControlGallery, tagNMCONTROL->pControl);
	
	if (pGallery)
	{
		CXTPControlGalleryItem* pItem = pGallery->GetItem(pGallery->GetSelectedItem());
		if (pItem)
		{
			m_nStyle = pItem->GetID();
		}

		*pResult = TRUE; // Handled
	}
}

void CMainFrame::OnUpdateGalleryStyles(CCmdUI* pCmdUI)
{
	CXTPControlGallery* pGallery = 	DYNAMIC_DOWNCAST(CXTPControlGallery, CXTPControl::FromUI(pCmdUI));
	
	if (pGallery)
	{
		if (pGallery->GetCheckedItem() != m_nStyle)
		{
			pGallery->SetCheckedItem(m_nStyle);
			pGallery->EnsureVisible(m_nStyle);
		}
	}
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnGalleryColumns(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CXTPControlGallery* pGallery = DYNAMIC_DOWNCAST(CXTPControlGallery, tagNMCONTROL->pControl);
	
	if (pGallery)
	{
		CXTPControlGalleryItem* pItem = pGallery->GetItem(pGallery->GetSelectedItem());
		if (pItem)
		{
			m_nColumns = pItem->GetID();
		}

		*pResult = TRUE; // Handled
	}
}

void CMainFrame::OnUpdateGalleryColumns(CCmdUI* pCmdUI)
{
	CXTPControlGallery* pGallery = 	DYNAMIC_DOWNCAST(CXTPControlGallery, CXTPControl::FromUI(pCmdUI));
	
	if (pGallery)
	{
		pGallery->SetCheckedItem(m_nColumns);
	}
	pCmdUI->Enable(TRUE);
}




void CMainFrame::OnGalleryStyleSet(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CXTPControlGallery* pGallery = DYNAMIC_DOWNCAST(CXTPControlGallery, tagNMCONTROL->pControl);
	
	if (pGallery)
	{
		CXTPControlGalleryItem* pItem = pGallery->GetItem(pGallery->GetSelectedItem());
		if (pItem)
		{
			m_nStyleSet = pItem->GetID();
		}

		*pResult = TRUE; // Handled
	}
}

void CMainFrame::OnUpdateGalleryStyleSet(CCmdUI* pCmdUI)
{
	CXTPControlGallery* pGallery = 	DYNAMIC_DOWNCAST(CXTPControlGallery, CXTPControl::FromUI(pCmdUI));
	
	if (pGallery)
	{
		pGallery->SetCheckedItem(m_nStyleSet);
	}
	pCmdUI->Enable(TRUE);
}


void CMainFrame::OnGalleryThemeColors(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CXTPControlGallery* pGallery = DYNAMIC_DOWNCAST(CXTPControlGallery, tagNMCONTROL->pControl);
	
	if (pGallery)
	{
		CXTPControlGalleryItem* pItem = pGallery->GetItem(pGallery->GetSelectedItem());
		if (pItem)
		{
			m_nThemeColors = pItem->GetID();
			
			m_pItemsFontTextColor->RemoveAll();
			pItem = m_pItemsFontTextColor->AddLabel(0);
			pItem->SetCaption(_T("Theme Colors"));
			CGalleryItemFontColor::AddThemeColors(m_pItemsFontTextColor, m_nThemeColors);
			
			pItem = m_pItemsFontTextColor->AddLabel(0);
			pItem->SetCaption(_T("Standard Colors"));
			CGalleryItemFontColor::AddStandardColors(m_pItemsFontTextColor);

		}

		*pResult = TRUE; // Handled
	}
}

void CMainFrame::OnUpdateGalleryThemeColors(CCmdUI* pCmdUI)
{
	CXTPControlGallery* pGallery = 	DYNAMIC_DOWNCAST(CXTPControlGallery, CXTPControl::FromUI(pCmdUI));
	
	if (pGallery)
	{
		pGallery->SetCheckedItem(m_nThemeColors);
	}
	pCmdUI->Enable(TRUE);
}


void CMainFrame::OnGalleryThemeFonts(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CXTPControlGallery* pGallery = DYNAMIC_DOWNCAST(CXTPControlGallery, tagNMCONTROL->pControl);
	
	if (pGallery)
	{
		CXTPControlGalleryItem* pItem = pGallery->GetItem(pGallery->GetSelectedItem());
		
		if (pItem)
		{
			m_nThemeFonts = pItem->GetID();
		}

		*pResult = TRUE; // Handled
	}
}

void CMainFrame::OnUpdateGalleryThemeFonts(CCmdUI* pCmdUI)
{
	CXTPControlGallery* pGallery = 	DYNAMIC_DOWNCAST(CXTPControlGallery, CXTPControl::FromUI(pCmdUI));
	
	if (pGallery)
	{
		pGallery->SetCheckedItem(m_nThemeFonts);
	}
	pCmdUI->Enable(TRUE);
}


void CMainFrame::OnOptionsAnimation() 
{
	m_bAnimation ^= 1;
	GetCommandBars()->GetMenuBar()->EnableAnimation(m_bAnimation);
	
}

void CMainFrame::OnUpdateOptionsAnimation(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bAnimation);	
}

void CMainFrame::OnOptionsRightToLeft() 
{
	if (GetExStyle() & WS_EX_LAYOUTRTL)
	{
		GetCommandBars()->SetLayoutRTL(FALSE);
		ModifyStyleEx(WS_EX_LAYOUTRTL, 0);

		((CWorkspaceView*)GetDlgItem(AFX_IDW_PANE_FIRST))->SetLayoutRTL(FALSE);
	}
	else
	{
		GetCommandBars()->SetLayoutRTL(TRUE);
		ModifyStyleEx(0, WS_EX_LAYOUTRTL);

		((CWorkspaceView*)GetDlgItem(AFX_IDW_PANE_FIRST))->SetLayoutRTL(TRUE);
	}	

	m_wndMessageBar.ModifyStyleEx(WS_EX_LAYOUTRTL, GetExStyle() & WS_EX_LAYOUTRTL);

	RecalcLayout(FALSE);
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

void CMainFrame::OnOptionsStyleOffice2013LtGray()
{
	m_eOffice2013Gray = (m_eOffice2013Gray == eGrayLight) ? eGrayNone : eGrayLight;
	SetStyle(m_enumTheme);
}

void CMainFrame::OnUpdateOptionsStyleOffice2013LtGray(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_eOffice2013Gray == eGrayLight);
	pCmdUI->Enable(
		m_enumTheme >= CRibbonSampleApp::themeOffice2013Access &&
		m_enumTheme <= CRibbonSampleApp::themeOffice2013Word);
}

void CMainFrame::OnOptionsStyleOffice2013DkGray()
{
	m_eOffice2013Gray = (m_eOffice2013Gray == eGrayDark) ? eGrayNone : eGrayDark;
	SetStyle(m_enumTheme);
}

void CMainFrame::OnUpdateOptionsStyleOffice2013DkGray(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_eOffice2013Gray == eGrayDark);
	pCmdUI->Enable(
		m_enumTheme >= CRibbonSampleApp::themeOffice2013Access &&
		m_enumTheme <= CRibbonSampleApp::themeOffice2013Word);
}

void CMainFrame::OnOptionsStyleVisualStudio2015Closed()
{
	m_eStudio2015State = eStateClosed;
	SetStateColor();
}

void CMainFrame::OnUpdateOptionsStyleVisualStudio2015Closed(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(m_eStudio2015State == eStateClosed);
	pCmdUI->Enable(
		m_enumTheme >= CRibbonSampleApp::themeVisualStudio2015Blue &&
		m_enumTheme <= CRibbonSampleApp::themeVisualStudio2015Light);
}

void CMainFrame::OnOptionsStyleVisualStudio2015Open()
{
	m_eStudio2015State = eStateOpen;
	SetStateColor();
}

void CMainFrame::OnUpdateOptionsStyleVisualStudio2015Open(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(m_eStudio2015State == eStateOpen);
	pCmdUI->Enable(
		m_enumTheme >= CRibbonSampleApp::themeVisualStudio2015Blue &&
		m_enumTheme <= CRibbonSampleApp::themeVisualStudio2015Light);
}

void CMainFrame::OnOptionsStyleVisualStudio2015Debug()
{
	m_eStudio2015State = eStateDebug;
	SetStateColor();
}

void CMainFrame::OnUpdateOptionsStyleVisualStudio2015Debug(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(m_eStudio2015State == eStateDebug);
	pCmdUI->Enable(
		m_enumTheme >= CRibbonSampleApp::themeVisualStudio2015Blue &&
		m_enumTheme <= CRibbonSampleApp::themeVisualStudio2015Light);
}

void CMainFrame::OnStyleOffice2010(UINT nStyle)
{
	OnOptionsStyle(nStyle);
}

void CMainFrame::OnOptionsStyleOffice2013Back(UINT nStyle)
{
	switch (nStyle)
	{
	case ID_OPTIONS_STYLE_OFFICE2013_BACK_NONE:
		m_nRibbonBackImage = ID_OPTIONS_STYLE_OFFICE2013_BACK_NONE;
		XTPSetOfficeSetBackImage(GetCommandBars());
		break;
	case ID_OPTIONS_STYLE_OFFICE2013_BACK_CALLIGRAPHY:
		m_nRibbonBackImage = ID_OPTIONS_STYLE_OFFICE2013_BACK_CALLIGRAPHY;
		XTPSetOfficeSetBackImage(GetCommandBars(), XTPCalligraphy);
		break;
	case ID_OPTIONS_STYLE_OFFICE2013_BACK_CIRCLESANDSTRIPES:
		m_nRibbonBackImage = ID_OPTIONS_STYLE_OFFICE2013_BACK_CIRCLESANDSTRIPES;
		XTPSetOfficeSetBackImage(GetCommandBars(), XTPCirclesAndStripes);
		break;
	case ID_OPTIONS_STYLE_OFFICE2013_BACK_CIRCUIT:
		m_nRibbonBackImage = ID_OPTIONS_STYLE_OFFICE2013_BACK_CIRCUIT;
		XTPSetOfficeSetBackImage(GetCommandBars(), XTPCircuit);
		break;
	case ID_OPTIONS_STYLE_OFFICE2013_BACK_CLOUDS:
		m_nRibbonBackImage = ID_OPTIONS_STYLE_OFFICE2013_BACK_CLOUDS;
		XTPSetOfficeSetBackImage(GetCommandBars(), XTPClouds);
		break;
	case ID_OPTIONS_STYLE_OFFICE2013_BACK_DOODLECIRCLES:
		m_nRibbonBackImage = ID_OPTIONS_STYLE_OFFICE2013_BACK_DOODLECIRCLES;
		XTPSetOfficeSetBackImage(GetCommandBars(), XTPDoodleCircles);
		break;
	case ID_OPTIONS_STYLE_OFFICE2013_BACK_DOODLEDIAMONDS:
		m_nRibbonBackImage = ID_OPTIONS_STYLE_OFFICE2013_BACK_DOODLEDIAMONDS;
		XTPSetOfficeSetBackImage(GetCommandBars(), XTPDoodleDiamonds);
		break;
	case ID_OPTIONS_STYLE_OFFICE2013_BACK_GEOMETRY:
		m_nRibbonBackImage = ID_OPTIONS_STYLE_OFFICE2013_BACK_GEOMETRY;
		XTPSetOfficeSetBackImage(GetCommandBars(), XTPGeometry);
		break;
	case ID_OPTIONS_STYLE_OFFICE2013_BACK_LUNCHBOX:
		m_nRibbonBackImage = ID_OPTIONS_STYLE_OFFICE2013_BACK_LUNCHBOX;
		XTPSetOfficeSetBackImage(GetCommandBars(), XTPLunchBox);
		break;
	case ID_OPTIONS_STYLE_OFFICE2013_BACK_SCHOOLSUPPLIES:
		m_nRibbonBackImage = ID_OPTIONS_STYLE_OFFICE2013_BACK_SCHOOLSUPPLIES;
		XTPSetOfficeSetBackImage(GetCommandBars(), XTPSchoolSupplies);
		break;
	case ID_OPTIONS_STYLE_OFFICE2013_BACK_SPRING:
		m_nRibbonBackImage = ID_OPTIONS_STYLE_OFFICE2013_BACK_SPRING;
		XTPSetOfficeSetBackImage(GetCommandBars(), XTPSpring);
		break;
	case ID_OPTIONS_STYLE_OFFICE2013_BACK_STARS:
		m_nRibbonBackImage = ID_OPTIONS_STYLE_OFFICE2013_BACK_STARS;
		XTPSetOfficeSetBackImage(GetCommandBars(), XTPStars);
		break;
	case ID_OPTIONS_STYLE_OFFICE2013_BACK_STRAWS:
		m_nRibbonBackImage = ID_OPTIONS_STYLE_OFFICE2013_BACK_STRAWS;
		XTPSetOfficeSetBackImage(GetCommandBars(), XTPStraws);
		break;
	case ID_OPTIONS_STYLE_OFFICE2013_BACK_TREERINGS:
		m_nRibbonBackImage = ID_OPTIONS_STYLE_OFFICE2013_BACK_TREERINGS;
		XTPSetOfficeSetBackImage(GetCommandBars(), XTPTreeRings);
		break;
	case ID_OPTIONS_STYLE_OFFICE2013_BACK_UNDERWATER:
		m_nRibbonBackImage = ID_OPTIONS_STYLE_OFFICE2013_BACK_UNDERWATER;
		XTPSetOfficeSetBackImage(GetCommandBars(), XTPUnderWater);
		break;
	}
}

void CMainFrame::OnUpdateOptionsStyleOffice2013Back(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nRibbonBackImage ? 1 : 0);

	pCmdUI->Enable(
		m_enumTheme >= CRibbonSampleApp::themeOffice2013Access &&
		m_enumTheme <= CRibbonSampleApp::themeOffice2013Word);
}

void CMainFrame::OnStyleWindows7()
{
	OnOptionsStyle(ID_OPTIONS_STYLE_WINDOWS7SCENIC);
}

void CMainFrame::OnOptionsStyleVisualStudio2015(UINT nStyle)
{
	switch (nStyle)
	{
	case ID_OPTIONS_STYLE_VISUALSTUDIO2015BLUE:
		SetTheme(CRibbonSampleApp::themeVisualStudio2015Blue);
		break;

	case ID_OPTIONS_STYLE_VISUALSTUDIO2015DARK:
		SetTheme(CRibbonSampleApp::themeVisualStudio2015Dark);
		break;

	case ID_OPTIONS_STYLE_VISUALSTUDIO2015LIGHT:
		SetTheme(CRibbonSampleApp::themeVisualStudio2015Light);
		break;
	}

	CXTPCommandBars* pCommandBars = GetCommandBars();
	if (pCommandBars)
	{
		pCommandBars->SetAllCaps(FALSE);
		pCommandBars->GetPaintManager()->m_bAutoResizeIcons = TRUE;
		pCommandBars->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE);

		CXTPToolTipContext* pContext = pCommandBars->GetToolTipContext();
		if (pContext)
		{
			pContext->SetStyle(xtpToolTipOffice2013);
		}

		CXTPPaintManager* pPaintManager = pCommandBars->GetPaintManager();
		if (pPaintManager)
		{
			pPaintManager->RefreshMetrics();
		}

		CXTPRibbonBar* pRibbonBar = DYNAMIC_DOWNCAST(CXTPRibbonBar, pCommandBars->GetMenuBar());
		if (pRibbonBar)
		{
			CXTPRibbonControlSystemButton* pSysButton = pRibbonBar->GetSystemButton();
			if (pSysButton)
			{
				pSysButton->SetStyle(xtpButtonCaption);
			}
		}
	}

	CreateBackstage();

#ifdef _XTP_INCLUDE_DOCKINGPANE
	SetDockingPaneTheme(xtpPaneThemeVisualStudio2015, XTP_DPI_X(5));
#endif

	m_wndStatusBar.SetAllCaps(FALSE);
	SetFrameIcon(CSize(20, 20));

	OnUpdateCommands();

	m_nRibbonStyle = nStyle;
}

#ifdef _XTP_INCLUDE_DOCKINGPANE

void CMainFrame::SetDockingPaneTheme(XTPDockingPanePaintTheme nTheme, int nMargin /*=0*/)
{
	m_paneManager.SetTheme(nTheme);
	m_paneManager.SetClientMargin(nMargin);
	m_paneStyles.RefreshMetrics(nTheme);
}

#endif /*_XTP_INCLUDE_DOCKINGPANE*/

void CMainFrame::OnOptionsStyleOffice2013(UINT nStyle)
{
	switch (nStyle)
	{
	case ID_OPTIONS_STYLE_OFFICE2013ACCESS:
		SetTheme(CRibbonSampleApp::themeOffice2013Access);
		break;

	case ID_OPTIONS_STYLE_OFFICE2013EXCEL:
		SetTheme(CRibbonSampleApp::themeOffice2013Excel);
		break;

	case ID_OPTIONS_STYLE_OFFICE2013ONENOTE:
		SetTheme(CRibbonSampleApp::themeOffice2013OneNote);
		break;

	case ID_OPTIONS_STYLE_OFFICE2013OUTLOOK:
		SetTheme(CRibbonSampleApp::themeOffice2013Outlook);
		break;

	case ID_OPTIONS_STYLE_OFFICE2013PUBLISHER:
		SetTheme(CRibbonSampleApp::themeOffice2013Publisher);
		break;

	case ID_OPTIONS_STYLE_OFFICE2013POWERPOINT:
		SetTheme(CRibbonSampleApp::themeOffice2013PowerPoint);
		break;

	case ID_OPTIONS_STYLE_OFFICE2013WORD:
		SetTheme(CRibbonSampleApp::themeOffice2013Word);
		break;
	}

	CXTPCommandBars* pCommandBars = GetCommandBars();
	if (pCommandBars)
	{
		pCommandBars->SetAllCaps(TRUE);
		pCommandBars->GetPaintManager()->m_bAutoResizeIcons = TRUE;
		pCommandBars->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE, FALSE);

		CXTPToolTipContext* pContext = pCommandBars->GetToolTipContext();
		if (pContext)
		{
			pContext->SetStyle(xtpToolTipOffice2013);
		}

		CXTPPaintManager* pPaintManager = pCommandBars->GetPaintManager();
		if (pPaintManager)
		{
			pPaintManager->RefreshMetrics();
		}

		CXTPRibbonBar* pRibbonBar = DYNAMIC_DOWNCAST(CXTPRibbonBar, pCommandBars->GetMenuBar());
		if (pRibbonBar)
		{
			CXTPRibbonControlSystemButton* pSysButton = pRibbonBar->GetSystemButton();
			if (pSysButton)
			{
				pSysButton->SetStyle(xtpButtonCaption);
			}
		}
	}

	CreateBackstage();

#ifdef _XTP_INCLUDE_DOCKINGPANE
	SetDockingPaneTheme(xtpPaneThemeOffice2013);
#endif

	m_wndStatusBar.SetAllCaps(TRUE);
	SetFrameIcon(CSize(20, 20));

	OnUpdateCommands();

	m_nRibbonStyle = nStyle;
}

void CMainFrame::OnOptionsStyle(UINT nStyle)
{
	int nTheme = 0;

	switch (nStyle)
	{
		// Office 2007
	case ID_OPTIONS_STYLE_OFFICE2007BLUE:
		nTheme = (CRibbonSampleApp::themeOffice2007Blue);
		break;

	case ID_OPTIONS_STYLE_OFFICE2007SILVER:
		nTheme = (CRibbonSampleApp::themeOffice2007Silver);
		break;

	case ID_OPTIONS_STYLE_OFFICE2007BLACK:
		nTheme = (CRibbonSampleApp::themeOffice2007Black);
		break;

	case ID_OPTIONS_STYLE_OFFICE2007AQUA:
		nTheme = (CRibbonSampleApp::themeOffice2007Aqua);
		break;

		// Office 2010 styles
	case ID_OPTIONS_STYLE_OFFICE2010BLUE:
		nTheme = (CRibbonSampleApp::themeOffice2010Blue);
		break;

	case ID_OPTIONS_STYLE_OFFICE2010SILVER:
		nTheme = (CRibbonSampleApp::themeOffice2010Silver);
		break;

	case ID_OPTIONS_STYLE_OFFICE2010BLACK:
		nTheme = (CRibbonSampleApp::themeOffice2010Black);
		break;

	case ID_OPTIONS_STYLE_WINDOWS7SCENIC:
		nTheme = (CRibbonSampleApp::themeWindows7);
		break;
	}

	GetCommandBars()->SetAllCaps(FALSE);
	GetCommandBars()->GetPaintManager()->RefreshMetrics();

	SetTheme(nTheme);
	GetCommandBars()->GetToolTipContext()->SetStyle(xtpToolTipResource);

	CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)GetCommandBars()->GetMenuBar();

	if (ID_OPTIONS_STYLE_OFFICE2007SILVER == nStyle ||
		ID_OPTIONS_STYLE_OFFICE2007BLUE == nStyle ||
		ID_OPTIONS_STYLE_OFFICE2007BLACK == nStyle ||
		ID_OPTIONS_STYLE_OFFICE2007AQUA == nStyle || 
		ID_OPTIONS_STYLE_OFFICE2007SYSTEM == nStyle)
	{
		pRibbonBar->GetSystemButton()->SetStyle(xtpButtonAutomatic);
		CreateSystemMenuPopup();
	}
	else
	{
		pRibbonBar->GetSystemButton()->SetStyle(xtpButtonCaption);
		CreateBackstage();
	}

#ifdef _XTP_INCLUDE_DOCKINGPANE
	switch (nTheme)
	{
	case CRibbonSampleApp::themeWindows7:
		SetDockingPaneTheme(xtpPaneThemeWinExplorer);
		break;
	default:
		SetDockingPaneTheme(xtpPaneThemeOffice2007Word);
		break;
	}
#endif

	m_wndStatusBar.SetAllCaps(FALSE);
	SetFrameIcon(CSize(16, 16));


	GetCommandBars()->GetPaintManager()->m_bAutoResizeIcons = TRUE;
	GetCommandBars()->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE);
	GetCommandBars()->GetImageManager()->RefreshAll();
	GetCommandBars()->RedrawCommandBars();
	SendMessage(WM_NCPAINT);

	RedrawWindow(0, 0, RDW_ALLCHILDREN | RDW_INVALIDATE);

	OnUpdateCommands();

	m_nRibbonStyle = nStyle;
}

void CMainFrame::OnUpdateOptionsStyle(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nRibbonStyle ? 1 : 0);
}

void CMainFrame::OnStyleOffice2007(UINT nStyle)
{
	OnOptionsStyle(nStyle);
}


void CMainFrame::SetStateColor()
{
	switch (m_eStudio2015State)
	{
	case eStateClosed:
		XTPSetVSStateColor(GetCommandBars());
		break;
	case eStateOpen:
		XTPSetVSStateColor(GetCommandBars(), RGB(0, 122, 204));
		break;
	case eStateDebug:
		XTPSetVSStateColor(GetCommandBars(), RGB(202, 81, 0));
		break;
	}
}

void CMainFrame::OnBackstagePageRecentContextMenu(NMHDR* pNMHDR, LRESULT* plResult)
{
	LPNMXTPRRNCONTEXTMENU pNotification = reinterpret_cast<LPNMXTPRRNCONTEXTMENU>(pNMHDR);

	CXTPPopupBar* pPopupBar = CXTPPopupBar::CreatePopupBar(GetCommandBars());
	pPopupBar->SetDefaultButtonStyle(xtpButtonCaption);
	pPopupBar->SetShowGripper(FALSE);
	if (pNotification->pItem->GetRecentItem()->IsPinned())
	{
		pPopupBar->GetControls()->Add(xtpControlButton, ID_RECENTFILE_UNPIN);
	}
	else
	{
		pPopupBar->GetControls()->Add(xtpControlButton, ID_RECENTFILE_PIN);
	}
	pPopupBar->GetControls()->Add(xtpControlButton, ID_RECENTFILE_REMOVE);

	UINT nID = GetCommandBars()->TrackPopupMenu(pPopupBar, 
		TPM_RETURNCMD | TPM_NONOTIFY, pNotification->pt.x, pNotification->pt.y, this);
	switch (nID)
	{
	case ID_RECENTFILE_PIN:
		m_pageRecent.PinItem(pNotification->pItem);
		break;
	case ID_RECENTFILE_UNPIN:
		m_pageRecent.UnpinItem(pNotification->pItem);
		break;
	case ID_RECENTFILE_REMOVE:
		m_pageRecent.RemoveItem(pNotification->pItem);
		break;
	}

	pPopupBar->InternalRelease();

	*plResult = 0;
}

void CMainFrame::SetCommandBarsTheme(XTPPaintTheme paintTheme, LPCTSTR lpszINI/*=NULL*/)
{
#ifdef _XTP_INCLUDE_COMMANDBARS

	CXTPCommandBars* pCommandBars = GetCommandBars();
	if (!pCommandBars)
		return;

	CXTPRibbonBar* pRibbonBar = DYNAMIC_DOWNCAST(CXTPRibbonBar, pCommandBars->GetMenuBar());
	if (!pRibbonBar)
		return;

	if (!m_bOverrideAllowDwm)
	{
		m_bAllowDwm = (XTPSystemVersion()->IsWin10OrGreater() ? FALSE
			: !(CXTPWinDwmWrapper().IsCompositionEnabled()
				&& (xtpThemeOffice2013 == paintTheme || xtpThemeVisualStudio2015 == paintTheme)));
	}

	pRibbonBar->EnableFrameTheme(FALSE);

	if (lpszINI != NULL)
	{
		XTPThemeDLL()->SetHandle(lpszINI);
	}

	if (lpszINI != NULL)
	{
		CXTPPaintManager::SetTheme(paintTheme);

		if (xtpThemeOffice2013 == paintTheme)
		{
			OnOptionsStyleOffice2013Back(m_nRibbonBackImage);
		}
	}


	pRibbonBar->EnableFrameTheme(m_bEnableFrameTheme);
	
	pCommandBars->GetPaintManager()->RefreshMetrics();
	pCommandBars->RedrawCommandBars();
	
	SendMessage(WM_NCPAINT);
	RedrawWindow(0, 0, RDW_ALLCHILDREN|RDW_INVALIDATE);

#else

	UNREFERENCED_PARAMETER(paintTheme);

#endif
}

void CMainFrame::SetStyle(int nTheme)
{
	switch (nTheme)
	{
		case CRibbonSampleApp::themeOffice2007Aqua:
			OnOptionsStyle(ID_OPTIONS_STYLE_OFFICE2007AQUA);
			break;
		case CRibbonSampleApp::themeOffice2007Black:
			OnOptionsStyle(ID_OPTIONS_STYLE_OFFICE2007BLACK);
			break;
		case CRibbonSampleApp::themeOffice2007Blue:
			OnOptionsStyle(ID_OPTIONS_STYLE_OFFICE2007BLUE);
			break;
		case CRibbonSampleApp::themeOffice2007System:
			OnOptionsStyle(ID_OPTIONS_STYLE_OFFICE2007SYSTEM);
			break;
		case CRibbonSampleApp::themeOffice2007Silver:
			OnOptionsStyle(ID_OPTIONS_STYLE_OFFICE2007SILVER);
			break;
		case CRibbonSampleApp::themeOffice2010Black:
			OnOptionsStyle(ID_OPTIONS_STYLE_OFFICE2010BLACK);
			break;
		case CRibbonSampleApp::themeOffice2010Blue:
			OnOptionsStyle(ID_OPTIONS_STYLE_OFFICE2010BLUE);
			break;
		case CRibbonSampleApp::themeOffice2010Silver:
			OnOptionsStyle(ID_OPTIONS_STYLE_OFFICE2010SILVER);
			break;
		case CRibbonSampleApp::themeWindows7:
			OnOptionsStyle(ID_OPTIONS_STYLE_WINDOWS7SCENIC);
			break;
		case CRibbonSampleApp::themeOffice2013Access:
			OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013ACCESS);
			break;
		case CRibbonSampleApp::themeOffice2013Excel:
			OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013EXCEL);
			break;
		case CRibbonSampleApp::themeOffice2013OneNote:
			OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013ONENOTE);
			break;
		case CRibbonSampleApp::themeOffice2013Outlook:
			OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013OUTLOOK);
			break;
		case CRibbonSampleApp::themeOffice2013Publisher:
			OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013PUBLISHER);
			break;
		case CRibbonSampleApp::themeOffice2013PowerPoint:
			OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013POWERPOINT);
			break;
		case CRibbonSampleApp::themeOffice2013Word:
			OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013WORD);
			break;
		case CRibbonSampleApp::themeVisualStudio2015Blue:
			OnOptionsStyleVisualStudio2015(ID_OPTIONS_STYLE_VISUALSTUDIO2015BLUE);
			break;
		case CRibbonSampleApp::themeVisualStudio2015Dark:
			OnOptionsStyleVisualStudio2015(ID_OPTIONS_STYLE_VISUALSTUDIO2015DARK);
			break;
		case CRibbonSampleApp::themeVisualStudio2015Light:
			OnOptionsStyleVisualStudio2015(ID_OPTIONS_STYLE_VISUALSTUDIO2015LIGHT);
			break;
	}
}

void CMainFrame::SetTheme(int theme)
{
	m_enumTheme = (CRibbonSampleApp::AppTheme)theme;

	switch (m_enumTheme)
	{
		case CRibbonSampleApp::themeOffice2013Access:
		{
			CString strResource = (m_eOffice2013Gray == eGrayDark) ? xtpIniOffice2013AccessGrayDark : (m_eOffice2013Gray == eGrayLight) ? xtpIniOffice2013AccessGrayLight : xtpIniOffice2013Access;
			SetCommandBarsTheme(xtpThemeOffice2013, strResource);
			break;
		}

		case CRibbonSampleApp::themeOffice2013Excel:
		{
			CString strResource = (m_eOffice2013Gray == eGrayDark) ? xtpIniOffice2013ExcelGrayDark : (m_eOffice2013Gray == eGrayLight) ? xtpIniOffice2013ExcelGrayLight : xtpIniOffice2013Excel;
			SetCommandBarsTheme(xtpThemeOffice2013, strResource);
			break;
		}

		case CRibbonSampleApp::themeOffice2013OneNote:
		{
			CString strResource = (m_eOffice2013Gray == eGrayDark) ? xtpIniOffice2013OneNoteGrayDark : (m_eOffice2013Gray == eGrayLight) ? xtpIniOffice2013OneNoteGrayLight : xtpIniOffice2013OneNote;
			SetCommandBarsTheme(xtpThemeOffice2013, strResource);
			break;
		}

		case CRibbonSampleApp::themeOffice2013Outlook:
		{
			CString strResource = (m_eOffice2013Gray == eGrayDark) ? xtpIniOffice2013OutlookGrayDark : (m_eOffice2013Gray == eGrayLight) ? xtpIniOffice2013OutlookGrayLight : xtpIniOffice2013Outlook;
			SetCommandBarsTheme(xtpThemeOffice2013, strResource);
			break;
		}

		case CRibbonSampleApp::themeOffice2013Publisher:
		{
			CString strResource = (m_eOffice2013Gray == eGrayDark) ? xtpIniOffice2013PublisherGrayDark : (m_eOffice2013Gray == eGrayLight) ? xtpIniOffice2013PublisherGrayLight : xtpIniOffice2013Publisher;
			SetCommandBarsTheme(xtpThemeOffice2013, strResource);
			break;
		}

		case CRibbonSampleApp::themeOffice2013PowerPoint:
		{
			CString strResource = (m_eOffice2013Gray == eGrayDark) ? xtpIniOffice2013PowerPointGrayDark : (m_eOffice2013Gray == eGrayLight) ? xtpIniOffice2013PowerPointGrayLight : xtpIniOffice2013PowerPoint;
			SetCommandBarsTheme(xtpThemeOffice2013, strResource);
			break;
		}

		case CRibbonSampleApp::themeOffice2013Word:
		{
			CString strResource = (m_eOffice2013Gray == eGrayDark) ? xtpIniOffice2013WordGrayDark : (m_eOffice2013Gray == eGrayLight) ? xtpIniOffice2013WordGrayLight : xtpIniOffice2013Word;
			SetCommandBarsTheme(xtpThemeOffice2013, strResource);
			break;
		}

		case CRibbonSampleApp::themeVisualStudio2015Blue:
		{
			SetCommandBarsTheme(xtpThemeVisualStudio2015, xtpIniVisualStudio2015Blue);
			SetStateColor();
			break;
		}

		case CRibbonSampleApp::themeVisualStudio2015Dark:
		{
			SetCommandBarsTheme(xtpThemeVisualStudio2015, xtpIniVisualStudio2015Dark);
			SetStateColor();
			break;
		}

		case CRibbonSampleApp::themeVisualStudio2015Light:
		{
			SetCommandBarsTheme(xtpThemeVisualStudio2015, xtpIniVisualStudio2015Light);
			SetStateColor();
			break;
		}

		case CRibbonSampleApp::themeOffice2007Aqua:
		{
			SetCommandBarsTheme(xtpThemeRibbon, xtpIniOffice2007Aqua);
			break;
		}

		case CRibbonSampleApp::themeOffice2007Blue:
		{
			SetCommandBarsTheme(xtpThemeRibbon, xtpIniOffice2007Blue);
			break;
		}

		case CRibbonSampleApp::themeOffice2007Black:
		{
			SetCommandBarsTheme(xtpThemeRibbon, xtpIniOffice2007Black);
			break;
		}

		case CRibbonSampleApp::themeOffice2007Silver:
		{
			SetCommandBarsTheme(xtpThemeRibbon, xtpIniOffice2007Silver);
			break;
		}

		case CRibbonSampleApp::themeWindows7:
		{
			SetCommandBarsTheme(xtpThemeRibbon, xtpIniWindows7Blue);
			break;
		}
	
		case CRibbonSampleApp::themeOffice2010Blue:
		{
			SetCommandBarsTheme(xtpThemeRibbon, xtpIniOffice2010Blue);
			break;
		}

		case CRibbonSampleApp::themeOffice2010Black:
		{
			SetCommandBarsTheme(xtpThemeRibbon, xtpIniOffice2010Black);
			break;
		}

		case CRibbonSampleApp::themeOffice2010Silver:
		{
			SetCommandBarsTheme(xtpThemeRibbon, xtpIniOffice2010Silver);
			break;
		}
	}
}

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

void CMainFrame::OnAllowDwm()
{
	m_bOverrideAllowDwm = TRUE;

	m_bAllowDwm = !m_bAllowDwm;

	OnOptionsStyle(m_nRibbonStyle);

	m_bOverrideAllowDwm = FALSE;
}

void CMainFrame::OnUpdateAllowDwm(CCmdUI* pCmdUI)
{
	if (!XTPSystemVersion()->IsWin10OrGreater())
	{
		pCmdUI->SetCheck(m_bAllowDwm);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CMainFrame::OnToggleGroups() 
{
	CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)GetCommandBars()->GetAt(0);
	
	pRibbonBar->SetRibbonMinimized(!pRibbonBar->IsRibbonMinimized());
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

void CMainFrame::OnDpiIconsScalling()
{
	GetCommandBars()->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE, !GetCommandBars()->GetCommandBarsOptions()->GetToolbarsIconsScalling());
	GetCommandBars()->RedrawCommandBars();
}

void CMainFrame::OnUpdateDpiIconsScalling(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetCommandBars()->GetCommandBarsOptions()->GetToolbarsIconsScalling());
}

void CMainFrame::OnFrameTheme()
{
	ShowWindow(SW_NORMAL);
	CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)GetCommandBars()->GetAt(0);

	CXTPWindowRect rc(this);
	rc.top += (m_bEnableFrameTheme ? -1 : +1) * GetSystemMetrics(SM_CYCAPTION);
	MoveWindow(rc);
	
	m_bEnableFrameTheme = !m_bEnableFrameTheme;
	pRibbonBar->EnableFrameTheme(m_bEnableFrameTheme);

}

void CMainFrame::OnUpdateFrameTheme(CCmdUI* pCmdUI)
{
	CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)GetCommandBars()->GetAt(0);

	pCmdUI->SetCheck(pRibbonBar->IsFrameThemeEnabled() ? TRUE : FALSE);
}

void CMainFrame::OnStatusBarSwitchView(UINT nID)
{
	CXTPStatusBarSwitchPane* pPane = (CXTPStatusBarSwitchPane*)m_wndStatusBar.FindPane(ID_INDICATOR_VIEWSHORTCUTS);

	pPane->SetChecked(nID);
}

void CMainFrame::OnUpdateRibbonMinimize(CCmdUI* pCmdUI)
{
	CXTPControl* pControl = CXTPControl::FromUI(pCmdUI);
	if (pControl)
	{
		CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)GetCommandBars()->GetMenuBar();
		pControl->SetVisible(!pRibbonBar->IsRibbonMinimized());
	}
	
}

void CMainFrame::OnUpdateRibbonExpand(CCmdUI* pCmdUI)
{
	CXTPControl* pControl = CXTPControl::FromUI(pCmdUI);
	if (pControl)
	{
		CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)GetCommandBars()->GetMenuBar();
		pControl->SetVisible(pRibbonBar->IsRibbonMinimized());
	}	
}

void CMainFrame::OnUpdateKeyIndicator(CCmdUI* pCmdUI)
{
	CXTPStatusBar* pStatusBar = DYNAMIC_DOWNCAST(CXTPStatusBar, pCmdUI->m_pOther);
	if (!pStatusBar)
		return;

	CXTPStatusBarPane* pPane = pStatusBar->GetPane(pCmdUI->m_nIndex);

	BOOL bVisible = ::GetKeyState(VK_CAPITAL) & 0x0001;
	pPane->SetVisible(bVisible);
	pPane->SetValue(bVisible ? _T("On") : _T("Off"));
}

void CMainFrame::OnMacroClick()
{
	CXTPStatusBarProgressPane* pPane = DYNAMIC_DOWNCAST(CXTPStatusBarProgressPane, m_wndStatusBar.FindPane(ID_INDICATOR_PROGRESS));
	if (!pPane)
		return;

	pPane->SetVisible(TRUE);

	pPane->SetPos(0);

	for (int i = 0; i <= 100; i += 5)
	{
		m_wndStatusBar.UpdateWindow();
		Sleep(1);
		pPane->SetPos(i);
	}

	pPane->SetVisible(FALSE);

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


void CMainFrame::CreateBackstage()
{
	CXTPRibbonBar* pRibbonBar = DYNAMIC_DOWNCAST(CXTPRibbonBar, GetCommandBars()->GetMenuBar());
	ASSERT (pRibbonBar);


	CXTPRibbonControlSystemButton* pButton = pRibbonBar->GetSystemButton();

	CXTPRibbonBackstageView* pView = CXTPRibbonBackstageView::CreateBackstageView(GetCommandBars());

	pView->AddCommand(ID_BACKSTAGE_SAVE);
	pView->AddCommand(ID_BACKSTAGE_SAVE_AS);
	pView->AddCommand(ID_FILE_OPEN);


	if (!m_pageInfo.GetSafeHwnd())
	{
		m_pageInfo.Create(CBackstagePageInfo::IDD, this);
	}

	if (!m_pageHelp.GetSafeHwnd())
	{
		m_pageHelp.Create(CBackstagePageHelp::IDD, this);
	}

	if (!m_pageSave.GetSafeHwnd())
	{
		m_pageSave.Create(CBackstagePageSave::IDD, this);
	}

	if (!m_pageRecent.GetSafeHwnd())
	{
		m_pageRecent.Create(CXTPRibbonBackstagePageRecent::IDD, this);
		//load translated backstage page:
		//m_pageRecent.CreateIndirect(XTPResourceManager()->LoadDialogTemplate(CXTPRibbonBackstagePageRecent::IDD), this);

		m_pageRecent.SetUseShellIcon(FALSE); // TRUE to improve performance but use generic shell icons.
	}

	if (!m_pageDisabled.GetSafeHwnd())
	{
		m_pageDisabled.Create(CXTPRibbonBackstagePageRecent::IDD, this);
		m_pageDisabled.SetUseShellIcon(FALSE); // TRUE to improve performance but use generic shell icons.
	}

	if (!m_pagePrint.GetSafeHwnd())
	{
		m_pagePrint.Create(CXTPRibbonBackstagePagePrint::IDD, this);
		//load translated backstage page:
		//m_pagePrint.CreateIndirect(XTPResourceManager()->LoadDialogTemplate(CXTPRibbonBackstagePagePrint::IDD), this);
	}
	

	CXTPRibbonBackstageTab* pTabInfo = pView->AddTab(&m_pageInfo, ID_BACKSTAGE_INFO);
	pTabInfo->SetFlags(xtpFlagManualUpdate); // No Need update with Update handler

	pTabInfo->SetControlPaneMinSize(XTP_DPI(CSize(650, 400)));

	CXTPRibbonBackstageTab* pTabRecent = pView->AddTab(&m_pageRecent, ID_BACKSTAGE_RECENT);
	pTabRecent->SetFlags(xtpFlagManualUpdate); // No Need update with Update handler

	CXTPRibbonBackstageTab* pTabDisabled = pView->AddTab(&m_pageDisabled, ID_BACKSTAGE_DISABLED);
	pTabDisabled->SetFlags(xtpFlagManualUpdate); // No Need update with Update handler
	pTabDisabled->SetEnabled(FALSE);

	CXTPRibbonBackstageTab* pTabPrint = pView->AddTab(&m_pagePrint, ID_BACKSTAGE_PRINT);
	pTabPrint->SetFlags(xtpFlagManualUpdate); // No Need update with Update handler
	
	CXTPRibbonBackstageTab* pTabSaveSend = pView->AddTab(&m_pageSave, ID_BACKSTAGE_SAVESEND);	
	pTabSaveSend->SetFlags(xtpFlagManualUpdate); // No Need update with Update handler
	
	CXTPRibbonBackstageTab* pTabHelp = pView->AddTab(&m_pageHelp, ID_BACKSTAGE_HELP);
	pTabHelp->SetFlags(xtpFlagManualUpdate); // No Need update with Update handler
	pTabHelp->SetIconId(ID_APP_ABOUT);

	pView->AddMenuSeparator();

	pView->AddCommand(ID_FOOTNOTES_SHOW);	//example of disabled Command
	GetCommandBars()->GetActions()->FindAction(ID_FOOTNOTES_SHOW)->SetEnabled(FALSE);

	pView->AddCommand(ID_APP_OPTIONS);
	pView->AddCommand(ID_APP_EXIT);

	pTabInfo->SetItemDefault(TRUE);

	pButton->SetCommandBar(pView);
	XTPPaintTheme	nPaintTheme = GetCommandBars()->GetPaintManager()->GetCurrentTheme();
	if (((nPaintTheme == xtpThemeOffice2013) || (xtpThemeVisualStudio2015 == nPaintTheme)) && m_bBackstageStyle2013)
		pView->SetBackstageStyle(xtpRibbonBackstageOffice2013Style);
	else
		pView->SetBackstageStyle(xtpRibbonBackstageOffice2010Style);

	pView->InternalRelease();
}


void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	CFrameWnd::OnGetMinMaxInfo(lpMMI);

	if (!GetCommandBars())
		return;

	CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)GetCommandBars()->GetMenuBar();

	if (pRibbonBar && pRibbonBar->IsBackstageViewVisible())
	{
		lpMMI->ptMinTrackSize.x = XTP_DPI_X(500);
		lpMMI->ptMinTrackSize.y = XTP_DPI_Y(400);

	}
}

LRESULT CMainFrame::OnMessageBarClosed(WPARAM wParam, LPARAM lParam)
{
	UNUSED_ALWAYS(wParam);
	CXTPMessageBar* pMessageBar = (CXTPMessageBar*)lParam;
	AfxMessageBox(_T("Message bar is being closed"), MB_ICONINFORMATION);
	
	return 0;
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
		case ID_OPTIONS_STYLE_OFFICE2013EXCEL:
		case ID_OPTIONS_STYLE_OFFICE2013ACCESS:
		case ID_OPTIONS_STYLE_OFFICE2013POWERPOINT:
		case ID_OPTIONS_STYLE_OFFICE2013ONENOTE:
			style = xtpToolTipOffice2013;
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


void CMainFrame::OnOptionsBackstageStyle2013()
{
	if (m_bBackstageStyle2013)
		m_bBackstageStyle2013 = FALSE;
	else
		m_bBackstageStyle2013 = TRUE;
	CXTPRibbonBar *pRibbonBar = (CXTPRibbonBar*)GetCommandBars()->GetMenuBar();
	CXTPRibbonBackstageView *pView = DYNAMIC_DOWNCAST(CXTPRibbonBackstageView, pRibbonBar->GetSystemButton()->GetCommandBar());
	if (pView)
	{
		if (m_bBackstageStyle2013)
			pView->SetBackstageStyle(xtpRibbonBackstageOffice2013Style);
		else
			pView->SetBackstageStyle(xtpRibbonBackstageOffice2010Style);
	}
	else
		m_bBackstageStyle2013 = FALSE;
}


void CMainFrame::OnUpdateOptionsBackstageStyle2013(CCmdUI *pCmdUI)
{
	XTPPaintTheme	nPaintTheme = GetCommandBars()->GetPaintManager()->GetCurrentTheme();
	if ((nPaintTheme == xtpThemeOffice2013) || (xtpThemeVisualStudio2015 == nPaintTheme))
	{
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(m_bBackstageStyle2013);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CMainFrame::OnViewOfficeTheme()
{
	m_dlgTheme.ShowWindow(SW_SHOW);
}

LRESULT CMainFrame::OnThemeChanged(WPARAM wParam, LPARAM lParam)
{
	int nTheme  = (int)LOWORD(wParam);
	int nColor  = (int)HIWORD(wParam);
	int nAccent = (int)LOWORD(lParam);
#ifdef _XTP_INCLUDE_RIBBON
	int nBack   = (int)HIWORD(lParam);
#endif

	switch (nTheme)
	{
    case xtpThemeDlgOffice2007:
		{
			switch (nColor)
			{
			case xtpThemeColor2007Blue:   OnStyleOffice2007(ID_OPTIONS_STYLE_OFFICE2007BLUE); break;
			case xtpThemeColor2007Silver: OnStyleOffice2007(ID_OPTIONS_STYLE_OFFICE2007SILVER); break;
			case xtpThemeColor2007Black:  OnStyleOffice2007(ID_OPTIONS_STYLE_OFFICE2007BLACK);  break;
			case xtpThemeColor2007Aqua:   OnStyleOffice2007(ID_OPTIONS_STYLE_OFFICE2007AQUA);   break;
			}
		}
		break;
    case xtpThemeDlgOffice2010:
		{
			switch (nColor)
			{
			case xtpThemeColor2010Blue:   OnStyleOffice2010(ID_OPTIONS_STYLE_OFFICE2010BLUE); break;
			case xtpThemeColor2010Silver: OnStyleOffice2010(ID_OPTIONS_STYLE_OFFICE2010SILVER); break;
			case xtpThemeColor2010Black:  OnStyleOffice2010(ID_OPTIONS_STYLE_OFFICE2010BLACK);  break;
			}
		}
		break;
    case xtpThemeDlgOffice2013:
		{
			switch (nColor)
			{
			case xtpThemeColor2013White:
				{
					m_eOffice2013Gray = eGrayNone;
					switch (nAccent)
					{
					case xtpThemeAccentAccess:     OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013ACCESS);     break;
					case xtpThemeAccentExcel:      OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013EXCEL);      break;
					case xtpThemeAccentOneNote:    OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013ONENOTE);    break;
					case xtpThemeAccentOutlook:    OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013OUTLOOK);    break;
					case xtpThemeAccentPowerPoint: OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013PUBLISHER);  break;
					case xtpThemeAccentPublisher:  OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013POWERPOINT); break;
					case xtpThemeAccentWord:       OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013WORD);       break;
					}
				}
				break;
			case xtpThemeColor2013GrayLight:
				{
					m_eOffice2013Gray = eGrayLight;
					switch (nAccent)
					{
					case xtpThemeAccentAccess:     OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013ACCESS);     break;
					case xtpThemeAccentExcel:      OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013EXCEL);      break;
					case xtpThemeAccentOneNote:    OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013ONENOTE);    break;
					case xtpThemeAccentOutlook:    OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013OUTLOOK);    break;
					case xtpThemeAccentPowerPoint: OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013PUBLISHER);  break;
					case xtpThemeAccentPublisher:  OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013POWERPOINT); break;
					case xtpThemeAccentWord:       OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013WORD);       break;
					}
				}
				break;
			case xtpThemeColor2013GrayDark:
				{
					m_eOffice2013Gray = eGrayDark;
					switch (nAccent)
					{
					case xtpThemeAccentAccess:     OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013ACCESS);     break;
					case xtpThemeAccentExcel:      OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013EXCEL);      break;
					case xtpThemeAccentOneNote:    OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013ONENOTE);    break;
					case xtpThemeAccentOutlook:    OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013OUTLOOK);    break;
					case xtpThemeAccentPowerPoint: OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013PUBLISHER);  break;
					case xtpThemeAccentPublisher:  OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013POWERPOINT); break;
					case xtpThemeAccentWord:       OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013WORD);       break;
					}
				}
				break;
			}
#ifdef _XTP_INCLUDE_RIBBON
			SetRibbonBackImage(nBack);
#endif
		}
		break;
    case xtpThemeDlgOffice2016:
		{
			switch (nColor)
			{
			case xtpThemeColor2016Black:
				{
					switch (nAccent)
					{
					case xtpThemeAccentAccess:
						m_enumTheme = CRibbonSampleApp::themeOffice2013Access;
						SetOffice2016Theme(xtpIniOffice2016AccessBlack);
						break;
					case xtpThemeAccentExcel:
						m_enumTheme = CRibbonSampleApp::themeOffice2013Excel;
						SetOffice2016Theme(xtpIniOffice2016ExcelBlack);
						break;
					case xtpThemeAccentOneNote:
						m_enumTheme = CRibbonSampleApp::themeOffice2013OneNote;
						SetOffice2016Theme(xtpIniOffice2016ExcelBlack);
						break;
					case xtpThemeAccentOutlook:
						m_enumTheme = CRibbonSampleApp::themeOffice2013Outlook;
						SetOffice2016Theme(xtpIniOffice2016OutlookBlack);
						break;
					case xtpThemeAccentPowerPoint:
						m_enumTheme = CRibbonSampleApp::themeOffice2013PowerPoint;
						SetOffice2016Theme(xtpIniOffice2016PowerPointBlack);
						break;
					case xtpThemeAccentPublisher:
						m_enumTheme = CRibbonSampleApp::themeOffice2013Publisher;
						SetOffice2016Theme(xtpIniOffice2016PublisherBlack);
						break;
					case xtpThemeAccentWord:
						m_enumTheme = CRibbonSampleApp::themeOffice2013Word;
						SetOffice2016Theme(xtpIniOffice2016WordBlack);
						break;
					}
				}
				break;
			case xtpThemeColor2016White:
				{
					switch (nAccent)
					{
					case xtpThemeAccentAccess:
						m_enumTheme = CRibbonSampleApp::themeOffice2013Access;
						SetOffice2016Theme(xtpIniOffice2016AccessWhite);
						break;
					case xtpThemeAccentExcel:
						m_enumTheme = CRibbonSampleApp::themeOffice2013Excel;
						SetOffice2016Theme(xtpIniOffice2016ExcelWhite);
						break;
					case xtpThemeAccentOneNote:
						m_enumTheme =CRibbonSampleApp::themeOffice2013OneNote;
						SetOffice2016Theme(xtpIniOffice2016OneNoteWhite);
						break;
					case xtpThemeAccentOutlook:
						m_enumTheme = CRibbonSampleApp::themeOffice2013Outlook;
						SetOffice2016Theme(xtpIniOffice2016OutlookWhite);
						break;
					case xtpThemeAccentPowerPoint:
						m_enumTheme = CRibbonSampleApp::themeOffice2013PowerPoint;
						SetOffice2016Theme(xtpIniOffice2016PowerPointWhite);
						break;
					case xtpThemeAccentPublisher:
						m_enumTheme = CRibbonSampleApp::themeOffice2013Publisher;
						SetOffice2016Theme(xtpIniOffice2016PublisherWhite);
						break;
					case xtpThemeAccentWord:
						m_enumTheme = CRibbonSampleApp::themeOffice2013Word;
						SetOffice2016Theme(xtpIniOffice2016WordWhite);
						break;
					}
				}
				break;
			case xtpThemeColor2016Colorful:
				{
					switch (nAccent)
					{
					case xtpThemeAccentAccess:
						m_enumTheme = CRibbonSampleApp::themeOffice2013Access;
						SetOffice2016Theme(xtpIniOffice2016AccessColorful);
						break;
					case xtpThemeAccentExcel:
						m_enumTheme = CRibbonSampleApp::themeOffice2013Excel;
						SetOffice2016Theme(xtpIniOffice2016ExcelColorful);
						break;
					case xtpThemeAccentOneNote:
						m_enumTheme = CRibbonSampleApp::themeOffice2013OneNote;
						SetOffice2016Theme(xtpIniOffice2016OneNoteColorful);
						break;
					case xtpThemeAccentOutlook:
						m_enumTheme = CRibbonSampleApp::themeOffice2013Outlook;
						SetOffice2016Theme(xtpIniOffice2016OutlookColorful);
						break;
					case xtpThemeAccentPowerPoint:
						m_enumTheme = CRibbonSampleApp::themeOffice2013PowerPoint;
						SetOffice2016Theme(xtpIniOffice2016PowerPointColorful);
						break;
					case xtpThemeAccentPublisher:
						m_enumTheme = CRibbonSampleApp::themeOffice2013Publisher;
						SetOffice2016Theme(xtpIniOffice2016PublisherColorful);
						break;
					case xtpThemeAccentWord:
						m_enumTheme = CRibbonSampleApp::themeOffice2013Word;
						SetOffice2016Theme(xtpIniOffice2016WordColorful);
						break;
					}
				}
				break;
			case xtpThemeColor2016GrayDark:
				{
					switch (nAccent)
					{
					case xtpThemeAccentAccess:
						m_enumTheme = CRibbonSampleApp::themeOffice2013Access;
						SetOffice2016Theme(xtpIniOffice2016AccessDarkGray);
						break;
					case xtpThemeAccentExcel:
						m_enumTheme = CRibbonSampleApp::themeOffice2013Excel;
						SetOffice2016Theme(xtpIniOffice2016ExcelDarkGray);
						break;
					case xtpThemeAccentOneNote:
						m_enumTheme = CRibbonSampleApp::themeOffice2013OneNote;
						SetOffice2016Theme(xtpIniOffice2016OneNoteDarkGray);
						break;
					case xtpThemeAccentOutlook:
						m_enumTheme = CRibbonSampleApp::themeOffice2013Outlook;
						SetOffice2016Theme(xtpIniOffice2016OutlookDarkGray);
						break;
					case xtpThemeAccentPowerPoint:
						m_enumTheme = CRibbonSampleApp::themeOffice2013PowerPoint;
						SetOffice2016Theme(xtpIniOffice2016PowerPointDarkGray);
						break;
					case xtpThemeAccentPublisher:
						m_enumTheme = CRibbonSampleApp::themeOffice2013Publisher;
						SetOffice2016Theme(xtpIniOffice2016PublisherDarkGray);
						break;
					case xtpThemeAccentWord:
						m_enumTheme = CRibbonSampleApp::themeOffice2013Word;
						SetOffice2016Theme(xtpIniOffice2016WordDarkGray);
						break;
					}
				}
				break;
			}
#ifdef _XTP_INCLUDE_RIBBON
			SetRibbonBackImage(nBack);
#endif
		}
		break;
    case xtpThemeDlgVisualStudio2015:
		{
			switch (nColor)
			{
			case xtpThemeColor2015Blue:  OnOptionsStyleVisualStudio2015(ID_OPTIONS_STYLE_VISUALSTUDIO2015BLUE);  break;
			case xtpThemeColor2015Dark:  OnOptionsStyleVisualStudio2015(ID_OPTIONS_STYLE_VISUALSTUDIO2015DARK);  break;
			case xtpThemeColor2015Light: OnOptionsStyleVisualStudio2015(ID_OPTIONS_STYLE_VISUALSTUDIO2015LIGHT);  break;
			}
		}
		break;
	}

	return 0;
}

void CMainFrame::SetRibbonBackImage(int nBack)
{
	UINT nStyle = ID_OPTIONS_STYLE_OFFICE2013_BACK_NONE;
	switch (nBack)
	{
    case xtpThemeRibbonBackNone:
		nStyle = ID_OPTIONS_STYLE_OFFICE2013_BACK_NONE;
		break;
    case xtpThemeRibbonBackCalligraphy:
		nStyle = ID_OPTIONS_STYLE_OFFICE2013_BACK_CALLIGRAPHY;
		break;
	case xtpThemeRibbonBackCirclesStripes:
		nStyle = ID_OPTIONS_STYLE_OFFICE2013_BACK_CIRCLESANDSTRIPES;
		break;
    case xtpThemeRibbonBackCircuit:
		nStyle = ID_OPTIONS_STYLE_OFFICE2013_BACK_CIRCUIT;
		break;
    case xtpThemeRibbonBackClouds:
		nStyle = ID_OPTIONS_STYLE_OFFICE2013_BACK_CLOUDS;
		break;
    case xtpThemeRibbonBackDoodleCircles:
		nStyle = ID_OPTIONS_STYLE_OFFICE2013_BACK_DOODLECIRCLES;
		break;
    case xtpThemeRibbonBackDoodleDiamonds:
		nStyle = ID_OPTIONS_STYLE_OFFICE2013_BACK_DOODLEDIAMONDS;
		break;
    case xtpThemeRibbonBackGeometry:
		nStyle = ID_OPTIONS_STYLE_OFFICE2013_BACK_GEOMETRY;
		break;
    case xtpThemeRibbonBackLunchBox:
		nStyle = ID_OPTIONS_STYLE_OFFICE2013_BACK_LUNCHBOX;
		break;
    case xtpThemeRibbonBackSchoolSupplies:
		nStyle = ID_OPTIONS_STYLE_OFFICE2013_BACK_SCHOOLSUPPLIES;
		break;
    case xtpThemeRibbonBackSpring:
		nStyle = ID_OPTIONS_STYLE_OFFICE2013_BACK_SPRING;
		break;
    case xtpThemeRibbonBackStars:
		nStyle = ID_OPTIONS_STYLE_OFFICE2013_BACK_STARS;
		break;
    case xtpThemeRibbonBackStraws:
		nStyle = ID_OPTIONS_STYLE_OFFICE2013_BACK_STRAWS;
		break;
    case xtpThemeRibbonBackTreeRings:
		nStyle = ID_OPTIONS_STYLE_OFFICE2013_BACK_TREERINGS;
		break;
    case xtpThemeRibbonBackUnderWater:
		nStyle = ID_OPTIONS_STYLE_OFFICE2013_BACK_UNDERWATER;
		break;
	default:
		nStyle = ID_OPTIONS_STYLE_OFFICE2013_BACK_NONE;
	}
	OnOptionsStyleOffice2013Back(nStyle);
}

void CMainFrame::SetOffice2016Theme(LPCTSTR lpszINI /*=NULL*/)
{
	SetCommandBarsTheme(xtpThemeOffice2013, lpszINI);
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if (pCommandBars)
	{
		pCommandBars->SetAllCaps(TRUE);
		pCommandBars->GetPaintManager()->m_bAutoResizeIcons = TRUE;
		pCommandBars->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE, FALSE);

		CXTPToolTipContext* pContext = pCommandBars->GetToolTipContext();
		if (pContext)
		{
			pContext->SetStyle(xtpToolTipOffice2013);
		}

		CXTPPaintManager* pPaintManager = pCommandBars->GetPaintManager();
		if (pPaintManager)
		{
			pPaintManager->RefreshMetrics();
		}

		CXTPRibbonBar* pRibbonBar = DYNAMIC_DOWNCAST(CXTPRibbonBar, pCommandBars->GetMenuBar());
		if (pRibbonBar)
		{
			CXTPRibbonControlSystemButton* pSysButton = pRibbonBar->GetSystemButton();
			if (pSysButton)
			{
				pSysButton->SetStyle(xtpButtonCaption);
			}
		}
	}

	CreateBackstage();

#ifdef _XTP_INCLUDE_DOCKINGPANE
	SetDockingPaneTheme(xtpPaneThemeOffice2013);
#endif

	m_wndStatusBar.SetAllCaps(TRUE);
	SetFrameIcon(CSize(20, 20));

	OnUpdateCommands();

	m_nRibbonStyle = ID_OPTIONS_STYLE_OFFICE2013WORD;
}