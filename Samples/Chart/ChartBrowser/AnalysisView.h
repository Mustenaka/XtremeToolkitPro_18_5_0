// AnalysisView.h
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

#if !defined(_ANALYSISVIEW_H_)
#define _ANALYSISVIEW_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAnalysisView form view

#include "BaseView.h"

class CAnalysisView : public CBaseView
{
	enum Style
	{
		styleBar,
		styleLine,
		stylePoint,
	};

	void UpdateChart();

public:
	CAnalysisView();
	DECLARE_DYNCREATE(CAnalysisView)

public:
	//{{AFX_DATA(CAnalysisView)
	enum { IDD = IDD_VIEW_ANALYSIS };
	CComboBox	m_wndDirection;
	CComboBox	m_wndType;
	BOOL	m_bRotated;
	BOOL	m_bShowErrorBars;
	BOOL	m_bShowCaps;
	int	m_nStyle;
	int	m_nType;
	int	m_nDirection;
	int	m_nTrendline;
	//}}AFX_DATA

	void CreateChart();

public:

	//{{AFX_VIRTUAL(CAnalysisView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	virtual ~CAnalysisView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	//{{AFX_MSG(CAnalysisView)
	afx_msg void OnCheckRotated();
	afx_msg void OnCheckShowErrorBars();
	afx_msg void OnCheckShowCaps();
	afx_msg void OnSelchangeStyle();
	afx_msg void OnSelchangeType();
	afx_msg void OnSelchangeDirection();
	afx_msg void OnSelchangeTrendline();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(_ANALYSISVIEW_H_)
