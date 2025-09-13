// Torus3dView.cpp
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
#include "Torus3dView.h"


// CTorus3dView

IMPLEMENT_DYNCREATE(CTorus3dView, CPie3dView)

CTorus3dView::CTorus3dView(UINT nID)
	: CPie3dView(nID)	
{
	m_strCaption = _T("3D Torus Style");
}

CTorus3dView::~CTorus3dView()
{
}

BEGIN_MESSAGE_MAP(CTorus3dView, CPie3dView)
END_MESSAGE_MAP()


// CTorus3dView diagnostics

#ifdef _DEBUG
void CTorus3dView::AssertValid() const
{
	CPie3dView::AssertValid();
}

#ifndef _WIN32_WCE
void CTorus3dView::Dump(CDumpContext& dc) const
{
	CPie3dView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTorus3dView message handlers

void CTorus3dView::OnInitialUpdate() 
{
	CPie3dView::OnInitialUpdate();

	CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);
	CXTPChart3dPieSeriesStyle* pStyle = DYNAMIC_DOWNCAST(CXTPChart3dPieSeriesStyle, pSeries->GetStyle());
	if (NULL != pStyle)
	{
		pStyle->SetTorus(TRUE);

		if (NULL != m_pOptionsDlg)
		{
			m_pOptionsDlg->ShowTorusControls();

			pStyle->SetDepth(m_pOptionsDlg->GetTorusDepthValue());
		}
	}
}
