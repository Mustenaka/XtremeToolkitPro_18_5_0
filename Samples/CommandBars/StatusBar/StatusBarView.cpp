// StatusBarView.cpp
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
#include "StatusBar.h"

#include "StatusBarDoc.h"
#include "StatusBarView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatusBarView

IMPLEMENT_DYNCREATE(CStatusBarView, CView)

BEGIN_MESSAGE_MAP(CStatusBarView, CView)
	//{{AFX_MSG_MAP(CStatusBarView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)

	ON_NOTIFY(XTP_SBN_SCROLL, ID_INDICATOR_ZOOMSLIDER, OnZoomSliderScroll)
	ON_COMMAND(ID_INDICATOR_ZOOM, OnZoomIndicator)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatusBarView construction/destruction

CStatusBarView::CStatusBarView()
{
	CXTPPaintManager::CNonClientMetrics ncm;
	ncm.lfMenuFont.lfWeight = FW_BOLD;
	m_font.CreateFontIndirect(&ncm.lfMenuFont);

	m_nZoom = 100;
}

CStatusBarView::~CStatusBarView()
{
}

BOOL CStatusBarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CStatusBarView drawing

void CStatusBarView::OnDraw(CDC* pDC)
{
	CStatusBarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CXTPFontDC fontDC(pDC, &m_font);
	pDC->SetBkMode(TRANSPARENT);

	// TODO: add draw code for native data here
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, GetParentFrame());
	if (pFrame && !pFrame->m_strMessage.IsEmpty())
	{
		pDC->TextOut(XTP_DPI_X(10), XTP_DPI_Y(10), pFrame->m_strMessage);
	}

	CString strZoom;
	strZoom.Format(_T("%i%%"), m_nZoom);

	pDC->TextOut(XTP_DPI_X(10), XTP_DPI_Y(40), strZoom);
}

/////////////////////////////////////////////////////////////////////////////
// CStatusBarView printing

BOOL CStatusBarView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CStatusBarView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CStatusBarView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CStatusBarView diagnostics

#ifdef _DEBUG
void CStatusBarView::AssertValid() const
{
	CView::AssertValid();
}

void CStatusBarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStatusBarDoc* CStatusBarView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStatusBarDoc)));
	return (CStatusBarDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStatusBarView message handlers


void CStatusBarView::OnZoomSliderScroll(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPSCROLL* pNMScroll = (NMXTPSCROLL*)pNMHDR;
	CXTPStatusBarSliderPane* pPane = DYNAMIC_DOWNCAST(CXTPStatusBarSliderPane, pNMScroll->pSender);
	if (!pPane)
		return;

	int nZoom = m_nZoom;

	switch (pNMScroll->nSBCode)
	{
		case SB_TOP: nZoom = 0; break;
		case SB_BOTTOM: nZoom = 200; break;

		case SB_LINEUP: nZoom = max(((nZoom / 10) - 1) * 10, 0); break;
		case SB_LINEDOWN: nZoom = min(((nZoom / 10) + 1) * 10, 200); break;

		case SB_THUMBTRACK: nZoom = pNMScroll->nPos; break;

		case SB_PAGEUP: nZoom = max(nZoom - 10, 0); break;
		case SB_PAGEDOWN: nZoom = min(nZoom + 10, 200); break;
	}

	if (nZoom == m_nZoom)
		return;

	m_nZoom = nZoom;
	
	pPane->SetPos(nZoom);

	CXTPStatusBar* pStatusBar = pPane->GetStatusBar();
	
	CXTPStatusBarPane* pPaneZoomIndicator = pStatusBar->FindPane(ID_INDICATOR_ZOOM);

	if (pPaneZoomIndicator)
	{
		CString strZoom;
		strZoom.Format(_T("%i%%"), m_nZoom);
		pPaneZoomIndicator->SetText(strZoom);
	}

	*pResult = 1;
	Invalidate(TRUE);
}

void CStatusBarView::OnZoomIndicator()
{
	AfxMessageBox(_T("Zoom dialog box"));
}
