// TestPopupDlg.cpp 
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

#include "StdAfx.h"
#include "Resource.h"
#include "TestPopupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestPopupDlg dialog

CTestPopupDlg::CTestPopupDlg(CWnd *pParent)
	: CDialog(CTestPopupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestPopupDlg)
	//}}AFX_DATA_INIT
}

void CTestPopupDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestPopupDlg)
	DDX_Control(pDX, IDC_REPORT, m_wndReport);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestPopupDlg, CDialog)
	//{{AFX_MSG_MAP(CTestPopupDlg)
	ON_NOTIFY(NM_RCLICK, IDC_REPORT, OnReportRClick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestPopupDlg message handlers

BOOL CTestPopupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	enum
	{
		ColumnCount = 3,
		RecordCount = 5,
	};

	// Add columns
	for (int nColumn=0; nColumn<ColumnCount; nColumn++)
	{
		CString sName;
		sName.Format(_T("Column %d"), nColumn);
		m_wndReport.AddColumn(new CXTPReportColumn(nColumn, sName, 100));
	}

	// Add records
	for (int nRecord=0; nRecord<RecordCount; nRecord++)
	{
		CXTPReportRecord *pRecord = m_wndReport.AddRecord(new CXTPReportRecord());

		for (int nColumn=0; nColumn<ColumnCount; nColumn++)
		{
			CXTPReportRecordItemText *pItem = new CXTPReportRecordItemText(_T("Test"));
			pRecord->AddItem(pItem);
		}
	}

	// Auto group
	m_wndReport.GetColumns()->GetGroupsOrder()->Clear();
	CXTPReportColumn *pColumn = m_wndReport.GetColumns()->GetAt(0);
	m_wndReport.GetColumns()->GetGroupsOrder()->Add(pColumn);

	// Populate
	m_wndReport.Populate();

	return FALSE;
}

void CTestPopupDlg::OnOK()
{
	CDialog::OnOK();
}

void CTestPopupDlg::OnReportRClick(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	XTP_NM_REPORTRECORDITEM *pItemNotify = reinterpret_cast<XTP_NM_REPORTRECORDITEM*>(pNotifyStruct);

	int nSubMenu = -1;

	if (NULL != pItemNotify->pRow)
	{
		if (pItemNotify->pRow->IsGroupRow())
		{
			nSubMenu = 0;
		}
		else
		{
			nSubMenu = 1;
		}
	}
	else
	{
		nSubMenu = 2;
	}

	if (-1 != nSubMenu)
	{
		CMenu menu;
		VERIFY(menu.LoadMenu(IDR_MENU_TEST_POPUP));
#ifndef _XTP_INCLUDE_COMMANDBARS
		int nMenuResult = menu.GetSubMenu(nSubMenu)->TrackPopupMenu(TPM_RETURNCMD | TPM_LEFTALIGN |TPM_RIGHTBUTTON, pItemNotify->pt.x, pItemNotify->pt.y, this, NULL);
#else
		int nMenuResult = CXTPCommandBars::TrackPopupMenu(menu.GetSubMenu(nSubMenu), TPM_NONOTIFY | TPM_RETURNCMD | TPM_LEFTALIGN |TPM_RIGHTBUTTON, pItemNotify->pt.x, pItemNotify->pt.y, this, NULL);
#endif
	}
}
