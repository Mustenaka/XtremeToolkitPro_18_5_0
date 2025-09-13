// IndicatorStatusBar.cpp
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
#include "styler.h"
#include "IndicatorStatusBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CIndicatorStatusBar::CIndicatorStatusBar()
{
	m_nProgress = 0;
}

CIndicatorStatusBar::~CIndicatorStatusBar()
{
}


/////////////////////////////////////////////////////////////////////////////
// CIndicatorStatusBar message handlers

void CIndicatorStatusBar::DrawPaneEntry(CDC* pDC, int nIndex, CRect rcItem)
{
	if (nIndex != 1 || m_nProgress != 0)
	{
		CXTPStatusBar::DrawPaneEntry(pDC, nIndex, rcItem);
	}
}

void CIndicatorStatusBar::SetProgress(int nProgress)
{
	if (m_nProgress != nProgress)
	{
		m_nProgress = nProgress;

		((CIndicatorStatusBarPane*)GetPane(1))->SetPos(nProgress);
	}

}

