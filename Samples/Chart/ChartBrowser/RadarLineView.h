// RadarLineView.h
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


// CRadarLineView form view

class CRadarLineView : public CBaseView
{
	DECLARE_DYNCREATE(CRadarLineView)

protected:
	CRadarLineView();           // protected constructor used by dynamic creation
	virtual ~CRadarLineView();

public:
	enum { IDD = IDD_VIEW_RADARLINE };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	BOOL m_bShowLabels;
	int m_nMarkerType;
	int m_nMarkerSize;

	BOOL m_bShowAxisX;
	BOOL m_bShowAxisY;

	BOOL m_bInterlaced;

	void CreateChart();

	void OnInitialUpdate();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	afx_msg void OnCheckShowLabels();
	afx_msg void OnCbnSelchangeComboMarkerSize();
	afx_msg void OnCbnSelchangeComboMarkerType();
	afx_msg void OnCheckShowAxisX();
	afx_msg void OnCheckShowAxisY();
	afx_msg void OnCheckInterlaced();
public:
};


