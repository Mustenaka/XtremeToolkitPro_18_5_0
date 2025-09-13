// DialogControlsTest.h
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

// CDialogControlsTest dialog

class CDialogControlsTest : public CDialog
{
	DECLARE_DYNAMIC(CDialogControlsTest)

public:
	CDialogControlsTest(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogControlsTest();

// Dialog Data
	enum { IDD = IDD_DIALOG_CONTROLS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CXTPFlowGraphControl m_wndControl;

	CTreeCtrl m_wndTreeCtrl;
	CListCtrl m_wndListView;

	virtual BOOL OnInitDialog();
};
