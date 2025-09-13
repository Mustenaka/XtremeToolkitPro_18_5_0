// SideBySideStackedBarView.h
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

// CSideBySideStackedBarView form view

class CSideBySideStackedBarView : public CBaseView
{
	DECLARE_DYNCREATE(CSideBySideStackedBarView)

protected:
	CSideBySideStackedBarView();           // protected constructor used by dynamic creation
	virtual ~CSideBySideStackedBarView();

public:
	enum { IDD = IDD_VIEW_SIDEBYDIDESTACKEDBAR };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	virtual void OnInitialUpdate();

	BOOL	m_bShowLabels;
	BOOL	m_bRotated;
	int m_nGroup;
	BOOL m_b100;

	void CreateChart();
	afx_msg void OnClickedGroup();
	afx_msg void OnCheck100();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg void OnCheckShowLabels();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheckRotated();
};

class CFullSideBySideStackedBarView : public CSideBySideStackedBarView
{
	DECLARE_DYNCREATE(CFullSideBySideStackedBarView)

protected:
	CFullSideBySideStackedBarView();           // protected constructor used by dynamic creation
	virtual void OnInitialUpdate();

};
