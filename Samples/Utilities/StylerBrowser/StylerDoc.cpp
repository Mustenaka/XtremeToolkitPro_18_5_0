// StylerDoc.cpp
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
#include "Styler.h"

#include "StylerDoc.h"
#include "StylerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStylerDoc

IMPLEMENT_DYNCREATE(CStylerDoc, CDocument)

BEGIN_MESSAGE_MAP(CStylerDoc, CDocument)
END_MESSAGE_MAP()


// CStylerDoc construction/destruction

CStylerDoc::CStylerDoc()
{
	m_strUrl = "";

}

CStylerDoc::~CStylerDoc()
{
}

BOOL CStylerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_strUrl = "";

	return TRUE;
}




// CStylerDoc serialization

void CStylerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CStylerDoc diagnostics

#ifdef _DEBUG
void CStylerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStylerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CStylerDoc commands

BOOL CStylerDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	POSITION pos = GetFirstViewPosition();
	CStylerView* pView = (CStylerView*)GetNextView(pos);
	if (pView)
	{
		CString strUrl = CString(_T("file://")) + lpszPathName;
		pView->Navigate2(strUrl);
		
		// Internet Explorer bug 
		if (strUrl.Right(4).CompareNoCase(_T(".mht")) == 0 && strUrl.Find(_T("#")) != -1)
		{		
			pView->Refresh();
			pView->Navigate2(strUrl);
		}

		m_strUrl = strUrl;
	}

	// TODO:  Add your specialized creation code here

	return TRUE;
}
