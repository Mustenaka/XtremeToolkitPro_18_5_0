// GnomeTheme.cpp
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
#include "GnomeTheme.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGnomeTheme::CGnomeTheme()
{

}

CGnomeTheme::~CGnomeTheme()
{

}

void CGnomeTheme::FillStatusBar(CDC* pDC, CXTPStatusBar* pBar)
{
	pDC->FillSolidRect(CXTPClientRect(pBar), GNOMECOLOR_3DFACE);
}

void CGnomeTheme::FillDockBar(CDC* pDC, CXTPDockBar* pBar)
{
	pDC->FillSolidRect(CXTPClientRect(pBar), GNOMECOLOR_3DFACE);
}

void CGnomeTheme::DrawStatusBarGripper(CDC* pDC, CRect rcClient)
{
	int i;

	CXTPPenDC penBorder(*pDC, GNOMECOLOR_3DSHADOW);
	for (i = 0; i < 4; i++) Line(pDC, CPoint(rcClient.Width() - XTP_DPI_X(4) - XTP_DPI_X(i) * 4,
		rcClient.Height() - XTP_DPI_Y(2)), CPoint(rcClient.Width() - XTP_DPI_X(1), 
		rcClient.Height() - XTP_DPI_Y(5) - XTP_DPI_Y(i) * 4));

	CXTPPenDC penBorderWhite(*pDC, GNOMECOLOR_BTNHIGHLIGHT);
	for (i = 0; i < 4; i++ )
		Line(pDC, CPoint(rcClient.Width() - XTP_DPI_X(5) - XTP_DPI_X(i) * 4, 
		rcClient.Height() - XTP_DPI_Y(2)), CPoint(rcClient.Width() - XTP_DPI_X(1),
		rcClient.Height() - XTP_DPI_Y(4) - XTP_DPI_Y(i) * 4 - XTP_DPI_Y(2)));
}

void CGnomeTheme::DrawStatusBarPane(CDC* pDC, CRect& rc, DWORD dwStyle, CString str)
{
	if (!(dwStyle & SBPS_DISABLED))
	{
		rc.DeflateRect(XTP_DPI_X(2), XTP_DPI_Y(1));
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(str, rc, DT_SINGLELINE | DT_VCENTER) ;
	}
}

void CGnomeTheme::FillCommandBarEntry(CDC* pDC, CXTPCommandBar* pBar)
{
	CRect rc;
	pBar->GetClientRect(&rc);
	pDC->FillSolidRect(rc, GNOMECOLOR_3DFACE);

	if (pBar->GetPosition() == xtpBarFloating || pBar->GetPosition() == xtpBarPopup)
	{
		Draw3dRect(pDC, rc, GNOMECOLOR_3DSHADOW, GNOMECOLOR_3DSHADOW);
		rc.DeflateRect(XTP_DPI_X(1), XTP_DPI_Y(1));
		Draw3dRect(pDC, rc, GNOMECOLOR_BTNHIGHLIGHT, RGB(206, 206, 206));
	}
	else
	{
		Draw3dRect(pDC, rc, RGB(245, 245, 245), RGB(196, 196, 196));
	}

}

CSize CGnomeTheme::DrawCommandBarGripper(CDC* pDC, CXTPCommandBar* pBar, BOOL bDraw)
{
	CRect rc;
	pBar->GetClientRect(&rc);

	CXTPPenDC pen(*pDC, 0);

	if (pBar->GetPosition() == xtpBarFloating)
	{
		ASSERT(pDC);
		CXTPFontDC font(pDC, GetSmCaptionFont());
		CSize sz = pDC->GetTextExtent(_T(" "));

		rc.SetRect(XTP_DPI_X(3), XTP_DPI_Y(3), 
			rc.right - XTP_DPI_X(3), XTP_DPI_Y(3) + max(XTP_DPI_Y(15), sz.cy));
		if (pDC && bDraw)
		{
			pDC->FillSolidRect(rc, RGB(68, 100, 172));
			pDC->SetTextColor(GetXtremeColor(COLOR_3DHIGHLIGHT));
			pDC->DrawText(pBar->GetTitle(), CRect(XTP_DPI_X(5), XTP_DPI_Y(3), 
				rc.right - 2 * rc.Size().cy, rc.bottom), DT_SINGLELINE | DT_VCENTER);
		}
		return rc.Size();

	}
	else if (pBar->GetPosition() == xtpBarRight || pBar->GetPosition() == xtpBarLeft)
	{
		if (pDC && bDraw)
		{
			for (int i = XTP_DPI_X(4); i < rc.right - XTP_DPI_X(4); i += XTP_DPI_X(5))
			{
				//pen.Color(clrGripper[i % 2]); pDC->MoveTo(i, 3); pDC->LineTo(i, 8);

				pen.Color(GNOMECOLOR_3DSHADOW);
				pDC->MoveTo(i, XTP_DPI_Y(7));
				pDC->LineTo(i + XTP_DPI_X(4), XTP_DPI_Y(3));
				
				pen.Color(GNOMECOLOR_BTNHIGHLIGHT);
				pDC->MoveTo(i, XTP_DPI_Y(8));
				pDC->LineTo(i + XTP_DPI_X(4), XTP_DPI_Y(4));

			}
		}
		return XTP_DPI(CSize(0, 8));
	}
	else if (pBar->GetPosition() == xtpBarTop || pBar->GetPosition() == xtpBarBottom)
	{
		if (pDC && bDraw)
		{
			for (int i = XTP_DPI_Y(8); i < rc.bottom - XTP_DPI_Y(4); i += XTP_DPI_Y(5))
			{
				pen.Color(GNOMECOLOR_BTNHIGHLIGHT);
				pDC->MoveTo(XTP_DPI_X(3), i);
				pDC->LineTo(XTP_DPI_X(7), i - XTP_DPI_Y(4));

				pen.Color(GNOMECOLOR_3DSHADOW);
				pDC->MoveTo(XTP_DPI_X(3), i - XTP_DPI_Y(1));
				pDC->LineTo(XTP_DPI_X(7), i - XTP_DPI_Y(5));
			}
		}
		return XTP_DPI(CSize(8, 0));
	}
	return 0;

}


CSize CGnomeTheme::DrawCommandBarSeparator(CDC* pDC, CXTPCommandBar* pBar, CXTPControl* pControl, BOOL bDraw)
{
	if (!bDraw)
	{
		if (pBar->GetType() == xtpBarTypePopup)
			return XTP_DPI(CSize(8, 8));
		
		return XTP_DPI(CSize(6, 6));
	}


	CRect rc;
	pBar->GetClientRect(&rc);
	CRect rcControl = pControl->GetRect();
	CRect rcRow = pControl->GetRowRect();

	if (pBar->GetType() == xtpBarTypePopup)
	{
		Draw3dRect(pDC, CRect(XTP_DPI_X(14), rcControl.top - XTP_DPI_Y(2) - XTP_DPI_Y(2) - XTP_DPI_Y(1), 
			rc.right - XTP_DPI_X(14), rcControl.top - XTP_DPI_Y(0) - XTP_DPI_Y(2) - XTP_DPI_Y(1)), RGB(206, 206, 206), GNOMECOLOR_BTNHIGHLIGHT);
	}
	else if (pBar->GetPosition() != xtpBarPopup && IsVerticalPosition(pBar->GetPosition()))
	{
		if (!pControl->GetWrap())
		{
			pDC->FillSolidRect(rcRow.left + XTP_DPI_X(4), rcControl.top - XTP_DPI_Y(4),
				rcRow.Width() - XTP_DPI_X(8), XTP_DPI_Y(1), RGB(161, 161, 161));
		}
		else
		{
			pDC->FillSolidRect(rcRow.right + XTP_DPI_X(2), rcRow.top + XTP_DPI_Y(4), 
				XTP_DPI_X(1), rcRow.Height() - XTP_DPI_Y(8), RGB(161, 161, 161));
		}
	} else
	{
		if (!pControl->GetWrap())
		{
			pDC->FillSolidRect(rcControl.left - XTP_DPI_X(4), rcRow.top + XTP_DPI_Y(4),
				XTP_DPI_X(1), rcRow.Height() - XTP_DPI_Y(8), RGB(161, 161, 161));
		}
		else
		{
			pDC->FillSolidRect(rcRow.left + XTP_DPI_X(4), rcRow.top - XTP_DPI_Y(4),
				rcRow.Width() - XTP_DPI_X(8), XTP_DPI_Y(1), RGB(161, 161, 161));
		}
	}
	return 0;
}

void CGnomeTheme::DrawRectangle(CDC* pDC, CRect rc, BOOL bSelected, BOOL bPressed, BOOL bEnabled, BOOL bChecked, BOOL bPopuped, BOOL /*bToolBar*/, XTPBarPosition /*barPosition = xtpBarPopup*/)
{
	if ((bSelected || bPressed || bPopuped) && bEnabled)
		pDC->FillSolidRect(rc, RGB(221, 221, 221));

	if (!bEnabled)
	{
		if (IsKeyboardSelected(bSelected)) Draw3dRect(pDC, rc, COLOR_3DSHADOW, COLOR_BTNHILIGHT);
	}
	else if (bChecked && !bSelected && !bPressed)
	{
		Draw3dRect(pDC, rc, GNOMECOLOR_3DSHADOW, GNOMECOLOR_BTNHIGHLIGHT);
	}
	else if (bChecked ||bPopuped || IsKeyboardSelected(bPressed) || (bSelected && bPressed))
	{
		//Draw3dRect(pDC, rc, COLOR_3DSHADOW, COLOR_BTNHILIGHT);
		pDC->FillSolidRect(rc, RGB(204, 204, 204));
		pDC->Draw3dRect(rc, RGB(92, 92, 92), RGB(92, 92, 92));

		rc.DeflateRect(XTP_DPI_X(1), XTP_DPI_Y(1));
		pDC->Draw3dRect(rc, RGB(204, 204, 204), GNOMECOLOR_BTNHIGHLIGHT);
	}
	else if (bSelected || bPressed)
	{
		pDC->FillSolidRect(rc, RGB(245, 245, 245));
		pDC->Draw3dRect(rc, RGB(92, 92, 92), RGB(92, 92, 92));
		rc.DeflateRect(XTP_DPI_X(1), XTP_DPI_Y(1));
		pDC->Draw3dRect(rc, GNOMECOLOR_BTNHIGHLIGHT, RGB(206, 206, 206));
	}
}

void CGnomeTheme::AdjustExcludeRect(CRect& /*rc*/, CXTPControl* /*pControl*/)
{
}
