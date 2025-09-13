// CandleStickView.cpp
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
#include "ChartBrowser.h"
#include "CandleStickView.h"


// CCandleStickView

IMPLEMENT_DYNCREATE(CCandleStickView, CHighLowView)

CCandleStickView::CCandleStickView()
	: CHighLowView(CCandleStickView::IDD)
{

}

CCandleStickView::~CCandleStickView()
{
}

void CCandleStickView::DoDataExchange(CDataExchange* pDX)
{
	CHighLowView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCandleStickView, CHighLowView)
END_MESSAGE_MAP()


// CCandleStickView diagnostics

#ifdef _DEBUG
void CCandleStickView::AssertValid() const
{
	CHighLowView::AssertValid();
}

#ifndef _WIN32_WCE
void CCandleStickView::Dump(CDumpContext& dc) const
{
	CHighLowView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCandleStickView message handlers
void CCandleStickView::OnInitialUpdate() 
{
	CHighLowView::OnInitialUpdate();

	CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);

	pSeries->SetStyle(new CXTPChartCandleStickSeriesStyle());
}
