// PageJumpList.h
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

#if !defined(AFX_PAGEJUMPLIST_H__5DB262A8_4DF9_4EDF_ABE6_5E7532BEAA83__INCLUDED_)
#define AFX_PAGEJUMPLIST_H__5DB262A8_4DF9_4EDF_ABE6_5E7532BEAA83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTaskRec
{

public:
	CString m_strTitle;
	CString m_strPath;       // String that represents the executable associated with this command.
};

typedef CList<CTaskRec, CTaskRec&> CTaskList;


/////////////////////////////////////////////////////////////////////////////
// CPageJumpList dialog

class CPageJumpList : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageJumpList)

// Construction
public:
	CPageJumpList();
	~CPageJumpList();


// Dialog Data
	//{{AFX_DATA(CPageJumpList)
	enum { IDD = IDD_PAGE_JUMP_LIST };
	CXTPEditListBox	m_lboxTaskList;
	CString	m_strPath;
	CString	m_strTitle;
	//}}AFX_DATA

	void AddTask(LPCTSTR lpszTitle, LPCTSTR lpszPath);

	void OnLabelEditEnd();
	void OnNewItem();
	void OnLabelEditCancel();
	void OnPreDeleteItem();

	CXTPTaskbarManager m_mgrTaskbar;




// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageJumpList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageJumpList)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeEditList();
	afx_msg void UpdateTaskData();
	afx_msg void OnDestroy();
	afx_msg void OnButtonCommit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEJUMPLIST_H__5DB262A8_4DF9_4EDF_ABE6_5E7532BEAA83__INCLUDED_)
