// TabListPage.h
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

#if !defined(AFX_TABLISTPAGE_H__C1BEF74B_D4D1_4964_B53E_A03D4D79CB42__INCLUDED_)
#define AFX_TABLISTPAGE_H__C1BEF74B_D4D1_4964_B53E_A03D4D79CB42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CTabListPage dialog

class CTabListPage : public CXTPPropertyPage
{
	DECLARE_DYNCREATE(CTabListPage)

// Construction
public:
	CTabListPage();
	~CTabListPage();

// Dialog Data
	//{{AFX_DATA(CTabListPage)
	enum { IDD = IDD_PAGE_LISTCONTROL };
	BOOL	m_bFlatPage;
	int		m_nStyle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTabListPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTabListPage)
	afx_msg void OnCheckFlat();
	afx_msg void OnSelchangeComboStyle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABLISTPAGE_H__C1BEF74B_D4D1_4964_B53E_A03D4D79CB42__INCLUDED_)
