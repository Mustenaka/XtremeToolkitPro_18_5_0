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
#include "GUI_VisualStudio.h"
#include "PaneWnd.h"

#include "MainFrm.h"
#include "DynamicHelpView.h"
#include "GUI_VisualStudioDoc.h"
#include "GUI_VisualStudioView.h"

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
	ON_COMMAND(ID_WINDOW_AUTOHIDEALL, OnWindowAutohideall)
	ON_COMMAND(ID_WINDOW_MORE, OnWindowMore)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify)

	ON_COMMAND(ID_VIEW_FULLSCREEN, OnFullScreen)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FULLSCREEN, OnUpdateFullScreen)

	ON_COMMAND_RANGE(ID_VIEW_SOLUTIONEXPLORER, ID_VIEW_TOOLBOX, OnShowView)
	ON_COMMAND_RANGE(ID_VIEW_CLASSVIEW, ID_HELP_DYNAMICHELP, OnShowViewOther)

	ON_COMMAND(ID_VIEW_OTHER, OnViewOther)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OTHER, OnUpdateViewOther)
	ON_COMMAND_RANGE(ID_FILE_NEW_PROJECT + 1, 200, OnEmptyCommandRange)

	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
	ON_XTP_CREATECONTROL()

	ON_COMMAND_RANGE(ID_THEME_VC6, ID_THEME_VC14_BLUE, OnTheme)
	ON_UPDATE_COMMAND_UI_RANGE(ID_THEME_VC6, ID_THEME_VC14_BLUE, OnUpdateTheme)

	ON_XTP_EXECUTE(ID_EDIT_STATE, OnEditState)
	ON_UPDATE_COMMAND_UI(ID_EDIT_STATE, OnUpdateEditState)

	ON_XTP_EXECUTE(ID_EDIT_PLATFORM, OnEditPlatform)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PLATFORM, OnUpdateEditPlatform)
	ON_WM_ACTIVATE()
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
	m_nState = 1;
	m_nPlatform = 0;
	m_bFullScreen = FALSE;

	// get path of executable
	TCHAR szBuff[_MAX_PATH];
	VERIFY(::GetModuleFileName(AfxGetInstanceHandle(), szBuff, _MAX_PATH));

	LPTSTR lpszExt = _tcsrchr(szBuff, '.');
	lstrcpy(lpszExt, _T(".xml"));

	m_strIniFileName = szBuff;

	m_pFullScreenLayout = NULL;
	m_rcMainFrame.SetRectEmpty();

	m_nTheme = 0;

	m_nOtherView = ID_VIEW_CLASSVIEW;
}

CMainFrame::~CMainFrame()
{
	if (m_pFullScreenLayout)
	{
		delete m_pFullScreenLayout;
	}
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!InitCommandBars())
		return -1;

	CXTPPaintManager::SetTheme(xtpThemeVisualStudio2012Light);

	CXTPCommandBars* pCommandBars = GetCommandBars();

	CXTPCommandBar* pMenuBar = pCommandBars->SetMenu(_T("Menu Bar"), IDR_MAINFRAME);
	pMenuBar->SetFlags(xtpFlagIgnoreSetMenuMessage);

	CXTPToolBar* pCommandBar = (CXTPToolBar*)pCommandBars->Add(_T("Standard"), xtpBarTop);
	if (!pCommandBar ||
		!pCommandBar->LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	CXTPToolBar* pWebBar = (CXTPToolBar*)pCommandBars->Add(_T("Web"), xtpBarTop);
	if (!pWebBar ||
		!pWebBar->LoadToolBar(IDR_TOOLBAR_WEB))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	CXTPToolBar* pThemeBar = (CXTPToolBar*)pCommandBars->Add(_T("Theme"), xtpBarTop);
	if (!pThemeBar ||
		!pThemeBar->LoadToolBar(IDR_TOOLBAR_THEME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}
	DockRightOf(pThemeBar, pWebBar);

	CXTPToolBar* pFullScreenBar = (CXTPToolBar*)pCommandBars->Add(_T("Full Screen"), xtpBarTop);
	if (!pFullScreenBar ||
		!pFullScreenBar->LoadToolBar(IDR_TOOLBAR_FULLSCREEN))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}
	pFullScreenBar->SetVisible(FALSE);

	XTPPaintManager()->GetIconsInfo()->bUseDisabledIcons = TRUE;
	
	pCommandBars->GetCommandBarsOptions()->ShowKeyboardCues(xtpKeyboardCuesShowWindowsDefault);
	pCommandBars->GetToolTipContext()->SetStyle(xtpToolTipOffice);
	pCommandBars->GetShortcutManager()->SetAccelerators(IDR_MAINFRAME);

	CreatePaneWindows();

	m_paneManager.InstallDockingPanes(this);
	m_paneManager.SetTheme(xtpPaneThemeVisualStudio2012);
	
	m_paneManager.CreatePane(
		ID_WINDOWS_OUTPUT, XTP_DPI(CRect(0, 0, 150, 120)), xtpPaneDockBottom);
	
	CXTPDockingPane* paneToolBox = m_paneManager.CreatePane(
		ID_VIEW_TOOLBOX, XTP_DPI(CRect(0, 0, 200, 120)), xtpPaneDockRight);
	
	CXTPDockingPane* paneClassView = m_paneManager.CreatePane(
		ID_VIEW_CLASSVIEW, XTP_DPI(CRect(0, 0, 230, 140)), xtpPaneDockLeft);
	
	CXTPDockingPane* paneSolutionExplorer = m_paneManager.CreatePane(
		ID_VIEW_SOLUTIONEXPLORER, XTP_DPI(CRect(0, 0, 230, 140)), xtpPaneDockLeft);
	
	CXTPDockingPane* paneResourceView = m_paneManager.CreatePane(
		ID_VIEW_RESOURCEVIEW, XTP_DPI(CRect(0, 0, 230, 140)), xtpPaneDockLeft);

	CXTPDockingPane* paneHelpView =m_paneManager.CreatePane(
		ID_HELP_DYNAMICHELP, XTP_DPI(CRect(0, 0, 210, 140)), xtpPaneDockBottom, paneToolBox);

	paneHelpView->Close();

	m_paneManager.AttachPane(paneClassView, paneSolutionExplorer);
	m_paneManager.AttachPane(paneResourceView, paneClassView);

	paneClassView->Select();
	
	m_paneManager.CreatePane(
		ID_VIEW_PROPERTIESWINDOW, XTP_DPI(CRect(0, 0, 180, 140)), xtpPaneDockBottom, paneClassView);

	m_paneManager.EnableKeyboardNavigate();
	

	//CXTPPropExchangeIniFile px(TRUE, 0, _T("Settings")); // To serialize to ini file
	CXTPPropExchangeXMLNode px(TRUE, 0, _T("Settings"));   // To serialize to XML file

	if (px.LoadFromFile(m_strIniFileName))
	{
#ifdef _XTP_INCLUDE_CONTROLS
		CXTPPropExchangeSection pxTaskPanel(px.GetSection(_T("TaskPanel")));
		m_wndPaneViewTaskPanel.DoPropExchange(&pxTaskPanel);
#endif
		CXTPPropExchangeSection pxNormalLayout(px.GetSection(_T("NormalLayout")));
		ExchangeLayout(&pxNormalLayout);

		m_pFullScreenLayout = DYNAMIC_DOWNCAST(CXTPPropExchangeXMLNode, px.GetSection(_T("FullScreenLayout")));
		ASSERT(m_pFullScreenLayout);
	}
	else
	{
		m_wndPaneViewTaskPanel.ResetToolboxItems();
	}

	CXTPImageManager* pImageManager = pCommandBars->GetImageManager();

	pImageManager->InternalAddRef();
	m_paneManager.SetImageManager(pImageManager);

	m_paneManager.SetDefaultPaneOptions(xtpPaneHasMenuButton);

	VERIFY(m_MTIClientWnd.Attach(this, TRUE));
	m_MTIClientWnd.EnableToolTips();

	m_MTIClientWnd.GetPaintManager()->m_bShowIcons = TRUE;
	m_MTIClientWnd.SetNewTabPosition(xtpWorkspaceNewTabLeftMost);

	OnTheme(ID_THEME_VC14_LIGHT);

	CXTPToolTipContext* pToolTipContext = GetCommandBars()->GetToolTipContext();
	pToolTipContext->SetStyle(GetToolTipStyle());
	pToolTipContext->SetDelayTime(TTDT_INITIAL, 900);

	return 0;
}

void CMainFrame::CreatePaneWindows()
{
	if (!m_wndClassView.GetSafeHwnd())
	{
		m_wndClassView.Create(_T("STATIC"), NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
	}

	if (!m_wndResourceView.GetSafeHwnd())
	{
		m_wndResourceView.Create(_T("STATIC"), NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
	}

	if (!m_wndSolutionExplorer.GetSafeHwnd())
	{
		m_wndSolutionExplorer.Create(_T("STATIC"), NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
	}

	if (!m_wndProperties.GetSafeHwnd())
	{
		m_wndProperties.Create(_T("STATIC"), NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
	}

	if (!m_wndPaneViewTaskPanel.GetSafeHwnd())
	{
		m_wndPaneViewTaskPanel.Create(_T("STATIC"), NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
	}

	if (!m_wndOutput.GetSafeHwnd())
	{
		m_wndOutput.Create(WS_HSCROLL|ES_AUTOHSCROLL|ES_MULTILINE|WS_VISIBLE, CXTPEmptyRect(), this, 0);
	}
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

void CMainFrame::ShowDockingPanePopupMenu(CXTPDockingPane* pPopupPane, CPoint pt, LPRECT lprcExclude)
{
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_POPUP_PANES));
	CMenu* pPopup = menu.GetSubMenu(0);
	
	
	if (pPopupPane->IsHidden())
	{
		pPopup->CheckMenuItem(ID_POPUP_AUTOHIDE, MF_BYCOMMAND|MF_CHECKED);
		pPopup->EnableMenuItem(ID_POPUP_FLOATING, MF_BYCOMMAND|MF_DISABLED);
		pPopup->EnableMenuItem(ID_POPUP_DOCKABLE, MF_BYCOMMAND|MF_DISABLED);
	}
	else if (pPopupPane->GetOptions() & xtpPaneNoDockable)
	{
		pPopup->CheckMenuItem(ID_POPUP_FLOATING, MF_BYCOMMAND|MF_CHECKED);
	}
	else
	{
		pPopup->CheckMenuItem(ID_POPUP_DOCKABLE, MF_BYCOMMAND|MF_CHECKED);
	}

	TPMPARAMS tpm;
	tpm.cbSize = sizeof(TPMPARAMS);
	tpm.rcExclude = lprcExclude ? *lprcExclude : CRect(0, 0, 0, 0);

	int nCommand = GetCommandBars()->TrackPopupMenuEx(pPopup, TPM_RIGHTBUTTON|TPM_NONOTIFY|TPM_RETURNCMD, pt.x, pt.y, NULL, &tpm);
	
	switch (nCommand)
	{
	case ID_POPUP_HIDE:
		pPopupPane->Close();
		break;		
		
	case ID_POPUP_AUTOHIDE:
		m_paneManager.ToggleAutoHide(pPopupPane);
		break;

	case ID_POPUP_DOCKABLE:
		if (pPopupPane->GetOptions() & xtpPaneNoDockable)
		{
			pPopupPane->SetOptions(pPopupPane->GetOptions() & ~xtpPaneNoDockable);
		}
		break;

	case ID_POPUP_FLOATING:
		if ((pPopupPane->GetOptions() & xtpPaneNoDockable) == 0)
		{
			if (!pPopupPane->IsFloating())
				m_paneManager.ToggleDocking(pPopupPane);
			
			pPopupPane->SetOptions(pPopupPane->GetOptions() | xtpPaneNoDockable);
		}

		break;
	}
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
					pPane->Attach(&m_wndPaneViewTaskPanel);
					m_wndPaneViewTaskPanel.SetOwnerPane(pPane);
					break;

				case ID_VIEW_CLASSVIEW:
					pPane->Attach(&m_wndClassView);
					m_wndClassView.SetOwnerPane(pPane);
					break;

				case ID_VIEW_RESOURCEVIEW:
					pPane->Attach(&m_wndResourceView);
					m_wndResourceView.SetOwnerPane(pPane);
					break;

				case ID_VIEW_SOLUTIONEXPLORER:
					pPane->Attach(&m_wndSolutionExplorer);
					m_wndSolutionExplorer.SetOwnerPane(pPane);
					break;

				case ID_VIEW_PROPERTIESWINDOW:
					pPane->Attach(&m_wndProperties);
					m_wndProperties.SetOwnerPane(pPane);
					break;

				case ID_WINDOWS_OUTPUT:
					pPane->Attach(&m_wndOutput);
					m_wndOutput.SetOwnerPane(pPane);
					break;

				case ID_HELP_DYNAMICHELP:
					{
						// attach the dynamic help view to the pane.
						CWnd* pView = pPane->AttachView(this, RUNTIME_CLASS(CDynamicHelpView));
						pView;
						break;
					}
	
			}
		}
		return 1;
	}

	if (wParam == XTP_DPN_CONTEXTMENU)
	{
		XTP_DOCKINGPANE_CLICK* pClick = (XTP_DOCKINGPANE_CLICK*)lParam;

		CXTPDockingPane* pPopupPane = pClick->pPane;
		if (!pPopupPane) 
			return FALSE;

		ShowDockingPanePopupMenu(pPopupPane, pClick->pt, pClick->rcExclude);

		return TRUE;
	}
	
	return 0;
}

void CMainFrame::OnShowView(UINT nID)
{
	m_paneManager.ShowPane(nID);
}

void CMainFrame::OnShowViewOther(UINT nID)
{
	m_nOtherView = nID;
	m_paneManager.ShowPane(nID);
}

void CMainFrame::OnViewOther()
{
	m_paneManager.ShowPane(m_nOtherView);
}

void CMainFrame::OnUpdateViewOther(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
	CXTPControl* pControl = CXTPControl::FromUI(pCmdUI);

	if (pControl && pControl->GetIconId() != m_nOtherView)
	{
		pControl->SetIconId(m_nOtherView);
		
		CString strPrompt;
		strPrompt.LoadString(m_nOtherView);
		pControl->SetPrompt(strPrompt);
	}
}

void CMainFrame::OnEmptyCommandRange(UINT)
{

}

void CMainFrame::OnWindowAutohideall()
{
	CXTPDockingPaneInfoList& lstPanes = m_paneManager.GetPaneList();
	POSITION pos = lstPanes.GetHeadPosition();
	while (pos)
	{
		CXTPDockingPane* pPane = lstPanes.GetNext(pos);
		if (!pPane->IsClosed() && !pPane->IsHidden())
			m_paneManager.HidePane(pPane);
	}
}

void CMainFrame::OnWindowMore()
{
#ifdef _XTP_INCLUDE_CONTROLS
	CXTPWindowList dlg(this);
	dlg.DoModal();
#endif
}


int CMainFrame::OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl)
{
	if (lpCreateControl->bToolBar)
	{
		CXTPToolBar* pToolBar = DYNAMIC_DOWNCAST(CXTPToolBar, lpCreateControl->pCommandBar);
		if (!pToolBar)
			return FALSE;

		if (lpCreateControl->nID == ID_VIEW_OTHER && pToolBar->GetBarID() == IDR_MAINFRAME)
		{
			lpCreateControl->controlType = xtpControlSplitButtonPopup;
			return TRUE;
		}
		if (lpCreateControl->nID == ID_VIEW_FULLSCREEN)
		{
			lpCreateControl->buttonStyle = xtpButtonIconAndCaption;
			return TRUE;
		}

		if (lpCreateControl->nID == ID_FILE_NEW_PROJECT && pToolBar->GetBarID() == IDR_MAINFRAME)
		{
			lpCreateControl->controlType = xtpControlSplitButtonPopup;
			return TRUE;
		}
		if (lpCreateControl->nID == ID_PROJECT_ADDNEWITEM && pToolBar->GetBarID() == IDR_MAINFRAME)
		{
			lpCreateControl->controlType = xtpControlSplitButtonPopup;
			return TRUE;
		}

		if (lpCreateControl->nID == ID_EDIT_FIND_EX && pToolBar->GetBarID() == IDR_MAINFRAME)
		{
			CXTPControlComboBox* pComboFind = new CXTPControlComboBox(GetCommandBars());
			pComboFind->ModifyListBoxStyle(0, LBS_OWNERDRAWFIXED | LBS_HASSTRINGS);
			pComboFind->SetFlags(xtpFlagManualUpdate);

			pComboFind->SetDropDownListStyle();

			pComboFind->AddString(_T("Line1"));
			pComboFind->AddString(_T("Line2"));
			pComboFind->AddString(_T("Line3"));

			pComboFind->SetWidth(XTP_DPI_X(180));
			pComboFind->SetCaption(_T("Find"));
			pComboFind->SetStyle(xtpComboLabel);
			pComboFind->SetEditText(_T("Line1"));

			lpCreateControl->pControl = pComboFind;
			return TRUE;
		}

		if (lpCreateControl->nID == ID_EDIT_STATE && pToolBar->GetBarID() == IDR_MAINFRAME)
		{
			CXTPControlComboBox* pComboState = new CXTPControlComboBox(GetCommandBars());
			pComboState->ModifyListBoxStyle(0, LBS_OWNERDRAWFIXED | LBS_HASSTRINGS);
			pComboState->SetFlags(xtpFlagManualUpdate);
			pComboState->AddString(_T("Debug"));
			pComboState->AddString(_T("Release"));
			pComboState->AddString(_T("Configuration Manager"));
			pComboState->SetDropDownWidth(XTP_DPI_X(150));
			pComboState->SetDropDownListStyle();
			pComboState->SetEditText(_T("Debug"));
			lpCreateControl->pControl = pComboState;
			return TRUE;
		}

		if (lpCreateControl->nID == ID_EDIT_PLATFORM && pToolBar->GetBarID() == IDR_MAINFRAME)
		{
			CXTPControlComboBox* pComboState = new CXTPControlComboBox(GetCommandBars());
			pComboState->ModifyListBoxStyle(0, LBS_OWNERDRAWFIXED | LBS_HASSTRINGS);
			pComboState->SetFlags(xtpFlagManualUpdate);			
			pComboState->AddString(_T("Win32"));
			pComboState->AddString(_T("Configuration Manager"));
			pComboState->SetDropDownWidth(XTP_DPI_X(150));
			pComboState->SetDropDownListStyle();
			pComboState->SetEditText(_T("Win32"));
			lpCreateControl->pControl = pComboState;
			return TRUE;
		}


		if (lpCreateControl->nID == ID_GOTO_URL && pToolBar->GetBarID() == IDR_TOOLBAR_WEB)
		{
			CXTPControlComboBox* pComboUrl = new CXTPControlComboBox(GetCommandBars());
			pComboUrl->ModifyListBoxStyle(0, LBS_OWNERDRAWFIXED | LBS_HASSTRINGS);
			pComboUrl->AddString(_T("http://www.codejock.com"));
			pComboUrl->AddString(_T("ms-help://MS.VSCC/vsccCommon/html/vsccCommon_Start_Page.htm"));
			pComboUrl->SetWidth(XTP_DPI_X(200));
			pComboUrl->SetDropDownWidth(XTP_DPI_X(300));
			pComboUrl->SetDropDownListStyle();
			pComboUrl->SetFlags(xtpFlagManualUpdate);
			pComboUrl->SetEditText(_T("http://www.codejock.com"));
			pComboUrl->EnableShellAutoComplete();

			lpCreateControl->pControl = pComboUrl;
			return TRUE;
		}


	}
	return FALSE;

}

void CMainFrame::OnCustomize()
{
	CXTPCustomizeSheet cs(GetCommandBars());

	CXTPCustomizeKeyboardPage pageKeyboard(&cs);
	cs.AddPage(&pageKeyboard);
	pageKeyboard.AddCategories(IDR_MAINFRAME, TRUE);

	CXTPCustomizeOptionsPage pageOptions(&cs);
	cs.AddPage(&pageOptions);

	CXTPCustomizeCommandsPage* pCommands = cs.GetCommandsPage();
	pCommands->AddCategories(IDR_MAINFRAME, TRUE);

	pCommands->InsertAllCommandsCategory();
	pCommands->InsertBuiltInMenus(IDR_MAINFRAME);
	pCommands->InsertNewMenuCategory();

	cs.DoModal();
}

void CMainFrame::OnEditState(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CXTPControlComboBox* pControl = (CXTPControlComboBox*)tagNMCONTROL->pControl;
	if (pControl->GetType() == xtpControlComboBox)
	{
		int nState = pControl->GetCurSel();
		if (nState != 2)
		{
			m_nState = nState;
		}
		else
		{
			MessageBox(_T("Configuration Manager"));
			pControl->SetCurSel(m_nState);
		}
		*pResult = TRUE; // Handled
	}
}

void CMainFrame::OnUpdateEditState(CCmdUI* pCmdUI)
{
	CXTPCommandBar* pToolBar = (CXTPToolBar*)pCmdUI->m_pOther;
	if (pToolBar && !XTPMouseManager()->IsTrackedLock())
	{
		CXTPControlComboBox* pStateCombo = (CXTPControlComboBox*)pToolBar->GetControls()->GetAt(pCmdUI->m_nIndex);

		if (pStateCombo->GetType() == xtpControlComboBox)
		{
			pStateCombo->SetCurSel(m_nState);
		}
	}

	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnEditPlatform(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CXTPControlComboBox* pControl = (CXTPControlComboBox*)tagNMCONTROL->pControl;
	if (pControl->GetType() == xtpControlComboBox)
	{
		int nState = pControl->GetCurSel();
		if (nState != 1)
		{
			m_nPlatform = nState;
		}
		else
		{
			MessageBox(_T("Configuration Manager"));
			pControl->SetCurSel(m_nPlatform);
		}
		*pResult = TRUE; // Handled
	}
}

void CMainFrame::OnUpdateEditPlatform(CCmdUI* pCmdUI)
{
	CXTPCommandBar* pToolBar = (CXTPToolBar*)pCmdUI->m_pOther;
	if (pToolBar && !XTPMouseManager()->IsTrackedLock())
	{
		CXTPControlComboBox* pStateCombo = (CXTPControlComboBox*)pToolBar->GetControls()->GetAt(pCmdUI->m_nIndex);

		if (pStateCombo->GetType() == xtpControlComboBox)
		{
			pStateCombo->SetCurSel(m_nPlatform);
		}
	}

	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnClose()
{
	//CXTPPropExchangeIniFile px(FALSE, 0, _T("Settings"));    // To serialize to ini file
	CXTPPropExchangeXMLNode px(FALSE, 0, _T("Settings"));      // To serialize to XML file

	if (px.OnBeforeExchange()) 
	{
#ifdef _XTP_INCLUDE_CONTROLS
		CXTPPropExchangeSection pxTaskPanel(px.GetSection(_T("TaskPanel")));
		m_wndPaneViewTaskPanel.DoPropExchange(&pxTaskPanel);
#endif

		// Reset Full Screen Mode
		if (m_bFullScreen)
		{
			OnFullScreen();
		}

		CXTPPropExchangeSection pxNormalLayout(px.GetSection(_T("NormalLayout")));
		ExchangeLayout(&pxNormalLayout);
	
		px.PutSection(m_pFullScreenLayout);

		px.SaveToFile(m_strIniFileName);
	}

	CMDIFrameWnd::OnClose();
}


void CMainFrame::OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState)
{

// Toggle CommandBars
	GetCommandBars()->OnSetPreviewMode(bPreview);
// Toggle Tab Client
	m_MTIClientWnd.ShowWorkspace(!bPreview);

// Toggle Docking Panes.
	m_paneManager.OnSetPreviewMode(bPreview);


	CMDIFrameWnd::OnSetPreviewMode(bPreview, pState);
}

void CMainFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	static HWND hFocus = 0;

	if (nState == WA_INACTIVE)
	{
		hFocus = m_paneManager.GetActivePane() != NULL ? ::GetFocus() : NULL;
	}
	
	CMDIFrameWnd::OnActivate(nState, pWndOther, bMinimized);

	if (nState != WA_INACTIVE && hFocus)
	{
		::SetFocus(hFocus);		
		hFocus = NULL;		
	}
}

void CMainFrame::ExchangeLayout(CXTPPropExchange* pPX, BOOL bSerializeControls /*= TRUE*/)
{
	XTP_COMMANDBARS_PROPEXCHANGE_PARAM param; param.bSerializeControls = bSerializeControls; 

	CXTPPropExchangeSection pxCommandBars(pPX->GetSection(_T("CommandBars")));
	GetCommandBars()->DoPropExchange(&pxCommandBars, &param);

	CXTPPropExchangeSection secShortcuts(pPX->GetSection(_T("Shortcuts")));
	GetCommandBars()->GetShortcutManager()->DoPropExchange(&secShortcuts);

	CXTPPropExchangeSection secOptions(pPX->GetSection(_T("Options")));	
	GetCommandBars()->GetCommandBarsOptions()->DoPropExchange(&secOptions, TRUE);

	CXTPPropExchangeSection pxDockingPane(pPX->GetSection(_T("DockingPane")));	
	m_paneManager.DoPropExchange(&pxDockingPane);
}

void CMainFrame::OnFullScreen()
{
	m_bFullScreen ^= 1;

	CXTPPropExchangeXMLNode px(FALSE, 0, _T("Settings"));
	CXTPPropExchangeXMLNode* pxLayoutSave = DYNAMIC_DOWNCAST(CXTPPropExchangeXMLNode, px.GetSection(_T("FullScreenLayout")));
	ASSERT(pxLayoutSave);

	// Save current layout
	if (pxLayoutSave != 0)
	{	
		ExchangeLayout(pxLayoutSave, FALSE);
	}

	// If Full screen layout exists
	if (m_pFullScreenLayout && m_pFullScreenLayout->IsSectionExists(_T("CommandBars")))
	{
		// Set it
		m_pFullScreenLayout->SetLoading(TRUE);
		ExchangeLayout(m_pFullScreenLayout, FALSE);
	}
	// Else create new fullscreen layout. Hide all toolbars and DockingPanes.
	else
	{		
		for (int i = 0; i < GetCommandBars()->GetCount(); i++)
		{
			CXTPToolBar* pToolBar = GetCommandBars()->GetAt(i);
			pToolBar->SetVisible((pToolBar->GetType() == xtpBarTypeMenuBar) || (pToolBar->GetBarID() == IDR_TOOLBAR_FULLSCREEN));
		}
		m_paneManager.CloseAll();
	}
	
	// Save old layout
	if (m_pFullScreenLayout)
	{
		delete m_pFullScreenLayout;
	}
	m_pFullScreenLayout = pxLayoutSave;


	if (m_bFullScreen)
	{
		GetWindowRect(&m_rcMainFrame);

		ModifyStyle(WS_CAPTION|WS_THICKFRAME, 0);
		
		// Now resize the main window
		CRect rcScreen = XTPMultiMonitor()->GetScreenArea(this);
		
		int cxBorder = ::GetSystemMetrics(SM_CXBORDER);
		int cyBorder = ::GetSystemMetrics(SM_CYBORDER);

		SetWindowPos(NULL, rcScreen.left - cxBorder, rcScreen.top - cyBorder, 
			rcScreen.Width() + cxBorder * 2, rcScreen.Height() + cyBorder * 2, SWP_NOZORDER);

		m_wndStatusBar.ShowWindow(SW_HIDE);

	} 
	else
	{
		ModifyStyle(0, WS_CAPTION|WS_THICKFRAME);
		MoveWindow(&m_rcMainFrame);
		m_wndStatusBar.ShowWindow(SW_SHOW);
	}
	RecalcLayout(TRUE);
}

void CMainFrame::OnUpdateFullScreen(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bFullScreen);
}

void CMainFrame::OnTheme(UINT nID)
{
	m_nTheme = nID;
	theApp.strSchema.Empty();
	theApp.strColor.Empty();

	switch (nID)
	{
	case ID_THEME_VC6:
		theApp.m_theme = themeVS6;
		SetCommandBarsTheme(xtpThemeVisualStudio6);
		SetDockingPaneTheme(xtpPaneThemeGrippered);
		break;

	case ID_THEME_VC7:
		theApp.m_theme = themeVS2003;
		SetCommandBarsTheme(xtpThemeOfficeXP);
		SetDockingPaneTheme(xtpPaneThemeVisualStudio2003);
		break;

	case ID_THEME_VC8:
		theApp.m_theme = themeVS2005;
		SetCommandBarsTheme(xtpThemeVisualStudio2005);
		SetDockingPaneTheme(xtpPaneThemeVisualStudio2005, xtpPaneStickerStyleVisualStudio2005);
		m_paneManager.GetPaintManager()->GetPanelPaintManager()->m_bShowIcons = TRUE;
		m_paneManager.GetPaintManager()->GetTabPaintManager()->m_bShowIcons = FALSE;
		break;

	case ID_THEME_VC9:
		theApp.m_theme = themeVS2008;
		SetCommandBarsTheme(xtpThemeVisualStudio2008);
		SetDockingPaneTheme(xtpPaneThemeVisualStudio2008, xtpPaneStickerStyleVisualStudio2008);
		break;

	case ID_THEME_VC10:
		theApp.m_theme = themeVS2010;
		SetCommandBarsTheme(xtpThemeVisualStudio2010);
		SetDockingPaneTheme(xtpPaneThemeVisualStudio2010, xtpPaneStickerStyleVisualStudio2010);
		break;

	case ID_THEME_VC11_LIGHT:
		theApp.m_theme = themeVS2012Light;
		SetCommandBarsTheme(xtpThemeVisualStudio2012Light, xtpIniVisualStudio2012Light);
		SetDockingPaneTheme(xtpPaneThemeVisualStudio2012, xtpPaneStickerStyleVisualStudio2012Light, XTP_DPI_X(5));
		break;

	case ID_THEME_VC11_DARK:
		theApp.m_theme = themeVS2012Dark;
		SetCommandBarsTheme(xtpThemeVisualStudio2012Dark, xtpIniVisualStudio2012Dark);
		SetDockingPaneTheme(xtpPaneThemeVisualStudio2012, xtpPaneStickerStyleVisualStudio2012Dark, XTP_DPI_X(5));
		break;

	case ID_THEME_VC14_LIGHT:
		theApp.m_theme = themeVS2015Light;
		SetCommandBarsTheme(xtpThemeVisualStudio2015, xtpIniVisualStudio2015Light);
		SetDockingPaneTheme(xtpPaneThemeVisualStudio2015, xtpPaneStickerStyleVisualStudio2015Light, XTP_DPI_X(5));
		break;

	case ID_THEME_VC14_DARK:
		theApp.m_theme = themeVS2015Dark;
		SetCommandBarsTheme(xtpThemeVisualStudio2015, xtpIniVisualStudio2015Dark);
		SetDockingPaneTheme(xtpPaneThemeVisualStudio2015, xtpPaneStickerStyleVisualStudio2015Dark, XTP_DPI_X(5));
		break;

	case ID_THEME_VC14_BLUE:
		theApp.m_theme = themeVS2015Blue;
		SetCommandBarsTheme(xtpThemeVisualStudio2015, xtpIniVisualStudio2015Blue);
		SetDockingPaneTheme(xtpPaneThemeVisualStudio2015, xtpPaneStickerStyleVisualStudio2015Blue, XTP_DPI_X(5));
		break;
	}
}

void CMainFrame::SetCommandBarsTheme(XTPPaintTheme paintTheme, LPCTSTR lpszINI/*=NULL*/)
{
	if (lpszINI != NULL)
		XTPThemeDLL()->SetHandle(lpszINI);
	else
		XTPThemeDLL()->Reset();
	theApp.m_csPane.RefreshMetrics();

	LoadIcons();

	CXTPCommandBars* pCommandBars = GetCommandBars();
	if (!pCommandBars)
		return;

	CXTPPaintManager::SetTheme(paintTheme);

	if (theApp.m_theme <= themeVS2010)
	{
		m_bAllowDwm = TRUE;
		EnableFrameTheme(NULL);
		pCommandBars->SetAllCaps(FALSE);

		for (int i=0; i<pCommandBars->GetCount(); i++)
		{
			CXTPToolBar *pToolBar = pCommandBars->GetAt(i);
			pToolBar->SetFlags(xtpFlagAlignTop | xtpFlagAlignBottom | xtpFlagAlignLeft | xtpFlagAlignRight | xtpFlagFloating, 0);
			pToolBar->SetShowGripper(TRUE);
		}

		SetFrameIcon(0, CSize(16,16));
	}
	else
	{
		m_bAllowDwm = FALSE;
		EnableFrameTheme(pCommandBars);
		pCommandBars->SetAllCaps(theApp.m_theme == themeVS2012Light || theApp.m_theme == themeVS2012Dark);

		for (int i=0; i<pCommandBars->GetCount(); i++)
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

		switch (theApp.m_theme)
		{
		case themeVS2012Light:
		case themeVS2015Light:
			SetFrameIcon(IDI_BLACK, CSize(20,20));
			break;

		case themeVS2012Dark:
		case themeVS2015Dark:
			SetFrameIcon(IDI_WHITE, CSize(20,20));
			break;

		case themeVS2015Blue:
			SetFrameIcon(0, CSize(20,20));
			break;
		}
	}

	// Update tooltip styles.
	CXTPToolTipContext* pToolTipContext = m_wndStatusBar.GetToolTipContext();
	if(NULL != pToolTipContext)
	{
		pToolTipContext->SetStyle(GetToolTipStyle());
	}

	pToolTipContext = GetCommandBars()->GetToolTipContext();
	if(NULL != pToolTipContext)
	{
		pToolTipContext->SetStyle(GetToolTipStyle());
	}	

	pCommandBars->GetPaintManager()->m_bAutoResizeIcons = TRUE;
	pCommandBars->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE);
	pCommandBars->RedrawCommandBars();

	UpdateMDIChildrenTheme();
	
	RedrawWindow(NULL, NULL,
		RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_ALLCHILDREN);
}

void CMainFrame::SetDockingPaneTheme(XTPDockingPanePaintTheme paintTheme, int nStyle /*=-1*/, int nMargin /*=0*/)
{
	BOOL bShowStickers = (nStyle != -1);

	m_paneManager.SetTheme(paintTheme);
	m_paneManager.SetClientMargin(nMargin);
	m_paneManager.SetThemedFloatingFrames(bShowStickers);
	m_paneManager.SetAlphaDockingContext(bShowStickers);
	m_paneManager.SetShowDockingContextStickers(bShowStickers);
	m_paneManager.SetShowContentsWhileDragging(bShowStickers);

	if (bShowStickers)
	{
		m_paneManager.SetDockingContextStickerStyle(
			(XTPDockingContextStickerStyle)nStyle);
	}

	SendMessageToDescendants(WM_REFRESHMETRICS, theApp.m_theme);

	m_paneManager.UpdatePanes();
	m_paneManager.RedrawPanes();

	if (theApp.m_theme > themeVS2008)
	{
 		m_MTIClientWnd.SetFlags(xtpWorkspaceHideClose | xtpWorkspaceHideArrowsAlways | xtpWorkspaceShowActiveFiles | xtpWorkspaceShowCloseTab);
	}
	else
	{
 		m_MTIClientWnd.SetFlags(0);
	}

	m_paneManager.ShowFloatingCaptionMaximizeButton(themeVS2010 <= theApp.m_theme);
}

BOOL CMainFrame::SetFrameIcon(UINT nID, CSize szIcon)
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
				
	if (nID > 0)
	{
		hIcon = (HICON)::LoadImage(theApp.m_hInstance,
			MAKEINTRESOURCE(nID), IMAGE_ICON, szIcon.cx, szIcon.cy, LR_SHARED);
	}
	
	pFramePaintManager->SetIcon(hIcon, szIcon);
	return TRUE;
}

void CMainFrame::OnUpdateTheme(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nTheme ? TRUE : FALSE);
}

void CMainFrame::LoadIcons()
{
	int nMAINFRAME				= IDR_MAINFRAME;
	int nTOOLBAR_WEB			= IDR_TOOLBAR_WEB;
	int nTOOLBAR_EXT			= IDR_TOOLBAR_EXT;
	int nPANE_PROPERTIES		= IDR_PANE_PROPERTIES;
	int nCLASSTREE				= IDB_CLASSTREE;
	int nFILETREE				= IDB_FILETREE;
	int nRESTREE				= IDB_RESTREE;
	int nPANE_SOLUTIONEXPLORER	= IDR_PANE_SOLUTIONEXPLORER;
	int nTOOLBAR_THEME			= IDR_TOOLBAR_THEME;
	int nTOOLBAR_FULLSCREEN     = IDR_TOOLBAR_FULLSCREEN;

	switch(theApp.m_theme)
	{
	case themeVS2012Light:
	case themeVS2015Light:
	case themeVS2015Blue:
		nMAINFRAME				= IDR_MAINFRAME_LIGHT;
		nTOOLBAR_WEB			= IDR_TOOLBAR_WEB_LIGHT;
		nTOOLBAR_EXT			= IDR_TOOLBAR_EXT_LIGHT;
		nPANE_PROPERTIES		= IDR_PANE_PROPERTIES_LIGHT;
		nCLASSTREE				= IDB_CLASSTREE_LIGHT;
		nFILETREE				= IDB_FILETREE_LIGHT;
		nRESTREE				= IDB_RESTREE_LIGHT;
		nPANE_SOLUTIONEXPLORER	= IDR_PANE_SOLUTIONEXPLORER_LIGHT;
		nTOOLBAR_THEME			= IDR_TOOLBAR_THEME_LIGHT;
		nTOOLBAR_FULLSCREEN     = IDR_TOOLBAR_FULLSCREEN_LIGHT;
		break;
	case themeVS2012Dark:
	case themeVS2015Dark:
		nMAINFRAME				= IDR_MAINFRAME_DARK;
		nTOOLBAR_WEB			= IDR_TOOLBAR_WEB_DARK;
		nTOOLBAR_EXT			= IDR_TOOLBAR_EXT_DARK;
		nPANE_PROPERTIES		= IDR_PANE_PROPERTIES_DARK;
		nCLASSTREE				= IDB_CLASSTREE_DARK;
		nFILETREE				= IDB_FILETREE_DARK;
		nRESTREE				= IDB_RESTREE_DARK;
		nPANE_SOLUTIONEXPLORER	= IDR_PANE_SOLUTIONEXPLORER_DARK;
		nTOOLBAR_THEME			= IDR_TOOLBAR_THEME_DARK;
		nTOOLBAR_FULLSCREEN     = IDR_TOOLBAR_FULLSCREEN_DARK;
		break;
	default:
		nMAINFRAME				= IDR_MAINFRAME;
		nTOOLBAR_WEB			= IDR_TOOLBAR_WEB;
		nTOOLBAR_EXT			= IDR_TOOLBAR_EXT;
		nPANE_PROPERTIES		= IDR_PANE_PROPERTIES;
		nCLASSTREE				= IDB_CLASSTREE;
		nFILETREE				= IDB_FILETREE;
		nRESTREE				= IDB_RESTREE;
		nPANE_SOLUTIONEXPLORER	= IDR_PANE_SOLUTIONEXPLORER;
		nTOOLBAR_THEME			= IDR_TOOLBAR_THEME;
		nTOOLBAR_FULLSCREEN     = IDR_TOOLBAR_FULLSCREEN;
		break;
	}

	XTPImageManager()->RemoveAll();

	UINT ui1[] = {ID_WEBBROWSER_BACK,ID_WEBBROWSER_FORWARD,ID_WEBBROWSER_STOP,ID_WEBBROWSER_REFRESH,ID_WEBBROWSER_HOME,ID_WEBBROWSER_SEARCH
		,ID_WEBBROWSER_FAVORITES,ID_WEBBROWSER_ORGANIZE,ID_WEBBROWSER_SYNC,ID_WEBBROWSER_PREV,ID_WEBBROWSER_NEXT,ID_WEBBROWSER_FONT,ID_GOTO_URL
	};
	XTPImageManager()->SetIcons(nTOOLBAR_WEB, ui1, _countof(ui1), CSize(16, 16));

	UINT ui2[] = {ID_FILE_NEW_PROJECT,ID_PROJECT_ADDNEWITEM,ID_FILE_OPEN,ID_FILE_SAVE,ID_FILE_SAVE_ALL,ID_EDIT_CUT,ID_EDIT_COPY,ID_EDIT_PASTE
		,ID_EDIT_UNDO,ID_EDIT_REDO,ID_DEBUG_START,ID_EDIT_STATE,ID_EDIT_PLATFORM,ID_FINDANDREPLACE_FINDINFILES,ID_EDIT_FIND_EX,ID_VIEW_SOLUTIONEXPLORER
		,ID_VIEW_PROPERTIESWINDOW,ID_VIEW_RESOURCEVIEW,ID_VIEW_TOOLBOX,ID_VIEW_OTHER
	};
	XTPImageManager()->SetIcons(nMAINFRAME, ui2, _countof(ui2), CSize(16, 16));

	UINT ui3[] = {ID_FILE_NEW,ID_FILE_PRINT,ID_PROJECT_ADDEXISTINGITEM,ID_FILE_NEW_BLANK,ID_FILE_OPENSOLUTION,ID_FILE_CLOSESOLUTION,ID_PROJECT_ADDCLASS,ID_BUILD_BUILDSOLUTION
		,ID_BUILD_COMPILE,ID_DEBUG_STARTWITHOUTDEBUG,ID_WINDOW_NEW,ID_HELP_DYNAMICHELP,ID_WINDOWS_OUTPUT,ID_VIEW_CLASSVIEW
	};
	XTPImageManager()->SetIcons(nTOOLBAR_EXT, ui3, _countof(ui3), CSize(16, 16));

	UINT ui4[] = {ID_PANEPROPERTIES_CATEGORIZED,ID_PANEPROPERTIES_ALPHABETIC,ID_PANEPROPERTIES_PAGES
	};
	XTPImageManager()->SetIcons(nPANE_PROPERTIES, ui4, _countof(ui4), CSize(16, 16));				

	UINT ui5[] = {ID_SOLUTION_PROPERTIES,ID_SOLUTION_ADDNEWFOLDER,ID_SOLUTION_UNHIDEALL
	};
	XTPImageManager()->SetIcons(nPANE_SOLUTIONEXPLORER, ui5, _countof(ui5), CSize(16, 16));

	UINT ui6[] = {ID_VIEW_FULLSCREEN
	};
	XTPImageManager()->SetIcons(nTOOLBAR_FULLSCREEN, ui6, _countof(ui6), CSize(16, 16));

	UINT ui7[] = {ID_THEME_VC6,ID_THEME_VC7,ID_THEME_VC8,ID_THEME_VC9,ID_THEME_VC10,ID_THEME_VC11_LIGHT
		, ID_THEME_VC11_DARK, ID_THEME_VC14_LIGHT, ID_THEME_VC14_DARK, ID_THEME_VC14_BLUE, 0
	};
	XTPImageManager()->SetIcons(nTOOLBAR_THEME, ui7, _countof(ui7), CSize(16, 16));

	if (m_wndClassView.m_ilClassView.DeleteImageList())
	{
		ASSERT(m_wndClassView.m_ilClassView.GetSafeHandle() == NULL);
		if (CreateImageList(m_wndClassView.m_ilClassView, nCLASSTREE))
			m_wndClassView.m_wndClassView.SetImageList( &m_wndClassView.m_ilClassView, TVSIL_NORMAL );
	}

	if (m_wndSolutionExplorer.m_ilSolutionView.DeleteImageList())
	{
		ASSERT(m_wndSolutionExplorer.m_ilSolutionView.GetSafeHandle() == NULL);
		if (CreateImageList(m_wndSolutionExplorer.m_ilSolutionView, nFILETREE))
			m_wndSolutionExplorer.m_wndSolutionView.SetImageList( &m_wndSolutionExplorer.m_ilSolutionView, TVSIL_NORMAL );
	}

	if (m_wndResourceView.m_ilResourceView.DeleteImageList())
	{
		ASSERT(m_wndResourceView.m_ilResourceView.GetSafeHandle() == NULL);
		if (CreateImageList(m_wndResourceView.m_ilResourceView, nRESTREE))
			m_wndResourceView.m_wndResourceView.SetImageList( &m_wndResourceView.m_ilResourceView, TVSIL_NORMAL );
	}
}

XTPToolTipStyle CMainFrame::GetToolTipStyle() const
{
	XTPToolTipStyle style;

	switch(theApp.m_theme)
	{
		case themeVS6:
		case themeVS2003:
		case themeVS2005:
			style = xtpToolTipResource;
			break;

		default:
			style = xtpToolTipStandard;
			break;
	}

	return style;
}
