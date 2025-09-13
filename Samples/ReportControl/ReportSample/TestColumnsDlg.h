// TestColumnsDlg.h
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

#if !defined(_TESTCOLUMNSDLG_H_)
#define _TESTCOLUMNSDLG_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestColumnsDlg dialog

class CTestColumnsDlg : public CDialog
{
public:
	CTestColumnsDlg(CWnd *pParent = NULL);

	//{{AFX_DATA(CTestColumnsDlg)
	enum { IDD = IDD_TEST_COLUMNS };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CTestColumnsDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange *pDX);   // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	CImageList m_ilTree;

	//{{AFX_MSG(CTestColumnsDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnReportRClick(NMHDR *pNotifyStruct, LRESULT *pResult);
	afx_msg void OnHeaderRClick(NMHDR *pNotifyStruct, LRESULT *pResult);
	afx_msg void OnColumnOrderChanged(NMHDR *pNotifyStruct, LRESULT *pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	int AddColumn(int iColumnID, LPCTSTR pstrTitle, LPCTSTR pstrInternalUniqueID,
		int iWidth, BOOL bAutoSize = TRUE, int iIconResourceID = XTP_REPORT_NOICON,
		BOOL bSortable = TRUE, BOOL bVisible = TRUE);

	CXTPReportRecordItemText* AddItemText(CXTPReportRecord* pRecord, LPCTSTR pszText);

private:
	CXTPOfficeBorder<CXTPReportControl,false> m_wndReport;
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(_TESTCOLUMNSDLG_H_)
