// TaskSheetProperties.h
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

#if !defined(__TASKSHEETPROPERTIES_H__)
#define __TASKSHEETPROPERTIES_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "TaskPageGeneral.h"
#include "TaskPageExpanded.h"
#include "TaskPageButtons.h"
#include "TaskPageRadioButtons.h"
#include "TaskPageIcons.h"
#include "TaskPageSamples.h"

class CTaskDialogEx : public CXTPTaskDialog
{
public:
	CTaskDialogEx(CWnd* pWndParent)
		: CXTPTaskDialog(pWndParent)
	{

	}
protected:
	virtual void OnHyperlinkClicked(LPCTSTR pszURL)
	{
		AfxMessageBox(pszURL);
	}
	virtual void OnDialogConstructed()
	{
		if (m_config.dwFlags & TDF_SHOW_PROGRESS_BAR)
			SetProgressBarPos(30);
		
		if (m_config.dwFlags & TDF_SHOW_MARQUEE_PROGRESS_BAR)
			StartProgressBarMarquee(1, 100);
	}
};

/////////////////////////////////////////////////////////////////////////////
// CTaskSheetProperties

typedef CMap<int,int,CString,CString> CButtonMap;

class CTaskSheetProperties : public CPropertySheet
{
	DECLARE_DYNAMIC(CTaskSheetProperties)

public:
	CTaskSheetProperties(CWnd* pWndParent = NULL);
	virtual ~CTaskSheetProperties();

public:
    CTaskPageGeneral      m_pageGeneral;
    CTaskPageExpanded     m_pageExpanded;
    CTaskPageButtons      m_pageButtons;
    CTaskPageRadioButtons m_pageRadioButtons;
    CTaskPageIcons        m_pageIcons;
	CTaskPageSamples      m_pageSamples;

	//{{AFX_DATA(CTaskSheetProperties)
	CButton m_btnOk;
	CButton m_btnCancel;
	CButton m_btnApply;
	CButton m_btnHelp;
	//}}AFX_DATA

	CButtonMap& GetButtonMap() {
		return m_mapButtons;
	}

	//{{AFX_VIRTUAL(CTaskSheetProperties)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

public:
	BOOL UsingComCtl32();
	BOOL UpdateButtonMap(CString strName, int nID, CComboBox* pWndCombo = NULL, BOOL bAdd = TRUE);


	BOOL  m_bUseComCtl32;

protected:
	int GetPadding();
	void GetButtonRect(CRect& rcButton, CButton& wndButton, BOOL bHideButton = FALSE);
	CButtonMap m_mapButtons;


	CRect m_rcOk;
	CRect m_rcCancel;
	CRect m_rcApply;
	CRect m_rcHelp;

	//CXTPTaskDialog m_taskDlg;

	//{{AFX_MSG(CTaskSheetProperties)
	afx_msg void OnChkUseComCtl();
	afx_msg void OnShowDialog();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

AFX_INLINE BOOL CTaskSheetProperties::UsingComCtl32() {
	return m_bUseComCtl32;
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__TASKSHEETPROPERTIES_H__)
