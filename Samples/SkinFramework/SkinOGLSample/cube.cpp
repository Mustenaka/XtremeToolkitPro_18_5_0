// cube.cpp
//

#include "StdAfx.h"
#include "cube.h"

#include "MainFrm.h"
#include "CubeDoc.h"
#include "CubeView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCubeApp

BEGIN_MESSAGE_MAP(CCubeApp, CWinApp)
	//{{AFX_MSG_MAP(CCubeApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_NEW,  CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCubeApp construction

CCubeApp::CCubeApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCubeApp object

CCubeApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCubeApp initialization

BOOL CCubeApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CCubeDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CCubeView));
	AddDocTemplate(pDocTemplate);

	// create a new (empty) document
	OnFileNew();

	if (m_lpCmdLine[0] != '\0')
	{
		// TODO: add command line processing here
	}

	return TRUE;
}

// App command to run the dialog
void CCubeApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CCubeApp commands
