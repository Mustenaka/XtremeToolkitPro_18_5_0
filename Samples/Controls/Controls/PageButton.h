// PageButton.h
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

#if !defined(AFX_BUTTONDLG_H__7838AF65_FBA8_45D4_B811_4979E8FE9761__INCLUDED_)
#define AFX_BUTTONDLG_H__7838AF65_FBA8_45D4_B811_4979E8FE9761__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPageButton dialog

class CPageButton : public CXTPResizePropertyPage
{
// Construction
public:
	CPageButton();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPageButton)
	enum { IDD = IDD_PAGE_BUTTONS };
	BOOL	m_bFlatStyle;
	BOOL	m_bUseVisualStyle;
	BOOL	m_bEnable;
	BOOL	m_bAlphaIcons;
	BOOL	m_bToggleButtons;
	BOOL	m_bShowFocus;
	int		m_nRelation;
	int		m_nPushButtonStyle;
	int		m_nImageAlignment;
	int		m_nTextAlignment;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageButton)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CBitmap m_bitmap;
	CXTPImageList m_imageList;

	CXTPButton m_btnRun;
	CXTPButton m_btnSettings;
	CXTPButton m_btnHelp;
	CXTPButton m_btnFind;

	CXTPButton m_btnState1;
	CXTPButton m_btnState2;

	CXTPButton m_btnOption1;
	CXTPButton m_btnOption2;

	CXTPButton m_frmRegular;
	CXTPButton m_frmTwoRows;
	CXTPButton m_frmCheckboxes;
	CXTPButton m_frmRadio;
	CXTPButton m_frmJustification;
	CXTPButton m_frmTheme;
	CXTPButton m_frmOptions;

	CXTPComboBox	m_cmbTEXTALIGNMENT;
	CXTPComboBox	m_cmbIMAGEALIGNMENT;
	CXTPComboBox	m_cmbRELATION;
	CXTPComboBox	m_cmbSTYLE;

	CXTPButton m_btnCLASSIC;
	CXTPButton m_btnFLAT;
	CXTPButton m_btnOFFICE2000;
	CXTPButton m_btnOFFICEXP;
	CXTPButton m_btnOFFICE2003;
	CXTPButton m_btnNATIVEWINXP;
	CXTPButton m_btnOFFICE2013_BUTTON;
	CXTPButton m_btnVS2012DARK;
	CXTPButton m_btnVS2012LIGHT;
	CXTPButton m_btnOFFICE2007;
	CXTPButton m_btnULTRAFLAT;

	CXTPButton m_btnFLATSTYLE;
	CXTPButton m_btnWINXP_THEMES;
	CXTPButton m_btnTOGGLE;
	CXTPButton m_btnENABLED;
	CXTPButton m_btnALPHA;
	CXTPButton m_btnFOCUS;

	void UpdateIcons(BOOL bAlpha);

	// Generated message map functions
	//{{AFX_MSG(CPageButton)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnCheckFlatstyle();
	afx_msg void OnCheckWinxpThemes();
	afx_msg void OnCheckEnabled();
	afx_msg void OnCheckAlpha();
	afx_msg void OnCheckToggle();
	afx_msg void OnCheckFocus();
	afx_msg void OnSelchangeComboRelation();
	afx_msg void OnSelchangeComboStyle();
	afx_msg void OnSelchangeComboImagealignment();
	afx_msg void OnSelchangeComboTextalignment();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	afx_msg void OnButtonClicked(UINT nID);
	afx_msg void OnButtonDropDown(UINT nID);

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTTONDLG_H__7838AF65_FBA8_45D4_B811_4979E8FE9761__INCLUDED_)
