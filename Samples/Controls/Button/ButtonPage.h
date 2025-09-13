// ButtonPage.h 
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

struct THEMEDATA
{
	LPCTSTR lpszINI;
	XTPControlTheme themeID;
};

typedef CList <THEMEDATA*, THEMEDATA*> CThemeDataList;

/////////////////////////////////////////////////////////////////////////////
// CButtonPage dialog

class CButtonPage : public CXTPResizePropertyPage
{
// Construction
public:
	CButtonPage();   // standard constructor
	virtual ~CButtonPage();

	//{{AFX_DATA(CButtonPage)
	enum { IDD = IDD_PAGE_SIMPLEBUTTONS };
	CXTPResizeGroupBox m_gboxOptions;
	CXTPResizeGroupBox m_gboxRegular;
	CXTPResizeGroupBox m_gboxTwoRows;
	CXTPResizeGroupBox m_gboxCheckboxes;
	CXTPResizeGroupBox m_gboxRadio;
	CXTPResizeGroupBox m_gboxTheme;
	CXTPResizeGroupBox m_gboxJustification;
	CXTPListBox	m_wndListBoxTheme;
	BOOL	m_bFlatStyle;
	BOOL	m_bUseVisualStyle;
	BOOL	m_bEnable;
	BOOL	m_bAlphaIcons;
	BOOL	m_bImageDPIScaling;
	BOOL	m_bToggleButtons;
	BOOL	m_bShowFocus;
	int		m_nRelation;
	int		m_nPushButtonStyle;
	int		m_nImageAlignment;
	int		m_nTextAlignment;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CButtonPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CBitmap m_bitmap;
	CImageList m_imageList;
	CThemeDataList m_themeList;

	CXTPButton m_btnRun;
	CXTPButton m_btnSettings;
	CXTPButton m_btnHelp;
	CXTPButton m_btnFind;

	CXTPButton m_btnState1;
	CXTPButton m_btnState2;

	CXTPButton m_btnOption1;
	CXTPButton m_btnOption2;

	void UpdateIcons(BOOL bAlpha);
	void AddTheme(LPCTSTR lpszThemeName, XTPControlTheme themeID, LPCTSTR lpszINI = NULL, BOOL bSelect = FALSE);

	// Generated message map functions
	//{{AFX_MSG(CButtonPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCheckFlatstyle();
	afx_msg void OnCheckWinxpThemes();
	afx_msg void OnCheckEnabled();
	afx_msg void OnCheckAlpha();
	afx_msg void OnBnClickedCheckDpiScaling();
	afx_msg void OnCheckToggle();
	afx_msg void OnCheckFocus();
	afx_msg void OnSelchangeComboRelation();
	afx_msg void OnSelchangeComboStyle();
	afx_msg void OnSelchangeComboImagealignment();
	afx_msg void OnSelchangeComboTextalignment();
	afx_msg void OnSelChangeListTheme();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	afx_msg void OnButtonClicked(UINT nID);
	afx_msg void OnButtonDropDown(UINT nID);

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTTONDLG_H__7838AF65_FBA8_45D4_B811_4979E8FE9761__INCLUDED_)
