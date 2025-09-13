// RibbonMDISampleView.h
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

#if !defined(AFX_RIBBONMDISAMPLEVIEW_H__1DA10B36_73A6_4712_A870_CD24CE1D8969__INCLUDED_)
#define AFX_RIBBONMDISAMPLEVIEW_H__1DA10B36_73A6_4712_A870_CD24CE1D8969__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRibbonMDISampleCntrItem;
class CRibbonMDISampleDoc;
class CRibbonMDISampleView : public CRichEditView
{
protected: // create from serialization only
	CRibbonMDISampleView();
	DECLARE_DYNCREATE(CRibbonMDISampleView)

	// Attributes
public:
	CRibbonMDISampleDoc* GetDocument();

	// Operations
public:
	void SetLayoutRTL(BOOL bRTLLayout);
	void Reposition(CSize sz);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRibbonMDISampleView)
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

	// Implementation
public:
	virtual ~CRibbonMDISampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void OnFilePrintPreview();
	void OnRequestResize(NMHDR * pNotifyStruct, LRESULT* result );
	void OnEditScrollChanged();
	void UpdateScrollInfo();
	virtual CScrollBar* GetScrollBarCtrl(int nBar) const;
	void SetScrollPos(int nScrollPos);
	void UpdatePosition();

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
	//{{AFX_MSG(CRibbonMDISampleView)
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnDestroy();
	afx_msg void OnNcPaint();
	//}}AFX_MSG

private:
	CRect GetViewRect(CRect rc);
	int GetPageSize();
	CXTPCommandBarScrollBarCtrl m_wndScrollBar;
	int m_nTextHeight;
	int m_nScrollPos;
	int m_nTotalHeight;
	BOOL m_bInScrollChanged;
};

#ifndef _DEBUG  // debug version in RibbonMDISampleView.cpp
inline CRibbonMDISampleDoc* CRibbonMDISampleView::GetDocument()
{ return (CRibbonMDISampleDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RIBBONMDISAMPLEVIEW_H__1DA10B36_73A6_4712_A870_CD24CE1D8969__INCLUDED_)
