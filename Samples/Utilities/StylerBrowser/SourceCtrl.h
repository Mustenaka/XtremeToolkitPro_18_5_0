// SourceCtrl.h
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

#if !defined(AFX_SOURCECTRL_H__77384FDA_915D_4187_AA1F_CF39C490C691__INCLUDED_)
#define AFX_SOURCECTRL_H__77384FDA_915D_4187_AA1F_CF39C490C691__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CSourceCtrl window

class CSourceCtrl : public CRichEditCtrl
{
// Construction
public:
	CSourceCtrl();

// Attributes
public:

private:
	CFont m_fntText;

// Operations
public:
	
	CString GetTitle()
	{
		CString strTitle;
		strTitle.LoadString(IDS_TITLE_SOURCE);
		return strTitle;
	}
	BOOL Create(CWnd* pParent);
	void Refresh(CHtmlView* pView, BOOL bForce);

private:
	void SetTextFormat(LPTSTR pText);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSourceCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSourceCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSourceCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOURCECTRL_H__77384FDA_915D_4187_AA1F_CF39C490C691__INCLUDED_)
