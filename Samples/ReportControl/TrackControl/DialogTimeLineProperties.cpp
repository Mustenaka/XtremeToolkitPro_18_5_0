// DialogTimeLineProperties.cpp
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
#include "trackcontrol.h"
#include "DialogTimeLineProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogTimeLineProperties dialog


CDialogTimeLineProperties::CDialogTimeLineProperties(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogTimeLineProperties::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogTimeLineProperties)
	m_nMin = 0;
	m_nMax = 0;
	//}}AFX_DATA_INIT
}


void CDialogTimeLineProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogTimeLineProperties)
	DDX_Text(pDX, IDC_EDIT_MIN, m_nMin);
	DDV_MinMaxInt(pDX, m_nMin, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_MAX, m_nMax);
	DDV_MinMaxInt(pDX, m_nMax, 0, 10000);
	//}}AFX_DATA_MAP
	DDV_MinMaxInt(pDX, m_nMax, m_nMin + 1, 10000);
}


BEGIN_MESSAGE_MAP(CDialogTimeLineProperties, CDialog)
	//{{AFX_MSG_MAP(CDialogTimeLineProperties)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogTimeLineProperties message handlers
