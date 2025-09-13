// MarkupPadEdit.h
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

#if !defined(AFX_MARKUPPADEDIT_H__BCE9D291_92E3_46A3_9669_13F398601812__INCLUDED_)
#define AFX_MARKUPPADEDIT_H__BCE9D291_92E3_46A3_9669_13F398601812__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMarkupPadEdit view

class CMarkupPadEdit : public CEditView
{
protected:
	CMarkupPadEdit();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMarkupPadEdit)

// Attributes
public:

// Operations
public:
	HINSTANCE m_hInstance;

	LPWSTR GetUnicodeText();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMarkupPadEdit)
	public:
	virtual void OnInitialUpdate();
	protected:
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMarkupPadEdit();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	CFont m_fnt;
	void UpdateViews();
	BOOL m_bFirstDoc;
	BOOL m_bError;

	void OnStatusBarHyperlinkClick(CXTPMarkupObject* pSender, CXTPMarkupRoutedEventArgs* pArgs);


	// Generated message map functions
public:
	//{{AFX_MSG(CMarkupPadEdit)
	afx_msg void OnChange();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MARKUPPADEDIT_H__BCE9D291_92E3_46A3_9669_13F398601812__INCLUDED_)
