// TestComboBoxDlg.cpp 
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
#include "TestComboBoxDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestComboBoxDlg dialog

CTestComboBoxDlg::CTestComboBoxDlg(CWnd *pParent)
	: CDialog(CTestComboBoxDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestComboBoxDlg)
	m_bEditOnClick      = FALSE;
	m_bEditOnDelayClick = FALSE;
	m_bShowInplace      = FALSE;
	//}}AFX_DATA_INIT
}

void CTestComboBoxDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestComboBoxDlg)
	DDX_Control(pDX, IDC_REPORT, m_wndReport);
	DDX_Check(pDX, IDC_EDIT_ON_CLICK,       m_bEditOnClick);
	DDX_Check(pDX, IDC_EDIT_ON_DELAY_CLICK, m_bEditOnDelayClick);
	DDX_Check(pDX, IDC_SHOW_INPLACE,        m_bShowInplace);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestComboBoxDlg, CDialog)
	//{{AFX_MSG_MAP(CTestComboBoxDlg)
	ON_BN_CLICKED(IDC_EDIT_ON_CLICK,       OnEditOnClick)
	ON_BN_CLICKED(IDC_EDIT_ON_DELAY_CLICK, OnEditOnDelayClick)
	ON_BN_CLICKED(IDC_SHOW_INPLACE,        OnShowInplace)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestComboBoxDlg message handlers

BOOL CTestComboBoxDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	enum
	{
		RecordCount = 5
	};

	struct EditOptions 
	{
		BOOL bAllowEdit;
		BOOL bConstraintEdit;
		LPCTSTR lpszCaption;
	};

	const EditOptions editOptions[] =
	{
		{TRUE,  TRUE,  _T(" AllowEdit  ConstraintEdit")},
		{TRUE,  FALSE, _T(" AllowEdit !ConstraintEdit")},
		{FALSE, TRUE,  _T("!AllowEdit  ConstraintEdit")},
		{FALSE, FALSE, _T("!AllowEdit !ConstraintEdit")},
	};
	
	// Add columns
	for (int nColumn=0; nColumn<_countof(editOptions); nColumn++)
	{
		CXTPReportColumn *pColumn = new CXTPReportColumn(nColumn, editOptions[nColumn].lpszCaption, 100);

		CXTPReportRecordItemEditOptions *pEditOptions = pColumn->GetEditOptions();
		pEditOptions->AddConstraint(_T("Test1"));
		pEditOptions->AddConstraint(_T("Test2"));
		pEditOptions->AddConstraint(_T("Test3"));
		pEditOptions->AddConstraint(_T("Test4"));
		pEditOptions->AddConstraint(_T("Test5"));
		pEditOptions->m_bAllowEdit      = editOptions[nColumn].bAllowEdit;
		pEditOptions->m_bConstraintEdit = editOptions[nColumn].bConstraintEdit;
		pEditOptions->AddComboButton(TRUE);

		m_wndReport.AddColumn(pColumn);
	}

	// Add records
	for (int nRecord=0; nRecord<RecordCount; nRecord++)
	{
		CXTPReportRecord *pRecord = m_wndReport.AddRecord(new CXTPReportRecord());

		for (int nColumn=0; nColumn<_countof(editOptions); nColumn++)
		{
			CXTPReportRecordItemText *pItem = new CXTPReportRecordItemText(_T("Test"));
			pRecord->AddItem(pItem);
		}
	}

	// Populate
	m_wndReport.Populate();

	m_wndReport.AllowEdit(TRUE);
	m_wndReport.EditOnClick(TRUE);

	// Initialize combo boxes
	InitComboBoxes();

	return FALSE;
}

void CTestComboBoxDlg::InitComboBoxes()
{
	m_bEditOnClick      = m_wndReport.IsEditOnClick();
	m_bEditOnDelayClick = m_wndReport.IsEditOnDelayClick();
	UpdateData(FALSE);
}

void CTestComboBoxDlg::OnOK()
{
	CDialog::OnOK();
}

void CTestComboBoxDlg::OnShowInplace()
{
	UpdateData();
	m_wndReport.GetPaintManager()->m_bShowNonActiveInPlaceButton = m_bShowInplace;
	m_wndReport.RedrawControl();
}

void CTestComboBoxDlg::OnEditOnClick()
{
	UpdateData();
	m_wndReport.EditOnClick(m_bEditOnClick);
	InitComboBoxes();
}

void CTestComboBoxDlg::OnEditOnDelayClick()
{
	UpdateData();
	m_wndReport.EditOnDelayClick(m_bEditOnDelayClick);
	InitComboBoxes();
}
