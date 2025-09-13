// PictureView.cpp 
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
#include "PictureView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CPictureView, CView);

CPictureView::CPictureView()
{
}

BEGIN_MESSAGE_MAP(CPictureView, CView)
	//{{AFX_MSG_MAP(CPictureView)
	ON_WM_CREATE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int CPictureView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	if(m_Image.LoadBitmap(IDB_BITMAP))
	{
		GetObject(m_Image.m_hObject, sizeof(m_bmpInfo), &m_bmpInfo);
		SCROLLINFO si = { 0 };
		si.cbSize = sizeof(si);
		si.fMask = SIF_ALL;
		si.nMax = m_bmpInfo.bmWidth;
		si.nPage = m_bmpInfo.bmWidth / 10;
		SetScrollInfo(SB_HORZ, &si);
		EnableScrollBarCtrl(SB_HORZ);

		si.nMax = m_bmpInfo.bmHeight;
		si.nPage = m_bmpInfo.bmHeight / 10;
		SetScrollInfo(SB_VERT, &si);
		EnableScrollBarCtrl(SB_VERT);
	}
	else
	{
		TRACE0("Failed to load IDB_BITMAP");
	}

	return 0;
}


void CPictureView::OnDraw(CDC* pDC)
{
	int xScroll = GetScrollPos(SB_HORZ);
	int yScroll = GetScrollPos(SB_VERT);

	CDC memDC;
	if(memDC.CreateCompatibleDC(pDC))
	{
		memDC.SelectObject(&m_Image);
		pDC->BitBlt(-xScroll, -yScroll, 
			m_bmpInfo.bmWidth, m_bmpInfo.bmHeight, 
			&memDC, 0, 0, SRCCOPY);
		memDC.DeleteDC();
	}
}

void CPictureView::OnScroll(int nBar, UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// Get the minimum and maximum scroll-bar positions. 
	int minpos;
	int maxpos;
	GetScrollRange(nBar, &minpos, &maxpos); 
	maxpos = GetScrollLimit(nBar);

	// Get the current position of scroll box. 
	int curpos = GetScrollPos(nBar);

	// Determine the new position of scroll box. 
	switch (nSBCode)
	{
	case SB_LEFT:      // Scroll to far left.
		curpos = minpos;
		break;
	case SB_RIGHT:      // Scroll to far right.
		curpos = maxpos;
		break;
	case SB_LINELEFT:      // Scroll left. 
		if(curpos > minpos)
		{
			curpos--;
		}
		break;
	case SB_LINERIGHT:   // Scroll right. 
		if(curpos < maxpos)
		{
			curpos++;
		}
		break;
	case SB_PAGELEFT:    // Scroll one page left.
		{
			// Get the page size. 
			SCROLLINFO   info;
			GetScrollInfo(nBar, &info, SIF_ALL);
			if(curpos > minpos)
			{
				curpos = __max(minpos, curpos - (int)info.nPage);
			}
		}
		break;
	case SB_PAGERIGHT:      // Scroll one page right.
		{
			// Get the page size. 
			SCROLLINFO   info;
			GetScrollInfo(nBar, &info, SIF_ALL);
			if(curpos < maxpos)
			{
				curpos = __min(maxpos, curpos + (int)info.nPage);
			}
		}
		break;
	case SB_THUMBPOSITION: // Scroll to absolute position. nPos is the position
		curpos = nPos;      // of the scroll box at the end of the drag operation. 
		break;
	case SB_THUMBTRACK:   // Drag scroll box to specified position. nPos is the
		curpos = nPos;     // position that the scroll box has been dragged to. 
		break;
	}

	// Set the new position of the thumb (scroll box).
	SetScrollPos(nBar, curpos);
}

void CPictureView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	OnScroll(SB_HORZ, nSBCode, nPos, pScrollBar);
	CView::OnHScroll(nSBCode, nPos, pScrollBar);
	RedrawWindow();
}


void CPictureView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	OnScroll(SB_VERT, nSBCode, nPos, pScrollBar);
	CView::OnVScroll(nSBCode, nPos, pScrollBar);
	RedrawWindow();
}
