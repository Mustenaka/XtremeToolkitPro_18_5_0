// ActionsSample.cpp
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
#include "ActionsSample.h"

#include "MainFrm.h"
#include "ActionsSampleDoc.h"
#include "ActionsSampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CActionsSampleApp

BEGIN_MESSAGE_MAP(CActionsSampleApp, CWinApp)
	//{{AFX_MSG_MAP(CActionsSampleApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CActionsSampleApp construction

CActionsSampleApp::CActionsSampleApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

	TCHAR szAppPath[_MAX_PATH];
	VERIFY(::GetModuleFileName(m_hInstance, szAppPath, _MAX_PATH));		
	
	CString strAppPath(szAppPath);
	int nIndex  = strAppPath.ReverseFind(_T('\\'));
	if (nIndex > 0)
	{
		strAppPath = strAppPath.Left(nIndex);
	}
	else
	{
		strAppPath.Empty();
	}
	
	CString strStylesPath;
	strStylesPath += strAppPath + _T("\\Styles\\");
	
	m_hModule2007.LoadLibrary(strStylesPath + _T("Office2007.dll"));
	m_hModule2010.LoadLibrary(strStylesPath + _T("Office2010.dll"));
	m_hModule2013.LoadLibrary(strStylesPath + _T("Office2013.dll"));
	m_hModule2012.LoadLibrary(strStylesPath + _T("VisualStudio2012.dll"));
	m_hModule2015.LoadLibrary(strStylesPath + _T("VisualStudio2015.dll"));
	m_hModuleWindows7.LoadLibrary(strStylesPath + _T("Windows7.dll"));

	m_theme = themeOffice2013Word;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CActionsSampleApp object

CActionsSampleApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CActionsSampleApp initialization

BOOL CActionsSampleApp::InitInstance()
{
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

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
#endif


	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Codejock Software Sample Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CActionsSampleDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CActionsSampleView));
	pDocTemplate->SetContainerInfo(IDR_CNTR_INPLACE);
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();


	ShowSampleHelpPopup(m_pMainWnd, IDR_MAINFRAME);

	return TRUE;
}

// App command to run the dialog
void CActionsSampleApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.SetCredits(_T("Toolbar icons for Office 2013 courtesy of Axialis SA"), _T("http://www.axialis.com"));
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CActionsSampleApp message handlers

