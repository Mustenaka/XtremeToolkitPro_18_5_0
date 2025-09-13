// PageOverlayIcons.h
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

#if !defined(AFX_PAGEOVERLAYICONS_H__D71EE683_D83E_46EE_9892_81BB9C7DA0F0__INCLUDED_)
#define AFX_PAGEOVERLAYICONS_H__D71EE683_D83E_46EE_9892_81BB9C7DA0F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CPageOverlayIcons dialog

class CPageOverlayIcons : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageOverlayIcons)

// Construction
public:
	CPageOverlayIcons();
	~CPageOverlayIcons();

// Dialog Data
	//{{AFX_DATA(CPageOverlayIcons)
	enum { IDD = IDD_PAGE_OVERLAY_ICONS };
	CXTPButton	m_btnQuestion;
	CXTPButton	m_btnNoVolume;
	CXTPButton	m_tnNoIcon;
	CXTPButton	m_btnInfo;
	//}}AFX_DATA

	CXTPTaskbarManager m_mgrTaskBar;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageOverlayIcons)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageOverlayIcons)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonInfo();
	afx_msg void OnButtonQuestion();
	afx_msg void OnButtonNoVolume();
	afx_msg void OnButtonNoIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEOVERLAYICONS_H__D71EE683_D83E_46EE_9892_81BB9C7DA0F0__INCLUDED_)
