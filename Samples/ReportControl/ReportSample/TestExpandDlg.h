// TestExpandDlg.h
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

#if !defined(_TESTEXPANDDLG_H_)
#define _TESTEXPANDDLG_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestExpandDlg dialog

class CTestExpandDlg : public CDialog
{
public:
	CTestExpandDlg(CWnd *pParent = NULL);

	//{{AFX_DATA(CTestExpandDlg)
	enum { IDD = IDD_TEST_EXPAND };
	BOOL	m_bNotificationExpanded;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CTestExpandDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange *pDX);   // DDX/DDV support
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CTestExpandDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnExpand();
	afx_msg void OnCollapse();
	afx_msg void OnCount();
	afx_msg void OnNotificationExpanded();
	afx_msg void OnIndexes();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	void AddRecords(int nRecordCount);

	CXTPReportControl m_wndReport;
	CString m_sTime;
	int m_nCount;
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(_TESTEXPANDDLG_H_)
