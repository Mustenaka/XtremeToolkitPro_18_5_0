// PageProgressBar.h
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

#if !defined(AFX_PAGEPROGRESSBAR_H__27CD5A09_EFEF_41CA_BD0F_35268CA3F3C3__INCLUDED_)
#define AFX_PAGEPROGRESSBAR_H__27CD5A09_EFEF_41CA_BD0F_35268CA3F3C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CPageProgressBar dialog

class CPageProgressBar : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageProgressBar)

// Construction
public:
	CPageProgressBar();
	~CPageProgressBar();

// Dialog Data
	//{{AFX_DATA(CPageProgressBar)
	enum { IDD = IDD_PAGE_PROGRESS_BAR };
	int		m_nStatus;
	int		m_nValue;
	//}}AFX_DATA

	CXTPTaskbarManager m_mgrTaskBar;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageProgressBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageProgressBar)
	afx_msg void OnSelChangeComboStatus();
	afx_msg void OnReleasedCaptureSliderProgress(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEPROGRESSBAR_H__27CD5A09_EFEF_41CA_BD0F_35268CA3F3C3__INCLUDED_)
