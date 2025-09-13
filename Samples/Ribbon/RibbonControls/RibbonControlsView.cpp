// RibbonControlsView.cpp
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
#include "RibbonControls.h"

#include "RibbonControlsDoc.h"
#include "RibbonControlsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRibbonControlsView

IMPLEMENT_DYNCREATE(CRibbonControlsView, CView)

BEGIN_MESSAGE_MAP(CRibbonControlsView, CView)
	//{{AFX_MSG_MAP(CRibbonControlsView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRibbonControlsView construction/destruction

CRibbonControlsView::CRibbonControlsView()
{
	// TODO: add construction code here

}

CRibbonControlsView::~CRibbonControlsView()
{
}

BOOL CRibbonControlsView::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CView::PreCreateWindow(cs) )
		return FALSE;

	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.dwExStyle &= ~(WS_EX_CLIENTEDGE);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CRibbonControlsView drawing

void CRibbonControlsView::OnDraw(CDC* /*pDC*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CRibbonControlsView printing

BOOL CRibbonControlsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRibbonControlsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRibbonControlsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CRibbonControlsView diagnostics

#ifdef _DEBUG
void CRibbonControlsView::AssertValid() const
{
	CView::AssertValid();
}

void CRibbonControlsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRibbonControlsDoc* CRibbonControlsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRibbonControlsDoc)));
	return (CRibbonControlsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRibbonControlsView message handlers
