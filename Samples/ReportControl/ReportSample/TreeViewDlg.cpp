// TreeViewDlg.cpp 
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
#include "TreeViewDlg.h"
#include "MessageRecord.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


const int COLUMN_MAIL_ICON   =  0;
const int COLUMN_CHECK_ICON  =  2;

/////////////////////////////////////////////////////////////////////////////
// CTreeViewDlg dialog


CTreeViewDlg::CTreeViewDlg(CWnd *pParent)
	: CDialog(CTreeViewDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTreeViewDlg)
	m_bNotificationExpanded = FALSE;
	//}}AFX_DATA_INIT
}


void CTreeViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTreeViewDlg)
	DDX_Control(pDX, IDC_REPORT, m_wndReport);
	DDX_Check(pDX, IDC_NOTIFICATION_EXPANDED, m_bNotificationExpanded);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTreeViewDlg, CDialog)
	//{{AFX_MSG_MAP(CTreeViewDlg)
	ON_BN_CLICKED(IDC_EXPAND,   OnExpand)
	ON_BN_CLICKED(IDC_COLLAPSE, OnCollapse)
	ON_BN_CLICKED(IDC_NOTIFICATION_EXPANDED, OnNotificationExpanded)
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_RCLICK, IDC_REPORT, OnReportRClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeViewDlg message handlers


BOOL CTreeViewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	int dpi = XTPDpiHelper()->GetDPIX();
	if(96 <= dpi && dpi < 120)
		VERIFY(m_wndReport.GetImageManager()->SetIcons(IDB_BMREPORT_16, 0, 0, CSize(16, 16)));
	else if (120 <= dpi && dpi < 144)
		VERIFY(m_wndReport.GetImageManager()->SetIcons(IDB_BMREPORT_20, 0, 0, CSize(20, 20)));
	else if (144 <= dpi && dpi < 192)
		VERIFY(m_wndReport.GetImageManager()->SetIcons(IDB_BMREPORT_24, 0, 0, CSize(24, 24)));
	else
		VERIFY(m_wndReport.GetImageManager()->SetIcons(IDB_BMREPORT_32, 0, 0, CSize(32, 32)));

	m_wndReport.ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_TABSTOP);
	m_wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReport.GetPaintManager()->m_nTreeIndent = XTP_DPI_X(10);
	
	ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS);

	//
	//  Add sample columns
	//
	m_wndReport.AddColumn(new CXTPReportColumn(COLUMN_ICON,    _T(""),         18, FALSE, COLUMN_MAIL_ICON));
	m_wndReport.AddColumn(new CXTPReportColumn(COLUMN_CHECK,   _T(""),         18, FALSE, COLUMN_CHECK_ICON));
	m_wndReport.AddColumn(new CXTPReportColumn(COLUMN_SUBJECT, _T("Subject"), 280));
	m_wndReport.AddColumn(new CXTPReportColumn(COLUMN_FROM,    _T("From"),    180));
	m_wndReport.AddColumn(new CXTPReportColumn(COLUMN_SENT,    _T("Sent"),    150));
	m_wndReport.AddColumn(new CXTPReportColumn(COLUMN_SIZE,    _T("Size"),     50));
	m_wndReport.AddColumn(new CXTPReportColumn(COLUMN_PRICE,   _T("Price"),    80));

	//
	//  Add sample records in tree
	//

	COleDateTime odtSent(COleDateTime::GetCurrentTime());
	COleDateTime odtCreated(COleDateTime::GetCurrentTime());
	COleDateTime odtReceived(COleDateTime::GetCurrentTime());
	CString strMessage(" ");
	CString strEmpty(" ");

	m_wndReport.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, FALSE, _T("postmaster@mail.codejock.com"), _T("Undeliverable Mail"), odtSent, 7, TRUE, 5,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage));   odtSent -= 0.8;
	m_wndReport.AddRecord(new CMessageRecord(msgImportanceLow, FALSE, FALSE, _T("Clark Kent"), _T("RE: Hi Louis"), odtSent, 14, FALSE, 4.3,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 0.8;
	CMessageRecord *pParentRec1 = new CMessageRecord(msgImportanceNormal, TRUE, TRUE, _T("Bruce Wayne"), _T("RE:"), odtSent, 24, FALSE, 56,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage); odtSent -= 0.8;
	m_wndReport.AddRecord(pParentRec1);
	pParentRec1->GetChilds()->Add(new CMessageRecord(msgImportanceHigh, TRUE, FALSE, _T("Peter Parker [pparker@codetoolbox.com]"), _T("Re: it's me again"), odtSent, 14, TRUE, 12.2,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 0.8;
	pParentRec1->GetChilds()->Add(new CMessageRecord(msgImportanceLow, FALSE, TRUE, _T("QueryReply"), _T("Re: it's me again"), odtSent, 13, FALSE, 1.345,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 0.8;
	CMessageRecord *pParentRec2 = new CMessageRecord(msgImportanceNormal, TRUE, FALSE, _T("Bruce Wayne"), _T("I don't understand:"), odtSent, 24, FALSE, 5.4321,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage); odtSent -= 0.8;
	pParentRec1->GetChilds()->Add(pParentRec2);
	pParentRec2->GetChilds()->Add(new CMessageRecord(msgImportanceHigh, FALSE, FALSE, _T("Programmers - www.codetoolbox.com"), _T("Am I a programmer?"), odtSent, 14, TRUE, 45,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 8;
	pParentRec2->GetChilds()->Add(new CMessageRecord(msgImportanceNormal, TRUE, FALSE, _T("Oswald Cobblepot"), _T("Yeah I know"), odtSent, 13, TRUE, 0.5,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 8;
	m_wndReport.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, TRUE, _T("postmaster@mail.codejock.com"), _T("Undeliverable Mail"), odtSent, 7, TRUE, 10,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 80;

//

	m_wndReport.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, FALSE, _T("postmaster@mail.codejock.com"), _T("Undeliverable Mail"), odtSent, 7, TRUE, 5,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage));   odtSent -= 0.8;
	m_wndReport.AddRecord(new CMessageRecord(msgImportanceLow, FALSE, FALSE, _T("Clark Kent"), _T("RE: Hi Louis"), odtSent, 14, FALSE, 4.3,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 0.8;
	pParentRec1 = new CMessageRecord(msgImportanceNormal, TRUE, TRUE, _T("Bruce Wayne"), _T("RE:"), odtSent, 24, FALSE, 56,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage); odtSent -= 0.8;
	m_wndReport.AddRecord(pParentRec1);
	pParentRec1->GetChilds()->Add(new CMessageRecord(msgImportanceHigh, TRUE, FALSE, _T("Peter Parker [pparker@codetoolbox.com]"), _T("Re: it's me again"), odtSent, 14, TRUE, 12.2,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 0.8;
	pParentRec1->GetChilds()->Add(new CMessageRecord(msgImportanceLow, FALSE, TRUE, _T("QueryReply"), _T("Re: it's me again"), odtSent, 13, FALSE, 1.345,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 0.8;
	pParentRec2 = new CMessageRecord(msgImportanceNormal, TRUE, FALSE, _T("Bruce Wayne"), _T("I don't understand:"), odtSent, 24, FALSE, 5.4321,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage); odtSent -= 0.8;
	pParentRec1->GetChilds()->Add(pParentRec2);
	pParentRec2->GetChilds()->Add(new CMessageRecord(msgImportanceHigh, FALSE, FALSE, _T("Programmers - www.codetoolbox.com"), _T("Am I a programmer?"), odtSent, 14, TRUE, 45,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 8;
	pParentRec2->GetChilds()->Add(new CMessageRecord(msgImportanceNormal, TRUE, FALSE, _T("Oswald Cobblepot"), _T("Yeah I know"), odtSent, 13, TRUE, 0.5,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 8;
	m_wndReport.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, TRUE, _T("postmaster@mail.codejock.com"), _T("Undeliverable Mail"), odtSent, 7, TRUE, 10,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 80;

	m_wndReport.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, FALSE, _T("postmaster@mail.codejock.com"), _T("Undeliverable Mail"), odtSent, 7, TRUE, 5,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage));   odtSent -= 0.8;
	m_wndReport.AddRecord(new CMessageRecord(msgImportanceLow, FALSE, FALSE, _T("Clark Kent"), _T("RE: Hi Louis"), odtSent, 14, FALSE, 4.3,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 0.8;
	pParentRec1 = new CMessageRecord(msgImportanceNormal, TRUE, TRUE, _T("Bruce Wayne"), _T("RE:"), odtSent, 24, FALSE, 56,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage); odtSent -= 0.8;
	m_wndReport.AddRecord(pParentRec1);
	pParentRec1->GetChilds()->Add(new CMessageRecord(msgImportanceHigh, TRUE, FALSE, _T("Peter Parker [pparker@codetoolbox.com]"), _T("Re: it's me again"), odtSent, 14, TRUE, 12.2,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 0.8;
	pParentRec1->GetChilds()->Add(new CMessageRecord(msgImportanceLow, FALSE, TRUE, _T("QueryReply"), _T("Re: it's me again"), odtSent, 13, FALSE, 1.345,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 0.8;
	pParentRec2 = new CMessageRecord(msgImportanceNormal, TRUE, FALSE, _T("Bruce Wayne"), _T("I don't understand:"), odtSent, 24, FALSE, 5.4321,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage); odtSent -= 0.8;
	pParentRec1->GetChilds()->Add(pParentRec2);
	pParentRec2->GetChilds()->Add(new CMessageRecord(msgImportanceHigh, FALSE, FALSE, _T("Programmers - www.codetoolbox.com"), _T("Am I a programmer?"), odtSent, 14, TRUE, 45,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 8;
	pParentRec2->GetChilds()->Add(new CMessageRecord(msgImportanceNormal, TRUE, FALSE, _T("Oswald Cobblepot"), _T("Yeah I know"), odtSent, 13, TRUE, 0.5,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 8;
	m_wndReport.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, TRUE, _T("postmaster@mail.codejock.com"), _T("Undeliverable Mail"), odtSent, 7, TRUE, 10,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 80;


	m_wndReport.GetColumns()->Find(COLUMN_SUBJECT)->SetTreeColumn(TRUE);

	// Populate all data on control
	m_wndReport.Populate();

	m_bNotificationExpanded = m_wndReport.GetBehavior()->Notifications->Row->bRowExpanded;
	UpdateData(FALSE);

	return FALSE;
}

void CTreeViewDlg::OnExpand()
{
	m_wndReport.ExpandAll(TRUE);
}

void CTreeViewDlg::OnCollapse()
{
	m_wndReport.CollapseAll();
}

void CTreeViewDlg::OnOK()
{
	CDialog::OnOK();
}

void CTreeViewDlg::OnNotificationExpanded() 
{
	UpdateData();
	m_wndReport.GetBehavior()->Notifications->Row->bRowExpanded = m_bNotificationExpanded;
}

void CTreeViewDlg::OnReportRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;
	
	if (pItemNotify->pRow)
	{
		TRACE(_T("Right click on row %d\n"), pItemNotify->pRow->GetIndex());
	}

}
