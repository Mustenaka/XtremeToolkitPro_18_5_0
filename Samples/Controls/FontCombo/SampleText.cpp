// SampleText.cpp
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
#include "FontCombo.h"
#include "FontComboDlg.h"
#include "SampleText.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSampleText

CSampleText::CSampleText()
{
	m_cr = COLORREF_NULL;
}

CSampleText::~CSampleText()
{
}

BEGIN_MESSAGE_MAP(CSampleText, CXTPEdit)
	//{{AFX_MSG_MAP(CSampleText)
	ON_WM_PAINT()
	ON_WM_NCPAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSampleText message handlers

void CSampleText::UpdateFont(const CXTPLogFont& lf, const COLORREF& cr)
{
	m_cr = cr;
	m_lf = lf;

	if (::IsWindow(m_hWnd))
		RedrawWindow();
}

void CSampleText::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CXTPClientRect rClient(this);
	
	// Paint to a memory device context to help
	// eliminate screen flicker...
	CXTPBufferDC memDC(dc, rClient);
	memDC.FillSolidRect(rClient, GetXtremeColor(COLOR_WINDOW));

	// create a font based on the current font selection.
	CFont font;
	font.CreateFontIndirect(&m_lf);

	// set the text color and font based on current selection
	CXTPFontDC fontDC(&memDC, &font);
	memDC.SetBkMode(TRANSPARENT);

	CString csWindowText;
	GetWindowText(csWindowText);

	// display the sample text.
	memDC.SetTextColor(m_cr);
	memDC.DrawText(csWindowText, &rClient, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

void CSampleText::OnNcPaint() 
{
	if(GetThemeID() == xtpControlThemeOffice2013 || GetThemeID() == xtpControlThemeVisualStudio2012Light || GetThemeID() == xtpControlThemeVisualStudio2012Dark)
		CXTPEdit::OnNcPaint();
	else
	{
		CWindowDC dc(this);

		// convert to client coordinates
		CXTPWindowRect rWindow(this);
		ScreenToClient(rWindow);
		
		// exclude the client area from paint operation.
		CXTPClientRect rClient(this);
		rClient.OffsetRect(-rWindow.left, -rWindow.top);
		dc.ExcludeClipRect(rClient);
		rWindow.OffsetRect(-rWindow.left, -rWindow.top);
		
		// Paint to a memory device context to help
		// eliminate screen flicker...
		CXTPBufferDC memDC(dc, rWindow);
		memDC.FillSolidRect(rWindow, GetXtremeColor(COLOR_WINDOW));
		memDC.Draw3dRect(&rWindow, GetXtremeColor(XPCOLOR_HIGHLIGHT_BORDER), GetXtremeColor(XPCOLOR_HIGHLIGHT_BORDER));
	}
}
