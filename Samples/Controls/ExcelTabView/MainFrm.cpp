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
#include "ExcelTab.h"

#include "MainFrm.h"

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
	ON_COMMAND(ID_VIEW_THEME_OFFICEXP, OnViewThemeOfficeXP)
	ON_UPDATE_COMMAND_UI(ID_VIEW_THEME_OFFICEXP, OnUpdateViewThemeOfficeXP)
	ON_COMMAND(ID_VIEW_DEFAULTTHEME, OnViewDefaultTheme)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DEFAULTTHEME, OnUpdateViewDefaultTheme)
	ON_COMMAND(ID_VIEW_OFFICE2013THEME, OnViewOffice2013Theme)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OFFICE2013THEME, OnUpdateViewOffice2013Theme)
	ON_COMMAND(ID_VIEW_OFFICE2016THEME, OnViewOffice2016Theme)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OFFICE2016THEME, OnUpdateViewOffice2016Theme)
	//}}AFX_MSG_MAP
#ifdef _XTP_INCLUDE_COMMANDBARS
	ON_WM_CLOSE()
	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
	ON_XTP_CREATECONTROL()
#endif
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
	
	// initialize themes.
	m_iTheme = m_regMgr.GetProfileInt(
		_T("Settings"), _T("Theme"), themeOffice2016);
}

CMainFrame::~CMainFrame()
{
	m_regMgr.WriteProfileInt(
		_T("Settings"), _T("Theme"), m_iTheme);
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

	pCommandBars->GetPaintManager()->m_bAutoResizeIcons = TRUE;
	pCommandBars->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE);
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
	SetTheme(m_iTheme);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMainFrameBase::PreCreateWindow(cs) )
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
	CMainFrameBase::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMainFrameBase::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

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
	if (lpCreateControl->nID == ID_EXCELTAB_PROPERTIES)
	{
		lpCreateControl->buttonStyle = xtpButtonIconAndCaption;
		return TRUE;
	}

	return FALSE;
}
#endif

void CMainFrame::SetTheme(int iTheme)
{
#ifdef _XTP_INCLUDE_COMMANDBARS	
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if (!pCommandBars)
		return;
#endif

	m_iTheme = iTheme;

	CString strINI;
	XTPControlTheme ctrlTheme;
#ifdef _XTP_INCLUDE_COMMANDBARS
	XTPPaintTheme cbarsTheme;
#endif

	switch (m_iTheme)
	{
	default:
		{
			ctrlTheme = xtpControlThemeOffice2000;
#ifdef _XTP_INCLUDE_COMMANDBARS
			cbarsTheme = xtpThemeNativeWinXP;
#endif
		}
		break;
	case themeOfficeXP:
		{
			ctrlTheme = xtpControlThemeOfficeXP;
#ifdef _XTP_INCLUDE_COMMANDBARS
			cbarsTheme = xtpThemeOfficeXP;
#endif
		}
		break;
	case themeOffice2013:
		{
			strINI = xtpIniOffice2013Word;
			ctrlTheme = xtpControlThemeOffice2013;
#ifdef _XTP_INCLUDE_COMMANDBARS
			cbarsTheme = xtpThemeOffice2013;
#endif
		}
		break;
	case themeOffice2016:
		{
			strINI = xtpIniOffice2016WordColorful;
			ctrlTheme = xtpControlThemeOffice2013;
#ifdef _XTP_INCLUDE_COMMANDBARS
			cbarsTheme = xtpThemeOffice2013;
#endif
		}
		break;
	}

	// load the resource DLL.
	if (!strINI.IsEmpty())
	{
		XTPThemeDLL()->SetHandle(strINI);
	}

	// notify children theme changed.
	SendMessageToDescendants(WM_XTP_SETCONTROLTHEME, ctrlTheme);

#ifdef _XTP_INCLUDE_COMMANDBARS
	pCommandBars->SetAllCaps(m_iTheme == themeOffice2013);
	pCommandBars->GetPaintManager()->RefreshMetrics();
	XTPPaintManager()->SetTheme(cbarsTheme);
	CXTPCommandBarsFrameHook::m_bAllowDwm = (XTPSystemVersion()->IsWin10OrGreater()? FALSE: (!CXTPWinDwmWrapper().IsCompositionEnabled() && m_iTheme >= themeOffice2013));
	pCommandBars->EnableFrameTheme(m_iTheme >= themeOffice2013);
	pCommandBars->GetPaintManager()->m_bAutoResizeIcons = TRUE;
	pCommandBars->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE);
	pCommandBars->RedrawCommandBars();
#endif

	RedrawWindow( NULL, NULL,
		RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_ALLCHILDREN );

	RecalcLayout();
}

void CMainFrame::OnViewDefaultTheme() 
{
	SetTheme(themeDefault);
}

void CMainFrame::OnUpdateViewDefaultTheme(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_iTheme == themeDefault);
}

void CMainFrame::OnViewThemeOfficeXP() 
{
	SetTheme(themeOfficeXP);
}

void CMainFrame::OnUpdateViewThemeOfficeXP(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_iTheme == themeOfficeXP);
}

void CMainFrame::OnViewOffice2013Theme() 
{
	SetTheme(themeOffice2013);
}

void CMainFrame::OnUpdateViewOffice2013Theme(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_iTheme == themeOffice2013);
}

void CMainFrame::OnViewOffice2016Theme() 
{
	SetTheme(themeOffice2016);
}

void CMainFrame::OnUpdateViewOffice2016Theme(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_iTheme == themeOffice2016);
}
