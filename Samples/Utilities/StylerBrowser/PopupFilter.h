// PopupFilter.h
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

#if !defined(AFX_POPUPFILTER_H__41456DE8_536B_4E89_94AA_BEEEC78595B7__INCLUDED_)
#define AFX_POPUPFILTER_H__41456DE8_536B_4E89_94AA_BEEEC78595B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPopupFilter dialog

class CPopupFilter : public CDialog
{
// Construction
public:
	static void LoadFilterList(void);
	void SaveFilterList();
	CPopupFilter(CWnd* pParent = NULL);   // standard constructor

// Atributes
public:
	static CStringArray m_lstFilter;

protected:
	CXTPEditListBox m_LBEditor;


// Dialog Data
	//{{AFX_DATA(CPopupFilter)
	enum { IDD = IDD_POPUPFILTER };
	BOOL	m_bCheckAll;
	BOOL	m_bCheckList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPopupFilter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPopupFilter)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POPUPFILTER_H__41456DE8_536B_4E89_94AA_BEEEC78595B7__INCLUDED_)
