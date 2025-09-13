// SecondaryAxesView.cpp
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
#include "SecondaryAxesView.h"


// CSecondaryAxesView

IMPLEMENT_DYNCREATE(CSecondaryAxesView, CBaseView)

CSecondaryAxesView::CSecondaryAxesView()
	: CBaseView(CSecondaryAxesView::IDD)
{
	m_strCaption = _T("Secondary Axes");
	
	m_bSecondaryAxisX = TRUE;
	m_bSecondaryAxisY = TRUE;

	m_bVisibleX = TRUE;
	m_bVisibleY = TRUE;
}

CSecondaryAxesView::~CSecondaryAxesView()
{
}

void CSecondaryAxesView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);

	DDX_Check(pDX, IDC_CHECK_AXISX, m_bSecondaryAxisX);
	DDX_Check(pDX, IDC_CHECK_AXISY, m_bSecondaryAxisY);

	DDX_Check(pDX, IDC_CHECK_VISIBLEX, m_bVisibleX);
	DDX_Check(pDX, IDC_CHECK_VISIBLEY, m_bVisibleY);

}

BEGIN_MESSAGE_MAP(CSecondaryAxesView, CBaseView)
	ON_BN_CLICKED(IDC_CHECK_AXISX, OnCheckSecondaryAxisX)
	ON_BN_CLICKED(IDC_CHECK_AXISY, OnCheckSecondaryAxisY)

	ON_BN_CLICKED(IDC_CHECK_VISIBLEX, OnCheckVisibleX)
	ON_BN_CLICKED(IDC_CHECK_VISIBLEY, OnCheckVisibleY)
END_MESSAGE_MAP()


// CSecondaryAxesView diagnostics

#ifdef _DEBUG
void CSecondaryAxesView::AssertValid() const
{
	CBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CSecondaryAxesView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSecondaryAxesView message handlers


void CSecondaryAxesView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();


	CreateChart();
}



void CSecondaryAxesView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	pContent->GetLegend()->SetVisible(TRUE);

	CXTPChartSeriesCollection* pCollection = pContent->GetSeries();
	pCollection->RemoveAll();

	if (pCollection)
	{
		CXTPChartSeries* pSeries1 = pCollection->Add(new CXTPChartSeries());
		if (pSeries1)
		{
			pSeries1->SetName(_T("Series 1"));

			CXTPChartSeriesPointCollection* pPoints = pSeries1->GetPoints();
			if (pPoints)
			{
				CXTPChartSeriesPoint* pPoint = NULL;

				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("A"), 1200));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("B"), 700));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("C"), 500));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("D"), 400));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("E"), 300));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("F"), 200));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("G"), 150));
			}

			CXTPChartLineSeriesStyle* pStyle = new CXTPChartLineSeriesStyle();
			pSeries1->SetStyle(pStyle);
			pStyle->GetMarker()->SetType(xtpChartMarkerTriangle);
			pStyle->GetMarker()->SetSize(16);
		}

		CXTPChartSeries* pSeries2 = pCollection->Add(new CXTPChartSeries());
		if (pSeries2)
		{
			pSeries2->SetName(_T("Series 2"));

			CXTPChartSeriesPointCollection* pPoints = pSeries2->GetPoints();
			if (pPoints)
			{
				CXTPChartSeriesPoint* pPoint = NULL;
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("A"), 65));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("B"), 55));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("C"), 45));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("D"), 35));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("E"), 25));
			}

			CXTPChartLineSeriesStyle* pStyle = new CXTPChartLineSeriesStyle();
			pSeries2->SetStyle(pStyle);
			pStyle->GetMarker()->SetType(xtpChartMarkerSquare);
			pStyle->GetMarker()->SetSize(16);
			pStyle->SetSecondaryAxisX(TRUE);
			pStyle->SetSecondaryAxisY(TRUE);
			pStyle->SetAxisIndexX(1);
			pStyle->SetAxisIndexY(1);
		}
	
		CXTPChartSeries* pSeries3 = pCollection->Add(new CXTPChartSeries());
		if (pSeries3)
		{
			pSeries3->SetName(_T("Series 3"));

			CXTPChartSeriesPointCollection* pPoints = pSeries3->GetPoints();
			if (pPoints)
			{
				CXTPChartSeriesPoint* pPoint = NULL;
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("A"), 500));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("B"), 400));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("C"), 300));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("D"), 200));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("E"), 150));
			}

			CXTPChartLineSeriesStyle* pStyle = new CXTPChartLineSeriesStyle();
			pSeries3->SetStyle(pStyle);
			pStyle->GetMarker()->SetType(xtpChartMarkerStar);
			pStyle->GetMarker()->SetSize(16);
			pStyle->SetSecondaryAxisX(FALSE);
			pStyle->SetSecondaryAxisY(TRUE);
			pStyle->SetAxisIndexY(2);
		}
	}

	CXTPChartDiagram2D* pDiagram = (CXTPChartDiagram2D*)m_wndChartControl.GetContent()->GetPanels()->GetAt(0);

	pDiagram->SetAxisCountX(2);
	pDiagram->SetAxisCountY(3);

	OnCheckSecondaryAxisX();
	OnCheckSecondaryAxisY();
}



void CSecondaryAxesView::OnCheckSecondaryAxisX() 
{
	UpdateData();

	CXTPChartDiagram2D* pDiagram = (CXTPChartDiagram2D*)m_wndChartControl.GetContent()->GetPanels()->GetAt(0);

	if (!m_bSecondaryAxisX)
	{
		pDiagram->GetSecondaryAxisX()->SetVisible(FALSE);
	}
	else
	{
		OnCheckVisibleX();
	}

	if (m_bSecondaryAxisX)
	{
		pDiagram->GetSecondaryAxisX()->GetTitle()->SetText(_T("Series 2 (Secondary Axis X)"));
		pDiagram->GetSecondaryAxisX()->GetTitle()->SetVisible(TRUE);

		pDiagram->GetAxisX()->GetTitle()->SetText(_T("Series 1 (Primary Axis X)"));
		pDiagram->GetAxisX()->GetTitle()->SetVisible(TRUE);
	}
	else
	{
		pDiagram->GetAxisX()->GetTitle()->SetText(_T("Series 1, Series2 (Primary Axis X)"));
		pDiagram->GetAxisX()->GetTitle()->SetVisible(TRUE);
	}

	{
		CXTPChartPointSeriesStyle* pStyle = (CXTPChartPointSeriesStyle*)m_wndChartControl.GetContent()->GetSeries()->GetAt(1)->GetStyle();
		pStyle->SetSecondaryAxisX(m_bSecondaryAxisX);
	}

	GetDlgItem(IDC_CHECK_VISIBLEX)->EnableWindow(m_bSecondaryAxisX);
}

void CSecondaryAxesView::OnCheckSecondaryAxisY() 
{
	UpdateData();

	CXTPChartDiagram2D* pDiagram = (CXTPChartDiagram2D*)m_wndChartControl.GetContent()->GetPanels()->GetAt(0);
	
	if (!m_bSecondaryAxisY)
	{
		pDiagram->GetAxisY(1)->SetVisible(FALSE);
		pDiagram->GetAxisY(2)->SetVisible(FALSE);
	}
	else
	{
		OnCheckVisibleY();
	}


	if (m_bSecondaryAxisY)
	{
		pDiagram->GetAxisY(2)->GetTitle()->SetText(_T("Series 3 (Third Axis Y)"));
		pDiagram->GetAxisY(2)->GetTitle()->SetVisible(TRUE);

		pDiagram->GetAxisY(1)->GetTitle()->SetText(_T("Series 2 (Secondary Axis Y)"));
		pDiagram->GetAxisY(1)->GetTitle()->SetVisible(TRUE);
		
		pDiagram->GetAxisY(0)->GetTitle()->SetText(_T("Series 1 (Primary Axis Y)"));
		pDiagram->GetAxisY(0)->GetTitle()->SetVisible(TRUE);

		CXTPChartPointSeriesStyle *pStyle;
		pStyle = (CXTPChartPointSeriesStyle*)m_wndChartControl.GetContent()->GetSeries()->GetAt(1)->GetStyle();
		pStyle->SetSecondaryAxisY(TRUE);

		pStyle = (CXTPChartPointSeriesStyle*)m_wndChartControl.GetContent()->GetSeries()->GetAt(2)->GetStyle();
		pStyle->SetSecondaryAxisY(TRUE);
	}
	else
	{
		pDiagram->GetAxisY()->GetTitle()->SetText(_T("Series 1, 2 and 3 (Primary Axis Y)"));
		pDiagram->GetAxisY()->GetTitle()->SetVisible(TRUE);

		CXTPChartPointSeriesStyle *pStyle;
		pStyle = (CXTPChartPointSeriesStyle*)m_wndChartControl.GetContent()->GetSeries()->GetAt(1)->GetStyle();
		pStyle->SetSecondaryAxisY(FALSE);

		pStyle = (CXTPChartPointSeriesStyle*)m_wndChartControl.GetContent()->GetSeries()->GetAt(2)->GetStyle();
		pStyle->SetSecondaryAxisY(FALSE);
	}

	GetDlgItem(IDC_CHECK_VISIBLEY)->EnableWindow(m_bSecondaryAxisY);
}

void CSecondaryAxesView::OnCheckVisibleX()
{
	UpdateData();

	CXTPChartDiagram2D* pDiagram = (CXTPChartDiagram2D*)m_wndChartControl.GetContent()->GetPanels()->GetAt(0);
	
	pDiagram->GetSecondaryAxisX()->SetVisible(m_bVisibleX);

}


void CSecondaryAxesView::OnCheckVisibleY()
{
	UpdateData();

	CXTPChartDiagram2D* pDiagram = (CXTPChartDiagram2D*)m_wndChartControl.GetContent()->GetPanels()->GetAt(0);
	
	pDiagram->GetAxisY(1)->SetVisible(m_bVisibleY);
	pDiagram->GetAxisY(2)->SetVisible(m_bVisibleY);
}