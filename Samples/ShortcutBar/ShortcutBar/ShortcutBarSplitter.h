// ShortcutBarSplitter.h
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

#if !defined(AFX_SHORTCUTBARSPLITTER_H__F44C5093_06DE_4CDC_AA2B_73D65FB65858__INCLUDED_)
#define AFX_SHORTCUTBARSPLITTER_H__F44C5093_06DE_4CDC_AA2B_73D65FB65858__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CShortcutBarSplitter frame with splitter

#ifndef _XTP_INCLUDE_CONTROLS
#define CXTPSplitterWndEx CSplitterWnd
#endif

class CShortcutBarSplitter : public CXTPSplitterWndEx
{
	DECLARE_DYNCREATE(CShortcutBarSplitter)

public:
	CShortcutBarSplitter();           // protected constructor used by dynamic creation

// Attributes
protected:
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShortcutBarSplitter)
	protected:
	//}}AFX_VIRTUAL

	void TrackColumnSize(int x, int col);

// Implementation
public:
	virtual ~CShortcutBarSplitter();

	// Generated message map functions
	//{{AFX_MSG(CShortcutBarSplitter)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#ifndef _XTP_INCLUDE_CONTROLS
#define CSplitterWndEx CSplitterWnd
#else
class CSplitterWndEx : public CXTPSplitterWnd
{
public:
	CSplitterWndEx()
	{
		m_cyBorder = m_cxBorder = 2;
		m_cxSplitter = m_cySplitter = 4;
		m_cySplitterGap = m_cxSplitterGap = 4;
		
		m_cxBorderShare = m_cyBorderShare = 0;
		
		
		EnableFullDrag(FALSE);
	}
	
};
#endif
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHORTCUTBARSPLITTER_H__F44C5093_06DE_4CDC_AA2B_73D65FB65858__INCLUDED_)
