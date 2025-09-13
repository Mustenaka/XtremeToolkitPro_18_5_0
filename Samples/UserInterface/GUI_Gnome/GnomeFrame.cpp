// GnomeFrame.cpp 
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
#include "GUI_Gnome.h"
#include "GnomeFrame.h"
#include "GnomeTheme.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGnomeFrame

IMPLEMENT_DYNCREATE(CGnomeFrame, CFrameWnd)

CGnomeFrame::CGnomeFrame()
{
	m_rcBorders.SetRect(XTP_DPI_X(4), XTP_DPI_Y(4), XTP_DPI_X(4), XTP_DPI_Y(4));
	m_szTitleBtn = CSize(21, 19);
	m_szRoundRadius = CSize(XTP_DPI_X(11), XTP_DPI_Y(11));
	m_nButtonDown = 0;
}

CGnomeFrame::~CGnomeFrame()
{
}


BEGIN_MESSAGE_MAP(CGnomeFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CGnomeFrame)
	ON_WM_CREATE()
	ON_WM_NCPAINT()
	ON_WM_NCACTIVATE()
	ON_WM_NCCALCSIZE()
	ON_WM_NCHITTEST_EX()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCLBUTTONUP()
	ON_WM_SIZE()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_LBUTTONUP()
	ON_WM_CAPTURECHANGED()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGnomeFrame message handlers




int CGnomeFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetMenu(0);
	ModifyStyle(WS_BORDER | WS_THICKFRAME, 0);

	VERIFY(m_bmpBottomLeft.LoadBitmap(IDB_GNOME_BOTTOMLEFT));
	VERIFY(m_bmpBottomRight.LoadBitmap(IDB_GNOME_BOTTOMRIGHT));
	VERIFY(m_bmpMenuNormal.LoadBitmap(IDB_GNOME_MENU_NORMAL));
	VERIFY(m_bmpCaption.LoadBitmap(IDB_GNOME_CAPTION));
	VERIFY(m_bmpCloseNormal.LoadBitmap(IDB_GNOME_CLOSE_NORMAL));
	VERIFY(m_bmpMaximizeNormal.LoadBitmap(IDB_GNOME_MAXIMIZE_NORMAL));
	VERIFY(m_bmpMinimizeNormal.LoadBitmap(IDB_GNOME_MINIMIZE_NORMAL));

	VERIFY(m_bmpClosePushed.LoadBitmap(IDB_GNOME_CLOSE_PUSHED));
	VERIFY(m_bmpMaximizePushed.LoadBitmap(IDB_GNOME_MAXIMIZE_PUSHED));
	VERIFY(m_bmpMinimizePushed.LoadBitmap(IDB_GNOME_MINIMIZE_PUSHED));

	MoveWindow(CXTPWindowRect(this));

	NONCLIENTMETRICS ncm;

	ZeroMemory(&ncm, sizeof(NONCLIENTMETRICS));
	ncm.cbSize = sizeof(NONCLIENTMETRICS);
	VERIFY(::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0));

	m_fntTitle.CreateFontIndirect(&ncm.lfCaptionFont);

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CGnomeFrame message handlers

#define GNOMECAPTION_HEIGHT 22

void CGnomeFrame::OnNcPaint()
{
	CWindowDC dcWindow(this);
	CXTPWindowRect rc(this);
	CXTPClientRect rcClient(this);
	ClientToScreen(&rcClient);

	rcClient.OffsetRect(-rc.TopLeft());
	rc.OffsetRect(-rc.TopLeft());

	CRgn rgnClient;
	rgnClient.CreateRectRgnIndirect(rcClient);

	CRgn rgnWindow;
	rgnWindow.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, m_szRoundRadius.cx, m_szRoundRadius.cy);

	dcWindow.SelectClipRgn(&rgnWindow);
	dcWindow.SelectClipRgn(&rgnClient, RGN_XOR );
	{
		CXTPBufferDC dc(dcWindow, rc);

		CXTPPenDC pen(dc, 0);
		CXTPBrushDC brush(dc, GNOMECOLOR_3DFACE);
		int nMagic23 = 23;	//without XTP_DPI
		dc.FillSolidRect(0, 0, rc.Width(), rc.Height(), 0);
		dc.RoundRect(0, 0, rc.Width() - XTP_DPI_X(1), rc.Height() - XTP_DPI_Y(1), XTP_DPI_X(14), XTP_DPI_Y(14));

		dc.FillSolidRect(0, m_szTitleBtn.cy, rc.Width(), XTP_DPI_Y(1), RGB(11, 11, 12));
		dc.FillSolidRect(XTP_DPI_X(1), GNOMECAPTION_HEIGHT, XTP_DPI_X(1), rc.Height() - GNOMECAPTION_HEIGHT - XTP_DPI_Y(6), RGB(0xFF, 0xFF, 0xFF));

		dc.FillSolidRect(XTP_DPI_X(5), GNOMECAPTION_HEIGHT, XTP_DPI_X(1), rc.Height() - GNOMECAPTION_HEIGHT - XTP_DPI_Y(6), RGB(161, 161, 161));
		dc.FillSolidRect(rc.Width() - 3, GNOMECAPTION_HEIGHT, XTP_DPI_X(1), rc.Height() - GNOMECAPTION_HEIGHT - XTP_DPI_Y(6), RGB(196, 196, 196));
		dc.FillSolidRect(rc.Width() - 7, GNOMECAPTION_HEIGHT, XTP_DPI_X(1), rc.Height() - GNOMECAPTION_HEIGHT - XTP_DPI_Y(6), RGB(255, 255, 255));
		dc.FillSolidRect(rc.Width() - 8, GNOMECAPTION_HEIGHT, XTP_DPI_X(1), rc.Height() - GNOMECAPTION_HEIGHT - XTP_DPI_Y(6), RGB(161, 161, 161));

		dc.FillSolidRect(XTP_DPI_X(5), rc.Height() - 3, rc.Width() - m_szRoundRadius.cx, XTP_DPI_Y(1), RGB(184, 184, 184));
		dc.FillSolidRect(XTP_DPI_X(5), rc.Height() - 6, rc.Width() - m_szRoundRadius.cx, XTP_DPI_Y(1), RGB(255, 255, 255));
		dc.FillSolidRect(XTP_DPI_X(5), rc.Height() - 7, rc.Width() - m_szRoundRadius.cx, XTP_DPI_Y(1), RGB(161, 161, 161));

		dc.FillSolidRect(XTP_DPI_X(10), XTP_DPI_Y(1), rc.Width() - XTP_DPI_X(20), XTP_DPI_Y(1), RGB(149, 169, 214));

		for (int nCaption = nMagic23; nCaption < rc.Width() - XTP_DPI_X(10); nCaption += 30)
		{
			dc.DrawState(CPoint(nCaption, 2), CSize(30, 17), m_bmpCaption, DST_BITMAP | DSS_NORMAL);
		}

		dc.DrawState(CPoint(XTP_DPI_X(1), rc.Height() - nMagic23), CSize(21, 21), m_bmpBottomLeft, DST_BITMAP | DSS_NORMAL);
		dc.DrawState(CPoint(rc.Width() - nMagic23, rc.Height() - nMagic23), CSize(21, 21), m_bmpBottomRight, DST_BITMAP | DSS_NORMAL);
		dc.DrawState(XTP_DPI(CPoint(1, 1)), CSize(22, 19), m_bmpMenuNormal, DST_BITMAP | DSS_NORMAL);

		dc.DrawState(CPoint(rc.Width() - nMagic23, XTP_DPI_Y(1)), m_szTitleBtn, m_nButtonDown == GNOME_HTCLOSE ? m_bmpClosePushed : m_bmpCloseNormal, DST_BITMAP | DSS_NORMAL);
		dc.DrawState(CPoint(rc.Width() - nMagic23 - m_szTitleBtn.cx, XTP_DPI_Y(1)), m_szTitleBtn, m_nButtonDown == GNOME_HTMAXIMIZE ? m_bmpMaximizePushed : m_bmpMaximizeNormal, DST_BITMAP | DSS_NORMAL);
		dc.DrawState(CPoint(rc.Width() - nMagic23 - m_szTitleBtn.cx * 2, XTP_DPI_Y(1)), m_szTitleBtn, m_nButtonDown == GNOME_HTMINIMIZE ? m_bmpMinimizePushed : m_bmpMinimizeNormal, DST_BITMAP | DSS_NORMAL);

		CRect rcTitle(rc.left + XTP_DPI_X(30), rc.top, 
			rc.right - XTP_DPI_X(70), rc.top + GNOMECAPTION_HEIGHT);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(255, 255, 255));

		CString strTitle;
		GetWindowText(strTitle);

		CXTPFontDC font(&dc, &m_fntTitle);
		dc.DrawText(strTitle, rcTitle, DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOCLIP);

	}


	dcWindow.SelectClipRgn(NULL);
}

void CGnomeFrame::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp)
{
	lpncsp->rgrc[0].top += GNOMECAPTION_HEIGHT - m_rcBorders.top + XTP_DPI_Y(1);
	lpncsp->rgrc[0].left += XTP_DPI_X(6) - m_rcBorders.left;
	lpncsp->rgrc[0].right -= XTP_DPI_X(6) + XTP_DPI_X(1) - m_rcBorders.right;
	lpncsp->rgrc[0].bottom -= XTP_DPI_Y(6) + XTP_DPI_Y(1) - m_rcBorders.bottom;

	CFrameWnd::OnNcCalcSize(bCalcValidRects, lpncsp);
}

LRESULT CGnomeFrame::OnNcHitTest(CPoint point)
{
	LRESULT nHit = (LRESULT)CFrameWnd::OnNcHitTest(point);

	CRect rcWindow;
	GetWindowRect(&rcWindow);

	if (point.y < rcWindow.top + GNOMECAPTION_HEIGHT && nHit == HTNOWHERE)
	{
		return HTCAPTION;
	}

	return nHit;
}

void CGnomeFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);


}

void CGnomeFrame::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CFrameWnd::OnWindowPosChanging(lpwndpos);

	if ((lpwndpos->flags & SWP_NOSIZE) ==  0 )
	{
		CRgn rgnResult;
		rgnResult.CreateRoundRectRgn(0, 0, lpwndpos->cx, lpwndpos->cy, m_szRoundRadius.cx, m_szRoundRadius.cy);

		SetWindowRgn((HRGN)rgnResult.Detach(), TRUE);
	}
}

int CGnomeFrame::GetSysButtonsHitTest(CPoint point)
{
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	int nMagic23 = 23;	//without XTP_DPI
	if (point.y < rcWindow.top + GNOMECAPTION_HEIGHT && (point.x > rcWindow.right - nMagic23))
		return GNOME_HTCLOSE;
	if (point.y < rcWindow.top + GNOMECAPTION_HEIGHT && (point.x > rcWindow.right - nMagic23 - m_szTitleBtn.cx))
		return GNOME_HTMAXIMIZE;
	if (point.y < rcWindow.top + GNOMECAPTION_HEIGHT && (point.x > rcWindow.right - nMagic23 - m_szTitleBtn.cx*2))
		return GNOME_HTMINIMIZE;
	return 0;
}

void CGnomeFrame::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	if (nHitTest == HTCAPTION)
	{
		int nHit = GetSysButtonsHitTest(point);

		if (nHit > 0)
		{
			SetCapture();
			m_nButtonDown = nHit;
			RedrawWindow(0, 0, RDW_FRAME|RDW_INVALIDATE );
		}
	}


	CFrameWnd::OnNcLButtonDown(nHitTest, point);
}

void CGnomeFrame::OnNcLButtonUp(UINT nHitTest, CPoint point)
{

	CFrameWnd::OnNcLButtonUp(nHitTest, point);
}

void CGnomeFrame::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_nButtonDown > 0)
	{
		int nButtonDown = m_nButtonDown;

		m_nButtonDown = 0;
		RedrawWindow(0, 0, RDW_FRAME|RDW_INVALIDATE );
		ReleaseCapture();

		ClientToScreen(&point);

		if (GetSysButtonsHitTest(point) == nButtonDown)
		{
			switch (nButtonDown)
			{
				case GNOME_HTCLOSE: SendMessage(WM_SYSCOMMAND, SC_CLOSE); break;
				case GNOME_HTMAXIMIZE:
					SendMessage(WM_SYSCOMMAND, (GetStyle() & WS_MAXIMIZE) != 0? SC_RESTORE: SC_MAXIMIZE ); break;
				case GNOME_HTMINIMIZE: SendMessage(WM_SYSCOMMAND, SC_MINIMIZE); break;
			}
		}
		return;

	}

	CFrameWnd::OnLButtonUp(nFlags, point);
}

void CGnomeFrame::OnCaptureChanged(CWnd *pWnd)
{
	if (m_nButtonDown > 0)
	{
		m_nButtonDown = 0;
		RedrawWindow(0, 0, RDW_FRAME|RDW_INVALIDATE );
	}

	CFrameWnd::OnCaptureChanged(pWnd);
}

BOOL CGnomeFrame::OnNcActivate(BOOL /*bActive*/)
{
	return TRUE;
}
