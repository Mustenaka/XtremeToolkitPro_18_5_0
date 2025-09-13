// FlowGraphSampleDoc.cpp
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
#include "FlowGraphSample.h"

#include "FlowGraphSampleDoc.h"
#include "FlowGraphSampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlowGraphSampleDoc

IMPLEMENT_DYNCREATE(CFlowGraphSampleDoc, CDocument)

BEGIN_MESSAGE_MAP(CFlowGraphSampleDoc, CDocument)
	//{{AFX_MSG_MAP(CFlowGraphSampleDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlowGraphSampleDoc construction/destruction

CFlowGraphSampleDoc::CFlowGraphSampleDoc()
{
	// TODO: add one-time construction code here

}

CFlowGraphSampleDoc::~CFlowGraphSampleDoc()
{
}

BOOL CFlowGraphSampleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	static BOOL bStartup = TRUE;

	if (bStartup)
	{
		bStartup = FALSE;
	}
	else
	{
		POSITION pos = GetFirstViewPosition();
		CFlowGraphSampleView* pView = (CFlowGraphSampleView*)GetNextView(pos);

		pView->m_wndControl.GetPages()->RemoveAll();
		CXTPFlowGraphPage* pPage = pView->m_wndControl.GetPages()->AddPage(new CXTPFlowGraphPage());
		pView->m_wndControl.SetActivePage(pPage);
	}


	return TRUE;
}


BOOL CFlowGraphSampleDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	TRY
	{
		POSITION pos = GetFirstViewPosition();
		CFlowGraphSampleView* pView = (CFlowGraphSampleView*)GetNextView(pos);

		CXTPPropExchangeXMLNode px(TRUE, 0, _T("FlowGraph"));
		
		if (!px.LoadFromFile(lpszPathName))
			return FALSE;

		if (px.GetSectionName() != _T("FlowGraph"))
		{
			MessageBox(pView->GetSafeHwnd(), _T("This XML doesn't seem to be saved in FlowGraph format"), _T("Error loading XML"), MB_ICONEXCLAMATION);

			return FALSE;
		}
		
		pView->m_wndControl.DoPropExchange(&px);			
	}
	CATCH_ALL(e)
	{
		TRY
		{
			ReportSaveLoadException(lpszPathName, e,
				TRUE, AFX_IDP_FAILED_TO_SAVE_DOC);
		}
		END_TRY
			
			e->Delete(); 
		return FALSE;
	}
	END_CATCH_ALL
		
		SetModifiedFlag(FALSE);     // back to unmodified
	
	
	return TRUE;
}

BOOL CFlowGraphSampleDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	TRY
	{
		CXTPPropExchangeXMLNode px(FALSE, 0, _T("FlowGraph"));
		
		POSITION pos = GetFirstViewPosition();
		CFlowGraphSampleView* pView = (CFlowGraphSampleView*)GetNextView(pos);
		
		pView->m_wndControl.DoPropExchange(&px);		
		
		if (FAILED(px.SaveToFile(lpszPathName)))
			return FALSE;
	}
	CATCH_ALL(e)
	{
		TRY
		{
			ReportSaveLoadException(lpszPathName, e,
				TRUE, AFX_IDP_FAILED_TO_SAVE_DOC);
		}
		END_TRY
			
			e->Delete(); 
		return FALSE;
	}
	END_CATCH_ALL
		
		SetModifiedFlag(FALSE);     // back to unmodified
	
	return TRUE;        // success
	
}


/////////////////////////////////////////////////////////////////////////////
// CFlowGraphSampleDoc serialization

void CFlowGraphSampleDoc::Serialize(CArchive& ar)
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

/////////////////////////////////////////////////////////////////////////////
// CFlowGraphSampleDoc diagnostics

#ifdef _DEBUG
void CFlowGraphSampleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFlowGraphSampleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFlowGraphSampleDoc commands
