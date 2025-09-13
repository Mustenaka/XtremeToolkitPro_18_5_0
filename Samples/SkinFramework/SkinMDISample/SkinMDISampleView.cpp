// SkinMDISampleView.cpp
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
#include "SkinMDISample.h"

#include "SkinMDISampleDoc.h"
#include "SkinMDISampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinMDISampleView

IMPLEMENT_DYNCREATE(CSkinMDISampleView, CScrollView)

BEGIN_MESSAGE_MAP(CSkinMDISampleView, CScrollView)
	//{{AFX_MSG_MAP(CSkinMDISampleView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinMDISampleView construction/destruction

CSkinMDISampleView::CSkinMDISampleView()
{
	// TODO: add construction code here

}

CSkinMDISampleView::~CSkinMDISampleView()
{
}

BOOL CSkinMDISampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CScrollView::PreCreateWindow(cs))
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;	
}

/////////////////////////////////////////////////////////////////////////////
// CSkinMDISampleView drawing

void CSkinMDISampleView::OnDraw(CDC* /*pDC*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CSkinMDISampleView printing

BOOL CSkinMDISampleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSkinMDISampleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSkinMDISampleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSkinMDISampleView diagnostics

#ifdef _DEBUG
void CSkinMDISampleView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSkinMDISampleView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CSkinMDISampleDoc* CSkinMDISampleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSkinMDISampleDoc)));
	return (CSkinMDISampleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSkinMDISampleView message handlers

void CSkinMDISampleView::OnInitialUpdate() 
{
	CScrollView::OnInitialUpdate();
	
	SetScrollSizes(MM_TEXT, CSize(500, 1000));
}
