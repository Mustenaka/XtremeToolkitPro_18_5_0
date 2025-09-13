// PaneViewClass.cpp 
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
#include "PaneViewClass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaneViewClass

CPaneViewClass::CPaneViewClass()
{
}

CPaneViewClass::~CPaneViewClass()
{
}

BEGIN_MESSAGE_MAP(CPaneViewClass, CPaneWnd)
	//{{AFX_MSG_MAP(CPaneViewClass)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_PROJECT_ADDEXISTINGITEM, OnProjectAddexistingitem)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT toolbar[] =
{
	ID_PROJECT_ADDEXISTINGITEM
};

/////////////////////////////////////////////////////////////////////////////
// CPaneViewClass message handlers

int CPaneViewClass::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	VERIFY(m_wndToolBar.CreateToolBar(WS_TABSTOP | WS_VISIBLE | WS_CHILD | CBRS_TOOLTIPS, this));
	m_wndToolBar.SetButtons(toolbar, 1);

	if (m_wndClassView.GetSafeHwnd() == 0)
	{
		if (!m_wndClassView.Create(WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS,
			CRect(0,0,0,0), this, 0xFF ))
		{
			TRACE0( "Unable to create tree control.\n" );
			return 0;
		}

		if (!CreateImageList(m_ilClassView, IDB_CLASSTREE))
			return 0;

		// Set the image list for the tree control.
		m_wndClassView.SetImageList( &m_ilClassView, TVSIL_NORMAL );

		// Add the parent item
		HTREEITEM htItem = m_wndClassView.InsertItem(_T("XtremeDemo classes"));
		m_wndClassView.SetItemState( htItem, TVIS_BOLD, TVIS_BOLD );

		// Add children
		HTREEITEM hti = m_wndClassView.InsertItem(_T("CAboutDlg"), 3, 3, htItem);
		m_wndClassView.InsertItem(_T("CAboutDlg()"), 4, 4, hti);
		m_wndClassView.InsertItem(_T("DoDataExchange(CDataExchange *pDX)"), 5, 5, hti);

		hti = m_wndClassView.InsertItem(_T("CChildFrame"), 3, 3, htItem);
		m_wndClassView.InsertItem(_T("AssertValid()"), 4, 4, hti);
		m_wndClassView.InsertItem(_T("CChildFrame()"), 4, 4, hti);
		m_wndClassView.InsertItem(_T("~CChildFrame()"), 4, 4, hti);
		m_wndClassView.InsertItem(_T("Dump(CDumpContext &dc)"), 4, 4, hti);
		m_wndClassView.InsertItem(_T("PreCreateWindow(CREATESTRUCT& cs)"), 4, 4, hti);

		hti = m_wndClassView.InsertItem(_T("CMainFrame"), 3, 3, htItem);
		m_wndClassView.InsertItem(_T("AssertValid()"), 4, 4, hti);
		m_wndClassView.InsertItem(_T("CMainFrame()"), 4, 4, hti);
		m_wndClassView.InsertItem(_T("~CMainFrame()"), 4, 4, hti);
		m_wndClassView.InsertItem(_T("Dump(CDumpContext &dc)"), 4, 4, hti);
		m_wndClassView.InsertItem(_T("OnCreate(LPCREATESTRUCT lpCreateStruct)"), 5, 5, hti);
		m_wndClassView.InsertItem(_T("PreCreateWindow(CREATESTRUCT& cs)"), 4, 4, hti);
		m_wndClassView.InsertItem(_T("m_wndStatusBar"), 7, 7, hti);
		m_wndClassView.InsertItem(_T("m_wndToolBar"), 7, 7, hti);

		hti = m_wndClassView.InsertItem(_T("CXtremeDemoApp"), 3, 3, htItem);
		m_wndClassView.InsertItem(_T("CXtremeDemoApp()"), 4, 4, hti);
		m_wndClassView.InsertItem(_T("InitInstance()"), 4, 4, hti);
		m_wndClassView.InsertItem(_T("OnAppAbout()"), 4, 4, hti);

		hti = m_wndClassView.InsertItem(_T("CXtremeDemoDoc"), 3, 3, htItem);
		m_wndClassView.InsertItem(_T("AssertValid()"), 5, 5, hti);
		m_wndClassView.InsertItem(_T("CXtremeDemoDoc()"), 4, 4, hti);
		m_wndClassView.InsertItem(_T("~CXtremeDemoDoc()"), 4, 4, hti);
		m_wndClassView.InsertItem(_T("Dump(CDumpContext &dc)"), 4, 4, hti);
		m_wndClassView.InsertItem(_T("OnNewDocument()"), 4, 4, hti);
		m_wndClassView.InsertItem(_T("Serialize(CArchive& ar)"), 4, 4, hti);

		hti = m_wndClassView.InsertItem(_T("CXtremeDemoView"), 3, 3, htItem);
		m_wndClassView.InsertItem(_T("AssertValid()"), 4, 4, hti);
		m_wndClassView.InsertItem(_T("CXtremeDemoView()"), 5, 5, hti);
		m_wndClassView.InsertItem(_T("~CXtremeDemoView()"), 4, 4, hti);
		m_wndClassView.InsertItem(_T("Dump(CDumpContext& dc)"), 4, 4, hti);
		m_wndClassView.InsertItem(_T("GetDocument()"), 4, 4, hti);
		m_wndClassView.InsertItem(_T("OnBeginPrinting(CDC* pDC, CPrintInfo *pInfo)"), 5, 5, hti);
		m_wndClassView.InsertItem(_T("OnDraw(CDC *pDC)"), 4, 4, hti);
		m_wndClassView.InsertItem(_T("OnEndPrinting(CDC *pDC, CPrintInfo *pInfo)"), 5, 5, hti);
		m_wndClassView.InsertItem(_T("OnPreparePrinting(CPrintInfo *pInfo)"), 5, 5, hti);
		m_wndClassView.InsertItem(_T("PreCreateWindow(CREATESTRUCT &cs)"), 4, 4, hti);

		hti = m_wndClassView.InsertItem(_T("Globals"), 1, 2, htItem);
		m_wndClassView.InsertItem(_T("theApp"), 6, 6, hti);
		m_wndClassView.Expand(hti, TVE_EXPAND);

		m_wndClassView.Expand(htItem, TVE_EXPAND);
	}

	return 0;
}

void CPaneViewClass::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	MoveChildren(&m_wndToolBar, &m_wndClassView, cx, cy);
}

void CPaneViewClass::OnProjectAddexistingitem()
{
	// TODO: Add your command handler code here

}

void CPaneViewClass::OnSetFocus(CWnd* /*pOldWnd*/)
{
	m_wndClassView.SetFocus();
}

void CPaneViewClass::RefreshMetrics(AppTheme nTheme)
{
	CPaneWnd::RefreshMetrics(nTheme);

	switch (nTheme)
	{
	case themeVS6:
		m_wndClassView.SetTheme(xtpControlThemeDefault);
		m_wndClassView.ModifyStyle(0, TVS_HASLINES);

		if (XTPSystemVersion()->IsWinVistaOrGreater())
		{
			m_wndClassView.SetExplorerTheme(FALSE);
		}
		break;
	case themeVS2003:
		m_wndClassView.SetTheme(xtpControlThemeVisualStudio2005);
		m_wndClassView.ModifyStyle(0, TVS_HASLINES);

		if (XTPSystemVersion()->IsWinVistaOrGreater())
		{
			m_wndClassView.SetExplorerTheme(FALSE);
		}
		break;
	case themeVS2005:
		m_wndClassView.SetTheme(xtpControlThemeVisualStudio2005);
		m_wndClassView.ModifyStyle(0, TVS_HASLINES);

		if (XTPSystemVersion()->IsWinVistaOrGreater())
		{
			m_wndClassView.SetExplorerTheme(FALSE);
		}
		break;
	case themeVS2008:
		{
			m_wndClassView.SetTheme(xtpControlThemeVisualStudio2008);
			m_wndClassView.ModifyStyle(0, TVS_HASLINES);

			if (XTPSystemVersion()->IsWinVistaOrGreater())
			{
				m_wndClassView.SetExplorerTheme(FALSE);
			}
		}
		break;
	case themeVS2010:
		m_wndClassView.SetTheme(xtpControlThemeVisualStudio2010);
		m_wndClassView.ModifyStyle(TVS_HASLINES, 0);

		if (XTPSystemVersion()->IsWinVistaOrGreater())
		{
			m_wndClassView.SetExplorerTheme(TRUE);
		}
		break;
	case themeVS2012Light:
		m_wndClassView.SetTheme(xtpControlThemeVisualStudio2012Light);
		m_wndClassView.ModifyStyle(TVS_HASLINES, 0);

		if (XTPSystemVersion()->IsWinVistaOrGreater())
		{
			m_wndClassView.SetExplorerTheme(TRUE);
		}
		break;
	case themeVS2012Dark:
		m_wndClassView.SetTheme(xtpControlThemeVisualStudio2012Dark);
		m_wndClassView.ModifyStyle(TVS_HASLINES, 0);

		if (XTPSystemVersion()->IsWinVistaOrGreater())
		{
			m_wndClassView.SetExplorerTheme(TRUE);
		}
		break;
	case themeVS2015Light:
	case themeVS2015Dark:
	case themeVS2015Blue:
		{
			m_wndClassView.SetTheme(xtpControlThemeVisualStudio2015);
			m_wndClassView.ModifyStyle(TVS_HASLINES, 0);

			if (XTPSystemVersion()->IsWinVistaOrGreater())
			{
				m_wndClassView.SetExplorerTheme(TRUE);
			}
		}
		break;
	}

	CXTPClientRect rClient(this);
	MoveChildren(&m_wndToolBar, &m_wndClassView, rClient.Width(), rClient.Height());
}
