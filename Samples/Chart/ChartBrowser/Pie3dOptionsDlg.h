// Pie3dOptionsDlg.h
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

#if !defined(AFX_PIE3DOPTIONSDLG_H__96EEFD1B_4CAD_4B38_8C2D_CEB452078B37__INCLUDED_)
#define AFX_PIE3DOPTIONSDLG_H__96EEFD1B_4CAD_4B38_8C2D_CEB452078B37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPie3dOptionsDlg dialog

struct IPie3dOptionsDlgCallback
{
	virtual void OnBnClickedCheckShowLabels() { }
	virtual void OnCbnSelChangeComboLabelPosition() { }
	virtual void OnCbnSelChangeComboExplodedPoints() { }
	virtual void OnEnChangeEditDepth() { }
	virtual void OnEnChangeEditHoleRadius() { }
};

class CPie3dOptionsDlg : public CTabCtrlDialog
{
// Construction
public:
	CPie3dOptionsDlg(IPie3dOptionsDlgCallback& callback, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPie3dOptionsDlg)
	enum { IDD = IDD_VIEW_PIE_3D_OPTIONS_TAB };
	//}}AFX_DATA

	BOOL GetShowLabelsValue() const;
	int GetPositionValue() const;
	int GetExplodedPointsValue() const;
	int GetTorusDepthValue() const;
	int GetDoughnutHoleRadiusValue() const;

	void ShowTorusControls();
	void ShowDoughnutControls();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPie3dOptionsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	IPie3dOptionsDlgCallback& m_callback;

	DECLARE_MESSAGE_MAP()
	// Generated message map functions
	//{{AFX_MSG(CPie3dOptionsDlg)
	afx_msg void OnBnClickedCheckShowLabels();
	afx_msg void OnCbnSelChangeComboLabelPosition();
	afx_msg void OnCbnSelChangeComboExplodedPoints();
	afx_msg void OnEnChangeEditDepth();
	afx_msg void OnEnChangeEditHoleRadius();
	//}}AFX_MSG

private:
	BOOL m_bShowLabels;
	int m_nPosition;
	int m_nExplodedPoints;
	int m_nDepth;
	int m_nHoleRadius;
};

AFX_INLINE BOOL CPie3dOptionsDlg::GetShowLabelsValue() const {
	return m_bShowLabels;
}

AFX_INLINE int CPie3dOptionsDlg::GetPositionValue() const {
	return m_nPosition;
}

AFX_INLINE int CPie3dOptionsDlg::GetExplodedPointsValue() const {
	return m_nExplodedPoints;
}

AFX_INLINE int CPie3dOptionsDlg::GetTorusDepthValue() const {
	return m_nDepth;
}

AFX_INLINE int CPie3dOptionsDlg::GetDoughnutHoleRadiusValue() const {
	return m_nHoleRadius;
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PIE3DOPTIONSDLG_H__96EEFD1B_4CAD_4B38_8C2D_CEB452078B37__INCLUDED_)
