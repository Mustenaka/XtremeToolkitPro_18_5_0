// MainFrm.cpp
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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef WM_MENURBUTTONUP
#define WM_MENURBUTTONUP 0x0122
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CXTPFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CXTPFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_MESSAGE(WM_MENURBUTTONUP, OnMenuRButtonUp)
	ON_COMMAND_RANGE(200, 299, OnSkin)
	ON_COMMAND_RANGE(ID_CONTEXT_ITEM1, ID_CONTEXT_ITEM3, OnContextItem)
	ON_UPDATE_COMMAND_UI_RANGE(200, 209, OnUpdateSkin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


struct Skin
{
	LPCTSTR pszName;
	LPCTSTR pszPath;
	LPCTSTR pszIni;
};

static const Skin skins[] =
{
	{_T("None"), NULL, NULL},

	// Office 2007
	{_T("Office 2007 Light Blue"),    _T("Office2007.cjstyles"), _T("LightBlue.ini")},
	{_T("Office 2007 Normal Aqua"),   _T("Office2007.cjstyles"), _T("NormalAqua.ini")},
	{_T("Office 2007 Normal Black"),  _T("Office2007.cjstyles"), _T("NormalBlack.ini")},
	{_T("Office 2007 Normal Blue"),   _T("Office2007.cjstyles"), _T("NormalBlue.ini")},
	{_T("Office 2007 Normal Silver"), _T("Office2007.cjstyles"), _T("NormalSilver.ini")},

	// Office 2010
	{_T("Office 2010 Normal Black"),  _T("Office2010.cjstyles"), _T("NormalBlack.ini")},
	{_T("Office 2010 Normal Blue"),   _T("Office2010.cjstyles"), _T("NormalBlue.ini")},
	{_T("Office 2010 Normal Silver"), _T("Office2010.cjstyles"), _T("NormalSilver.ini")},

	// Vista
	{_T("Vista"),  _T("Vista.cjstyles"), NULL},
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
	: m_nSkin(200)
{
	XTPSkinManager()->SetAutoApplyNewWindows(TRUE);
	OnSkin(204);
}

CMainFrame::~CMainFrame()
{
	XTPSkinManager()->LoadSkin(NULL);
}

void CMainFrame::OnContextItem(UINT nID)
{
}

void CMainFrame::OnSkin(UINT nID)
{
	m_nSkin = nID;

	int nSkin = nID-200;
	XTPSkinManager()->LoadSkin(GetStylesPath() + skins[nSkin].pszPath, skins[nSkin].pszIni);

	if (NULL != GetSafeHwnd())
		RedrawWindow(0, 0, RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ALLCHILDREN);
}

void CMainFrame::OnUpdateSkin(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nSkin==pCmdUI->m_nID ? 1 : 0);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	//////////////////////////////////////////////////////////////////////////
	// Skin
	//////////////////////////////////////////////////////////////////////////

	CMenu *pMenu = GetMenu()->GetSubMenu(mnuSkin);

	if ((NULL != pMenu) && (::IsMenu(pMenu->m_hMenu)))
	{
		for (int nItem=0; nItem<_countof(skins); nItem++)
		{
			pMenu->AppendMenu(MF_STRING, 200+nItem, skins[nItem].pszName);
		}

		pMenu->DeleteMenu(ID_SKIN, MF_BYCOMMAND);
	}

	//////////////////////////////////////////////////////////////////////////
	// Scroll
	//////////////////////////////////////////////////////////////////////////

	pMenu = GetMenu()->GetSubMenu(mnuScroll);

	if ((NULL != pMenu) && (::IsMenu(pMenu->m_hMenu)))
	{
		for (int nItem=0; nItem<50; nItem++)
		{
			CString sCaption;
			sCaption.Format(_T("Item %d"), nItem);

			pMenu->AppendMenu(MF_STRING, 400+nItem, sCaption);
		}

		pMenu->DeleteMenu(ID_TEST_SCROLL, MF_BYCOMMAND);
	}

	//////////////////////////////////////////////////////////////////////////
	// Menu break
	//////////////////////////////////////////////////////////////////////////

	pMenu = GetMenu()->GetSubMenu(mnuMenuBreak);

	if ((NULL != pMenu) && (::IsMenu(pMenu->m_hMenu)))
	{
		for (int nColumn=0; nColumn<3; nColumn++)
		{
			for (int nItem=0; nItem<10+nColumn; nItem++)
			{
				CString sCaption;
				sCaption.Format(_T("Item %d"), nItem);

				UINT nFlags = MF_STRING;

				if (0 < nColumn && 0 == nItem)
				{
					nFlags |= MF_MENUBREAK;
				}

				pMenu->AppendMenu(nFlags, 500+(nColumn*nItem), sCaption);
			}
		}

		pMenu->DeleteMenu(ID_TEST_MENUBREAK, MF_BYCOMMAND);
	}

#if 0
	// Initialize the command bars
	if (!InitCommandBars())
	{
		return -1;
	}

	// Get a pointer to the command bars object.
	CXTPCommandBars *pCommandBars = GetCommandBars();
	if (NULL == pCommandBars)
	{
		TRACE0("Failed to create command bars object.\n");
		return -1;      // fail to create
	}

	pCommandBars->SetTheme(xtpThemeResource);
	pCommandBars->GetPaintManager()->m_bAutoResizeIcons = TRUE;
	pCommandBars->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE);

	// Add the menu bar
	CXTPMenuBar *pMenuBar = pCommandBars->SetMenu(_T("Menu Bar"), IDR_MAINFRAME);
	CXTPControlPopup *pPopup;
	
	
	//////////////////////////////////////////////////////////////////////////
	// Scroll
	//////////////////////////////////////////////////////////////////////////

	pPopup = DYNAMIC_DOWNCAST(CXTPControlPopup, pMenuBar->GetControl(mnuScroll));
	pPopup->GetCommandBar()->GetControls()->RemoveAll();

	for (int nItem=0; nItem<50; nItem++)
	{
		CString sCaption;
		sCaption.Format(_T("Item %d"), nItem);

		CXTPControl *pItem = pPopup->GetCommandBar()->GetControls()->Add(xtpControlButton, 400+nItem);
		pItem->SetCaption(sCaption);
	}

	//////////////////////////////////////////////////////////////////////////
	// Menu break
	//////////////////////////////////////////////////////////////////////////
	
	pPopup = DYNAMIC_DOWNCAST(CXTPControlPopup, pMenuBar->GetControl(mnuMenuBreak));
	pPopup->GetCommandBar()->GetControls()->RemoveAll();

	for (int nColumn=0; nColumn<5; nColumn++)
	{
		for (int nItem=0; nItem<10+nColumn; nItem++)
		{
			CString sCaption;
			sCaption.Format(_T("Item %d"), nItem);

			CXTPControl *pItem = pPopup->GetCommandBar()->GetControls()->Add(xtpControlButton, 500+(nColumn*nItem));
			pItem->SetCaption(sCaption);

			if (0 < nColumn && (0 == nItem))
			{
				pItem->SetBeginGroup(TRUE);
				pItem->SetFlags(xtpFlagWrapRow);
			}
		}
	}
#endif
	return 0;
}

LRESULT CMainFrame::OnMenuRButtonUp(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	return TRUE;
}


CString CMainFrame::GetStylesPath() const
{
	TCHAR szStylesPath[_MAX_PATH];

	VERIFY(::GetModuleFileName(AfxGetApp()->m_hInstance, szStylesPath, _MAX_PATH));

	CString csStylesPath(szStylesPath);
	int nIndex  = csStylesPath.ReverseFind(_T('\\'));
	if (nIndex > 0)
	{
		csStylesPath = csStylesPath.Left(nIndex);
	}
	else
	{
		csStylesPath.Empty();
	}

	return csStylesPath + _T("\\Styles\\");
}



/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

