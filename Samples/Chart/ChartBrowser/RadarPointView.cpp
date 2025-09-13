// RadarPointView.cpp
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
#include "RadarPointView.h"


// CRadarPointView

IMPLEMENT_DYNCREATE(CRadarPointView, CBaseView)

CRadarPointView::CRadarPointView()
	: CBaseView(CRadarPointView::IDD)
{
	m_strCaption = _T("Radar Point Style");
	m_bShowLabels = TRUE;
	
	m_bShowAxisX = 1;
	m_bShowAxisY = 1;
	m_nMarkerType = 0;
	m_nMarkerSize = 0;

	m_bInterlaced = FALSE;
}

CRadarPointView::~CRadarPointView()
{
}

void CRadarPointView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);

	DDX_Check(pDX, IDC_CHECK_SHOWLABELS, m_bShowLabels);
	DDX_Check(pDX, IDC_CHECK_AXISX, m_bShowAxisX);
	DDX_Check(pDX, IDC_CHECK_AXISY, m_bShowAxisY);
	DDX_Check(pDX, IDC_CHECK_INTERLACED, m_bInterlaced);

	DDX_CBIndex(pDX, IDC_COMBO_MARKER_TYPE, m_nMarkerType);
	DDX_CBIndex(pDX, IDC_COMBO_MARKER_SIZE, m_nMarkerSize);



}

BEGIN_MESSAGE_MAP(CRadarPointView, CBaseView)
	ON_BN_CLICKED(IDC_CHECK_SHOWLABELS, OnCheckShowLabels)

	ON_CBN_SELCHANGE(IDC_COMBO_MARKER_SIZE, OnCbnSelchangeComboMarkerSize)
	ON_CBN_SELCHANGE(IDC_COMBO_MARKER_TYPE, OnCbnSelchangeComboMarkerType)

	ON_BN_CLICKED(IDC_CHECK_AXISX, OnCheckShowAxisX)
	ON_BN_CLICKED(IDC_CHECK_AXISY, OnCheckShowAxisY)
	ON_BN_CLICKED(IDC_CHECK_INTERLACED, OnCheckInterlaced)

END_MESSAGE_MAP()


// CRadarPointView diagnostics

#ifdef _DEBUG
void CRadarPointView::AssertValid() const
{
	CBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CRadarPointView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CRadarPointView message handlers

void CRadarPointView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();


	CreateChart();

	int i;

	CComboBox* pComboBoxSize = (CComboBox*)GetDlgItem(IDC_COMBO_MARKER_SIZE);
	for (i = 8; i <= 30; i += 2)
	{
		CString strSize;
		strSize.Format(_T("%d"), i);

		pComboBoxSize->AddString(strSize);
	}
	pComboBoxSize->SetCurSel(0);

	OnCbnSelchangeComboMarkerSize();
}

void CRadarPointView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	pContent->GetLegend()->SetVisible(TRUE);

	CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	pTitle->SetText(_T("Radar Point Chart"));

	CXTPChartSeries* pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());
	pSeries->SetArgumentScaleType(xtpChartScaleNumerical);

	pSeries->SetName(_T("Points 1"));
	pSeries->SetStyle(new CXTPChartRadarPointSeriesStyle());

	int i;
	for (i = 0; i < 20; i++)
	{
		pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(rand() % 40, 50 + (rand() % 50)));
	}

	pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());
	pSeries->SetArgumentScaleType(xtpChartScaleNumerical);

	pSeries->SetName(_T("Points 2"));
	pSeries->SetStyle(new CXTPChartRadarPointSeriesStyle());

	for (i = 0; i < 20; i++)
	{
		pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(40 + (rand() % 40), rand() % 50));
	}


	CXTPChartRadarDiagram* pDiagram = DYNAMIC_DOWNCAST(CXTPChartRadarDiagram, pSeries->GetDiagram());
	ASSERT (pDiagram);

	pDiagram->GetAxisX()->SetInterlaced(m_bInterlaced);

	
}

void CRadarPointView::OnCheckShowLabels() 
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartRadarPointSeriesStyle* pStyle = (CXTPChartRadarPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetLabel()->SetVisible(m_bShowLabels);
	}
}

void CRadarPointView::OnCheckShowAxisX() 
{
	UpdateData();
	
	CXTPChartRadarDiagram* pDiagram = (CXTPChartRadarDiagram*)m_wndChartControl.GetContent()->GetPrimaryDiagram();
	
	pDiagram->GetAxisX()->SetVisible(m_bShowAxisX);
}

void CRadarPointView::OnCheckShowAxisY() 
{
	UpdateData();
	
	CXTPChartRadarDiagram* pDiagram = (CXTPChartRadarDiagram*)m_wndChartControl.GetContent()->GetPrimaryDiagram();
	
	pDiagram->GetAxisY()->SetVisible(m_bShowAxisY);
}

void CRadarPointView::OnCheckInterlaced() 
{
	UpdateData();
	
	CXTPChartRadarDiagram* pDiagram = (CXTPChartRadarDiagram*)m_wndChartControl.GetContent()->GetPrimaryDiagram();
	
	pDiagram->GetAxisX()->SetInterlaced(m_bInterlaced);
}





void CRadarPointView::OnCbnSelchangeComboMarkerSize()
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	int nMarkerSize = 8 + 2 * m_nMarkerSize;
	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartRadarPointSeriesStyle* pStyle = (CXTPChartRadarPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetMarker()->SetSize(nMarkerSize);

		// Solid Mode
		// pStyle->GetMarker()->GetFillStyle()->SetFillMode(xtpChartFillSolid);
	}

	m_wndChartControl.GetContent()->GetLegend()->SetMarkerSize(CSize(nMarkerSize + nMarkerSize / 2, nMarkerSize));
}


void CRadarPointView::OnCbnSelchangeComboMarkerType()
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartRadarPointSeriesStyle* pStyle = (CXTPChartRadarPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetMarker()->SetType((XTPChartMarkerType)m_nMarkerType);
	}
}