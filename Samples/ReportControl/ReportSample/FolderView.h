// FolderView.h 
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

#if !defined(_FOLDERVIEW_H_)
#define _FOLDERVIEW_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CReportSampleDoc;

class CFolderView : public CXTPReportView
{
protected: // create from serialization only
	CFolderView();
	DECLARE_DYNCREATE(CFolderView)

// Attributes
public:
	CReportSampleDoc* GetDocument();

public:

	//{{AFX_VIRTUAL(CFolderView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	//}}AFX_VIRTUAL

public:
	virtual ~CFolderView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


protected:
	//{{AFX_MSG(CReportSampleView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnDestroy();
	afx_msg void OnFilePrint();
	DECLARE_MESSAGE_MAP()

};

#ifndef _DEBUG  // debug version in ReportSampleView.cpp
inline CReportSampleDoc* CFolderView::GetDocument()
{
	return (CReportSampleDoc*)m_pDocument;
}
#endif

//{{AFX_INSERT_LOCATION}}

#endif // !defined(_FOLDERVIEW_H_)
