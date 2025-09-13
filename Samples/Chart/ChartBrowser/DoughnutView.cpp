// DoughnutView.cpp
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
#include "DoughnutView.h"


// CDoughnutView

IMPLEMENT_DYNCREATE(CDoughnutView, CPieView)

CDoughnutView::CDoughnutView(UINT nID)
	: CPieView(nID)	
{
	m_strCaption = _T("Doughnut Style");
	m_nHoleRadius = 60;

}

CDoughnutView::~CDoughnutView()
{
}

void CDoughnutView::DoDataExchange(CDataExchange* pDX)
{
	CPieView::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_HOLE_RADIUS, m_nHoleRadius);
}

BEGIN_MESSAGE_MAP(CDoughnutView, CPieView)
	ON_EN_CHANGE(IDC_EDIT_HOLE_RADIUS, OnEnChangeEditHoleRadius)
END_MESSAGE_MAP()


// CDoughnutView diagnostics

#ifdef _DEBUG
void CDoughnutView::AssertValid() const
{
	CPieView::AssertValid();
}

#ifndef _WIN32_WCE
void CDoughnutView::Dump(CDumpContext& dc) const
{
	CPieView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDoughnutView message handlers

void CDoughnutView::OnInitialUpdate() 
{
	CPieView::OnInitialUpdate();

	CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);

	CXTPChartPieSeriesStyle* pStyle = (CXTPChartPieSeriesStyle*)pSeries->GetStyle();

	pStyle->SetHolePercent(60);
}

void CDoughnutView::OnEnChangeEditHoleRadius()
{
	UpdateData();

	if (m_nHoleRadius > 0 && m_nHoleRadius <= 100)
	{
		CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);

		CXTPChartPieSeriesStyle* pStyle = (CXTPChartPieSeriesStyle*)pSeries->GetStyle();

		pStyle->SetHolePercent(m_nHoleRadius);

	}
}
