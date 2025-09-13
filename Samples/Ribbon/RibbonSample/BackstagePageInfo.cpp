// BackstagePageInfo.cpp
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
#include "MainFrm.h"
#include "BackstagePageInfo.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBackstagePageInfo dialog


CBackstagePageInfo::CBackstagePageInfo()
	: CXTPRibbonBackstagePage(CBackstagePageInfo::IDD)
{
	//{{AFX_DATA_INIT(CBackstagePageInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CBackstagePageInfo::SetImages(XTPControlTheme nTheme)
{
	m_imagelist.RemoveAll();

	if (nTheme == xtpControlThemeOffice2013)
	{
		UINT nIDs[] = {IDC_BUTTON_PROTECTDOCUMENT, IDC_BUTTON_CHECKFORISSUE, IDC_BUTTON_MANAGEVERSIONS, 0,0,0,0,0,0,0};
		m_imagelist.SetIcons(IDB_BITMAP_OFFICE2013_BACKSTAGE_32, nIDs, 10, CSize(32, 32), xtpImageNormal);
	}
	else
	{
		UINT nID1[] = {IDC_BUTTON_PROTECTDOCUMENT}; m_imagelist.SetIcons(IDC_BUTTON_PROTECTDOCUMENT, nID1, 1, CSize(32, 32), xtpImageNormal);
		UINT nID2[] = {IDC_BUTTON_CHECKFORISSUE  }; m_imagelist.SetIcons(IDC_BUTTON_CHECKFORISSUE  , nID2, 1, CSize(32, 32), xtpImageNormal);
		UINT nID3[] = {IDC_BUTTON_MANAGEVERSIONS }; m_imagelist.SetIcons(IDC_BUTTON_MANAGEVERSIONS , nID3, 1, CSize(32, 32), xtpImageNormal);
	}
}

void CBackstagePageInfo::DoDataExchange(CDataExchange* pDX)
{
	CXTPRibbonBackstagePage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBackstagePageInfo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_SEPARATOR_1, m_lblSeparator1);
	DDX_Control(pDX, IDC_SEPARATOR_2, m_lblSeparator2);
	DDX_Control(pDX, IDC_SEPARATOR_3, m_lblSeparator3);
	DDX_Control(pDX, IDC_SEPARATOR_4, m_lblSeparator4);

	DDX_Control(pDX, IDC_LABEL_CAPTION, m_lblInformation);

	DDX_Control(pDX, IDC_LABEL_PERMISSIONS, m_lblPermissions);
	DDX_Control(pDX, IDC_LABEL_PREPAREFORSHARING, m_lblPrepareForSharing);
	DDX_Control(pDX, IDC_LABEL_VERSIONS, m_lblVersions);
	
	DDX_Control(pDX, IDC_BUTTON_PROTECTDOCUMENT, m_btnProtectDocument);
	DDX_Control(pDX, IDC_BUTTON_CHECKFORISSUE, m_btnCheckForIssues);
	DDX_Control(pDX, IDC_BUTTON_MANAGEVERSIONS, m_btnManageVersions);
}


BEGIN_MESSAGE_MAP(CBackstagePageInfo, CXTPRibbonBackstagePage)
	//{{AFX_MSG_MAP(CBackstagePageInfo)
	ON_BN_CLICKED(IDC_STATIC_PREVIEW, OnStaticPreview)
	//}}AFX_MSG_MAP
	ON_CBN_DROPDOWN(IDC_BUTTON_PROTECTDOCUMENT, OnProtectDocumentDropDown)
	ON_CBN_DROPDOWN(IDC_BUTTON_CHECKFORISSUE, OnCheckForIssuesDropDown)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBackstagePageInfo message handlers

void CBackstagePageInfo::InitButton(UINT nID, BOOL bPopup)
{
	CXTPRibbonBackstageButton* pButton = (CXTPRibbonBackstageButton*)GetDlgItem(nID);

	pButton->SetTextImageRelation(xtpButtonImageAboveText);
	pButton->ShowShadow(TRUE);
	
	if (bPopup)
	{
		pButton->EnableMarkup(TRUE);
		
		CString strWindowText;
		pButton->GetWindowText(strWindowText);
		
		CString strText;
		strText.Format(_T("<TextBlock Margin='5, 0, 5, 0' TextWrapping='Wrap' TextAlignment='Center'>%s <InlineUIContainer BaselineAlignment='Center'><Image Source='res://XTP_IDB_BUTTONDROPDOWNGLYPH'/></InlineUIContainer></TextBlock>"), (LPCTSTR)strWindowText);
		
		pButton->SetWindowText(strText);
		
		pButton->SetPushButtonStyle(xtpButtonDropDownNoGlyph);
	}
}

void CBackstagePageInfo::ReinitButton(UINT nID, BOOL /*bPopup*/)
{
	CXTPRibbonBackstageButton* pButton = (CXTPRibbonBackstageButton*)GetDlgItem(nID);
	pButton->SetTheme(GetTheme());
	
	UINT nIDIcon = pButton->GetDlgCtrlID();
	CXTPImageManagerIcon* pIcon = m_imagelist.GetImage(nIDIcon);
	ASSERT(pIcon);
	if (pIcon)
	{
		pButton->SetIcon(pIcon->GetExtent(), pIcon);
		pIcon->InternalAddRef();
	}
}

BOOL CBackstagePageInfo::OnInitDialog() 
{
	CXTPRibbonBackstagePage::OnInitDialog();

	ModifyStyleEx(0, WS_EX_CONTROLPARENT);

	m_lblInformation.SetFont(&m_xtpFontTitle);
	m_lblPermissions.SetFont(&m_xtpFontCaption);
	m_lblPrepareForSharing.SetFont(&m_xtpFontCaption);
	m_lblVersions.SetFont(&m_xtpFontCaption);

	m_lblSeparator4.SetVerticalStyle(TRUE);

	InitButton(IDC_BUTTON_PROTECTDOCUMENT, TRUE);
	InitButton(IDC_BUTTON_CHECKFORISSUE, TRUE);
	InitButton(IDC_BUTTON_MANAGEVERSIONS, FALSE);

	SetResize(IDC_SEPARATOR_1, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_SEPARATOR_2, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_SEPARATOR_3, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_SEPARATOR_4, XTP_ANCHOR_TOPRIGHT, XTP_ANCHOR_BOTTOMRIGHT);

	SetResize(IDC_STATIC_PREVIEW, XTP_ANCHOR_TOPRIGHT, XTP_ANCHOR_TOPRIGHT);
	

	SetResize(IDC_TEXT1, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_TEXT2, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_TEXT3, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBackstagePageInfo::SetTheme(XTPControlTheme nTheme)
{
	CXTPRibbonBackstagePage::SetTheme(nTheme);
	SetImages(nTheme);
	
	m_lblInformation.SetTheme(nTheme);

	m_lblPermissions.SetTheme(nTheme);
	m_lblPrepareForSharing.SetTheme(nTheme);
	m_lblVersions.SetTheme(nTheme);

	m_lblSeparator1.SetTheme(nTheme);
	m_lblSeparator2.SetTheme(nTheme);
	m_lblSeparator3.SetTheme(nTheme);
	m_lblSeparator4.SetTheme(nTheme);
	
	ReinitButton(IDC_BUTTON_PROTECTDOCUMENT, TRUE);
	ReinitButton(IDC_BUTTON_CHECKFORISSUE, TRUE);
	ReinitButton(IDC_BUTTON_MANAGEVERSIONS, FALSE);
}

void CBackstagePageInfo::OnProtectDocumentDropDown()
{

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	CXTPPopupBar* pPopupBar = CXTPPopupBar::CreatePopupBar(pMainFrame->GetCommandBars());
	pPopupBar->SetDefaultButtonStyle(xtpButtonCaptionAndDescription);
	pPopupBar->SetShowGripper(FALSE);
	pPopupBar->SetIconSize(CSize(32, 32));

	pPopupBar->GetControls()->Add(xtpControlButton, IDS_PROTECT_MARK_AS_FINAL);
	pPopupBar->GetControls()->Add(xtpControlButton, IDS_PROTECT_ENCRYPT);


	UINT nIDs[] = {IDS_PROTECT_ENCRYPT};
	XTPImageManager()->SetIcons(IDC_BUTTON_PROTECTDOCUMENT, nIDs, 1, CSize(0, 0), xtpImageNormal);


	CXTPWindowRect rcButton(GetDlgItem(IDC_BUTTON_PROTECTDOCUMENT));
	UINT nID = pMainFrame->GetCommandBars()->TrackPopupMenu(pPopupBar, TPM_RETURNCMD | TPM_NONOTIFY, rcButton.left, rcButton.bottom, this);
	switch(nID)
	{
	case IDS_PROTECT_MARK_AS_FINAL:
		AfxMessageBox(_T("Mark as Final"));
		break;
	case IDS_PROTECT_ENCRYPT:
		AfxMessageBox(_T("Encrypt with Password"));
		break;
	}


	pPopupBar->InternalRelease();
}

void CBackstagePageInfo::OnCheckForIssuesDropDown()
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	
	CXTPPopupBar* pPopupBar = CXTPPopupBar::CreatePopupBar(pMainFrame->GetCommandBars());
	pPopupBar->SetDefaultButtonStyle(xtpButtonCaptionAndDescription);
	pPopupBar->SetShowGripper(FALSE);
	
	pPopupBar->GetControls()->Add(xtpControlButton, IDS_CHECK_INSPECT_DOCUMENT);
	pPopupBar->GetControls()->Add(xtpControlButton, IDS_CHECK_ACCESSIBILITY);
	
	CXTPWindowRect rcButton(GetDlgItem(IDC_BUTTON_CHECKFORISSUE));	
	UINT nID = pMainFrame->GetCommandBars()->TrackPopupMenu(pPopupBar, TPM_RETURNCMD | TPM_NONOTIFY, rcButton.left, rcButton.bottom, this);
	switch(nID)
	{
	case IDS_CHECK_INSPECT_DOCUMENT:
		AfxMessageBox(_T("Inspect Document"));
		break;
	case IDS_CHECK_ACCESSIBILITY:
		AfxMessageBox(_T("Check Accessibility"));
		break;
	}
	
	
	pPopupBar->InternalRelease();
}

void CBackstagePageInfo::OnStaticPreview() 
{	
	CXTPRibbonBackstageView* pView = (CXTPRibbonBackstageView*)GetParent();

	pView->OnCancel();
}
