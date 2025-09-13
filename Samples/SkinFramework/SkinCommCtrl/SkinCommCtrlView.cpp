// SkinCommCtrlView.cpp
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

#include "StdAfx.h"
#include "SkinCommCtrl.h"

#include "SkinCommCtrlDoc.h"
#include "SkinCommCtrlView.h"
#include "MainFrm.h"

#ifndef TPM_RECURSE
#define TPM_RECURSE         0x0001L
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinCommCtrlView

#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#endif

#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))
#endif

#ifndef WM_MENURBUTTONUP
#define WM_MENURBUTTONUP 0x0122
#endif

IMPLEMENT_DYNCREATE(CSkinCommCtrlView, CEditView)

BEGIN_MESSAGE_MAP(CSkinCommCtrlView, CEditView)
	//{{AFX_MSG_MAP(CSkinCommCtrlView)
	ON_WM_INITMENUPOPUP()
	ON_WM_ENTERMENULOOP()
	//ON_WM_EXITMENULOOP()
	ON_WM_RBUTTONUP()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT,         CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT,  CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)

	ON_MESSAGE(WM_MENURBUTTONUP, OnMenuRButtonUp)

	ON_COMMAND_RANGE(400, 499, OnMenuRange)
	ON_COMMAND_RANGE(500, 599, OnMenuRange)

	ON_COMMAND(ID_TEST_CHECKED,  OnMenuDummy)
	ON_COMMAND(ID_TEST_GRAYED,   OnMenuDummy)
	ON_COMMAND(ID_TEST_INACTIVE, OnMenuDummy)

	ON_COMMAND(ID_TEST_CLEAR_OUTPUT,    OnClearOutput)
	ON_COMMAND(ID_TEST_GETMENUITEMID,   OnGetMenuItemID)
	ON_COMMAND(ID_TEST_GETMENUITEMRECT, OnGetMenuItemRect)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinCommCtrlView construction/destruction

CSkinCommCtrlView::CSkinCommCtrlView()
{
}

CSkinCommCtrlView::~CSkinCommCtrlView()
{
}

BOOL CSkinCommCtrlView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CEditView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSkinCommCtrlView drawing

void CSkinCommCtrlView::OnDraw(CDC *pDC)
{
	CSkinCommCtrlDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CSkinCommCtrlView printing

BOOL CSkinCommCtrlView::OnPreparePrinting(CPrintInfo *pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSkinCommCtrlView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CSkinCommCtrlView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CEditView::OnEndPrinting(pDC, pInfo);
}

void CSkinCommCtrlView::OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	RECT rcItem;

	::GetMenuItemRect(GetSafeHwnd(), pPopupMenu->GetSafeHmenu(), 0, &rcItem);
	PrintRect(_T("Context"), rcItem);
}

void CSkinCommCtrlView::OnEnterMenuLoop(BOOL bIsTrackPopupMenu)
{
}

void CSkinCommCtrlView::OnRButtonUp(UINT nFlags, CPoint point)
{
	CEditView::OnRButtonUp(nFlags, point);
}

void CSkinCommCtrlView::OnContextMenu(CWnd *pWnd, CPoint pos)
{
	PrintPoint(_T("OnContextMenu"), pos);

	CMenu mnuContext;
	mnuContext.LoadMenu(IDR_CONTEXT);
	CMenu *pPopup = mnuContext.GetSubMenu(0);
	
	//pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, pos.x, pos.y, this);

	::TrackPopupMenuEx(pPopup->GetSafeHmenu(), TPM_LEFTALIGN | TPM_LEFTBUTTON,
		pos.x, pos.y, GetSafeHwnd(), NULL);
}


LRESULT CSkinCommCtrlView::OnMenuRButtonUp(WPARAM wParam, LPARAM lParam)
{
	UINT  nPos  = static_cast     <UINT> (wParam);
	HMENU hMenu = reinterpret_cast<HMENU>(lParam);

	CString sLine;
	sLine.Format(_T("OnMenuRButtonUp(Position %d, Count %d)\n"), nPos, ::GetMenuItemCount(hMenu));
	PrintLine(sLine);

	DWORD dwPos   = ::GetMessagePos();
	DWORD dwFlags = 0;

	CMenu mnuRecurse;
	mnuRecurse.LoadMenu(IDR_RECURSE);
	CMenu *pPopup = mnuRecurse.GetSubMenu(0);

	if (0 == nPos)
	{
		dwFlags = TPM_RECURSE | TPM_RETURNCMD;
	}
	else
	{
		dwFlags = TPM_LEFTALIGN | TPM_LEFTBUTTON;
	}

	BOOL bTrack = ::TrackPopupMenuEx(pPopup->GetSafeHmenu(), dwFlags,
		GET_X_LPARAM(dwPos), GET_Y_LPARAM(dwPos), GetSafeHwnd(), NULL);

	if (!bTrack)
	{
		DWORD dwError = ::GetLastError();
		sLine.Format(_T("Last error: 0x%.4x\n"), dwError);
		PrintLine(sLine);
	}

	return 0;
}

void CSkinCommCtrlView::OnClearOutput()
{
	CEdit &wndEdit = GetEditCtrl();
	wndEdit.SetWindowText(_T(""));
}

void CSkinCommCtrlView::OnGetMenuItemID()
{
	CMenu *pMenu = AfxGetMainWnd()->GetMenu()->GetSubMenu(mnuFile);

	for (UINT nItem=0; nItem < (UINT)pMenu->GetMenuItemCount(); nItem++)
	{
		UINT nID = pMenu->GetMenuItemID(nItem);

		CString sID;
		sID.Format(_T("GetMenuItemID: %d\n"), nID);
		PrintLine(sID);
	}
}

void CSkinCommCtrlView::OnGetMenuItemRect()
{
	CWnd  *pWndMain    = AfxGetMainWnd();
	CMenu *pMenuMain   = pWndMain->GetMenu();
	CMenu *pMenuFile   = pMenuMain->GetSubMenu(mnuFile);
	CMenu *pMenuStyles = pMenuMain->GetSubMenu(mnuMenuStyles);
	CMenu *pMenuPopUp  = pMenuStyles->GetSubMenu(0);

	RECT rcItem;

	::GetMenuItemRect(pWndMain->GetSafeHwnd(), pMenuMain->GetSafeHmenu(), mnuFile,     &rcItem);
	PrintRect(_T("File"), rcItem);

	::GetMenuItemRect(pWndMain->GetSafeHwnd(), pMenuFile->GetSafeHmenu(), mnuFileOpen, &rcItem);
	PrintRect(_T("File open"), rcItem);

	::GetMenuItemRect(pWndMain->GetSafeHwnd(), pMenuPopUp->GetSafeHmenu(), 0, &rcItem);
	PrintRect(_T("Pop-up"), rcItem);
}


void CSkinCommCtrlView::PrintPoint(LPCTSTR pszText, POINT point)
{
	CString sLine;
	sLine.Format(_T("%s: %3d %3d\n"), pszText, point.x, point.y);
	PrintLine(sLine);
}

void CSkinCommCtrlView::PrintRect(LPCTSTR pszText, RECT rcItem)
{
	CString sLine;
	sLine.Format(_T("%s: %3d %3d %3d %3d\n"), pszText, rcItem.left, rcItem.top, rcItem.right, rcItem.bottom);
	PrintLine(sLine);
}


void CSkinCommCtrlView::PrintLine(LPCTSTR pszText)
{
	CEdit &wndEdit = GetEditCtrl();
	    
	int nLength = wndEdit.GetWindowTextLength();
	
	// Put the selection at the end of text
	wndEdit.SetSel(nLength, nLength); 
	
	// Replace the selection
    wndEdit.ReplaceSel(pszText);
}

/////////////////////////////////////////////////////////////////////////////
// CSkinCommCtrlView diagnostics

#ifdef _DEBUG
void CSkinCommCtrlView::AssertValid() const
{
	CEditView::AssertValid();
}

void CSkinCommCtrlView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CSkinCommCtrlDoc* CSkinCommCtrlView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSkinCommCtrlDoc)));
	return (CSkinCommCtrlDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSkinCommCtrlView message handlers
