// TestMarkupDlg.h
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

#if !defined(_TESTMARKUPDLG_H_)
#define _TESTMARKUPDLG_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestMarkupDlg dialog

class CTestMarkupDlg : public CDialog
{
public:
	CTestMarkupDlg(CWnd *pParent = NULL);

	//{{AFX_DATA(CTestMarkupDlg)
	enum { IDD = IDD_TEST_MARKUP };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CTestMarkupDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange *pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CTestMarkupDlg)
#if _XTPLIB_VERSION_PREFIX >= 1520
	afx_msg void OnReportMouseMove(NMHDR *pNotifyStruct, LRESULT *pResult);
#endif
	afx_msg void OnSetScrollPosition();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

#if defined(_XTP_INCLUDE_MARKUP)
	void OnHyperlinkClick(CXTPMarkupObject* pSender, CXTPMarkupRoutedEventArgs* pArgs);
	void OnButtonClick(CXTPMarkupObject* pSender, CXTPMarkupRoutedEventArgs* pArgs);
#endif

	int AddEvent(LPCTSTR pszEvent);

	CXTPOfficeBorder<CXTPReportControl,false> m_wndReport;
	CListCtrl m_wndHitTest;

	CXTPReportRecordItemText *m_pItemScrollViewer;
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(_TESTMARKUPDLG_H_)
