// PictureView.h 
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

#if !defined(AFX_PICTUREVIEW_H__693E9CEE_BC86_4FBA_A6CC_A5B3BE7BBFF8__INCLUDED_)
#define AFX_VIEW_H__693E9CEE_BC86_4FBA_A6CC_A5B3BE7BBFF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPictureView dialog

class CPictureView : public CView
{
	DECLARE_DYNCREATE(CPictureView);

	CPictureView();

// Implementation
private:
	CBitmap m_Image;
	BITMAP m_bmpInfo;

	void OnScroll(int nBar, UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

protected:
	// Generated message map functions
	//{{AFX_MSG(CPictureView)
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEW_H__693E9CEE_BC86_4FBA_A6CC_A5B3BE7BBFF8__INCLUDED_)
