// DialogPageTransitionTest.h
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

#pragma once

#include "FlowGraphSampleView.h"

// CDialogPageTransitionTest dialog

#ifndef __XTPRESIZEDIALOG_H__
#define CXTPResizeDialog CDialog
#endif

class CDialogPageTransitionTest : public CXTPResizeDialog
{
	DECLARE_DYNAMIC(CDialogPageTransitionTest)

public:
	CDialogPageTransitionTest(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogPageTransitionTest();

// Dialog Data
	enum { IDD = IDD_DIALOG_PAGETRANSITION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CXTPFlowGraphControl m_wndControl;
	virtual BOOL OnInitDialog();

	afx_msg void OnGraphDblClick(NMHDR* pNMHDR, LRESULT* pResult);

	void UpdateButtons();

	void CreateDatabasePage();
	void CreateTable1Page();
	void CreateTable2Page();

	afx_msg void OnBnClickedButtonPrev();
	afx_msg void OnBnClickedButtonNext();
	afx_msg LRESULT OnAppCommand(WPARAM wParam, LPARAM lParam);
};
