// CommandBarControlsView.cpp
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
#include "CommandBarControls.h"

#include "CommandBarControlsDoc.h"
#include "CommandBarControlsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommandBarControlsView

IMPLEMENT_DYNCREATE(CCommandBarControlsView, CView)

BEGIN_MESSAGE_MAP(CCommandBarControlsView, CView)
	//{{AFX_MSG_MAP(CCommandBarControlsView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)

	ON_COMMAND(ID_EDIT_COPY, OnEmptyCommand)
	ON_COMMAND(ID_EDIT_CUT, OnEmptyCommand)
	ON_COMMAND(ID_EDIT_PASTE, OnEmptyCommand)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEmptyCommand)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommandBarControlsView construction/destruction

CCommandBarControlsView::CCommandBarControlsView()
{
	// TODO: add construction code here

}

CCommandBarControlsView::~CCommandBarControlsView()
{
}

BOOL CCommandBarControlsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCommandBarControlsView drawing

void CCommandBarControlsView::OnDraw(CDC* /*pDC*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CCommandBarControlsView printing

BOOL CCommandBarControlsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCommandBarControlsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCommandBarControlsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCommandBarControlsView diagnostics

#ifdef _DEBUG
void CCommandBarControlsView::AssertValid() const
{
	CView::AssertValid();
}

void CCommandBarControlsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCommandBarControlsDoc* CCommandBarControlsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCommandBarControlsDoc)));
	return (CCommandBarControlsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCommandBarControlsView message handlers


void CCommandBarControlsView::OnEmptyCommand()
{

}