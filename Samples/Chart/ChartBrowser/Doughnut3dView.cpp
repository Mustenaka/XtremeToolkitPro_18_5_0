// Doughnut3dView.cpp
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
#include "BaseView.h"
#include "Pie3dOptionsDlg.h"
#include "Doughnut3dView.h"


// CDoughnut3dView

IMPLEMENT_DYNCREATE(CDoughnut3dView, CPie3dView)

CDoughnut3dView::CDoughnut3dView(UINT nID)
	: CPie3dView(nID)	
{
	m_strCaption = _T("3D Doughnut Style");
}

CDoughnut3dView::~CDoughnut3dView()
{
}

BEGIN_MESSAGE_MAP(CDoughnut3dView, CPie3dView)
END_MESSAGE_MAP()


// CDoughnut3dView diagnostics

#ifdef _DEBUG
void CDoughnut3dView::AssertValid() const
{
	CPie3dView::AssertValid();
}

#ifndef _WIN32_WCE
void CDoughnut3dView::Dump(CDumpContext& dc) const
{
	CPie3dView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDoughnut3dView message handlers

void CDoughnut3dView::OnInitialUpdate() 
{
	CPie3dView::OnInitialUpdate();

	CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);
	CXTPChartPieSeriesStyleBase* pStyle = DYNAMIC_DOWNCAST(CXTPChartPieSeriesStyleBase, pSeries->GetStyle());
	if (NULL != pStyle)
	{
		pStyle->SetHolePercent(60);
	}

	if (NULL != m_pOptionsDlg)
	{
		m_pOptionsDlg->ShowDoughnutControls();
	}
}

void CDoughnut3dView::OnEnChangeEditHoleRadius()
{
	UpdateData();

	if (NULL != m_pOptionsDlg)
	{
		int nHoleRadius = m_pOptionsDlg->GetDoughnutHoleRadiusValue();
		if (nHoleRadius > 0 && nHoleRadius <= 100)
		{
			CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);
			CXTPChartPieSeriesStyleBase* pStyle = DYNAMIC_DOWNCAST(CXTPChartPieSeriesStyleBase, pSeries->GetStyle());
			if (NULL != pStyle)
			{
				pStyle->SetHolePercent(nHoleRadius);
			}
		}
	}
}
