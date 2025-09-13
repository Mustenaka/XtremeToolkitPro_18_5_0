// GridSampleDoc.cpp
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
#include "GridSample.h"
#include "GridSampleDoc.h"
#include "GridSampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGridSampleDoc

IMPLEMENT_DYNCREATE(CGridSampleDoc, CDocument)

BEGIN_MESSAGE_MAP(CGridSampleDoc, CDocument)
	//{{AFX_MSG_MAP(CGridSampleDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridSampleDoc construction/destruction

CGridSampleDoc::CGridSampleDoc()
{
	// TODO: add one-time construction code here

}

CGridSampleDoc::~CGridSampleDoc()
{
}

BOOL CGridSampleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGridSampleDoc serialization

void CGridSampleDoc::Serialize(CArchive& ar)
{
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		CGridSampleView* pReportView = DYNAMIC_DOWNCAST(CGridSampleView, pView);
		pReportView->GetReportCtrl().SerializeState(ar);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGridSampleDoc diagnostics

#ifdef _DEBUG
void CGridSampleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGridSampleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGridSampleDoc commands
