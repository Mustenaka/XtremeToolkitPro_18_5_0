// PaneViewTaskPanel.h 
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

#if !defined(__PANETASKPANEL_H__)
#define __PANETASKPANEL_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPaneViewTaskPanel window

class CPaneViewTaskPanel : public CPaneWnd
{
public:
	CPaneViewTaskPanel();
	virtual ~CPaneViewTaskPanel();

	CXTPTaskPanel m_wndTaskPanel;

	void DoPropExchange(CXTPPropExchange* pPX);
	void ResetToolboxItems();

	//{{AFX_VIRTUAL(CPaneViewTaskPanel)
	//}}AFX_VIRTUAL

protected:
	int m_nToolboxIcons;

	virtual void RefreshMetrics(AppTheme nTheme);
	CXTPTaskPanelGroup* CreateToolboxGroup(UINT nID);

	//{{AFX_MSG(CPaneViewTaskPanel)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__PANETASKPANEL_H__)
