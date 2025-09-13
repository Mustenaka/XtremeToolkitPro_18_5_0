// AnalysisView.cpp
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

#include "StdAfx.h"
#include "ChartBrowser.h"
#include "AnalysisView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnalysisView

IMPLEMENT_DYNCREATE(CAnalysisView, CBaseView)

CAnalysisView::CAnalysisView()
	: CBaseView(CAnalysisView::IDD)
{
	//{{AFX_DATA_INIT(CAnalysisView)
	m_bRotated       = FALSE;
	m_bShowErrorBars = TRUE;
	m_bShowCaps      = TRUE;
	m_nStyle         = styleBar;
	m_nType          = xtpChartErrorBarTypeStandardDeviation;
	m_nDirection     = xtpChartErrorBarDirectionBoth;
	m_nTrendline     = xtpChartSeriesTrendlineTypeLinear;
	//}}AFX_DATA_INIT

	m_strCaption = _T("Analysis");
}

CAnalysisView::~CAnalysisView()
{
} 

void CAnalysisView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnalysisView)
	DDX_Control(pDX, IDC_COMBO_DIRECTION, m_wndDirection);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_wndType);
	DDX_Check(pDX, IDC_CHECK_ROTATED,       m_bRotated);
	DDX_Check(pDX, IDC_CHECK_SHOWERRORBARS, m_bShowErrorBars);
	DDX_Check(pDX, IDC_CHECK_SHOWCAPS,      m_bShowCaps);
	DDX_CBIndex(pDX, IDC_COMBO_STYLE,     m_nStyle);
	DDX_CBIndex(pDX, IDC_COMBO_TYPE,      m_nType);
	DDX_CBIndex(pDX, IDC_COMBO_DIRECTION, m_nDirection);
	DDX_CBIndex(pDX, IDC_COMBO_TRENDLINE, m_nTrendline);
	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAnalysisView, CBaseView)
	//{{AFX_MSG_MAP(CAnalysisView)
	ON_BN_CLICKED(IDC_CHECK_ROTATED,       OnCheckRotated)
	ON_BN_CLICKED(IDC_CHECK_SHOWERRORBARS, OnCheckShowErrorBars)
	ON_BN_CLICKED(IDC_CHECK_SHOWCAPS,      OnCheckShowCaps)

	ON_CBN_SELCHANGE(IDC_COMBO_STYLE,     OnSelchangeStyle)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE,      OnSelchangeType)
	ON_CBN_SELCHANGE(IDC_COMBO_DIRECTION, OnSelchangeDirection)
	ON_CBN_SELCHANGE(IDC_COMBO_TRENDLINE, OnSelchangeTrendline)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnalysisView diagnostics

#ifdef _DEBUG
void CAnalysisView::AssertValid() const
{
	CBaseView::AssertValid();
}

void CAnalysisView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAnalysisView message handlers


LPCTSTR lpszErrorBarType[] =
{
	_T("None"),
	_T("Fixed value"),
	_T("Percentage"),
	_T("Standard deviation"),
	_T("Standard error"),
	_T("Custom"),
};


void CAnalysisView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();

	for(int n=0; n<_countof(lpszErrorBarType); n++)
	{
		m_wndType.AddString(lpszErrorBarType[n]);
	}

	CreateChart();

	UpdateData(FALSE);
}

void CAnalysisView::CreateChart()
{
	CXTPChartContent *pContent = m_wndChartControl.GetContent();

	pContent->GetLegend()->SetVisible(TRUE);

	CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	pTitle->SetText(_T("Orders"));

	CXTPChartSeries* pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());

	pSeries->SetName(_T("Year"));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(1950, 120.0)); //  1
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(1960,  90.0)); //  2
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(1970,  50.0)); //  3
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(1980, 120.0)); //  4
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(1990, 110.0)); //  5
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(2000,  80.0)); //  6
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(2005, 110.0)); //  7
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(2006, 120.0)); //  8
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(2007, 140.0)); //  9
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(2008, 160.0)); // 10
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(2009, 100.0)); // 11
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(2010,  80.0)); // 12
	UpdateChart();

	CXTPChartSeriesTrendline *pSeriesTrendline;
	
	pSeriesTrendline = new CXTPChartSeriesTrendline();
	pContent->GetSeries()->Add(pSeriesTrendline);
	pSeriesTrendline->SetSource(pSeries);
	pSeriesTrendline->SetType(xtpChartSeriesTrendlineTypeLinear);

	pSeriesTrendline = new CXTPChartSeriesTrendline();
	pContent->GetSeries()->Add(pSeriesTrendline);
	pSeriesTrendline->SetSource(pSeries);
	pSeriesTrendline->SetType(xtpChartSeriesTrendlineTypeMinimum);

	pSeriesTrendline = new CXTPChartSeriesTrendline();
	pContent->GetSeries()->Add(pSeriesTrendline);
	pSeriesTrendline->SetSource(pSeries);
	pSeriesTrendline->SetType(xtpChartSeriesTrendlineTypeMaximum);

	
	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries->GetDiagram());
	ASSERT (pDiagram);

	pDiagram->GetAxisX()->GetTitle()->SetVisible(TRUE);
	pDiagram->GetAxisX()->GetTitle()->SetText(_T("Year"));

	pDiagram->GetAxisY()->GetTitle()->SetVisible(TRUE);
	pDiagram->GetAxisY()->GetTitle()->SetText(_T("Orders"));
}

void CAnalysisView::OnCheckShowErrorBars() 
{
	UpdateData();
	UpdateChart();
}


void CAnalysisView::OnCheckShowCaps() 
{
	UpdateData();
	UpdateChart();
}

void CAnalysisView::OnCheckRotated()
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	CXTPChartDiagram2D* pDiagram = STATIC_DOWNCAST(CXTPChartDiagram2D, pSeriesCollection->GetAt(0)->GetDiagram());

	pDiagram->SetRotated(m_bRotated);
}

void CAnalysisView::OnSelchangeStyle()
{
	UpdateData();
	UpdateChart();
}

void CAnalysisView::OnSelchangeType()
{
	UpdateData();
	UpdateChart();
}

void CAnalysisView::OnSelchangeDirection()
{
	UpdateData();
	UpdateChart();
}

void CAnalysisView::OnSelchangeTrendline()
{
	UpdateData();
	UpdateChart();
}


void CAnalysisView::UpdateChart()
{
	CXTPChartContent *pContent = m_wndChartControl.GetContent();
	CXTPChartSeries *pSeries = pContent->GetSeries()->GetAt(0);

	switch(m_nStyle)
	{
	case styleBar:
		pSeries->SetStyle(new CXTPChartBarSeriesStyle());
		pSeries->SetArgumentScaleType(xtpChartScaleQualitative);
		break;
	case styleLine:
		pSeries->SetStyle(new CXTPChartLineSeriesStyle());
		pSeries->SetArgumentScaleType(xtpChartScaleQualitative);
		break;
	case stylePoint:
		pSeries->SetStyle(new CXTPChartPointSeriesStyle());
		pSeries->SetArgumentScaleType(xtpChartScaleNumerical);
		break;
	}

	CXTPChartErrorBar *pErrorBar = pSeries->GetStyle()->GetErrorBar();

	if (NULL != pErrorBar)
	{
		pErrorBar->SetVisible(m_bShowErrorBars);
		pErrorBar->SetEndStyle(m_bShowCaps ? xtpChartErrorBarEndStyleCap : xtpChartErrorBarEndStyleNoCap);
		pErrorBar->SetType(XTPChartErrorBarType(m_nType));
		pErrorBar->SetDirection(XTPChartErrorBarDirection(m_nDirection));
		pErrorBar->SetAmount(10);
		pErrorBar->SetValuePlus(20);
		pErrorBar->SetValueMinus(10);
	}

	CXTPChartSeriesTrendline *pTrendline = (CXTPChartSeriesTrendline*)pContent->GetSeries()->GetAt(1);

	if (NULL != pTrendline)
	{
		pTrendline->SetType(XTPChartSeriesTrendlineType(m_nTrendline));
	}
}
