// TestItemTypesDlg.cpp
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
#include "TestItemTypesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestItemTypesDlg dialog

CTestItemTypesDlg::CTestItemTypesDlg(CWnd *pParent)
	: CDialog(CTestItemTypesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestItemTypesDlg)
	//}}AFX_DATA_INIT
}

void CTestItemTypesDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestItemTypesDlg)
	DDX_Control(pDX, IDC_REPORT, m_wndReport);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestItemTypesDlg, CDialog)
	//{{AFX_MSG_MAP(CTestItemTypesDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestItemTypesDlg message handlers

BOOL CTestItemTypesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	enum Column
	{
		ColumnDateTime,
		ColumnIcon,
		ColumnNumber,
		ColumnText,
		ColumnCount
	};

	static const LPCTSTR columnName[ColumnCount] =
	{
		_T("DateTime"),
		_T("Icon"),
		_T("Number"),
		_T("Text")
	};

	// Add columns
	for (int nColumn=0; nColumn<ColumnCount; nColumn++)
	{
		m_wndReport.AddColumn(new CXTPReportColumn(nColumn, columnName[nColumn], 100));
	}

/*
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
*/

	// Populate
	m_wndReport.Populate();

	return FALSE;
}

void CTestItemTypesDlg::OnOK()
{
	CDialog::OnOK();
}
