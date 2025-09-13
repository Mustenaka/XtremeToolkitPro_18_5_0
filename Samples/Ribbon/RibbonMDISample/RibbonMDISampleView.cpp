// RibbonMDISampleView.cpp
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
#include "RibbonMDISample.h"
#include "MainFrm.h"
#include "RibbonMDISampleDoc.h"
#include "CntrItem.h"
#include "RibbonMDISampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SCROLLBAR_ID 100
#define LINE_HEIGH 20
#define SCROLLBAR_WHEEL_SPEED 60

#ifndef EM_SHOWSCROLLBAR
#define EM_SHOWSCROLLBAR		(WM_USER + 96)
#endif

#ifndef EM_GETSCROLLPOS
#define EM_GETSCROLLPOS 		(WM_USER + 221)
#endif

#ifndef EM_SETSCROLLPOS
#define EM_SETSCROLLPOS 		(WM_USER + 222)
#endif

/////////////////////////////////////////////////////////////////////////////
// CRibbonMDISampleView

IMPLEMENT_DYNCREATE(CRibbonMDISampleView, CRichEditView)

BEGIN_MESSAGE_MAP(CRibbonMDISampleView, CRichEditView)
	//{{AFX_MSG_MAP(CRibbonMDISampleView)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_CONTROL_REFLECT(EN_VSCROLL, OnEditScrollChanged)
	ON_NOTIFY_REFLECT(EN_REQUESTRESIZE,	OnRequestResize)
	ON_WM_NCPAINT()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRibbonMDISampleView construction/destruction

CRibbonMDISampleView::CRibbonMDISampleView()
{
	m_nTextHeight = 0;
	m_nTotalHeight = 0;
	m_nScrollPos = 0;
	m_bInScrollChanged = FALSE;
}

CRibbonMDISampleView::~CRibbonMDISampleView()
{
}

BOOL CRibbonMDISampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	if (!CRichEditView::PreCreateWindow(cs))
		return FALSE;
	//cs.lpszClass = RICHEDIT_CLASS;
#ifdef _UNICODE
	cs.lpszClass = L"RichEdit20W";
#else
	cs.lpszClass = "RichEdit20A";
#endif
	return TRUE;
}

void CRibbonMDISampleView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();

	m_nScrollPos = 0;
	SendMessage(EM_SHOWSCROLLBAR, SB_VERT, FALSE);
	SendMessage(EM_SHOWSCROLLBAR, SB_HORZ, FALSE);
	GetRichEditCtrl().SetEventMask(GetRichEditCtrl().GetEventMask()| ENM_SCROLL | ENM_REQUESTRESIZE);

	GetScrollBarCtrl(SB_VERT)->ShowScrollBar(FALSE);
	UpdateScrollInfo();

	// Set the printing margins (720 twips = 1/2 inch).
	SetMargins(CRect(720, 720, 720, 720));

}

/////////////////////////////////////////////////////////////////////////////
// CRibbonMDISampleView printing

BOOL CRibbonMDISampleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}


void CRibbonMDISampleView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
	CRichEditView::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CRibbonMDISampleView diagnostics

#ifdef _DEBUG
void CRibbonMDISampleView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CRibbonMDISampleView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CRibbonMDISampleDoc* CRibbonMDISampleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRibbonMDISampleDoc)));
	return (CRibbonMDISampleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRibbonMDISampleView message handlers

void CRibbonMDISampleView::OnFilePrintPreview()
{
	// In derived classes, implement special window handling here
	// Be sure to Unhook Frame Window close if hooked.

	// must not create this on the frame.  Must outlive this function
	CPrintPreviewState* pState = new CPrintPreviewState;

	// DoPrintPreview's return value does not necessarily indicate that
	// Print preview succeeded or failed, but rather what actions are necessary
	// at this point.  If DoPrintPreview returns TRUE, it means that
	// OnEndPrintPreview will be (or has already been) called and the
	// pState structure will be/has been deleted.
	// If DoPrintPreview returns FALSE, it means that OnEndPrintPreview
	// WILL NOT be called and that cleanup, including deleting pState
	// must be done here.

	if ( !DoPrintPreview( XTP_IDD_PREVIEW_DIALOGBAR, this,
		RUNTIME_CLASS( CXTPPreviewView ), pState ))
	{
		// In derived classes, reverse special window handling here for
		// Preview failure case
		TRACE0( "Error: DoPrintPreview failed.\n" );
		AfxMessageBox( AFX_IDP_COMMAND_FAILURE );
		delete pState;      // preview failed to initialize, delete State now
	}
}

int CRibbonMDISampleView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CRichEditView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_wndScrollBar.Create(WS_CHILD | WS_VISIBLE | SBS_VERT, CRect(0, 0, 0, 0), this, SCROLLBAR_ID);
	m_wndScrollBar.SetScrollBarStyle(xtpScrollStyleOffice2007Dark);
	return 0;
}

void CRibbonMDISampleView::Reposition(CSize sz)
{
	if (m_wndScrollBar.GetSafeHwnd())
	{
		int nWidth = GetSystemMetrics(SM_CXVSCROLL);		
		m_wndScrollBar.MoveWindow(sz.cx - nWidth, 0, nWidth, sz.cy);
	}
}

void CRibbonMDISampleView::OnSize(UINT nType, int cx, int cy) 
{
	CRichEditView::OnSize(nType, cx, cy);
	//Show/hide scrollbar
	if (m_nTextHeight > GetPageSize())
	{
		CScrollBar* pScrollBar = GetScrollBarCtrl(SB_VERT);
		if (pScrollBar != NULL && pScrollBar->GetSafeHwnd())
		{
			pScrollBar->ShowScrollBar(TRUE);
		}
	}
	else
	{
		CScrollBar* pScrollBar = GetScrollBarCtrl(SB_VERT);
		if (pScrollBar != NULL && pScrollBar->GetSafeHwnd())
		{
			pScrollBar->ShowScrollBar(FALSE);
		}
		RedrawWindow(NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
	}

	Reposition(CSize(cx, cy));
	UpdateScrollInfo();
}

CRect CRibbonMDISampleView::GetViewRect(CRect rc)
{
	if (m_wndScrollBar.GetSafeHwnd())
	{
		int nWidth = GetSystemMetrics(SM_CXVSCROLL);		
		rc.right -= nWidth;
	}
	return rc;
}

void CRibbonMDISampleView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int y = GetScrollPos(SB_VERT);

	switch (nSBCode)
	{
	case SB_TOP:
		y = 0;
		break;
	case SB_BOTTOM:
		y = m_nTotalHeight;
		break;
	case SB_LINEUP:
		y -= LINE_HEIGH;
		break;
	case SB_LINEDOWN:
		y += LINE_HEIGH;
		break;
	case SB_PAGEUP:
		y -= GetPageSize();
		break;
	case SB_PAGEDOWN:
		y += GetPageSize();
		break;
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		y = nPos;
		break;
	}

	SetScrollPos(y);
}

void CRibbonMDISampleView::SetLayoutRTL(BOOL bRTLLayout)
{
	ModifyStyleEx(bRTLLayout ? 0 : WS_EX_LAYOUTRTL, !bRTLLayout ? 0 : WS_EX_LAYOUTRTL);
	Reposition(CXTPClientRect(this).Size());
	Invalidate(FALSE);
}

int CRibbonMDISampleView::GetPageSize()
{
	return CXTPClientRect(this).Height();
}

CScrollBar* CRibbonMDISampleView::GetScrollBarCtrl(int nBar) const
{
	ASSERT(nBar == SB_VERT); 
	UNUSED(nBar);

	if (!AfxGetMainWnd())
		return NULL;

	return (CScrollBar *) &m_wndScrollBar;
}

void CRibbonMDISampleView::UpdateScrollInfo()
{
	m_nTotalHeight = m_nTextHeight;
	CScrollBar* pScrollBar = GetScrollBarCtrl(SB_VERT);

	if (!pScrollBar)
		return;

	SCROLLINFO si;
	ZeroMemory(&si, sizeof(SCROLLINFO));

	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL;
	si.nPos = m_nScrollPos;

	si.nPage = GetPageSize();
	si.nMax = m_nTotalHeight;

	pScrollBar->SetScrollInfo(&si);
}

void CRibbonMDISampleView::OnEditScrollChanged()
{
	if (m_bInScrollChanged)	
		return;

	POINT pt;
	GetRichEditCtrl().SendMessage(EM_GETSCROLLPOS, 0, (LPARAM)&pt);

	m_nScrollPos = pt.y;
	UpdateScrollInfo();
	UpdatePosition();
}

void CRibbonMDISampleView::OnRequestResize(NMHDR * pNotifyStruct, LRESULT* /*result*/)
{
	REQRESIZE* rs = (REQRESIZE*)pNotifyStruct;
	m_nTextHeight = rs->rc.bottom - rs->rc.top;

	//Show/hide scrollbar
	if (m_nTextHeight > GetPageSize())
	{
		CScrollBar* pScrollBar = GetScrollBarCtrl(SB_VERT);
		pScrollBar->ShowScrollBar(TRUE);
	}
	else
	{
		CScrollBar* pScrollBar = GetScrollBarCtrl(SB_VERT);
		pScrollBar->ShowScrollBar(FALSE);
		RedrawWindow(NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
	}

	UpdateScrollInfo();
}

void CRibbonMDISampleView::UpdatePosition()
{
	SendMessage(WM_NCPAINT);
}

void CRibbonMDISampleView::SetScrollPos(int nScrollPos)
{
	int nMaxPos = m_nTotalHeight - GetPageSize();

	if (nScrollPos > nMaxPos)
		nScrollPos = nMaxPos;

	if (nScrollPos < 0)
		nScrollPos = 0;

	if (m_nScrollPos == nScrollPos)
		return;

	m_nScrollPos = nScrollPos;
	int nEditScroll = max(0, m_nScrollPos);

	m_bInScrollChanged = TRUE;
	POINT pt = {0, nEditScroll};
	SendMessage(EM_SETSCROLLPOS, 0, (LPARAM)&pt);
	m_bInScrollChanged = FALSE;

	UpdateScrollInfo();
	UpdatePosition();
}

BOOL CRibbonMDISampleView::OnMouseWheel(UINT /*nFlags*/, short zDelta, CPoint /*pt*/) 
{
	SetScrollPos(m_nScrollPos + (zDelta < 0 ? SCROLLBAR_WHEEL_SPEED : -SCROLLBAR_WHEEL_SPEED));
	return TRUE;
}

void CRibbonMDISampleView::OnNcPaint() 
{
	CRichEditView::OnNcPaint();

	CMDIChildWnd* pChildWnd = DYNAMIC_DOWNCAST(CMDIChildWnd, GetParentFrame());

	CString strName = XTPIniString(_T("Theme"), _T("Name"), NULL);
	
	if (strName == _T("OFFICE2013"))
	{
		const COLORREF clrBack = ::GetSysColor(COLOR_WINDOW);
		const COLORREF clrBorder = XTPIniColor(_T("CommandBars.Ribbon"), _T("RibbonBorder"), RGB(171, 171, 171));
		
		CWindowDC dc(this);
		CXTPWindowRect rc(this);
		rc.OffsetRect(-rc.TopLeft());
		
		if (pChildWnd->IsZoomed())
		{
			// fill non client border.
			dc.Draw3dRect(rc.left, rc.top, rc.Width(), rc.Height(), clrBack, clrBack);
			rc.DeflateRect(XTP_DPI_X(1),XTP_DPI_Y(1));
			dc.Draw3dRect(rc.left, rc.top, rc.Width(), rc.Height(), clrBack, clrBack);
		}
		else
		{
			// fill non client border.
			dc.Draw3dRect(rc.left, rc.top, rc.Width(), rc.Height(), clrBorder, clrBorder);
			rc.DeflateRect(XTP_DPI_X(1),XTP_DPI_Y(1));
			dc.Draw3dRect(rc.left, rc.top, rc.Width(), rc.Height(), clrBack, clrBack);
		}
	}
	else if (strName == _T("OFFICE2016"))
	{
		const COLORREF clrBack = ::GetSysColor(COLOR_WINDOW);
		const COLORREF clrBorder = XTPIniColor(_T("TabClient"), _T("Border"), RGB(171, 171, 171));
		
		CWindowDC dc(this);
		CXTPWindowRect rc(this);
		rc.OffsetRect(-rc.TopLeft());
		
		if (pChildWnd->IsZoomed())
		{
			// fill non client border.
			dc.Draw3dRect(rc.left, rc.top, rc.Width(), rc.Height(), clrBack, clrBack);
			rc.DeflateRect(XTP_DPI_X(1),XTP_DPI_Y(1));
			dc.Draw3dRect(rc.left, rc.top, rc.Width(), rc.Height(), clrBack, clrBack);
			rc.InflateRect(XTP_DPI_X(1),XTP_DPI_Y(1));
			
			// draw single line border on the bottom.
			CXTPPenDC pen(dc, PS_SOLID, 1, clrBorder);
			dc.MoveTo(rc.left, rc.bottom-XTP_DPI_Y(1));
			dc.LineTo(rc.right, rc.bottom-XTP_DPI_Y(1));
		}
		else
		{
			// fill non client border.
			dc.Draw3dRect(rc.left, rc.top, rc.Width(), rc.Height(), clrBack, clrBack);
			rc.DeflateRect(XTP_DPI_X(1),XTP_DPI_Y(1));
			dc.Draw3dRect(rc.left, rc.top, rc.Width(), rc.Height(), clrBack, clrBack);
		}
	}
}
