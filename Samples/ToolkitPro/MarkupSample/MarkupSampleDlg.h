// MarkupSampleDlg.h
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

#if !defined(AFX_MARKUPSAMPLEDLG_H__E6161FD9_6D1A_4018_B00E_6AA977CAB4BF__INCLUDED_)
#define AFX_MARKUPSAMPLEDLG_H__E6161FD9_6D1A_4018_B00E_6AA977CAB4BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMarkupSampleDlg dialog

class CMarkupSampleDlg : public CXTPResizeDialog
{
// Construction
public:
	CMarkupSampleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMarkupSampleDlg)
	enum { IDD = IDD_MARKUPSAMPLE_DIALOG };
	CXTPButton	m_btnMore;
	CXTPButton	m_wndCheckBox;
	CXTPButton	m_wndButton;
	CXTPButton	m_wndRadio;
	CXTPMarkupStatic	m_wndStatic;
	CXTPMarkupListBox	 m_wndList;
	CXTPMarkupTreeCtrl m_wndTree;
	CXTPTabControl m_wndTabControl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMarkupSampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	void AddListItem(LPCTSTR lpszMarkup);	


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMarkupSampleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMorePopupcontrol();
	afx_msg void OnMoreUnicodesupport();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMoreTaskdialog();
	//}}AFX_MSG
	
	void OnHyperlinkClick(CXTPMarkupObject* pSender, CXTPMarkupRoutedEventArgs* pArgs);

	void OnMoreDropDown();
	void OnTabControlSelChanged(NMHDR* pHeader, LRESULT* pResult);
	void OnMoreTipoftheDay();

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MARKUPSAMPLEDLG_H__E6161FD9_6D1A_4018_B00E_6AA977CAB4BF__INCLUDED_)
