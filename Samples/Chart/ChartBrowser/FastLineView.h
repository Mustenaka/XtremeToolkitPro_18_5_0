// FastLineView.h
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

// CFastLineView form view

class CFastLineView : public CBaseView
{
	DECLARE_DYNCREATE(CFastLineView)

protected:
	CFastLineView();           // protected constructor used by dynamic creation
	virtual ~CFastLineView();

public:
	enum { IDD = IDD_VIEW_FASTLINE };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
   //{{AFX_DATA(CFastLineView)
   //}}AFX_DATA

	//{{AFX_MSG(CFastLineView)
   afx_msg void OnTimer(UINT_PTR nIDEvent);
   afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	UINT m_nTimer;
	
	DWORD m_dwTickCount;
	
	int m_nSeriesCount;
	int m_nInterval;

	BOOL m_bInterlaced;
	BOOL m_bAntialiased;
	
	void AddPoint();

	void OnCbnSelchangeComboSeriesCount();
	void OnCbnSelchangeComboInterval();
	void OnButtonAdd();
	void OnInterlacedClick();
	void OnAntialiasedClick();
	
	void SetInterval();
	
	void CreateChart();
	
	void OnInitialUpdate();
	
	void SetAxisTitle(CXTPChartDiagram2D* pDiagram, CString strAxisX, CString strAxisY);
};


