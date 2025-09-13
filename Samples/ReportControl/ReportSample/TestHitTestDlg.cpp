// TestHitTestDlg.cpp 
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
#include "TestHitTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CTestHitTestDlg dialog


CTestHitTestDlg::CTestHitTestDlg(CWnd *pParent)
	: CDialog(CTestHitTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestHitTestDlg)
	//}}AFX_DATA_INIT
}


void CTestHitTestDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestHitTestDlg)
	DDX_Control(pDX, IDC_REPORT,  m_wndReport);
	DDX_Control(pDX, IDC_HITTEST, m_wndHitTest);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestHitTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTestHitTestDlg)
	ON_WM_MOUSEMOVE()
#if _XTPLIB_VERSION_PREFIX >= 1520
	ON_NOTIFY(XTP_NM_REPORT_MOUSEMOVE, IDC_REPORT, OnReportMouseMove)
#endif
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestHitTestDlg message handlers


void AddItems(CXTPReportRecord *pRecord, int nRecord, int nColumns)
{
	CString sName;
	for (int nColumn=0; nColumn<nColumns; nColumn++)
	{
		sName.Format(_T("Item %d, %d"), nRecord, nColumn);
		pRecord->AddItem(new CXTPReportRecordItemText(sName));
	}
}

BOOL CTestHitTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	enum Constants
	{
		ColumnCount = 5,
		RecordCount = 3
	};

	// Initialize list control first
	m_wndHitTest.InsertColumn(0, _T("Hit code"),     LVCFMT_LEFT, 225);
	m_wndHitTest.InsertColumn(1, _T("Column index"), LVCFMT_LEFT, 100);
	m_wndHitTest.InsertColumn(2, _T("Row index"),    LVCFMT_LEFT, 100);

	// Add columns
	for (int nColumn=0; nColumn<ColumnCount; nColumn++)
	{
		CString sName;
		sName.Format(_T("Column %d"), nColumn);
		m_wndReport.AddColumn(new CXTPReportColumn(nColumn, sName, 100));
	}

	// Add sample records
	for (int nRecord=0; nRecord<RecordCount; nRecord++)
	{
		CXTPReportRecord *pRecord;

		// Header records
		pRecord = m_wndReport.GetHeaderRecords()->Add(new CXTPReportRecord());
		AddItems(pRecord, nRecord, ColumnCount);

		// Body records
		pRecord = m_wndReport.GetRecords()->Add(new CXTPReportRecord());
		AddItems(pRecord, nRecord, ColumnCount);

		// Footer records
		pRecord = m_wndReport.GetFooterRecords()->Add(new CXTPReportRecord());
		AddItems(pRecord, nRecord, ColumnCount);
	}

	m_wndReport.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_wndReport.ShowGroupBy(TRUE);
	m_wndReport.ShowHeaderRows(TRUE);
	m_wndReport.ShowFooterRows(TRUE);
	m_wndReport.Populate();

	return FALSE;
}

void CTestHitTestDlg::OnOK()
{
	CDialog::OnOK();
}

int CTestHitTestDlg::AddHitTest(LPCTSTR pszHitCode, int nColumn, int nRow)
{
	int nItem = m_wndHitTest.InsertItem(m_wndHitTest.GetItemCount(), pszHitCode);

	CString sColumn;
	sColumn.Format(_T("%d"), nColumn);

	CString sRow;
	sRow.Format(_T("%d"), nRow);

	VERIFY(m_wndHitTest.SetItemText(nItem, 1, sColumn));
	VERIFY(m_wndHitTest.SetItemText(nItem, 2, sRow));

	m_wndHitTest.EnsureVisible(nItem, FALSE);

	return nItem;
}

static const LPCTSTR XTPReportHitTestString[] =
{
	_T("xtpReportHitTestUnknown"),
	_T("xtpReportHitTestHeader"),
	_T("xtpReportHitTestGroupBox"),
	_T("xtpReportHitTestBodyRows"),
	_T("xtpReportHitTestBlock"),
	_T("xtpReportHitTestHeaderRows"),
	_T("xtpReportHitTestFooterRows")
};

#if _XTPLIB_VERSION_PREFIX >= 1520

void CTestHitTestDlg::OnReportMouseMove(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	XTP_NM_REPORTRECORDITEM *pItem = reinterpret_cast<XTP_NM_REPORTRECORDITEM*>(pNotifyStruct);

	CXTPReportHitTestInfo htInfo;

	if (m_wndReport.HitTest(pItem->pt, &htInfo))
	{
		int nColumn = -1;
		int nRow    = -1;

		if (NULL != htInfo.m_pColumn)
		{
			nColumn = htInfo.m_pColumn->GetIndex();
		}

		if (NULL != htInfo.m_pRow)
		{
			nRow = htInfo.m_pRow->GetIndex();
		}

		AddHitTest(XTPReportHitTestString[htInfo.m_htCode], nColumn, nRow);
	}
}

#endif
