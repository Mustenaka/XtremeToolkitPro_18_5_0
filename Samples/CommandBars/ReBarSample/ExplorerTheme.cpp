// ExplorerTheme.cpp
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
#include "ExplorerTheme.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExplorerTabPaintManager::CExplorerTabPaintManager()
{
	SetAppearanceSet(new CExplorerTabAppearance());
	SetColor(xtpTabColorWinNative);
	m_bBoldSelected = FALSE;
	m_rcButtonMargin.SetRect(XTP_DPI_X(4), XTP_DPI_Y(2), XTP_DPI_X(4), XTP_DPI_Y(1));
	m_bHotTracking = TRUE;
	m_bFillBackground = FALSE;
	m_szNavigateButton = XTP_DPI(CSize(17, 16));
}

void CExplorerTabPaintManager::DrawNavigateButton(CDC* pDC, CXTPTabManagerNavigateButton* pButton, CRect& rc)
{
	if (GetColorSet()->IsAppThemed() && pButton->GetID() == xtpTabNavigateButtonClose)
	{
		LPCTSTR lpszImage = pButton->IsPressed() ? _T("IDB_EXPLORERTABCLOSEBUTTONPUSHED") : 
			pButton->IsHighlighted() ? _T("IDB_EXPLORERTABCLOSEBUTTONHOT") : _T("IDB_EXPLORERTABCLOSEBUTTON");

		CXTPResourceImage* pImage = ((CExplorerTabAppearance*)GetAppearanceSet())->m_images.LoadFile(lpszImage);
		if (pImage)
		{
			pImage->Premultiply();
			pImage->DrawImage(pDC, rc, pImage->GetSource());
		}

	}
	else
	{
		CXTPTabPaintManager::DrawNavigateButton(pDC, pButton, rc);
	}
}



void CExplorerTabPaintManager::CExplorerTabAppearance::DrawSingleButton(CDC* pDC, CXTPTabManagerItem* pItem)
{
	if (!m_pPaintManager->GetColorSet()->IsAppThemed())
	{
		CAppearanceSetPropertyPage::DrawSingleButton(pDC, pItem);
		return;
	}
	
	CRect rcItem = pItem->GetRect();

	if (pItem->IsSelected())
		rcItem.InflateRect(XTP_DPI_X(1), XTP_DPI_Y(2), XTP_DPI_X(1), 0);
	else rcItem.InflateRect(0, 0, XTP_DPI_X(1), 0);


	LPCTSTR lpszImage = pItem->IsSelected() ? _T("IDB_EXPLORERTABSELECTED") : 
		pItem->IsHighlighted() ? _T("IDB_EXPLORERTABHOT") : _T("IDB_EXPLORERTABNORMAL");

	CXTPResourceImage* pImage = m_images.LoadFile(lpszImage);
	ASSERT(pImage);

	if (pImage)
	{
		pImage->Premultiply();
		pImage->DrawImage(pDC, rcItem, pImage->GetSource(), CRect(3, 3, 3, 3));
	}

	m_pPaintManager->DrawSingleButtonIconAndText(pDC, pItem, rcItem, TRUE);
}
