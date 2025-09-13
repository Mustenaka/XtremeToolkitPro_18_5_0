// CustomizePageRibbon.h
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

#if !defined(AFX_CUSTOMIZEPAGERIBBON_H__5EE0BF5B_4AE4_43BE_9EC0_CD0A5C36ECB3__INCLUDED_)
#define AFX_CUSTOMIZEPAGERIBBON_H__5EE0BF5B_4AE4_43BE_9EC0_CD0A5C36ECB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCustomizePageRibbon dialog

class CCustomizePageRibbon : public CXTPRibbonCustomizePage
{

// Construction
public:
	CCustomizePageRibbon(CXTPCommandBars* pCommandBars);
	~CCustomizePageRibbon();

// Dialog Data
	//{{AFX_DATA(CCustomizePageRibbon)
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCustomizePageRibbon)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	BOOL OnInitDialog();

	void OnButtonReset();

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCustomizePageRibbon)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMIZEPAGERIBBON_H__5EE0BF5B_4AE4_43BE_9EC0_CD0A5C36ECB3__INCLUDED_)
