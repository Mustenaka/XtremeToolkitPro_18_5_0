// EditStyleDlg.h : header file
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

#if !defined(AFX_TAGSTYLEDLG_H__EDCBDE17_FE58_46BB_95D6_A524D3B9597E__INCLUDED_)
#define AFX_TAGSTYLEDLG_H__EDCBDE17_FE58_46BB_95D6_A524D3B9597E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPreviewText

class CPreviewText : public CStatic
{
public:
	CPreviewText();

	void SetStyle(COLORREF clrBack, COLORREF clrText, COLORREF clrBorder);

	//{{AFX_VIRTUAL(CPreviewText)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CPreviewText)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnNcPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	COLORREF m_clrBack;
	COLORREF m_clrText;
	COLORREF m_clrBorder;
	CBrush   m_brBack;
};

/////////////////////////////////////////////////////////////////////////////
// CEditStyleDlg dialog

class CEditStyleDlg : public CDialog
{
public:
	CEditStyleDlg(COLORREF clrBack, COLORREF clrBorder, LPCTSTR lpszTitle, CXTPTagCloudStyle* pTagStyle, CWnd* pParent = NULL);
	CEditStyleDlg(COLORREF clrBack, COLORREF clrBorder, LPCTSTR lpszTitle, int nScore, CWnd* pParent = NULL);

	//{{AFX_DATA(CEditStyleDlg)
	enum { IDD = IDD_EDITSTYLE };
	CXTPColorPicker	m_cpNormal;
	CXTPColorPicker	m_cpHilight;
	CXTPColorPicker	m_cpBorder;
	CPreviewText	m_wndNormal;
	CPreviewText	m_wndHighlight;
	CString	m_strFont;
	//}}AFX_DATA

	CXTPTagCloudStyle m_tagStyle;

	//{{AFX_VIRTUAL(CEditStyleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:

	CString m_strTitle;
	COLORREF m_clrBack;
	COLORREF m_clrBorder;

	// Generated message map functions
	//{{AFX_MSG(CEditStyleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnFont();
	//}}AFX_MSG
	afx_msg void OnColorSelEndOkNormal();
	afx_msg void OnColorSelEndOkHilight();
	afx_msg void OnColorSelEndOkBorder();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TAGSTYLEDLG_H__EDCBDE17_FE58_46BB_95D6_A524D3B9597E__INCLUDED_)
