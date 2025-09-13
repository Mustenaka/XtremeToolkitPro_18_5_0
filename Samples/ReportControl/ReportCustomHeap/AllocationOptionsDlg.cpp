// AllocationOptionsDlg.cpp
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
#include "reportcustomheap.h"
#include "AllocationOptionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAllocationOptionsDlg dialog


CAllocationOptionsDlg::CAllocationOptionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAllocationOptionsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAllocationOptionsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAllocationOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAllocationOptionsDlg)
	DDX_Control(pDX, IDC_CHK_USE_CUSTOM_HEAP, m_ctrlUseCustomHeap);
	DDX_Control(pDX, IDC_CHK_ENABLE_ROW_BATCH_ALLOCATION, m_ctrlRowsBatchAlloc);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAllocationOptionsDlg, CDialog)
	//{{AFX_MSG_MAP(CAllocationOptionsDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAllocationOptionsDlg message handlers

BOOL CAllocationOptionsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ctrlUseCustomHeap.SetCheck(1);
	m_ctrlRowsBatchAlloc.SetCheck(1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAllocationOptionsDlg::OnOK() 
{
	if (m_ctrlUseCustomHeap.GetCheck())
	{
		VERIFY(CXTPReportControl::UseReportCustomHeap());
	}
	
	if (m_ctrlRowsBatchAlloc.GetCheck())
	{
		CXTPReportControl::UseRowBatchAllocation();
	}
	
	CDialog::OnOK();
}
