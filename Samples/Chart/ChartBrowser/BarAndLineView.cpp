// BarAndLineView.cpp
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
#include "BarAndLineView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBarAndLineView

IMPLEMENT_DYNCREATE(CBarAndLineView, CBaseView)

CBarAndLineView::CBarAndLineView()
	: CBaseView(CBarAndLineView::IDD)
{
	//{{AFX_DATA_INIT(CBarAndLineView)
	m_bShowLabels = TRUE;
	m_bRotated = FALSE;
	//}}AFX_DATA_INIT

	m_strCaption = _T("Combination Chart");
}

CBarAndLineView::~CBarAndLineView()
{
} 

void CBarAndLineView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBarAndLineView)
	//DDX_Control(pDX, IDC_COMBO_LABEL_POSITION, m_cboPosition);
	//DDX_Control(pDX, IDC_CHECK_SHOWLABELS, m_chkShowLabels);
	DDX_Check(pDX, IDC_CHECK_SHOWLABELS, m_bShowLabels);
	DDX_Check(pDX, IDC_CHECK_ROTATED, m_bRotated);
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);

}


BEGIN_MESSAGE_MAP(CBarAndLineView, CBaseView)
	//{{AFX_MSG_MAP(CBarAndLineView)
	ON_BN_CLICKED(IDC_CHECK_SHOWLABELS, OnCheckShowLabels)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CHECK_ROTATED, OnBnClickedCheckRotated)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBarAndLineView diagnostics

#ifdef _DEBUG
void CBarAndLineView::AssertValid() const
{
	CBaseView::AssertValid();
}

void CBarAndLineView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBarAndLineView message handlers


void CBarAndLineView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();

	CreateChart();
}

void CBarAndLineView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();
	pContent->GetLegend()->SetVisible(TRUE);
	pContent->GetLegend()->SetHorizontalAlignment(xtpChartLegendNearOutside);


	CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	pTitle->SetText(_T("Population by U.S. State"));

	CXTPChartSeries* pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());
	pSeries->SetName(_T("New York"));
	pSeries->SetStyle(new CXTPChartSplineSeriesStyle());
	pSeries->GetStyle()->GetLabel()->GetFormat()->SetCategory(xtpChartNumber);
	pSeries->GetStyle()->GetLabel()->GetFormat()->SetDecimalPlaces(0);

    pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(1900, 7268));
    pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(1950, 14830));
    pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(1990, 17990));
    pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(2000, 18976));
    pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(2008, 20323));
    
	pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());
    pSeries->SetName(_T("California"));
	pSeries->SetStyle(new CXTPChartBarSeriesStyle());
	pSeries->GetStyle()->GetLabel()->GetFormat()->SetCategory(xtpChartNumber);
	pSeries->GetStyle()->GetLabel()->GetFormat()->SetDecimalPlaces(0);

    pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(1900, 1485));
    pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(1950, 10586));
    pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(1990, 29760));
    pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(2000, 33871));
    pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(2008, 36756));
    
	pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());
    pSeries->SetName(_T("Florida"));
	pSeries->SetStyle(new CXTPChartPointSeriesStyle());
	pSeries->GetStyle()->GetLabel()->GetFormat()->SetCategory(xtpChartNumber);
	pSeries->GetStyle()->GetLabel()->GetFormat()->SetDecimalPlaces(0);

    pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(1900, 528));
    pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(1950, 2771));
    pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(1990, 12937));
    pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(2000, 15982));
    pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(2008, 18328));
        
	pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());
    pSeries->SetName(_T("Texas"));
	pSeries->SetStyle(new CXTPChartAreaSeriesStyle());
	pSeries->GetStyle()->GetLabel()->GetFormat()->SetCategory(xtpChartNumber);
	pSeries->GetStyle()->GetLabel()->GetFormat()->SetDecimalPlaces(0);

    pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(1900, 3048));
    pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(1950, 7711));
    pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(1990, 14986));
    pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(2000, 20851));
    pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(2008, 24326));

	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries->GetDiagram());
	ASSERT (pDiagram);

	pDiagram->GetAxisX()->GetTitle()->SetVisible(TRUE);
	pDiagram->GetAxisX()->GetTitle()->SetText(_T("Decade / Year"));

	pDiagram->GetAxisY()->GetTitle()->SetVisible(TRUE);
	pDiagram->GetAxisY()->GetTitle()->SetText(_T("Population Growth (Millions)"));
	pDiagram->GetAxisY()->GetLabel()->GetFormat()->SetCategory(xtpChartNumber);
	pDiagram->GetAxisY()->GetLabel()->GetFormat()->SetDecimalPlaces(0);
}

void CBarAndLineView::OnCheckShowLabels() 
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartSeriesStyle* pStyle = pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetLabel()->SetVisible(m_bShowLabels);
	}	
}

void CBarAndLineView::OnBnClickedCheckRotated()
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	CXTPChartDiagram2D* pDiagram = STATIC_DOWNCAST(CXTPChartDiagram2D, pSeriesCollection->GetAt(0)->GetDiagram());

	pDiagram->SetRotated(m_bRotated);


}
