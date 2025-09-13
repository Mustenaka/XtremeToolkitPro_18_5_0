// FolderView.cpp 
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
#include "Resource.h"
#include "ReportSampleDoc.h"
#include "FolderView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFolderView

IMPLEMENT_DYNCREATE(CFolderView, CXTPReportView)

BEGIN_MESSAGE_MAP(CFolderView, CXTPReportView)
	//{{AFX_MSG_MAP(CFolderView)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_DESTROY()
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFolderView construction/destruction

CFolderView::CFolderView()
{
}

CFolderView::~CFolderView()
{
}

BOOL CFolderView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CXTPReportView::PreCreateWindow(cs))
		return FALSE;

	//cs.dwExStyle |= WS_EX_STATICEDGE;
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CFolderView diagnostics

#ifdef _DEBUG
void CFolderView::AssertValid() const
{
	CXTPReportView::AssertValid();
}

void CFolderView::Dump(CDumpContext& dc) const
{
	CXTPReportView::Dump(dc);
}

CReportSampleDoc* CFolderView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CReportSampleDoc)));
	return (CReportSampleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReportSampleView message handlers


static const LPCTSTR Folder[] =
{
	_T("Deleted Items"),
	_T("Drafts"),
	_T("<TextBlock><Bold>Inbox</Bold> <Run Foreground='Blue' Text='(1)'/></TextBlock>"),
	_T("<TextBlock><Bold>Junk E-mail</Bold> <Run Foreground='Green' Text='[3]'/></TextBlock>"),
	_T("Outbox")
};


int CFolderView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CXTPReportView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CXTPReportControl &wndReport = GetReportCtrl();

	wndReport.ShowHeader(FALSE);
	wndReport.EnableMarkup(TRUE);

	CXTPReportColumn *pColumn = new CXTPReportColumn(0, _T("Folder"), 180);
	wndReport.AddColumn(pColumn);
	pColumn->SetTreeColumn(TRUE);

	CXTPReportRecord *pFolder;
	CXTPReportRecordItemText *pItem;

	pFolder = wndReport.AddRecord(new CXTPReportRecord());
	pItem   = new CXTPReportRecordItemText(_T("Personal Folders"));
	//pItem->SetIconIndex();
	pFolder->AddItem(pItem);

	for (int nFolder=0; nFolder<_countof(Folder); nFolder++)
	{
		CXTPReportRecord *pRecord = new CXTPReportRecord();
		pItem = new CXTPReportRecordItemText(_T(""));
		pRecord->AddItem(pItem);
		pFolder->GetChilds()->Add(pRecord);
		pItem->SetCaption(Folder[nFolder]);
	}

	wndReport.Populate();
	wndReport.ExpandAll();

#if _XTPLIB_VERSION_PREFIX >= 1520
	wndReport.GetPaintManager()->SetGridStyle(FALSE, xtpReportLineStyleNone);
#else
	wndReport.GetPaintManager()->SetGridStyle(FALSE, xtpReportGridNoLines);
#endif

#if _XTPLIB_VERSION_PREFIX >= 1511
	wndReport.GetPaintManager()->SetColumnStyle(xtpReportColumnResource);
#else
	wndReport.GetPaintManager()->SetColumnStyle(xtpReportColumnOffice2007);
#endif

	return 0;
}

void CFolderView::OnInitialUpdate()
{
	CXTPReportView::OnInitialUpdate();
}


// Before self destroying destroy all child forms 
void CFolderView::OnDestroy()
{
	CXTPReportView::OnDestroy();
}

void CFolderView::OnSetFocus(CWnd *pOldWnd)
{
	CXTPReportView::OnSetFocus(pOldWnd);

	GetReportCtrl().SetFocus();
}

void CFolderView::OnFilePrint()
{

}