// AppearanceSetEclipse.cpp
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
#include "GUI_Eclipse.h"
#include "AppearanceSetEclipse.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CRect CEclipseTabPaintManager::CAppearanceSetEclipse::FillTabControl(CXTPTabManager* pTabManager, CDC* pDC, CRect rcControl)
{

	pDC->FillSolidRect(rcControl, XTPPaintManager()->GetXtremeColor(XPCOLOR_3DFACE));

	CRect rcHeader = GetHeaderRect(rcControl, pTabManager);
	GetColorSet()->FillHeader(pDC, rcHeader, pTabManager);

	CRect rcClient = GetClientRect(rcControl, pTabManager);

	switch (pTabManager->GetPosition())
	{
		case xtpTabPositionTop:
			pDC->FillSolidRect(rcHeader.left, rcHeader.bottom - XTP_DPI_Y(1), 
				rcHeader.Width(), XTP_DPI_Y(1), GetColorSet()->m_clrFrameBorder);
			break;
		case xtpTabPositionBottom:
			pDC->FillSolidRect(rcHeader.left, rcHeader.top, 
				rcHeader.Width(), XTP_DPI_Y(1), GetColorSet()->m_clrFrameBorder);
			break;
	}

	return rcHeader;
}

void CEclipseTabPaintManager::CAppearanceSetEclipse::DrawSingleButton(CDC* pDC, CXTPTabManagerItem* pItem)
{
	CRect rcItem = pItem->GetRect();

	if (!pItem->IsSelected())
	{
		if (pItem->GetIndex() != pItem->GetTabManager()->GetItemCount() - 1)
		{
			switch (pItem->GetTabManager()->GetPosition())
			{
				case xtpTabPositionTop:
					pDC->FillSolidRect(rcItem.right, rcItem.top + XTP_DPI_Y(1), 
						XTP_DPI_X(1), rcItem.Height() / 2, GetXtremeColor(COLOR_3DSHADOW));
					break;
				case xtpTabPositionBottom:
					pDC->FillSolidRect(rcItem.right, rcItem.bottom - XTP_DPI_Y(1) - rcItem.Height() / 2,
						XTP_DPI_X(1), rcItem.Height() / 2, GetXtremeColor(COLOR_3DSHADOW));
					break;
			}
		}
	}
	else
	{
		CRect rcFill(rcItem);
		rcFill.DeflateRect(XTP_DPI_X(1), XTP_DPI_Y(1));
		pDC->Draw3dRect(rcFill, GetXtremeColor(COLOR_WINDOW), GetXtremeColor(COLOR_WINDOW));

		pDC->FillSolidRect(rcItem.left, rcItem.top + XTP_DPI_Y(1), 
			XTP_DPI_X(1), rcItem.Height() - XTP_DPI_Y(2), GetColorSet()->m_clrFrameBorder);
		pDC->FillSolidRect(rcItem.right - XTP_DPI_X(1), rcItem.top + XTP_DPI_Y(1), 
			XTP_DPI_X(1), rcItem.Height() - XTP_DPI_Y(2), GetColorSet()->m_clrFrameBorder);

		DeflateRectEx(rcItem, XTP_DPI(CRect(2, 2, 2, 1)), pItem->GetTabManager()->GetPosition());

		//if (((CEclipseTabPaintManager*)m_pPaintManager)->m_bFillTab)
		XTPDrawHelpers()->GradientFill(pDC, rcItem, GetXtremeColor(COLOR_ACTIVECAPTION), XTPPaintManager()->GetXtremeColor(XPCOLOR_TOOLBAR_FACE), TRUE);

	}
	m_pPaintManager->DrawSingleButtonIconAndText(pDC, pItem, pItem->GetRect(), TRUE);
}



void CEclipseTabPaintManager::DrawFrame(CDC* pDC, CRect rcControl, BOOL bFillRect)
{
	if (bFillRect)
	{
		pDC->FillSolidRect(rcControl, XTPPaintManager()->GetXtremeColor(XPCOLOR_3DFACE));

	} else
	{
		pDC->FillSolidRect(rcControl.left, rcControl.top, rcControl.Width(), XTP_DPI_Y(4), XTPPaintManager()->GetXtremeColor(XPCOLOR_3DFACE));
		pDC->FillSolidRect(rcControl.left, rcControl.top, XTP_DPI_X(4), rcControl.Height(), XTPPaintManager()->GetXtremeColor(XPCOLOR_3DFACE));
	}


	pDC->Draw3dRect(rcControl.left + XTP_DPI_X(3), rcControl.top + XTP_DPI_Y(3), 
		rcControl.Width() - XTP_DPI_X(6), rcControl.Height() - XTP_DPI_Y(6), RGB(132, 130, 132), RGB(132, 130, 132));

	pDC->FillSolidRect(rcControl.left + XTP_DPI_X(4), rcControl.bottom - XTP_DPI_Y(3),
		rcControl.Width() - XTP_DPI_X(4), XTP_DPI_Y(1), RGB(143, 141, 138));
	pDC->FillSolidRect(rcControl.right - XTP_DPI_X(3), rcControl.top + XTP_DPI_Y(4), 
		XTP_DPI_X(1), rcControl.Height(), RGB(143, 141, 138));

	pDC->FillSolidRect(rcControl.left + XTP_DPI_X(5), rcControl.bottom - XTP_DPI_Y(2), 
		rcControl.Width() - XTP_DPI_X(4), XTP_DPI_Y(1), RGB(171, 168, 165));
	pDC->FillSolidRect(rcControl.right - XTP_DPI_X(2), rcControl.top + XTP_DPI_Y(5), 
		XTP_DPI_X(1), rcControl.Height(), RGB(171, 168, 165));

	pDC->Draw3dRect(rcControl.left, rcControl.top, rcControl.Width(), rcControl.Height(), XTPPaintManager()->GetXtremeColor(XPCOLOR_3DFACE), XTPPaintManager()->GetXtremeColor(XPCOLOR_3DFACE));

}

void CEclipseTabPaintManager::DrawTabControl (CXTPTabManager* pTabManager, CDC* pDC, CRect rcControl)
{
	CXTPTabPaintManager::DrawTabControl(pTabManager, pDC, rcControl);

	if (m_bFrame)
	{
		DrawFrame(pDC, rcControl);
	}

}
