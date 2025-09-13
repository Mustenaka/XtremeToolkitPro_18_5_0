// ColorPickerDlg.h
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

#if !defined(__COLORPICKERDLG_H__)
#define __COLORPICKERDLG_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPreviewText dialog

class CPreviewText : public CStatic
{
public:
	//{{AFX_VIRTUAL(CPreviewText)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CPreviewText)
	afx_msg void OnNcPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CColorPickerDlg dialog

class CColorPickerDlg : public CDialog
{
// Construction
public:
	CColorPickerDlg(CWnd* pParent = NULL);  // standard constructor

// Dialog Data
	//{{AFX_DATA(CColorPickerDlg)
	enum { IDD = IDD_COLORPICKER_DIALOG };
	CButton	m_chkRecent;
	CButton	m_chkColorText;
	CXTPResizeGroupBox m_gboxButton;
	CXTPResizeGroupBox m_gboxPopup;
	CXTPResizeGroupBox m_gboxDialog;
	CXTPColorPicker  m_cpTextColor;
	CXTPColorPicker  m_cpBackColor;
	CPreviewText m_wndSample;
	BOOL    m_bNoFill;
	BOOL    m_3DBorder;
	BOOL    m_bDisable;
	BOOL    m_bDisplayHex;
	BOOL    m_bColorText;
	BOOL    m_bShowText;
	BOOL	m_bEyeDropper;
	BOOL	m_bRecent;
	int		m_nStyle;
	BOOL	m_bMoreColors;
	int		m_nTheme;
	BOOL	m_bCaptions;
	//}}AFX_DATA

	COLORREF m_clrText;
	COLORREF m_clrBack;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorPickerDlg)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON  m_hIcon;
	CBrush m_brBack;

	// Generated message map functions
	//{{AFX_MSG(CColorPickerDlg)
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSelEndOkTextClr();
	afx_msg void OnSelEndOkBackClr();
	afx_msg void OnChkNoFill();
	afx_msg void OnChkMoreColors();
	afx_msg void OnChk3dBorder();
	afx_msg void OnChkDisplayHex();
	afx_msg void OnChkDisable();
	afx_msg void OnChkNoText();
	afx_msg void OnChkColorText();
	afx_msg void OnSelEndOkComboStyle();
	afx_msg void OnSelEndOkComboTheme();
	afx_msg void OnChkRecent();
	afx_msg void OnChkEyeDropper();
	afx_msg void OnChkCaptions();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__COLORPICKERDLG_H__)
