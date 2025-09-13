// PaneViewProperties.cpp
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
#include "GUI_VisualStudio.h"
#include "PaneWnd.h"
#include "PaneViewProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaneViewProperties

CPaneViewProperties::CPaneViewProperties()
{
}

CPaneViewProperties::~CPaneViewProperties()
{
}


BEGIN_MESSAGE_MAP(CPaneViewProperties, CPaneWnd)
	//{{AFX_MSG_MAP(CPaneViewProperties)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_PANEPROPERTIES_CATEGORIZED, OnPanePropertiesCategorized)
	ON_UPDATE_COMMAND_UI(ID_PANEPROPERTIES_CATEGORIZED, OnUpdatePanePropertiesCategorized)
	ON_COMMAND(ID_PANEPROPERTIES_ALPHABETIC, OnPanePropertiesAlphabetic)
	ON_UPDATE_COMMAND_UI(ID_PANEPROPERTIES_ALPHABETIC, OnUpdatePanePropertiesAlphabetic)
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaneViewProperties message handlers

int CPaneViewProperties::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	VERIFY(m_wndToolBar.CreateToolBar(WS_TABSTOP|WS_VISIBLE|WS_CHILD|CBRS_TOOLTIPS, this));
	VERIFY(m_wndToolBar.LoadToolBar(IDR_PANE_PROPERTIES));


	if (m_wndPropertyGrid.GetSafeHwnd() == 0)
	{
		m_wndPropertyGrid.Create( CRect(0, 0, 0, 0), this, 0 );
		m_wndPropertyGrid.SetOwner(this);
		m_wndPropertyGrid.SetTheme(xtpGridThemeVisualStudio2005);

		CFont font;
		font.CreatePointFont(60, _T("Marlett"));

		LOGFONT lf;
		font.GetLogFont(&lf);



		// create document settings category.
		CXTPPropertyGridItem* pSettings        = m_wndPropertyGrid.AddCategory(_T("Document Settings"));

		// add child items to category.
		CXTPPropertyGridItem* pItemSaveOnClose = pSettings->AddChildItem(new CXTPPropertyGridItemBool(_T("SaveOnClose"), TRUE));
		pSettings->AddChildItem(new CXTPPropertyGridItemFont(_T("WindowFont"), lf));
		pSettings->AddChildItem(new CXTPPropertyGridItemSize(_T("WindowSize"), CSize(100, 100)));

		pSettings->Expand();
		pItemSaveOnClose->Select();

		// create global settings category.
		CXTPPropertyGridItem* pGlobals      = m_wndPropertyGrid.AddCategory(_T("Global Settings"));

		// add child items to category.
		CXTPPropertyGridItem* pItemGreeting = pGlobals->AddChildItem(new CXTPPropertyGridItem(_T("Greeting Text"), _T("Welcome to your application!")));
		pGlobals->AddChildItem(new CXTPPropertyGridItemNumber(_T("ItemsInMRUList"), 4));
		CXTPPropertyGridItem* pItemRate     = pGlobals->AddChildItem(new CXTPPropertyGridItemNumber(_T("MaxRepeatRate"), 10));
		pGlobals->AddChildItem(new CXTPPropertyGridItemColor(_T("ToolbarColor"), RGB(255, 192,128)));

		pItemGreeting->SetReadOnly(TRUE);
		pItemRate->SetDescription(_T("The rate in milliseconds that the text will repeat."));

		// create version category.
		CXTPPropertyGridItem* pVersion      = m_wndPropertyGrid.AddCategory(_T("Version"));

		// add child items to category.
		CXTPPropertyGridItem* pItemVersion  = pVersion->AddChildItem(new CXTPPropertyGridItem(_T("AppVersion"), _T("1.0")));
		CXTPPropertyGridItem* pItemLanguage = pVersion->AddChildItem(new CXTPPropertyGridItem(_T("Language"), _T("English (United States)")));

		pItemVersion->SetReadOnly(TRUE);
		pVersion->Expand();

		CXTPPropertyGridItemConstraints* pList = pItemLanguage->GetConstraints();

		pList->AddConstraint(_T("Neutral"));
		pList->AddConstraint(_T("Arabic"));
		pList->AddConstraint(_T("German"));
		pList->AddConstraint(_T("Chinese(Taiwan)"));
		pList->AddConstraint(_T("English (United Kingdom)"));
		pList->AddConstraint(_T("English (United States)"));
		pList->AddConstraint(_T("France"));
		pList->AddConstraint(_T("Russian"));

		pItemLanguage->SetFlags(xtpGridItemHasComboButton | xtpGridItemHasEdit);

		// create custom items category.
		CXTPPropertyGridItem* pCustom   = m_wndPropertyGrid.AddCategory(_T("Custom Items"));


		// add multi level tree node.
		CXTPPropertyGridItem* pItemOne    = pCustom->AddChildItem(new CXTPPropertyGridItem(_T("First Level"), _T("")));
		CXTPPropertyGridItem* pItemTwo    = pItemOne->AddChildItem(new CXTPPropertyGridItem(_T("Second Level"), _T("")));
		CXTPPropertyGridItem* pItemThird     = pItemTwo->AddChildItem(new CXTPPropertyGridItem(_T("Third Level"), _T("")));
		pItemThird->AddChildItem(new CXTPPropertyGridItem(_T("Fourth Level 1"), _T("")));
		pItemThird->AddChildItem(new CXTPPropertyGridItem(_T("Fourth Level 2"), _T("")));

		m_wndPropertyGrid.HighlightChangedItems(TRUE);
	}

	return 0;
}

void CPaneViewProperties::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	MoveChildren(&m_wndToolBar, &m_wndPropertyGrid, cx, cy);
}

void CPaneViewProperties::OnPanePropertiesCategorized()
{
	m_wndPropertyGrid.SetPropertySort(xtpGridSortCategorized);
}

void CPaneViewProperties::OnUpdatePanePropertiesCategorized(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropertyGrid.GetPropertySort() == xtpGridSortCategorized);
}

void CPaneViewProperties::OnPanePropertiesAlphabetic()
{
	m_wndPropertyGrid.SetPropertySort(xtpGridSortAlphabetical);
}

void CPaneViewProperties::OnUpdatePanePropertiesAlphabetic(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropertyGrid.GetPropertySort() == xtpGridSortAlphabetical);
}

void CPaneViewProperties::OnSetFocus(CWnd* /*pOldWnd*/)
{
	m_wndPropertyGrid.SetFocus();
}

void CPaneViewProperties::RefreshMetrics(AppTheme nTheme)
{
	CPaneWnd::RefreshMetrics(nTheme);

	switch (nTheme)
	{
	case themeVS6:
		m_wndPropertyGrid.SetTheme(xtpGridThemeDefault);
		break;
	case themeVS2003:
		m_wndPropertyGrid.SetTheme(xtpGridThemeOfficeXP);
		break;
	case themeVS2005:
		m_wndPropertyGrid.SetTheme(xtpGridThemeVisualStudio2005);
		break;
	case themeVS2008:
		m_wndPropertyGrid.SetTheme(xtpGridThemeVisualStudio2005);
		break;
	case themeVS2010:
		m_wndPropertyGrid.SetTheme(xtpGridThemeVisualStudio2010);
		break;
	case themeVS2012Light:
		m_wndPropertyGrid.SetTheme(xtpGridThemeVisualStudio2012Light);
		break;
	case themeVS2012Dark:
		m_wndPropertyGrid.SetTheme(xtpGridThemeVisualStudio2012Dark);
		break;
	case themeVS2015Light:
	case themeVS2015Dark:
	case themeVS2015Blue:
		m_wndPropertyGrid.SetTheme(xtpGridThemeVisualStudio2015);
		break;
	}

	CXTPClientRect rClient(this);
	MoveChildren(&m_wndToolBar, &m_wndPropertyGrid, rClient.Width(), rClient.Height());
}
