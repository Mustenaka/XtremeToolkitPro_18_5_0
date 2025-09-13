// BubbleView.h
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
// CBubbleView form view

class CBubbleView : public CBaseView
{
	DECLARE_DYNCREATE(CBubbleView)

protected:
	CBubbleView();           // protected constructor used by dynamic creation
	virtual ~CBubbleView();

public:
	enum { IDD = IDD_VIEW_BUBBLE };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif


	void CreateChart();

	void OnInitialUpdate();

	void UpdateBubbleSize();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditMin();
	double m_dMinSize;
	double m_dMaxSize;
	int m_nMarkerType;
	afx_msg void OnEnChangeEditMax();
	afx_msg void OnCbnSelchangeComboTransparency();
	afx_msg void OnCbnSelchangeComboMarkerType();
	int m_nTransparency;
};


