// ShortcutBarSplitter.cpp
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
#include "shortcutbar.h"
#include "ShortcutBarSplitter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShortcutBarSplitter

IMPLEMENT_DYNCREATE(CShortcutBarSplitter, CXTPSplitterWndEx)

CShortcutBarSplitter::CShortcutBarSplitter()
{
#ifdef _XTP_INCLUDE_CONTROLS
	m_bShowTopBorder = FALSE;
	m_cyTopBorderGap = 2;
#endif
}

CShortcutBarSplitter::~CShortcutBarSplitter()
{
}

BEGIN_MESSAGE_MAP(CShortcutBarSplitter, CXTPSplitterWndEx)
	//{{AFX_MSG_MAP(CShortcutBarSplitter)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShortcutBarSplitter message handlers

void CShortcutBarSplitter::TrackColumnSize(int x, int col)
{
	ASSERT_VALID(this);
	ASSERT(m_nCols > 1);
	
	CPoint pt(x, 0);
	ClientToScreen(&pt);
	GetPane(0, col)->ScreenToClient(&pt);
	m_pColInfo[col].nIdealSize = pt.x;      // new size
	if (pt.x < XTP_DPI_X(32))
	{
		// resized too small
		m_pColInfo[col].nIdealSize = XTP_DPI_X(32); // make it go away
	}
}