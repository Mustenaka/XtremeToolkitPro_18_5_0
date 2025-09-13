// ActionsSampleView.cpp
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
#include "CntrItem.h"
#include "ActionsSampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CActionsSampleView

IMPLEMENT_DYNCREATE(CActionsSampleView, CRichEditView)

BEGIN_MESSAGE_MAP(CActionsSampleView, CRichEditView)
	//{{AFX_MSG_MAP(CActionsSampleView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRichEditView::OnFilePrintPreview)

	ON_NOTIFY_REFLECT(EN_SELCHANGE, OnSelChange)

	ON_COMMAND(ID_CHAR_BOLD, OnCharBold)
	ON_COMMAND(ID_CHAR_ITALIC, OnCharItalic)
	ON_COMMAND(ID_CHAR_UNDERLINE, OnCharUnderline)

	ON_COMMAND(ID_PARA_CENTER, CRichEditView::OnParaCenter)
	ON_UPDATE_COMMAND_UI(ID_PARA_CENTER, CRichEditView::OnUpdateParaCenter)
	ON_COMMAND(ID_PARA_LEFT, CRichEditView::OnParaLeft)
	ON_UPDATE_COMMAND_UI(ID_PARA_LEFT, CRichEditView::OnUpdateParaLeft)
	ON_COMMAND(ID_PARA_RIGHT, CRichEditView::OnParaRight)
	ON_UPDATE_COMMAND_UI(ID_PARA_RIGHT, CRichEditView::OnUpdateParaRight)

#define IMPLEMENT_APPTHEME_MAP(ID,Theme)\
	ON_COMMAND(ID_OPTIONS_STYLE_##ID, OnViewTheme##Theme)\
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_STYLE_##ID, OnUpdateViewTheme##Theme)
	
	IMPLEMENT_APPTHEME_MAP(OFFICE2000, Office2000)
	IMPLEMENT_APPTHEME_MAP(OFFICEXP, OfficeXP)
	IMPLEMENT_APPTHEME_MAP(OFFICE2003, Office2003)
	IMPLEMENT_APPTHEME_MAP(WINDOWSXP, WindowsXP)
	IMPLEMENT_APPTHEME_MAP(RIBBON, Ribbon)	
	IMPLEMENT_APPTHEME_MAP(OFFICE2007AQUA, Office2007Aqua)
	IMPLEMENT_APPTHEME_MAP(OFFICE2007BLACK, Office2007Black)
	IMPLEMENT_APPTHEME_MAP(OFFICE2007BLUE, Office2007Blue)
	IMPLEMENT_APPTHEME_MAP(OFFICE2007SILVER, Office2007Silver)
	IMPLEMENT_APPTHEME_MAP(OFFICE2007SYSTEM, Office2007System)
	IMPLEMENT_APPTHEME_MAP(OFFICE2010BLACK, Office2010Black)
	IMPLEMENT_APPTHEME_MAP(OFFICE2010BLUE, Office2010Blue)
	IMPLEMENT_APPTHEME_MAP(OFFICE2010SILVER, Office2010Silver)
	IMPLEMENT_APPTHEME_MAP(OFFICE2013WORD, Office2013Word)
	IMPLEMENT_APPTHEME_MAP(OFFICE2013EXCEL, Office2013Excel)
	IMPLEMENT_APPTHEME_MAP(OFFICE2013ACCESS, Office2013Access)
	IMPLEMENT_APPTHEME_MAP(OFFICE2013POWERPOINT, Office2013Powerpoint)
	IMPLEMENT_APPTHEME_MAP(OFFICE2013ONENOTE, Office2013OneNote)
	IMPLEMENT_APPTHEME_MAP(OFFICE2013OUTLOOK, Office2013Outlook)
	IMPLEMENT_APPTHEME_MAP(WINDOWS7SCENIC, Windows7)
	IMPLEMENT_APPTHEME_MAP(VC6, VisualStudio6)
	IMPLEMENT_APPTHEME_MAP(VC8, VisualStudio8)
	IMPLEMENT_APPTHEME_MAP(VC9, VisualStudio9)
	IMPLEMENT_APPTHEME_MAP(VC10, VisualStudio10)
	IMPLEMENT_APPTHEME_MAP(VC11_LIGHT, VisualStudio2012Light)
	IMPLEMENT_APPTHEME_MAP(VC11_DARK, VisualStudio2012Dark)
	IMPLEMENT_APPTHEME_MAP(VC14_LIGHT, VisualStudio2015Light)
	IMPLEMENT_APPTHEME_MAP(VC14_BLUE, VisualStudio2015Blue)
	IMPLEMENT_APPTHEME_MAP(VC14_DARK, VisualStudio2015Dark)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CActionsSampleView construction/destruction

CActionsSampleView::CActionsSampleView()
{
	// TODO: add construction code here

}

CActionsSampleView::~CActionsSampleView()
{
}

BOOL CActionsSampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRichEditView::PreCreateWindow(cs);
}

void CActionsSampleView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();

	USES_CONVERSION;

	// Set the printing margins (720 twips = 1/2 inch).
	SetMargins(CRect(720, 720, 720, 720));

	CHARFORMAT cf;
	ZeroMemory(&cf, sizeof(CHARFORMAT));
	
	CString strDefFont = _T("Tahoma");
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_BOLD |CFM_ITALIC | CFM_UNDERLINE | CFM_STRIKEOUT | CFM_SIZE |
		CFM_COLOR | CFM_OFFSET | CFM_PROTECTED | CFM_FACE;
	cf.dwEffects = CFE_AUTOCOLOR;
	cf.yHeight = 200; //10pt
	cf.bPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;

#if (_RICHEDIT_VER >= 0x0200)
	lstrcpyn(cf.szFaceName, strDefFont, LF_FACESIZE);
#else
	lstrcpynA(cf.szFaceName, T2A((LPTSTR) (LPCTSTR) strDefFont), LF_FACESIZE);
#endif

	GetRichEditCtrl().SetDefaultCharFormat(cf);

}

/////////////////////////////////////////////////////////////////////////////
// CActionsSampleView printing

BOOL CActionsSampleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}


void CActionsSampleView::OnDestroy()
{
   CRichEditView::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CActionsSampleView diagnostics

#ifdef _DEBUG
void CActionsSampleView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CActionsSampleView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CActionsSampleDoc* CActionsSampleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CActionsSampleDoc)));
	return (CActionsSampleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CActionsSampleView message handlers

void CActionsSampleView::OnCharBold()
{
	CRichEditView::OnCharBold();
	UpdateActionsState();
}

void CActionsSampleView::OnCharItalic()
{
	CRichEditView::OnCharItalic();
	UpdateActionsState();
}

void CActionsSampleView::OnCharUnderline()
{
	CRichEditView::OnCharUnderline();
	UpdateActionsState();
}


void CActionsSampleView::OnSelChange(NMHDR* pNMHDR, LRESULT* pResult)
{
	CRichEditView::OnSelChange(pNMHDR, pResult);

	UpdateActionsState();
}

void CActionsSampleView::UpdateActionsState()
{
	CHARFORMAT& cfm = GetCharFormatSelection();

	CXTPCommandBars* pCommandBars = ((CXTPFrameWnd*)GetParentFrame())->GetCommandBars();

	pCommandBars->GetActions()->FindAction(ID_CHAR_BOLD)->SetChecked(
		(cfm.dwMask & CFM_BOLD ? (cfm.dwEffects & CFE_BOLD ? 1 : 0) : 2));
	
	pCommandBars->GetActions()->FindAction(ID_CHAR_ITALIC)->SetChecked(
		(cfm.dwMask & CFM_ITALIC ? (cfm.dwEffects & CFE_ITALIC ? 1 : 0) : 2));

	pCommandBars->GetActions()->FindAction(ID_CHAR_UNDERLINE)->SetChecked(
		(cfm.dwMask & CFM_UNDERLINE ? (cfm.dwEffects & CFE_UNDERLINE ? 1 : 0) : 2));

}

#define IMPLEMENT_APPTHEME(Theme)\
	void CActionsSampleView::OnViewTheme##Theme()\
	{\
		SetTheme(CActionsSampleApp::theme##Theme);\
	}\
	void CActionsSampleView::OnUpdateViewTheme##Theme(CCmdUI* pCmdUI)\
	{\
		pCmdUI->SetCheck(CActionsSampleApp::theme##Theme == theApp.m_theme ? 1 : 0);\
	}

	IMPLEMENT_APPTHEME(Office2000)
	IMPLEMENT_APPTHEME(OfficeXP)
	IMPLEMENT_APPTHEME(Office2003)
	IMPLEMENT_APPTHEME(WindowsXP)
	IMPLEMENT_APPTHEME(Ribbon)	
	IMPLEMENT_APPTHEME(Office2007Aqua)
	IMPLEMENT_APPTHEME(Office2007Black)
	IMPLEMENT_APPTHEME(Office2007Blue)
	IMPLEMENT_APPTHEME(Office2007Silver)
	IMPLEMENT_APPTHEME(Office2007System)
	IMPLEMENT_APPTHEME(Office2010Black)
	IMPLEMENT_APPTHEME(Office2010Blue)
	IMPLEMENT_APPTHEME(Office2010Silver)
	IMPLEMENT_APPTHEME(Office2013Word)
	IMPLEMENT_APPTHEME(Office2013Excel)
	IMPLEMENT_APPTHEME(Office2013Access)
	IMPLEMENT_APPTHEME(Office2013Powerpoint)
	IMPLEMENT_APPTHEME(Office2013OneNote)
	IMPLEMENT_APPTHEME(Office2013Outlook)
	IMPLEMENT_APPTHEME(Windows7)
	IMPLEMENT_APPTHEME(VisualStudio6)	
	IMPLEMENT_APPTHEME(VisualStudio8)
	IMPLEMENT_APPTHEME(VisualStudio9)
	IMPLEMENT_APPTHEME(VisualStudio10)
	IMPLEMENT_APPTHEME(VisualStudio2012Light)
	IMPLEMENT_APPTHEME(VisualStudio2012Dark)
	IMPLEMENT_APPTHEME(VisualStudio2015Light)
	IMPLEMENT_APPTHEME(VisualStudio2015Blue)
	IMPLEMENT_APPTHEME(VisualStudio2015Dark)

void CActionsSampleView::SetTheme(CActionsSampleApp::AppTheme theme, BOOL bRedraw/*=TRUE*/)
{
	theApp.m_theme = theme;

	CMainFrame* pMainFrame = DYNAMIC_DOWNCAST(CMainFrame, theApp.m_pMainWnd);
	ASSERT_VALID(pMainFrame);
	if (!pMainFrame)
		return;

	if (bRedraw == FALSE)
	{
		pMainFrame->SetRedraw(FALSE);
	}

	switch(theme)
	{
	case CActionsSampleApp::themeOffice2000:
		pMainFrame->SetTheme(xtpThemeOffice2000);
		break;
	case CActionsSampleApp::themeOfficeXP:
		pMainFrame->SetTheme(xtpThemeOfficeXP);
		break;
	case CActionsSampleApp::themeOffice2003:
		pMainFrame->SetTheme(xtpThemeOffice2003);
		break;
	case CActionsSampleApp::themeWindowsXP:
		pMainFrame->SetTheme(xtpThemeNativeWinXP);
		break;
	case CActionsSampleApp::themeRibbon:
		pMainFrame->SetTheme(xtpThemeRibbon);
		break;
	case CActionsSampleApp::themeOffice2007Aqua:
		pMainFrame->SetTheme(xtpThemeRibbon, theApp.m_hModule2007, xtpIniOffice2007Aqua);
		break;
	case CActionsSampleApp::themeOffice2007Black:
		pMainFrame->SetTheme(xtpThemeRibbon, theApp.m_hModule2007, xtpIniOffice2007Black);
		break;
	case CActionsSampleApp::themeOffice2007Blue:
		pMainFrame->SetTheme(xtpThemeRibbon, theApp.m_hModule2007, xtpIniOffice2007Blue);
		break;
	case CActionsSampleApp::themeOffice2007Silver:
		pMainFrame->SetTheme(xtpThemeRibbon, theApp.m_hModule2007, xtpIniOffice2007Silver);
		break;
	case CActionsSampleApp::themeOffice2007System:
		pMainFrame->SetTheme(xtpThemeOffice2007System);
		break;
	case CActionsSampleApp::themeOffice2010Black:
		pMainFrame->SetTheme(xtpThemeRibbon, theApp.m_hModule2010, xtpIniOffice2010Black);
		break;
	case CActionsSampleApp::themeOffice2010Blue:
		pMainFrame->SetTheme(xtpThemeRibbon, theApp.m_hModule2010, xtpIniOffice2010Blue);
		break;
	case CActionsSampleApp::themeOffice2010Silver:
		pMainFrame->SetTheme(xtpThemeRibbon, theApp.m_hModule2010, xtpIniOffice2010Silver);
		break;
	case CActionsSampleApp::themeOffice2013Word:
		pMainFrame->SetTheme(xtpThemeOffice2013, theApp.m_hModule2013, xtpIniOffice2013Word);
		break;
	case CActionsSampleApp::themeOffice2013Excel:
		pMainFrame->SetTheme(xtpThemeOffice2013, theApp.m_hModule2013, xtpIniOffice2013Excel);
		break;
	case CActionsSampleApp::themeOffice2013Access:
		pMainFrame->SetTheme(xtpThemeOffice2013, theApp.m_hModule2013, xtpIniOffice2013Access);
		break;
	case CActionsSampleApp::themeOffice2013Powerpoint:
		pMainFrame->SetTheme(xtpThemeOffice2013, theApp.m_hModule2013, xtpIniOffice2013PowerPoint);
		break;
	case CActionsSampleApp::themeOffice2013OneNote:
		pMainFrame->SetTheme(xtpThemeOffice2013, theApp.m_hModule2013, xtpIniOffice2013OneNote);
		break;
	case CActionsSampleApp::themeOffice2013Outlook:
		pMainFrame->SetTheme(xtpThemeOffice2013, theApp.m_hModule2013, xtpIniOffice2013Outlook);
		break;
	case CActionsSampleApp::themeWindows7:
		pMainFrame->SetTheme(xtpThemeRibbon, theApp.m_hModuleWindows7, xtpIniWindows7Blue);
		break;
	case CActionsSampleApp::themeVisualStudio6:
		pMainFrame->SetTheme(xtpThemeVisualStudio6);
		break;
	case CActionsSampleApp::themeVisualStudio8:
		pMainFrame->SetTheme(xtpThemeVisualStudio2005);
		break;
	case CActionsSampleApp::themeVisualStudio9:
		pMainFrame->SetTheme(xtpThemeVisualStudio2008);
		break;
	case CActionsSampleApp::themeVisualStudio10:
		pMainFrame->SetTheme(xtpThemeVisualStudio2010);
		break;
	case CActionsSampleApp::themeVisualStudio2012Dark:
		pMainFrame->SetTheme(xtpThemeVisualStudio2012Dark, theApp.m_hModule2012, xtpIniVisualStudio2012Dark);
		break;
	case CActionsSampleApp::themeVisualStudio2012Light:
		pMainFrame->SetTheme(xtpThemeVisualStudio2012Light, theApp.m_hModule2012, xtpIniVisualStudio2012Light);
		break;
	case CActionsSampleApp::themeVisualStudio2015Light:
		pMainFrame->SetTheme(xtpThemeVisualStudio2015, theApp.m_hModule2015, xtpIniVisualStudio2015Light);
		break;
	case CActionsSampleApp::themeVisualStudio2015Blue:
		pMainFrame->SetTheme(xtpThemeVisualStudio2015, theApp.m_hModule2015, xtpIniVisualStudio2015Blue);
		break;
	case CActionsSampleApp::themeVisualStudio2015Dark:
		pMainFrame->SetTheme(xtpThemeVisualStudio2015, theApp.m_hModule2015, xtpIniVisualStudio2015Dark);
		break;
	}

	if (bRedraw == FALSE)
	{
		pMainFrame->SetRedraw(TRUE);
	}
}
