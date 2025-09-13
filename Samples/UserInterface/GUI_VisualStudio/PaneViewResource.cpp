// PaneViewResource.cpp 
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
#include "PaneViewResource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaneViewResource

CPaneViewResource::CPaneViewResource()
{
}

CPaneViewResource::~CPaneViewResource()
{
}


BEGIN_MESSAGE_MAP(CPaneViewResource, CPaneWnd)
	//{{AFX_MSG_MAP(CPaneViewResource)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPaneViewResource message handlers

int CPaneViewResource::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (m_wndResourceView.GetSafeHwnd() == 0)
	{
		if (!m_wndResourceView.Create( WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS,
			CRect(0,0,0,0), this, 0xFF ))
		{
			TRACE0( "Unable to create tree control.\n" );
			return 0;
		}

		// load the tree images bitmap and add it to the image list.
		if (!CreateImageList(m_ilResourceView, IDB_RESTREE))
			return 0;

		// Set the image list for the tree control.
		m_wndResourceView.SetImageList( &m_ilResourceView, TVSIL_NORMAL );

		// add the parent item
		HTREEITEM htItem = m_wndResourceView.InsertItem(_T("XtremeDemo resources"), 0, 1);
		m_wndResourceView.SetItemState(htItem, TVIS_BOLD, TVIS_BOLD);

		HTREEITEM hti = m_wndResourceView.InsertItem(_T("Accelerator"), 0, 1, htItem);
		m_wndResourceView.InsertItem(_T("IDR_MAINFRAME"), 2, 2, hti);
		m_wndResourceView.Expand(hti, TVE_EXPAND);

		hti = m_wndResourceView.InsertItem(_T("Dialog"), 0, 1, htItem);
		m_wndResourceView.InsertItem(_T("IDD_ABOUTBOX"), 3, 3, hti);

		hti = m_wndResourceView.InsertItem(_T("Icon"), 0, 1, htItem);
		m_wndResourceView.InsertItem(_T("IDR_MAINFRAME"), 4, 4, hti);
		m_wndResourceView.InsertItem(_T("IDR_XTREMETYPE"), 4, 4, hti);

		hti = m_wndResourceView.InsertItem(_T("Menu"), 0, 1, htItem);
		m_wndResourceView.InsertItem(_T("IDR_MAINFRAME"), 5, 5, hti);
		m_wndResourceView.InsertItem(_T("IDR_XTREMETYPE"), 5, 5, hti);

		hti = m_wndResourceView.InsertItem(_T("String Table"), 0, 1, htItem);
		m_wndResourceView.InsertItem(_T("String Table"), 6, 6, hti);

		hti = m_wndResourceView.InsertItem(_T("Toolbar"), 0, 1, htItem);
		m_wndResourceView.InsertItem(_T("IDR_MAINFRAME"), 7, 7, hti);

		hti = m_wndResourceView.InsertItem(_T("Version"), 0, 1, htItem);
		m_wndResourceView.InsertItem(_T("VS_VERSION_INFO"), 8, 8, hti);

		m_wndResourceView.Expand (htItem, TVE_EXPAND);
	}

	return 0;
}

void CPaneViewResource::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	MoveChildren(NULL, &m_wndResourceView, cx, cy);
}

void CPaneViewResource::OnSetFocus(CWnd* /*pOldWnd*/)
{
	m_wndResourceView.SetFocus();
}

void CPaneViewResource::RefreshMetrics(AppTheme nTheme)
{
	CPaneWnd::RefreshMetrics(nTheme);

	switch (nTheme)
	{
	case themeVS6:
		m_wndResourceView.SetTheme(xtpControlThemeDefault);
		m_wndResourceView.ModifyStyle(0, TVS_HASLINES);

		if (XTPSystemVersion()->IsWinVistaOrGreater())
		{
			m_wndResourceView.SetExplorerTheme(FALSE);
		}
		break;
	case themeVS2003:
		m_wndResourceView.SetTheme(xtpControlThemeVisualStudio2005);
		m_wndResourceView.ModifyStyle(0, TVS_HASLINES);

		if (XTPSystemVersion()->IsWinVistaOrGreater())
		{
			m_wndResourceView.SetExplorerTheme(FALSE);
		}
		break;
	case themeVS2005:
		m_wndResourceView.SetTheme(xtpControlThemeVisualStudio2005);
		m_wndResourceView.ModifyStyle(0, TVS_HASLINES);

		if (XTPSystemVersion()->IsWinVistaOrGreater())
		{
			m_wndResourceView.SetExplorerTheme(FALSE);
		}
		break;
	case themeVS2008:
		{
			m_wndResourceView.SetTheme(xtpControlThemeVisualStudio2008);
			m_wndResourceView.ModifyStyle(0, TVS_HASLINES);

			if (XTPSystemVersion()->IsWinVistaOrGreater())
			{
				m_wndResourceView.SetExplorerTheme(FALSE);
			}
		}
		break;
	case themeVS2010:
		m_wndResourceView.SetTheme(xtpControlThemeVisualStudio2010);
		m_wndResourceView.ModifyStyle(TVS_HASLINES, 0);

		if (XTPSystemVersion()->IsWinVistaOrGreater())
		{
			m_wndResourceView.SetExplorerTheme(TRUE);
		}
		break;
	case themeVS2012Light:
		m_wndResourceView.SetTheme(xtpControlThemeVisualStudio2012Light);
		m_wndResourceView.ModifyStyle(TVS_HASLINES, 0);

		if (XTPSystemVersion()->IsWinVistaOrGreater())
		{
			m_wndResourceView.SetExplorerTheme(TRUE);
		}
		break;
	case themeVS2012Dark:
		m_wndResourceView.SetTheme(xtpControlThemeVisualStudio2012Dark);
		m_wndResourceView.ModifyStyle(TVS_HASLINES, 0);

		if (XTPSystemVersion()->IsWinVistaOrGreater())
		{
			m_wndResourceView.SetExplorerTheme(TRUE);
		}
		break;
	case themeVS2015Light:
	case themeVS2015Dark:
	case themeVS2015Blue:
		{
			m_wndResourceView.SetTheme(xtpControlThemeVisualStudio2015);
			m_wndResourceView.ModifyStyle(TVS_HASLINES, 0);

			if (XTPSystemVersion()->IsWinVistaOrGreater())
			{
				m_wndResourceView.SetExplorerTheme(TRUE);
			}
		}
		break;
	}

	CXTPClientRect rClient(this);
	MoveChildren(NULL, &m_wndResourceView, rClient.Width(), rClient.Height());
}
