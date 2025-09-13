// SplineAreaView.h
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

#pragma once

#include "BaseView.h"
// CSplineAreaView dialog

class CSplineAreaView : public CBaseView
{
	DECLARE_DYNCREATE(CSplineAreaView)

public:
	CSplineAreaView();
	virtual ~CSplineAreaView();
// Overrides

// Dialog Data
	enum { IDD = IDD_VIEW_SPLINEAREA};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	void CreateChart();
	
	void OnInitialUpdate();
	
	void SetAxisTitle(CXTPChartDiagram2D* pDiagram, CString strAxisX, CString strAxisY);
	
	afx_msg void OnCbnSelchangeComboMarkerType();
	afx_msg void OnCbnSelchangeComboTransparency();
	afx_msg void OnCheckShowLabels();
	afx_msg void OnCbnSelchangeComboLabelAngle();
	
	BOOL m_bShowLabels;
	int m_nLabelAngle;
	int m_nMarkerType;
	int m_nTransparency;

	DECLARE_MESSAGE_MAP()
};
