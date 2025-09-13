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
#include "ShortcutBar.h"
#include "MainFrm.h"

#include "ShortcutBarDoc.h"
#include "ShortcutBarView.h"


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
	ON_WM_CLOSE()
	ON_COMMAND(ID_THEME_CLIENTPANE, OnThemeClientpane)
	ON_UPDATE_COMMAND_UI(ID_THEME_CLIENTPANE, OnUpdateThemeClientpane)
	ON_COMMAND(ID_THEME_SHOWEXPANDBUTTON, OnThemeShowexpandbutton)
	ON_UPDATE_COMMAND_UI(ID_THEME_SHOWEXPANDBUTTON, OnUpdateThemeShowexpandbutton)
	ON_COMMAND(ID_THEME_SHOWACTIVEITEMONTOP, OnThemeShowactiveitemontop)
	ON_UPDATE_COMMAND_UI(ID_THEME_SHOWACTIVEITEMONTOP, OnUpdateThemeShowactiveitemontop)
	ON_COMMAND(ID_THEME_ALLOWFREERESIZE, OnThemeAllowfreeresize)
	ON_UPDATE_COMMAND_UI(ID_THEME_ALLOWFREERESIZE, OnUpdateThemeAllowfreeresize)
	ON_MESSAGE(XTPWM_SHORTCUTBAR_NOTIFY, OnShortcutBarNotify)
	ON_COMMAND(ID_THEME_SELECTTHEME, OnThemeSelectTheme)
	//}}AFX_MSG_MAP

#ifdef _XTP_INCLUDE_COMMANDBARS
	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
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

static UINT shortcuts[] =
{
	ID_SHORTCUT_MAIL,
	ID_SHORTCUT_CALENDAR,
	ID_SHORTCUT_CONTACTS,
	ID_SHORTCUT_TASKS,
	ID_SHORTCUT_NOTES,
	ID_SHORTCUT_FOLDERS,
	ID_SHORTCUT_SHORTCUTS,
	ID_SHORTCUT_JOURNAL
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
	m_csStylesPath += csStylesPath + _T("\\Styles\\");



	m_bClientPane = TRUE;

}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

#ifndef _XTP_INCLUDE_COMMANDBARS
	if (!m_wndToolBar.Create(this) ||
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

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// TODO: Remove this if you don't want tool tips
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

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

	pCommandBars->SetMenu(_T("Menu Bar"), IDR_MAINFRAME);


	CXTPToolBar* pStandardBar = (CXTPToolBar*)pCommandBars->Add(_T("Standard"), xtpBarTop);
	if (!pStandardBar ||
		!pStandardBar->LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
	}

	pCommandBars->GetToolTipContext()->SetStyle(xtpToolTipOffice);

	// Load the previous state for command bars.
	LoadCommandBars(_T("CommandBars"));

#endif

	// exclude unused themes.
	m_dlgTheme.ExcludeTheme(
		XTP_EXCLUDE_THEME_VISUALSTUDIO6    | 
		XTP_EXCLUDE_THEME_VISUALSTUDIO2005 | 
		XTP_EXCLUDE_THEME_VISUALSTUDIO2008 | 
		XTP_EXCLUDE_THEME_VISUALSTUDIO2010 | 
		XTP_EXCLUDE_THEME_VISUALSTUDIO2012 | 
		XTP_EXCLUDE_THEME_NATIVEWINDOWS    | 
		XTP_EXCLUDE_THEME_CUSTOM);

	// create theme dialog.
	VERIFY(m_dlgTheme.Create(IDD_THEME_DIALOG, this));

	// set startup theme
	m_dlgTheme.SetTheme(
		xtpThemeDlgOffice2016,
		xtpThemeColor2016Colorful,
		xtpThemeAccentOutlook,
		xtpThemeRibbonBackUndef,
		TRUE);

	// enable auto preview.
	m_dlgTheme.EnableAutoPreview(TRUE);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.lpszClass = _T("XTPMainFrame");
	CXTPDrawHelpers::RegisterWndClass(AfxGetInstanceHandle(), cs.lpszClass, 
		CS_DBLCLKS, AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	cs.style |= WS_CLIPSIBLINGS|WS_CLIPCHILDREN;

	return TRUE;
}
#ifdef _XTP_INCLUDE_COMMANDBARS

XTPPaintTheme GetPaintTheme(int nTheme)
{
	switch (nTheme)
	{
    case xtpThemeDlgOffice2000:       return xtpThemeOffice2000;
    case xtpThemeDlgOfficeXP:         return xtpThemeOfficeXP;
    case xtpThemeDlgOffice2003:       return xtpThemeOffice2003;
    case xtpThemeDlgOffice2007:       return xtpThemeResource;
    case xtpThemeDlgOffice2010:       return xtpThemeResource;
    case xtpThemeDlgOffice2013:       return xtpThemeOffice2013;
    case xtpThemeDlgOffice2016:       return xtpThemeOffice2013;
    case xtpThemeDlgVisualStudio2015: return xtpThemeVisualStudio2015;
	}
	return xtpThemeNone;
}
#endif
#ifdef _XTP_INCLUDE_CONTROLS

XTPControlTheme GetControlsTheme(int nTheme)
{
	switch (nTheme)
	{
    case xtpThemeDlgOffice2000:       return xtpControlThemeOffice2000;
    case xtpThemeDlgOfficeXP:         return xtpControlThemeOfficeXP;
    case xtpThemeDlgOffice2003:       return xtpControlThemeOffice2003;
    case xtpThemeDlgOffice2007:       return xtpControlThemeResource;
    case xtpThemeDlgOffice2010:       return xtpControlThemeResource;
    case xtpThemeDlgOffice2013:       return xtpControlThemeOffice2013;
    case xtpThemeDlgOffice2016:       return xtpControlThemeOffice2013;
    case xtpThemeDlgVisualStudio2015: return xtpControlThemeVisualStudio2015;
	}
	return xtpControlThemeOffice2000;
}
#endif
#ifdef _XTP_INCLUDE_CALENDAR

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
	}
	return xtpCalendarThemeOffice2000;
}
#endif

XTPShortcutBarPaintTheme GetShortcutBarTheme(int nTheme)
{
	switch (nTheme)
	{
    case xtpThemeDlgOffice2000:       return xtpShortcutThemeOffice2000;
    case xtpThemeDlgOfficeXP:         return xtpShortcutThemeOfficeXP;
    case xtpThemeDlgOffice2003:       return xtpShortcutThemeOffice2003;
    case xtpThemeDlgOffice2007:       return xtpShortcutThemeResource;
    case xtpThemeDlgOffice2010:       return xtpShortcutThemeResource;
    case xtpThemeDlgOffice2013:       return xtpShortcutThemeOffice2013;
    case xtpThemeDlgOffice2016:       return xtpShortcutThemeOffice2013;
    case xtpThemeDlgVisualStudio2015: return xtpShortcutThemeVisualStudio2015;
	}
	return xtpShortcutThemeOffice2000;
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
	pCommandBars->SetAllCaps(nTheme == xtpThemeDlgOffice2013 || nTheme == xtpThemeDlgVisualStudio2015);
	pCommandBars->GetPaintManager()->m_bAutoResizeIcons = TRUE;
	pCommandBars->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE);

	if (nTheme >= xtpThemeDlgOffice2013)
	{
		pCommandBars->GetToolTipContext()->SetStyle(xtpToolTipOffice2013);
	}
	else
	{
		pCommandBars->GetToolTipContext()->SetStyle(xtpToolTipResource);
	}
	
	EnableFrameTheme((nTheme > xtpThemeDlgOffice2003) ? pCommandBars : NULL);

	pCommandBars->GetPaintManager()->RefreshMetrics();
	pCommandBars->GetImageManager()->RefreshAll();
	pCommandBars->RedrawCommandBars();
#endif
#ifdef _XTP_INCLUDE_CONTROLS
	
	SendMessageToDescendants(WM_XTP_SETCONTROLTHEME, GetControlsTheme(nTheme), 0);
#endif

	m_wndShortcutBar.SetTheme(GetShortcutBarTheme(nTheme));

	BOOL bFlatBorders = (nTheme >= xtpThemeDlgOffice2010);

	m_paneMail.SetFlatStyle(bFlatBorders);
	m_paneCalendar.SetFlatStyle(bFlatBorders);
	m_paneContacts.SetFlatStyle(bFlatBorders);
	m_paneTasks.SetFlatStyle(bFlatBorders);
	m_paneNotes.SetFlatStyle(bFlatBorders);
	m_paneShortcuts.SetFlatStyle(bFlatBorders);
	m_paneFolders.SetFlatStyle(bFlatBorders);
	m_paneJournal.SetFlatStyle(bFlatBorders);

#ifdef _XTP_INCLUDE_CALENDAR
	m_paneCalendar.m_wndCalendar.SetPaintTheme(GetCalendarTheme(nTheme));
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

void CMainFrame::CreateShortcutBar()
{
	m_wndShortcutBar.Create(WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CRect(0, 0, 0, 0),
		&m_wndSplitter,  m_wndSplitter.IdFromRowCol(0, 0));

	m_wndShortcutBar.SetOwner(this);
	m_wndShortcutBar.GetToolTipContext()->SetStyle(xtpToolTipOffice);

	BOOL bUseAlphaIcons = XTPImageManager()->IsAlphaIconsSupported();

	XTPImageManager()->SetIcons(bUseAlphaIcons ? IDB_SHORTCUTS_SMALL_ALPHA : IDB_SHORTCUTS_SMALL, 
		shortcuts, sizeof(shortcuts)/sizeof(UINT), CSize(16, 16));

	XTPImageManager()->SetIcons(bUseAlphaIcons ? IDB_SHORTCUTS_BIG_ALPHA : IDB_SHORTCUTS_BIG, 
		shortcuts, sizeof(shortcuts)/sizeof(UINT), CSize(24, 24));


	VERIFY(m_paneMail.Create(_T("Mail"), &m_wndShortcutBar));
	VERIFY(m_paneCalendar.Create(_T("Calendar"), &m_wndShortcutBar));
	VERIFY(m_paneFolders.Create(_T("Folders"), &m_wndShortcutBar));
	VERIFY(m_paneContacts.Create(_T("Contacts"), &m_wndShortcutBar));

	VERIFY(m_paneTasks.Create(_T("Tasks"), &m_wndShortcutBar));
	VERIFY(m_paneNotes.Create(_T("Notes"), &m_wndShortcutBar));
	VERIFY(m_paneShortcuts.Create(_T("Shortcuts"), &m_wndShortcutBar));
	VERIFY(m_paneJournal.Create(_T("Journal"), &m_wndShortcutBar));

	CXTPShortcutBarItem* pItemMail = m_wndShortcutBar.AddItem(ID_SHORTCUT_MAIL, &m_paneMail);
	m_wndShortcutBar.AddItem(ID_SHORTCUT_CALENDAR, &m_paneCalendar);
	m_wndShortcutBar.AddItem(ID_SHORTCUT_CONTACTS, &m_paneContacts);
	m_wndShortcutBar.AddItem(ID_SHORTCUT_TASKS, &m_paneTasks);
	m_wndShortcutBar.AddItem(ID_SHORTCUT_NOTES, &m_paneNotes);
	m_wndShortcutBar.AddItem(ID_SHORTCUT_FOLDERS, &m_paneFolders);
	m_wndShortcutBar.AddItem(ID_SHORTCUT_SHORTCUTS, &m_paneShortcuts);
	m_wndShortcutBar.AddItem(ID_SHORTCUT_JOURNAL, &m_paneJournal);

	m_wndShortcutBar.AllowMinimize(TRUE);
	m_wndShortcutBar.ShowMinimizeButton(TRUE);

	m_wndShortcutBar.SelectItem(pItemMail);
	m_wndShortcutBar.LoadState(_T("ShortcutBar"));

}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
	m_wndSplitter.CreateStatic(this, 1, 2);

	CreateShortcutBar();

	m_wndSplitter.SetColumnInfo(0, XTP_DPI_X(250), 0);
	m_wndSplitter2.CreateStatic(&m_wndSplitter, 2, 1, WS_CHILD|WS_VISIBLE, m_wndSplitter.IdFromRowCol(0, 1));
	m_wndSplitter2.CreateView(0, 0, RUNTIME_CLASS(CShortcutBarView), CSize(0, XTP_DPI_Y(200)), pContext);
	m_wndSplitter2.CreateView(1, 0, RUNTIME_CLASS(CShortcutBarView), CSize(0, 0), pContext);

	return TRUE;
}

void CMainFrame::OnClose()
{
#ifdef _XTP_INCLUDE_COMMANDBARS
	// Save the current state for command bars.
	SaveCommandBars(_T("CommandBars"));
#endif

	m_wndShortcutBar.SaveState(_T("ShortcutBar"));

	CFrameWnd::OnClose();
}

LRESULT CMainFrame::OnShortcutBarNotify(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		case XTP_SBN_SELECTION_CHANGING:
			{
				CXTPShortcutBarItem* pItem = (CXTPShortcutBarItem*)lParam;
				TRACE(_T("Selection Changing. Item.Caption = %s\n"), pItem->GetCaption().operator LPCTSTR());

				// TODO: You can return -1 to ignore changing

			}
			return TRUE;
		case XTP_SBN_RCLICK:
			{
				CPoint point(lParam);
				CXTPShortcutBarItem* pItem = m_wndShortcutBar.HitTest(point);
				if (pItem)
				{
					TRACE(_T("RClick. Item.ID = %i\n"), pItem->GetID());

					CMenu mnu;
					mnu.LoadMenu(IDR_POPUP_MENU);

					m_wndShortcutBar.ClientToScreen(&point);

#ifdef _XTP_INCLUDE_COMMANDBARS
					CXTPCommandBars::TrackPopupMenu(mnu.GetSubMenu(0), 0, point.x, point.y, AfxGetMainWnd());
#else
					TrackPopupMenu(mnu.GetSubMenu(0)->GetSafeHmenu(), 0, point.x, point.y, 0, AfxGetMainWnd()->GetSafeHwnd(), 0);
#endif

				}
			}
			return TRUE;

		case XTP_SBN_MINIMIZEBUTTONCLICKED:
			{

				if (m_wndShortcutBar.IsShortcutBarMinimized())
				{
					m_wndSplitter.SetColumnInfo(0, XTP_DPI_X(250), 0);
				}
				else
				{
					m_wndSplitter.SetColumnInfo(0, XTP_DPI_X(32), 0);
				}
				m_wndSplitter.RecalcLayout();

			}
			return TRUE;
	}
	return 0;
}

void CMainFrame::OnThemeClientpane()
{
	m_bClientPane = !m_bClientPane;
	m_wndShortcutBar.SetClientPaneVisible(m_bClientPane);
}

void CMainFrame::OnUpdateThemeClientpane(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bClientPane);
}
void CMainFrame::OnCustomize()
{
#ifdef _XTP_INCLUDE_COMMANDBARS
	// get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if (pCommandBars == NULL)
		return;

	// instanciate the customize dialog
	CXTPCustomizeSheet dlg(pCommandBars);

	// add the options page to the customize dialog.
	CXTPCustomizeOptionsPage pageOptions(&dlg);
	dlg.AddPage(&pageOptions);

	// add the commands page to the customize dialog.
	CXTPCustomizeCommandsPage* pPageCommands = dlg.GetCommandsPage();
	pPageCommands->AddCategories(IDR_MAINFRAME);

	// initialize the commands page page.
	pPageCommands->InsertAllCommandsCategory();
	pPageCommands->InsertBuiltInMenus(IDR_MAINFRAME);
	pPageCommands->InsertNewMenuCategory();

	// display the customize dialog.
	dlg.DoModal();
#endif
}

void CMainFrame::OnThemeShowexpandbutton() 
{
	m_wndShortcutBar.ShowExpandButton(!m_wndShortcutBar.IsExpandButtonVisible());
}

void CMainFrame::OnUpdateThemeShowexpandbutton(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndShortcutBar.IsExpandButtonVisible()? TRUE: FALSE);	
}

void CMainFrame::OnThemeShowactiveitemontop() 
{
	BOOL bShowActiveItemOnTop = !m_wndShortcutBar.IsShowActiveItemOnTop();

	m_paneMail.ShowCaption(!bShowActiveItemOnTop);
	m_paneCalendar.ShowCaption(!bShowActiveItemOnTop);
	m_paneFolders.ShowCaption(!bShowActiveItemOnTop);
	m_paneMail.ShowCaption(!bShowActiveItemOnTop);
	m_paneContacts.ShowCaption(!bShowActiveItemOnTop);
	
	m_wndShortcutBar.ShowActiveItemOnTop(bShowActiveItemOnTop);	
}

void CMainFrame::OnUpdateThemeShowactiveitemontop(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndShortcutBar.IsShowActiveItemOnTop()? TRUE: FALSE);		
}

void CMainFrame::OnThemeAllowfreeresize() 
{
	m_wndShortcutBar.AllowFreeResize(!m_wndShortcutBar.IsAllowFreeResize());		
}

void CMainFrame::OnUpdateThemeAllowfreeresize(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndShortcutBar.IsAllowFreeResize()? TRUE: FALSE);		
}

void CMainFrame::OnThemeSelectTheme() 
{
	m_dlgTheme.ShowWindow(SW_SHOW);
}
