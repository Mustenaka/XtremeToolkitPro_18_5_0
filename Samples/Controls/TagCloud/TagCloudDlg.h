// TagCloudDlg.h : header file
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

#if !defined(AFX_TAGCLOUDDLG_H__F7ADA705_D164_4F66_903E_B8CA59043F7E__INCLUDED_)
#define AFX_TAGCLOUDDLG_H__F7ADA705_D164_4F66_903E_B8CA59043F7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTagCloudDlg dialog

class CTagCloudDlg : public CXTPResizeDialog
{
// Construction
public:
	CTagCloudDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTagCloudDlg)
	enum { IDD = IDD_TAGCLOUD };
	CXTPResizeGroupBox	m_gboxControl;
	CXTPResizeGroupBox	m_gboxTag;
	CXTPResizeGroupBox	m_gboxStyles;
	CXTPButton	m_chkAsc;
	CXTPButton	m_btnTagDelete;
	CXTPButton	m_btnTagEdit;
	CXTPButton	m_btnStylesDelete;
	CXTPButton	m_btnStylesEdit;
	CXTPListCtrl	m_wndStyleList;
	CStatic	m_wndPlaceHolder;
	BOOL	m_bFocus;
	BOOL	m_bTooltip;
	BOOL    m_bAsc;
	int		m_nSort;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTagCloudDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	void RebuildTagStyleListCtrl();
	void RebuildTagCloudCtrl(BOOL bRecalcLayout = TRUE);

// Implementation
protected:
	int m_nSelItem;
	HICON m_hIcon;
	CXTPTagCloudCtrl m_wndTagCloud;
	XTP_TAGCLOUDTAG* m_pSelTag;

	void EnableButtons();
	void Sort(XTPTagCloudSort nSort);

	// Generated message map functions
	//{{AFX_MSG(CTagCloudDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChkTooltip();
	afx_msg void OnChkFocus();
	afx_msg void OnItemChangedListStyles(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTagEditTag();
	afx_msg void OnTagAddTag();
	afx_msg void OnTagDeleteTag();
	afx_msg void OnBtnStylesEdit();
	afx_msg void OnBtnStylesAdd();
	afx_msg void OnBtnStylesDelete();
	afx_msg void OnBtnTagEdit();
	afx_msg void OnBtnTagAdd();
	afx_msg void OnBtnTagDelete();
	afx_msg void OnSelendOkComboControlSort();
	afx_msg void OnBtnControlColors();
	afx_msg void OnBtnControlReset();
	afx_msg void OnControlTooltip();
	afx_msg void OnControlFocus();
	afx_msg void OnControlSortOrderNone();
	afx_msg void OnControlSortOrderByName();
	afx_msg void OnControlSortOrderByScore();
	afx_msg void OnControlEditCloudColors();
	afx_msg void OnControlResetAll();
	afx_msg void OnChkControlAsc();
	afx_msg void OnDblClkListStyles(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnInitMenuPopup(CMenu* pMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnUpdateControlTooltip(CCmdUI* pCmdUI);
	afx_msg void OnUpdateControlFocus(CCmdUI* pCmdUI);
	afx_msg void OnUpdateControlSortOrderNone(CCmdUI* pCmdUI);
	afx_msg void OnUpdateControlSortOrderByName(CCmdUI* pCmdUI);
	afx_msg void OnUpdateControlSortOrderByScore(CCmdUI* pCmdUI);
	afx_msg void OnControlSortOrderAscending();
	afx_msg void OnUpdateControlSortOrderAscending(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnTagCloudSelChange(XTP_TAGCLOUDTAG* pTag);
	afx_msg void OnTagCloudRightClk(XTP_TAGCLOUDTAG* pTag);
	afx_msg void OnTagCloudDblClk(XTP_TAGCLOUDTAG* pTag);

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TAGCLOUDDLG_H__F7ADA705_D164_4F66_903E_B8CA59043F7E__INCLUDED_)
