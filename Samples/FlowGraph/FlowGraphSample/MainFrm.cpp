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
#include "FlowGraphSample.h"

#include "MainFrm.h"
#include "DialogPerfomanceTest.h"
#include "DialogControlsTest.h"
#include "DialogPageTransitionTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

#define ID_TESTS_TOOLBAR_BUTTON					0xCAFE
#define ID_TESTS_TOOLBAR_BUTTON_POPUP_ID		0xCAFE + 1

#define ID_GRAPH_TYPE_COMBO						0xCAFE + 2

enum ID_DOCKING_PANE
{
	ID_VIEW_TOOLBOX = 0x14, ID_VIEW_PROPERTYGRID
};

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_TEST_GRAPHWITH500NODES, OnTestGraphwith500nodes)
	ON_COMMAND(ID_TEST_NODESWITHCONTROLS, OnTestNodeswithcontrols)
	ON_COMMAND(ID_TEST_PAGETRANSITION, OnTestPagetransition)
	
#ifdef _XTP_INCLUDE_DOCKINGPANE
	ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify)
#endif

	ON_UPDATE_COMMAND_UI(ID_TESTS_TOOLBAR_BUTTON, OnUpdateContextTests)

#ifdef _XTP_INCLUDE_COMMANDBARS
	ON_XTP_INITCOMMANDSPOPUP()

	ON_XTP_EXECUTE(ID_GRAPH_TYPE_COMBO, OnGraphChanged)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_TYPE_COMBO, OnGraphChanged_Update)
#endif

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
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
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME_SIMPLE))
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


	if (!m_ilToolbarIcons.Create(16, 16, ILC_MASK|ILC_COLOR24, 0, 1))
		return -1;

	CBitmap bmp;
	VERIFY(bmp.LoadBitmap(IDR_MAINFRAME_SIMPLE));
	
	m_ilToolbarIcons.Add(&bmp, CXTPImageManager::GetBitmapMaskColor(bmp, CPoint(0, 0)));
	m_wndToolBar.SendMessage(TB_SETIMAGELIST, 0, (LPARAM)m_ilToolbarIcons.GetSafeHandle());

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

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
	
	XTPPaintManager()->SetTheme(xtpThemeRibbon);
	
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

	// insert Tests menu in the toolbar for convenience

	CXTPControlComboBox *pComboBox = new CXTPControlComboBox(pCommandBars);
	pComboBox->SetID(ID_GRAPH_TYPE_COMBO);
	pComboBox->SetCaption(_T("Flow Graph Diagrams: "));
	pComboBox->SetStyle(xtpButtonIconAndCaption);
	pComboBox->SetWidth(XTP_DPI_X(270));
	//pComboBox->SetDropDownWidth(100);

	pComboBox->AddString(_T("Database Relations") );
	pComboBox->AddString(_T("Network Diagram") );
	pComboBox->AddString(_T("Flow Chart") );

	pComboBox->SetCurSel(0);

	pCommandBar->GetControls()->InsertAt(pComboBox, pCommandBar->GetControls()->GetCount() - 1);

	//////////////////////////////////////////////////////////////////////////

	CXTPControlPopup *pButtonTests = new CXTPControlPopup();

	pButtonTests->SetCaption(_T("Flow Graph Tests"));
	pButtonTests->SetID(ID_TESTS_TOOLBAR_BUTTON);
	pButtonTests->SetBeginGroup(TRUE);
	pButtonTests->SetStyle(xtpButtonIconAndCaption);

	//pButtonTests->SetCustomIcon(static_cast<HICON>(LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME), IMAGE_ICON, 16, 16, LR_SHARED)) );

	pCommandBar->GetControls()->InsertAt(pButtonTests, pCommandBar->GetControls()->GetCount() - 1);

	CXTPPopupBar* pLineBar = (CXTPPopupBar*)CXTPPopupBar::CreateObject();
	pButtonTests->SetCommandBar(pLineBar);
	pLineBar->InternalRelease();

	pLineBar->SetBarID(ID_TESTS_TOOLBAR_BUTTON_POPUP_ID);	

	// end of tests

	pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME, IDR_TOOLBAR_ALPHA);

	CXTPStatusBarPane* pPane = m_wndStatusBar.AddIndicator(ID_INDICATOR_ZOOM);
	pPane->SetText(_T("100%"));
	pPane->SetButton();
	pPane->SetTextAlignment(DT_CENTER);
	pPane->SetPadding(XTP_DPI_X(8), 0, XTP_DPI_X(8), 0);
	pPane->SetWidth(pPane->GetBestFit());
	pPane->SetTooltip(_T("Zoom level. Click to open the Zoom dialog box."));
	pPane->SetCaption(_T("&Zoom"));
	pPane->SetBeginGroup(FALSE);
	
	CXTPStatusBarSliderPane* pZoomPane = (CXTPStatusBarSliderPane*)m_wndStatusBar.AddIndicator(new CXTPStatusBarSliderPane(), ID_INDICATOR_ZOOMSLIDER);
	pZoomPane->SetBeginGroup(FALSE);
	pZoomPane->SetWidth(XTP_DPI_X(130));
	pZoomPane->SetPos(500); // We will convert 0 -> 10%, 500 -> 100 %, 1000 -> 500 %
	pZoomPane->SetRange(0, 1000);
	pZoomPane->SetCaption(_T("&Zoom Slider"));
	pZoomPane->SetTooltip(_T("Zoom"));
	pZoomPane->SetTooltipPart(XTP_HTSCROLLUP, _T("Zoom Out"));
	pZoomPane->SetTooltipPart(XTP_HTSCROLLDOWN, _T("Zoom In"));
	
	if (theApp.m_hModule2013)
	{
		XTPResourceImages()->SetHandle(theApp.m_hModule2013, _T("OFFICE2013WHITE.INI"));
		XTPPaintManager()->SetTheme(xtpThemeOffice2013);
		CXTPCommandBarsFrameHook::m_bAllowDwm = FALSE;
		GetCommandBars()->EnableFrameTheme(TRUE);
		GetCommandBars()->SetAllCaps(TRUE);

		UINT uiSystemMenu[] = {ID_FILE_NEW,ID_FILE_OPEN,ID_FILE_SAVE,ID_EDIT_CUT,ID_EDIT_COPY,ID_EDIT_PASTE,ID_FILE_PRINT,ID_VIEW_ZOOM_FITWINDOW, ID_VIEW_ZOOM_TOSELECTION, ID_APP_ABOUT}; 
		GetCommandBars()->GetImageManager()->SetIcons(IDR_MAINFRAME2013_16, uiSystemMenu, _countof(uiSystemMenu), CSize(16, 16));
		GetCommandBars()->GetImageManager()->SetIcons(IDR_MAINFRAME2013_24, uiSystemMenu, _countof(uiSystemMenu), CSize(24, 24));
		GetCommandBars()->GetImageManager()->SetIcons(IDR_MAINFRAME2013_32, uiSystemMenu, _countof(uiSystemMenu), CSize(32, 32));
		GetCommandBars()->GetImageManager()->SetIcons(IDR_MAINFRAME2013_40, uiSystemMenu, _countof(uiSystemMenu), CSize(40, 40));
		GetCommandBars()->GetImageManager()->SetIcons(IDR_MAINFRAME2013_48, uiSystemMenu, _countof(uiSystemMenu), CSize(48, 48));
		GetCommandBars()->GetImageManager()->SetIcons(IDR_MAINFRAME2013_64, uiSystemMenu, _countof(uiSystemMenu), CSize(64, 64));

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
		GetCommandBars()->GetPaintManager()->m_bAutoResizeIcons = TRUE;
		GetCommandBars()->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE, FALSE);
		GetCommandBars()->GetPaintManager()->RefreshMetrics();
		GetCommandBars()->RedrawCommandBars();
		SendMessage(WM_NCPAINT);

		RedrawWindow(0, 0, RDW_ALLCHILDREN|RDW_INVALIDATE);
	}
	else
	{
		GetCommandBars()->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE, TRUE);
		EnableFrameTheme(pCommandBars);
	}

	// Load the previous state for toolbars and menus.
	LoadCommandBars(_T("CommandBars"));

	// Docking pane

	// Initialize the docking pane manager and set the
	// initial them for the docking panes.  Do this only after all
	// control bars objects have been created and docked.
	m_paneManager.InstallDockingPanes(this);
	SetDockingPaneTheme(xtpPaneThemeOffice2013);
	m_paneManager.SetFloatingFrameCaption(_T("Panes"));
	m_paneManager.SetStickyFloatingFrames(TRUE);
	m_paneManager.SetThemedFloatingFrames(TRUE);

	m_paneManager.SetSideDockingMargin(XTP_DPI(CRect(2, 2, 2, 2)));
	m_paneManager.EnableSideDocking();

	m_paneManager.EnableKeyboardNavigate();

	// Create docking panes.
	CXTPDockingPane* pwndPane1 = m_paneManager.CreatePane(
		ID_VIEW_TOOLBOX, XTP_DPI(CRect(0, 0, 220, 120)), xtpPaneDockLeft);

	CXTPDockingPane* pwndPaneProperties = m_paneManager.CreatePane(
		ID_VIEW_PROPERTYGRID, XTP_DPI(CRect(0, 0, 260, 120)), xtpPaneDockRight);

	pwndPane1->SetOptions(xtpPaneNoCaption | xtpPaneNoCloseable | xtpPaneNoHideable | xtpPaneNoFloatable);
	pwndPaneProperties->SetOptions(xtpPaneNoCaption | xtpPaneNoCloseable | xtpPaneNoHideable | xtpPaneNoFloatable);
	
#endif

	return 0;
}

#ifdef _XTP_INCLUDE_TASKPANEL

CXTPTaskPanelGroup* CMainFrame::CreateToolboxGroup(UINT nID, LPCTSTR szGroupCaption)
{
	CXTPTaskPanelGroup* pFolder = m_wndTaskPanel.AddGroup(nID);

	pFolder->SetCaption(szGroupCaption);
	
	return pFolder;
}

CXTPTaskPanelGroupItem* CMainFrame::AddToolboxGroupItem(CXTPTaskPanelGroup* pGroup, UINT nID, UINT nImageID, UINT uResShapeID, const CString sCaption/* = CString()*/ )
{
	CXTPTaskPanelGroupItem *pItem = pGroup->AddLinkItem(nID, nImageID);

	pItem->SetCaption(sCaption);
	pItem->SetItemData(uResShapeID);

	return pItem;
}	

CXTPTaskPanelGroupItem* CMainFrame::AddToolboxGroupItem(CXTPTaskPanelGroup* pGroup, UINT nID, UINT nImageID, const CString sCaption)
{
	CXTPTaskPanelGroupItem *pItem = pGroup->AddLinkItem(nID, nImageID);

	pItem->SetCaption(sCaption);
	
	return pItem;
}

CWnd* CMainFrame::CreateToolBox()
{
	if (!m_wndTaskPanel.GetSafeHwnd() && GetActiveView())
	{
		if (!m_wndTaskPanel.Create(WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN, CRect(0, 0, 0, 0), this, 0))
			return FALSE;

		m_wndTaskPanel.SetOwner(GetActiveView());

		//m_wndTaskPanel.GetImageManager()->SetIcons(IDB_TOOLBOXICONS, 0, 0, CSize(16, 16));
		m_wndTaskPanel.SetBehaviour(xtpTaskPanelBehaviourExplorer);
		m_wndTaskPanel.SetTheme(xtpTaskPanelThemeOffice2013);
		m_wndTaskPanel.SetHotTrackStyle(xtpTaskPanelHighlightItem);
		//m_wndTaskPanel.SetSelectItemOnFocus(TRUE);
		m_wndTaskPanel.SetSingleSelection();
		m_wndTaskPanel.AllowDrag(xtpTaskItemAllowDragCopyOutsideControl);

		CXTPTaskPanelGroup* pGroupShapes = CreateToolboxGroup(TOOLBOX_GROUP_SHAPES, _T("Main FlowGraph Shapes") );

		AddToolboxGroupItem(pGroupShapes, FG_SHAPE_TABLE, (UINT)-1, _T("Table (default node)"));
		AddToolboxGroupItem(pGroupShapes, FG_SHAPE_PICTURE, (UINT)-1, _T("Picture"));
		AddToolboxGroupItem(pGroupShapes, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_DOCUMENT, _T("Document"));
		AddToolboxGroupItem(pGroupShapes, FG_SHAPE_USERCARD, (UINT)-1, _T("User Card"));

		CXTPTaskPanelGroup* pGroupGeometric = CreateToolboxGroup(TOOLBOX_GROUP_GEO_FIGURES, _T("Geometric Figures") );

		AddToolboxGroupItem(pGroupGeometric, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_RECTANGLE, _T("Rectangle"));
		AddToolboxGroupItem(pGroupGeometric, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_RECTANGLE_ROUNDED, _T("Rounded rectangle"));
		AddToolboxGroupItem(pGroupGeometric, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_PENTAGON, _T("Pentagon"));
		AddToolboxGroupItem(pGroupGeometric, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_HEXAGON, _T("Hexagon"));
		AddToolboxGroupItem(pGroupGeometric, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_RHOMBUS, _T("Rhombus"));
		AddToolboxGroupItem(pGroupGeometric, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_PARALLELOGRAM, _T("Parallelogram"));
		AddToolboxGroupItem(pGroupGeometric, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_TRAPEZOID, _T("Trapezoid"));
		AddToolboxGroupItem(pGroupGeometric, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_ELLIPSE, _T("Ellipse"));
		AddToolboxGroupItem(pGroupGeometric, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_TRIANGLE, _T("Triangle"));
		AddToolboxGroupItem(pGroupGeometric, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_TRIANGLE_RIGHT, _T("Triangle right"));

		CXTPTaskPanelGroup* pGroupOther = CreateToolboxGroup(TOOLBOX_GROUP_OTHER, _T("Other Shapes") );

		AddToolboxGroupItem(pGroupOther, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_CALLOUT_ELLIPSE, _T("Callout ellipse"));
		AddToolboxGroupItem(pGroupOther, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_CALLOUT_RECTANGLE, _T("Callout rectangle"));
		AddToolboxGroupItem(pGroupOther, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_CALLOUT_RECTANGLE_ROUNDED, _T("Callout rectangle rounded"));
		AddToolboxGroupItem(pGroupOther, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_STAR, _T("Star"));
		AddToolboxGroupItem(pGroupOther, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_CROSS, _T("Cross"));
		AddToolboxGroupItem(pGroupOther, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_CHEVRON, _T("Chevron"));	
		AddToolboxGroupItem(pGroupOther, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_FLAG, _T("Flag"));
		AddToolboxGroupItem(pGroupOther, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_RING, _T("Ring"));
		AddToolboxGroupItem(pGroupOther, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_RING_HALF, _T("Ring half"));
		AddToolboxGroupItem(pGroupOther, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_CLOUD, _T("Cloud"));
		AddToolboxGroupItem(pGroupOther, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_MOON, _T("Moon"));
		AddToolboxGroupItem(pGroupOther, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_LIGHTNING, _T("Lightning"));
		AddToolboxGroupItem(pGroupOther, FG_SHAPE_CUSTOM, (UINT)-1, _T("Custom XAML shape"));

		CXTPTaskPanelGroup* pGroupArrows = CreateToolboxGroup(TOOLBOX_GROUP_ARROWS, _T("Arrows Shapes") );

		AddToolboxGroupItem(pGroupArrows, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_ARROW, _T("Arrow"));
		AddToolboxGroupItem(pGroupArrows, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_ARROW_DOWN, _T("Arrow down"));
		AddToolboxGroupItem(pGroupArrows, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_ARROW_UP, _T("Arrow up"));
		AddToolboxGroupItem(pGroupArrows, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_ARROW_LEFT, _T("Arrow left"));
		AddToolboxGroupItem(pGroupArrows, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_ARROW_RIGHT, _T("Arrow right"));
		AddToolboxGroupItem(pGroupArrows, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_ARROW_LEFTRIGHT, _T("Arrow leftright"));
		AddToolboxGroupItem(pGroupArrows, FG_SHAPE_FROM_RESOURCE, (UINT)-1, XTP_FLOWGRAPH_SHAPE_ARROW_UPDOWN, _T("Arrow updown"));

		CXTPTaskPanelGroup* pGroupConnections = CreateToolboxGroup(TOOLBOX_GROUP_CONNECTIONS, _T("Set connections style to:") );

		AddToolboxGroupItem(pGroupConnections, xtpFlowGraphConnectorStraight, (UINT)-1, _T("Straight") );
		AddToolboxGroupItem(pGroupConnections, xtpFlowGraphConnectorStraightArrow, (UINT)-1, _T("Straight with arrow") );
		AddToolboxGroupItem(pGroupConnections, xtpFlowGraphConnectorStraightDoubleArrow, (UINT)-1, _T("Straight with double arrow") );
		AddToolboxGroupItem(pGroupConnections, xtpFlowGraphConnectorCurved, (UINT)-1, _T("Curved") );
		AddToolboxGroupItem(pGroupConnections, xtpFlowGraphConnectorCurvedArrow, (UINT)-1, _T("Curved with arrow") );
		AddToolboxGroupItem(pGroupConnections, xtpFlowGraphConnectorCurvedDoubleArrow, (UINT)-1, _T("Curved with double arrow") );
		AddToolboxGroupItem(pGroupConnections, xtpFlowGraphConnectorElbow, (UINT)-1, _T("Elbow") );
		AddToolboxGroupItem(pGroupConnections, xtpFlowGraphConnectorElbowArrow, (UINT)-1, _T("Elbow with arrow") );
		AddToolboxGroupItem(pGroupConnections, xtpFlowGraphConnectorElbowDoubleArrow, (UINT)-1, _T("Elbow with double arrow") );

		pGroupShapes->SetExpanded(TRUE);
		pGroupArrows->SetExpanded(FALSE);
		pGroupOther->SetExpanded(FALSE);
	}

	return &m_wndTaskPanel;
}

#endif _XTP_EXCLUDE_TASKPANEL

#ifdef _XTP_INCLUDE_PROPERTYGRID

CWnd* CMainFrame::CreateGrid()
{
	if (!m_wndPropertyGrid.GetSafeHwnd() && GetActiveView())
	{
		if (!m_wndPropertyGrid.Create(CRect(0, 0, 0, 0), this, 0))
			return FALSE;

		m_wndPropertyGrid.SetTheme(xtpGridThemeOffice2013);
		m_wndPropertyGrid.SetOwner(GetActiveView());

		CXTPPropertyGridItem *pGroupDefault = m_wndPropertyGrid.AddCategory( _T("Nothing's selected") );
		
		m_wndPropertyGrid.SendNotifyMessage(XTP_PGN_USER, reinterpret_cast<LPARAM>(&m_wndPropertyGrid));
	}

	return &m_wndPropertyGrid;
}

#endif // _XTP_EXCLUDE_PROPERTYGRID

#ifdef _XTP_INCLUDE_DOCKINGPANE

void CMainFrame::SetDockingPaneTheme(XTPDockingPanePaintTheme theme)
{
	m_paneManager.SetClientMargin(theme == xtpPaneThemeOffice2013 ? 3 : 0);
	m_paneManager.SetTheme(theme);
}

LRESULT CMainFrame::OnDockingPaneNotify(WPARAM wParam, LPARAM lParam)
{
	if (wParam == XTP_DPN_SHOWWINDOW)
	{
		CXTPDockingPane* pPane = (CXTPDockingPane*)lParam;

		if (!pPane->IsValid())
		{
			switch (pPane->GetID())
			{
				case ID_VIEW_TOOLBOX:
				{
					pPane->Attach(CreateToolBox());

					break;
				}
				case ID_VIEW_PROPERTYGRID:
				{
					pPane->Attach(CreateGrid());

					break;
				}
			}
		}
		return TRUE;
	}

	return FALSE;
}

#endif

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

	cs.lpszClass = _T("XTPMainFrame");

#ifdef _XTP_INCLUDE_COMMANDBARS
	CXTPDrawHelpers::RegisterWndClass(AfxGetInstanceHandle(), cs.lpszClass, 
		CS_DBLCLKS, AfxGetApp()->LoadIcon(IDR_MAINFRAME));
#else
	CXTPDrawHelpers::RegisterWndClass(AfxGetInstanceHandle(), cs.lpszClass,
		CS_DBLCLKS, AfxGetApp()->LoadIcon(IDR_MAINFRAME_SIMPLE));
#endif

#ifndef _XTP_INCLUDE_PROPERTYGRID
	cs.cx = min(GetSystemMetrics(SM_CXSCREEN) - XTP_DPI_X(300), XTP_DPI_X(1000));
	cs.cy = min(GetSystemMetrics(SM_CYSCREEN) - XTP_DPI_Y(300), XTP_DPI_Y(700));
#endif

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


void CMainFrame::OnTestGraphwith500nodes()
{
	CDialogPerfomanceTest cd;
	cd.DoModal();
}

void CMainFrame::OnTestNodeswithcontrols()
{
	CDialogControlsTest cd;
	cd.DoModal();

}

void CMainFrame::OnTestPagetransition()
{
	CDialogPageTransitionTest cd;
	cd.DoModal();
}

void CMainFrame::OnUpdateContextTests(CCmdUI *pCmdUi)
{
	pCmdUi->Enable(TRUE);
}

#ifdef _XTP_INCLUDE_COMMANDBARS

void CMainFrame::OnInitCommandsPopup(CXTPPopupBar* pComandBar)
{
	CXTPMenuBar *pMenuBar = NULL;
	CXTPCommandBars* pCommandBars = GetCommandBars();

	if (pCommandBars)
	{
		pMenuBar = pCommandBars->GetMenuBar();
	}

	if (pComandBar)
	{
		UINT barID = pComandBar->GetBarID();

		switch (barID)
		{
			case ID_TESTS_TOOLBAR_BUTTON_POPUP_ID:
			{
				pComandBar->GetControls()->RemoveAll();

				#define MENU_FLOWGRAPH 3

				if (pMenuBar && pMenuBar->GetControls() && pMenuBar->GetControls()->GetAt(MENU_FLOWGRAPH))
				{
					// be aware of potentially dangerous code below 
					CXTPCommandBar *pCommandBar = pMenuBar->GetControls()->GetAt(MENU_FLOWGRAPH)->GetCommandBar()->GetControls()->GetAt(0)->GetCommandBar();

					if (pCommandBar)
					{
						CXTPControls *pControlsHelp = pCommandBar->GetControls();

						if (pControlsHelp)
						{
							for (int i=0; i<pControlsHelp->GetCount(); i++)
							{
								pComandBar->GetControls()->AddClone(pControlsHelp->GetAt(i));
							}
						}
					}
				}

				break;
			}
		}
	}
}

void CMainFrame::OnGraphChanged_Update(CCmdUI *pUi)
{
	pUi->Enable(TRUE);
}

void CMainFrame::OnGraphChanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CXTPControlComboBox* pControl = (CXTPControlComboBox*)tagNMCONTROL->pControl;
	ASSERT(pControl->GetType() == xtpControlComboBox);
	if (pControl->GetType() != xtpControlComboBox)
	{
		ASSERT(FALSE);
		return;
	}
	int nCurSel = pControl->GetCurSel();
	if (nCurSel < 0 || nCurSel >= pControl->GetCount())
	{
		ASSERT(FALSE);
		return;
	}

	((CFlowGraphSampleView *)GetActiveView())->SwitchGraph(nCurSel);

	if (pResult)
		*pResult = 0;
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

#endif
