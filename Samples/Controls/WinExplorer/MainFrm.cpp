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
#include "WinExplorer.h"

#include "MainFrm.h"
#include "ShellTreeView.h"
#include "ShellListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef AFX_ID_VIEW_MINIMUM
#define AFX_ID_VIEW_MINIMUM              ID_VIEW_SMALLICON
#endif

#ifndef AFX_ID_VIEW_MAXIMUM
#define AFX_ID_VIEW_MAXIMUM              ID_VIEW_BYNAME
#endif
 
BOOL CAddressComboBox::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		GetOwner()->SendMessage(WM_COMMAND, IDOK);
	}

	return CComboBoxEx::PreTranslateMessage(pMsg);
}



/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEWS, OnViews)
	ON_COMMAND(ID_VIEW_FOLDERS, OnFolders)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FOLDERS, OnUpdateFolders)
	ON_COMMAND(ID_VIEW_THEME_OFFICEXP, OnViewThemeOfficeXP)
	ON_UPDATE_COMMAND_UI(ID_VIEW_THEME_OFFICEXP, OnUpdateViewThemeOfficeXP)
	//}}AFX_MSG_MAP
#ifdef _XTP_INCLUDE_COMMANDBARS
	ON_XTP_CREATECONTROL()
	ON_WM_CLOSE()
	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
#endif
	ON_COMMAND_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnViewStyle)
	ON_UPDATE_COMMAND_UI_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnUpdateViewStyles)
	ON_COMMAND(IDOK, OnAddressBarEnter)
	ON_CBN_SELENDOK(IDC_ADDRESSBAR, OnSelEndOkAddressBar)
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
	m_pTreeView    = NULL;
	m_pListView    = NULL;
	
	// initialize themes.
	m_bOfficeTheme = m_regMgr.GetProfileInt(
		_T("Settings"), _T("OfficeTheme"), FALSE);
}

CMainFrame::~CMainFrame()
{
	m_regMgr.WriteProfileInt(
		_T("Settings"), _T("OfficeTheme"), m_bOfficeTheme);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	

	CRect rCombo(0,0,400,250);
	if (!m_wndAddressCombo.Create( WS_CHILD|WS_VISIBLE|CBS_DROPDOWN|WS_CLIPCHILDREN,
		rCombo, this, IDC_ADDRESSBAR ))
	{
		TRACE(_T("Failed to create combo-box\n"));
		return FALSE;      // fail to create
	}
	
	m_wndAddressCombo.SetOwner(this);


	m_pTreeView = (CShellTreeView*)m_wndSplitter.GetPane(0,0);
	m_pListView = (CShellListView*)m_wndSplitter.GetPane(0,1);
	
	m_pTreeView->SetListView(m_pListView);
	m_pTreeView->SetWindowPos(0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
	
	m_pTreeView->AssociateCombo(&m_wndAddressCombo);


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

	// Load the previous state for command bars.
	LoadCommandBars(_T("CommandBars"));
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

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	InitAddressBar();

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

#endif

	UpdateTheme();

	

	return 0;
}

#ifndef _XTP_INCLUDE_COMMANDBARS
void CMainFrame::InitAddressBar()
{
	CRect rCombo;
	int nIndex = m_wndToolBar.GetToolBarCtrl().CommandToIndex(IDC_ADDRESSBAR);
	m_wndToolBar.SetButtonInfo(nIndex, IDC_ADDRESSBAR, TBBS_SEPARATOR, 400);
	m_wndToolBar.GetToolBarCtrl().GetItemRect(nIndex, &rCombo);

	rCombo.top = 1;
	rCombo.bottom = rCombo.top + 250 /*drop height*/;

	m_wndAddressCombo.SetParent(&m_wndToolBar);
	m_wndAddressCombo.MoveWindow(rCombo);
	
	m_wndAddressCombo.SetOwner(this);
}
#endif

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.lpszClass = _T("XTPMainFrame");
	CXTPDrawHelpers::RegisterWndClass(AfxGetInstanceHandle(), cs.lpszClass, 
		CS_DBLCLKS, AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	cs.style &= ~FWS_ADDTOTITLE;

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

void CMainFrame::OnUpdateViewStyles(CCmdUI* pCmdUI)
{
	// TODO: customize or extend this code to handle choices on the
	// View menu.

	// if the right-hand pane hasn't been created or isn't a view,
	// disable commands in our range

	CListCtrl* pListCtrl = &m_pListView->GetListCtrl();

	if (pListCtrl == NULL)
		pCmdUI->Enable(FALSE);
	else
	{
		DWORD dwStyle = pListCtrl->GetStyle() & LVS_TYPEMASK;

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

	CListCtrl* pListCtrl = &m_pListView->GetListCtrl();

	// if the right-hand pane has been created and is a CGUI_ExplorerView,
	// process the menu commands...
	if (pListCtrl != NULL)
	{
		DWORD dwStyle = (DWORD)-1;

		switch (nCommandID)
		{
		case ID_VIEW_LINEUP:
			{
				// ask the list control to snap to grid
				pListCtrl->Arrange(LVA_SNAPTOGRID);
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
		if (dwStyle != (DWORD)-1)
			pListCtrl->ModifyStyle(LVS_TYPEMASK, dwStyle);
	}
}

void CMainFrame::OnViews() 
{
	CListCtrl* pListCtrl = &m_pListView->GetListCtrl();
	DWORD dwStyle =pListCtrl->GetStyle();
	
	switch (dwStyle & (LVS_REPORT | LVS_SMALLICON | LVS_ICON | LVS_LIST))
	{
	case LVS_ICON:      OnViewStyle( ID_VIEW_SMALLICON ); break;
	case LVS_SMALLICON: OnViewStyle( ID_VIEW_LIST );      break;
	case LVS_LIST:      OnViewStyle( ID_VIEW_DETAILS );   break;
	case LVS_REPORT:    OnViewStyle( ID_VIEW_LARGEICON ); break;
	}
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext) 
{
	// create splitter window
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CShellTreeView),
		CSize(250, 100), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}
	
	if (!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CShellListView),
		CSize(100, 100), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}

	m_wndSplitter.ShowTopBorder(false, 3);
	m_wndSplitter.SetSplitterStyle(XTP_SPLIT_DOTTRACKER|XTP_SPLIT_NOBORDER);

	return TRUE;
}


void CMainFrame::OnAddressBarEnter()
{
	CString strNewPath;
	m_wndAddressCombo.GetWindowText(strNewPath);

	if (strNewPath.GetLength())
	{
		m_pTreeView->TunnelTree(strNewPath);
	}
}

void CMainFrame::OnSelEndOkAddressBar()
{
	if (m_pTreeView != NULL)
	{
		HTREEITEM hItem = (HTREEITEM)m_wndAddressCombo.GetItemData(
			m_wndAddressCombo.GetCurSel());

		if (hItem != NULL) {
			m_pTreeView->SelectItem(hItem);
		}
	}
}

void CMainFrame::OnFolders()
{
	if (m_wndSplitter.GetColumnCount() == 1)
	{
		m_wndSplitter.ShowColumn();
	}
	else
	{
		m_wndSplitter.HideColumn(0);
	}
}

void CMainFrame::OnUpdateFolders(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndSplitter.GetPane(0,0)->IsKindOf(
		RUNTIME_CLASS(CShellTreeView)));
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

int CMainFrame::OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl)
{
	if (lpCreateControl->nID == IDC_ADDRESSBAR)
	{

		CXTPControlCustom* pAddressCombo = CXTPControlCustom::CreateControlCustom(&m_wndAddressCombo);
		pAddressCombo->SetFlags(xtpFlagManualUpdate);

		lpCreateControl->pControl = pAddressCombo;
		return TRUE;
	}

	return FALSE;
}
#endif

void CMainFrame::UpdateTheme()
{
#ifdef _XTP_INCLUDE_COMMANDBARS
	XTPPaintManager()->SetTheme(m_bOfficeTheme?
		xtpThemeOfficeXP: xtpThemeNativeWinXP);
	GetCommandBars()->GetPaintManager()->m_bAutoResizeIcons = TRUE;
	GetCommandBars()->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE);
	GetCommandBars()->RedrawCommandBars();
	
#endif
	RedrawWindow( NULL, NULL,
		RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_ALLCHILDREN );

	RecalcLayout();
}

void CMainFrame::OnViewThemeOfficeXP() 
{
	m_bOfficeTheme = !m_bOfficeTheme;
	UpdateTheme();
}

void CMainFrame::OnUpdateViewThemeOfficeXP(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bOfficeTheme);
}
