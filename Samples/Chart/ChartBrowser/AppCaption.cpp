// AppCaption.cpp
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
#include "chartbrowser.h"
#include "AppCaption.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppCaption

CAppCaption::CAppCaption()
{

	m_strContent = _T("Bar Style");

	LOGFONT lf;
	XTPDrawHelpers()->GetIconLogFont(&lf);
	lf.lfHeight  = -30;
	STRCPY_S(lf.lfFaceName, LF_FACESIZE, _T("Segoe UI"));
	m_fnt.CreateFontIndirect(&lf);
}

CAppCaption::~CAppCaption()
{
}


void CAppCaption::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	// update the dialog controls added to the status bar
	UpdateDialogControls(pTarget, bDisableIfNoHndler);
}

void CAppCaption::Create(CWnd* pParentWnd)
{
	m_dwStyle = CBRS_TOP;

	CControlBar::Create(AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)), 0, WS_CHILD | WS_VISIBLE| CBRS_TOP, 
		CRect(0, 0, 0, 0), pParentWnd, 0xE806);

}

CSize CAppCaption::CalcFixedLayout(BOOL, BOOL /*bHorz*/)
{
	ASSERT_VALID(this);
	ASSERT(::IsWindow(m_hWnd));
	
	CSize size(32767, 40);
	return size;
}



BEGIN_MESSAGE_MAP(CAppCaption, CControlBar)
	//{{AFX_MSG_MAP(CAppCaption)
	ON_WM_PAINT()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAppCaption message handlers

void CAppCaption::OnPaint()
{
	CPaintDC dcPaint(this); // device context for painting
	
	CXTPBufferDC dc(dcPaint);
	
	CXTPFontDC font(&dc, &m_fnt);

	CXTPClientRect rc(this);

#ifndef _XTP_INCLUDE_COMMANDBARS
	dc.FillSolidRect(rc, RGB(255, 255, 255));
#else
	dc.FillSolidRect(rc, RGB(246,246,246));
#endif
	rc.DeflateRect(8, 0);
	
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(0);
	dc.DrawText(m_strContent, rc, DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_NOPREFIX);
}

void CAppCaption::SetContent(CString str)
{
	m_strContent = str;
	Invalidate();
}


void CAppCaption::OnSize(UINT nType, int cx, int cy)
{
	CControlBar::OnSize(nType, cx, cy);
	Invalidate(FALSE);
}
