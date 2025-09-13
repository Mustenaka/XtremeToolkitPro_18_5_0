// PaneViewOutput.cpp
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
#include "PaneWnd.h"
#include "PaneViewOutput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaneViewOutput

CPaneViewOutput::CPaneViewOutput() : m_pPane(NULL)
{
}

CPaneViewOutput::~CPaneViewOutput()
{
}

BEGIN_MESSAGE_MAP(CPaneViewOutput, CXTPEditor)
	//{{AFX_MSG_MAP(CPaneViewOutput)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_NCPAINT()
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(WM_REFRESHMETRICS, OnRefreshMetrics)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPaneViewOutput message handlers

int CPaneViewOutput::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CXTPEditor::OnCreate(lpCreateStruct) == -1)
		return -1;

	ModifyStyle(0, WS_BORDER);

	SetFont(XTPPaintManager()->GetRegularFont());
	SetMargins(XTP_DPI_X(10), XTP_DPI_Y(5));

	return 0;
}

void CPaneViewOutput::OnSize(UINT nType, int cx, int cy)
{
	CXTPEditor::OnSize(nType, cx, cy);
}

void CPaneViewOutput::OnNcPaint() 
{
	TBase::OnNcPaint();

	CWindowDC dc(this);
	CXTPWindowRect rWindow(this);
	rWindow.OffsetRect(-rWindow.TopLeft());

	theApp.m_csPane.DrawBorders(&dc, rWindow, m_pPane);
}

LRESULT CPaneViewOutput::OnRefreshMetrics(WPARAM wParam, LPARAM /*lParam*/)
{
	switch (AppTheme(wParam))
	{
	case themeVS6:
		SetTheme(xtpControlThemeDefault);
		break;
	case themeVS2003:
		SetTheme(xtpControlThemeVisualStudio2005);
		break;
	case themeVS2005:
		SetTheme(xtpControlThemeVisualStudio2005);
		break;
	case themeVS2008:
		SetTheme(xtpControlThemeVisualStudio2008);
		break;
	case themeVS2010:
		SetTheme(xtpControlThemeVisualStudio2010);
		break;
	case themeVS2012Light:
		SetTheme(xtpControlThemeVisualStudio2012Light);
		break;
	case themeVS2012Dark:
		SetTheme(xtpControlThemeVisualStudio2012Dark);
		break;
	case themeVS2015Light:
	case themeVS2015Dark:
	case themeVS2015Blue:
		SetTheme(xtpControlThemeVisualStudio2015);
		break;
	}

	return 0;
}
