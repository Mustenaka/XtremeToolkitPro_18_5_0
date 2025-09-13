// TestAlternateBackgroundDlg.h
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

#if !defined(_TESTALTERNATEBACKGROUNDDLG_H_)
#define _TESTALTERNATEBACKGROUNDDLG_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestAlternateBackgroundDlg dialog

class CTestAlternateBackgroundDlg : public CDialog
{
public:
	CTestAlternateBackgroundDlg(CWnd *pParent = NULL);

	//{{AFX_DATA(CTestAlternateBackgroundDlg)
	enum { IDD = IDD_TEST_ALTERNATE_BACKGROUND };
	BOOL	m_bAlternateBackground;
	BOOL	m_bShowHeader;
	BOOL	m_bShowWatermark;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CTestAlternateBackgroundDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange *pDX);   // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	CImageList m_ilTree;

	//{{AFX_MSG(CTestAlternateBackgroundDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAlternateBackground();
	afx_msg void OnShowHeader();
	afx_msg void OnShowWatermark();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CXTPOfficeBorder<CXTPReportControl,false> m_wndReport;
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(_TESTALTERNATEBACKGROUNDDLG_H_)
