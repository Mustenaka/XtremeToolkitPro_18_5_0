// PaneViewTaskPanel.cpp 
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
#include "PaneViewTaskPanel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaneViewTaskPanel

CPaneViewTaskPanel::CPaneViewTaskPanel() : CPaneWnd(), m_nToolboxIcons(IDB_TOOLBOXICONS)
{
}

CPaneViewTaskPanel::~CPaneViewTaskPanel()
{
}


BEGIN_MESSAGE_MAP(CPaneViewTaskPanel, CPaneWnd)
	//{{AFX_MSG_MAP(CPaneViewTaskPanel)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPaneViewTaskPanel message handlers

int CPaneViewTaskPanel::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndTaskPanel.GetSafeHwnd())
	{
		if (!m_wndTaskPanel.Create(WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN, CRect(0, 0, 0, 0), this, 0))
			return FALSE;
		
		m_wndTaskPanel.SetOwner(this);
		
		m_wndTaskPanel.GetImageManager()->SetIcons(IDB_TOOLBOXICONS, 0, 0, CSize(16, 16));
		m_wndTaskPanel.SetBehaviour(xtpTaskPanelBehaviourExplorer);
		m_wndTaskPanel.SetTheme(xtpTaskPanelThemeVisualStudio2005);
		m_wndTaskPanel.SetHotTrackStyle(xtpTaskPanelHighlightItem);
		m_wndTaskPanel.SetSelectItemOnFocus(TRUE);
		m_wndTaskPanel.SetSingleSelection();
		m_wndTaskPanel.AllowDrag(TRUE);		
	}

	return 0;
}

void CPaneViewTaskPanel::DoPropExchange(CXTPPropExchange* pPX)
{
	m_wndTaskPanel.GetGroups()->DoPropExchange(pPX);
}

CXTPTaskPanelGroup* CPaneViewTaskPanel::CreateToolboxGroup(UINT nID)
{
	CXTPTaskPanelGroup* pFolder = m_wndTaskPanel.AddGroup(nID);

	CXTPTaskPanelGroupItem* pPointer = pFolder->AddLinkItem(ID_TOOLBOXITEM_POINTER, 0);
	pPointer->SetItemSelected(TRUE);
	pPointer->AllowDrag(FALSE);
	pPointer->AllowDrop(FALSE);

	return pFolder;
}

void CPaneViewTaskPanel::ResetToolboxItems()
{
	m_wndTaskPanel.GetGroups()->Clear(FALSE);

	CXTPTaskPanelGroup* pFolderPropertyPanes = CreateToolboxGroup(ID_TOOLBOXFOLDER_PROPERTYPANES);

	CXTPTaskPanelGroup* pFolderData = CreateToolboxGroup(ID_TOOLBOXFOLDER_DATA);
	pFolderData->AddLinkItem(ID_TOOLBOXITEM_DATASET                 ,26);
	pFolderData->AddLinkItem(ID_TOOLBOXITEM_OLEDBDATAADAPTER        ,27);
	pFolderData->AddLinkItem(ID_TOOLBOXITEM_OLEDBCONNECTION         ,28);
	pFolderData->AddLinkItem(ID_TOOLBOXITEM_OLEDBCOMMAND            ,29);
	pFolderData->AddLinkItem(ID_TOOLBOXITEM_SQLDATAADAPTER          ,30);
	pFolderData->AddLinkItem(ID_TOOLBOXITEM_SQLCONNECTION           ,31);
	pFolderData->AddLinkItem(ID_TOOLBOXITEM_SQLCOMMAND              ,32);
	pFolderData->AddLinkItem(ID_TOOLBOXITEM_DATAVIEW                ,33);

	CXTPTaskPanelGroup* pFolderComponents = CreateToolboxGroup(ID_TOOLBOXFOLDER_COMPONENTS);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_FILESYSTEMWATCHER     ,34);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_EVENTLOG              ,35);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_DIRECTORYENTRY        ,36);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_DIRECTORYSEARCHER     ,37);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_MESSAGEQUEUE          ,38);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_PERFORMANCECOUNTER    ,39);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_PROCESS               ,40);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_SERVICECONTROLLER     ,41);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_TIMER                 ,42);

	CXTPTaskPanelGroup* pFolderWindowsForms = CreateToolboxGroup(ID_TOOLBOXFOLDER_WINDOWSFORMS);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_BUTTON,             1);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_CHECK_BOX,              2);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_EDIT_CONTROL,           3);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_COMBO_BOX,              4);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_LIST_BOX,               5);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_GROUP_BOX,              6);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_RADIO_BUTTON,           7);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_STATIC_TEXT,            8);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_PICTURE_CONTROL,        9);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_HORIZONTAL_SCROLL_BAR,  10);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_VERTICAL_SCROLL_BAR,    11);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_SLIDER_CONTROL,     12);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_SPIN_CONTROL,           13);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_PROGRESS_CONTROL,       14);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_HOT_KEY,                15);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_LIST_CONTROL,           16);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_TREE_CONTROL,           17);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_TAB_CONTROL,            18);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_ANIMATION_CONTROL,      19);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_RICH_EDIT_CONTROL,      20);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_DATE_TIME_PICKER,       21);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_MONTH_CALENDAR_CONTROL,22);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_IP_ADDRESS_CONTROL, 23);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_EXTENDED_COMBO_BOX, 24);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_CUSTOM_CONTROL,     25);

	CreateToolboxGroup(ID_TOOLBOXFOLDER_CLIPBOARDRING);
	CreateToolboxGroup(ID_TOOLBOXFOLDER_GENERAL);

	pFolderPropertyPanes->SetExpanded(TRUE);

}

void CPaneViewTaskPanel::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	MoveChildren(NULL, &m_wndTaskPanel, cx, cy);
}

void CPaneViewTaskPanel::OnSetFocus(CWnd* /*pOldWnd*/)
{
	m_wndTaskPanel.SetFocus();
}

void CPaneViewTaskPanel::RefreshMetrics(AppTheme nTheme)
{
	CPaneWnd::RefreshMetrics(nTheme);

	switch (nTheme)
	{
	case themeVS6:
		m_nToolboxIcons = IDB_TOOLBOXICONS;
		m_wndTaskPanel.SetTheme(xtpTaskPanelThemeVisualStudio2003);
		break;
	case themeVS2003:
		m_nToolboxIcons = IDB_TOOLBOXICONS;
		m_wndTaskPanel.SetTheme(xtpTaskPanelThemeVisualStudio2003);
		break;
	case themeVS2005:
		m_nToolboxIcons = IDB_TOOLBOXICONS;
		m_wndTaskPanel.SetTheme(xtpTaskPanelThemeVisualStudio2005);
		break;
	case themeVS2008:
		m_nToolboxIcons = IDB_TOOLBOXICONS;
		m_wndTaskPanel.SetTheme(xtpTaskPanelThemeVisualStudio2005);
		break;
	case themeVS2010:
		m_nToolboxIcons = IDB_TOOLBOXICONS;
		m_wndTaskPanel.SetTheme(xtpTaskPanelThemeVisualStudio2010);
		break;
	case themeVS2012Light:
		m_nToolboxIcons = IDB_TOOLBOXICONS_LIGHT;
		m_wndTaskPanel.SetTheme(xtpTaskPanelThemeVisualStudio2012Light);
		break;
	case themeVS2012Dark:
		m_nToolboxIcons = IDB_TOOLBOXICONS_DARK;
		m_wndTaskPanel.SetTheme(xtpTaskPanelThemeVisualStudio2012Dark);
		break;
	case themeVS2015Light:
		m_nToolboxIcons = IDB_TOOLBOXICONS_LIGHT;
		m_wndTaskPanel.SetTheme(xtpTaskPanelThemeVisualStudio2015);
		break;
	case themeVS2015Dark:
		m_nToolboxIcons = IDB_TOOLBOXICONS_DARK;
		m_wndTaskPanel.SetTheme(xtpTaskPanelThemeVisualStudio2015);
		break;
	case themeVS2015Blue:
		m_nToolboxIcons = IDB_TOOLBOXICONS_LIGHT;
		m_wndTaskPanel.SetTheme(xtpTaskPanelThemeVisualStudio2015);
		break;
	}

	XTP_SAFE_CALL1(m_wndTaskPanel.GetImageManager(),
		SetIcons(m_nToolboxIcons, 0, 0, CSize(16, 16)));

	CXTPClientRect rClient(this);
	MoveChildren(NULL, &m_wndTaskPanel, rClient.Width(), rClient.Height());
}
