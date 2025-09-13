// ScrollBarDlg.h 
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

#if !defined(AFX_SCROLLBARDLG_H__693E9CEE_BC86_4FBA_A6CC_A5B3BE7BBFF8__INCLUDED_)
#define AFX_SCROLLBARDLG_H__693E9CEE_BC86_4FBA_A6CC_A5B3BE7BBFF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CScrollBarDlg dialog

class CScrollBarDlg : public CXTPDialogScrollBarContainer<CDialog>
{
// Construction
public:
	CScrollBarDlg(CWnd* pParent = NULL); // standard constructor

// Dialog Data
	//{{AFX_DATA(CScrollBarDlg)
	enum { IDD = IDD_SCROLLBAR_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScrollBarDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:
	void SetScrollBarTheme(XTPScrollBarTheme theme);
	void FillThemeScrollbar();
	void CreateViewDlg();

	CComboBox m_cboxTheme;
	CViewFrame m_dlgView;

	CButton m_btnHUseHScroll;
	CButton m_btnHVisible;
	CButton m_btnHEnabled;

	CButton m_btnVUseVScroll;
	CButton m_btnVVisible;
	CButton m_btnVEnabled;

	struct
	{
		CButton* m_pBtnUseScrollBar;
		CButton* m_pBtnVisible;
		CButton* m_pBtnEnabled;
	} m_btnSet[2];

protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CScrollBarDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCbnSelchangeComboThemes();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHScrollChanged();
	afx_msg void OnVScrollChanged();

	void SyncScrollbarState(int nBar);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCROLLBARDLG_H__693E9CEE_BC86_4FBA_A6CC_A5B3BE7BBFF8__INCLUDED_)
