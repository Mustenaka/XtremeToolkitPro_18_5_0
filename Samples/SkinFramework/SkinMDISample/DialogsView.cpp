// DialogsView.cpp
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
#include "skinmdisample.h"
#include "DialogsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogsView

IMPLEMENT_DYNCREATE(CDialogsView, CFormView)

CDialogsView::CDialogsView()
	: CFormView(CDialogsView::IDD)
{
	//{{AFX_DATA_INIT(CDialogsView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDialogsView::~CDialogsView()
{
}

void CDialogsView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogsView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogsView, CFormView)
	//{{AFX_MSG_MAP(CDialogsView)
	ON_BN_CLICKED(IDC_BUTTON_COLORDIALOG, OnButtonColordialog)
	ON_BN_CLICKED(IDC_BUTTON_FONTDIALOG, OnButtonFontdialog)
	ON_BN_CLICKED(IDC_BUTTON_PRINTDIALOG, OnButtonPrintdialog)
	ON_BN_CLICKED(IDC_BUTTON_OPENDIALOG, OnButtonOpendialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVEDIALOG, OnButtonSavedialog)
	ON_BN_CLICKED(IDC_BUTTON_BROWSEDIALOG, OnButtonBrowsedialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogsView diagnostics

#ifdef _DEBUG
void CDialogsView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDialogsView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDialogsView message handlers

void CDialogsView::OnButtonColordialog() 
{
	CColorDialog cd;
	cd.DoModal();
}

void CDialogsView::OnButtonFontdialog() 
{
	CFontDialog fd;
	fd.DoModal();
}

void CDialogsView::OnButtonPrintdialog() 
{
	CPrintDialog pd(TRUE);
	pd.DoModal();
}

void CDialogsView::OnButtonOpendialog() 
{
#if(WINVER >= 0x0400)
	DWORD dwFlags = OFN_EXPLORER;
#else
	DWORD dwFlags = 0;
#endif

	CFileDialog fd(TRUE, NULL, NULL, dwFlags, _T("Text Files (*.txt)|*.txt||All Files (*.*)|*.*||"));
	fd.DoModal();
}

void CDialogsView::OnButtonSavedialog()
{
#if(WINVER >= 0x0400)
	DWORD dwFlags = OFN_EXPLORER;
#else
	DWORD dwFlags = 0;
#endif

	CFileDialog fd(FALSE, NULL, NULL, dwFlags, _T("Text Files (*.txt)|*.txt||All Files (*.*)|*.*||"));
	fd.DoModal();
}

void CDialogsView::OnButtonBrowsedialog()
{
	TCHAR szPath[MAX_PATH + 1];
	BROWSEINFO bi = { 0 };
	bi.lpszTitle = _T("Test Folder Browsing");
	bi.pszDisplayName = szPath;
	bi.ulFlags = BIF_EDITBOX | BIF_VALIDATE | BIF_BROWSEINCLUDEFILES;
#if(WINVER >= 0x0501)
	bi.ulFlags |= BIF_USENEWUI;
#endif
	SHBrowseForFolder(&bi);
}

void CDialogsView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	ResizeParentToFit();
}
