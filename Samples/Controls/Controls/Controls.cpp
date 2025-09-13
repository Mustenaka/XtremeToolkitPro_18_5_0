// Controls.cpp
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
#include "Controls.h"
#include "PageButton.h"
#include "PageEdit.h"
#include "PageComboBox.h"
#include "PageScrollBar.h"
#include "PageProgressBar.h"
#include "ControlsPropertySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CControlsApp

BEGIN_MESSAGE_MAP(CControlsApp, CWinApp)
	//{{AFX_MSG_MAP(CControlsApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CControlsApp construction

CControlsApp::CControlsApp()
	: m_nCurSel(CB_ERR)
	, m_nTheme(xtpControlThemeDefault)
	, m_clrText(COLORREF_NULL)
	, m_clrBack(COLORREF_NULL)
	, m_clrEdge(COLORREF_NULL)
{
}

CControlsApp::~CControlsApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CControlsApp object

CControlsApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CControlsApp initialization

BOOL CControlsApp::InitInstance()
{
	AfxEnableControlContainer();

	AfxOleInit();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#if _MSC_VER <= 1200 // MFC 6.0 or earlier
#ifdef _AFXDLL
	Enable3dControls();         // Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();   // Call this when linking to MFC statically
#endif
#endif // MFC 6.0 or earlier

#ifdef _XTP_INCLUDE_COMMANDBARS
	XTPPaintManager()->SetTheme(xtpThemeOffice2013);
#endif

	CControlsPropertySheet dlg(AFX_IDS_APP_TITLE, 0, 0, xtpResizeNoVertical);
	dlg.m_psh.dwFlags |= PSH_NOAPPLYNOW;

	CPageButton pageButtons;
	dlg.AddPage(&pageButtons);

	CPageEdit pageEdit;
	dlg.AddPage(&pageEdit);

	CPageComboBox pageComboBox;
	dlg.AddPage(&pageComboBox);

	CPageProgressBar pageProgressBar;
	dlg.AddPage(&pageProgressBar);

	CPageScrollBar pageScrollBar;
	dlg.AddPage(&pageScrollBar);

	m_pMainWnd = &dlg;
	int nResponse = (int)dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
