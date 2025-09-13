// Pie3dView.cpp
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
#include "ComponentSliderCtrl.h"
#include "3dParametersDlg.h"
#include "Pie3dOptionsDlg.h"
#include "Pie3dView.h"


// CPie3dView

IMPLEMENT_DYNCREATE(CPie3dView, CBase3dView)

CPie3dView::CPie3dView(UINT nID)
	: CBase3dView(nID)
	, m_pOptionsDlg(NULL)
{
	m_strCaption = _T("3D Pie Style");
}

CPie3dView::~CPie3dView()
{
	SAFE_DELETE(m_pOptionsDlg);
}

void CPie3dView::DoDataExchange(CDataExchange* pDX)
{
	CBase3dView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);
}

BEGIN_MESSAGE_MAP(CPie3dView, CBase3dView)
END_MESSAGE_MAP()

// CPie3dView diagnostics

#ifdef _DEBUG
void CPie3dView::AssertValid() const
{
	CBase3dView::AssertValid();
}

#ifndef _WIN32_WCE
void CPie3dView::Dump(CDumpContext& dc) const
{
	CBase3dView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPie3dView message handlers


void CPie3dView::OnInitialUpdate() 
{
	CBase3dView::OnInitialUpdate();

	m_pOptionsDlg = new CPie3dOptionsDlg(*this, &m_wndTabControl);
	if (m_pOptionsDlg->Create(CPie3dOptionsDlg::IDD, &m_wndTabControl))
	{
		m_pOptionsDlg->SetWindowText(_T("Options"));
		AddTab(0, m_pOptionsDlg);
		SetActiveTab(0);
	}
	else
	{
		TRACE(_T("Unable to create CPie3dOptionsDlg.\n"));
	}

	m_wndTabControl.SetCurSel(0);

	CreateChart();
}

static CXTPChartSeriesPoint* CreatPiePoint(LPCTSTR lpszLegendText, double nYear, double nValue, double dWidth, BOOL bPie)
{
	CXTPChartSeriesPoint* pPoint = new CXTPChartSeriesPoint(nYear, nValue, dWidth);
	pPoint->SetLegentText(lpszLegendText);
	return pPoint;
}

void CPie3dView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	pContent->GetLegend()->SetVisible(TRUE);

	CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	pTitle->SetText(_T("Top 10 States by Population"));

	CXTPChartSeries* pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());

	pSeries->SetName(_T("Top 10 States by Population"));
	CXTPChart3dPieSeriesStyle* pStyle = new CXTPChart3dPieSeriesStyle();
	pSeries->SetStyle(pStyle);

	CXTPChart3dRotation chartRotation = pStyle->Get3dRotation();
	chartRotation.m_dYaw += 30;
	chartRotation.m_dRoll -= 10;
	pStyle->Set3dRotation(chartRotation);

	CXTPChartSeriesPoint* pPoint = NULL;
	CXTPChartSeriesPointCollection* pPoints = pSeries->GetPoints();
	BOOL bPie = TRUE;

	pPoint = pPoints->Add(CreatPiePoint(_T("California"), 10, 37.623, 11.95, bPie));
	pPoint->m_bSpecial = TRUE;
	pPoint = pPoints->Add(CreatPiePoint(_T("Texas"), 9, 25.532, 7.81, bPie));
	pPoint = pPoints->Add(CreatPiePoint(_T("New York"), 8, 20.987, 6.31, bPie));
	pPoint = pPoints->Add(CreatPiePoint(_T("Florida"), 7, 18.145, 5.97, bPie));
	pPoint = pPoints->Add(CreatPiePoint(_T("Illinois"), 6, 13.320, 4.2, bPie));
	pPoint->m_bSpecial = TRUE;
	pPoint = pPoints->Add(CreatPiePoint(_T("Pennsylvania"), 5, 12.875, 4.06, bPie));
	pPoint = pPoints->Add(CreatPiePoint(_T("Ohio"), 4, 11.650, 3.75, bPie));
	pPoint = pPoints->Add(CreatPiePoint(_T("Michigan"), 3, 10.340, 3.29, bPie));
	pPoint->m_bSpecial = TRUE;
	pPoint = pPoints->Add(CreatPiePoint(_T("Georgia"), 2, 9.964, 3.12, bPie));
	pPoint = pPoints->Add(CreatPiePoint(_T("North Carolina"), 1, 9.120, 3, bPie));

	pStyle->GetLabel()->SetFormat(_T("{V} Million"));

	if (NULL != m_p3dParametersDlg)
	{
		CXTPChartDiagram3DAppearance* p3dAppearance = m_wndChartControl.GetContent()->GetAppearance()->GetDiagram3DAppearance();
		ASSERT(NULL != p3dAppearance);
		m_p3dParametersDlg->SetRotation(pStyle->Get3dRotation());
		m_p3dParametersDlg->SetLightPosition(p3dAppearance->LightPosition);
		m_p3dParametersDlg->SetLightModelAmbientColor(p3dAppearance->LightModelAmbientColor);
		m_p3dParametersDlg->SetLightAmbientColor(p3dAppearance->LightAmbientColor);
		m_p3dParametersDlg->SetLightDiffuseColor(p3dAppearance->LightDiffuseColor);
		m_p3dParametersDlg->SetLightSpecularColor(p3dAppearance->LightSpecularColor);
		m_p3dParametersDlg->SetMaterialEmissionColor(p3dAppearance->MaterialEmissionColor);
		m_p3dParametersDlg->SetMaterialDiffuseColor(p3dAppearance->MaterialDiffuseColor);
		m_p3dParametersDlg->SetMaterialSpecularColor(p3dAppearance->MaterialSpecularColor);
		m_p3dParametersDlg->SetMaterialShininess(p3dAppearance->MaterialShininess);
	}
}

void CPie3dView::OnBnClickedCheckShowLabels()
{
	if (NULL != m_pOptionsDlg)
	{
		CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

		for (int i = 0; i < pSeriesCollection->GetCount(); i++)
		{
			CXTPChartSeriesStyle* pStyle = pSeriesCollection->GetAt(i)->GetStyle();
			pStyle->GetLabel()->SetVisible(m_pOptionsDlg->GetShowLabelsValue());
		}

		m_pOptionsDlg->GetDlgItem(IDC_COMBO_LABEL_POSITION)->EnableWindow(m_pOptionsDlg->GetShowLabelsValue());
	}
}

void CPie3dView::OnCbnSelChangeComboLabelPosition()
{
	if (NULL != m_pOptionsDlg)
	{
		CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();
		CXTPChartPieSeriesStyle* pStyle = (CXTPChartPieSeriesStyle*)pSeriesCollection->GetAt(0)->GetStyle();
		CXTPChartPieSeriesLabel* pLabel = (CXTPChartPieSeriesLabel*)pStyle->GetLabel();
		pLabel->SetPosition(static_cast<XTPChartPieLabelPosition>(m_pOptionsDlg->GetPositionValue()));
	}
}

void CPie3dView::OnCbnSelChangeComboExplodedPoints()
{
	if (NULL != m_pOptionsDlg)
	{
		CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);

		int i;
		for (i = 0; i < pSeries->GetPoints()->GetCount(); i++)
		{
			CXTPChartSeriesPoint* pPoint = pSeries->GetPoints()->GetAt(i);
			ASSERT(NULL != pPoint);

			pPoint->m_bSpecial = (m_pOptionsDlg->GetExplodedPointsValue() == 1);
		}

		if (m_pOptionsDlg->GetExplodedPointsValue() == 2)
		{
			pSeries->GetPoints()->GetAt(0)->m_bSpecial = TRUE;
			pSeries->GetPoints()->GetAt(4)->m_bSpecial = TRUE;
			pSeries->GetPoints()->GetAt(7)->m_bSpecial = TRUE;
		}

		m_wndChartControl.OnChartChanged();
	}
}

void CPie3dView::OnEnChangeEditDepth()
{
	if (NULL != m_pOptionsDlg)
	{
		int nDepth = m_pOptionsDlg->GetTorusDepthValue();
		if (nDepth > 0 && nDepth <= 40)
		{
			CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);
			CXTPChart3dPieSeriesStyle* pStyle = DYNAMIC_DOWNCAST(CXTPChart3dPieSeriesStyle, pSeries->GetStyle());
			if (NULL != pStyle)
			{
				pStyle->SetDepth(nDepth);
			}
		}
	}
}
