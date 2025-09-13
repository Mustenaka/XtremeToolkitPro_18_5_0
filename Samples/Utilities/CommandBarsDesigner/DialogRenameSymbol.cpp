// DialogRenameSymbol.cpp
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
#include "commandbarsdesigner.h"
#include "DialogRenameSymbol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogRenameSymbol dialog


CDialogRenameSymbol::CDialogRenameSymbol(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogRenameSymbol::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogRenameSymbol)
	m_strName = _T("");
	m_nValue = 0;
	//}}AFX_DATA_INIT
}


void CDialogRenameSymbol::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogRenameSymbol)
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_VALUE, m_nValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogRenameSymbol, CDialog)
	//{{AFX_MSG_MAP(CDialogRenameSymbol)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogRenameSymbol message handlers
