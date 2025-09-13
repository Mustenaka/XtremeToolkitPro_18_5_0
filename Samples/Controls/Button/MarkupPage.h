// MarkupPage.h
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

#if !defined(AFX_MARKUPPAGE_H__B562CD82_7DEE_4D53_8D59_6DAD12D3ECAF__INCLUDED_)
#define AFX_MARKUPPAGE_H__B562CD82_7DEE_4D53_8D59_6DAD12D3ECAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CMarkupPage dialog

class CMarkupPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMarkupPage)

// Construction
public:
	CMarkupPage();
	~CMarkupPage();

// Dialog Data
	//{{AFX_DATA(CMarkupPage)
	enum { IDD = IDD_PAGE_MARKUPBUTTONS };
	CXTPButton	m_btnRadioWithLink;
	CXTPButton	m_btnDeleteOutbox;
	CXTPButton	m_btnDeleteInbox;
	CXTPButton	m_btnFirewall;
	CXTPButton	m_btnPushButton;
	CXTPButton	m_btnRadio;
	CXTPButton	m_btnCheckBox;
	//}}AFX_DATA

#ifdef _XTP_INCLUDE_MARKUP
	void OnHyperlinkClick(CXTPMarkupObject* pSender, CXTPMarkupRoutedEventArgs* pArgs);
#endif

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMarkupPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMarkupPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MARKUPPAGE_H__B562CD82_7DEE_4D53_8D59_6DAD12D3ECAF__INCLUDED_)
