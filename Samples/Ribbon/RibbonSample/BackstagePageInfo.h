// BackstagePageInfo.h
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

#if !defined(AFX_BACKSTAGEPAGEINFO_H__96962F77_2D2D_4C65_BE2B_DF2425152C6C__INCLUDED_)
#define AFX_BACKSTAGEPAGEINFO_H__96962F77_2D2D_4C65_BE2B_DF2425152C6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBackstagePageInfo dialog

class CBackstagePageInfo : public CXTPRibbonBackstagePage
{
// Construction
public:
	CBackstagePageInfo();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBackstagePageInfo)
	enum { IDD = IDD_BACKSTAGEPAGE_INFO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	virtual void SetTheme(const XTPControlTheme nTheme);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBackstagePageInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

public:

	CXTPRibbonBackstageLabel m_lblInformation;

	CXTPRibbonBackstageLabel m_lblPermissions;
	CXTPRibbonBackstageLabel m_lblPrepareForSharing;
	CXTPRibbonBackstageLabel m_lblVersions;
	
	CXTPRibbonBackstageSeparator m_lblSeparator1;
	CXTPRibbonBackstageSeparator m_lblSeparator2;
	CXTPRibbonBackstageSeparator m_lblSeparator3;
	CXTPRibbonBackstageSeparator m_lblSeparator4;

	CXTPRibbonBackstageButton m_btnProtectDocument;
	CXTPRibbonBackstageButton m_btnCheckForIssues;
	CXTPRibbonBackstageButton m_btnManageVersions;

	CXTPImageManager m_imagelist;

	void InitButton(UINT nID, BOOL bPopup);
	void ReinitButton(UINT nID, BOOL bPopup);
	void SetImages(XTPControlTheme nTheme);

	// Generated message map functions
	//{{AFX_MSG(CBackstagePageInfo)
	virtual BOOL OnInitDialog();
	afx_msg void OnStaticPreview();
	//}}AFX_MSG
	void OnProtectDocumentDropDown();
	void OnCheckForIssuesDropDown();
	
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BACKSTAGEPAGEINFO_H__96962F77_2D2D_4C65_BE2B_DF2425152C6C__INCLUDED_)
