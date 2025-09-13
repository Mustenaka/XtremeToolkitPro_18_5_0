// TaskPageButtons.h
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

#if !defined(__TASKPAGEBUTTONS_H__)
#define __TASKPAGEBUTTONS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTaskPageButtons dialog

class CTaskSheetProperties;
class CTaskPageButtons : public CPropertyPage
{
	DECLARE_DYNCREATE(CTaskPageButtons)

public:
	CTaskPageButtons();
	~CTaskPageButtons();

	//{{AFX_DATA(CTaskPageButtons)
	enum { IDD = IDD_TASKDIALOG_BUTTONS };
	CButton	m_btnRemove;
	CButton	m_btnEdit;
	CButton	m_btnAdd;
	CXTPListCtrl	m_listCustom;
	CComboBox	m_comboDefault;
	BOOL	m_bOk;
	BOOL	m_bYes;
	BOOL	m_bNo;
	BOOL	m_bCancel;
	BOOL	m_bRetry;
	BOOL	m_bClose;
	BOOL	m_bUseLinks;
	BOOL	m_bShowIcons;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CTaskPageButtons)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnSetActive();
	//}}AFX_VIRTUAL

	void EnableButtons();
	void InsertItem(UINT nString, UINT nID);
	void InsertItem(CString strText, UINT nID);

protected:
	CString m_strOk;
    CString m_strYes;
    CString m_strNo;
    CString m_strCancel;
    CString m_strRetry;
    CString m_strClose;

	CTaskSheetProperties* m_pDlgParent;

	//{{AFX_MSG(CTaskPageButtons)
	afx_msg void OnUpdateData();
	afx_msg void OnChkOk();
	afx_msg void OnChkYes();
	afx_msg void OnChkCancel();
	afx_msg void OnChkNo();
	afx_msg void OnChkRetry();
	afx_msg void OnChkClose();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnEdit();
	afx_msg void OnBtnRemove();
	afx_msg void OnItemChangedListCustom(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void AddCommonButton(int nID);
	void LoadState();
	void SaveState();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__TASKPAGEBUTTONS_H__)
