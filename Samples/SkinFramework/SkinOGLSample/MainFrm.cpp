// MainFrm.cpp
//

#include "StdAfx.h"
#include "cube.h"

#include "CubeDoc.h"
#include "CubeView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	ON_COMMAND(ID_THEME_NONE,       OnThemeNone)
	ON_COMMAND(ID_THEME_OFFICE2007, OnThemeOffice2007)
	ON_COMMAND(ID_THEME_OFFICE2010, OnThemeOffice2010)
	ON_COMMAND(ID_THEME_VISTA,      OnThemeVista)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// arrays of IDs used to initialize control bars

// toolbar buttons - IDs are command buttons
static UINT BASED_CODE buttons[] =
{
	// same order as in the bitmap 'toolbar.bmp'
	ID_FILE_PLAY,
	ID_APP_ABOUT,
};


static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	XTPSkinManager()->ExcludeModule(_T("opengl32.dll"));
	XTPSkinManager()->ExcludeModule(_T("glu32.dll"));
	XTPSkinManager()->ExcludeModule(_T("ddraw.dll"));
	XTPSkinManager()->ExcludeModule(_T("nvoglv32.dll"));	//if installed nvidia graphic card
	OnThemeChanged(ID_THEME_NONE);
}

CMainFrame::~CMainFrame()
{
	XTPSkinManager()->LoadSkin(NULL);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

#if defined(_XTP_INCLUDE_COMMANDBARS)
	
	if (!m_wndStatusBar.Create(this) ||
		 !m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	
	if (!InitCommandBars())
		return -1;

	CXTPCommandBars* pCommandBars = GetCommandBars();
	
	pCommandBars->SetMenu(_T("Menu Bar"), IDR_MAINFRAME);
	pCommandBars->GetToolTipContext()->SetStyle(xtpToolTipOffice);
	pCommandBars->GetPaintManager()->m_bAutoResizeIcons = TRUE;
	pCommandBars->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE);

#else

#endif

	return 0;
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

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd)
{
	CFrameWnd::OnPaletteChanged(pFocusWnd);

	if(pFocusWnd != this)
		OnQueryNewPalette();
}

BOOL CMainFrame::OnQueryNewPalette()
{
	int        i;
	CPalette    *pOldPal;
	CCubeView   *pView = (CCubeView *)GetActiveView();
	CClientDC   dc(pView);


	pOldPal = dc.SelectPalette(&pView->m_cPalette, FALSE);
	i = dc.RealizePalette();
	dc.SelectPalette(pOldPal, FALSE);

	if(i > 0)
		InvalidateRect(NULL);


	return CFrameWnd::OnQueryNewPalette();
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// remove this flag to remove " - Untitled" from the frame's caption

	cs.style &= ~ FWS_ADDTOTITLE;

	return CFrameWnd::PreCreateWindow(cs);
}


CString CMainFrame::GetStylesPath()
{
	TCHAR szStylesPath[_MAX_PATH];

	VERIFY(::GetModuleFileName(
		AfxGetApp()->m_hInstance, szStylesPath, _MAX_PATH));		
	
	CString csStylesPath(szStylesPath);
	int nIndex  = csStylesPath.ReverseFind(_T('\\'));
	if (nIndex > 0) {
		csStylesPath = csStylesPath.Left(nIndex);
	}
	else {
		csStylesPath.Empty();
	}

	return csStylesPath + _T("\\Styles\\");
}

void CMainFrame::OnThemeNone()
{
	OnThemeChanged(ID_THEME_NONE);
}

void CMainFrame::OnThemeOffice2007()
{
	OnThemeChanged(ID_THEME_OFFICE2007);
}

void CMainFrame::OnThemeOffice2010()
{
	OnThemeChanged(ID_THEME_OFFICE2010);
}

void CMainFrame::OnThemeVista()
{
	OnThemeChanged(ID_THEME_VISTA);
}

void CMainFrame::OnThemeChanged(int nTheme)
{
	m_nTheme = nTheme;

	switch (nTheme)
	{
	case ID_THEME_NONE:
		XTPSkinManager()->LoadSkin(_T(""), _T(""));
		break;
	case ID_THEME_OFFICE2007:
		XTPSkinManager()->LoadSkin(GetStylesPath() + _T("Office2007.cjstyles"));
		break;
	case ID_THEME_OFFICE2010:
		XTPSkinManager()->LoadSkin(GetStylesPath() + _T("Office2010.cjstyles"));
		break;
	case ID_THEME_VISTA:
		XTPSkinManager()->LoadSkin(GetStylesPath() + _T("Vista.cjstyles"), _T("NormalBlack2.INI"));
		break;
	}
}
