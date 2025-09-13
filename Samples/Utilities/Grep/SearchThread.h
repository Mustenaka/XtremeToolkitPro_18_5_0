// SearchThread.h
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

#if !defined(AFX_SEARCHTHREAD_H__76911A8F_3028_4045_9702_016A2C49950A__INCLUDED_)
#define AFX_SEARCHTHREAD_H__76911A8F_3028_4045_9702_016A2C49950A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BatchSearch.h"

class CMainFrame;

#define WM_SEARCHFINISHED (WM_USER + 100)

/////////////////////////////////////////////////////////////////////////////
// CSearchThread thread

class CSearchThread : public CWinThread
{
	struct SEARCH_RESULT
	{
		int nMatchingLines;
		int nMatchingFiles;
		int nTotalFiles;
	} m_searchResult;

	DECLARE_DYNCREATE(CSearchThread)
protected:
	CSearchThread();           // protected constructor used by dynamic creation

public:
	virtual ~CSearchThread();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:

	BOOL ProcessPath(CString strPath);
	BOOL ProcessFile(CString strPath, CFileFind& finder);

	void SetMessageText();
	void AddRecord(CXTPReportControl& wndControl, TCHAR* lpszFileBuffer, TCHAR* lpszEndBuffer, long nIndex, long nLength,
		CString strMatch, CString strReplace, CString strPath, CFileFind& finder);


public:
	CMainFrame* m_pMainFrame;
	CXTPReportControl* m_pReportControl;
	BOOL m_bCancel;

	CBatchSearch m_batchSearch;

	// Generated message map functions
	//{{AFX_MSG(CSearchThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHTHREAD_H__76911A8F_3028_4045_9702_016A2C49950A__INCLUDED_)
