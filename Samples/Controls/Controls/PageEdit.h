// PageEdit.h
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

#if !defined(AFX_PAGEEDIT_H__BF497E7A_7D9A_4F20_A1EA_0DCF588EC931__INCLUDED_)
#define AFX_PAGEEDIT_H__BF497E7A_7D9A_4F20_A1EA_0DCF588EC931__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CPageEdit dialog

class CPageEdit : public CXTPResizePropertyPage
{
public:
	CPageEdit(CWnd* pParent = NULL);   // standard constructor

	//{{AFX_DATA(CPageEdit)
	enum { IDD = IDD_PAGE_EDIT };
	CXTPButton	m_gboxOptions;
	CXTPButton	m_btnPassword;
	CXTPButton	m_btnReadOnly;
	CXTPButton	m_btnEnabled;
	CXTPButton	m_btnVisualStyle;
	CXTPButton	m_btnFlatStyle;
	CXTPButton	m_gboxTheme;
	CXTPButton	m_btnBuddy;
	CXTPSpinButtonCtrl	m_btnSpinButton;
	CXTPEdit	m_edtSpin;
	CXTPEdit	m_edtButton;
	CXTPEdit	m_edtPattern;
	CXTPEdit	m_edtMultiline;
	CXTPEdit	m_edtMasked;
	CXTPEdit	m_edtSingleLine;
	BOOL	m_bEnabled;
	BOOL	m_bPassword;
	BOOL	m_bReadOnly;
	BOOL	m_bUseVisualStyle;
	BOOL	m_bFlatStyle;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CPageEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CPageEdit)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckEnabled();
	afx_msg void OnCheckReadonly();
	afx_msg void OnCheckPassword();
	afx_msg void OnCheckFlatstyle();
	afx_msg void OnCheckWinxpThemes();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEEDIT_H__BF497E7A_7D9A_4F20_A1EA_0DCF588EC931__INCLUDED_)
