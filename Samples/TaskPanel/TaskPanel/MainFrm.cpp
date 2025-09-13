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
#include "TaskPanel.h"

#include "MainFrm.h"

#include "SlidersTheme.h"

#include "SearchDlg.h"

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
	ON_COMMAND(ID_TASKPANEL_ANIMATION, OnTaskpanelAnimation)
	ON_UPDATE_COMMAND_UI(ID_TASKPANEL_ANIMATION, OnUpdateTaskpanelAnimation)
	ON_COMMAND(ID_VIEW_SEARCH, OnViewSearch)
	ON_WM_CLOSE()
	ON_COMMAND(ID_TASKPANEL_SELECTTHEME, OnTaskPanelSelectTheme)
	//}}AFX_MSG_MAP
#if defined(_XTP_INCLUDE_COMMANDBARS) && defined(_XTP_INCLUDE_CONTROLS)
	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
#endif
	ON_MESSAGE(XTPWM_TASKPANEL_NOTIFY, OnTaskPanelNotify)
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
	pCommandBars->GetPaintManager()->m_bAutoResizeIcons = TRUE;
	pCommandBars->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE);

	CXTPCommandBar* pMenuBar = pCommandBars->SetMenu(_T("Menu Bar"), IDR_MAINFRAME);
	UNREFERENCED_PARAMETER(pMenuBar);

	CXTPToolBar* pStandardBar = (CXTPToolBar*)pCommandBars->Add(_T("Standard"), xtpBarTop);
	if (!pStandardBar ||
		!pStandardBar->LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}
	if (pCommandBars->GetImageManager()->IsAlphaIconsSupported())
	{
		pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME, IDR_TOOLBAR_A);
	}

	pStandardBar->GetControls()->FindControl(ID_VIEW_SEARCH)->SetStyle(xtpButtonIconAndCaption);
	pStandardBar->GetControls()->CreateOriginalControls();

	// Load the previous state for command bars.
	LoadCommandBars(_T("CommandBars"));
#endif

	// exclude unused themes.
	m_dlgTheme.ExcludeTheme(
		XTP_EXCLUDE_THEME_VISUALSTUDIO6    | 
		XTP_EXCLUDE_THEME_VISUALSTUDIO2005 | 
		XTP_EXCLUDE_THEME_VISUALSTUDIO2008 | 
		XTP_EXCLUDE_THEME_VISUALSTUDIO2012);

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

	// rename existing themes.
	m_dlgTheme.RenameItem(_T("Office XP"), _T("Office XP (Plain)"));
	
	// insert additional themes.
	m_dlgTheme.InsertAfter(_T("Office 2000"),    xtpThemeDlgCustom+1, _T("Office 2000 (Plain)"));
	m_dlgTheme.InsertAfter(_T("Office 2003"),    xtpThemeDlgCustom+2, _T("Office 2003 (Plain)"));
	m_dlgTheme.InsertAfter(_T("Native Windows"), xtpThemeDlgCustom+3, _T("Native Windows (Plain)"));

	return 0;
}

LRESULT CMainFrame::OnThemeChanged(WPARAM wParam, LPARAM lParam)
{
	int nTheme  = (int)LOWORD(wParam);
	int nColor  = (int)HIWORD(wParam);
	int nAccent = (int)LOWORD(lParam);

	switch (nTheme)
	{
    case xtpThemeDlgOffice2000: SetTheme(nTheme); break;
    case xtpThemeDlgOfficeXP:   SetTheme(nTheme); break;
    case xtpThemeDlgOffice2003: SetTheme(nTheme); break;
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
    case xtpThemeDlgVisualStudio2010:    SetTheme(nTheme);  break;
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
    case xtpThemeDlgNativeWindows: SetTheme(nTheme);    break;
    case xtpThemeDlgCustom:        SetTheme(nTheme, NULL, new CSlidersTheme); break; // Custom
    case xtpThemeDlgCustom+1:      SetTheme(nTheme, xtpIniOffice2010Silver);  break; // Office 2000 Plain
    case xtpThemeDlgCustom+2:      SetTheme(nTheme, xtpIniOffice2010Silver);  break; // Office 2003 Plain
    case xtpThemeDlgCustom+3:      SetTheme(nTheme, xtpIniOffice2010Blue);    break; // Native Windows Plain
	}

	return 0;
}
#ifdef _XTP_INCLUDE_COMMANDBARS

AFX_STATIC XTPPaintTheme GetPaintTheme(int nTheme)
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
    case xtpThemeDlgVisualStudio2010: return xtpThemeVisualStudio2010;
    case xtpThemeDlgVisualStudio2015: return xtpThemeVisualStudio2015;
    case xtpThemeDlgNativeWindows:    return xtpThemeNativeWinXP;
    case xtpThemeDlgCustom:           return xtpThemeCustom;
    case xtpThemeDlgCustom+1:         return xtpThemeOffice2000;
    case xtpThemeDlgCustom+2:         return xtpThemeOffice2003;
    case xtpThemeDlgCustom+3:         return xtpThemeNativeWinXP;
	}
	return xtpThemeOffice2000;
}

AFX_STATIC BOOL EnableFrameThemes(int nTheme)
{
	switch (nTheme)
	{
    case xtpThemeDlgOffice2007:
    case xtpThemeDlgOffice2010:
    case xtpThemeDlgOffice2013:
    case xtpThemeDlgOffice2016:
    case xtpThemeDlgVisualStudio2015: return TRUE;
	}
	return FALSE;
}
#endif
#ifdef _XTP_INCLUDE_CONTROLS

AFX_STATIC XTPControlTheme GetControlsTheme(int nTheme)
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
    case xtpThemeDlgVisualStudio2010: return xtpControlThemeVisualStudio2010;
    case xtpThemeDlgVisualStudio2015: return xtpControlThemeVisualStudio2015;
    case xtpThemeDlgNativeWindows:    return xtpControlThemeNativeWinXP;
    case xtpThemeDlgCustom:           return xtpControlThemeCustom;
    case xtpThemeDlgCustom+1:         return xtpControlThemeOffice2000;
    case xtpThemeDlgCustom+2:         return xtpControlThemeOffice2003;
    case xtpThemeDlgCustom+3:         return xtpControlThemeNativeWinXP;
	}
	return xtpControlThemeOffice2000;
}
#endif

AFX_STATIC XTPTaskPanelPaintTheme GetTaskPanelTheme(int nTheme)
{
	switch (nTheme)
	{
    case xtpThemeDlgOffice2000:       return xtpTaskPanelThemeOffice2000;
    case xtpThemeDlgOfficeXP:         return xtpTaskPanelThemeOfficeXPPlain;
    case xtpThemeDlgOffice2003:       return xtpTaskPanelThemeOffice2003;
    case xtpThemeDlgOffice2007:       return xtpTaskPanelThemeResource;
    case xtpThemeDlgOffice2010:       return xtpTaskPanelThemeResource;
    case xtpThemeDlgOffice2013:       return xtpTaskPanelThemeOffice2013;
    case xtpThemeDlgOffice2016:       return xtpTaskPanelThemeOffice2013;
    case xtpThemeDlgVisualStudio2010: return xtpTaskPanelThemeVisualStudio2010;
    case xtpThemeDlgVisualStudio2015: return xtpTaskPanelThemeVisualStudio2015;
    case xtpThemeDlgNativeWindows:    return xtpTaskPanelThemeNativeWinXP;
    case xtpThemeDlgCustom:           return xtpTaskPanelThemeCustom;
    case xtpThemeDlgCustom+1:         return xtpTaskPanelThemeOffice2000Plain;
    case xtpThemeDlgCustom+2:         return xtpTaskPanelThemeOffice2003Plain;
    case xtpThemeDlgCustom+3:         return xtpTaskPanelThemeNativeWinXPPlain;
	}
	return xtpTaskPanelThemeOffice2000;
}

void CMainFrame::SetTheme(int nTheme, LPCTSTR lpszINI /*=NULL*/, CXTPTaskPanelPaintManager* pPaintManager /*=NULL*/)
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
	
	EnableFrameTheme(EnableFrameThemes(nTheme) ? pCommandBars : NULL);

	pCommandBars->GetPaintManager()->RefreshMetrics();
	pCommandBars->GetImageManager()->RefreshAll();
	pCommandBars->RedrawCommandBars();
#endif
#ifdef _XTP_INCLUDE_CONTROLS
	
	SendMessageToDescendants(WM_XTP_SETCONTROLTHEME, GetControlsTheme(nTheme), 0);
#endif

	if (pPaintManager)
	{
		m_wndTaskPanel.SetCustomTheme(pPaintManager);
	}
	else
	{
		m_wndTaskPanel.SetTheme(GetTaskPanelTheme(nTheme));
	}

	SendMessage(WM_NCPAINT);
	RedrawWindow(0, 0, RDW_ALLCHILDREN|RDW_INVALIDATE);
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.lpszClass = _T("XTPMainFrame");
	CXTPDrawHelpers::RegisterWndClass(AfxGetInstanceHandle(), cs.lpszClass, 
		CS_DBLCLKS, AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	cs.style |= WS_CLIPCHILDREN|WS_CLIPSIBLINGS;

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

void CMainFrame::CreateTaskPanelItems()
{
	CXTPTaskPanelGroup* pGroupSystem = m_wndTaskPanel.AddGroup(ID_TASKGROUP_SYSTEM);
	pGroupSystem->SetIconIndex(IDI_SYSTEM_TASKS);

	pGroupSystem->AddLinkItem(ID_TASKITEM_HIDECONTENTS, 0);
	pGroupSystem->AddLinkItem(ID_TASKITEM_ADDORREMOVE, 1);
	pGroupSystem->AddLinkItem(ID_TASKITEM_SEARCH, 2);

	pGroupSystem->SetSpecialGroup();

	CXTPTaskPanelGroup* pGroupFiles = m_wndTaskPanel.AddGroup(ID_TASKGROUP_FILES);

	pGroupFiles->AddLinkItem(ID_TASKITEM_NEWFOLDER, 3);
	pGroupFiles->AddLinkItem(ID_TASKITEM_PUBLISH, 4);
	pGroupFiles->AddLinkItem(ID_TASKITEM_SHARE, 5);


	CXTPTaskPanelGroup* pGroupOtherPlaces = m_wndTaskPanel.AddGroup(ID_TASKGROUP_OTHERPLACES);

	pGroupOtherPlaces->AddLinkItem(ID_TASKITEM_MYCOMPUTER, 6);
	pGroupOtherPlaces->AddLinkItem(ID_TASKITEM_MYDOCUMENTS, 7);
	pGroupOtherPlaces->AddLinkItem(ID_TASKITEM_SHAREDDOCUMENTS, 8);
	pGroupOtherPlaces->AddLinkItem(ID_TASKITEM_MYNETWORKPLACES, 9);

	//pGroupOtherPlaces->ShowCaption(FALSE);
	//pGroupOtherPlaces->SetExpanded(FALSE);
	//pGroupOtherPlaces->SetExpandable(FALSE);

	CXTPTaskPanelGroup* pGroupDetails = m_wndTaskPanel.AddGroup(ID_TASKGROUP_DETAILS);

	CXTPTaskPanelGroupItem* pItemDisk = pGroupDetails->AddTextItem(_T("Local Disk (C:)"));
	pItemDisk->SetBold(TRUE);
	pItemDisk->GetMargins().SetRectEmpty();

	pGroupDetails->AddTextItem(_T("Local Disk"));
	pGroupDetails->AddTextItem(_T("File Sytem: FAT32"));
	pGroupDetails->AddTextItem(_T("Free Space: 23,3 GB"));
	pGroupDetails->AddTextItem(_T("Total Size: 76,2 GB"));

	m_wndTaskPanel.GetImageManager()->SetIcons(XTPImageManager()->IsAlphaIconsSupported()?
		IDB_TASKICONS_ALPHA: IDB_TASKICONS_NORMAL, 0, 0, CSize(16, 16));

	m_wndTaskPanel.GetImageManager()->SetIcon(IDI_SYSTEM_TASKS, IDI_SYSTEM_TASKS, CSize(32, 32));

}
BOOL CMainFrame::CreateTaskPanel()
{

	if (!m_wndTaskPanel.Create(WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_TABSTOP, CRect(0, 0, 0, 0), &m_wndSplitter, m_wndSplitter.IdFromRowCol(0, 0)))
		return FALSE;

	m_wndTaskPanel.SetOwner(this);

	m_wndSplitter.SetColumnInfo(0, 210, 0);


	CreateTaskPanelItems();

	return TRUE;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
	m_wndSplitter.CreateStatic(this, 1, 2);

	if (!CreateTaskPanel())
		return FALSE;

	m_wndSplitter.CreateView(0, 1, pContext->m_pNewViewClass, CSize(300, 0), pContext);

	return TRUE;
}

void CMainFrame::OnTaskpanelAnimation()
{
	m_wndTaskPanel.SetAnimation(m_wndTaskPanel.GetAnimation() == xtpTaskPanelAnimationNo? xtpTaskPanelAnimationYes: xtpTaskPanelAnimationNo);
}

void CMainFrame::OnUpdateTaskpanelAnimation(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndTaskPanel.GetAnimation() == xtpTaskPanelAnimationYes);
}

LRESULT CMainFrame::OnTaskPanelNotify(WPARAM wParam, LPARAM lParam)
{
	switch(wParam) {
	case XTP_TPN_CLICK:
		{
			CXTPTaskPanelGroupItem* pItem = (CXTPTaskPanelGroupItem*)lParam;
			TRACE(_T("Click Event: pItem.Caption = %s, pItem.ID = %i\n"), 
				pItem->GetCaption().operator LPCTSTR(), pItem->GetID());
		}
		break;

	case XTP_TPN_RCLICK:
		{
			CXTPTaskPanelItem* pItem = (CXTPTaskPanelItem*)lParam;
			TRACE(_T("RClick Event: pItem.Caption = %s, pItem.ID = %i\n"), 
				pItem->GetCaption().operator LPCTSTR(), pItem->GetID());
		}
		break;
	}

	return 0;
}

void CMainFrame::OnViewSearch()
{
	CSearchDlg sd;
	sd.DoModal();
}

void CMainFrame::OnClose()
{
#ifdef _XTP_INCLUDE_COMMANDBARS
	// Save the current state for command bars.
	SaveCommandBars(_T("CommandBars"));
#endif

	CFrameWnd::OnClose();
}

#if defined(_XTP_INCLUDE_COMMANDBARS) && defined(_XTP_INCLUDE_CONTROLS)

void CMainFrame::OnCustomize()
{
	// get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if (pCommandBars == NULL)
		return;

	// instantiate the customize dialog
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
}

#endif

void CMainFrame::OnTaskPanelSelectTheme() 
{
	m_dlgTheme.ShowWindow(SW_SHOW);
}
