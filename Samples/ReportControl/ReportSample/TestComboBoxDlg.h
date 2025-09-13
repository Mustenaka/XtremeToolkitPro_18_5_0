// TestComboBoxDlg.h
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

#if !defined(_TESTCOMBOBOXDLG_H_)
#define _TESTCOMBOBOXDLG_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestComboBoxDlg dialog

class CTestComboBoxDlg : public CDialog
{
public:
	CTestComboBoxDlg(CWnd *pParent = NULL);

	//{{AFX_DATA(CTestComboBoxDlg)
	enum { IDD = IDD_TEST_COMBOBOX };
	BOOL	m_bShowInplace;
	BOOL	m_bEditOnDelayClick;
	BOOL	m_bEditOnClick;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CTestComboBoxDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange *pDX);   // DDX/DDV support
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CTestComboBoxDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnShowInplace();
	afx_msg void OnEditOnClick();
	afx_msg void OnEditOnDelayClick();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void InitComboBoxes();

	CXTPOfficeBorder<CXTPReportControl,false> m_wndReport;
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(_TESTCOMBOBOXDLG_H_)
