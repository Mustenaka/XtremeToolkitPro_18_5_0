// ChartBrowser.cpp
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
#include "ChartBrowser.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChartBrowserApp

BEGIN_MESSAGE_MAP(CChartBrowserApp, CWinApp)
	//{{AFX_MSG_MAP(CChartBrowserApp)
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
// CChartBrowserApp construction

CChartBrowserApp::CChartBrowserApp()
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

	m_hModule2012.LoadLibrary(strStylesPath + _T("VisualStudio2012.dll"));
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CChartBrowserApp object

CChartBrowserApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CChartBrowserApp initialization

BOOL CChartBrowserApp::InitInstance()
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



	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Codejock Software Sample Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;
	
	// create and load the frame with its resources
	
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);
	
	
	
	
	// The one and only window has been initialized, so show and update it.
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About


// App command to run the dialog
void CChartBrowserApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CChartBrowserApp message handlers

