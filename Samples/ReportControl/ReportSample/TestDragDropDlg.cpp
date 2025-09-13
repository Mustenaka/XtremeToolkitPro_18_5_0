// TestDragDropDlg.cpp 
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
#include "TestDragDropDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestDragDropDlg dialog

CTestDragDropDlg::CTestDragDropDlg(CWnd *pParent)
	: CDialog(CTestDragDropDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDragDropDlg)
	m_bSortedDragDrop1 = FALSE;
	m_bSortedDragDrop2 = FALSE;
	//}}AFX_DATA_INIT
}

void CTestDragDropDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDragDropDlg)
	DDX_Check  (pDX, IDC_SORTED_DRAG_DROP1, m_bSortedDragDrop1);
	DDX_Check  (pDX, IDC_SORTED_DRAG_DROP2, m_bSortedDragDrop2);
	DDX_Control(pDX, IDC_REPORT1,           m_wndReport1);
	DDX_Control(pDX, IDC_REPORT2,           m_wndReport2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDragDropDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDragDropDlg)
	ON_BN_CLICKED(IDC_SORTED_DRAG_DROP1, OnSortedDragDrop1)
	ON_BN_CLICKED(IDC_SORTED_DRAG_DROP2, OnSortedDragDrop2)
	ON_NOTIFY(XTP_NM_REPORT_BEGINDRAG, IDC_REPORT1, OnReportBeginDrag1)
	ON_NOTIFY(XTP_NM_REPORT_DROP,      IDC_REPORT2, OnReportDrop2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDragDropDlg message handlers

BOOL CTestDragDropDlg::OnInitDialog()
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
		m_wndReport1.AddColumn(new CXTPReportColumn(nColumn, sName, 100));
		m_wndReport2.AddColumn(new CXTPReportColumn(nColumn, sName, 100));
	}

	// Add records
	for (int nRecord=0; nRecord<RecordCount; nRecord++)
	{
		CXTPReportRecord *pRecord = m_wndReport1.AddRecord(new CXTPReportRecord());

		for (int nColumn=0; nColumn<ColumnCount; nColumn++)
		{
			CString sItem;
			sItem.Format(_T("Item %d, %d"), nRecord, nColumn);

			CXTPReportRecordItemText *pItem = new CXTPReportRecordItemText(sItem);
			pRecord->AddItem(pItem);
		}
	}

	// Populate
	m_wndReport1.Populate();

	// Enable drag & drop
	m_wndReport1.EnableDragDrop(_T("TestDragDrop"), xtpReportAllowDrag | xtpReportAllowDrop);
	m_wndReport2.EnableDragDrop(_T("TestDragDrop"), xtpReportAllowDrag | xtpReportAllowDrop);
	
	m_bSortedDragDrop1 = m_wndReport1.m_bSortedDragDrop;
	m_bSortedDragDrop2 = m_wndReport2.m_bSortedDragDrop;
	UpdateData(FALSE);

	return FALSE;
}

void CTestDragDropDlg::OnOK()
{
	CDialog::OnOK();
}

void CTestDragDropDlg::OnSortedDragDrop1()
{
	UpdateData();
	m_wndReport1.m_bSortedDragDrop = m_bSortedDragDrop1;
}

void CTestDragDropDlg::OnSortedDragDrop2()
{
	UpdateData();
	m_wndReport2.m_bSortedDragDrop = m_bSortedDragDrop2;
}

void CTestDragDropDlg::OnReportBeginDrag1(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	XTP_NM_REPORTDRAGDROP *pItemNotify = reinterpret_cast<XTP_NM_REPORTDRAGDROP *>(pNotifyStruct);
}

void CTestDragDropDlg::OnReportDrop2(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	XTP_NM_REPORTDRAGDROP *pItemNotify = reinterpret_cast<XTP_NM_REPORTDRAGDROP *>(pNotifyStruct);
}
