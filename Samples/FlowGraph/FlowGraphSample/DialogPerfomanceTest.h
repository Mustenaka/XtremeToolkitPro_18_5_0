// DialogPerfomanceTest.h
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


#ifndef __XTPRESIZEDIALOG_H__
#define CXTPResizeDialog CDialog
#endif

// CDialogPerfomanceTest dialog

class CDialogPerfomanceTest : public CXTPResizeDialog
{
	DECLARE_DYNAMIC(CDialogPerfomanceTest)

public:
	CDialogPerfomanceTest(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogPerfomanceTest();

// Dialog Data
	enum { IDD = IDD_DIALOG_PERFOMANCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CXTPFlowGraphControl m_wndControl;
	int m_nSmoothingMode;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonArrange();
	afx_msg void OnSmoothingModeChanged();
};
