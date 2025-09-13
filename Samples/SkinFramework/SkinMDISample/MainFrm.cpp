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
#include "SkinMDISample.h"

#include "SkinPropertySheet.h"
#include "MainFrm.h"
#include "DialogsView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_VIEW_THEME_DIALOG, OnViewThemeDialog)
	ON_COMMAND(ID_VIEW_THEME, OnViewTheme)
	ON_UPDATE_COMMAND_UI(ID_VIEW_THEME, OnUpdateViewTheme)
	//}}AFX_MSG_MAP
#ifdef _XTP_INCLUDE_COMMANDBARS
	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
	ON_XTP_CREATECONTROL()
#endif
	ON_COMMAND_RANGE(ID_THEME_OFFICE2000, ID_THEME_WINXP, OnViewThemePopup)
	ON_UPDATE_COMMAND_UI_RANGE(ID_THEME_OFFICE2000, ID_THEME_WINXP, OnUpdateViewTheme)
	
#ifdef _XTP_INCLUDE_DOCKINGPANE
	ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify) 
#endif
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

CString CMainFrame::GetStylesPath()
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

	return csStylesPath + _T("\\Styles\\");
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	OnSchemaChanged(0);
}

CMainFrame::~CMainFrame()
{
	XTPSkinManager()->LoadSkin(NULL);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
#ifndef _XTP_INCLUDE_COMMANDBARS

// create and initialize all control bars prior to
	// creating docking panes...

	if (!m_wndToolBar.Create(this, TBSTYLE_FLAT|WS_CHILD | WS_VISIBLE | CBRS_TOP
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

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

#else
	if (!m_wndStatusBar.Create(this) ||
		 !m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT)))
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

	m_MTIClientWnd.Attach(this);

#endif
	
	// Load the previous state for command bars.
	//LoadCommandBars(_T("CommandBars"));

#ifdef _XTP_INCLUDE_DOCKINGPANE
	m_paneManager.InstallDockingPanes(this);

	// Create docking panes.
	m_paneManager.CreatePane(
		IDD_PANE_DIALOGS, CRect(0, 0,120, 120), xtpPaneDockRight);
#else

#ifdef _XTP_INCLUDE_COMMANDBARS
	CXTPDialogBar* pBar = (CXTPDialogBar*)pCommandBars->Add(_T("System Dialogs"), xtpBarRight, RUNTIME_CLASS(CXTPDialogBar));
	pBar->SetBarID(200);
	pBar->EnableDocking(xtpFlagAlignAny|xtpFlagFloating|xtpFlagStretched);
	pBar->SetCaption(_T("System Dialogs"));
	pBar->ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS);

	CCreateContext contextT;
	contextT.m_pLastView = NULL;
	contextT.m_pCurrentFrame = NULL;
	contextT.m_pNewDocTemplate = NULL;
	contextT.m_pCurrentDoc = NULL;
	contextT.m_pNewViewClass = RUNTIME_CLASS(CDialogsView);

	CFrameWnd* pSystemDialogs = new CFrameWnd;

	pSystemDialogs->Create(NULL, NULL, WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		CRect(0, 0, 0, 0), pBar, NULL, 0, &contextT);

	pSystemDialogs->ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);

	CWnd* pView = pSystemDialogs->GetDescendantWindow(AFX_IDW_PANE_FIRST, TRUE);
	pView->ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);

	pBar->SetChild(pSystemDialogs);

#endif


#endif


#ifdef _XTP_INCLUDE_COMMANDBARS
	SetTheme(xtpThemeNativeWinXP);

	GetCommandBars()->GetPaintManager()->m_bAutoResizeIcons = TRUE;
	GetCommandBars()->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE);
#endif

	ShowThemesDialog();

	return 0;
}

void CMainFrame::ShowThemesDialog()
{
	if (!::IsWindow(m_dlgThemes.GetSafeHwnd()))
	{
		m_dlgThemes.Create(this);
		m_dlgThemes.CenterWindow(this);
	}
	else
	{
		m_dlgThemes.SetFocus();
	}
	
	m_dlgThemes.ShowWindow(SW_SHOW);
}

void CMainFrame::OnClose() 
{
#ifdef _XTP_INCLUDE_COMMANDBARS

    // Save the current state for toolbars and menus.
    SaveCommandBars(_T("CommandBars"));
#endif

    CMDIFrameWnd::OnClose();
}

void CMainFrame::OnCustomize()
{
#ifdef _XTP_INCLUDE_COMMANDBARS
    // Get a pointer to the command bars object.
    CXTPCommandBars* pCommandBars = GetCommandBars();
    if(pCommandBars != NULL)
    {
        // Instantiate the customize dialog object.
        CXTPCustomizeSheet dlg(pCommandBars);

        // Add the options page to the customize dialog.
        CXTPCustomizeOptionsPage pageOptions(&dlg);
        dlg.AddPage(&pageOptions);

        // Add the commands page to the customize dialog.
        CXTPCustomizeCommandsPage* pCommands = dlg.GetCommandsPage();
        pCommands->AddCategories(IDR_SKINMDTYPE);

        // Use the command bar manager to initialize the 
        // customize dialog.
        pCommands->InsertAllCommandsCategory();
        pCommands->InsertBuiltInMenus(IDR_SKINMDTYPE);
        pCommands->InsertNewMenuCategory();

        // Display the dialog.
        dlg.DoModal();
    }
#endif
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

/////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::RedrawFrame(CWnd* pWnd)
{
	pWnd->RedrawWindow(0, 0, RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ALLCHILDREN);		
}

void CMainFrame::OnSkinChanged()
{
#ifdef _XTP_INCLUDE_COMMANDBARS
	if (m_nTheme == xtpThemeOffice2003)
	{
		if (XTPSkinManager()->GetResourceFile() &&
			XTPSkinManager()->GetResourceFile()->GetResourcePath().Find(_T("Office2007")) > 0)
		{
			XTPPaintManager()->SetTheme(xtpThemeResource);
		}
		else
		{		
			XTPPaintManager()->SetTheme(xtpThemeOffice2003);
		}
	}

	GetCommandBars()->GetPaintManager()->m_bAutoResizeIcons = TRUE;
	GetCommandBars()->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE);
	XTPPaintManager()->RefreshMetrics();
#endif

	RedrawFrame(this);	
	
	if (::IsWindow(m_dlgThemes.m_hWnd))
		RedrawFrame(&m_dlgThemes);
	
	m_wndStatusBar.Invalidate();

	CWnd* pWnd = CWnd::FromHandle(m_hWndMDIClient)->GetWindow(GW_CHILD);
	while(pWnd)
	{
		RedrawFrame(pWnd);
		
		pWnd = pWnd->GetWindow(GW_HWNDNEXT);
	}

#ifdef _XTP_INCLUDE_COMMANDBARS
	GetCommandBars()->GetPaintManager()->RefreshMetrics();

	GetCommandBars()->RedrawCommandBars();
#endif

}

void CMainFrame::OnSchemaChanged(int nSchema)
{
	switch (nSchema)
	{
	case 0:
		XTPSkinManager()->LoadSkin(GetStylesPath() + _T("Office2007.cjstyles"));
		break;
	case 1:
		XTPSkinManager()->LoadSkin(GetStylesPath() + _T("WinXP.Luna.cjstyles"), _T("NormalBlue.INI"));
		break;
	case 2:
		XTPSkinManager()->LoadSkin(GetStylesPath() + _T("WinXP.Royale.cjstyles"), _T("NormalRoyale.INI"));
		break;
	case 3:
		XTPSkinManager()->LoadSkin(GetStylesPath() + _T("Vista.cjstyles"), _T("NormalBlack2.INI"));
		break;
	default:
		XTPSkinManager()->LoadSkin(_T(""), _T(""));
	}

	if (m_hWnd) OnSkinChanged();
}


void CMainFrame::OnViewThemeDialog() 
{
	ShowThemesDialog();
}



void CMainFrame::OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState)
{
#ifdef _XTP_INCLUDE_COMMANDBARS

// Toggle CommandBars
	GetCommandBars()->OnSetPreviewMode(bPreview);

// Toggle Tab Client
	m_MTIClientWnd.ShowWorkspace(!bPreview);
#endif

	CMDIFrameWnd::OnSetPreviewMode(bPreview, pState);
}

 
void CMainFrame::OnViewTheme() 
{
	SetTheme((m_nTheme + 1) % 4);
}

void CMainFrame::OnUpdateViewTheme(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();	
	pCmdUI->SetCheck((int)pCmdUI->m_nID == m_nTheme + ID_THEME_OFFICE2000 ? TRUE : FALSE);
}


void CMainFrame::OnViewThemePopup(UINT nCommand)
{
	SetTheme(nCommand - ID_THEME_OFFICE2000);
}

void CMainFrame::SetTheme(int nTheme)
{

	m_nTheme = nTheme;

#ifdef _XTP_INCLUDE_COMMANDBARS
	if (m_nTheme == xtpThemeOffice2003)
	{
		if (XTPSkinManager()->GetResourceFile() &&
			XTPSkinManager()->GetResourceFile()->GetResourcePath().Find(_T("Office2007")) > 0)
		{
			nTheme = xtpThemeResource;
		}
	}
#endif

#ifdef _XTP_INCLUDE_DOCKINGPANE
	m_paneManager.SetTheme((XTPDockingPanePaintTheme)nTheme);
#endif
	
#ifdef _XTP_INCLUDE_COMMANDBARS

	CXTPPaintManager::SetTheme((XTPPaintTheme)nTheme);
	XTPPaintManager()->GetIconsInfo()->bUseFadedIcons = FALSE;
	XTPPaintManager()->GetIconsInfo()->bIconsWithShadow = FALSE;

	GetCommandBars()->GetPaintManager()->m_bAutoResizeIcons = TRUE;
	GetCommandBars()->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE);
	GetCommandBars()->RedrawCommandBars();

	m_MTIClientWnd.GetPaintManager()->RefreshMetrics();	
#endif
	
	RedrawWindow( NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_ALLCHILDREN);

}

#ifdef _XTP_INCLUDE_COMMANDBARS
int CMainFrame::OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl)
{
	if (lpCreateControl->nID == ID_VIEW_THEME)
	{
		lpCreateControl->controlType = xtpControlSplitButtonPopup;
		lpCreateControl->buttonStyle = xtpButtonIconAndCaption;
		return TRUE;
	}
	
	return FALSE;
}
#endif

#ifdef _XTP_INCLUDE_DOCKINGPANE

LRESULT CMainFrame::OnDockingPaneNotify(WPARAM wParam, LPARAM lParam)
{
	if (wParam == XTP_DPN_SHOWWINDOW)
	{
		// get a pointer to the docking pane being shown.
		CXTPDockingPane* pPane = (CXTPDockingPane*)lParam;
		if (!pPane->IsValid())
		{
			pPane->AttachView(this, RUNTIME_CLASS(CDialogsView));
		}

		return TRUE; // handled
	}
	
	return FALSE;
}

#endif
 
