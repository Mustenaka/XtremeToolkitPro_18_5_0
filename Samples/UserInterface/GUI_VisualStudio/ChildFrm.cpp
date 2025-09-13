// ChildFrm.cpp 
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
#include "GUI_VisualStudio.h"
#include "GUI_VisualStudioDoc.h"
#include "GUI_VisualStudioView.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_CREATE()
	ON_REGISTERED_MESSAGE(XTP_WM_UPDATE_MDI_CHILD_THEME, OnUpdateMDIChildrenTheme)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here

}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

LRESULT CChildFrame::OnUpdateMDIChildrenTheme(WPARAM, LPARAM)
{
	SetTheme(theApp.m_theme);
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CMenu* pMenu = GetSystemMenu(FALSE);

	pMenu->RemoveMenu(SC_RESTORE, MF_BYCOMMAND);
	pMenu->RemoveMenu(SC_MINIMIZE, MF_BYCOMMAND);
	pMenu->RemoveMenu(SC_MAXIMIZE, MF_BYCOMMAND);
	pMenu->RemoveMenu(SC_MOVE, MF_BYCOMMAND);
	pMenu->RemoveMenu(SC_SIZE, MF_BYCOMMAND);
	
	return 0;
}

void CChildFrame::SetTheme(AppTheme theme)
{
	switch(theme)
	{
	case themeVS2012Light:
		m_wndSplitter.SetTheme(xtpControlThemeVisualStudio2012Light);
		break;
	case themeVS2012Dark:
		m_wndSplitter.SetTheme(xtpControlThemeVisualStudio2012Dark);
		break;
	case themeVS2015Light:
	case themeVS2015Dark:
	case themeVS2015Blue:
		m_wndSplitter.SetTheme(xtpControlThemeVisualStudio2015);
		break;
	case themeVS2010:
		if (m_wndSplitter.SetTheme(xtpControlThemeVisualStudio2010))			
			m_wndSplitter.GetTheme()->EnableTabColors(); // Use theme colors for MDI tabs.
		break;
	case themeVS2008:
		m_wndSplitter.SetTheme(xtpControlThemeVisualStudio2008);
		break;
	case themeVS2005:
		m_wndSplitter.SetTheme(xtpControlThemeVisualStudio2005);
		break;
	case themeVS2003:
		m_wndSplitter.SetTheme(xtpControlThemeOfficeXP);
		break;
	default:
		m_wndSplitter.SetTheme(xtpControlThemeDefault);
		break;
	}

	if(NULL != GetActiveView())
	{
		CGUI_VisualStudioView* pView = (CGUI_VisualStudioView*)GetActiveView();
		pView->RefreshColors();
	}
}

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	DragAcceptFiles();

#ifdef _XTP_INCLUDE_SYNTAXEDIT
	UNREFERENCED_PARAMETER(lpcs);

	if (!m_wndSplitter.Create(this, 2, 2, CSize(25, 25), pContext))
	{
		TRACE0("Failed to create splitter window.\n");
		return FALSE;
	}
#endif

	SetTheme(theApp.m_theme);

#ifdef _XTP_INCLUDE_SYNTAXEDIT
	return TRUE;
#else
	return CMDIChildWnd::OnCreateClient(lpcs, pContext);
#endif
}
