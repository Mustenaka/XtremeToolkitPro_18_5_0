// CalendarDataSourceDialog.cpp
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

#include "stdafx.h"
#include "SQLServerDataProvider.h"
#include "CalendarDataSourceDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalendarDataSourceDialog dialog


CCalendarDataSourceDialog::CCalendarDataSourceDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCalendarDataSourceDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalendarDataSourceDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCalendarDataSourceDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalendarDataSourceDialog)
	DDX_Control(pDX, IDC_CONNECTION_STRING_EDIT, m_ctrlConnectionString);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCalendarDataSourceDialog, CDialog)
	//{{AFX_MSG_MAP(CCalendarDataSourceDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalendarDataSourceDialog message handlers

void CCalendarDataSourceDialog::OnOK() 
{
	m_ctrlConnectionString.GetWindowText(m_strConnectionString);
	
	CDialog::OnOK();
}

BOOL CCalendarDataSourceDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ctrlConnectionString.SetWindowText(m_strConnectionString);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
