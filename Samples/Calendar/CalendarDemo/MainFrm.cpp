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
#include "CalendarDemo.h"

#include "MainFrm.h"
#include "CalendarDemoView.h"

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
#ifdef _XTP_INCLUDE_COMMANDBARS
	ON_COMMAND(ID_OPTIONS_STYLE_VISUALSTUDIO2015_CLOSED, OnOptionsStyleVisualStudio2015Closed)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_STYLE_VISUALSTUDIO2015_CLOSED, OnUpdateOptionsStyleVisualStudio2015Closed)
	ON_COMMAND(ID_OPTIONS_STYLE_VISUALSTUDIO2015_OPEN, OnOptionsStyleVisualStudio2015Open)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_STYLE_VISUALSTUDIO2015_OPEN, OnUpdateOptionsStyleVisualStudio2015Open)
	ON_COMMAND(ID_OPTIONS_STYLE_VISUALSTUDIO2015_DEBUG, OnOptionsStyleVisualStudio2015Debug)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_STYLE_VISUALSTUDIO2015_DEBUG, OnUpdateOptionsStyleVisualStudio2015Debug)
#endif
	//}}AFX_MSG_MAP
	ON_COMMAND_EX(ID_VIEW_DATEPICKER, OnBarCheck)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DATEPICKER, OnUpdateControlBarMenu)

	ON_COMMAND_EX(ID_VIEW_PROPERTIES, OnBarCheck)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PROPERTIES, OnUpdateControlBarMenu)

#ifdef _XTP_INCLUDE_COMMANDBARS	
	// Styles
	ON_COMMAND(ID_CALENDAR_THEMES, OnEmptyCommand)
	ON_COMMAND(ID_CALENDAR_MANAGE_OPEN, OnEmptyCommand)
	ON_COMMAND(ID_CALENDAR_TIME, OnEmptyCommand)
	ON_COMMAND(ID_CALENDAR_MEETING_CATEGORIZE, OnEmptyCommand)
#endif
	ON_COMMAND(ID_VIEW_OFFICE_THEME, OnViewOfficeTheme)
	ON_WM_XTP_THEMECHANGED()

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
	m_eStudio2015State = eStateClosed;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

#ifdef _XTP_INCLUDE_COMMANDBARS

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
	m_wndStatusBar.SetCommandBars(pCommandBars);

	CXTPToolTipContext* pToolTipContext = GetCommandBars()->GetToolTipContext();
	pToolTipContext->SetStyle(xtpToolTipResource);
	pToolTipContext->ShowTitleAndDescription();
	pToolTipContext->ShowImage(TRUE, 0);
	pToolTipContext->EnableImageDPIScaling(FALSE);
	pToolTipContext->SetMargin(CRect(XTP_DPI_X(2), XTP_DPI_Y(2), XTP_DPI_X(2), XTP_DPI_Y(2)));
	pToolTipContext->SetMaxTipWidth(XTP_DPI_X(180));
	pToolTipContext->SetFont(pCommandBars->GetPaintManager()->GetIconFont());
	pToolTipContext->SetDelayTime(TTDT_INITIAL, 900);
	Load2013Icons();

	if (!CreateRibbonBar())
	{
		TRACE0("Failed to create ribbon\n");
		return -1;
	}

	GetCommandBars()->GetImageManager()->RefreshAll();

	// Load the previous state for command bars.
	//LoadCommandBars(_T("CommandBars"));

	EnableDocking(CBRS_ALIGN_ANY);
#else

#if _MSC_VER >= 1200	// MFC 6.0
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
#else
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

#endif
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	EnableDocking(CBRS_ALIGN_ANY);

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

#endif
	// Initialize dialog bar
	if (!m_dlgDatePicker.Create(this, IDD_DATEPICKER,
		CBRS_LEFT|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_HIDE_INPLACE, ID_VIEW_DATEPICKER))
		return -1;		// fail to create

	// Initialize dialog bar
	if (!m_dlgOptions.Create(this, IDD_CALENDAR_DEMO_VIEW,
		CBRS_ALIGN_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_HIDE_INPLACE, ID_VIEW_PROPERTIES))
		return -1;		// fail to create

	m_dlgOptions.EnableDocking(0);
	m_dlgOptions.SetWindowText(_T("Options"));
	
	ShowControlBar(&m_dlgOptions, FALSE, FALSE);
	
	FloatControlBar(&m_dlgOptions, CPoint(100, 200));
	
	// docking for DatePicker
	m_dlgDatePicker.EnableDocking(CBRS_ALIGN_LEFT);
	m_dlgDatePicker.SetWindowText(_T("Date Picker"));

	ShowControlBar(&m_dlgDatePicker, TRUE, FALSE);

	m_dlgDatePicker.MoveWindow(0,0,0,0);

	// exclude unused themes.
	m_dlgTheme.ExcludeTheme(
		XTP_EXCLUDE_THEME_VISUALSTUDIO6    | 
		XTP_EXCLUDE_THEME_VISUALSTUDIO2005 | 
		XTP_EXCLUDE_THEME_VISUALSTUDIO2008 | 
		XTP_EXCLUDE_THEME_VISUALSTUDIO2010 | 
		XTP_EXCLUDE_THEME_VISUALSTUDIO2012 | 
		XTP_EXCLUDE_THEME_NATIVEWINDOWS    | 
		XTP_EXCLUDE_THEME_CUSTOM);

	// set startup theme
	m_dlgTheme.SetTheme(
		xtpThemeDlgOffice2016,
		xtpThemeColor2016Colorful,
#ifdef _XTP_INCLUDE_RIBBON
		xtpThemeAccentOutlook,
		xtpThemeRibbonBackSchoolSupplies);
#else
		xtpThemeAccentOutlook);
#endif

	// create theme dialog.
	VERIFY(m_dlgTheme.Create(IDD_THEME_DIALOG, this));

	// enable auto preview.
	m_dlgTheme.EnableAutoPreview(TRUE);

	SetTheme(xtpThemeDlgOffice2016, xtpIniOffice2016OutlookColorful);
#ifdef _XTP_INCLUDE_RIBBON
	SetRibbonBackImage(xtpThemeRibbonBackSchoolSupplies);
#endif

	return 0;
}
#ifdef _XTP_INCLUDE_COMMANDBARS

XTPPaintTheme GetPaintTheme(int nTheme)
{
	switch (nTheme)
	{
    case xtpThemeDlgOffice2000:       return xtpThemeRibbon;
    case xtpThemeDlgOfficeXP:         return xtpThemeRibbon;
    case xtpThemeDlgOffice2003:       return xtpThemeRibbon;
    case xtpThemeDlgOffice2007:       return xtpThemeRibbon;
    case xtpThemeDlgOffice2010:       return xtpThemeRibbon;
    case xtpThemeDlgOffice2013:       return xtpThemeOffice2013;
    case xtpThemeDlgOffice2016:       return xtpThemeOffice2013;
    case xtpThemeDlgVisualStudio2015: return xtpThemeVisualStudio2015;
    case xtpThemeDlgNativeWindows:    return xtpThemeRibbon;
	}
	return xtpThemeNone;
}
#endif

XTPCalendarTheme GetCalendarTheme(int nTheme)
{
	switch (nTheme)
	{
    case xtpThemeDlgOffice2000:       return xtpCalendarThemeOffice2000;
    case xtpThemeDlgOfficeXP:         return xtpCalendarThemeOfficeXP;
    case xtpThemeDlgOffice2003:       return xtpCalendarThemeOffice2003;
    case xtpThemeDlgOffice2007:       return xtpCalendarThemeResource;
    case xtpThemeDlgOffice2010:       return xtpCalendarThemeResource;
    case xtpThemeDlgOffice2013:       return xtpCalendarThemeOffice2013;
    case xtpThemeDlgOffice2016:       return xtpCalendarThemeOffice2013;
    case xtpThemeDlgVisualStudio2015: return xtpCalendarThemeVisualStudio2015;
    case xtpThemeDlgNativeWindows:    return xtpCalendarThemeResource;
	}
	return xtpCalendarThemeUnknown;
}

void CMainFrame::SetTheme(int nTheme, LPCTSTR lpszINI /*=NULL*/)
{
	// load resource DLL.
	if (lpszINI != NULL)
	{
		XTPThemeDLL()->SetHandle(lpszINI);
	}
#ifdef _XTP_INCLUDE_COMMANDBARS

	CXTPCommandBars* pCommandBars = GetCommandBars();
	ASSERT(pCommandBars != NULL);

	if (!pCommandBars)
		return;

	CXTPPaintManager::SetTheme(GetPaintTheme(nTheme));
		
	m_bAllowDwm = !(CXTPWinDwmWrapper().IsCompositionEnabled() && (nTheme >= xtpThemeDlgOffice2013));

	pCommandBars->SetAllCaps(nTheme == xtpThemeDlgOffice2013 || nTheme == xtpThemeDlgVisualStudio2015);
	pCommandBars->GetPaintManager()->m_bAutoResizeIcons = TRUE;
	pCommandBars->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE, FALSE);

	if (nTheme >= xtpThemeDlgOffice2013)
	{
		pCommandBars->GetToolTipContext()->SetStyle(xtpToolTipOffice2013);
	}
	else
	{
		pCommandBars->GetToolTipContext()->SetStyle(xtpToolTipResource);
	}

	pCommandBars->GetPaintManager()->RefreshMetrics();
	pCommandBars->GetImageManager()->RefreshAll();
#ifdef _XTP_INCLUDE_RIBBON

	CXTPRibbonBar* pRibbonBar = DYNAMIC_DOWNCAST(CXTPRibbonBar, pCommandBars->GetMenuBar());
	ASSERT(pRibbonBar != NULL);
		
	if (pRibbonBar)
	{
		pRibbonBar->EnableFrameTheme();
		
		if (nTheme != xtpThemeDlgOffice2007)
		{
			pRibbonBar->GetSystemButton()->SetStyle(xtpButtonCaption);
			CreateBackstage();
		}
		else
		{
			pRibbonBar->GetSystemButton()->SetStyle(xtpButtonAutomatic);
			CreateSystemMenuPopup();
		}
	}

#endif
	pCommandBars->RedrawCommandBars();
		
	SendMessage(WM_NCPAINT);
	RedrawWindow(0, 0, RDW_ALLCHILDREN|RDW_INVALIDATE);

#endif
	// set calendar theme.
	CCalendarDemoView* pCalendarView = DYNAMIC_DOWNCAST(CCalendarDemoView, GetActiveView());
	XTP_SAFE_CALL1(pCalendarView, SetTheme(GetCalendarTheme(nTheme)));
}
#ifdef _XTP_INCLUDE_RIBBON

BOOL CMainFrame::SetRibbonBackImage(int nBack)
{
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if (!pCommandBars)
		return FALSE;

	CXTPCommandBarsOffice2013Theme* pPaintManager = DYNAMIC_DOWNCAST(
		CXTPCommandBarsOffice2013Theme, pCommandBars->GetPaintManager());
	if (!pPaintManager)
		return FALSE;

	return pPaintManager->SetOfficeBackImage(pCommandBars, XTPBackImage(nBack));
}
#endif

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
    case xtpThemeDlgOffice2000: SetTheme(nTheme, xtpIniOffice2010Silver); break;
    case xtpThemeDlgOfficeXP:   SetTheme(nTheme, xtpIniOffice2010Silver); break;
    case xtpThemeDlgOffice2003: SetTheme(nTheme, xtpIniOffice2010Blue);   break;
    case xtpThemeDlgOffice2007:
		{
			switch (nColor)
			{
			case xtpThemeColor2007Blue:   SetTheme(nTheme, xtpIniOffice2007Blue);   break;
			case xtpThemeColor2007Silver: SetTheme(nTheme, xtpIniOffice2007Silver); break;
			case xtpThemeColor2007Black:  SetTheme(nTheme, xtpIniOffice2007Black);  break;
			case xtpThemeColor2007Aqua:   SetTheme(nTheme, xtpIniOffice2007Aqua);   break;
			}
		}
		break;
    case xtpThemeDlgOffice2010:
		{
			switch (nColor)
			{
			case xtpThemeColor2010Blue:   SetTheme(nTheme, xtpIniOffice2010Blue);   break;
			case xtpThemeColor2010Silver: SetTheme(nTheme, xtpIniOffice2010Silver); break;
			case xtpThemeColor2010Black:  SetTheme(nTheme, xtpIniOffice2010Black);  break;
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
					case xtpThemeAccentAccess:     SetTheme(nTheme, xtpIniOffice2013Access);     break;
					case xtpThemeAccentExcel:      SetTheme(nTheme, xtpIniOffice2013Excel);      break;
					case xtpThemeAccentOneNote:    SetTheme(nTheme, xtpIniOffice2013OneNote);    break;
					case xtpThemeAccentOutlook:    SetTheme(nTheme, xtpIniOffice2013Outlook);    break;
					case xtpThemeAccentPowerPoint: SetTheme(nTheme, xtpIniOffice2013PowerPoint); break;
					case xtpThemeAccentPublisher:  SetTheme(nTheme, xtpIniOffice2013Publisher);  break;
					case xtpThemeAccentWord:       SetTheme(nTheme, xtpIniOffice2013Word);       break;
					}
				}
				break;
			case xtpThemeColor2013GrayLight:
				{
					switch (nAccent)
					{
					case xtpThemeAccentAccess:     SetTheme(nTheme, xtpIniOffice2013AccessGrayLight);     break;
					case xtpThemeAccentExcel:      SetTheme(nTheme, xtpIniOffice2013ExcelGrayLight);      break;
					case xtpThemeAccentOneNote:    SetTheme(nTheme, xtpIniOffice2013OneNoteGrayLight);    break;
					case xtpThemeAccentOutlook:    SetTheme(nTheme, xtpIniOffice2013OutlookGrayLight);    break;
					case xtpThemeAccentPowerPoint: SetTheme(nTheme, xtpIniOffice2013PowerPointGrayLight); break;
					case xtpThemeAccentPublisher:  SetTheme(nTheme, xtpIniOffice2013PublisherGrayLight);  break;
					case xtpThemeAccentWord:       SetTheme(nTheme, xtpIniOffice2013WordGrayLight);       break;
					}
				}
				break;
			case xtpThemeColor2013GrayDark:
				{
					switch (nAccent)
					{
					case xtpThemeAccentAccess:     SetTheme(nTheme, xtpIniOffice2013AccessGrayDark);     break;
					case xtpThemeAccentExcel:      SetTheme(nTheme, xtpIniOffice2013ExcelGrayDark);      break;
					case xtpThemeAccentOneNote:    SetTheme(nTheme, xtpIniOffice2013OneNoteGrayDark);    break;
					case xtpThemeAccentOutlook:    SetTheme(nTheme, xtpIniOffice2013OutlookGrayDark);    break;
					case xtpThemeAccentPowerPoint: SetTheme(nTheme, xtpIniOffice2013PowerPointGrayDark); break;
					case xtpThemeAccentPublisher:  SetTheme(nTheme, xtpIniOffice2013PublisherGrayDark);  break;
					case xtpThemeAccentWord:       SetTheme(nTheme, xtpIniOffice2013WordGrayDark);       break;
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
					case xtpThemeAccentAccess:     SetTheme(nTheme, xtpIniOffice2016AccessBlack);     break;
					case xtpThemeAccentExcel:      SetTheme(nTheme, xtpIniOffice2016ExcelBlack);      break;
					case xtpThemeAccentOneNote:    SetTheme(nTheme, xtpIniOffice2016OneNoteBlack);    break;
					case xtpThemeAccentOutlook:    SetTheme(nTheme, xtpIniOffice2016OutlookBlack);    break;
					case xtpThemeAccentPowerPoint: SetTheme(nTheme, xtpIniOffice2016PowerPointBlack); break;
					case xtpThemeAccentPublisher:  SetTheme(nTheme, xtpIniOffice2016PublisherBlack);  break;
					case xtpThemeAccentWord:       SetTheme(nTheme, xtpIniOffice2016WordBlack);       break;
					}
				}
				break;
			case xtpThemeColor2016White:
				{
					switch (nAccent)
					{
					case xtpThemeAccentAccess:     SetTheme(nTheme, xtpIniOffice2016AccessWhite);     break;
					case xtpThemeAccentExcel:      SetTheme(nTheme, xtpIniOffice2016ExcelWhite);      break;
					case xtpThemeAccentOneNote:    SetTheme(nTheme, xtpIniOffice2016OneNoteWhite);    break;
					case xtpThemeAccentOutlook:    SetTheme(nTheme, xtpIniOffice2016OutlookWhite);    break;
					case xtpThemeAccentPowerPoint: SetTheme(nTheme, xtpIniOffice2016PowerPointWhite); break;
					case xtpThemeAccentPublisher:  SetTheme(nTheme, xtpIniOffice2016PublisherWhite);  break;
					case xtpThemeAccentWord:       SetTheme(nTheme, xtpIniOffice2016WordWhite);       break;
					}
				}
				break;
			case xtpThemeColor2016Colorful:
				{
					switch (nAccent)
					{
					case xtpThemeAccentAccess:     SetTheme(nTheme, xtpIniOffice2016AccessColorful);     break;
					case xtpThemeAccentExcel:      SetTheme(nTheme, xtpIniOffice2016ExcelColorful);      break;
					case xtpThemeAccentOneNote:    SetTheme(nTheme, xtpIniOffice2016OneNoteColorful);    break;
					case xtpThemeAccentOutlook:    SetTheme(nTheme, xtpIniOffice2016OutlookColorful);    break;
					case xtpThemeAccentPowerPoint: SetTheme(nTheme, xtpIniOffice2016PowerPointColorful); break;
					case xtpThemeAccentPublisher:  SetTheme(nTheme, xtpIniOffice2016PublisherColorful);  break;
					case xtpThemeAccentWord:       SetTheme(nTheme, xtpIniOffice2016WordColorful);       break;
					}
				}
				break;
			case xtpThemeColor2016GrayDark:
				{
					switch (nAccent)
					{
					case xtpThemeAccentAccess:     SetTheme(nTheme, xtpIniOffice2016AccessDarkGray);     break;
					case xtpThemeAccentExcel:      SetTheme(nTheme, xtpIniOffice2016ExcelDarkGray);      break;
					case xtpThemeAccentOneNote:    SetTheme(nTheme, xtpIniOffice2016OneNoteDarkGray);    break;
					case xtpThemeAccentOutlook:    SetTheme(nTheme, xtpIniOffice2016OutlookDarkGray);    break;
					case xtpThemeAccentPowerPoint: SetTheme(nTheme, xtpIniOffice2016PowerPointDarkGray); break;
					case xtpThemeAccentPublisher:  SetTheme(nTheme, xtpIniOffice2016PublisherDarkGray);  break;
					case xtpThemeAccentWord:       SetTheme(nTheme, xtpIniOffice2016WordDarkGray);       break;
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
			case xtpThemeColor2015Blue:  SetTheme(nTheme, xtpIniVisualStudio2015Blue);  break;
			case xtpThemeColor2015Dark:  SetTheme(nTheme, xtpIniVisualStudio2015Dark);  break;
			case xtpThemeColor2015Light: SetTheme(nTheme, xtpIniVisualStudio2015Light); break;
			}
		}
		break;
	}

	return 0;
}
#ifdef _XTP_INCLUDE_COMMANDBARS

void CMainFrame::Load2013Icons()
{
	CXTPCommandBars* pCommandBars = GetCommandBars();

	pCommandBars->GetImageManager()->RemoveAll();

	UINT uHomeIDs[] = {
		ID_VIEW_PROPERTIES,IDC_ADVANCED_OPT_BTN,ID_CALENDAR_ADD_NEW_EVENT,ID_CALENDAR_NEW_MEETING,ID_CALENDAR_NEW_ITEMS,ID_CALENDAR_GOTO_TODAY
		,ID_CALENDAR_GOTO_NEXT7DAYS,ID_CALENDAR_VIEW_DAY,ID_CALENDAR_VIEW_WORKWEEK,ID_CALENDAR_VIEW_WEEK,ID_CALENDAR_VIEW_MONTH,ID_CALENDAR_VIEW_SCHEDULE
		,ID_CALENDAR_MANAGE_OPEN,ID_CALENDAR_MANAGE_GROUPS,ID_CALENDAR_SHARE_EMAIL,ID_CALENDAR_SHARE_SHARE,ID_CALENDAR_SHARE_PUBLISH
		,ID_CALENDAR_SHARE_PERMISSIONS,ID_CALENDAR_THEMES,ID_APP_ABOUT,ID_CALENDAR_TIME,ID_CALENDAR_SCHEDULES,ID_VIEW_REMINDERS,ID_VIEW_DATEPICKER};

	pCommandBars->GetImageManager()->SetIcons(IDR_OUTLOOK_2013_HOME_16, uHomeIDs, _countof(uHomeIDs), CSize(16, 16));
	pCommandBars->GetImageManager()->SetIcons(IDR_OUTLOOK_2013_HOME_24, uHomeIDs, _countof(uHomeIDs), CSize(24, 24));
	pCommandBars->GetImageManager()->SetIcons(IDR_OUTLOOK_2013_HOME_32, uHomeIDs, _countof(uHomeIDs), CSize(32, 32));
	pCommandBars->GetImageManager()->SetIcons(IDR_OUTLOOK_2013_HOME_40, uHomeIDs, _countof(uHomeIDs), CSize(40, 40));
	pCommandBars->GetImageManager()->SetIcons(IDR_OUTLOOK_2013_HOME_48, uHomeIDs, _countof(uHomeIDs), CSize(48, 48));
	pCommandBars->GetImageManager()->SetIcons(IDR_OUTLOOK_2013_HOME_64, uHomeIDs, _countof(uHomeIDs), CSize(64, 64));

	//reuse icons for groups
	UINT uHomeGroupIDs[] = {ID_GROUP_PROPERTIES, 0, 0, 0, ID_GROUP_NEW, ID_GROUP_GOTO, 0, 0, 0, ID_GROUP_ARRANGE,
							0, 0, 0, ID_GROUP_MANAGECALENDARS, 0, ID_GROUP_SHARE, 0, 0, ID_GROUP_THEMES, 0,
							0, 0, 0, 0};

	pCommandBars->GetImageManager()->SetIcons(IDR_OUTLOOK_2013_HOME_16, uHomeGroupIDs, _countof(uHomeGroupIDs), CSize(16, 16));
	pCommandBars->GetImageManager()->SetIcons(IDR_OUTLOOK_2013_HOME_24, uHomeGroupIDs, _countof(uHomeGroupIDs), CSize(24, 24));
	pCommandBars->GetImageManager()->SetIcons(IDR_OUTLOOK_2013_HOME_32, uHomeGroupIDs, _countof(uHomeGroupIDs), CSize(32, 32));
	pCommandBars->GetImageManager()->SetIcons(IDR_OUTLOOK_2013_HOME_40, uHomeGroupIDs, _countof(uHomeGroupIDs), CSize(40, 40));
	pCommandBars->GetImageManager()->SetIcons(IDR_OUTLOOK_2013_HOME_48, uHomeGroupIDs, _countof(uHomeGroupIDs), CSize(48, 48));
	pCommandBars->GetImageManager()->SetIcons(IDR_OUTLOOK_2013_HOME_64, uHomeGroupIDs, _countof(uHomeGroupIDs), CSize(64, 64));
	
	UINT uMeetingIDs[] = {
		ID_CALENDAR_MEETING_OPEN,
		ID_CALENDAR_MEETING_DELETE,
		ID_CALENDAR_MEETING_CATEGORIZE,
		ID_CALENDAR_MEETING_PRIVATE,
		ID_CALENDAR_MEETING_MEETING,
		ID_CALENDAR_MEETING_REMINDER };

	pCommandBars->GetImageManager()->SetIcons(IDR_OUTLOOK_2013_MEETING_16, uMeetingIDs, _countof(uMeetingIDs), CSize(16, 16));
	pCommandBars->GetImageManager()->SetIcons(IDR_OUTLOOK_2013_MEETING_24, uMeetingIDs, _countof(uMeetingIDs), CSize(24, 24));
	pCommandBars->GetImageManager()->SetIcons(IDR_OUTLOOK_2013_MEETING_32, uMeetingIDs, _countof(uMeetingIDs), CSize(32, 32));
	pCommandBars->GetImageManager()->SetIcons(IDR_OUTLOOK_2013_MEETING_40, uMeetingIDs, _countof(uMeetingIDs), CSize(40, 40));
	pCommandBars->GetImageManager()->SetIcons(IDR_OUTLOOK_2013_MEETING_48, uMeetingIDs, _countof(uMeetingIDs), CSize(48, 48));
	pCommandBars->GetImageManager()->SetIcons(IDR_OUTLOOK_2013_MEETING_64, uMeetingIDs, _countof(uMeetingIDs), CSize(64, 64));

}

BOOL CMainFrame::CreateRibbonBar()
{
	CXTPCommandBars* pCommandBars = GetCommandBars();

	CMenu menu;
	menu.Attach(::GetMenu(m_hWnd));
	SetMenu(NULL);

	m_pRibbonBar = (CXTPRibbonBar*)pCommandBars->Add(_T("The Ribbon"), xtpBarTop, RUNTIME_CLASS(CXTPRibbonBar));
	if (!m_pRibbonBar)
	{
		return FALSE;
	}
	m_pRibbonBar->EnableDocking(0);

	CXTPControlPopup* pControlFile = (CXTPControlPopup*)m_pRibbonBar->AddSystemButton(ID_MENU_FILE);

	pControlFile = (CXTPControlPopup*)m_pRibbonBar->AddSystemButton(ID_MENU_FILE);
	pControlFile->SetIconId(IDB_GEAR);

	UINT uCommand = {IDB_GEAR};
	pCommandBars->GetImageManager()->SetIcons(IDB_GEAR, &uCommand, 1, CSize(0, 0), xtpImageNormal);

	CreateBackstage();
	
	CXTPRibbonTab* pTabHome = m_pRibbonBar->AddTab(ID_TAB_HOME);

	CXTPRibbonGroup* pGroupNew = pTabHome->AddGroup(ID_GROUP_NEW);
	pGroupNew->Add(xtpControlButton, ID_CALENDAR_ADD_NEW_EVENT);
	pGroupNew->Add(xtpControlButton, ID_CALENDAR_NEW_MEETING);
	pGroupNew->Add(xtpControlPopup, ID_CALENDAR_NEW_ITEMS);

	CXTPRibbonGroup* pGroupGoTo = pTabHome->AddGroup(ID_GROUP_GOTO);
	pGroupGoTo->Add(xtpControlButton, ID_CALENDAR_GOTO_TODAY);
	pGroupGoTo->Add(xtpControlPopup, ID_CALENDAR_GOTO_NEXT7DAYS);

	CXTPRibbonGroup* pGroupArrange = pTabHome->AddGroup(ID_GROUP_ARRANGE);
	pGroupArrange->Add(xtpControlButton, ID_CALENDAR_VIEW_DAY);
	pGroupArrange->Add(xtpControlButton, ID_CALENDAR_VIEW_WORKWEEK);
	pGroupArrange->Add(xtpControlButton, ID_CALENDAR_VIEW_WEEK);
	pGroupArrange->Add(xtpControlButton, ID_CALENDAR_VIEW_MONTH);
	pGroupArrange->Add(xtpControlButton, ID_CALENDAR_VIEW_SCHEDULE);

	CXTPRibbonGroup* pGroupManageCalendars = pTabHome->AddGroup(ID_GROUP_MANAGECALENDARS);
	CXTPControlPopup* pControlOpen = (CXTPControlPopup*)pGroupManageCalendars->Add(xtpControlPopup, ID_CALENDAR_MANAGE_OPEN);
	CMenu mnuOpen;
	VERIFY(mnuOpen.LoadMenu(IDR_MENU_CONTEXT_MULTI));
	pControlOpen->SetCommandBar(mnuOpen.GetSubMenu(0));

	pGroupManageCalendars->Add(xtpControlPopup, ID_CALENDAR_MANAGE_GROUPS);
	pGroupManageCalendars->Add(xtpControlButton, ID_VIEW_REMINDERS);

	CXTPRibbonGroup* pGroupShare = pTabHome->AddGroup(ID_GROUP_SHARE);
	pGroupShare->Add(xtpControlButton, ID_CALENDAR_SHARE_EMAIL);
	pGroupShare->Add(xtpControlButton, ID_CALENDAR_SHARE_SHARE);
	pGroupShare->Add(xtpControlPopup, ID_CALENDAR_SHARE_PUBLISH);
	pGroupShare->Add(xtpControlButton, ID_CALENDAR_SHARE_PERMISSIONS);

	//CXTPRibbonGroup* pGroupFind = pTabHome->AddGroup(ID_GROUP_FIND);
	//pGroupFind->Add(xtpControlButton, ID_CALENDAR_FIND_ADDRESSBOOK);

	CXTPRibbonGroup* pGroupProperties = pTabHome->AddGroup(ID_GROUP_PROPERTIES);
	pGroupProperties->Add(xtpControlButton, ID_VIEW_PROPERTIES);
	pGroupProperties->Add(xtpControlButton, IDC_ADVANCED_OPT_BTN);

	CXTPRibbonGroup* pGroupThemes = pTabHome->AddGroup(ID_GROUP_THEMES);
	CXTPControlPopup* pControlOptions = (CXTPControlPopup*)pGroupThemes->Add(xtpControlPopup, ID_CALENDAR_THEMES);
	CMenu mnuOptions;
	VERIFY(mnuOptions.LoadMenu(IDR_MENU_OPTIONS));
	pControlOptions->SetCommandBar(mnuOptions.GetSubMenu(0));

	CXTPControlPopup* pControlTimeLine = (CXTPControlPopup*)pGroupThemes->Add(xtpControlPopup, ID_CALENDAR_TIME);
	CMenu mnuTime;
	VERIFY(mnuTime.LoadMenu(IDR_MENU_CONTEXT_TIME));
	pControlTimeLine->SetCommandBar(mnuTime.GetSubMenu(0));

	pGroupThemes->Add(xtpControlButton, ID_VIEW_DATEPICKER);
	pGroupThemes->Add(xtpControlButton, ID_APP_ABOUT);

	m_pRibbonBar->SetCloseable(FALSE);
	
	return TRUE;
}

void CMainFrame::CreateBackstage()
{
	CXTPRibbonBar* pRibbonBar = DYNAMIC_DOWNCAST(CXTPRibbonBar, GetCommandBars()->GetMenuBar());
	ASSERT (pRibbonBar);

	CXTPRibbonControlSystemButton* pButton = pRibbonBar->GetSystemButton();

	CXTPRibbonBackstageView* pView = CXTPRibbonBackstageView::CreateBackstageView(GetCommandBars());

	pView->AddCommand(ID_FILE_SAVE);
	pView->AddCommand(ID_FILE_OPEN);
	pView->AddCommand(ID_FILE_LOAD_SAMPLE_MULTISCHEDULES_SIMPLE);
	pView->AddCommand(ID_FILE_LOAD_SAMPLE_MULTISCHEDULES_EXTENDED);
	pView->AddCommand(ID_FILE_MULTISCHEDULES_CFG);
	pView->AddCommand(ID_FILE_PAGE_SETUP);
	pView->AddCommand(ID_FILE_PRINT_PREVIEW);
	pView->AddCommand(ID_FILE_PRINT);

	//pView->AddCommand(IDC_ADVANCED_OPT_BTN);
	pView->AddCommand(ID_APP_EXIT);

	pButton->SetCommandBar(pView);
	
	pView->InternalRelease();
}
#endif

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.lpszClass = _T("XTPMainFrame");
	CXTPDrawHelpers::RegisterWndClass(AfxGetInstanceHandle(), cs.lpszClass, 
		CS_DBLCLKS, AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE|WS_EX_STATICEDGE;

	return TRUE;
}
#ifdef _XTP_INCLUDE_COMMANDBARS

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
#endif

void CMainFrame::OnViewOfficeTheme()
{
	m_dlgTheme.ShowWindow(SW_SHOW);
}
#ifdef _XTP_INCLUDE_COMMANDBARS

void CMainFrame::OnEmptyCommandRange(UINT)
{

}

void CMainFrame::OnEmptyCommand()
{

}

#endif

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
CDatePickerDialogBar::CDatePickerDialogBar()
{
}
BEGIN_MESSAGE_MAP(CDatePickerDialogBar, CDialogBar)
	ON_WM_SIZE()
	ON_MESSAGE_VOID(WM_INITDIALOG, OnInitDialog)
END_MESSAGE_MAP()

void CDatePickerDialogBar::OnInitDialog() 
{
	Default();

	VERIFY(m_wndDatePicker.SubclassDlgItem(IDC_DATEPICKER, this));
	
	m_wndDatePicker.SetBorderStyle(xtpDatePickerBorderNone);
	m_wndDatePicker.SetShowWeekNumbers(TRUE);

	ResizeDatePicker();
}

void CDatePickerDialogBar::ResizeDatePicker()
{
	if (::IsWindow(m_wndDatePicker.m_hWnd))
	{
		CXTPClientRect rcClient(this);
		CXTPWindowRect rcDatePicker(&m_wndDatePicker);
		ScreenToClient(&rcDatePicker);
		rcDatePicker.top = rcClient.top;
		rcDatePicker.bottom = rcClient.bottom;
		
		m_wndDatePicker.MoveWindow(&rcDatePicker);
	}
}

void CDatePickerDialogBar::OnSize(UINT nType, int cx, int cy)
{
	CDialogBar::OnSize(nType, cx, cy);

	ResizeDatePicker();
}

#ifdef _XTP_INCLUDE_COMMANDBARS

void CMainFrame::OnOptionsStyleVisualStudio2015Closed() 
{
	m_eStudio2015State = eStateClosed;
	SetStateColor();
}

void CMainFrame::OnUpdateOptionsStyleVisualStudio2015Closed(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_eStudio2015State == eStateClosed);
    pCmdUI->Enable(m_dlgTheme.m_tc.nTheme == xtpThemeDlgVisualStudio2015);
}

void CMainFrame::OnOptionsStyleVisualStudio2015Open() 
{
	m_eStudio2015State = eStateOpen;
	SetStateColor();
}

void CMainFrame::OnUpdateOptionsStyleVisualStudio2015Open(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_eStudio2015State == eStateOpen);
    pCmdUI->Enable(m_dlgTheme.m_tc.nTheme == xtpThemeDlgVisualStudio2015);
}

void CMainFrame::OnOptionsStyleVisualStudio2015Debug() 
{
	m_eStudio2015State = eStateDebug;
	SetStateColor();
}

void CMainFrame::OnUpdateOptionsStyleVisualStudio2015Debug(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_eStudio2015State == eStateDebug);
    pCmdUI->Enable(m_dlgTheme.m_tc.nTheme == xtpThemeDlgVisualStudio2015);
}

void CMainFrame::SetStateColor()
{
	switch (m_eStudio2015State)
	{
	case eStateClosed:
		XTPSetVSStateColor(GetCommandBars());
		break;
	case eStateOpen:
		XTPSetVSStateColor(GetCommandBars(), RGB(0,122,204));
		break;
	case eStateDebug:
		XTPSetVSStateColor(GetCommandBars(), RGB(202,81,0));
		break;
	}
}

#endif /*_XTP_INCLUDE_COMMANDBARS*/
