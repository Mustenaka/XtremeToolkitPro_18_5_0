// CustomizePageQuickAccessToolbar.h
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

#if !defined(AFX_CUSTOMIZEPAGEQUICKACCESSTOOLBAR_H__163B7B41_F44C_432F_8D73_B0996EDF2E56__INCLUDED_)
#define AFX_CUSTOMIZEPAGEQUICKACCESSTOOLBAR_H__163B7B41_F44C_432F_8D73_B0996EDF2E56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCustomizePageQuickAccessToolbar dialog

class CCustomizePageQuickAccessToolbar : public CXTPRibbonCustomizeQuickAccessPage
{
// Construction
public:
	CCustomizePageQuickAccessToolbar(CXTPCommandBars* pCommandBars);
	~CCustomizePageQuickAccessToolbar();


// Dialog Data
	//{{AFX_DATA(CCustomizePageQuickAccessToolbar)
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCustomizePageQuickAccessToolbar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	BOOL OnInitDialog();

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCustomizePageQuickAccessToolbar)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMIZEPAGEQUICKACCESSTOOLBAR_H__163B7B41_F44C_432F_8D73_B0996EDF2E56__INCLUDED_)
