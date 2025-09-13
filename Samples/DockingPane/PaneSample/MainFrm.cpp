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
#include "Pane.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#define VISIO_EDIT_BACKGROUND
//#define VISIO_OFFICE2003_THEME
BOOL m_bMinMaxSample = FALSE;

using namespace XTPDockingPanePaintThemes;

//////////////////////////////////////////////////////////////////////////
// CCustomTheme

class CCustomTheme :  public CXTPDockingPaneGripperedTheme
{
	virtual void DrawCaption(CDC* pDC, CXTPDockingPaneTabbedContainer* pPane, CRect rc)
	{
		CRect rcCaption(0, XTP_DPI_Y(2), rc.right, m_nTitleHeight + XTP_DPI_Y(1));

		// Drawing Frame
		pDC->FillSolidRect(rcCaption, GetSysColor(COLOR_3DFACE));
		pDC->Draw3dRect(XTP_DPI_X(1), rc.top + XTP_DPI_Y(1), 
			rc.Width() - XTP_DPI_X(1), rcCaption.bottom + XTP_DPI_Y(1), 
			GetSysColor(COLOR_WINDOW), GetSysColor(COLOR_WINDOW));
		pDC->Draw3dRect(0, rc.top, rc.Width() - XTP_DPI_X(1), rcCaption.bottom + XTP_DPI_Y(2), 
			GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DSHADOW));

		COLORREF clrText = GetSysColor(COLOR_BTNTEXT);

		rcCaption.right -= XTP_DPI_X(3);
		DrawCaptionButtons(pDC, pPane->GetCaptionButtons(), rcCaption, clrText, 
			XTP_DPI_X(14), XTP_DPI_X(2), FALSE);

		// Drawing Title
		if (pPane->GetSelected())
		{
			CRect rcText(rcCaption.left + XTP_DPI_X(4), rcCaption.top + XTP_DPI_Y(1), 
				rcCaption.right, rcCaption.bottom);

			pDC->SetTextColor(clrText);
			CXTPFontDC font(pDC, &m_xtpFontTitle);
			pDC->DrawText(pPane->GetSelected()->GetTitle(), rcText, DT_SINGLELINE|DT_END_ELLIPSIS|DT_VCENTER);
		}
	}

};

//////////////////////////////////////////////////////////////////////////
// CEditPane

CEditPane::CEditPane() : m_pPane(NULL)
{
}

BEGIN_MESSAGE_MAP(CEditPane, CEdit)
	//{{AFX_MSG_MAP(CEditPane)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CEditPane::SetOwnerPane(CXTPDockingPane* pPane)
{
	ASSERT(pPane);
	m_pPane = pPane;
}

LRESULT CEditPane::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_NCPAINT)
	{
		CWindowDC dc(this);
		CXTPWindowRect rWindow(this);
		rWindow.OffsetRect(-rWindow.TopLeft());

		theApp.m_csPane.DrawBorders(&dc, rWindow, m_pPane);
		return TRUE;
	}

	return CEdit::WindowProc(message, wParam, lParam);
}

HBRUSH CEditPane::CtlColor(CDC* pDC, UINT /*nCtlColor*/)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	
	if (pMainFrame)
	{
		pDC->SetTextColor(theApp.m_csPane.m_clrText);
		pDC->SetBkColor(theApp.m_csPane.m_clrBack);

		m_brush.DeleteObject();
		m_brush.CreateSolidBrush(theApp.m_csPane.m_clrBack);

		return m_brush;
	}

	return ::GetSysColorBrush(COLOR_WINDOW);
}

void CEditPane::OnSize(UINT nType, int cx, int cy)
{
	CEdit::OnSize(nType, cx, cy);

	if (!m_bMinMaxSample || (cx == 0 && cy == 0))
		return;

	if (m_pPane)
	{
		MINMAXINFO mmi;
		m_pPane->GetMinMaxInfo(&mmi);

		CString strInfo;

		if (mmi.ptMinTrackSize.x > 0)
		{
			CXTPWindowRect rc(this);

			strInfo.Format(_T("Tracking Size:\r\nMin (%i, %i)\r\nMax (%i, %i)\r\nCurrent (%i, %i)"),
				mmi.ptMinTrackSize.x, mmi.ptMinTrackSize.y, mmi.ptMaxTrackSize.x, mmi.ptMaxTrackSize.y, rc.Width(), rc.Height());
		}
		SetWindowText(strInfo);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_LAYOUT_RUN, OnLayoutRun)
	ON_COMMAND(ID_LAYOUT_EDITOR, OnLayoutEditor)
	ON_UPDATE_COMMAND_UI(ID_LAYOUT_EDITOR, OnUpdateLayoutEditor)
	ON_UPDATE_COMMAND_UI(ID_LAYOUT_RUN, OnUpdateLayoutRun)
	ON_WM_DESTROY()
	ON_COMMAND(ID_LAYOUT_LOADFROMFILE, OnLoadFromFile)
	ON_COMMAND(ID_LAYOUT_SAVETOFILE, OnSaveToFile)
	ON_COMMAND(ID_LAYOUT_LOADFROMRESOURCE, OnLoadFromResource)
	ON_COMMAND(ID_DOCKINGPANE_HIDECLIENT, OnHideClient)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_HIDECLIENT, OnUpdateHideClient)
	ON_COMMAND(ID_DOCKINGPANE_USESPLITTERTRACKER, OnUseSplitterTracker)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_USESPLITTERTRACKER, OnUpdateUseSplitterTracker)
	ON_COMMAND(ID_DOCKINGPANE_THEMEDFLOATINGFRAMES, OnThemedFloatingFrames)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_THEMEDFLOATINGFRAMES, OnUpdateThemedFloatingFrames)
	ON_COMMAND(ID_DOCKINGCONTEXT_ALPHACONTEXT, OnAlphaContext)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGCONTEXT_ALPHACONTEXT, OnUpdateAlphaContext)
	ON_COMMAND(ID_DOCKINGCONTEXT_DOCKINGSTICKERS, OnDockingStickers)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGCONTEXT_DOCKINGSTICKERS, OnUpdateDockingStickers)
	ON_COMMAND(ID_DOCKINGPANE_MINMAXSAMPLE, OnMinMaxSample)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_MINMAXSAMPLE, OnUpdateMinMaxSample)
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_DOCKINGPANE_CAPTIONBUTTONS_CLOSEBUTTON, OnCaptionButtonClose)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_CAPTIONBUTTONS_CLOSEBUTTON, OnUpdateCaptionButtonClose)
	ON_COMMAND(ID_DOCKINGPANE_CAPTIONBUTTONS_AUTOHIDEBUTTON, OnCaptionButtonAutoHide)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_CAPTIONBUTTONS_AUTOHIDEBUTTON, OnUpdateCaptionButtonAutoHide)
	ON_COMMAND(ID_DOCKINGPANE_CAPTIONBUTTONS_MENUBUTTON, OnCaptionButtonMenu)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_CAPTIONBUTTONS_MENUBUTTON, OnUpdateCaptionButtonMenu)
	ON_COMMAND(ID_DOCKINGPANE_CAPTIONBUTTONS_MAXIMIZERESTOREBUTTON, OnCaptionButtonMaximize)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_CAPTIONBUTTONS_MAXIMIZERESTOREBUTTON, OnUpdateCaptionButtonMaximize)
	ON_COMMAND(ID_DOCKINGPANE_CAPTIONBUTTONS_MAXIMIZERESTOREBUTTON_FLOATING, OnCaptionButtonMaximizeFloating)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_CAPTIONBUTTONS_MAXIMIZERESTOREBUTTON_FLOATING, OnUpdateCaptionButtonMaximizeFloating)
	ON_COMMAND(ID_DOCKINGPANE_CAPTIONS_VISIBLE, OnCaptionVisible)
	ON_COMMAND(ID_DOCKINGPANE_CAPTIONS_CUSTOM_TITLES, OnCaptionUseCustomTitles)
	ON_COMMAND(ID_DOCKINGPANE_CAPTIONS_HORIZONTAL, OnCaptionHorizontal)
	ON_COMMAND(ID_DOCKINGPANE_CAPTIONS_VERTICAL, OnCaptionVertical)
	ON_COMMAND(ID_DOCKINGPANE_CAPTIONS_AUTOBYSIZE, OnCaptionAutoBySize)
	ON_COMMAND(ID_DOCKINGPANE_CAPTIONS_AUTOBYPOSITION, OnCaptionAutoByPosition)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_CAPTIONS_VISIBLE, OnUpdateCaptionVisible)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_CAPTIONS_CUSTOM_TITLES, OnUpdateCaptionUseCustomTitles)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_CAPTIONS_HORIZONTAL, OnUpdateCaptionHorizontal)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_CAPTIONS_VERTICAL, OnUpdateCaptionVertical)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_CAPTIONS_AUTOBYSIZE, OnUpdateCaptionAutoBySize)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_CAPTIONS_AUTOBYPOSITION, OnUpdateCaptionAutoByPosition)
	ON_COMMAND(ID_DOCKINGPANE_CLOSEBUTTONAFFECTS, OnCloseButtonAffects)
	ON_COMMAND(ID_DOCKINGPANE_AUTOHIDEBUTTONAFFECTS, OnAutoHideButtonAffects)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_CLOSEBUTTONAFFECTS, OnUpdateCloseButtonAffects)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_AUTOHIDEBUTTONAFFECTS, OnUpdateAutoHideButtonAffects)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGCONTEXT_SHOWWHILEDRAGGING, OnUpdateShowContentsWhileDragging)
	ON_COMMAND(ID_DOCKINGCONTEXT_SHOWWHILEDRAGGING, OnShowContentsWhileDragging)
	ON_COMMAND(ID_DOCKINGPANE_STICKYFLOATINGFRAMES, OnStickyFloatingFrames)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_STICKYFLOATINGFRAMES, OnUpdateStickyFloatingFrames)
	ON_COMMAND(ID_DOCKINGPANE_TRANSPARENTFLOATINGFRAMES, OnTransparentFloatingFrames)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_TRANSPARENTFLOATINGFRAMES, OnUpdateTransparentFloatingFrames)
	ON_COMMAND(ID_DOCKINGCONTEXT_ENABLESIDEDOCKING, OnEnableSideDocking)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGCONTEXT_ENABLESIDEDOCKING, OnUpdateEnableSideDocking)
	ON_COMMAND(ID_DOCKINGPANE_THEME, OnDockingPaneTheme)
	//}}AFX_MSG_MAP

	ON_COMMAND_RANGE(IDR_PANE1, IDR_PANE10, OnShowPane)
	ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify)

#ifdef _XTP_INCLUDE_COMMANDBARS
	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
	ON_WM_CLOSE()
#endif

	ON_WM_XTP_THEMECHANGED()

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame construction/destruction

CMainFrame::CMainFrame()
	: m_pEditorLayout(NULL)
	, m_pRunLayout(NULL)
	, m_fUseCustomPaneTitleBrushes(FALSE)
{

}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	LOGFONT lfIcon;
	VERIFY( ::SystemParametersInfo( SPI_GETICONTITLELOGFONT, sizeof( lfIcon ), &lfIcon, 0 ) );
	m_fntEdit.CreateFontIndirect(&lfIcon);


#ifndef _XTP_INCLUDE_COMMANDBARS

	// create and initialize all control bars prior to
	// creating docking panes...

	if (!m_wndToolBar.Create(this, TBSTYLE_FLAT|WS_CHILD | WS_VISIBLE | CBRS_TOP
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

	XTPColorManager()->DisableLunaColors();

#else

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

	CXTPCommandBar* pMenuBar = pCommandBars->SetMenu(_T("Menu Bar"), IDR_MAINFRAME);
	pMenuBar->SetFlags(xtpFlagAddMDISysPopup);


	CXTPToolBar* pCommandBar = (CXTPToolBar*)pCommandBars->Add(_T("Standard"), xtpBarTop);
	if (!pCommandBar ||
		!pCommandBar->LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	// Load the previous state for toolbars and menus.
	//LoadCommandBars(_T("CommandBars"));

#endif

	// Initialize the docking pane manager and set the
	// initial them for the docking panes.  Do this only after all
	// control bars objects have been created and docked.
	m_paneManager.InstallDockingPanes(this);
	m_paneManager.SetFloatingFrameCaption(_T("Panes"));
	m_paneManager.SetStickyFloatingFrames(TRUE);
	m_paneManager.SetThemedFloatingFrames(TRUE);
	m_paneManager.SetAlphaDockingContext(TRUE);
	m_paneManager.SetShowDockingContextStickers(TRUE);
	m_paneManager.SetShowContentsWhileDragging(TRUE);
	m_paneManager.SetSideDockingMargin(XTP_DPI(CRect(2, 2, 2, 2)));
	m_paneManager.EnableSideDocking();
	m_paneManager.EnableKeyboardNavigate();

	// Create docking panes.
	CXTPDockingPane* pwndPane1 = m_paneManager.CreatePane(
		IDR_PANE1, XTP_DPI(CRect(0, 0, 200, 120)), xtpPaneDockTop);
	m_paneManager.CreatePane(
		IDR_PANE2, XTP_DPI(CRect(0, 0, 200, 120)), xtpPaneDockLeft, pwndPane1);
	CXTPDockingPane* pwndPane3 = m_paneManager.CreatePane(
		IDR_PANE3, XTP_DPI(CRect(0, 0, 200, 120)), xtpPaneDockLeft);
	CXTPDockingPane* pwndPane4 = m_paneManager.CreatePane(
		IDR_PANE4, XTP_DPI(CRect(0, 0, 200, 120)), xtpPaneDockTop, pwndPane3);
	CXTPDockingPane* pwndPane5 = m_paneManager.CreatePane(
		IDR_PANE5, XTP_DPI(CRect(0, 0, 200, 120)), xtpPaneDockLeft, pwndPane4);
	CXTPDockingPane* pwndPane6 = m_paneManager.CreatePane(
		IDR_PANE6, XTP_DPI(CRect(0, 0, 200, 120)), xtpPaneDockTop, pwndPane5);
	CXTPDockingPane* pwndPane7 = m_paneManager.CreatePane(
		IDR_PANE7, XTP_DPI(CRect(0, 0, 200, 120)), xtpPaneDockTop, pwndPane6);
	CXTPDockingPane* pwndPane8 = m_paneManager.CreatePane(
		IDR_PANE8, XTP_DPI(CRect(0, 0, 200, 120)), xtpPaneDockRight);
	CXTPDockingPane* pwndPane9 = m_paneManager.CreatePane(
		IDR_PANE9, XTP_DPI(CRect(0, 0, 200, 120)), xtpPaneDockBottom, pwndPane8);
	CXTPDockingPane* pwndPane10 = m_paneManager.CreatePane(
		IDR_PANE10, XTP_DPI(CRect(0, 0, 200, 120)), xtpPaneDockBottom, pwndPane9);

	// Create custom pane title brushes.
	m_customPaneTitleBrushes.active.CreateSolidBrush(RGB(46, 90, 90));
	m_customPaneTitleBrushes.inactive.CreateSolidBrush(RGB(64, 128, 128));

	// Create the layout manager for run mode.  Layouts define how
	// the panes will appear when docked, you can define multiple
	// layouts.

	// If "RunLayout" layout does not exist, save the current configuration
	// as "RunLayout", otherwise load previous state.
	m_pRunLayout = m_paneManager.CreateLayout();
	if (!m_pRunLayout->Load(_T("RunLayout"))) {
		m_paneManager.GetLayout(m_pRunLayout);
	}

	// Initialize the default layout for "EditorLayout".
	m_paneManager.AttachPane(
		pwndPane9, pwndPane8);
	m_paneManager.AttachPane(
		pwndPane6, pwndPane1);
	m_paneManager.AttachPane(
		pwndPane4, pwndPane7);
	m_paneManager.HidePane(
		pwndPane7);

	CXTPDockingPaneSidePanel* pPanel = m_paneManager.DockSidePane(pwndPane10, 
		xtpPaneDockRight, XTP_DPI(CRect(0, 100, 120, 300)));
	pPanel->Collapse();

	// If "EditorLayout" layout does not exist, save the current configuration
	// as "EditorLayout", otherwise load previous state and set it as the active
	// layout.
	m_pEditorLayout = m_paneManager.CreateLayout();

	if (m_pEditorLayout->Load(_T("EditorLayout"))) {
		m_paneManager.SetLayout(m_pEditorLayout);
	}
	else {
		m_paneManager.GetLayout(m_pEditorLayout);
	}

	// Get a pointer to IDR_PANE1 and set the title.
	CXTPDockingPane* pPane = m_paneManager.FindPane(IDR_PANE1);
	ASSERT(pPane);
	if (pPane) {
		pPane->SetTitle(_T("Pane 1 - Long Title\nPane 1"));
	}

	// Get a pointer to IDR_PANE2 and set the title.
	pPane = m_paneManager.FindPane(IDR_PANE2);
	ASSERT(pPane);
	if (pPane) {
		pPane->SetTitle(_T("Pane 2 - No Closeable\nPane 2"));
		pPane->SetOptions(xtpPaneNoCloseable);
	}

	// Get a pointer to IDR_PANE3 and set the title.
	pPane = m_paneManager.FindPane(IDR_PANE3);
	ASSERT(pPane);
	if (pPane) {
		pPane->SetTitle(_T("Pane 3 - No Hideable\nPane 3"));
		pPane->SetOptions(xtpPaneNoHideable);
	}


	m_bEditor = TRUE;

	// Set the icons for the docking pane tabs.
	int nIDs1[] = {IDR_PANE1, IDR_PANE2, IDR_PANE3, IDR_PANE4, IDR_PANE5};
	m_paneManager.SetIcons(IDB_BITMAP1, nIDs1, 5, RGB(0, 255, 0));

	int nIDs2[] = {IDR_PANE6, IDR_PANE7, IDR_PANE8, IDR_PANE9, IDR_PANE10};
	m_paneManager.SetIcons(IDB_BITMAP2, nIDs2, 5, RGB(0, 255, 0));

	// exclude unused themes.
	m_dlgTheme.ExcludeTheme(
		XTP_EXCLUDE_THEME_VISUALSTUDIO6    | 
		XTP_EXCLUDE_THEME_VISUALSTUDIO2008 | 
		XTP_EXCLUDE_THEME_VISUALSTUDIO2010);

	// create theme dialog.
	VERIFY(m_dlgTheme.Create(IDD_THEME_DIALOG, this));

	// set startup theme
	m_dlgTheme.SetTheme(
		xtpThemeDlgOffice2016,
		xtpThemeColor2016Colorful,
		xtpThemeAccentOutlook, -1, TRUE);

	// enable auto preview.
	m_dlgTheme.EnableAutoPreview(TRUE);

	// rename custom item.
	m_dlgTheme.RenameItem(_T("Custom"), _T("Grippered"));

	// add additional themes.
	m_dlgTheme.InsertAfter(_T("Office 2000"),       int(xtpThemeDlgCustom+1), _T("Office 2000 Visio"));
	m_dlgTheme.InsertAfter(_T("Office XP"),         int(xtpThemeDlgCustom+2), _T("Office XP Visio"));
	m_dlgTheme.InsertAfter(_T("Office 2003"),       int(xtpThemeDlgCustom+3), _T("Office 2003 Visio"));
	m_dlgTheme.InsertAfter(_T("Office 2003 Visio"), int(xtpThemeDlgCustom+4), _T("Office 2003 ShortcutBar"));
	m_dlgTheme.InsertAfter(_T("Office 2007"),       int(xtpThemeDlgCustom+5), _T("Office 2007 Word"));
	m_dlgTheme.InsertAfter(_T("Native Windows"),    int(xtpThemeDlgCustom+6), _T("Explorer"));

	// add custom themes.
	m_dlgTheme.AddCustomTheme(int(xtpThemeDlgCustom+7),  _T("Custom Caption"));
	m_dlgTheme.AddCustomTheme(int(xtpThemeDlgCustom+8),  _T("Custom Tabs At Top"));
	m_dlgTheme.AddCustomTheme(int(xtpThemeDlgCustom+9),  _T("Custom State Buttons"));
	m_dlgTheme.AddCustomTheme(int(xtpThemeDlgCustom+10), _T("Custom Excel"));

	return 0;
}

void CMainFrame::OnDockingPaneTheme() 
{
	m_dlgTheme.ShowWindow(SW_SHOW);
}

void CMainFrame::SetTheme(XTPPaintTheme nTheme, LPCTSTR lpszINI /*=NULL*/)
{
#ifdef _XTP_INCLUDE_COMMANDBARS
	SetCommandBarsTheme(nTheme, lpszINI);
#else
	UNREFERENCED_PARAMETER(nTheme);
	if (lpszINI)
	{
		XTPThemeDLL()->SetHandle(lpszINI);
	}
#endif
	SendMessage(WM_NCPAINT);
	RedrawWindow(0, 0, RDW_ALLCHILDREN|RDW_INVALIDATE);
}

LRESULT CMainFrame::OnThemeChanged(WPARAM wParam, LPARAM lParam)
{
	int nTheme  = (int)LOWORD(wParam);
	int nColor  = (int)HIWORD(wParam);
	int nAccent = (int)LOWORD(lParam);

	switch (nTheme)
	{
    case xtpThemeDlgOffice2000:
		{
			SetTheme(xtpThemeOffice2000);
			AdjustStyle(xtpPaneThemeDefault);
			SetDockingPaneTheme(xtpPaneThemeDefault);
		}
		break;
    case xtpThemeDlgOfficeXP:
		{
			SetTheme(xtpThemeOfficeXP);
			AdjustStyle(xtpPaneThemeVisualStudio2003);
			SetDockingPaneTheme(xtpPaneThemeVisualStudio2003);
		}
		break;
    case xtpThemeDlgOffice2003:
		{
			SetTheme(xtpThemeOffice2003);
			AdjustStyle(xtpPaneThemeVisualStudio2003);
			SetDockingPaneTheme(xtpPaneThemeOffice2003);
		}
		break;
    case xtpThemeDlgOffice2007:
		{
			switch (nColor)
			{
			case xtpThemeColor2007Blue:
				{
					SetTheme(xtpThemeRibbon, xtpIniOffice2007Blue);
					AdjustStyle(xtpPaneThemeVisualStudio2003);
					SetDockingPaneTheme(xtpPaneThemeResource, xtpPaneStickerStyleVisualStudio2005, XTP_DPI_X(3));
				}
				break;
			case xtpThemeColor2007Silver:
				{
					SetTheme(xtpThemeRibbon, xtpIniOffice2007Silver);
					AdjustStyle(xtpPaneThemeVisualStudio2003);
					SetDockingPaneTheme(xtpPaneThemeResource, xtpPaneStickerStyleVisualStudio2005, XTP_DPI_X(3));
				}
				break;
			case xtpThemeColor2007Black:
				{
					SetTheme(xtpThemeRibbon, xtpIniOffice2007Black);
					AdjustStyle(xtpPaneThemeVisualStudio2003);
					SetDockingPaneTheme(xtpPaneThemeResource, xtpPaneStickerStyleVisualStudio2005, XTP_DPI_X(3));
				}
				break;
			case xtpThemeColor2007Aqua:
				{
					SetTheme(xtpThemeRibbon, xtpIniOffice2007Aqua);
					AdjustStyle(xtpPaneThemeVisualStudio2003);
					SetDockingPaneTheme(xtpPaneThemeResource, xtpPaneStickerStyleVisualStudio2005, XTP_DPI_X(3));
				}
				break;
			}
		}
		break;
    case xtpThemeDlgOffice2010:
		{
			switch (nColor)
			{
			case xtpThemeColor2010Blue:
				{
					SetTheme(xtpThemeRibbon, xtpIniOffice2010Blue);
					SetDockingPaneTheme(xtpPaneThemeResource, xtpPaneStickerStyleVisualStudio2005, XTP_DPI_X(3));
				}
				break;
			case xtpThemeColor2010Silver:
				{
					SetTheme(xtpThemeRibbon, xtpIniOffice2010Silver);
					SetDockingPaneTheme(xtpPaneThemeResource, xtpPaneStickerStyleVisualStudio2005, XTP_DPI_X(3));
				}
				break;
			case xtpThemeColor2010Black:
				{
					SetTheme(xtpThemeRibbon, xtpIniOffice2010Black);
					SetDockingPaneTheme(xtpPaneThemeResource, xtpPaneStickerStyleVisualStudio2005, XTP_DPI_X(3));
				}
				break;
			}
		}
		break;
    case xtpThemeDlgOffice2013:
		{
			switch (nColor)
			{
			case xtpThemeColor2013White:
				{
					switch (nAccent)
					{
					case xtpThemeAccentAccess:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2013Access);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentExcel:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2013Excel);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentOneNote:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2013OneNote);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentOutlook:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2013Outlook);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentPowerPoint:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2013PowerPoint);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentPublisher:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2013Publisher);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentWord:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2013Word);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					}
				}
				break;
			case xtpThemeColor2013GrayLight:
				{
					switch (nAccent)
					{
					case xtpThemeAccentAccess:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2013AccessGrayLight);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentExcel:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2013ExcelGrayLight);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentOneNote:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2013OneNoteGrayLight);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentOutlook:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2013OutlookGrayLight);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentPowerPoint:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2013PowerPointGrayLight);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentPublisher:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2013PublisherGrayLight);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentWord:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2013WordGrayLight);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					}
				}
				break;
			case xtpThemeColor2013GrayDark:
				{
					switch (nAccent)
					{
					case xtpThemeAccentAccess:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2013AccessGrayDark);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentExcel:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2013ExcelGrayDark);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentOneNote:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2013OneNoteGrayDark);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentOutlook:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2013OutlookGrayDark);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentPowerPoint:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2013PowerPointGrayDark);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentPublisher:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2013PublisherGrayDark);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentWord:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2013WordGrayDark);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					}
				}
				break;
			}
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
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2016AccessBlack);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentExcel:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2016ExcelBlack);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentOneNote:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2016OneNoteBlack);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentOutlook:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2016OutlookBlack);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentPowerPoint:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2016PowerPointBlack);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentPublisher:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2016PublisherBlack);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentWord:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2016WordBlack);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					}
				}
				break;
			case xtpThemeColor2016White:
				{
					switch (nAccent)
					{
					case xtpThemeAccentAccess:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2016AccessWhite);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentExcel:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2016ExcelWhite);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentOneNote:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2016OneNoteWhite);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentOutlook:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2016OutlookWhite);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentPowerPoint:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2016PowerPointWhite);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentPublisher:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2016PublisherWhite);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentWord:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2016WordWhite);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					}
				}
				break;
			case xtpThemeColor2016Colorful:
				{
					switch (nAccent)
					{
					case xtpThemeAccentAccess:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2016AccessColorful);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentExcel:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2016ExcelColorful);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentOneNote:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2016OneNoteColorful);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentOutlook:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2016OutlookColorful);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentPowerPoint:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2016PowerPointColorful);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentPublisher:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2016PublisherColorful);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentWord:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2016WordColorful);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					}
				}
				break;
			case xtpThemeColor2016GrayDark:
				{
					switch (nAccent)
					{
					case xtpThemeAccentAccess:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2016AccessDarkGray);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentExcel:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2016ExcelDarkGray);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentOneNote:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2016OneNoteDarkGray);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentOutlook:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2016OutlookDarkGray);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentPowerPoint:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2016PowerPointDarkGray);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentPublisher:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2016PublisherDarkGray);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					case xtpThemeAccentWord:
						{
							SetTheme(xtpThemeOffice2013, xtpIniOffice2016WordDarkGray);
							SetDockingPaneTheme(xtpPaneThemeOffice2013, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(1));
						}
						break;
					}
				}
				break;
			}
		}
		break;
	case xtpThemeDlgVisualStudio2005:
		{
			SetTheme(xtpThemeVisualStudio2005);
			AdjustStyle(xtpPaneThemeVisualStudio2003);
			SetDockingPaneTheme(xtpPaneThemeVisualStudio2005);
		}
		break;
	case xtpThemeDlgVisualStudio2012:
		{
			switch (nColor)
			{
			case xtpThemeColor2012Dark:
				{
					SetTheme(xtpThemeVisualStudio2012Dark, xtpIniVisualStudio2012Dark);
					SetDockingPaneTheme(xtpPaneThemeVisualStudio2012, xtpPaneStickerStyleVisualStudio2012Dark, XTP_DPI_X(5));
				}
				break;
			case xtpThemeColor2012Light:
				{
					SetTheme(xtpThemeVisualStudio2012Light, xtpIniVisualStudio2012Light);
					SetDockingPaneTheme(xtpPaneThemeVisualStudio2012, xtpPaneStickerStyleVisualStudio2012Light, XTP_DPI_X(5));
				}
				break;
			}
		}
		break;
    case xtpThemeDlgVisualStudio2015:
		{
			switch (nColor)
			{
			case xtpThemeColor2015Blue:
				{
					SetTheme(xtpThemeVisualStudio2015, xtpIniVisualStudio2015Blue);
					SetDockingPaneTheme(xtpPaneThemeVisualStudio2015, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(5));
				}
				break;
			case xtpThemeColor2015Dark:
				{
					SetTheme(xtpThemeVisualStudio2015, xtpIniVisualStudio2015Dark);
					SetDockingPaneTheme(xtpPaneThemeVisualStudio2015, xtpPaneStickerStyleVisualStudio2015Dark, XTP_DPI_X(5));
				}
				break;
			case xtpThemeColor2015Light:
				{
					SetTheme(xtpThemeVisualStudio2015, xtpIniVisualStudio2015Light);
					SetDockingPaneTheme(xtpPaneThemeVisualStudio2015, xtpPaneStickerStyleVisualStudio2015Light, XTP_DPI_X(5));
				}
				break;
			}
		}
		break;
	case xtpThemeDlgNativeWindows:
		{
			SetTheme(xtpThemeNativeWinXP);
			AdjustStyle(xtpPaneThemeGrippered);
			SetDockingPaneTheme(xtpPaneThemeWinNative);
		}
		break;
	case xtpThemeDlgCustom:   // Grippered
		{
			SetTheme(xtpThemeOffice2000);
			AdjustStyle(xtpPaneThemeGrippered);
			SetDockingPaneTheme(xtpPaneThemeGrippered);
			m_paneManager.GetPaintManager()->GetTabPaintManager()->m_clientFrame = xtpTabFrameBorder;
		}
		break;
	case xtpThemeDlgCustom+1: // Office 2000 Visio
		{
			SetTheme(xtpThemeOffice2000);
			AdjustStyle(xtpPaneThemeOffice2002Visio);
			SetDockingPaneTheme(xtpPaneThemeDefault);
			m_paneManager.GetPaintManager()->GetTabPaintManager()->SetAppearance(xtpTabAppearanceVisio);
		}
		break;
	case xtpThemeDlgCustom+2: // Office XP Visio
		{
			SetTheme(xtpThemeOfficeXP);
			AdjustStyle(xtpPaneThemeOffice2002Visio);
			SetDockingPaneTheme(xtpPaneThemeOffice2002Visio);
		}
		break;
	case xtpThemeDlgCustom+3: // Office 2003 Visio
		{
			SetTheme(xtpThemeOffice2003);
			AdjustStyle(xtpPaneThemeOffice2002Visio);
			SetDockingPaneTheme(xtpPaneThemeOffice2003);
			m_paneManager.GetPaintManager()->GetTabPaintManager()->SetAppearance(xtpTabAppearanceVisio);
			m_paneManager.GetPaintManager()->GetTabPaintManager()->SetColor(xtpTabColorOffice2003);
			m_paneManager.GetPaintManager()->GetTabPaintManager()->m_bHotTracking = TRUE;
			m_paneManager.GetPaintManager()->GetPanelPaintManager()->SetColor(xtpTabColorOffice2003);
		}
		break;
	case xtpThemeDlgCustom+4: // Office 2003 ShortcutBar
		{
			SetTheme(xtpThemeOffice2003);
			AdjustStyle(xtpPaneThemeVisualStudio2003);
			SetDockingPaneTheme(xtpPaneThemeOffice2003Outlook);
		}
		break;
	case xtpThemeDlgCustom+5: // Office 2007 Word
		{
			SetTheme(xtpThemeRibbon, xtpIniOffice2007Blue);
			AdjustStyle(xtpPaneThemeVisualStudio2003);
			SetDockingPaneTheme(xtpPaneThemeOffice2007Word);
		}
		break;
	case xtpThemeDlgCustom+6: // Explorer
		{
			SetTheme(xtpThemeNativeWinXP);
			AdjustStyle(xtpPaneThemeGrippered);
			SetDockingPaneTheme(xtpPaneThemeWinExplorer);
		}
		break;
	case xtpThemeDlgCustom+7: // Custom Caption
		{
			SetTheme(xtpThemeOfficeXP);
			AdjustStyle(xtpPaneThemeCustom);
			m_paneManager.SetCustomTheme(new CCustomTheme());
		}
		break;
	case xtpThemeDlgCustom+8: // Custom Tabs At Top
		{
			SetTheme(xtpThemeOffice2000);
			AdjustStyle(xtpPaneThemeGrippered);
			m_paneManager.SetCustomTheme(new CXTPDockingPaneDefaultTheme());
			CXTPTabPaintManager* pTabPaintManager = m_paneManager.GetPaintManager()->GetTabPaintManager();
			pTabPaintManager->SetPosition(xtpTabPositionTop);
			pTabPaintManager->m_clientFrame = xtpTabFrameBorder;
		}
		break;
	case xtpThemeDlgCustom+9: // Custom State Buttons
		{
			SetTheme(xtpThemeOfficeXP);
			AdjustStyle(xtpPaneThemeVisualStudio2003);
			m_paneManager.SetCustomTheme(new CXTPDockingPaneVisualStudio2003Theme());
			m_paneManager.GetPaintManager()->GetTabPaintManager()->SetAppearance(xtpTabAppearanceStateButtons);
			m_paneManager.GetPaintManager()->GetPanelPaintManager()->SetAppearance(xtpTabAppearanceStateButtons);
		}
		break;
	case xtpThemeDlgCustom+10: // Custom Excel
		{
			SetTheme(xtpThemeOfficeXP);
			AdjustStyle(xtpPaneThemeOffice2002Visio);
			m_paneManager.SetCustomTheme(new CXTPDockingPaneVisualStudio2003Theme());
			CXTPTabPaintManager* pTabPaintManager = m_paneManager.GetPaintManager()->GetTabPaintManager();
			pTabPaintManager->SetAppearance(xtpTabAppearanceExcel2003);
			pTabPaintManager->m_clientFrame = xtpTabFrameBorder;
			pTabPaintManager = m_paneManager.GetPaintManager()->GetPanelPaintManager();
			pTabPaintManager->SetAppearance(xtpTabAppearanceExcel2003);
		}
		break;
	}

	return 0;
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

LRESULT CMainFrame::OnDockingPaneNotify(WPARAM wParam, LPARAM lParam)
{
	if (wParam == XTP_DPN_SHOWWINDOW)
	{
		// get a pointer to the docking pane being shown.
		CXTPDockingPane* pPane = (CXTPDockingPane*)lParam;
		if (!pPane->IsValid())
		{
			int nIndex = pPane->GetID() - IDR_PANE1;
			ASSERT(nIndex >=0 &&  nIndex < sizeof(m_wndPanes) / sizeof(m_wndPanes[0]));
			CEditPane& wndEdit = m_wndPanes[nIndex];

			// create and attach the edit control for this pane.
			if (!::IsWindow(wndEdit.m_hWnd))
			{
				if (!wndEdit.CreateEx(WS_EX_STATICEDGE, _T("EDIT"), _T(""),
					WS_CHILD|ES_AUTOVSCROLL|ES_MULTILINE, 
					XTP_DPI(CRect(0, 0, 200, 120)), this, pPane->GetID()))
				{
					TRACE0( "Error creating pane edit control.\n" );
				}
				wndEdit.SetFont(&m_fntEdit);

				AdjustStyle(m_paneManager.GetCurrentTheme());
			}

			pPane->Attach(&wndEdit);
			wndEdit.SetOwnerPane(pPane);
		}

		return TRUE; // handled
	}

	if (wParam == XTP_DPN_CONTEXTMENU)
	{
		XTP_DOCKINGPANE_CLICK* pClick = (XTP_DOCKINGPANE_CLICK*)lParam;

		CMenu menu;
		VERIFY(menu.LoadMenu(IDR_POPUP_PANES));
		CMenu* pPopup = menu.GetSubMenu(0);
		TrackPopupMenu(pPopup->GetSafeHmenu(), TPM_RIGHTBUTTON, pClick->pt.x, pClick->pt.y, 0, AfxGetMainWnd()->GetSafeHwnd(), 0);

		return TRUE;
	}

	return FALSE;
}

void CMainFrame::AdjustStyle(XTPDockingPanePaintTheme nTheme)
{
	for (int i = 0; i < sizeof(m_wndPanes) / sizeof(m_wndPanes[0]); i++)
	{
		if (!m_wndPanes[i].m_hWnd)
		{
			if (!m_wndPanes[i].CreateEx(WS_EX_STATICEDGE, _T("EDIT"), _T(""),
				WS_CHILD|ES_AUTOVSCROLL|ES_MULTILINE, CRect(0, 0,0, 0), this, IDR_PANE1 + i))
			{
				TRACE0( "Error creating pane edit control.\n" );
			}
			m_wndPanes[i].SetFont(&m_fntEdit);
		}
	}
}
// CMainFrame message handlers

void CMainFrame::OnShowPane(UINT nID)
{
	m_paneManager.ShowPane(nID);
}


void CMainFrame::SwitchLayout()
{
	if (m_bMinMaxSample)
		OnMinMaxSample();

	if (m_bEditor)
	{
		m_paneManager.GetLayout(m_pEditorLayout);
		m_paneManager.SetLayout(m_pRunLayout);
	} else
	{
		m_paneManager.GetLayout(m_pRunLayout);
		m_paneManager.SetLayout(m_pEditorLayout);
	}
	m_bEditor = !m_bEditor;
}

void CMainFrame::OnLayoutEditor()
{
	if (!m_bEditor) SwitchLayout();

}

void CMainFrame::OnLayoutRun()
{
	if (m_bEditor) SwitchLayout();
}

void CMainFrame::OnUpdateLayoutEditor(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bEditor);
}

void CMainFrame::OnUpdateLayoutRun(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(!m_bEditor);
}

void CMainFrame::OnDestroy()
{
	if (m_bMinMaxSample)
	{
		OnMinMaxSample();
	}

	CMDIFrameWnd::OnDestroy();

	m_paneManager.GetLayout(m_bEditor? m_pEditorLayout: m_pRunLayout);

	m_pEditorLayout->Save(_T("EditorLayout"));
	m_pRunLayout->Save(_T("RunLayout"));


	delete m_pEditorLayout;
	delete m_pRunLayout;
}

#ifdef _XTP_INCLUDE_COMMANDBARS

void CMainFrame::SetCommandBarsTheme(XTPPaintTheme paintTheme, LPCTSTR lpszINI/*=NULL*/)
{
	if (lpszINI != NULL)
	{
		XTPThemeDLL()->SetHandle(lpszINI);
	}

	CXTPCommandBars* pCommandBars = GetCommandBars();
	if (pCommandBars != NULL)
	{
		CXTPPaintManager::SetTheme(paintTheme);

		CString strINI = lpszINI;
		pCommandBars->SetAllCaps((strINI.Find(_T("2013")) != -1) || (strINI.Find(_T("2015")) != -1));

		int nTheme = (int)paintTheme;

		switch(nTheme)
		{
			case xtpThemeRibbon:
			{
				CXTPCommandBarsFrameHook::m_bAllowDwm = TRUE;
				EnableFrameTheme(pCommandBars);

				for (int i=0; i<pCommandBars->GetCount(); i++)
				{
					CXTPToolBar *pToolBar = pCommandBars->GetAt(i);
					pToolBar->SetFlags(xtpFlagAlignTop | xtpFlagAlignBottom | xtpFlagAlignLeft | xtpFlagAlignRight | xtpFlagFloating, xtpFlagNoBorders);
					pToolBar->SetShowGripper(TRUE);
				}
			}
			break;
			case xtpThemeVisualStudio2012Light:
			case xtpThemeVisualStudio2012Dark:
			case xtpThemeVisualStudio2012:
			case xtpThemeVisualStudio2015:
			case xtpThemeOffice2013:
			{
				CXTPCommandBarsFrameHook::m_bAllowDwm = FALSE;
				EnableFrameTheme(pCommandBars);

				for (int i=0; i<pCommandBars->GetCount(); i++)
				{
					CXTPToolBar *pToolBar = pCommandBars->GetAt(i);
					pToolBar->SetFlags(xtpFlagAlignTop | xtpFlagNoBorders, xtpFlagAlignBottom | xtpFlagAlignLeft | xtpFlagAlignRight | xtpFlagFloating);

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
			{
				CXTPCommandBarsFrameHook::m_bAllowDwm = FALSE;
				EnableFrameTheme(NULL);

				for (int i=0; i<pCommandBars->GetCount(); i++)
				{
					CXTPToolBar *pToolBar = pCommandBars->GetAt(i);
					pToolBar->SetFlags(xtpFlagAlignTop | xtpFlagAlignBottom | xtpFlagAlignLeft | xtpFlagAlignRight | xtpFlagFloating, xtpFlagNoBorders);
					pToolBar->SetShowGripper(TRUE);
				}
			}
			break;
		};

		pCommandBars->GetPaintManager()->RefreshMetrics();
		pCommandBars->GetPaintManager()->m_bAutoResizeIcons = TRUE;
		pCommandBars->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE);
		pCommandBars->RedrawCommandBars();
	}
}

#endif /*_XTP_INCLUDE_COMMANDBARS*/

void CMainFrame::SetDockingPaneTheme(XTPDockingPanePaintTheme nTheme, XTPDockingContextStickerStyle nStyle /*=xtpPaneStickerStyleVisualStudio2005*/, int nMargin /*=0*/)
{
	m_paneManager.SetTheme(nTheme);
	m_paneManager.SetClientMargin(nMargin);
	m_paneManager.SetDockingContextStickerStyle(nStyle);

	theApp.m_csPane.RefreshMetrics(nTheme);

	if (m_fUseCustomPaneTitleBrushes)
	{
		m_paneManager.GetPaintManager()->SetCustomTitleBrushes(m_customPaneTitleBrushes.active, m_customPaneTitleBrushes.inactive);
		m_paneManager.RedrawPanes();
	}
}

void CMainFrame::OnHideClient()
{
	m_paneManager.HideClient(!m_paneManager.IsClientHidden());
}

void CMainFrame::OnUpdateHideClient(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.IsClientHidden()? TRUE: FALSE);
}

void CMainFrame::OnUseSplitterTracker()
{
	m_paneManager.UseSplitterTracker(!m_paneManager.IsSplitterTrackerUsed());
}

void CMainFrame::OnUpdateUseSplitterTracker(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.IsSplitterTrackerUsed()? TRUE: FALSE);
}

void CMainFrame::OnThemedFloatingFrames()
{
	m_paneManager.SetThemedFloatingFrames(!m_paneManager.IsThemedFloatingFrames());
}
void CMainFrame::OnUpdateThemedFloatingFrames(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.IsThemedFloatingFrames()? TRUE: FALSE);
}

void CMainFrame::OnAlphaContext()
{
	m_paneManager.SetAlphaDockingContext(!m_paneManager.IsAlphaDockingContext());

}
void CMainFrame::OnUpdateAlphaContext(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.IsAlphaDockingContext()? TRUE: FALSE);
}

void CMainFrame::OnDockingStickers()
{
	m_paneManager.SetShowDockingContextStickers(!m_paneManager.IsShowDockingContextStickers());
}
void CMainFrame::OnUpdateDockingStickers(CCmdUI *pCmdUI)
{
	if (m_paneManager.IsAlphaDockingContext())
	{
		pCmdUI->SetCheck(m_paneManager.IsShowDockingContextStickers()? TRUE: FALSE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CMainFrame::OnMinMaxSample()
{
	m_bMinMaxSample = !m_bMinMaxSample;

	if (m_bMinMaxSample)
	{
		CXTPDockingPane* pPane = m_paneManager.FindPane(IDR_PANE1);
		ASSERT(pPane);
		pPane->SetMinTrackSize(CSize(100, 100));
		pPane->SetMaxTrackSize(CSize(150, 150));

		pPane = m_paneManager.FindPane(IDR_PANE2);
		ASSERT(pPane);
		pPane->SetMinTrackSize(CSize(130, 130));
		pPane->SetMaxTrackSize(CSize(130, 130));
	}
	else
	{
		CXTPDockingPane* pPane = m_paneManager.FindPane(IDR_PANE1);
		ASSERT(pPane);
		pPane->SetMinTrackSize(CSize(0, 0));
		pPane->SetMaxTrackSize(CSize(32000, 32000));

		pPane = m_paneManager.FindPane(IDR_PANE2);
		ASSERT(pPane);
		pPane->SetMinTrackSize(CSize(0, 0));
		pPane->SetMaxTrackSize(CSize(32000, 32000));
	}

	for (int i = 0; i < sizeof(m_wndPanes) / sizeof(m_wndPanes[0]); i++)
	{
		if (m_wndPanes[i].m_hWnd)
		{
			m_wndPanes[i].OnSize(0, 0, 0);
			m_wndPanes[i].RedrawWindow();
		}
	}
	m_paneManager.RedrawPanes();
}

void CMainFrame::OnUpdateMinMaxSample(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bMinMaxSample);
}

void CMainFrame::OnLoadFromFile()
{
	CXTPDockingPaneLayout* pLayout = m_bEditor? m_pEditorLayout: m_pRunLayout;

	CString strFilter = _T("XML Document(*.xml)|*.xml|All files (*.*)|*.*||");
	CFileDialog fd(TRUE, _T("xml"), NULL, OFN_HIDEREADONLY|OFN_FILEMUSTEXIST, strFilter);
	if (fd.DoModal() == IDOK)
	{
#ifndef _XTP_EXCLUDE_XML
		if (pLayout->LoadFromFile(fd.GetPathName(), _T("Common")))
		{
			m_paneManager.SetLayout(pLayout);
		}
#else
		CFile file(fd.GetPathName(), CFile::modeRead);
		CArchive ar(&file, CArchive::load);

		pLayout->Serialize(ar);
		if (pLayout->IsValid())
		{
			m_paneManager.SetLayout(pLayout);
		}

#endif
	}
}

void CMainFrame::OnSaveToFile()
{
	CXTPDockingPaneLayout* pLayout = m_bEditor? m_pEditorLayout: m_pRunLayout;

	CString strFilter = _T("XML Document(*.xml)|*.xml|All files (*.*)|*.*||");
	CFileDialog fd(FALSE, _T("xml"), NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, strFilter);
	if (fd.DoModal() == IDOK)
	{
#ifndef _XTP_EXCLUDE_XML

		m_paneManager.GetLayout(pLayout);
		pLayout->SaveToFile(fd.GetPathName(), _T("Common"));
#else
		m_paneManager.GetLayout(pLayout);
		CFile file(fd.GetPathName(), CFile::modeCreate|CFile::modeWrite);
		CArchive ar(&file, CArchive::store);

		pLayout->Serialize(ar);

#endif
	}

}

void CMainFrame::OnLoadFromResource()
{

#ifndef _XTP_EXCLUDE_XML

	LPCTSTR lpszResourceName = MAKEINTRESOURCE(IDR_SPIRAL);

	CXTPPropExchangeXMLNode px(TRUE, NULL, _T("DockingPaneLayouts"));

	if (px.LoadFromResource(AfxGetInstanceHandle(), lpszResourceName, RT_HTML))
	{
		CXTPDockingPaneLayout* pLayout = m_bEditor? m_pEditorLayout: m_pRunLayout;
		CXTPPropExchangeSection pxCommon(px.GetSection(_T("Common")));

		if (pLayout->DoPropExchange(&pxCommon))
		{
			m_paneManager.SetLayout(pLayout);
		}

	}

#endif

}

#ifdef _XTP_INCLUDE_COMMANDBARS

void CMainFrame::OnCustomize()
{
	// Get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if(pCommandBars != NULL)
	{
		// Instanciate the customize dialog object.
		CXTPCustomizeSheet dlg(pCommandBars);

		// Add the options page to the customize dialog.
		CXTPCustomizeOptionsPage pageOptions(&dlg);
		dlg.AddPage(&pageOptions);

		// Add the commands page to the customize dialog.
		CXTPCustomizeCommandsPage* pCommands = dlg.GetCommandsPage();
		pCommands->AddCategories(IDR_PANETYPE);

		// Use the command bar manager to initialize the
		// customize dialog.
		pCommands->InsertAllCommandsCategory();
		pCommands->InsertBuiltInMenus(IDR_PANETYPE);
		pCommands->InsertNewMenuCategory();

		// Dispaly the dialog.
		dlg.DoModal();
	}
}

void CMainFrame::OnClose()
{
	// Save the current state for toolbars and menus.
	SaveCommandBars(_T("CommandBars"));
	CMDIFrameWnd::OnClose();
}

#endif


void CMainFrame::OnGetMinMaxInfo(LPMINMAXINFO pMinMaxInfo)
{
	CMDIFrameWnd::OnGetMinMaxInfo(pMinMaxInfo);

	if (m_bMinMaxSample)
	{
		CXTPWindowRect rcWindow(this);

		CRect rcTopPane= m_paneManager.GetTopPane()->GetPaneWindowRect();

		CSize szBorder = rcWindow.Size() - rcTopPane.Size();

		MINMAXINFO mmi;
		m_paneManager.GetTopPane()->GetMinMaxInfo(&mmi);

		pMinMaxInfo->ptMinTrackSize = CPoint(mmi.ptMinTrackSize) + szBorder;
	}
}

void CMainFrame::OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState)
{

#ifdef _XTP_INCLUDE_COMMANDBARS
	// Toggle CommandBars
	GetCommandBars()->OnSetPreviewMode(bPreview);
#endif


// Toggle Docking Panes.
	m_paneManager.OnSetPreviewMode(bPreview);


	CMDIFrameWnd::OnSetPreviewMode(bPreview, pState);
}


void CMainFrame::SwitchDefaultPaneOptions(XTPDockingPaneOptions dwOption)
{
	DWORD dwOptions = m_paneManager.GetDefaultPaneOptions();

	m_paneManager.SetDefaultPaneOptions(dwOptions & dwOption? dwOptions & ~dwOption: dwOptions | dwOption);
	m_paneManager.RecalcFramesLayout();
}

void CMainFrame::OnCaptionButtonClose()
{
	SwitchDefaultPaneOptions(xtpPaneNoCloseable);
}

void CMainFrame::OnUpdateCaptionButtonClose(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.GetDefaultPaneOptions() & xtpPaneNoCloseable? FALSE: TRUE);
}

void CMainFrame::OnCaptionButtonAutoHide()
{
	SwitchDefaultPaneOptions(xtpPaneNoHideable);
}

void CMainFrame::OnUpdateCaptionButtonAutoHide(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.GetDefaultPaneOptions() & xtpPaneNoHideable? FALSE: TRUE);
}

void CMainFrame::OnCaptionButtonMenu()
{
	SwitchDefaultPaneOptions(xtpPaneHasMenuButton);
}

void CMainFrame::OnUpdateCaptionButtonMenu(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.GetDefaultPaneOptions() & xtpPaneHasMenuButton? TRUE: FALSE);
}

void CMainFrame::OnCaptionButtonMaximize()
{
	m_paneManager.ShowCaptionMaximizeButton(!m_paneManager.IsCaptionMaximizeButtonsVisible());
	m_paneManager.RedrawPanes();
}

void CMainFrame::OnCaptionButtonMaximizeFloating()
{
	m_paneManager.ShowFloatingCaptionMaximizeButton(!m_paneManager.IsFloatingCaptionMaximizeButtonsVisible());
	m_paneManager.RedrawPanes();
}

void CMainFrame::OnUpdateCaptionButtonMaximize(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.IsCaptionMaximizeButtonsVisible()? TRUE: FALSE);
}

void CMainFrame::OnUpdateCaptionButtonMaximizeFloating(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.IsFloatingCaptionMaximizeButtonsVisible() ? TRUE : FALSE);
}

void CMainFrame::OnCaptionVisible()
{
	m_paneManager.GetPaintManager()->m_bShowCaption = !m_paneManager.GetPaintManager()->m_bShowCaption;
	m_paneManager.RedrawPanes();
}

void CMainFrame::OnCaptionUseCustomTitles()
{
	m_fUseCustomPaneTitleBrushes = !m_fUseCustomPaneTitleBrushes;
	if(m_fUseCustomPaneTitleBrushes)
	{
		m_paneManager.GetPaintManager()->SetCustomTitleBrushes(
			m_customPaneTitleBrushes.active,
			m_customPaneTitleBrushes.inactive);
	}
	else
	{
		m_paneManager.GetPaintManager()->SetCustomTitleBrushes(NULL);
	}

	m_paneManager.RedrawPanes();
}

void CMainFrame::OnCaptionHorizontal()
{
	m_paneManager.SetCaptionDirection(xtpPaneCaptionHorizontal);
}

void CMainFrame::OnCaptionVertical()
{
	m_paneManager.SetCaptionDirection(xtpPaneCaptionVertical);
}

void CMainFrame::OnCaptionAutoBySize()
{
	m_paneManager.SetCaptionDirection(xtpPaneCaptionAutoBySize);
}

void CMainFrame::OnCaptionAutoByPosition()
{
	m_paneManager.SetCaptionDirection(xtpPaneCaptionAutoByPosition);
}

void CMainFrame::OnUpdateCaptionVisible(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.GetPaintManager()->m_bShowCaption? TRUE: FALSE);
}

void CMainFrame::OnUpdateCaptionUseCustomTitles(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_fUseCustomPaneTitleBrushes);
}

void CMainFrame::OnUpdateCaptionHorizontal(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.GetCaptionDirection() == xtpPaneCaptionHorizontal? TRUE: FALSE);
}

void CMainFrame::OnUpdateCaptionVertical(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.GetCaptionDirection() == xtpPaneCaptionVertical? TRUE: FALSE);
}

void CMainFrame::OnUpdateCaptionAutoBySize(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.GetCaptionDirection() == xtpPaneCaptionAutoBySize? TRUE: FALSE);
}

void CMainFrame::OnUpdateCaptionAutoByPosition(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.GetCaptionDirection() == xtpPaneCaptionAutoByPosition? TRUE: FALSE);
}

void CMainFrame::OnCloseButtonAffects()
{
	m_paneManager.m_bCloseGroupOnButtonClick = !m_paneManager.m_bCloseGroupOnButtonClick;
}

void CMainFrame::OnAutoHideButtonAffects()
{
	m_paneManager.m_bHideGroupOnButtonClick = !m_paneManager.m_bHideGroupOnButtonClick;
}

void CMainFrame::OnUpdateCloseButtonAffects(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.m_bCloseGroupOnButtonClick? FALSE: TRUE);
}

void CMainFrame::OnUpdateAutoHideButtonAffects(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.m_bHideGroupOnButtonClick? FALSE: TRUE);
}


void CMainFrame::OnUpdateShowContentsWhileDragging(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.GetShowContentsWhileDragging()? TRUE: FALSE);
}

void CMainFrame::OnShowContentsWhileDragging()
{
	m_paneManager.SetShowContentsWhileDragging(!m_paneManager.GetShowContentsWhileDragging());
}

void CMainFrame::OnStickyFloatingFrames()
{
	m_paneManager.SetStickyFloatingFrames(!m_paneManager.IsStickyFloatingFrames());
}

void CMainFrame::OnUpdateStickyFloatingFrames(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.IsStickyFloatingFrames() ? TRUE: FALSE);
}

void CMainFrame::OnTransparentFloatingFrames()
{
	m_paneManager.SetFloatingFramesOpacity(m_paneManager.GetFloatingFramesOpacity() != 255 ? 255 : 200);
}

void CMainFrame::OnUpdateTransparentFloatingFrames(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.GetFloatingFramesOpacity() != 255);
}

void CMainFrame::OnEnableSideDocking()
{
	m_paneManager.EnableSideDocking(!m_paneManager.IsSideDockingEnabled());
}

void CMainFrame::OnUpdateEnableSideDocking(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.IsSideDockingEnabled());
}
