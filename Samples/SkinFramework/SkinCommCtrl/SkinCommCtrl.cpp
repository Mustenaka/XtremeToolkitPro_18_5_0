// SkinCommCtrl.cpp
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
#include "SkinCommCtrl.h"

#include "MainFrm.h"
#include "SkinCommCtrlDoc.h"
#include "SkinCommCtrlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinCommCtrlApp

BEGIN_MESSAGE_MAP(CSkinCommCtrlApp, CWinApp)
	//{{AFX_MSG_MAP(CSkinCommCtrlApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinCommCtrlApp construction

CSkinCommCtrlApp::CSkinCommCtrlApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSkinCommCtrlApp object

CSkinCommCtrlApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSkinCommCtrlApp initialization

BOOL CSkinCommCtrlApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization

#if _MSC_VER <= 1200 // MFC 6.0 or earlier
#ifdef _AFXDLL
	Enable3dControls();         // Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();   // Call this when linking to MFC statically
#endif
#endif

	// Change the registry key under which our settings are stored.
	SetRegistryKey(_T("Codejock Software Sample Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register document templates

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSkinCommCtrlDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CSkinCommCtrlView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

// App command to run the dialog
void CSkinCommCtrlApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CSkinCommCtrlApp message handlers

