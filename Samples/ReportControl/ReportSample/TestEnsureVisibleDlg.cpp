// TestEnsureVisibleDlg.cpp 
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
#include "TestEnsureVisibleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CTestEnsureVisibleDlg dialog


CTestEnsureVisibleDlg::CTestEnsureVisibleDlg(CWnd *pParent)
	: CDialog(CTestEnsureVisibleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestEnsureVisibleDlg)
	//}}AFX_DATA_INIT
}


void CTestEnsureVisibleDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestEnsureVisibleDlg)
	DDX_Control(pDX, IDC_BEHAVIOR, m_wndBehavior);
	DDX_Control(pDX, IDC_REPORT,   m_wndReport);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestEnsureVisibleDlg, CDialog)
	//{{AFX_MSG_MAP(CTestEnsureVisibleDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestEnsureVisibleDlg message handlers

#if _XTPLIB_VERSION_PREFIX >= 1520

struct Behavior 
{
	XTPReportBehavior behavior;
	LPCTSTR lpszBehavior;
};

static const Behavior behavior[] =
{
	{xtpReportBehaviorCodejockDefault,	_T("Codejock Default")  },
	{xtpReportBehaviorCodejock1502,     _T("Codejock 15.0.2")   },
	{xtpReportBehaviorCodejock1501,     _T("Codejock 15.0.1")   },
	{xtpReportBehaviorCodejock1342,     _T("Codejock 13.4.2")   },
	{xtpReportBehaviorCodejock1341,     _T("Codejock 13.4.1")   },
	{xtpReportBehaviorCodejock1340,     _T("Codejock 13.4.0")   },
};

#endif

BOOL CTestEnsureVisibleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	enum Constants
	{
		ColumnCount =  5,
		RecordCount = 20
	};

#if _XTPLIB_VERSION_PREFIX >= 1520
	for (int nBehavior=0; nBehavior<_countof(behavior); nBehavior++)
	{
		m_wndBehavior.InsertString(nBehavior, behavior[nBehavior].lpszBehavior);
	}
	m_wndBehavior.SetCurSel(0);
#else
	m_wndBehavior.EnableWindow(FALSE);
#endif

	CString sName;
	int nColumn;

	// Add columns
	for (nColumn=0; nColumn<ColumnCount; nColumn++)
	{
		sName.Format(_T("Column %d"), nColumn);
		m_wndReport.AddColumn(new CXTPReportColumn(nColumn, sName, 100));
	}

	int nRecord;

	// Add body records
	for (nRecord=0; nRecord<RecordCount; nRecord++)
	{
		CXTPReportRecord *pRecord = m_wndReport.AddRecord(new CXTPReportRecord());

		for (nColumn=0; nColumn<ColumnCount; nColumn++)
		{
			sName.Format(_T("Item %d, %d"), nRecord, nColumn);
			pRecord->AddItem(new CXTPReportRecordItemText(sName));
		}
	}

	m_wndReport.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_wndReport.ShowHeaderRows(FALSE);
	m_wndReport.Populate();
	m_wndReport.SetFocus();

	return FALSE;
}

void CTestEnsureVisibleDlg::OnOK()
{
	CDialog::OnOK();
}
