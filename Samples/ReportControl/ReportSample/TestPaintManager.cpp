// TestPaintManager.cpp
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

#include "StdAfx.h"
#include "TestPaintManager.h"


void CTestReportPaintManager::FillRow(CDC *pDC, CXTPReportRow *pRow, CRect rcRow)
{
	if(!pRow->IsGroupRow())
	{
		if (pRow->IsSelected())
		{
			pDC->FillSolidRect(&rcRow, RGB(255,0,0));
		}
		else
		{
			pDC->FillSolidRect(&rcRow, RGB(128,128,128));
		}
	}
	else
	{
		CXTPReportPaintManager::FillRow(pDC,pRow,rcRow);
	}
}
