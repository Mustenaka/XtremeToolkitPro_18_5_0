// MarkupPage.cpp
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
#include "button.h"
#include "MarkupPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMarkupPage property page

IMPLEMENT_DYNCREATE(CMarkupPage, CPropertyPage)

CMarkupPage::CMarkupPage() : CPropertyPage(CMarkupPage::IDD)
{
	//{{AFX_DATA_INIT(CMarkupPage)
	//}}AFX_DATA_INIT
}

CMarkupPage::~CMarkupPage()
{
}

void CMarkupPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMarkupPage)
	DDX_Control(pDX, IDC_RADIO_WITHLINK, m_btnRadioWithLink);
	DDX_Control(pDX, IDC_CHECK_DELETEOUTBOX, m_btnDeleteOutbox);
	DDX_Control(pDX, IDC_CHECK_DELETEINBOX, m_btnDeleteInbox);
	DDX_Control(pDX, IDC_BUTTON_FIREWALL, m_btnFirewall);
	DDX_Control(pDX, IDC_BUTTON_MARKUP, m_btnPushButton);
	DDX_Control(pDX, IDC_RADIO_MARKUP, m_btnRadio);
	DDX_Control(pDX, IDC_CHECK_MARKUP, m_btnCheckBox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMarkupPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMarkupPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMarkupPage message handlers

BOOL CMarkupPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
#ifdef _XTP_INCLUDE_MARKUP
	m_btnCheckBox.EnableMarkup();
	m_btnRadio.EnableMarkup();
	m_btnPushButton.EnableMarkup();
	m_btnFirewall.EnableMarkup();
	m_btnDeleteInbox.EnableMarkup();
	m_btnDeleteOutbox.EnableMarkup();
	m_btnRadioWithLink.EnableMarkup();

	m_btnFirewall.SetWindowText(
		_T("<StackPanel Orientation='Horizontal'>")
		_T("<Image Source='res://glyph.bmp' VerticalAlignment='Center'/>")
		_T("<StackPanel Margin='5, 0, 0, 0'>")
 		 _T("<TextBlock Foreground='#151c55' FontSize='18'>Turn on Firewall now</TextBlock>")
 	 	 _T("<TextBlock FontSize='11'>(recommended)</TextBlock>")
		_T("</StackPanel>")
		_T("</StackPanel>"));

	m_btnDeleteInbox.SetWindowText(
		_T("<TextBlock><Run FontWeight='Bold'>Delete Inbox </Run> <Run Foreground='Blue'>[10 Items]</Run></TextBlock>"));

	m_btnDeleteOutbox.SetWindowText(
		_T("<TextBlock><Run FontWeight='Bold'>Delete Outbox </Run> <Run Foreground='Green'>[14 Items]</Run></TextBlock>"));

	m_btnDeleteOutbox.SetWindowText(
		_T("<TextBlock><Run FontWeight='Bold'>Delete Outbox </Run> <Run Foreground='Green'>[14 Items]</Run></TextBlock>"));

	m_btnDeleteOutbox.SetWindowText(
		_T("<TextBlock><Run FontWeight='Bold'>Delete Outbox </Run> <Run Foreground='Green'>[14 Items]</Run></TextBlock>"));

	m_btnRadioWithLink.SetWindowText(
		_T("<TextBlock>Radio Button with <Hyperlink>Hyperlink</Hyperlink></TextBlock>"));

	m_btnRadioWithLink.GetMarkupContext()->AddHandler(CXTPMarkupHyperlink::m_pClickEvent, 
		CreateMarkupClassDelegate(this, &CMarkupPage::OnHyperlinkClick));
#endif

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
	
#ifdef _XTP_INCLUDE_MARKUP

void CMarkupPage::OnHyperlinkClick(CXTPMarkupObject* pSender, CXTPMarkupRoutedEventArgs* pArgs)
{
	if (pSender->IsKindOf(MARKUP_TYPE(CXTPMarkupHyperlink)))
	{
		AfxMessageBox(_T("Hyperlink Clicked"));
		pArgs->SetHandled();
	}
}

#endif