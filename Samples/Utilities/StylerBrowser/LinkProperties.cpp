// LinkProperties.cpp
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
#include "styler.h"
#include "LinkProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLinkProperties dialog


CLinkProperties::CLinkProperties(CWnd* pParent /*=NULL*/)
	: CDialog(CLinkProperties::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLinkProperties)
	m_strAddress = _T("");
	m_strTitle = _T("");
	m_strParent = _T("");
	//}}AFX_DATA_INIT
}


void CLinkProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLinkProperties)
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_strAddress);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_strTitle);
	DDX_Text(pDX, IDC_STATIC_PARENT, m_strParent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLinkProperties, CDialog)
	//{{AFX_MSG_MAP(CLinkProperties)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLinkProperties message handlers
