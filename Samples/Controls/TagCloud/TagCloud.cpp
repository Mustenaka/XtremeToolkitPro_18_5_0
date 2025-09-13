// TagCloud.cpp : Defines the class behaviors for the application.
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
#include "TagCloud.h"
#include "TagCloudDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTagCloudApp

BEGIN_MESSAGE_MAP(CTagCloudApp, CWinApp)
	//{{AFX_MSG_MAP(CTagCloudApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTagCloudApp construction

CTagCloudApp::CTagCloudApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTagCloudApp object

CTagCloudApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTagCloudApp initialization

BOOL CTagCloudApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#if _MSC_VER <= 1200 //MFC 6.0 or earlier
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif

	CTagCloudDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
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

void CTagCloudApp::InitColorPicker(CXTPColorPicker& colorPicker, COLORREF crDefault)
{
	XTP_PICK_BUTTON _CustomColors[] =
	{
		{ RGB(0x10,0xA2,0x84), 0, _T("Sea Green")     },
		{ RGB(0x21,0xAE,0x63), 0, _T("Emerald")       },
		{ RGB(0x29,0x82,0xBD), 0, _T("Peter River")   },
		{ RGB(0x8C,0x45,0xAD), 0, _T("Amethyst")      },
		{ RGB(0x29,0x3C,0x52), 0, _T("Midnight Blue") },
		{ RGB(0xF7,0x9E,0x10), 0, _T("Orange")        },
		{ RGB(0xD6,0x55,0x00), 0, _T("Pumpkin")       },
		{ RGB(0xC6,0x38,0x29), 0, _T("Pomegranate")   },
		{ RGB(0xBD,0xC3,0xC6), 0, _T("Silver")        },
		{ RGB(0x7B,0x8E,0x8C), 0, _T("Asbestos")      },
	};

	LPCTSTR _ColorDesc[10] = 
	{
		_T("Accent 1"),
		_T("Accent 2"),
		_T("Accent 3"),
		_T("Accent 4"),
		_T("Accent 5"),
		_T("Accent 6"),
		_T("Accent 7"),
		_T("Accent 8"),
		_T("Accent 9"),
		_T("Accent 10"),
	};

	int _ShadeMatrix[6][10] = 
	{
		{   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
		{ +80, +80, +80, +80, +80, +80, +80, +80, +80, +80 },
		{ +60, +60, +60, +60, +60, +60, +60, +60, +60, +60 },
		{ +20, +20, +20, +20, +20, +20, +20, +20, +20, +20 },
		{ -25, -25, -25, -25, -25, -25, -25, -25, -25, -25 },
		{ -50, -50, -50, -50, -50, -50, -50, -50, -50, -50 },
	};

	colorPicker.SetColors(NULL, 0, 8);
	colorPicker.SetThemeColors(_CustomColors, _countof(_CustomColors), _T("Tag Cloud Colors"), _ColorDesc, _ShadeMatrix);
	colorPicker.GetStandardColors().RemoveAll();
	colorPicker.ModifyCPStyle(0, CPS_XTP_SHOWEYEDROPPER);
	colorPicker.SetTheme(xtpControlThemeOffice2013);
	colorPicker.SetDefaultColor(crDefault);
}