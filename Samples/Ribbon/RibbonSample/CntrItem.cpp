// CntrItem.cpp
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
#include "RibbonSample.h"

#include "RibbonSampleDoc.h"
#include "RibbonSampleView.h"
#include "CntrItem.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRibbonSampleCntrItem implementation

IMPLEMENT_SERIAL(CRibbonSampleCntrItem, CRichEditCntrItem, 0)

CRibbonSampleCntrItem::CRibbonSampleCntrItem(REOBJECT* preo, CRibbonSampleDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
	
}

CRibbonSampleCntrItem::~CRibbonSampleCntrItem()
{
	// TODO: add cleanup code here
	
}

/////////////////////////////////////////////////////////////////////////////
// CRibbonSampleCntrItem diagnostics

#ifdef _DEBUG
void CRibbonSampleCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CRibbonSampleCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////

void CRibbonSampleCntrItem::ActiveStateChanged(BOOL bActive)
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	if (!pFrame)
		return;


	CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)pFrame->GetCommandBars()->GetMenuBar();
	ASSERT(pRibbonBar);
	if (!pRibbonBar)
		return;

	pFrame->GetCommandBars()->OnSetPreviewMode(bActive);

	if (bActive)
	{
		pRibbonBar->EnableFrameTheme(FALSE);

		CDocTemplate* pTemplate = GetDocument()->GetDocTemplate();
		HMENU hMenuOLE = pTemplate->m_hMenuInPlace;

		::SetMenu(pFrame->GetSafeHwnd(), hMenuOLE);
	}
	else
	{
		pRibbonBar->EnableFrameTheme(TRUE);
	}

	pFrame->DelayRecalcLayout(FALSE);
}

void CRibbonSampleCntrItem::OnActivate()
{
	// allow only one inplace active item per frame
	CView* pView = GetActiveView();
	ASSERT_VALID(pView);
	COleClientItem* pItem = GetDocument()->GetInPlaceActiveItem(pView);
	if (pItem != NULL && pItem != this)
		pItem->Close();

	ActiveStateChanged(TRUE);

	COleClientItem::OnActivate();
}

void CRibbonSampleCntrItem::OnDeactivateUI(BOOL bUndoable)
{
	COleClientItem::OnDeactivateUI(bUndoable);

	// hide the object if it is not an outside-in object
	DWORD dwMisc = 0;
	m_lpObject->GetMiscStatus(GetDrawAspect(), &dwMisc);
	if (dwMisc & OLEMISC_INSIDEOUT)
		DoVerb(OLEIVERB_HIDE, NULL);

	ActiveStateChanged(FALSE);

}