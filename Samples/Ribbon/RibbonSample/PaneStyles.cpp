// PaneStyles.cpp
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
#include "ribbonsample.h"
#include "PaneStyles.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef _XTP_INCLUDE_DOCKINGPANE

/////////////////////////////////////////////////////////////////////////////
// CPaneStyles dialog


CPaneStyles::CPaneStyles(CWnd* pParent /*=NULL*/)
	: CXTPResizeDialog(CPaneStyles::IDD, pParent), m_pPane(NULL)
{
	//{{AFX_DATA_INIT(CPaneStyles)
	//}}AFX_DATA_INIT
}


void CPaneStyles::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPaneStyles)
	DDX_Control(pDX, IDC_LIST_STYLES, m_lstStyles);
	DDX_Control(pDX, IDC_CHECK_LINKEDSTYLE, m_chkLinkedStyle);
	DDX_Control(pDX, IDC_CHECK_PREV, m_chkPreview);
	DDX_Control(pDX, IDC_BUTTON_STYLEINSPECTOR, m_btnStyleInspector);
	DDX_Control(pDX, IDC_BUTTON_NEWSTYLE, m_btnNewStyle);
	DDX_Control(pDX, IDC_BUTTON_MANAGESTYLES, m_btnManageStyles);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPaneStyles, CXTPResizeDialog)
	//{{AFX_MSG_MAP(CPaneStyles)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_WINDOWPOSCHANGED()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CPaneStyles::SetOwnerPane(CXTPDockingPane* pPane)
{
	ASSERT(pPane);
	m_pPane = pPane;
}

/////////////////////////////////////////////////////////////////////////////
// CPaneStyles message handlers

void CPaneStyles::OnCancel()
{
}

void CPaneStyles::OnOK()
{
}

HBRUSH CPaneStyles::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	return m_brush;
}

BOOL CPaneStyles::OnInitDialog() 
{
	CXTPResizeDialog::OnInitDialog();

	SetResize(IDC_LIST_STYLES,           XTP_ANCHOR_TOPLEFT,    XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_CHECK_PREV,         XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CHECK_LINKEDSTYLE,     XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_BUTTON_NEWSTYLE,       XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_BUTTON_STYLEINSPECTOR, XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_BUTTON_MANAGESTYLES,   XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);

	m_lstStyles.AddString(_T("Clear All"));
	m_lstStyles.AddString(_T("Normal"));
	m_lstStyles.AddString(_T("No Spacing"));
	m_lstStyles.AddString(_T("Heading 1"));
	m_lstStyles.AddString(_T("Heading 2"));
	m_lstStyles.AddString(_T("Heading 3"));
	m_lstStyles.AddString(_T("Title"));
	m_lstStyles.AddString(_T("Subtitle"));


	CXTPImageManagerIconHandle ih;
	CXTPImageManagerIconHandle ihh;
	
	ih.Attach(CXTPImageManagerIcon::LoadBitmapFromResource(MAKEINTRESOURCE(IDC_BUTTON_NEWSTYLE), NULL), FALSE);
	m_btnNewStyle.SetIcon(CSize(16, 16), ih, ihh);

	ih.Attach(CXTPImageManagerIcon::LoadBitmapFromResource(MAKEINTRESOURCE(IDC_BUTTON_MANAGESTYLES), NULL), FALSE);
	m_btnManageStyles.SetIcon(CSize(16, 16), ih, ihh);

	ih.Attach(CXTPImageManagerIcon::LoadBitmapFromResource(MAKEINTRESOURCE(IDC_BUTTON_STYLEINSPECTOR), NULL), FALSE);
	m_btnStyleInspector.SetIcon(CSize(16, 16), ih, ihh);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPaneStyles::RefreshMetrics(XTPDockingPanePaintTheme nPaneTheme)
{
	m_brush.DeleteObject();

	XTPControlTheme nTheme = xtpControlThemeDefault;
	COLORREF clrBrush = ::GetSysColor(COLOR_3DFACE);

	switch(nPaneTheme)
	{
	case xtpPaneThemeOffice2007Word:
		clrBrush = XTPResourceImages()->GetImageColor(_T("DockingPane"), _T("WordPaneBackground"));
		nTheme = xtpControlThemeResource;
		break;
	case xtpPaneThemeOffice2013:
		clrBrush = XTPIniColor(_T("DockingPane"), _T("Background"), RGB(255,255,255));
		nTheme = xtpControlThemeOffice2013;
		break;
	case xtpPaneThemeVisualStudio2003: // System nTheme
		clrBrush = ::GetSysColor(COLOR_3DFACE);
		nTheme = xtpControlThemeOfficeXP;
		break;
	case xtpPaneThemeVisualStudio2015:
		clrBrush = XTPIniColor(_T("DockingPane"), _T("Background"), RGB(255,255,255));
		nTheme = xtpControlThemeVisualStudio2015;
		break;
	}

	theApp.m_csPane.RefreshMetrics(nPaneTheme);
	m_brush.CreateSolidBrush(clrBrush);

	SendMessageToDescendants(
		WM_XTP_SETCONTROLTHEME, nTheme);

	RedrawWindow(NULL ,NULL,
		RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_ALLCHILDREN);
}

void CPaneStyles::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CXTPClientRect rWindow(this);
	theApp.m_csPane.DrawBorders(&dc, rWindow, m_pPane);
}

void CPaneStyles::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	CXTPResizeDialog::OnWindowPosChanged(lpwndpos);
	
	// refresh borders.
	RedrawWindow(NULL ,NULL,
		RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_ALLCHILDREN);
}

#endif
