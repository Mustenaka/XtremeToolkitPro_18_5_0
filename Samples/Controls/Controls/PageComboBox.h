// PageComboBox.h
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

#if !defined(AFX_PAGECOMBOBOX_H__17A13E29_3B64_4956_9D9D_11AEABC6518E__INCLUDED_)
#define AFX_PAGECOMBOBOX_H__17A13E29_3B64_4956_9D9D_11AEABC6518E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CPageComboBox dialog

class CPageComboBox : public CXTPResizePropertyPage
{
	DECLARE_DYNCREATE(CPageComboBox)

// Construction
public:
	CPageComboBox();
	~CPageComboBox();

// Dialog Data
	//{{AFX_DATA(CPageComboBox)
	enum { IDD = IDD_PAGE_COMBOBOX };
	CXTPButton	m_chkAutoComplete;
	CXTPButton	m_chkEnabled;
	CXTPButton	m_chkVisualStyle;
	CXTPButton	m_chkFlatStyle;
	CXTPButton	m_gboxOptions;
	CXTPButton	m_gboxTheme;
	CXTPComboBox	m_cmbDropDown;
	CXTPComboBox	m_cmbDropDownList;
	BOOL	m_bEnabled;
	BOOL	m_bFlatStyle;
	int		m_nTheme;
	BOOL	m_bUseVisualStyle;
	BOOL	m_bAutoComplete;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageComboBox)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageComboBox)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckFlatstyle();
	afx_msg void OnCheckWinxpThemes();
	afx_msg void OnCheckEnabled();
	afx_msg void OnCheckAutocomplete();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGECOMBOBOX_H__17A13E29_3B64_4956_9D9D_11AEABC6518E__INCLUDED_)
