// Doughnut3dView.h
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


#include "Pie3dView.h"

// CDoughnut3dView form view

class CDoughnut3dView : public CPie3dView
{
	DECLARE_DYNCREATE(CDoughnut3dView)

protected:
	CDoughnut3dView(UINT nID = IDD);           // protected constructor used by dynamic creation
	virtual ~CDoughnut3dView();

public:
	enum { IDD = IDD_VIEW_PIE_3D };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	void OnInitialUpdate();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditHoleRadius();
};


