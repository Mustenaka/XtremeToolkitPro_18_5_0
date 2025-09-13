// TestColumnsDlg.cpp 
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
#include "TestColumnsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestColumnsDlg dialog

CTestColumnsDlg::CTestColumnsDlg(CWnd *pParent)
	: CDialog(CTestColumnsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestColumnsDlg)
	//}}AFX_DATA_INIT
}

void CTestColumnsDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestColumnsDlg)
	DDX_Control(pDX, IDC_REPORT, m_wndReport);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestColumnsDlg, CDialog)
	//{{AFX_MSG_MAP(CTestColumnsDlg)
	ON_NOTIFY(NM_RCLICK,                        IDC_REPORT, OnReportRClick)
	ON_NOTIFY(XTP_NM_REPORT_HEADER_RCLICK,      IDC_REPORT, OnHeaderRClick)
	ON_NOTIFY(XTP_NM_REPORT_COLUMNORDERCHANGED, IDC_REPORT, OnColumnOrderChanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestColumnsDlg message handlers

BOOL CTestColumnsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add columns
	AddColumn(0, _T("Test1"),  _T("ID1"), 100);
	AddColumn(1, _T("Test2"),  _T("ID1"), 100);
	AddColumn(2, _T("Test3"),  _T("ID1"), 100);
	AddColumn(3, _T("Test4"),  _T("ID1"), 100);
	AddColumn(4, _T("Test5"),  _T("ID1"), 100);
	AddColumn(5, _T("Test6"),  _T("ID1"), 100);
	AddColumn(6, _T("Test7"),  _T("ID1"), 100);
	AddColumn(7, _T("Test8"),  _T("ID1"), 100);
	AddColumn(8, _T("Test9"),  _T("ID1"), 100);
	AddColumn(9, _T("Test10"), _T("ID1"), 100);

	// Remove columns
	m_wndReport.GetColumns()->Remove(m_wndReport.GetColumns()->Find(3));
	m_wndReport.GetColumns()->Remove(m_wndReport.GetColumns()->Find(4));
	m_wndReport.GetColumns()->Remove(m_wndReport.GetColumns()->Find(5));
	m_wndReport.GetColumns()->Remove(m_wndReport.GetColumns()->Find(6));

	// Add one record with items (for remaining columns)
	CXTPReportRecord* pRecord = new CXTPReportRecord();
	AddItemText(pRecord, _T("Test1"));
	AddItemText(pRecord, _T("Test2"));
	AddItemText(pRecord, _T("Test3"));
	AddItemText(pRecord, _T("Test8"));
	AddItemText(pRecord, _T("Test9"));
	AddItemText(pRecord, _T("Test10"));
	m_wndReport.AddRecord(pRecord);

	// Populate
	m_wndReport.Populate();

#if 0
	enum
	{
		ColumnCount = 4,
		RecordCount = 5,
	};

	CString sName;

	// Add columns
	for (int nColumn=0; nColumn<ColumnCount; nColumn++)
	{
		sName.Format(_T("Column %d"), nColumn);
		m_wndReport.AddColumn(new CXTPReportColumn(nColumn, sName, 100, FALSE));
	}

	// Add records
	for (int nRecord=0; nRecord<RecordCount; nRecord++)
	{
		CXTPReportRecord *pRecord = m_wndReport.AddRecord(new CXTPReportRecord());

		for (int nColumn=0; nColumn<ColumnCount; nColumn++)
		{
			sName.Format(_T("Item %d"), nColumn);
			CXTPReportRecordItemText *pItem = new CXTPReportRecordItemText(sName);
			pRecord->AddItem(pItem);
		}
	}

	// Populate
	m_wndReport.Populate();
#endif

	return FALSE;
}

int CTestColumnsDlg::AddColumn(int iColumnID, LPCTSTR pstrTitle, LPCTSTR pstrInternalUniqueID,
  int iWidth, BOOL bAutoSize, int iIconResourceID, BOOL bSortable, BOOL bVisible)
{
	CXTPReportColumn *pColumn = new CXTPReportColumn(iColumnID, pstrTitle, iWidth, bAutoSize, iIconResourceID, bSortable, bVisible);

	m_wndReport.AddColumn(pColumn);
	pColumn->SetInternalName(pstrInternalUniqueID);
	return iColumnID;
}

CXTPReportRecordItemText* CTestColumnsDlg::AddItemText(CXTPReportRecord* pRecord, LPCTSTR pszText)
{
	CXTPReportRecordItemText *pItem = new CXTPReportRecordItemText(pszText);
	pRecord->AddItem(pItem);
	return pItem;
}


void CTestColumnsDlg::OnOK()
{
	CDialog::OnOK();
}

void CTestColumnsDlg::OnColumnOrderChanged(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	XTP_NM_REPORTCOLUMNORDERCHANGED *pItemNotify =
		reinterpret_cast<XTP_NM_REPORTCOLUMNORDERCHANGED*>(pNotifyStruct);
}

void CTestColumnsDlg::OnHeaderRClick(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	XTP_NM_REPORTRECORDITEM *pItemNotify =
		reinterpret_cast<XTP_NM_REPORTRECORDITEM*>(pNotifyStruct);

	if (NULL != pItemNotify->pColumn)
	{
		int nSubMenu = 3;

		CMenu menu;
		VERIFY(menu.LoadMenu(IDR_MENU_TEST_COLUMNS));
#ifndef _XTP_INCLUDE_COMMANDBARS
		int nMenuResult = menu.GetSubMenu(nSubMenu)->TrackPopupMenu(TPM_RETURNCMD | TPM_LEFTALIGN |TPM_RIGHTBUTTON, pItemNotify->pt.x, pItemNotify->pt.y, this, NULL);
#else
		int nMenuResult = CXTPCommandBars::TrackPopupMenu(menu.GetSubMenu(nSubMenu), TPM_NONOTIFY | TPM_RETURNCMD | TPM_LEFTALIGN |TPM_RIGHTBUTTON, pItemNotify->pt.x, pItemNotify->pt.y, this, NULL);
#endif

		switch(nMenuResult)
		{
		case ID_TEST_COLUMN_REMOVE:
			m_wndReport.GetColumns()->Remove(pItemNotify->pColumn);
			break;
		}
	}
}

void CTestColumnsDlg::OnReportRClick(NMHDR *pNotifyStruct, LRESULT *pResult)
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
