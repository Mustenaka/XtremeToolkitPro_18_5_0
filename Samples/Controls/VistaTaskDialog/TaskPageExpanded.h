// TaskPageExpanded.h
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

#if !defined(AFX_TASKPAGEEXPANDED_H__8144BA9B_1833_4CF3_BB89_6D0777B408EC__INCLUDED_)
#define AFX_TASKPAGEEXPANDED_H__8144BA9B_1833_4CF3_BB89_6D0777B408EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CTaskPageExpanded dialog

class CTaskSheetProperties;
class CTaskPageExpanded : public CPropertyPage
{
	DECLARE_DYNCREATE(CTaskPageExpanded)

public:
	CTaskPageExpanded();
	~CTaskPageExpanded();

	//{{AFX_DATA(CTaskPageExpanded)
	enum { IDD = IDD_TASKDIALOG_EXPANDED };
	BOOL	m_bByDefault;
	BOOL	m_bFooterArea;
	CString	m_strCollapsedControlText;
	CString	m_strExpandedControlText;
	CString	m_strExpandedInformation;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CTaskPageExpanded)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnSetActive();
	//}}AFX_VIRTUAL

protected:
	CTaskSheetProperties* m_pDlgParent;

	//{{AFX_MSG(CTaskPageExpanded)
	afx_msg void OnUpdateData();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TASKPAGEEXPANDED_H__8144BA9B_1833_4CF3_BB89_6D0777B408EC__INCLUDED_)
