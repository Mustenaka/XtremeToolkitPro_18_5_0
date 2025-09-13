// StockSampleView.h
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

#if !defined(AFX_STOCKSAMPLEVIEW_H__E4BA6578_52B4_4E3C_8A42_893DE0BD5E23__INCLUDED_)
#define AFX_STOCKSAMPLEVIEW_H__E4BA6578_52B4_4E3C_8A42_893DE0BD5E23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStockSampleView : public CView
{
protected: // create from serialization only
	CStockSampleView();
	DECLARE_DYNCREATE(CStockSampleView)

// Attributes
public:
	CStockSampleDoc* GetDocument();

// Operations
public:
	void UpdateHistory(LPCTSTR lpszSymbol, BOOL bCandleStick, int nDays = 180);
    void SetThickStyle(BOOL bThickLine);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStockSampleView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStockSampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	BOOL m_bCandleStick;
	BOOL m_bThickLine;

	CXTPChartControl m_wndChartControl;
	CStockQuoteDlg m_dlgStockQuote;

	void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	void OnFilePrintPreview();
	void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo);

// Generated message map functions
protected:
	//{{AFX_MSG(CStockSampleView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnViewStockquote();
	afx_msg void OnUpdateViewStockquote(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnViewThickstyle();
	afx_msg void OnUpdateViewThickstyle(CCmdUI *pCmdUI);
	afx_msg void OnViewCandles();
	afx_msg void OnUpdateViewCandles(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in StockSampleView.cpp
inline CStockSampleDoc* CStockSampleView::GetDocument()
   { return (CStockSampleDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STOCKSAMPLEVIEW_H__E4BA6578_52B4_4E3C_8A42_893DE0BD5E23__INCLUDED_)
