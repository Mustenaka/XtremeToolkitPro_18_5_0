// ViewFrame.cpp 
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
#include "ScrollBar.h"
#include "ViewFrame.h"
#include "AboutDlg.h"
#include "PictureView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewFrame dialog

CViewFrame::CViewFrame()
	: m_bFirstShow(TRUE)
{
}

void CViewFrame::SetScrollBarTheme(XTPScrollBarTheme theme)
{
	m_wndSplitter.SetScrollBarTheme(theme);
	RedrawWindow(NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

void CViewFrame::PostNcDestroy()
{
}

BOOL CViewFrame::CreateSplitter()
{
	ASSERT(!::IsWindow(m_wndSplitter));

	CCreateContext ctx;
	ctx.m_pNewViewClass = RUNTIME_CLASS(CPictureView);
	return m_wndSplitter.Create(this, 2, 2, CSize(1, 1), &ctx);
}

BEGIN_MESSAGE_MAP(CViewFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CViewFrame)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewFrame message handlers

int CViewFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
	{
		TRACE0("CViewFrame window creation failed");
		return -1;
	}

	if(!CreateSplitter())
	{
		TRACE0("Failed to create CXTPSplitterWnd window");
		return -1;
	}

	return 0;
}

void CViewFrame::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CFrameWnd::OnShowWindow(bShow, nStatus);

	if(m_bFirstShow)
	{
		m_bFirstShow = FALSE;

		CRect rcClient;
		GetClientRect(&rcClient);
		m_wndSplitter.SplitColumn(rcClient.Width() / 2);
		m_wndSplitter.SplitRow(rcClient.Height() / 2);
	}
}
