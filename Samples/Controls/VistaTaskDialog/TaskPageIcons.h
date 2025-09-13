// TaskPageIcons.h
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

#if !defined(__TASKPAGEICONS_H__)
#define __TASKPAGEICONS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTaskPageIcons dialog

class CTaskSheetProperties;
class CTaskPageIcons : public CPropertyPage
{
	DECLARE_DYNCREATE(CTaskPageIcons)

// Construction
public:
	CTaskPageIcons();
	~CTaskPageIcons();

	//{{AFX_DATA(CTaskPageIcons)
	enum { IDD = IDD_TASKDIALOG_ICONS };
	CComboBox	m_comboMainIcon;
	CComboBox	m_comboFootIcon;
	int		m_nFootIcon;
	int		m_nMainIcon;
	CString	m_strFootPath;
	CString	m_strMainPath;
	BOOL	m_bSysIcons;
	CButton m_chkSysIcon;
	//}}AFX_DATA

	HICON	m_hFootIcon;
	HICON	m_hMainIcon;

	//{{AFX_VIRTUAL(CTaskPageIcons)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnSetActive();
	//}}AFX_VIRTUAL

protected:
	CTaskSheetProperties* m_pDlgParent;

	//{{AFX_MSG(CTaskPageIcons)
	afx_msg void OnSelEndOkMainIcon();
	afx_msg void OnEditChangeMainPath();
	afx_msg void OnSelEndOkFootIcon();
	afx_msg void OnEditChangeFootPath();
	afx_msg void OnBtnMainPath();
	afx_msg void OnBtnFootPath();
	virtual BOOL OnInitDialog();
	afx_msg void OnChkSysIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__TASKPAGEICONS_H__)
