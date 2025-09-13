// PaneViewSolution.cpp
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
#include "PaneViewSolution.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaneViewSolution

CPaneViewSolution::CPaneViewSolution()
{
}

CPaneViewSolution::~CPaneViewSolution()
{
}


BEGIN_MESSAGE_MAP(CPaneViewSolution, CPaneWnd)
	//{{AFX_MSG_MAP(CPaneViewSolution)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND_RANGE(ID_SOLUTION_PROPERTIES, ID_SOLUTION_ADDNEWFOLDER, OnEmptyCommand)
	//}}AFX_MSG_MAP
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPaneViewSolution message handlers

int CPaneViewSolution::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	VERIFY(m_wndToolBar.CreateToolBar(WS_TABSTOP|WS_VISIBLE|WS_CHILD|CBRS_TOOLTIPS, this));
	VERIFY(m_wndToolBar.LoadToolBar(IDR_PANE_SOLUTIONEXPLORER));

	if (m_wndSolutionView.GetSafeHwnd() == 0)
	{
		if (!m_wndSolutionView.Create(WS_VISIBLE  | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS/* | TVS_NOSCROLL*/,
			CRect(0,0,0,0), this, 0xFF ))
		{
			TRACE0( "Unable to create tree control.\n" );
			return 0;
		}

		// load the tree images bitmap and add it to the image list.
		if (!CreateImageList(m_ilSolutionView, IDB_FILETREE))
			return 0;

		// Set the image list for the tree control.
		m_wndSolutionView.SetImageList( &m_ilSolutionView, TVSIL_NORMAL );

		// add the parent item, make it bold
		HTREEITEM htiParent = m_wndSolutionView.InsertItem(_T("Solution 'XtremeDemo': 1 project(s)"));
		HTREEITEM htiChild; // child item

		htiChild = m_wndSolutionView.InsertItem (_T("XtremeDemo Files"), 1, 1, htiParent);
		m_wndSolutionView.SetItemState (htiChild, TVIS_BOLD, TVIS_BOLD);

		// add the children of the parent item
		HTREEITEM hti = m_wndSolutionView.InsertItem(_T("Source Files"), 2, 3, htiChild);
		m_wndSolutionView.InsertItem(_T("ChildFrm.cpp"), 4, 4, hti);
		m_wndSolutionView.InsertItem(_T("MainFrm.cpp"), 4, 4, hti);
		m_wndSolutionView.InsertItem(_T("StdAfx.cpp"), 4, 4, hti);
		m_wndSolutionView.InsertItem(_T("XtremeDemo.cpp"), 4, 4, hti);
		m_wndSolutionView.InsertItem(_T("XtremeDemo.rc"), 4, 4, hti);
		m_wndSolutionView.InsertItem(_T("XtremeDemoDoc.cpp"), 4, 4, hti);
		m_wndSolutionView.InsertItem(_T("XtremeDemoView.cpp"), 4, 4, hti);

		hti = m_wndSolutionView.InsertItem(_T("Header Files"), 2, 3, htiChild);
		m_wndSolutionView.InsertItem(_T("ChildFrm.h"), 5, 5, hti);
		m_wndSolutionView.InsertItem(_T("MainFrm.h"), 5, 5, hti);
		m_wndSolutionView.InsertItem(_T("Resource.rc"), 5, 5, hti);
		m_wndSolutionView.InsertItem(_T("StdAfx.h"), 5, 5, hti);
		m_wndSolutionView.InsertItem(_T("XtremeDemo.h"), 5, 5, hti);
		m_wndSolutionView.InsertItem(_T("XtremeDemoDoc.h"), 5, 5, hti);
		m_wndSolutionView.InsertItem(_T("XtremeDemoView.h"), 5, 5, hti);

		hti = m_wndSolutionView.InsertItem(_T("Resource Files"), 2, 3, htiChild);
		m_wndSolutionView.InsertItem(_T("Toolbar.bmp"), 5, 5, hti);
		m_wndSolutionView.InsertItem(_T("XtremeDemo.ico"), 5, 5, hti);
		m_wndSolutionView.InsertItem(_T("XtremeDemo.rc2"), 5, 5, hti);
		m_wndSolutionView.InsertItem(_T("XtremeDemoDoc.ico"), 5, 5, hti);

		m_wndSolutionView.InsertItem(_T("ReadMe.txt"), 5, 5, htiChild);
		m_wndSolutionView.InsertItem(_T("External Dependencies"), 2, 3, htiChild);

		m_wndSolutionView.Expand(htiParent, TVE_EXPAND);
		m_wndSolutionView.Expand(htiChild, TVE_EXPAND);
	}
	return 0;
}

void CPaneViewSolution::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	MoveChildren(&m_wndToolBar, &m_wndSolutionView, cx, cy);
}

void CPaneViewSolution::OnEmptyCommand(UINT)
{

}

void CPaneViewSolution::OnSetFocus(CWnd* /*pOldWnd*/)
{
	m_wndSolutionView.SetFocus();
}

void CPaneViewSolution::RefreshMetrics(AppTheme nTheme)
{
	CPaneWnd::RefreshMetrics(nTheme);

	switch (nTheme)
	{
	case themeVS6:
		m_wndSolutionView.SetTheme(xtpControlThemeDefault);
		m_wndSolutionView.ModifyStyle(0, TVS_HASLINES);

		if (XTPSystemVersion()->IsWinVistaOrGreater())
		{
			m_wndSolutionView.SetExplorerTheme(FALSE);
		}
		break;
	case themeVS2003:
		m_wndSolutionView.SetTheme(xtpControlThemeVisualStudio2005);
		m_wndSolutionView.ModifyStyle(0, TVS_HASLINES);

		if (XTPSystemVersion()->IsWinVistaOrGreater())
		{
			m_wndSolutionView.SetExplorerTheme(FALSE);
		}
		break;
	case themeVS2005:
		m_wndSolutionView.SetTheme(xtpControlThemeVisualStudio2005);
		m_wndSolutionView.ModifyStyle(0, TVS_HASLINES);

		if (XTPSystemVersion()->IsWinVistaOrGreater())
		{
			m_wndSolutionView.SetExplorerTheme(FALSE);
		}
		break;
	case themeVS2008:
		{
			m_wndSolutionView.SetTheme(xtpControlThemeVisualStudio2008);
			m_wndSolutionView.ModifyStyle(0, TVS_HASLINES);

			if (XTPSystemVersion()->IsWinVistaOrGreater())
			{
				m_wndSolutionView.SetExplorerTheme(FALSE);
			}
		}
		break;
	case themeVS2010:
		m_wndSolutionView.SetTheme(xtpControlThemeVisualStudio2010);
		m_wndSolutionView.ModifyStyle(TVS_HASLINES, 0);

		if (XTPSystemVersion()->IsWinVistaOrGreater())
		{
			m_wndSolutionView.SetExplorerTheme(TRUE);
		}
		break;
	case themeVS2012Light:
		m_wndSolutionView.SetTheme(xtpControlThemeVisualStudio2012Light);
		m_wndSolutionView.ModifyStyle(TVS_HASLINES, 0);

		if (XTPSystemVersion()->IsWinVistaOrGreater())
		{
			m_wndSolutionView.SetExplorerTheme(TRUE);
		}
		break;
	case themeVS2012Dark:
		m_wndSolutionView.SetTheme(xtpControlThemeVisualStudio2012Dark);
		m_wndSolutionView.ModifyStyle(TVS_HASLINES, 0);

		if (XTPSystemVersion()->IsWinVistaOrGreater())
		{
			m_wndSolutionView.SetExplorerTheme(TRUE);
		}
		break;
	case themeVS2015Light:
	case themeVS2015Dark:
	case themeVS2015Blue:
		{
			m_wndSolutionView.SetTheme(xtpControlThemeVisualStudio2015);
			m_wndSolutionView.ModifyStyle(TVS_HASLINES, 0);

			if (XTPSystemVersion()->IsWinVistaOrGreater())
			{
				m_wndSolutionView.SetExplorerTheme(TRUE);
			}
		}
		break;
	}

	CXTPClientRect rClient(this);
	MoveChildren(&m_wndToolBar, &m_wndSolutionView, rClient.Width(), rClient.Height());
}
