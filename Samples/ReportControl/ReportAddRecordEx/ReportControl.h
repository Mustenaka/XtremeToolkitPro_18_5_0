// ReportControl.h
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

#if !defined(AFX_REPORTCONTROL_H__7361D7E3_7483_4EAC_BDC2_15CA2BC0F49B__INCLUDED_)
#define AFX_REPORTCONTROL_H__7361D7E3_7483_4EAC_BDC2_15CA2BC0F49B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WM_ADD_RECORD_EX (WM_USER + 1)

class CReportControl : public CXTPReportControl  
{
public:
	CReportControl();
	virtual ~CReportControl();

// Attributes
public:
protected:
	CXTPReportRecord* m_pFocusedRecord;
	CXTPReportRow* m_pTopRow;

// Operations
public:
	void DeleteSelectedRows();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportControl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual BOOL OnFocusChanging(CXTPReportRow* pNewRow, CXTPReportColumn* pNewCol);

	// Generated message map functions
protected:
	//{{AFX_MSG(CReportControl)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	afx_msg LRESULT OnAddRecordEx(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_REPORTCONTROL_H__7361D7E3_7483_4EAC_BDC2_15CA2BC0F49B__INCLUDED_)
