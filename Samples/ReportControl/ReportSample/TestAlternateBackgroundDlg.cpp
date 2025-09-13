// TestAlternateBackgroundDlg.cpp 
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
#include "TestAlternateBackgroundDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestAlternateBackgroundDlg dialog

CTestAlternateBackgroundDlg::CTestAlternateBackgroundDlg(CWnd *pParent)
	: CDialog(CTestAlternateBackgroundDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestAlternateBackgroundDlg)
	//}}AFX_DATA_INIT
}

void CTestAlternateBackgroundDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestAlternateBackgroundDlg)
	DDX_Check(pDX, IDC_ALTERNATE_BACKGROUND, m_bAlternateBackground);
	DDX_Check(pDX, IDC_SHOW_HEADER,          m_bShowHeader);
	DDX_Check(pDX, IDC_SHOW_WATERMARK,       m_bShowWatermark);
	DDX_Control(pDX, IDC_REPORT, m_wndReport);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestAlternateBackgroundDlg, CDialog)
	//{{AFX_MSG_MAP(CTestAlternateBackgroundDlg)
	ON_BN_CLICKED(IDC_ALTERNATE_BACKGROUND, OnAlternateBackground)
	ON_BN_CLICKED(IDC_SHOW_HEADER,          OnShowHeader)
	ON_BN_CLICKED(IDC_SHOW_WATERMARK,       OnShowWatermark)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestAlternateBackgroundDlg message handlers

BOOL CTestAlternateBackgroundDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	enum
	{
		ColumnCount = 5,
		RecordCount = 20,
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

	// Populate
	m_wndReport.Populate();

	m_wndReport.GetPaintManager()->m_bUseAlternativeBackground = TRUE;

	// Initialize check boxes
	m_bAlternateBackground = m_wndReport.GetPaintManager()->m_bUseAlternativeBackground;
	m_bShowHeader          = m_wndReport.IsHeaderVisible();
	m_bShowWatermark       = FALSE;
	UpdateData(FALSE);

	return FALSE;
}

void CTestAlternateBackgroundDlg::OnOK()
{
	CDialog::OnOK();
}

void CTestAlternateBackgroundDlg::OnAlternateBackground() 
{
	UpdateData();
	m_wndReport.GetPaintManager()->m_bUseAlternativeBackground = m_bAlternateBackground;
	m_wndReport.RedrawControl();
}

void CTestAlternateBackgroundDlg::OnShowHeader() 
{
	UpdateData();
	m_wndReport.ShowHeader(m_bShowHeader);
}

void CTestAlternateBackgroundDlg::OnShowWatermark() 
{
	UpdateData();

	if (m_bShowWatermark)
	{
		CBitmap bmpWatermark;

		if (bmpWatermark.LoadBitmap(IDB_CODEJOCKGEAR))
		{
			m_wndReport.SetWatermarkBitmap(bmpWatermark, 64);
			m_wndReport.SetWatermarkAlignment(xtpReportWatermarkCenter | xtpReportWatermarkVCenter);
		}
	}
	else
	{
		m_wndReport.SetWatermarkBitmap(HBITMAP(NULL), 0);
	}

	m_wndReport.RedrawControl();
}
