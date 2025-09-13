// TestHeaderAlignmentDlg.h
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

#if !defined(_TESTHEADERALIGNMENTDLG_H_)
#define _TESTHEADERALIGNMENTDLG_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestHeaderAlignmentDlg dialog

class CTestHeaderAlignmentDlg : public CDialog
{
public:
	CTestHeaderAlignmentDlg(CWnd *pParent = NULL);

	//{{AFX_DATA(CTestHeaderAlignmentDlg)
	enum { IDD = IDD_TEST_HEADER_ALIGNMENT };
	CComboBox	m_cboTheme;
	BOOL m_bFixedRowHeight;
	int  m_nHeaderHeight;
	int  m_nTheme;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CTestHeaderAlignmentDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange *pDX);   // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	CImageList m_ilTree;

	//{{AFX_MSG(CTestHeaderAlignmentDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnFixedRowHeight();
	afx_msg void OnUpdateHeaderHeight();
	afx_msg void OnTheme();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CXTPOfficeBorder<CXTPReportControl,false> m_wndReport;
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(_TESTHEADERALIGNMENTDLG_H_)
