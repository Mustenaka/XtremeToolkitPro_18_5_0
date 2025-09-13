// FlatComboDlg.h 
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

#if !defined(AFX_FLATCOMBODLG_H__03B48B0F_47BD_4632_B28B_BCE982A01581__INCLUDED_)
#define AFX_FLATCOMBODLG_H__03B48B0F_47BD_4632_B28B_BCE982A01581__INCLUDED_

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
// CFlatComboDlg dialog

#include "afxwin.h"

class CFlatComboDlg : public CXTPResizeDialog
{
// Construction
public:
	CFlatComboDlg(CWnd* pParent = NULL);    // standard constructor
	virtual ~CFlatComboDlg();

// Dialog Data
	//{{AFX_DATA(CFlatComboDlg)
	enum { IDD = IDD_COMBOBOX_DIALOG };
	CXTPButton	m_btnCancel;
	CXTPButton	m_btnOk;
	CXTPButton	m_chkAutoComplete;
	CXTPButton	m_chkDropDownDisable;
	CXTPButton	m_chkDropDownUseDefColors;
	CXTPButton	m_chkDropListDisabled;
	CXTPButton	m_chkDropListUseDefColors;
	CXTPListBox	m_wndListBoxTheme;
	CXTPEdit m_wndEditThemed;
	CXTPResizeGroupBox m_gboxEdit;
	CXTPResizeGroupBox m_gboxList;
	CXTPResizeGroupBox m_gboxDown;
	CXTPResizeGroupBox m_gboxAppear;
	CXTPColorPicker  m_txtDropListColor;
	CXTPColorPicker  m_cpDropList;
	CXTPColorPicker  m_txtDropDownColor;
	CXTPColorPicker  m_cpDropDown;
	CXTPComboBox m_wndDropDownCombo;
	CXTPComboBox m_wndDropListCombo;
	BOOL m_bAutoComplete;
	BOOL m_bDropDownDisable;
	BOOL m_bDropListDisable;
	BOOL m_bDropDownUseDefColors;
	BOOL m_bDropListUseDefColors;
	BOOL m_bFlatBorders;
	int  m_nTheme;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlatComboDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	HICON    m_hIcon;
	CThemeDataList m_themeList;

	void UpdateCombo1();
	void UpdateCombo2();
	void AddTheme(LPCTSTR lpszThemeName, XTPControlTheme themeID, LPCTSTR lpszINI = NULL, BOOL bSelect = FALSE);

	// Generated message map functions
	//{{AFX_MSG(CFlatComboDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDroplistDisable();
	afx_msg void OnDropdownDisable();
	afx_msg void OnDropdownAutocomp();
	afx_msg void OnSelEndOKDLTxtClr();
	afx_msg void OnSelEndOKDLBakClr();
	afx_msg void OnSelEndOKDDTxtClr();
	afx_msg void OnSelEndOKDDBakClr();
	afx_msg void OnDestroy();
	afx_msg void OnSelChangeListTheme();
	afx_msg void OnBnClickedChkDropDownUseDefColors();
	afx_msg void OnBnClickedChkDropListUseDefColors();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLATCOMBODLG_H__03B48B0F_47BD_4632_B28B_BCE982A01581__INCLUDED_)
