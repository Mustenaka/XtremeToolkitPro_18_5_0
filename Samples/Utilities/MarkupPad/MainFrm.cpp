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
#include "MarkupPad.h"
#include "MarkupPadEdit.h"
#include "MarkupPadView.h"

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
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP

	ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify)
	ON_COMMAND(ID_VIEW_RTL, CMainFrame::OnViewRTL)
	ON_UPDATE_COMMAND_UI(ID_VIEW_RTL, CMainFrame::OnUpdateViewRTL)
	ON_COMMAND(ID_SMOOTHINGMODE_APPLYTOTEXT, OnSmoothingModeApplyToText)
	ON_UPDATE_COMMAND_UI(ID_SMOOTHINGMODE_APPLYTOTEXT, OnUpdateSmoothingModeApplyToText)
	ON_COMMAND_RANGE(ID_SMOOTHINGMODE_DEFAULT, ID_SMOOTHINGMODE_NONE, OnSmoothingMode)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SMOOTHINGMODE_DEFAULT, ID_SMOOTHINGMODE_NONE, OnUpdateSmoothingMode)
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
	: m_bRTL(FALSE)
	, m_DefaultSmoothingMode(xtpMarkupSmoothingDefault)
	, m_bDefaultTextSmoothing(FALSE)
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create Status bar.
	// Important: All control bars including the Status Bar
	// must be created before CommandBars....
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.EnableMarkup();

	// Initialize the command bars
	if (!InitCommandBars())
		return -1;

	// Get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if(pCommandBars == NULL)
	{
		TRACE0("Failed to create command bars object.\n");
		return -1;      // fail to create
	}

	// Add the menu bar
	CXTPCommandBar* pMenuBar = pCommandBars->SetMenu(
		_T("Menu Bar"), IDR_MAINFRAME);
	if(pMenuBar == NULL)
	{
		TRACE0("Failed to create menu bar.\n");
		return -1;      // fail to create
	}

	// Create ToolBar
	CXTPToolBar* pToolBar = (CXTPToolBar*)
		pCommandBars->Add(_T("Standard"), xtpBarTop);
	if (!pToolBar || !pToolBar->LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	pCommandBars->GetCommandBarsOptions()->ShowKeyboardCues(xtpKeyboardCuesShowWindowsDefault);

	// Set Office 2003 Theme
	CXTPPaintManager::SetTheme(xtpThemeVisualStudio2005);

	pCommandBars->GetPaintManager()->m_bAutoResizeIcons = TRUE;
	pCommandBars->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE);

	m_paneManager.InstallDockingPanes(this);
	m_paneManager.SetTheme(xtpPaneThemeVisualStudio2005);

	CXTPDockingPane* pPaneEdit = m_paneManager.CreatePane(
		1, XTP_DPI(CRect(0, 0,200, 200)), xtpPaneDockBottom);
	pPaneEdit->SetTitle(_T("Markup"));
	pPaneEdit->SetOptions(xtpPaneNoCloseable);


	return 0;
}

void CMainFrame::OnViewRTL()
{
	m_bRTL = !m_bRTL;

	// Apply RTL style to the views
	CDocument* pActiveDoc = GetActiveDocument();
	if (NULL != pActiveDoc)
	{
		POSITION pos = pActiveDoc->GetFirstViewPosition();
		while (NULL != pos)
		{
			CView* pView = pActiveDoc->GetNextView(pos);
			if (NULL != pView)
			{
				pView->ModifyStyleEx(!m_bRTL ? WS_EX_LAYOUTRTL : 0, m_bRTL ? WS_EX_LAYOUTRTL : 0);
			}
		}
	}

	// Apply RTL style to other components
	if (m_bRTL)
	{
		ModifyStyleEx(0, WS_EX_LAYOUTRTL);
		m_paneManager.ModifyStyleEx(0, WS_EX_LAYOUTRTL);
		m_pEditView->ModifyStyleEx(0, WS_EX_LAYOUTRTL);
	}
	else
	{
		ModifyStyleEx(WS_EX_LAYOUTRTL, 0);
		m_paneManager.ModifyStyleEx(WS_EX_LAYOUTRTL, 0);
		m_pEditView->ModifyStyleEx(WS_EX_LAYOUTRTL, 0);
	}

	GetCommandBars()->SetLayoutRTL(m_bRTL);

	// Enforce re-drawing
	static_cast<CMarkupPadEdit*>(m_pEditView)->OnChange();

	m_paneManager.RedrawPanes();

	m_pEditView->Invalidate();
	m_pEditView->UpdateWindow();

	Invalidate();
	UpdateWindow();
}

void CMainFrame::OnUpdateViewRTL(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bRTL);
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.lpszClass = _T("XTPMainFrame");
	CXTPDrawHelpers::RegisterWndClass(AfxGetInstanceHandle(), cs.lpszClass, 
		CS_DBLCLKS, AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

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


LRESULT CMainFrame::OnDockingPaneNotify(WPARAM wParam, LPARAM lParam)
{
	if (wParam == XTP_DPN_SHOWWINDOW)
	{
		// get a pointer to the docking pane being shown.
		CXTPDockingPane* pPane = (CXTPDockingPane*)lParam;

		if (!pPane->IsValid())
		{
			pPane->Attach(m_pEditView);
		}

		return TRUE; // handled
	}


	return FALSE;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	if (!CFrameWnd::OnCreateClient(lpcs, pContext))
		return FALSE;

	pContext->m_pNewViewClass = RUNTIME_CLASS(CMarkupPadEdit);
	m_pEditView = (CView*)CreateView(pContext);
	m_pEditView->SetDlgCtrlID(0);

	return TRUE;
}


void CMainFrame::OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState)
{
	// Toggle CommandBars
	GetCommandBars()->OnSetPreviewMode(bPreview);

	// Toggle Docking Panes.
	m_paneManager.OnSetPreviewMode(bPreview);

	CFrameWnd::OnSetPreviewMode(bPreview, pState);
}

void CMainFrame::OnSmoothingModeApplyToText()
{
	m_bDefaultTextSmoothing = !m_bDefaultTextSmoothing;
	UpdateMarkupViews();
}

void CMainFrame::OnUpdateSmoothingModeApplyToText(CCmdUI *pCmdUI)
{
	ASSERT(NULL != pCmdUI);
	pCmdUI->SetCheck(m_bDefaultTextSmoothing);
}

void CMainFrame::OnSmoothingMode(UINT nCommand)
{
	switch (nCommand)
	{
	case ID_SMOOTHINGMODE_DEFAULT:
		m_DefaultSmoothingMode = xtpMarkupSmoothingDefault;
		break;
	case ID_SMOOTHINGMODE_HIGHSPEED:
		m_DefaultSmoothingMode = xtpMarkupSmoothingHighSpeed;
		break;
	case ID_SMOOTHINGMODE_HIGHQUALITY:
		m_DefaultSmoothingMode = xtpMarkupSmoothingHighQuality;
		break;
	case ID_SMOOTHINGMODE_ANTIALIASING:
		m_DefaultSmoothingMode = xtpMarkupSmoothingAntiAlias;
		break;
	case ID_SMOOTHINGMODE_NONE:
		m_DefaultSmoothingMode = xtpMarkupSmoothingNone;
		break;
	default:
		ASSERT(!"Unexpected ID");
		break;
	}

	UpdateMarkupViews();
}

void CMainFrame::OnUpdateSmoothingMode(CCmdUI* pCmdUI)
{
	ASSERT(NULL != pCmdUI);

	XTPMarkupSmoothingMode mode = xtpMarkupSmoothingDefault;
	switch (pCmdUI->m_nID)
	{
	case ID_SMOOTHINGMODE_DEFAULT:
		mode = xtpMarkupSmoothingDefault;
		break;
	case ID_SMOOTHINGMODE_HIGHSPEED:
		mode = xtpMarkupSmoothingHighSpeed;
		break;
	case ID_SMOOTHINGMODE_HIGHQUALITY:
		mode = xtpMarkupSmoothingHighQuality;
		break;
	case ID_SMOOTHINGMODE_ANTIALIASING:
		mode = xtpMarkupSmoothingAntiAlias;
		break;
	case ID_SMOOTHINGMODE_NONE:
		mode = xtpMarkupSmoothingNone;
		break;
	default:
		ASSERT(!"Unexpected ID");
		break;
	}

	pCmdUI->SetCheck(m_DefaultSmoothingMode == mode);
}

void CMainFrame::UpdateMarkupViews()
{
	CDocument* pActiveDoc = GetActiveDocument();
	if (NULL != pActiveDoc)
	{
		POSITION pos = pActiveDoc->GetFirstViewPosition();
		while (NULL != pos)
		{
			CView* pView = pActiveDoc->GetNextView(pos);
			if (NULL != pView)
			{
				CMarkupPadView* pMarkupView = DYNAMIC_DOWNCAST(CMarkupPadView, pView);
				if (NULL != pMarkupView)
				{
					pMarkupView->SetDefaultSmoothingMode(m_DefaultSmoothingMode);
					pMarkupView->SetDefaultTextSmoothing(m_bDefaultTextSmoothing);
					pMarkupView->Invalidate();
				}
			}
		}
	}
}
