// FlowGraphSample.cpp
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
#include "FlowGraphSample.h"

#include "MainFrm.h"
#include "FlowGraphSampleDoc.h"
#include "FlowGraphSampleView.h"

#include <shlwapi.h>

#pragma comment(lib, "shlwapi.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlowGraphSampleApp

BEGIN_MESSAGE_MAP(CFlowGraphSampleApp, CWinApp)
	//{{AFX_MSG_MAP(CFlowGraphSampleApp)
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
// CFlowGraphSampleApp construction

CFlowGraphSampleApp::CFlowGraphSampleApp()
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

	m_hModule2013.LoadLibrary(strStylesPath + _T("Office2013.dll"));
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFlowGraphSampleApp object

CFlowGraphSampleApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CFlowGraphSampleApp initialization

BOOL CFlowGraphSampleApp::InitInstance()
{
	AfxEnableControlContainer();

	InitCommonControls();

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

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CFlowGraphSampleDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CFlowGraphSampleView));
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

	return TRUE;
}

// App command to run the dialog
void CFlowGraphSampleApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.SetCredits(_T("Toolbar icons for Office 2013 courtesy of Axialis SA"), _T("http://www.axialis.com"));
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CFlowGraphSampleApp message handlers

CXTPFlowGraphNodeCustom* AddCustomFlowGraphShape(CXTPFlowGraphControl &m_wndControl, UINT uResShapeID, const CPoint &point, const CSize &shapeSize)
{
	CXTPFlowGraphNodeCustom *pNode = m_wndControl.AddCustomNodeFromToolkitResource(uResShapeID);

	if (pNode)
	{
		pNode->SetLocation(point);
		pNode->SetSize(shapeSize);
		pNode->SetCaption(_T("New node"));
		pNode->SetTooltip(_T("New node"));
	}

	return pNode;
}

CXTPFlowGraphNodeCustom* AddUserCardNode(CXTPFlowGraphControl &m_wndControl, CString xaml, const CPoint &point, const CSize &shapeSize, const CStringList &strings)
{
	CXTPFlowGraphNodeCustom *pNode = NULL;

	if (xaml.GetLength())
	{
		for (int i=0; i<strings.GetCount(); i++)
		{
			CString repl_str;
			repl_str.Format(_T("[placeholder%d]"), i);

			xaml.Replace(repl_str, strings.GetAt(strings.FindIndex(i)));
		}

		m_wndControl.GetUndoManager()->StartGroup();

		if (m_wndControl.GetActivePage())
		{
			pNode = m_wndControl.GetActivePage()->GetNodes()->AddCustomNode();

			pNode->SetMarkupText(xaml);
			pNode->SetLocation(point);
			pNode->SetSize(shapeSize);
			pNode->SetMinSize(XTP_DPI(CSize(340, 172)));

			m_wndControl.GetUndoManager()->EndGroup();
		}
	}

	return pNode;
}
