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
#include "SkinSDISample.h"

#include "SkinSDISampleDoc.h"
#include "SkinSDISampleView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinSDISampleCntrItem implementation

IMPLEMENT_SERIAL(CSkinSDISampleCntrItem, CRichEditCntrItem, 0)

CSkinSDISampleCntrItem::CSkinSDISampleCntrItem(REOBJECT* preo, CSkinSDISampleDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here

}

CSkinSDISampleCntrItem::~CSkinSDISampleCntrItem()
{
	// TODO: add cleanup code here

}

/////////////////////////////////////////////////////////////////////////////
// CSkinSDISampleCntrItem diagnostics

#ifdef _DEBUG
void CSkinSDISampleCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CSkinSDISampleCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
