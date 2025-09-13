// TestHitTestDlg.h
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

#if !defined(_TESTHITTESTDLG_H_)
#define _TESTHITTESTDLG_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestHitTestDlg dialog

class CTestHitTestDlg : public CDialog
{
public:
	CTestHitTestDlg(CWnd *pParent = NULL);

	//{{AFX_DATA(CTestHitTestDlg)
	enum { IDD = IDD_TEST_HITTEST };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CTestHitTestDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange *pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CTestHitTestDlg)
#if _XTPLIB_VERSION_PREFIX >= 1520
	afx_msg void OnReportMouseMove(NMHDR *pNotifyStruct, LRESULT *pResult);
#endif
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	int AddHitTest(LPCTSTR pszHitCode, int nColumn, int nRow);

	CXTPOfficeBorder<CXTPReportControl,false> m_wndReport;
	CListCtrl m_wndHitTest;
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(_TESTHITTESTDLG_H_)
