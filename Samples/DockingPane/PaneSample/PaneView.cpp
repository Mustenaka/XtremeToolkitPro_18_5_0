// PaneView.cpp 
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
#include "Pane.h"

#include "MainFrm.h"
#include "PaneDoc.h"
#include "PaneView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaneView

IMPLEMENT_DYNCREATE(CPaneView, CView)

BEGIN_MESSAGE_MAP(CPaneView, CView)
	//{{AFX_MSG_MAP(CPaneView)
	ON_WM_NCPAINT()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaneView construction/destruction

CPaneView::CPaneView()
{
	// TODO: add construction code here

}

CPaneView::~CPaneView()
{
}

BOOL CPaneView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPaneView drawing

void CPaneView::OnDraw(CDC* /*pDC*/)
{
}

// CPaneView printing

BOOL CPaneView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPaneView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPaneView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CPaneView diagnostics

#ifdef _DEBUG
void CPaneView::AssertValid() const
{
	CView::AssertValid();
}

void CPaneView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPaneDoc* CPaneView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPaneDoc)));
	return (CPaneDoc*)m_pDocument;
}
#endif //_DEBUG

// CPaneView message handlers

void CPaneView::OnNcPaint() 
{
	{
		Default();
	}

	CWindowDC dc(this);
	CXTPWindowRect rWindow(this);
	rWindow.OffsetRect(-rWindow.TopLeft());
	
	theApp.m_csPane.DrawBorders(&dc, rWindow);
}

void CPaneView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CXTPClientRect rcClient(this);
	dc.FillSolidRect(rcClient, theApp.m_csPane.m_clrBack);
}
