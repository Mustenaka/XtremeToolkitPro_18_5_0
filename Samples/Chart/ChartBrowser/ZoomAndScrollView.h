// ZoomAndScrollView.h
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

// CZoomAndScrollView form view

class CZoomAndScrollView : public CBaseView
{
	DECLARE_DYNCREATE(CZoomAndScrollView)

protected:
	CZoomAndScrollView();           // protected constructor used by dynamic creation
	virtual ~CZoomAndScrollView();

public:
	enum { IDD = IDD_VIEW_ZOOMANDSCROLL};
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	BOOL m_bShowLabels;
	BOOL m_bShowMarkers;
	BOOL m_bAllowZoom;
	BOOL m_bAllowScroll;

	void OnCheckShowLabels();
	void OnCheckShowMarkers();
	void OnCheckAllowScroll();
	void OnCheckAllowZoom();



	void CreateChart();

	void OnInitialUpdate();


	DECLARE_MESSAGE_MAP()
};


