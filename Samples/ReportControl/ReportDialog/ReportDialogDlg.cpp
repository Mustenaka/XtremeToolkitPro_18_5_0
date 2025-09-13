// ReportDialogDlg.cpp
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
#include "ReportDialog.h"
#include "ReportDialogDlg.h"
#include "MessageRecord.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportDialogDlg dialog

CReportDialogDlg::CReportDialogDlg(CWnd* pParent /*=NULL*/)
	: CXTPResizeDialog(CReportDialogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReportDialogDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CReportDialogDlg::~CReportDialogDlg()
{
}

void CReportDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTPResizeDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportDialogDlg)
	DDX_Control(pDX, IDC_REPORTCTRL, m_wndReportCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CReportDialogDlg, CXTPResizeDialog)
	//{{AFX_MSG_MAP(CReportDialogDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportDialogDlg message handlers

enum
{
	COLUMN_IMPORTANCE,
	COLUMN_ICON,
	COLUMN_ATTACHMENT,
	COLUMN_FROM,
	COLUMN_SUBJECT,
	COLUMN_SENT,
	COLUMN_SIZE,
	COLUMN_CHECK,
	COLUMN_PRICE,
	COLUMN_CREATED,
	COLUMN_RECEIVED,
	COLUMN_CONVERSATION,
	COLUMN_CONTACTS,
	COLUMN_MESSAGE,
	COLUMN_CC,
	COLUMN_CATEGORIES,
	COLUMN_AUTOFORWARD,
	COLUMN_DO_NOT_AUTOARCH,
	COLUMN_DUE_BY,
};

const int COLUMN_MAIL_ICON   =  0;
const int COLUMN_CHECK_ICON  =  2;

BOOL CReportDialogDlg::OnInitDialog()
{
	CXTPResizeDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//
	//  Add images
	//
	int dpi = XTPDpiHelper()->GetDPIX();
	if(96 <= dpi && dpi < 120)
		VERIFY(m_wndReportCtrl.GetImageManager()->SetIcons(IDB_BMREPORT_16, 0, 0, CSize(16, 16)));
	else if (120 <= dpi && dpi < 144)
		VERIFY(m_wndReportCtrl.GetImageManager()->SetIcons(IDB_BMREPORT_20, 0, 0, CSize(20, 20)));
	else if (144 <= dpi && dpi < 192)
		VERIFY(m_wndReportCtrl.GetImageManager()->SetIcons(IDB_BMREPORT_24, 0, 0, CSize(24, 24)));
	else
		VERIFY(m_wndReportCtrl.GetImageManager()->SetIcons(IDB_BMREPORT_32, 0, 0, CSize(32, 32)));
	
	//
	//  Add sample columns
	//
	m_wndReportCtrl.AddColumn(new CXTPReportColumn(COLUMN_ICON, _T(""), 18, FALSE, COLUMN_MAIL_ICON));
	m_wndReportCtrl.AddColumn(new CXTPReportColumn(COLUMN_CHECK, _T(""), 18, FALSE, COLUMN_CHECK_ICON));
	m_wndReportCtrl.AddColumn(new CXTPReportColumn(COLUMN_SUBJECT, _T("Subject"), 280));
	m_wndReportCtrl.AddColumn(new CXTPReportColumn(COLUMN_FROM, _T("From"), 180));
	m_wndReportCtrl.AddColumn(new CXTPReportColumn(COLUMN_SENT, _T("Sent"), 150));
	m_wndReportCtrl.AddColumn(new CXTPReportColumn(COLUMN_SIZE, _T("Size"), 50));
	m_wndReportCtrl.AddColumn(new CXTPReportColumn(COLUMN_PRICE, _T("Price"), 80));

	//
	//  Add sample records in tree
	//

	COleDateTime odtSent(COleDateTime::GetCurrentTime());
	COleDateTime odtCreated(COleDateTime::GetCurrentTime());
	COleDateTime odtReceived(COleDateTime::GetCurrentTime());
	CString strMessage(" ");
	CString strEmpty(" ");

	m_wndReportCtrl.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, FALSE, _T("postmaster@mail.codejock.com"), _T("Undeliverable Mail"), odtSent, 7, TRUE, 5,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage));   odtSent -= 0.8;
	m_wndReportCtrl.AddRecord(new CMessageRecord(msgImportanceLow, FALSE, FALSE, _T("Clark Kent"), _T("RE: Hi Louis"), odtSent, 14, FALSE, 4.3,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 0.8;
	CMessageRecord *pParentRec1 = new CMessageRecord(msgImportanceNormal, TRUE, TRUE, _T("Bruce Wayne"), _T("RE:"), odtSent, 24, FALSE, 56,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage); odtSent -= 0.8;
	m_wndReportCtrl.AddRecord(pParentRec1);
	m_wndReportCtrl.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, TRUE, _T("postmaster@mail.codejock.com"), _T("Undeliverable Mail"), odtSent, 7, TRUE, 10,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 80;

	m_wndReportCtrl.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, FALSE, _T("postmaster@mail.codejock.com"), _T("Undeliverable Mail"), odtSent, 7, TRUE, 5,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage));   odtSent -= 0.8;
	m_wndReportCtrl.AddRecord(new CMessageRecord(msgImportanceLow, FALSE, FALSE, _T("Clark Kent"), _T("RE: Hi Louis"), odtSent, 14, FALSE, 4.3,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 0.8;
	pParentRec1 = new CMessageRecord(msgImportanceNormal, TRUE, TRUE, _T("Bruce Wayne"), _T("RE:"), odtSent, 24, FALSE, 56,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage); odtSent -= 0.8;
	m_wndReportCtrl.AddRecord(pParentRec1);
	m_wndReportCtrl.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, TRUE, _T("postmaster@mail.codejock.com"), _T("Undeliverable Mail"), odtSent, 7, TRUE, 10,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 80;

	m_wndReportCtrl.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, FALSE, _T("postmaster@mail.codejock.com"), _T("Undeliverable Mail"), odtSent, 7, TRUE, 5,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage));   odtSent -= 0.8;
	m_wndReportCtrl.AddRecord(new CMessageRecord(msgImportanceLow, FALSE, FALSE, _T("Clark Kent"), _T("RE: Hi Louis"), odtSent, 14, FALSE, 4.3,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 0.8;
	pParentRec1 = new CMessageRecord(msgImportanceNormal, TRUE, TRUE, _T("Bruce Wayne"), _T("RE:"), odtSent, 24, FALSE, 56,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage); odtSent -= 0.8;
	m_wndReportCtrl.AddRecord(pParentRec1);
	m_wndReportCtrl.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, TRUE, _T("postmaster@mail.codejock.com"), _T("Undeliverable Mail"), odtSent, 7, TRUE, 10,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 80;
	
	//
	// define style attributes for the report control.
	//
	
	m_wndReportCtrl.GetColumns()->Find(COLUMN_SUBJECT)->SetTreeColumn(TRUE);

	//
	// after columns and data have been added call Populate to 
	// populate all of the date for the control.
	//

	m_wndReportCtrl.Populate();

	m_wndReportCtrl.EnableDragDrop(_T("ReportDialog"), xtpReportAllowDrag | xtpReportAllowDrop);

#ifdef _XTP_INCLUDE_CONTROLS

	// Set control resizing.
	SetResize(IDC_REPORTCTRL, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDCANCEL, XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDOK, XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);
	
	// Load window placement
	LoadPlacement(_T("CReportDialogDlg"));

#endif

	// Set the appearance for the report control.
	m_wndReportCtrl.SetTheme(xtpReportThemeOfficeXP);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CReportDialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CXTPResizeDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CReportDialogDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CXTPResizeDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CReportDialogDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CReportDialogDlg::OnDestroy() 
{
	CXTPResizeDialog::OnDestroy();
	
#ifdef _XTP_INCLUDE_CONTROLS
	
	// Save window placement
	SavePlacement(_T("CReportDialogDlg"));
	
#endif
}
