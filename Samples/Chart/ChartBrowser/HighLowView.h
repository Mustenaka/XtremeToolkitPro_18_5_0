// HighLowView.h
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
// CHighLowView form view

class CHighLowView : public CBaseView
{
	DECLARE_DYNCREATE(CHighLowView)

protected:
	CHighLowView(UINT nIDD = IDD);           // protected constructor used by dynamic creation
	virtual ~CHighLowView();

public:
	enum { IDD = IDD_VIEW_HIGHLOW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	void CreateChart();

	void OnInitialUpdate();

	BOOL m_bThickStyle;
	void OnCheckThickStyle();


	DECLARE_MESSAGE_MAP()
};


