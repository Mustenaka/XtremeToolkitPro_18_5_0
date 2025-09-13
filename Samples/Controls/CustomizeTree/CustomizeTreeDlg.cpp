// CustomizeTreeDlg.cpp
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
#include "CustomizeTree.h"
#include "CustomizeTreeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CCustomizeTreeDlg dialog

CCustomizeTreeDlg::CCustomizeTreeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomizeTreeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCustomizeTreeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCustomizeTreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomizeTreeDlg)
	DDX_Control(pDX, IDC_TREE_CUSTOMIZE, m_wndTreeCustomize);
	DDX_Control(pDX, IDC_TREE_ITEMS, m_wndTreeItems);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCustomizeTreeDlg, CDialog)
	//{{AFX_MSG_MAP(CCustomizeTreeDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomizeTreeDlg message handlers

BOOL CCustomizeTreeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// AddItem "About..." menu item to system menu.

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





#if 0
	// 100000 items test

	m_wndTreeCustomize.SetLockRedraw(TRUE);
	for (int i = 0; i < 100000; i++)
	{
		CString s;
		s.Format(_T("%d"), i);
		CXTPCoreTreeItem* pItem = m_wndTreeCustomize.GetItems()->AddItem(s);
	}
	m_wndTreeCustomize.SetLockRedraw(FALSE);
#endif

	//////////////////////////////////////////////////////////////////////////
	// m_wndTreeCustomize
	
	m_wndTreeCustomize.SetFont(CWnd::GetFont());
	m_wndTreeCustomize.GetImageManager()->SetIcons(IDR_TREEICONS);

	m_wndTreeCustomize.SetLockRedraw(TRUE);

	CXTPCoreTreeItem* pLabelMainTabs = m_wndTreeCustomize.GetItems()->AddItem(_T("Main Tabs"));
	pLabelMainTabs->SetLabel(TRUE);
	
	CXTPCoreTreeItem* pItemHome = m_wndTreeCustomize.GetItems()->AddItem(_T("Home"));
	pItemHome->ShowCheckbox();

	CXTPCoreTreeItem* pItemClipboard = pItemHome->GetChildren()->AddItem(_T("Clipboard"));
	CXTPCoreTreeItem* pItemPaste = pItemClipboard->GetChildren()->AddItem(_T("Paste"));
	pItemPaste->SetEnabled(FALSE);
	pItemPaste->SetIconId(ID_EDIT_PASTE);

	CXTPCoreTreeItem* pItemCut = pItemClipboard->GetChildren()->AddItem(_T("Cut"));
	pItemCut->SetEnabled(FALSE);
	pItemCut->SetIconId(ID_EDIT_CUT);

	CXTPCoreTreeItem* pItemCopy = pItemClipboard->GetChildren()->AddItem(_T("Copy"));
	pItemCopy->SetEnabled(FALSE);
	pItemCopy->SetIconId(ID_EDIT_COPY);

	pItemClipboard->SetExpanded(TRUE);
	pItemHome->SetExpanded(TRUE);

	CXTPCoreTreeItem* pItemFont = pItemHome->GetChildren()->AddItem(_T("Font"));
	pItemFont->GetChildren()->AddItem(_T("Font"));
	pItemFont->GetChildren()->AddItem(_T("Font Size"));
	pItemFont->GetChildren()->AddItem(_T("Grow Font"));
	pItemFont->GetChildren()->AddItem(_T("Shrink Font"));
	pItemFont->GetChildren()->AddItem(_T("Change Case"));
	

	CXTPCoreTreeItem* pLabelSmartArt = m_wndTreeCustomize.GetItems()->AddItem(_T("SmartArt Tools"));
	pLabelSmartArt->SetLabel(TRUE);

	CXTPCoreTreeItem* pItemDesign =  m_wndTreeCustomize.GetItems()->AddItem(_T("Design"));
	pItemDesign->ShowCheckbox();

	CXTPCoreTreeItem* pLabelChartTools = m_wndTreeCustomize.GetItems()->AddItem(_T("Chart Tools"));
	pLabelChartTools->SetLabel(TRUE);

	pItemDesign = m_wndTreeCustomize.GetItems()->AddItem(_T("Design"));
	pItemDesign->ShowCheckbox();

	pItemDesign->GetChildren()->AddItem(_T("Type"));
	pItemDesign->GetChildren()->AddItem(_T("Data"));


	CXTPCoreTreeItem* pItemLayout =m_wndTreeCustomize.GetItems()->AddItem(_T("Layout"));
	pItemLayout->ShowCheckbox();

	pItemLayout->GetChildren()->AddItem(_T("Current Selection"));
	pItemLayout->GetChildren()->AddItem(_T("Insert"));
	pItemLayout->GetChildren()->AddItem(_T("Labels"));
	pItemLayout->GetChildren()->AddItem(_T("Axes"));

	CXTPCoreTreeItem* pItemFormat = m_wndTreeCustomize.GetItems()->AddItem(_T("Format"));
	pItemFormat->ShowCheckbox();

	m_wndTreeCustomize.SetLockRedraw(FALSE);

#ifdef _XTP_INCLUDE_MARKUP
	
	m_wndTreeCustomize.EnableMarkup();
	
	pItemFormat->GetChildren()->AddItem(_T("<TextBlock VerticalAlignment='Center'><Bold>Markup Item</Bold> <Run Foreground='Blue'>(1)</Run></TextBlock>"));
	
	
#endif

	//////////////////////////////////////////////////////////////////////////
	// m_wndTreeItems
	
	m_wndTreeItems.SetFont(CWnd::GetFont());
	m_wndTreeItems.GetImageManager()->SetIcons(IDR_TREEICONS);

	m_wndTreeItems.SetLockRedraw(TRUE);
	
	pItemPaste = m_wndTreeItems.GetItems()->AddItem(_T("Paste"));
	pItemPaste->SetIconId(ID_EDIT_PASTE);
	
	pItemCut = m_wndTreeItems.GetItems()->AddItem(_T("Cut"));
	pItemCut->SetIconId(ID_EDIT_CUT);
	
	pItemCopy = m_wndTreeItems.GetItems()->AddItem(_T("Copy"));
	pItemCopy->SetIconId(ID_EDIT_COPY);

	CXTPCoreTreeItem* pItem = m_wndTreeItems.GetItems()->AddItem(_T("New"));
	pItem->SetIconId(ID_FILE_NEW);

	pItem = m_wndTreeItems.GetItems()->AddItem(_T("Save"));
	pItem->SetIconId(ID_FILE_SAVE);

	pItem = m_wndTreeItems.GetItems()->AddItem(_T("Print"));
	pItem->SetIconId(ID_FILE_PRINT);

	m_wndTreeItems.SetLockRedraw(FALSE);

	m_wndTreeItems.m_bItemsTree = TRUE;
	m_wndTreeItems.GetPaintManager()->m_bShowButtons = FALSE;


	
	// TODO: AddItem extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCustomizeTreeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCustomizeTreeDlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCustomizeTreeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
