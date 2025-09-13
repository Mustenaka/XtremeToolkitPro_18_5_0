// PaneStyles.h
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

#if !defined(AFX_PANESTYLES_H__12778969_E726_421D_A3ED_D6C977E48A7A__INCLUDED_)
#define AFX_PANESTYLES_H__12778969_E726_421D_A3ED_D6C977E48A7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef _XTP_INCLUDE_DOCKINGPANE

class CPaneStyles : public CXTPResizeDialog
{
// Construction
public:
	CPaneStyles(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPaneStyles)
	enum { IDD = IDD_PANE_STYLES };
	CXTPListBox	m_lstStyles;
	CXTPButton	m_chkLinkedStyle;
	CXTPButton	m_chkPreview;
	CXTPButton	m_btnStyleInspector;
	CXTPButton	m_btnNewStyle;
	CXTPButton	m_btnManageStyles;
	//}}AFX_DATA

	CBrush m_brush;
	CXTPDockingPane* m_pPane;

	void RefreshMetrics(XTPDockingPanePaintTheme nPaneTheme);
	void SetOwnerPane(CXTPDockingPane* pPane);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaneStyles)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnOK();
	void OnCancel();

	// Generated message map functions
	//{{AFX_MSG(CPaneStyles)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANESTYLES_H__12778969_E726_421D_A3ED_D6C977E48A7A__INCLUDED_)
