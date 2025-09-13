// EditTagCloudDlg.h : header file
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

#if !defined(AFX_EDITTAGCLOUDDLG_H__70DFB980_D9A4_4407_A308_6E6E5E57AEBD__INCLUDED_)
#define AFX_EDITTAGCLOUDDLG_H__70DFB980_D9A4_4407_A308_6E6E5E57AEBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEditTagCloudDlg dialog

class CEditTagCloudDlg : public CDialog
{
public:
	CEditTagCloudDlg(CXTPTagCloudCtrl& wndTagCloud, CWnd* pParent = NULL);   // standard constructor

	//{{AFX_DATA(CEditTagCloudDlg)
	enum { IDD = IDD_EDITTAGCLOUD };
	CComboBox	m_wndComboPadding;
	CComboBox	m_wndComboMargin;
	CComboBox	m_wndComboStyle;
	CStatic	m_txtDark;
	CXTPColorPicker	m_cpDark;
	CXTPColorPicker	m_cpLight;
	CXTPColorPicker	m_cpBorder;
	int		m_nStyle;
	int		m_nMargin;
	int		m_nPadding;
	//}}AFX_DATA
	COLORREF m_clrDark;
	COLORREF m_clrLight;
	COLORREF m_clrBorder;

	//{{AFX_VIRTUAL(CEditTagCloudDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CEditTagCloudDlg)
	afx_msg void OnSelEndOkComboStyle();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg void OnSelEndOk();
	afx_msg void OnSelEndOkBackLight();
	afx_msg void OnSelEndOkBackDark();
	afx_msg void OnSelEndOkBorder();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITTAGCLOUDDLG_H__70DFB980_D9A4_4407_A308_6E6E5E57AEBD__INCLUDED_)
