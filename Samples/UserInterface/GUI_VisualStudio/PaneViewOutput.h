// PaneViewOutput.h 
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

#if !defined(AFX_OUTPUTPANE_H__C81C6B0E_433E_46A5_9598_EFBD9CD6A93E__INCLUDED_)
#define AFX_OUTPUTPANE_H__C81C6B0E_433E_46A5_9598_EFBD9CD6A93E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPaneViewOutput window

class CPaneViewOutput : public CXTPEditor
{
public:
	CPaneViewOutput();
	virtual ~CPaneViewOutput();

	void SetOwnerPane(CXTPDockingPane* pPane);

	//{{AFX_VIRTUAL(CPaneViewOutput)
	//}}AFX_VIRTUAL

protected:
	CXTPDockingPane* m_pPane;

	//{{AFX_MSG(CPaneViewOutput)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNcPaint();
	//}}AFX_MSG
	afx_msg LRESULT OnRefreshMetrics(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

AFX_INLINE void CPaneViewOutput::SetOwnerPane(CXTPDockingPane* pPane) {
	m_pPane = pPane;
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTPUTPANE_H__C81C6B0E_433E_46A5_9598_EFBD9CD6A93E__INCLUDED_)
