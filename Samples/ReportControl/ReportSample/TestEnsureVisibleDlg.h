// TestEnsureVisibleDlg.h
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

#if !defined(_TESTENSUREVISIBLEDLG_H_)
#define _TESTENSUREVISIBLEDLG_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestEnsureVisibleDlg dialog
/////////////////////////////////////////////////////////////////////////////

class CTestEnsureVisibleDlg : public CDialog
{
public:
	CTestEnsureVisibleDlg(CWnd* pParent = NULL);

	//{{AFX_DATA(CTestEnsureVisibleDlg)
	enum { IDD = IDD_TEST_ENSURE_VISIBLE };
	CComboBox	m_wndBehavior;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CTestEnsureVisibleDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange *pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CTestEnsureVisibleDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	CXTPOfficeBorder<CXTPReportControl,false> m_wndReport;
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(_TESTENSUREVISIBLEDLG_H_)
