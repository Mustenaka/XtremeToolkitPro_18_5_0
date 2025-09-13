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
#include "CaptionBar.h"

#include "MainFrm.h"
#include "TreeViewEx.h"
#include "ListViewEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef AFX_ID_VIEW_MINIMUM // VC5
#define AFX_ID_VIEW_MINIMUM              0xE810
#define AFX_ID_VIEW_MAXIMUM              0xE815
#endif


/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_THEME_DEFAULT, OnViewThemeDefault)
	ON_UPDATE_COMMAND_UI(ID_VIEW_THEME_DEFAULT, OnUpdateViewThemeDefault)
	ON_COMMAND(ID_VIEW_THEME_OFFICEXP, OnViewThemeOfficeXP)
	ON_UPDATE_COMMAND_UI(ID_VIEW_THEME_OFFICEXP, OnUpdateViewThemeOfficeXP)
	ON_COMMAND(ID_VIEW_THEME_OFFICE2003, OnViewThemeOffice2003)
	ON_UPDATE_COMMAND_UI(ID_VIEW_THEME_OFFICE2003, OnUpdateViewThemeOffice2003)
	//}}AFX_MSG_MAP
#ifdef _XTP_INCLUDE_COMMANDBARS
	ON_WM_CLOSE()
	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
#endif
	ON_UPDATE_COMMAND_UI_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnUpdateViewStyles)
	ON_COMMAND_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnViewStyle)
	ON_MESSAGE_VOID(CPN_XTP_PUSHPINBUTTON, OnPushPinButton)
	ON_MESSAGE_VOID(CPN_XTP_PUSHPINCANCEL, OnPushPinCancel)
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
	// TODO: add member initialization code here
	m_nColumn      = 1;
	m_pwndTreeCtrl = NULL;
	m_pListView    = NULL;
	m_pTreeView    = NULL;
	
	// initialize themes.
	m_eTheme = (XTPControlTheme)m_regMgr.GetProfileInt(
		_T("Settings"), _T("Theme"), xtpControlThemeOfficeXP);
}

CMainFrame::~CMainFrame()
{
	m_regMgr.WriteProfileInt(
		_T("Settings"), _T("Theme"), m_eTheme);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMainFrameBase::OnCreate(lpCreateStruct) == -1)
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
	if(pCommandBars == NULL)
	{
		TRACE0("Failed to create command bars object.\n");
		return -1;      // fail to create
	}

	pCommandBars->SetMenu(_T("Menu Bar"), IDR_MAINFRAME);

	CXTPToolBar* pCommandBar = (CXTPToolBar*)pCommandBars->Add(_T("Standard"), xtpBarTop);
	if (!pCommandBar ||
		!pCommandBar->LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	GetCommandBars()->GetPaintManager()->m_bAutoResizeIcons = TRUE;
	GetCommandBars()->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE);

	// Load the previous state for command bars.
	LoadCommandBars(_T("CommandBars"));
#else

#ifdef _XTP_INCLUDE_CONTROLBARS
	if (!m_wndMenuBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndMenuBar.LoadMenuBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
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

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetWindowText(_T("Address Bar"));
	m_wndToolBar.ModifyStyle(0, TBSTYLE_FLAT);
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
#endif

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
#ifdef _XTP_INCLUDE_CONTROLBARS
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
#endif
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
#ifdef _XTP_INCLUDE_CONTROLBARS
	DockControlBar(&m_wndMenuBar);
#endif
	DockControlBar(&m_wndToolBar);
#ifdef _XTP_INCLUDE_CONTROLBARS

	// TODO: Remove this line if you don't want cool menus.
	InstallCoolMenus(IDR_MAINFRAME);
#endif
#endif

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	// Create the splitter window with two rows
	if (!m_wndSplitter.CreateStatic(this, 2, 1))
	{
		TRACE0("Failed to create splitter window\n");
		return FALSE;
	}

	if (!m_wndCaption.Create(&m_wndSplitter, _T("Caption Text"), CPWS_EX_RAISED_EDGE,
		WS_VISIBLE|SS_CENTER|SS_CENTERIMAGE, CRect(0,0,0,0), m_wndSplitter.IdFromRowCol(0, 0)))
	{
		TRACE0("Failed to caption window.\n");
		return -1;
	}

	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_wndCaption.SetCaptionColors(
		GetXtremeColor(COLOR_3DFACE),    // border color.
		GetXtremeColor(COLOR_3DSHADOW),  // background color.
		GetXtremeColor(COLOR_WINDOW) );  // font color.

	m_wndCaption.ModifyCaptionStyle(
		4,       // border size in pixels.
		&XTPAuxData().xtpFontBold,   // caption font.
		NULL,    // caption text.
		hIcon);  // caption icon.

	// add the third splitter pane - which is a nested splitter with 2 rows
	if (!m_wndSplitter2.CreateStatic(&m_wndSplitter,    // our parent window is the first splitter
		1, 2,                                           // the new splitter is 2 rows, 1 column
		WS_CHILD | WS_VISIBLE | WS_BORDER,              // style, WS_BORDER is needed
		m_wndSplitter.IdFromRowCol(1, 0)))              // new splitter is in the first row, 3rd column of first splitter
	{
		TRACE0("Failed to create nested splitter\n");
		return FALSE;
	}

	if (!m_wndSplitter2.CreateView(0, 0, RUNTIME_CLASS(CTreeViewEx), XTP_DPI(CSize(200, 100)), pContext) ||
		!m_wndSplitter2.CreateView(0, 1, RUNTIME_CLASS(CListViewEx), XTP_DPI(CSize(100, 100)), pContext))
	{
		m_wndSplitter2.DestroyWindow();
		return FALSE;
	}

	m_wndSplitter.SetRowInfo (0, XTP_DPI_Y(28), 0);

	m_pTreeView = (CTreeViewEx*)m_wndSplitter2.GetPane(0,0);
	m_pListView = (CListViewEx*)m_wndSplitter2.GetPane(0,1);

	// Initialize m_pwndTreeCtrl to point to the tree control in CTreeViewEx
	m_pwndTreeCtrl = &m_pTreeView->m_wndTreeCtrl;

	SetTheme(m_eTheme);

	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMainFrameBase::PreCreateWindow(cs) )
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
	CMainFrameBase::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMainFrameBase::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

CListViewEx* CMainFrame::GetRightPane()
{
	ASSERT_VALID(m_pListView); return m_pListView;
}

CTreeViewEx* CMainFrame::GetLeftPane()
{
	ASSERT_VALID(m_pTreeView); return m_pTreeView;
}

void CMainFrame::OnUpdateViewStyles(CCmdUI* pCmdUI)
{
	// TODO: customize or extend this code to handle choices on the
	// View menu.

	CListViewEx* pView = GetRightPane();

	// if the right-hand pane hasn't been created or isn't a view,
	// disable commands in our range

	if (pView == NULL)
		pCmdUI->Enable(FALSE);
	else
	{
		DWORD dwStyle = pView->GetStyle() & LVS_TYPEMASK;

		// if the command is ID_VIEW_LINEUP, only enable command
		// when we're in LVS_ICON or LVS_SMALLICON mode

		if (pCmdUI->m_nID == ID_VIEW_LINEUP)
		{
			if (dwStyle == LVS_ICON || dwStyle == LVS_SMALLICON)
				pCmdUI->Enable();
			else
				pCmdUI->Enable(FALSE);
		}
		else
		{
			// otherwise, use dots to reflect the style of the view
			pCmdUI->Enable();
			BOOL bChecked = FALSE;

			switch (pCmdUI->m_nID)
			{
			case ID_VIEW_DETAILS:
				bChecked = (dwStyle == LVS_REPORT);
				break;

			case ID_VIEW_SMALLICON:
				bChecked = (dwStyle == LVS_SMALLICON);
				break;

			case ID_VIEW_LARGEICON:
				bChecked = (dwStyle == LVS_ICON);
				break;

			case ID_VIEW_LIST:
				bChecked = (dwStyle == LVS_LIST);
				break;

			default:
				bChecked = FALSE;
				break;
			}

			pCmdUI->SetRadio(bChecked ? 1 : 0);
		}
	}
}


void CMainFrame::OnViewStyle(UINT nCommandID)
{
	// TODO: customize or extend this code to handle choices on the
	// View menu.
	CListViewEx* pView = GetRightPane();

	// if the right-hand pane has been created and is a CListViewEx,
	// process the menu commands...
	if (pView != NULL)
	{
		DWORD dwStyle = (DWORD)-1;

		switch (nCommandID)
		{
		case ID_VIEW_LINEUP:
			{
				// ask the list control to snap to grid
				CListCtrl& refListCtrl = pView->GetListCtrl();
				refListCtrl.Arrange(LVA_SNAPTOGRID);
			}
			break;

		// other commands change the style on the list control
		case ID_VIEW_DETAILS:
			dwStyle = LVS_REPORT;
			break;

		case ID_VIEW_SMALLICON:
			dwStyle = LVS_SMALLICON;
			break;

		case ID_VIEW_LARGEICON:
			dwStyle = LVS_ICON;
			break;

		case ID_VIEW_LIST:
			dwStyle = LVS_LIST;
			break;
		}

		// change the style; window will repaint automatically
		if (dwStyle != -1)
			pView->ModifyStyle(LVS_TYPEMASK, dwStyle);
	}
}

void CMainFrame::CloseTreeViewPane()
{
	ASSERT_VALID(this);
	m_wndCaption.SetChildWindow(m_pwndTreeCtrl, this);
	m_wndSplitter2.HideColumn(0);
	m_nColumn = 0;
}

void CMainFrame::OnPushPinButton()
{
	m_wndSplitter2.ShowColumn();
	m_nColumn = 1;
}

void CMainFrame::OnPushPinCancel()
{
	// TODO: Add your message handler code here and/or call default

}

void CMainFrame::UpdateButtonStyle(CXTPCaptionButton& btnCaption)
{
	UNREFERENCED_PARAMETER(btnCaption);
}

#ifdef _XTP_INCLUDE_COMMANDBARS
void CMainFrame::OnClose()
{
	// Save the current state for command bars.
	SaveCommandBars(_T("CommandBars"));
	CMainFrameBase::OnClose();
}

void CMainFrame::OnCustomize()
{
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
}
#endif

void CMainFrame::SetTheme(XTPControlTheme eTheme)
{
	m_eTheme = eTheme;

#ifdef _XTP_INCLUDE_COMMANDBARS
	switch (eTheme)
	{
	case xtpControlThemeOffice2000: XTPPaintManager()->SetTheme(xtpThemeOffice2000); break;
	case xtpControlThemeOfficeXP:   XTPPaintManager()->SetTheme(xtpThemeOfficeXP);   break;
	case xtpControlThemeOffice2003: XTPPaintManager()->SetTheme(xtpThemeOffice2003); break;
	}
#endif

	CXTPControlTheme::SetTheme(m_hWnd, m_eTheme);

	if (m_eTheme == xtpControlThemeOfficeXP)
		m_wndSplitter.SetSplitterStyle(XTP_SPLIT_NOSIZE|XTP_SPLIT_NOBORDER);
	else
		m_wndSplitter.SetSplitterStyle(XTP_SPLIT_NOSIZE);

#ifdef _XTP_INCLUDE_COMMANDBARS
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if (NULL != pCommandBars)
	{
		pCommandBars->GetPaintManager()->m_bAutoResizeIcons = TRUE;
		pCommandBars->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE);
	}
#endif

	RedrawWindow( NULL, NULL,
		RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_ALLCHILDREN );

	RecalcLayout();
}

void CMainFrame::OnViewThemeDefault() 
{
	SetTheme(xtpControlThemeOffice2000);
}

void CMainFrame::OnUpdateViewThemeDefault(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_eTheme == xtpControlThemeOffice2000);
}

void CMainFrame::OnViewThemeOfficeXP() 
{
	SetTheme(xtpControlThemeOfficeXP);
}

void CMainFrame::OnUpdateViewThemeOfficeXP(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_eTheme == xtpControlThemeOfficeXP);
}

void CMainFrame::OnViewThemeOffice2003() 
{
	SetTheme(xtpControlThemeOffice2003);
}

void CMainFrame::OnUpdateViewThemeOffice2003(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_eTheme == xtpControlThemeOffice2003);
}
