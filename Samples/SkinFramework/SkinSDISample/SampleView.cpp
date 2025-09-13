// SampleView.cpp
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
#include "SkinSDISample.h"
#include "SampleView.h"
#include "Mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSampleView

IMPLEMENT_DYNCREATE(CSampleView, CFormView)

CSampleView::CSampleView()
	: CFormView(CSampleView::IDD)
{
	//{{AFX_DATA_INIT(CSampleView)
	m_nSkin = 0;
	m_nTheme = 1;
	m_strFind = _T("");
	m_bMatchCase = FALSE;
	m_bMatchWord = FALSE;
	m_bFlat = FALSE;
	m_bShowGripper = TRUE;
	//}}AFX_DATA_INIT
}

CSampleView::~CSampleView()
{
}

void CSampleView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSampleView)
	DDX_Radio(pDX, IDC_RADIO_LE5, m_nSkin);
	DDX_Radio(pDX, IDC_RADIO_OFFICE2003, m_nTheme);
	DDX_Text(pDX, IDC_EDIT_FIND, m_strFind);
	DDX_Check(pDX, IDC_CHECK_MATCHCASE, m_bMatchCase);
	DDX_Check(pDX, IDC_CHECK_MATCHWORD, m_bMatchWord);
	DDX_Check(pDX, IDC_CHECK_FLAT, m_bFlat);
	DDX_Check(pDX, IDC_CHECK_GRIPPER, m_bShowGripper);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSampleView, CFormView)
	//{{AFX_MSG_MAP(CSampleView)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnButtonFind)
	ON_BN_CLICKED(IDC_BUTTON_COLORDIALOG, OnButtonColordialog)
	ON_BN_CLICKED(IDC_BUTTON_FONTDIALOG, OnButtonFontdialog)
	ON_BN_CLICKED(IDC_BUTTON_PRINTDIALOG, OnButtonPrintdialog)
	ON_BN_CLICKED(IDC_BUTTON_OPENDIALOG, OnButtonOpendialog)
	ON_BN_CLICKED(IDC_BUTTON_BROWSEDIALOG, OnButtonBrowsedialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVEDIALOG, OnButtonSavedialog)
	ON_BN_CLICKED(IDC_RADIO_LE5, OnSkinChanged)
	ON_BN_CLICKED(IDC_RADIO_OFFICE2003, OnThemeChanged)
	ON_BN_CLICKED(IDC_CHECK_FLAT, OnThemeChanged)
	ON_BN_CLICKED(IDC_RADIO_ITUNES, OnSkinChanged)
	ON_BN_CLICKED(IDC_RADIO_DEFAULT, OnSkinChanged)
	ON_BN_CLICKED(IDC_RADIO_WINXP, OnThemeChanged)
	ON_EN_CHANGE(IDC_EDIT_FIND, OnChangeEditFind)
	ON_BN_CLICKED(IDC_CHECK_GRIPPER, OnCheckGripper)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSampleView diagnostics

#ifdef _DEBUG
void CSampleView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSampleView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSampleView message handlers

void CSampleView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

#ifndef _XTP_INCLUDE_COMMANDBARS
	GetDlgItem(IDC_CHECK_GRIPPER)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_FLAT)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO_OFFICE2003)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO_WINXP)->EnableWindow(FALSE);
#endif
}


void CSampleView::OnButtonFind() 
{
	UpdateData();

	CMainFrame* pWnd = (CMainFrame*)AfxGetMainWnd();
	CRichEditView* pView = (CRichEditView*)pWnd->m_wndSplitter.GetPane(0, 1);	
	
	if (!pView->FindText(m_strFind, m_bMatchCase, m_bMatchWord))
	{
		pView->TextNotFound(m_strFind);
	}
	
}
void CSampleView::OnChangeEditFind() 
{
	UpdateData();

	GetDlgItem(IDC_BUTTON_FIND)->EnableWindow(!m_strFind.IsEmpty());
}


void CSampleView::OnButtonColordialog() 
{
	CColorDialog cd;
	cd.DoModal();
	
}

void CSampleView::OnButtonFontdialog() 
{
	CFontDialog fd;
	fd.DoModal();
	
}

void CSampleView::OnButtonPrintdialog() 
{
	CPrintDialog pd(TRUE);
	pd.DoModal();
	
}

struct OPENFILENAMEEX
{
	void*  pvReserved; // 4 bytes
	DWORD  dwReserved; // 4 bytes
	DWORD  FlagsEx;    // 4 bytes
};

void CSampleView::OnButtonOpendialog() 
{
#if(WINVER >= 0x0400)
	DWORD dwFlags = OFN_EXPLORER;
#else
	DWORD dwFlags = 0;
#endif

	CFileDialog fd(TRUE, NULL, NULL, dwFlags, _T("Text Files (*.txt)|*.txt||All Files (*.*)|*.*||"));
	fd.DoModal();
}

void CSampleView::OnButtonBrowsedialog()
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

void CSampleView::OnButtonSavedialog()
{
#if(WINVER >= 0x0400)
	DWORD dwFlags = OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;
#else
	DWORD dwFlags = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;
#endif

	CFileDialog fd(FALSE, NULL, NULL, dwFlags, _T("Text Files (*.txt)|*.txt||All Files (*.*)|*.*||"));
	fd.DoModal();
}

void CSampleView::OnSkinChanged() 
{
	UpdateData();
	CMainFrame* pWnd = (CMainFrame*)AfxGetMainWnd();
	pWnd->LoadSkin(m_nSkin);	
}

void CSampleView::OnThemeChanged() 
{
	UpdateData();

	CMainFrame* pWnd = (CMainFrame*)AfxGetMainWnd();
	pWnd->SetTheme(m_nTheme, m_bFlat);
}

void CSampleView::OnCheckGripper()
{
	UpdateData();
	CMainFrame* pWnd = (CMainFrame*)AfxGetMainWnd();

#ifdef _XTP_INCLUDE_COMMANDBARS
	pWnd->GetCommandBars()->GetAt(0)->SetShowGripper(m_bShowGripper);
	pWnd->GetCommandBars()->GetAt(1)->SetShowGripper(m_bShowGripper);
	pWnd->GetCommandBars()->RedrawCommandBars();
#endif
}
 

