// OptionsPage.cpp
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
#include "OptionsPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsPage property page

IMPLEMENT_DYNCREATE(COptionsPage, CPropertyPage)

COptionsPage::COptionsPage(UINT nIDTemplate) : CPropertyPage(nIDTemplate)
{
	//{{AFX_DATA_INIT(COptionsPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_strTitle.LoadString(nIDTemplate);
}

COptionsPage::~COptionsPage()
{
}

void COptionsPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsPage, CPropertyPage)
	//{{AFX_MSG_MAP(COptionsPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsPage message handlers

BOOL COptionsPage::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_TAB && GetKeyState(VK_CONTROL) < 0)
		return GetParent()->PreTranslateMessage(pMsg);

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return GetParent()->PreTranslateMessage(pMsg);

	if(IsDialogMessage(pMsg))
		return TRUE;
	
	return CPropertyPage::PreTranslateMessage(pMsg);
}



void ConvertMenuItem(CString &strTitle)
{

	strTitle.Replace(_T("&"), _T(""));
	strTitle.Replace(_T("."), _T(""));
	strTitle.Replace(_T(" "), _T(""));
	
	int nIndex = strTitle.Find('\t');
	if (nIndex >= 0)
		strTitle.Delete(nIndex, strTitle.GetLength() - nIndex);
}  
