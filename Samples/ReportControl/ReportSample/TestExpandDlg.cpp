// TestExpandDlg.cpp 
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
#include "TestExpandDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestExpandDlg dialog

CTestExpandDlg::CTestExpandDlg(CWnd *pParent)
	: CDialog(CTestExpandDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestExpandDlg)
	m_bNotificationExpanded = FALSE;
	//}}AFX_DATA_INIT
}

void CTestExpandDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestExpandDlg)
	DDX_Control(pDX, IDC_REPORT, m_wndReport);
	DDX_Text(pDX, IDC_TIME, m_sTime);
	DDX_CBIndex(pDX, IDC_COUNT, m_nCount);
	DDX_Check(pDX, IDC_NOTIFICATION_EXPANDED, m_bNotificationExpanded);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestExpandDlg, CDialog)
	//{{AFX_MSG_MAP(CTestExpandDlg)
	ON_BN_CLICKED(IDC_EXPAND,   OnExpand)
	ON_BN_CLICKED(IDC_COLLAPSE, OnCollapse)
	ON_CBN_SELENDOK(IDC_COUNT, OnCount)
	ON_BN_CLICKED(IDC_NOTIFICATION_EXPANDED, OnNotificationExpanded)
	ON_BN_CLICKED(IDC_INDEXES, OnIndexes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestExpandDlg message handlers


int Count[] =
{
	10,
	100,
	1000,
	2500,
	5000,
	10000,
	20000,
	30000,
	100000
};


BOOL CTestExpandDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	// Add columns
	CXTPReportColumn *pColumn;
	
	pColumn = new CXTPReportColumn(0, _T("Tree"), 100);
	m_wndReport.AddColumn(pColumn);
	pColumn->SetTreeColumn(TRUE);

	pColumn = new CXTPReportColumn(1, _T("Index"), 100);
	m_wndReport.AddColumn(pColumn);


	m_bNotificationExpanded = m_wndReport.GetBehavior()->Notifications->Row->bRowExpanded;
	m_nCount = 1;
	AddRecords(Count[m_nCount]);

	UpdateData(FALSE);

	return FALSE;
}

CXTPReportRecord* AddItems(CXTPReportRecord *pRecord, CString sText, int nRecord)
{
	CString sRecord;
	sRecord.Format(_T("Record %d"), nRecord);

	CXTPReportRecordItemText *pItem = new CXTPReportRecordItemText(sRecord);
	pRecord->AddItem(pItem);
	pRecord->AddItem(new CXTPReportRecordItemNumber());

	CString sItem;
	sItem.Format(_T("%s %d %d"), sText, nRecord, 0);

	// Text
	CXTPReportRecord *pChild = new CXTPReportRecord();
	pChild->AddItem(new CXTPReportRecordItemText(sItem));
	pChild->AddItem(new CXTPReportRecordItemNumber());
	pRecord->GetChilds()->Add(pChild);

	return pChild;
}

void CTestExpandDlg::AddRecords(int nRecordCount)
{
	m_wndReport.ResetContent(FALSE);

	DWORD dwStart = ::GetTickCount();

	CXTPReportRecord *pRecord;

	// Add records
	for (int nRecord=0; nRecord<nRecordCount; nRecord++)
	{
		pRecord = m_wndReport.AddRecord(new CXTPReportRecord());
		CXTPReportRecord *pChild;
		pChild = AddItems(pRecord, _T("Level 1"), nRecord);
		pChild = AddItems(pChild,  _T("Level 2"), nRecord);
		pChild = AddItems(pChild,  _T("Level 3"), nRecord);
	}

	pRecord = m_wndReport.GetFooterRecords()->Add(new CXTPReportRecord());
	AddItems(pRecord, _T("Item"), 0);

	m_wndReport.Populate();
	m_wndReport.ShowFooterRows(TRUE);
	m_wndReport.PinFooterRows(TRUE);

	DWORD dwEnd = ::GetTickCount();

	m_sTime.Format(_T("Populate: %d"), dwEnd - dwStart);
	UpdateData(FALSE);
}

void CTestExpandDlg::OnExpand()
{
	DWORD dwStart = ::GetTickCount();

	m_wndReport.ExpandAll(TRUE);

	DWORD dwEnd = ::GetTickCount();

	m_sTime.Format(_T("Expand: %d"), dwEnd - dwStart);
	UpdateData(FALSE);
}

void CTestExpandDlg::OnCollapse()
{
	m_wndReport.CollapseAll();
}

void CTestExpandDlg::OnCount()
{
	UpdateData();
	AddRecords(Count[m_nCount]);
}

void CTestExpandDlg::OnOK()
{
	CDialog::OnOK();
}

void CTestExpandDlg::OnNotificationExpanded() 
{
	UpdateData();
	m_wndReport.GetBehavior()->Notifications->Row->bRowExpanded = m_bNotificationExpanded;
}

void CTestExpandDlg::OnIndexes() 
{
	CXTPReportRows *pRows = m_wndReport.GetRows();

	for (int nIndex=0; nIndex<pRows->GetCount(); nIndex++)
	{
		CXTPReportRow *pRow = pRows->GetAt(nIndex);
		CXTPReportRecordItemNumber *pItem = DYNAMIC_DOWNCAST(CXTPReportRecordItemNumber, pRow->GetRecord()->GetItem(1));

		pItem->SetValue(pRow->GetIndex());
	}

	m_wndReport.RedrawControl();
}
