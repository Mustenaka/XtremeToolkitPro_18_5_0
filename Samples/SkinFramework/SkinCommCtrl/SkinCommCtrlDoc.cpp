// SkinCommCtrlDoc.cpp
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
#include "SkinCommCtrl.h"

#include "SkinCommCtrlDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinCommCtrlDoc

IMPLEMENT_DYNCREATE(CSkinCommCtrlDoc, CDocument)

BEGIN_MESSAGE_MAP(CSkinCommCtrlDoc, CDocument)
	//{{AFX_MSG_MAP(CSkinCommCtrlDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinCommCtrlDoc construction/destruction

CSkinCommCtrlDoc::CSkinCommCtrlDoc()
{
}

CSkinCommCtrlDoc::~CSkinCommCtrlDoc()
{
}

BOOL CSkinCommCtrlDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSkinCommCtrlDoc serialization

void CSkinCommCtrlDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSkinCommCtrlDoc diagnostics

#ifdef _DEBUG
void CSkinCommCtrlDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSkinCommCtrlDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSkinCommCtrlDoc commands
