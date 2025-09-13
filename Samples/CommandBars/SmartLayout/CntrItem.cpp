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
#include "SmartLayout.h"

#include "SmartLayoutDoc.h"
#include "SmartLayoutView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSmartLayoutCntrItem implementation

IMPLEMENT_SERIAL(CSmartLayoutCntrItem, CRichEditCntrItem, 0)

CSmartLayoutCntrItem::CSmartLayoutCntrItem(REOBJECT* preo, CSmartLayoutDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here

}

CSmartLayoutCntrItem::~CSmartLayoutCntrItem()
{
	// TODO: add cleanup code here

}

/////////////////////////////////////////////////////////////////////////////
// CSmartLayoutCntrItem diagnostics

#ifdef _DEBUG
void CSmartLayoutCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CSmartLayoutCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
