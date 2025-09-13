// FontComboDlg.h
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

#if !defined(AFX_FONTCOMBODLG_H__5CE7C7B1_76A4_4FA3_B954_A3D40C539494__INCLUDED_)
#define AFX_FONTCOMBODLG_H__5CE7C7B1_76A4_4FA3_B954_A3D40C539494__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SampleText.h"

/////////////////////////////////////////////////////////////////////////////
// CFontComboDlg dialog

class CFontComboDlg : public CDialog
{
// Construction
public:
	CFontComboDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CFontComboDlg();

	void UpdateFont();
	void SetTheme(XTPControlTheme theme);

	//{{AFX_DATA(CFontComboDlg)
	enum { IDD = IDD_FONTCOMBO_DIALOG };
	CSampleText	m_txtSample;
	CXTPComboBox	m_wndComboTheme;
	CXTPComboBox	m_wndComboSize;
	CXTPFontComboBox	m_wndComboFont;
	CXTPColorPicker	m_wndColorPicker;
	BOOL	m_bBold;
	BOOL	m_bItalic;
	BOOL	m_bUnderline;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFontComboDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	COLORREF m_crCurrent;
	CXTPLogFont m_lf;
	CString  m_strFontSize;
	CString  m_strFontName;

	CXTPButton m_btnBold;
	CXTPButton m_btnItalic;
	CXTPButton m_btnUnderline;

	CXTPButton m_btnCancel;

	// Generated message map functions
	//{{AFX_MSG(CFontComboDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnThemeChanged();
	afx_msg void OnSelendokComboSize();
	afx_msg void OnChkBold();
	afx_msg void OnChkItalic();
	afx_msg void OnChkUnderline();
	//}}AFX_MSG
	afx_msg void OnSelEndOKColor();
	afx_msg void OnSelEndOKFontCombo();
	
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FONTCOMBODLG_H__5CE7C7B1_76A4_4FA3_B954_A3D40C539494__INCLUDED_)
