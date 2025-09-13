// TestDragDropDlg.h
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

#if !defined(_TESTDRAGDROPDLG_H_)
#define _TESTDRAGDROPDLG_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestDragDropDlg dialog

class CTestDragDropDlg : public CDialog
{
public:
	CTestDragDropDlg(CWnd *pParent = NULL);

	//{{AFX_DATA(CTestDragDropDlg)
	enum { IDD = IDD_TEST_DRAG_DROP };
	BOOL	m_bSortedDragDrop1;
	BOOL	m_bSortedDragDrop2;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CTestDragDropDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange *pDX);   // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	CImageList m_ilTree;

	//{{AFX_MSG(CTestDragDropDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSortedDragDrop1();
	afx_msg void OnSortedDragDrop2();
	afx_msg void OnReportBeginDrag1(NMHDR *pNotifyStruct, LRESULT *pResult);
	afx_msg void OnReportDrop2(NMHDR *pNotifyStruct, LRESULT *pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CXTPOfficeBorder<CXTPReportControl,false> m_wndReport1;
	CXTPOfficeBorder<CXTPReportControl,false> m_wndReport2;
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(_TESTDRAGDROPDLG_H_)
