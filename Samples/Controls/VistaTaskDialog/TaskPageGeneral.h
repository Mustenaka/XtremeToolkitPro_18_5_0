// TaskPageGeneral.h
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

#if !defined(__TASKPAGEGENERAT_H__)
#define __TASKPAGEGENERAT_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTaskPageGeneral dialog

class CTaskSheetProperties;
class CTaskPageGeneral : public CPropertyPage
{
	DECLARE_DYNCREATE(CTaskPageGeneral)

public:
	CTaskPageGeneral();
	~CTaskPageGeneral();

	//{{AFX_DATA(CTaskPageGeneral)
	enum { IDD = IDD_TASKDIALOG_GENERAL };
	BOOL	m_bAllowCancel;
	BOOL	m_bHyperLinks;
	BOOL	m_bMarquee;
	BOOL	m_bPosition;
	BOOL	m_bProgress;
	BOOL	m_bRtl;
	BOOL	m_bVerify;
	BOOL	m_bWidth;
	CString	m_strContent;
	CString	m_strFooter;
	CString	m_strMainInstruction;
	CString	m_strWindowTitle;
	CString	m_strVerificationText;
	int		m_nCount;
	int		m_nWidth;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CTaskPageGeneral)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnSetActive();
	//}}AFX_VIRTUAL

protected:
	CTaskSheetProperties* m_pDlgParent;

	//{{AFX_MSG(CTaskPageGeneral)
	afx_msg void OnUpdateData();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedBtnAdd();
public:
	afx_msg void OnBnClickedBtnSub();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__TASKPAGEGENERAT_H__)
