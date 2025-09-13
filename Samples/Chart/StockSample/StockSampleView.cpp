// StockSampleView.cpp
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
#include "math.h"

#include "StockSample.h"
#include "StockSampleDoc.h"
#include "StockSampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStockSampleView

IMPLEMENT_DYNCREATE(CStockSampleView, CView)

BEGIN_MESSAGE_MAP(CStockSampleView, CView)
	//{{AFX_MSG_MAP(CStockSampleView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_VIEW_STOCKQUOTE, OnViewStockquote)
	ON_UPDATE_COMMAND_UI(ID_VIEW_STOCKQUOTE, OnUpdateViewStockquote)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_VIEW_THICKSTYLE,OnViewThickstyle)
	ON_UPDATE_COMMAND_UI(ID_VIEW_THICKSTYLE, OnUpdateViewThickstyle)
	ON_COMMAND(ID_VIEW_CANDLES, OnViewCandles)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CANDLES, OnUpdateViewCandles)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStockSampleView construction/destruction

CStockSampleView::CStockSampleView()
{
	m_bCandleStick = TRUE;
	m_bThickLine = FALSE;
}

CStockSampleView::~CStockSampleView()
{
}

BOOL CStockSampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CView::PreCreateWindow(cs))
        return FALSE;

    cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CStockSampleView drawing

void CStockSampleView::OnDraw(CDC* pDC)
{
	CStockSampleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}


/////////////////////////////////////////////////////////////////////////////
// CStockSampleView diagnostics

#ifdef _DEBUG
void CStockSampleView::AssertValid() const
{
	CView::AssertValid();
}

void CStockSampleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStockSampleDoc* CStockSampleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStockSampleDoc)));
	return (CStockSampleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStockSampleView message handlers

void AddDate(CXTPChartSeries* pSeries, LPCTSTR arg, double low, double high, double open, double close)
{
	CXTPChartSeriesPoint* pPoint;	
	pPoint = pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(arg, low, high, open, close));	
}

void CStockSampleView::UpdateHistory(LPCTSTR lpszSymbol, BOOL bCandleStick, int nDays /*=180*/)
{
	m_wndChartControl.GetContent()->GetSeries()->RemoveAll();

	CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->Add(new CXTPChartSeries());
	pSeries->SetArgumentScaleType(xtpChartScaleDateTime);
	
	CTime timeEnd = CTime::GetCurrentTime();

	CTime timeStart = timeEnd;
	timeStart -= CTimeSpan(nDays,0,0,0);
	
	CStringArray& arrQuote = CQuandlAPI::Inst().GetHistory(lpszSymbol, timeStart, timeEnd);

    if (CQuandlAPI::Inst().IsValid())
    {
        CXTPChartHighLowSeriesStyle* pStyle = NULL;
        
        if (bCandleStick)
        {
            pStyle = (CXTPChartHighLowSeriesStyle*)pSeries->SetStyle(new CXTPChartCandleStickSeriesStyle());
        }
        else
        {
            pStyle = (CXTPChartHighLowSeriesStyle*)pSeries->SetStyle(new CXTPChartHighLowSeriesStyle());
        }
        
        pStyle->SetLineThickness(m_bThickLine ? 2 : 1);
        m_bCandleStick = bCandleStick;
        
        CXTPChartDiagram2D* pDiagram = (CXTPChartDiagram2D*)pSeries->GetDiagram();
        
        pDiagram->GetAxisY()->GetGridLines()->SetMinorVisible(TRUE);
        pDiagram->GetAxisY()->GetGridLines()->GetMinorLineStyle()->SetDashStyle(xtpChartDashStyleDot);
        
        pDiagram->GetAxisY()->GetTitle()->SetText(_T("US Dollars"));
        pDiagram->GetAxisY()->GetTitle()->SetVisible(TRUE);
        
        pDiagram->GetAxisY()->GetRange()->SetShowZeroLevel(FALSE);
        
        pDiagram->GetAxisX()->GetLabel()->SetAngle(360-30);
        pDiagram->GetAxisX()->GetLabel()->SetAntialiasing(TRUE);
        
        pSeries->SetArgumentScaleType(xtpChartScaleQualitative);
        pDiagram->GetAxisX()->GetLabel()->SetVisible(TRUE);
        
        pDiagram->GetAxisX()->GetCustomLabels()->RemoveAll();
        
        int nUpperBound = int(arrQuote.GetUpperBound());
        
        for (int i=nUpperBound; i > 0; --i)
        {
            AddDate(pSeries,
                CQuandlAPI::Inst().GetDate (arrQuote[i]),
                CQuandlAPI::Inst().GetLow  (arrQuote[i]),
                CQuandlAPI::Inst().GetHigh (arrQuote[i]),
                CQuandlAPI::Inst().GetOpen (arrQuote[i]),
                CQuandlAPI::Inst().GetClose(arrQuote[i]));
            
            if ((i % 10) == 0)
            {
                CXTPChartAxisCustomLabel* pLabel = new CXTPChartAxisCustomLabel();
                pLabel->SetAxisValue(CQuandlAPI::Inst().GetDate(arrQuote[i]));
                pLabel->SetText(CQuandlAPI::Inst().GetDate(arrQuote[i]));
                pDiagram->GetAxisX()->GetCustomLabels()->Add(pLabel);
            }
        }
    }
    else
    {
        CQuandlAPI::Inst().ShowError();
    }
}

int CStockSampleView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// create the chart control.
	if (!m_wndChartControl.Create(WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, 0))
	{
		TRACE0("Error creating chart control.\n");
		return -1;
	}

	m_wndChartControl.GetContent()->GetAppearance()->LoadAppearance(_T("CHART_APPEARANCE_GRAY"));

	// set chart title.
	CXTPChartTitleCollection* pTitles = m_wndChartControl.GetContent()->GetTitles();
	CXTPChartTitle* pTitle = pTitles->Add(new CXTPChartTitle());
	pTitle->SetText(_T("Historical Stock Prices"));

	// set chart subtitle.
	CXTPChartTitle* pSubTitle = pTitles->Add(new CXTPChartTitle());
	pSubTitle->SetText(_T("www.codejock.com"));
	pSubTitle->SetDocking(xtpChartDockBottom);
	pSubTitle->SetAlignment(xtpChartAlignFar);
	pSubTitle->SetFont(CXTPChartFont::GetTahoma8());
	pSubTitle->SetTextColor(CXTPChartColor::Gray);

	// turn off legend.
	m_wndChartControl.GetContent()->GetLegend()->SetVisible(FALSE);

	// create stock quote dialog.
	if (m_dlgStockQuote.Create(IDD_STOCKQUOTE, this))
	{
		// get the client area size.
		CRect rcClient;
		GetParentFrame()->GetClientRect(&rcClient);
		GetParentFrame()->ClientToScreen(&rcClient);
		
		CRect rcDialog;
		m_dlgStockQuote.GetWindowRect(&rcDialog);
		
		// offset client rect and determine dialog position.
		rcClient.OffsetRect(-20,-40);
		rcClient.left = rcClient.right - rcDialog.Width();
		rcClient.top = rcClient.bottom - rcDialog.Height();
		
		// quote dialog at new location.
		m_dlgStockQuote.MoveWindow(&rcClient, FALSE);
		m_dlgStockQuote.ShowWindow(SW_SHOW);
	}

	return 0;
}

void CStockSampleView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if (m_wndChartControl.GetSafeHwnd())
	{
		m_wndChartControl.MoveWindow(0, 0, cx, cy);
	}
}

BOOL CStockSampleView::OnEraseBkgnd(CDC* pDC) 
{
	UNREFERENCED_PARAMETER(pDC);
	return TRUE;
}

void CStockSampleView::OnSetFocus(CWnd* pOldWnd) 
{
	m_wndChartControl.SetFocus();
}

void CStockSampleView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (m_dlgStockQuote.m_hWnd == (HWND)lHint)
	{
        if (pHint)
        {
            if (m_dlgStockQuote.m_bThickLines != m_bThickLine)
            {
                OnViewThickstyle();
            }
        }
        else
        {
		    UpdateHistory(m_dlgStockQuote.m_strTicker, (m_dlgStockQuote.m_nStyle == 0));
        }
    }
}

void CStockSampleView::OnViewStockquote() 
{
	if (::IsWindow(m_dlgStockQuote.m_hWnd))
	{
		m_dlgStockQuote.ShowWindow(
			m_dlgStockQuote.IsWindowVisible() ? SW_HIDE : SW_SHOW);
	}
}

void CStockSampleView::OnUpdateViewStockquote(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_dlgStockQuote.IsWindowVisible());
}

void CStockSampleView::SetThickStyle(BOOL bThickLine)
{
	m_bThickLine = bThickLine;

	CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);
	CXTPChartHighLowSeriesStyle* pStyle = (CXTPChartHighLowSeriesStyle*)pSeries->GetStyle();

	pStyle->SetLineThickness(m_bThickLine ? 2 : 1);
}

void CStockSampleView::OnViewThickstyle()
{
    SetThickStyle(!m_bThickLine);

    if (m_dlgStockQuote.m_bThickLines != m_bThickLine)
    {
        m_dlgStockQuote.m_bThickLines = m_bThickLine;
        m_dlgStockQuote.UpdateData(FALSE);
    }
}

void CStockSampleView::OnUpdateViewThickstyle(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bThickLine ? 1 : 0);
}

void CStockSampleView::OnViewCandles()
{
	m_bCandleStick = !m_bCandleStick;	

	CXTPChartHighLowSeriesStyle* pStyle;

	CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);
	
	if (m_bCandleStick)
		pStyle = (CXTPChartHighLowSeriesStyle*)pSeries->SetStyle(new CXTPChartCandleStickSeriesStyle());
	else
		pStyle = (CXTPChartHighLowSeriesStyle*)pSeries->SetStyle(new CXTPChartHighLowSeriesStyle());

	pStyle->SetLineThickness(m_bThickLine ? 2 : 1);

	if (m_dlgStockQuote.GetSafeHwnd())
	{
		m_dlgStockQuote.m_nStyle = m_bCandleStick ? 0 : 1;
		m_dlgStockQuote.UpdateData(FALSE);
	}
}

void CStockSampleView::OnUpdateViewCandles(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bCandleStick ? 1 : 0);
}


/////////////////////////////////////////////////////////////////////////////
// CStockSampleView printing

void CStockSampleView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	//CXTPFlowGraphDrawContext dc(pDC->m_hDC, pDC->m_hAttribDC);
	//m_wndControl.OnDraw(&dc);
	
	m_wndChartControl.PrintToDC(pDC->m_hDC, pInfo->m_rectDraw);
}

BOOL CStockSampleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	pInfo->m_nNumPreviewPages = 1;
	pInfo->SetMinPage(1);
	pInfo->SetMaxPage(1);
	
	
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CStockSampleView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);
	
	if (!pInfo)
		return;
	
	HDC hScreenDC = ::GetDC(NULL);
	int nLogPixelsX = ::GetDeviceCaps(hScreenDC, LOGPIXELSX);
	int nLogPixelsY = ::GetDeviceCaps(hScreenDC, LOGPIXELSY);
	VERIFY(1 == ::ReleaseDC(NULL, hScreenDC));

	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(nLogPixelsX, nLogPixelsY);
	pDC->SetViewportExt(pDC->GetDeviceCaps(LOGPIXELSX), pDC->GetDeviceCaps(LOGPIXELSY));
	
	// ptOrg is in logical coordinates
	pDC->OffsetWindowOrg(0, 0);
}


void CStockSampleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CStockSampleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CStockSampleView::OnFilePrintPreview()
{
#ifdef __XTPPREVIEWVIEW_H__
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
#else
	CView::OnFilePrintPreview();
#endif
	
}
