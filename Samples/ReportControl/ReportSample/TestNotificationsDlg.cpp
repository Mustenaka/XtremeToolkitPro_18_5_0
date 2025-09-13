// TestNotificationsDlg.cpp 
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
#include "TestNotificationsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CTestNotificationsDlg dialog


CTestNotificationsDlg::CTestNotificationsDlg(CWnd *pParent)
	: CDialog(CTestNotificationsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestNotificationsDlg)
	m_bCancelFocusChanging = FALSE;
	m_bCancelLButtonDown = FALSE;
	m_bCancelLButtonUp = FALSE;
	m_bCancelSelectionClear = FALSE;
	m_bCancelSelectionAdd = FALSE;
	//}}AFX_DATA_INIT
}


void CTestNotificationsDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestNotificationsDlg)
	DDX_Control(pDX, IDC_BEHAVIOR, m_wndBehavior);
	// Header rows
	DDX_Check(pDX, IDC_HEADER_ROWS_ENABLE_SELECTION, m_bHeaderRowsEnableSelection);
	DDX_Check(pDX, IDC_HEADER_ROWS_ALLOW_ACCESS,     m_bHeaderRowsAllowAccess);
	// Options
	DDX_Check(pDX, IDC_CANCEL_FOCUS_CHANGING,  m_bCancelFocusChanging);
	DDX_Check(pDX, IDC_CANCEL_LBUTTON_DOWN,    m_bCancelLButtonDown);
	DDX_Check(pDX, IDC_CANCEL_LBUTTON_UP,      m_bCancelLButtonUp);
	DDX_Check(pDX, IDC_CANCEL_SELECTION_CLEAR, m_bCancelSelectionClear);
	DDX_Check(pDX, IDC_CANCEL_SELECTION_ADD,   m_bCancelSelectionAdd);
	DDX_Control(pDX, IDC_REPORT,			m_wndReport);
	DDX_Control(pDX, IDC_NOTIFICATIONS, m_wndNotifications);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestNotificationsDlg, CDialog)
	//{{AFX_MSG_MAP(CTestNotificationsDlg)
	ON_NOTIFY(NM_CLICK,                     IDC_REPORT, OnReportClick)
	ON_NOTIFY(NM_RCLICK,                    IDC_REPORT, OnReportRClick)
	ON_NOTIFY(NM_DBLCLK,                    IDC_REPORT, OnReportDblClick)
	ON_NOTIFY(XTP_NM_REPORT_LBUTTONDOWN,    IDC_REPORT, OnReportLButtonDown)
	ON_NOTIFY(XTP_NM_REPORT_SELCHANGING,    IDC_REPORT, OnReportSelChanging)
	ON_NOTIFY(XTP_NM_REPORT_SELCHANGED,     IDC_REPORT, OnReportSelChanged)
	ON_NOTIFY(XTP_NM_REPORT_FOCUS_CHANGING, IDC_REPORT, OnReportFocusChanging)
	// Header rows
	ON_BN_CLICKED(IDC_HEADER_ROWS_ENABLE_SELECTION, OnHeaderRowsEnableSelection)
	ON_BN_CLICKED(IDC_HEADER_ROWS_ALLOW_ACCESS,     OnHeaderRowsAllowAccess)
	//
	ON_BN_CLICKED(IDC_REMOVE_ROW_EX,      OnRemoveRowEx)
	ON_BN_CLICKED(IDC_REMOVE_RECORD_EX,   OnRemoveRecordEx)
	ON_BN_CLICKED(IDC_SELECT_FOCUSED_ROW, OnSelectFocusedRow)
	ON_BN_CLICKED(IDC_CLEAR_NOTIFICATIONS, OnClearNotifications)
	ON_CBN_SELCHANGE(IDC_BEHAVIOR, OnSelchangeBehavior)
	//}}AFX_MSG_MAP
#if _XTPLIB_VERSION_PREFIX >= 1502
	ON_NOTIFY(XTP_NM_REPORT_STATECHANGED,   IDC_REPORT, OnReportStateChanged)
#endif
#if _XTPLIB_VERSION_PREFIX >= 1520
	ON_NOTIFY(XTP_NM_REPORT_LBUTTONUP,			IDC_REPORT, OnReportLButtonUp) // Added 15.2.0
#endif
#if _XTPLIB_VERSION_PREFIX >= 1520
	ON_NOTIFY(XTP_NM_REPORT_HSCROLL,				IDC_REPORT, OnReportHScroll) // Added 15.2.0
	ON_NOTIFY(XTP_NM_REPORT_VSCROLL,				IDC_REPORT, OnReportVScroll) // Added 15.2.0
#endif
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestNotificationsDlg message handlers

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

BOOL CTestNotificationsDlg::OnInitDialog()
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

	// Initialize list control first
	m_wndNotifications.InsertColumn(0, _T("Notification"), LVCFMT_LEFT, 225);
	m_wndNotifications.InsertColumn(1, _T("Row index"),    LVCFMT_LEFT,  75);
	m_wndNotifications.InsertColumn(2, _T("Parameter"),    LVCFMT_LEFT, 150);

	CString sName;
	int nColumn;

	// Add columns
	for (nColumn=0; nColumn<ColumnCount; nColumn++)
	{
		sName.Format(_T("Column %d"), nColumn);
		m_wndReport.AddColumn(new CXTPReportColumn(nColumn, sName, 100));
	}

	int nRecord;

	// Add header records
	for (nRecord=0; nRecord<3; nRecord++)
	{
		CXTPReportRecord *pRecord = m_wndReport.GetHeaderRecords()->Add(new CXTPReportRecord());

		for (nColumn=0; nColumn<ColumnCount; nColumn++)
		{
			sName.Format(_T("Item %d, %d"), nRecord, nColumn);
			pRecord->AddItem(new CXTPReportRecordItemText(sName));
		}
	}

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
	m_wndReport.ShowHeaderRows(TRUE);
	m_wndReport.Populate();
	m_wndReport.SetFocus();

	// Initialize header row options
	m_bHeaderRowsEnableSelection = m_wndReport.IsHeaderRowsSelectionEnabled();
	m_bHeaderRowsAllowAccess     = m_wndReport.IsHeaderRowsAllowAccess();
	UpdateData(FALSE);

	return FALSE;
}

void CTestNotificationsDlg::OnOK()
{
	CDialog::OnOK();
}

int CTestNotificationsDlg::AddNotification(LPCTSTR pszNotification, int nRow, LPCTSTR pszParameter)
{
	int nItem = m_wndNotifications.InsertItem(m_wndNotifications.GetItemCount(), pszNotification);

	CString sRow;
	sRow.Format(_T("%d"), nRow);

	VERIFY(m_wndNotifications.SetItemText(nItem, 1, sRow));
	VERIFY(m_wndNotifications.SetItemText(nItem, 2, pszParameter));

	m_wndNotifications.EnsureVisible(nItem, FALSE);

	return nItem;
}

/////////////////////////////////////////////////////////////////////////////
// Notifications
/////////////////////////////////////////////////////////////////////////////

void CTestNotificationsDlg::OnReportClick(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	ASSERT(NULL != pNotifyStruct);
	ASSERT(NULL != pResult);

	XTP_NM_REPORTRECORDITEM *pItemNotify = reinterpret_cast<XTP_NM_REPORTRECORDITEM*>(pNotifyStruct);

	int nRow = -1;
	
	if (pItemNotify->pRow)
	{
		nRow = pItemNotify->pRow->GetIndex();
	}

	int nItem = AddNotification(_T("NM_CLICK"), nRow);
}

void CTestNotificationsDlg::OnReportRClick(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	ASSERT(NULL != pNotifyStruct);
	ASSERT(NULL != pResult);

	XTP_NM_REPORTRECORDITEM *pItemNotify = reinterpret_cast<XTP_NM_REPORTRECORDITEM*>(pNotifyStruct);

	int nRow = -1;
	
	if (pItemNotify->pRow)
	{
		nRow = pItemNotify->pRow->GetIndex();
	}
	
	int nItem = AddNotification(_T("NM_RCLICK"), nRow);
}

void CTestNotificationsDlg::OnReportDblClick(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	ASSERT(NULL != pNotifyStruct);
	ASSERT(NULL != pResult);

	XTP_NM_REPORTRECORDITEM *pItemNotify = reinterpret_cast<XTP_NM_REPORTRECORDITEM*>(pNotifyStruct);

	int nRow = -1;
	
	if (pItemNotify->pRow)
	{
		nRow = pItemNotify->pRow->GetIndex();
	}
	
	int nItem = AddNotification(_T("NM_DBLCLICK"), nRow);
}

void CTestNotificationsDlg::OnReportLButtonDown(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	ASSERT(NULL != pNotifyStruct);
	ASSERT(NULL != pResult);

	XTP_NM_REPORTRECORDITEM *pItemNotify = reinterpret_cast<XTP_NM_REPORTRECORDITEM*>(pNotifyStruct);

	int nRow = -1;
	
	if (pItemNotify->pRow)
	{
		nRow = pItemNotify->pRow->GetIndex();
	}

	int nItem = AddNotification(_T("XTP_NM_REPORT_LBUTTONDOWN"), nRow);

	UpdateData();
	*pResult = m_bCancelLButtonDown;
}

#if _XTPLIB_VERSION_PREFIX >= 1520

void CTestNotificationsDlg::OnReportLButtonUp(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	ASSERT(NULL != pNotifyStruct);
	ASSERT(NULL != pResult);

	XTP_NM_REPORTRECORDITEM *pItemNotify = reinterpret_cast<XTP_NM_REPORTRECORDITEM*>(pNotifyStruct);

	int nRow = -1;
	
	if (pItemNotify->pRow)
	{
		nRow = pItemNotify->pRow->GetIndex();
	}

	int nItem = AddNotification(_T("XTP_NM_REPORT_LBUTTONUP"), nRow);

	UpdateData();
	*pResult = m_bCancelLButtonUp;
}

#endif

static const LPCTSTR XTPReportSelectionChangeTypeString[] =
{
	_T("xtpReportSelectionAdd"),
	_T("xtpReportSelectionRemove"),
	_T("xtpReportSelectionClear")
};

void CTestNotificationsDlg::OnReportSelChanging(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	ASSERT(NULL != pNotifyStruct);
	ASSERT(NULL != pResult);

	XTP_NM_SELECTION_CHANGING *pItemNotify = reinterpret_cast<XTP_NM_SELECTION_CHANGING*>(pNotifyStruct);

	int nRow = -1;
	
	if (pItemNotify->pRow)
	{
		nRow = pItemNotify->pRow->GetIndex();
	}

	int nItem = AddNotification(_T("XTP_NM_REPORT_SELCHANGING"), nRow, XTPReportSelectionChangeTypeString[pItemNotify->nType]);

	UpdateData();
	switch(pItemNotify->nType)
	{
	case xtpReportSelectionAdd:
		*pResult = m_bCancelSelectionAdd;
		break;
	case xtpReportSelectionRemove:
		break;
	case xtpReportSelectionClear:
		*pResult = m_bCancelSelectionClear;
		break;
	}
}

void CTestNotificationsDlg::OnReportSelChanged(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	ASSERT(NULL != pNotifyStruct);
	ASSERT(NULL != pResult);

	int nItem = AddNotification(_T("XTP_NM_REPORT_SELCHANGED"), -1);
}

void CTestNotificationsDlg::OnReportFocusChanging(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	ASSERT(NULL != pNotifyStruct);
	ASSERT(NULL != pResult);

	XTP_NM_REPORTREQUESTEDIT *pItemNotify = reinterpret_cast<XTP_NM_REPORTREQUESTEDIT*>(pNotifyStruct);
	
	int nRow = -1;
	
	if (pItemNotify->pRow)
	{
		nRow = pItemNotify->pRow->GetIndex();
	}
	
	int nItem = AddNotification(_T("XTP_NM_REPORT_FOCUS_CHANGING"), nRow);

	UpdateData();
	pItemNotify->bCancel = m_bCancelFocusChanging;
}

#if _XTPLIB_VERSION_PREFIX >= 1502

void CTestNotificationsDlg::OnReportStateChanged(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	ASSERT(NULL != pNotifyStruct);
	ASSERT(NULL != pResult);

	XTP_NM_REPORTSTATECHANGED *pItemNotify = reinterpret_cast<XTP_NM_REPORTSTATECHANGED*>(pNotifyStruct);

	int nItem = AddNotification(_T("XTP_NM_REPORT_STATECHANGED"), pItemNotify->nBegin);
}

#endif

#if _XTPLIB_VERSION_PREFIX >= 1520

void CTestNotificationsDlg::OnReportHScroll(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	ASSERT(NULL != pNotifyStruct);
	ASSERT(NULL != pResult);

	XTP_NM_REPORTSCROLL *pItemNotify = reinterpret_cast<XTP_NM_REPORTSCROLL*>(pNotifyStruct);

	int nItem = AddNotification(_T("XTP_NM_REPORT_HSCROLL"), pItemNotify->nPosition);
}

void CTestNotificationsDlg::OnReportVScroll(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	ASSERT(NULL != pNotifyStruct);
	ASSERT(NULL != pResult);

	XTP_NM_REPORTSCROLL *pItemNotify = reinterpret_cast<XTP_NM_REPORTSCROLL*>(pNotifyStruct);

	int nItem = AddNotification(_T("XTP_NM_REPORT_VSCROLL"), pItemNotify->nPosition);
}

#endif


void CTestNotificationsDlg::OnRemoveRowEx()
{
	CXTPReportSelectedRows *pSelectedRows = m_wndReport.GetSelectedRows();

	CXTPReportSection* pSection = NULL;
	if (pSelectedRows->GetCount() > 0)
	{
		CXTPReportRow* pRow = pSelectedRows->GetAt(0);
		if (pRow)
		{
			pSection = pRow->GetSection();
		}
	}
	
	if (!pSection)
		return;

	while (pSelectedRows->GetCount() > 0)
	{
		pSection->RemoveRowEx(pSelectedRows->GetAt(pSelectedRows->GetCount() - 1), TRUE);
	}
}

void CTestNotificationsDlg::OnRemoveRecordEx()
{
	CXTPReportSelectedRows *pSelectedRows = m_wndReport.GetSelectedRows();
	
	CXTPReportSection* pSection = NULL;
	if (pSelectedRows->GetCount() > 0)
	{
		CXTPReportRow* pRow = pSelectedRows->GetAt(0);
		if (pRow)
		{
			pSection = pRow->GetSection();
		}
	}
	
	if (!pSection)
		return;

	while (pSelectedRows->GetCount() > 0)
	{
		CXTPReportRow *pRow = pSelectedRows->GetAt(pSelectedRows->GetCount() - 1);
		pSection->RemoveRecordEx(pRow->GetRecord(), TRUE, TRUE);
	}
}

void CTestNotificationsDlg::OnSelectFocusedRow()
{
	CXTPReportRow *pRow = m_wndReport.GetFocusedRow();

	if (NULL != pRow)
	{
		m_wndReport.GetSelectedRows()->Select(pRow);
	}
}

void CTestNotificationsDlg::OnClearNotifications()
{
	m_wndNotifications.DeleteAllItems();
}

void CTestNotificationsDlg::OnSelchangeBehavior() 
{
#if _XTPLIB_VERSION_PREFIX >= 1520
	int nCurSel = m_wndBehavior.GetCurSel();

	m_wndReport.GetBehavior()->SetScheme(behavior[nCurSel].behavior);
#endif
}


void CTestNotificationsDlg::OnHeaderRowsEnableSelection()
{
	UpdateData();
	m_wndReport.HeaderRowsEnableSelection(m_bHeaderRowsEnableSelection);
}

void CTestNotificationsDlg::OnHeaderRowsAllowAccess()
{
	UpdateData();
	m_wndReport.HeaderRowsAllowAccess(m_bHeaderRowsAllowAccess);
}
