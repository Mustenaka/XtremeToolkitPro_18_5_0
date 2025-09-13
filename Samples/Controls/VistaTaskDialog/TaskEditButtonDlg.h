// TaskEditButtonDlg.h
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

#if !defined(AFX_TASKEDITBUTTONDLG_H__AEF40CD1_D8B9_4867_8BAA_0E592EE8F3C4__INCLUDED_)
#define AFX_TASKEDITBUTTONDLG_H__AEF40CD1_D8B9_4867_8BAA_0E592EE8F3C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CTaskEditButtonDlg dialog

class CTaskSheetProperties;
class CTaskEditButtonDlg : public CDialog
{
public:
	CTaskEditButtonDlg(CComboBox* pWndCombo = NULL, BOOL bIsEdit = TRUE, CWnd* pParent = NULL);   // standard constructor

	//{{AFX_DATA(CTaskEditButtonDlg)
	enum { IDD = IDD_TASKDIALOG_BUTTONEDIT };
	CEdit m_wndEditCtrl;
	CEdit m_wndEditText;
	CSpinButtonCtrl	m_wndSpinCtrl;
	CString	m_strText;
	int		m_nID;
	//}}AFX_DATA

	BOOL m_bIsEdit;
	CComboBox* m_pWndCombo;

	//{{AFX_VIRTUAL(CTaskEditButtonDlg)
	protected:
	virtual void OnOK();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	CArray<TASKDIALOG_BUTTON,TASKDIALOG_BUTTON&> m_arButtons;
	CTaskSheetProperties*                        m_pDlgParent;

	void GetNextAvailableID(BOOL bUpdateData = FALSE);
	void AddButton(PCWSTR pszText, int nButtonID);

	//{{AFX_MSG(CTaskEditButtonDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TASKEDITBUTTONDLG_H__AEF40CD1_D8B9_4867_8BAA_0E592EE8F3C4__INCLUDED_)
