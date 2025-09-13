// HistoryTree.h
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

#if !defined(AFX_HISTORYTREE_H__CC415E43_148C_11D4_9BB0_CFFDB04BA878__INCLUDED_)
#define AFX_HISTORYTREE_H__CC415E43_148C_11D4_9BB0_CFFDB04BA878__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <UrlHist.h>
#include "HisTreeCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CHistoryTree window

class CHistoryTree : public CObject, CXTPShellPidl
{
// Construction
public:
	CHistoryTree();
	CHisTreeCtrl m_wndHisTree;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistoryTree)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL m_bIE4;
	void AddHistory(IShellFolder* pFolder,HTREEITEM root, int nImg=0, int nOImg=0, BOOL bNeedCmp=FALSE);
	BOOL Update(int nLevel);
//for ie4 and win95
	CTime montime;
	int today;
	HTREEITEM FindAndInsert(HTREEITEM hRoot, LPCTSTR text, int nImg, int nOImg, int data=0);
	BOOL insertUrl(LPSTATURL pSUrl,int ind);
//end
	virtual void Destroy();
	LPCTSTR GetTitle();
	virtual ~CHistoryTree();
	CString strTitle;
	virtual BOOL Initialize();
	virtual BOOL Create(CWnd* pParent);
	virtual CWnd* GetWindow();
	IMalloc * m_pMalloc;
	BOOL ResolveHistory(IShellFolder* pFolder, LPCITEMIDLIST pidl, LPTSTR* lpszURL);

	// Generated message map functions
protected:
	//{{AFX_MSG(CHistoryTree)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	friend class CHisTreeCtrl;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTORYTREE_H__CC415E43_148C_11D4_9BB0_CFFDB04BA878__INCLUDED_)
