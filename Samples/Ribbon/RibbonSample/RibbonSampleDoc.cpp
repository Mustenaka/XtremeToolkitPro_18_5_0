// RibbonSampleDoc.cpp
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
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRibbonSampleDoc

IMPLEMENT_DYNCREATE(CRibbonSampleDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CRibbonSampleDoc, CRichEditDoc)
	//{{AFX_MSG_MAP(CRibbonSampleDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, CRichEditDoc::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_BACKSTAGE_SAVE, CDocument::OnFileSave)
	ON_COMMAND(ID_BACKSTAGE_SAVE_AS, CDocument::OnFileSaveAs)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRibbonSampleDoc construction/destruction

CRibbonSampleDoc::CRibbonSampleDoc()
{
	// TODO: add one-time construction code here

}

CRibbonSampleDoc::~CRibbonSampleDoc()
{
}

BOOL CRibbonSampleDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

CRichEditCntrItem* CRibbonSampleDoc::CreateClientItem(REOBJECT* preo) const
{
	// cast away constness of this
	return new CRibbonSampleCntrItem(preo, (CRibbonSampleDoc*) this);
}



/////////////////////////////////////////////////////////////////////////////
// CRibbonSampleDoc serialization

void CRibbonSampleDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	// Calling the base class CRichEditDoc enables serialization
	//  of the container document's COleClientItem objects.
	// TODO: set CRichEditDoc::m_bRTF = FALSE if you are serializing as text
	CRichEditDoc::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CRibbonSampleDoc diagnostics

#ifdef _DEBUG
void CRibbonSampleDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CRibbonSampleDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRibbonSampleDoc commands
