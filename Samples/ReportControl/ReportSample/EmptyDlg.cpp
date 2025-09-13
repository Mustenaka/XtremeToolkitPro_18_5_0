// EmptyDlg.cpp 
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
#include "EmptyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CTreeViewDlg dialog


CEmptyDlg::CEmptyDlg(CWnd *pParent)
	: CDialog(CEmptyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEmptyDlg)
	m_nScrollModeH = -1;
	m_nScrollModeV = -1;
	//}}AFX_DATA_INIT
}


void CEmptyDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEmptyDlg)
	DDX_Control(pDX, IDC_REPORT1, m_wndReport1);
	DDX_Control(pDX, IDC_REPORT2, m_wndReport2);
	DDX_Control(pDX, IDC_REPORT3, m_wndReport3);
	DDX_Control(pDX, IDC_REPORT4, m_wndReport4);
	DDX_CBIndex(pDX, IDC_SCROLLMODE_H, m_nScrollModeH);
	DDX_CBIndex(pDX, IDC_SCROLLMODE_V, m_nScrollModeV);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEmptyDlg, CDialog)
	//{{AFX_MSG_MAP(CEmptyDlg)
	//}}AFX_MSG_MAP
#if _XTPLIB_VERSION_PREFIX >= 1520
	ON_CBN_SELENDOK(IDC_SCROLLMODE_H, OnScrollModeH)
	ON_CBN_SELENDOK(IDC_SCROLLMODE_V, OnScrollModeV)
#endif
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEmptyDlg message handlers


BOOL CEmptyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//////////////////////////////////////////////////////////////////////////
	// Report 1: Nothing
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Report 2: Populate with no columns and no rows
	//////////////////////////////////////////////////////////////////////////
	m_wndReport2.Populate();
	
	//////////////////////////////////////////////////////////////////////////
	// Report 3: Populate with one column and no rows
	//////////////////////////////////////////////////////////////////////////
	m_wndReport3.AddColumn(new CXTPReportColumn(0, _T("Column 0"), 100));
	m_wndReport3.Populate();

	//////////////////////////////////////////////////////////////////////////
	// Report 4: Populate with one column and no rows, draw grid
	//////////////////////////////////////////////////////////////////////////
	m_wndReport4.AddColumn(new CXTPReportColumn(0, _T("Column 0"), 100));
	m_wndReport4.Populate();
	m_wndReport4.GetPaintManager()->SetDrawGridForEmptySpace(TRUE);

	//////////////////////////////////////////////////////////////////////////
	// 
	//////////////////////////////////////////////////////////////////////////
#if _XTPLIB_VERSION_PREFIX >= 1520
	m_nScrollModeH = m_wndReport1.GetScrollMode(xtpReportOrientationHorizontal);
	m_nScrollModeV = m_wndReport1.GetScrollMode(xtpReportOrientationVertical);
#endif
	UpdateData(FALSE);

	return FALSE;
}

void CEmptyDlg::OnOK()
{
	CDialog::OnOK();
}

#if _XTPLIB_VERSION_PREFIX >= 1520

void CEmptyDlg::OnScrollModeH() 
{
	UpdateData();
	m_wndReport1.SetScrollMode(xtpReportOrientationHorizontal, XTPReportScrollMode(m_nScrollModeH));
	m_wndReport2.SetScrollMode(xtpReportOrientationHorizontal, XTPReportScrollMode(m_nScrollModeH));
	m_wndReport3.SetScrollMode(xtpReportOrientationHorizontal, XTPReportScrollMode(m_nScrollModeH));
	m_wndReport4.SetScrollMode(xtpReportOrientationHorizontal, XTPReportScrollMode(m_nScrollModeH));
}

void CEmptyDlg::OnScrollModeV() 
{
	UpdateData();
	m_wndReport1.SetScrollMode(xtpReportOrientationVertical, XTPReportScrollMode(m_nScrollModeV));
	m_wndReport2.SetScrollMode(xtpReportOrientationVertical, XTPReportScrollMode(m_nScrollModeV));
	m_wndReport3.SetScrollMode(xtpReportOrientationVertical, XTPReportScrollMode(m_nScrollModeV));
	m_wndReport4.SetScrollMode(xtpReportOrientationVertical, XTPReportScrollMode(m_nScrollModeV));
}

#endif
