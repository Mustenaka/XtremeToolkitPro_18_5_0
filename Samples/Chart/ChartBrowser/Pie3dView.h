// Pie3dView.h
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

// CPie3dView form view

class CPie3dOptionsDlg;

class CPie3dView 
	: public CBase3dView
	, private IPie3dOptionsDlgCallback
{
	DECLARE_DYNCREATE(CPie3dView)

protected:
	CPie3dView(UINT nID = IDD);           // protected constructor used by dynamic creation
	virtual ~CPie3dView();

public:
	enum { IDD = IDD_VIEW_PIE_3D };
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

	// IPie3dOptionsDlgCallback overrides
	virtual void OnBnClickedCheckShowLabels();
	virtual void OnCbnSelChangeComboLabelPosition();
	virtual void OnCbnSelChangeComboExplodedPoints();
	virtual void OnEnChangeEditDepth();

private:
	DECLARE_MESSAGE_MAP()
	CPie3dOptionsDlg* m_pOptionsDlg;
};
