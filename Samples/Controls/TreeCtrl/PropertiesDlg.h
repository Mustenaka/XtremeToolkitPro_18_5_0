// PropertiesDlg.h
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

#if !defined(AFX_PROPERTIESDLG_H__31B41A07_5CBC_4C5F_8C9D_474D9D55BE65__INCLUDED_)
#define AFX_PROPERTIESDLG_H__31B41A07_5CBC_4C5F_8C9D_474D9D55BE65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CPropertiesDlg dialog

class CPropertiesDlg : public CDialog
{
public:
	CPropertiesDlg(CWnd* pParent = NULL);   // standard constructor

	//{{AFX_DATA(CPropertiesDlg)
	enum { IDD = IDD_ITEM_PROPERTIES };
	CButton	m_btnApply;
	CXTPComboBox m_comboSize;
	CXTPColorPicker  m_cpText;
	CXTPColorPicker  m_cpBack;
	CXTPFontComboBox    m_comboFont;
	int     m_nIndex;
	BOOL    m_bBoldCheck;
	CString m_strFontSize;
	//}}AFX_DATA

	COLORREF		m_crText;
	COLORREF		m_crBack;
	CXTPLogFont		m_LogFont;
	CXTPTreeCtrl*	m_pTreeCtrl;

	void UpdateItem(HTREEITEM hItem);
	int DoModalEx(CXTPTreeCtrl* pTreeCtrl);

	//{{AFX_VIRTUAL(CPropertiesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CPropertiesDlg)
	afx_msg void OnBoldCheck();
	afx_msg void OnSelendokSizeCombo();
	afx_msg void OnSelendokFontCombo();
	afx_msg void OnSelEndOkColorText();
	afx_msg void OnSelEndOkColorBack();
	afx_msg void OnEditchangeSizeCombo();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnApply();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTIESDLG_H__31B41A07_5CBC_4C5F_8C9D_474D9D55BE65__INCLUDED_)
