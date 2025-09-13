// EditTagDlg.h : header file
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

#if !defined(AFX_EDITTAGDLG_H__C714C3AF_EF81_4FFF_A700_4653227C633C__INCLUDED_)
#define AFX_EDITTAGDLG_H__C714C3AF_EF81_4FFF_A700_4653227C633C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEditTagDlg dialog

class CEditTagDlg : public CDialog
{
public:

	CEditTagDlg(COLORREF clrBack, COLORREF clrBorder, LPCTSTR lpszTitle, XTP_TAGCLOUDTAG* pSelTag, CWnd* pParent = NULL);   // standard constructor

	//{{AFX_DATA(CEditTagDlg)
	enum { IDD = IDD_EDITTAG };
	CButton	m_btnOk;
	CComboBox	m_wndComboScore;
	CPreviewText	m_wndNormal;
	CPreviewText	m_wndHighlight;
	CString	m_strFont;
	int		m_nIndex;
	CString	m_strTagName;
	//}}AFX_DATA

	CXTPTagCloudStyle m_tagStyle;

	int GetScore() {
		return m_nIndex + 1;
	}

	//{{AFX_VIRTUAL(CEditTagDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:

	CString m_strTitle;
	COLORREF m_clrBack;
	COLORREF m_clrBorder;

	void UpdateControls();

	//{{AFX_MSG(CEditTagDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelEndOkComboScore();
	afx_msg void OnChangeEditTag();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITTAGDLG_H__C714C3AF_EF81_4FFF_A700_4653227C633C__INCLUDED_)
