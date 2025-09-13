// RibbonResourceDoc.cpp
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
#include "RibbonResource.h"

#include "RibbonResourceDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRibbonResourceDoc

IMPLEMENT_DYNCREATE(CRibbonResourceDoc, CDocument)

BEGIN_MESSAGE_MAP(CRibbonResourceDoc, CDocument)
	//{{AFX_MSG_MAP(CRibbonResourceDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRibbonResourceDoc construction/destruction

CRibbonResourceDoc::CRibbonResourceDoc()
{
	// TODO: add one-time construction code here

}

CRibbonResourceDoc::~CRibbonResourceDoc()
{
}

BOOL CRibbonResourceDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}


CRichEditCntrItem* CRibbonResourceDoc::CreateClientItem(REOBJECT* preo) const
{
	// cast away constness of this
	return new CRichEditCntrItem(preo, (CRibbonResourceDoc*) this);
}




/////////////////////////////////////////////////////////////////////////////
// CRibbonResourceDoc serialization

void CRibbonResourceDoc::Serialize(CArchive& ar)
{
	CRichEditDoc::Serialize(ar);
	
}

/////////////////////////////////////////////////////////////////////////////
// CRibbonResourceDoc diagnostics

#ifdef _DEBUG
void CRibbonResourceDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRibbonResourceDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRibbonResourceDoc commands
