// TagCloudDlg.cpp : implementation file
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
#include "TagCloud.h"
#include "TagCloudDlg.h"
#include "EditStyleDlg.h"
#include "EditTagDlg.h"
#include "EditTagCloudDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTagCloudDlg dialog

CTagCloudDlg::CTagCloudDlg(CWnd* pParent /*=NULL*/)
	: CXTPResizeDialog(CTagCloudDlg::IDD, pParent), m_nSelItem(-1), m_pSelTag(NULL)
{
	//{{AFX_DATA_INIT(CTagCloudDlg)
	m_bFocus = FALSE;
	m_bTooltip = FALSE;
	m_nSort = 0;
	m_bAsc = TRUE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTagCloudDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTPResizeDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTagCloudDlg)
	DDX_Control(pDX, IDC_GBOX_CONTROL, m_gboxControl);
	DDX_Control(pDX, IDC_GBOX_TAG, m_gboxTag);
	DDX_Control(pDX, IDC_GBOX_STYLES, m_gboxStyles);
	DDX_Control(pDX, IDC_CHK_CONTROL_ASC, m_chkAsc);
	DDX_Control(pDX, IDC_BTN_TAG_DELETE, m_btnTagDelete);
	DDX_Control(pDX, IDC_BTN_TAG_EDIT, m_btnTagEdit);
	DDX_Control(pDX, IDC_BTN_STYLES_DELETE, m_btnStylesDelete);
	DDX_Control(pDX, IDC_BTN_STYLES_EDIT, m_btnStylesEdit);
	DDX_Control(pDX, IDC_LIST_STYLES, m_wndStyleList);
	DDX_Control(pDX, IDC_TAGCLOUD_FRAME, m_wndPlaceHolder);
	DDX_Check(pDX, IDC_CHK_CONTROL_FOCUS, m_bFocus);
	DDX_Check(pDX, IDC_CHK_CONTROL_TOOLTIP, m_bTooltip);
	DDX_Check(pDX, IDC_CHK_CONTROL_ASC, m_bAsc);
	DDX_CBIndex(pDX, IDC_COMBO_CONTROL_SORT, m_nSort);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTagCloudDlg, CXTPResizeDialog)
	//{{AFX_MSG_MAP(CTagCloudDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHK_CONTROL_TOOLTIP, OnChkTooltip)
	ON_BN_CLICKED(IDC_CHK_CONTROL_FOCUS, OnChkFocus)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_STYLES, OnItemChangedListStyles)
	ON_COMMAND(ID_TAG_EDITTAG, OnTagEditTag)
	ON_COMMAND(ID_TAG_ADDTAG, OnTagAddTag)
	ON_COMMAND(ID_TAG_DELETETAG, OnTagDeleteTag)
	ON_BN_CLICKED(IDC_BTN_STYLES_EDIT, OnBtnStylesEdit)
	ON_BN_CLICKED(IDC_BTN_STYLES_ADD, OnBtnStylesAdd)
	ON_BN_CLICKED(IDC_BTN_STYLES_DELETE, OnBtnStylesDelete)
	ON_BN_CLICKED(IDC_BTN_TAG_EDIT, OnBtnTagEdit)
	ON_BN_CLICKED(IDC_BTN_TAG_ADD, OnBtnTagAdd)
	ON_BN_CLICKED(IDC_BTN_TAG_DELETE, OnBtnTagDelete)
	ON_CBN_SELENDOK(IDC_COMBO_CONTROL_SORT, OnSelendOkComboControlSort)
	ON_BN_CLICKED(IDC_BTN_CONTROL_COLORS, OnBtnControlColors)
	ON_BN_CLICKED(IDC_BTN_CONTROL_RESET, OnBtnControlReset)
	ON_COMMAND(ID_CONTROL_TOOLTIP, OnControlTooltip)
	ON_COMMAND(ID_CONTROL_FOCUS, OnControlFocus)
	ON_COMMAND(ID_CONTROL_SORTORDER_NONE, OnControlSortOrderNone)
	ON_COMMAND(ID_CONTROL_SORTORDER_BYNAME, OnControlSortOrderByName)
	ON_COMMAND(ID_CONTROL_SORTORDER_BYSCORE, OnControlSortOrderByScore)
	ON_COMMAND(ID_CONTROL_EDITCLOUDCOLORS, OnControlEditCloudColors)
	ON_COMMAND(ID_CONTROL_RESETALL, OnControlResetAll)
	ON_BN_CLICKED(IDC_CHK_CONTROL_ASC, OnChkControlAsc)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_STYLES, OnDblClkListStyles)
	ON_WM_INITMENUPOPUP()
	ON_UPDATE_COMMAND_UI(ID_CONTROL_TOOLTIP, OnUpdateControlTooltip)
	ON_UPDATE_COMMAND_UI(ID_CONTROL_FOCUS, OnUpdateControlFocus)
	ON_UPDATE_COMMAND_UI(ID_CONTROL_SORTORDER_NONE, OnUpdateControlSortOrderNone)
	ON_UPDATE_COMMAND_UI(ID_CONTROL_SORTORDER_BYNAME, OnUpdateControlSortOrderByName)
	ON_UPDATE_COMMAND_UI(ID_CONTROL_SORTORDER_BYSCORE, OnUpdateControlSortOrderByScore)
	ON_COMMAND(ID_CONTROL_SORTORDER_ASCENDING, OnControlSortOrderAscending)
	ON_UPDATE_COMMAND_UI(ID_CONTROL_SORTORDER_ASCENDING, OnUpdateControlSortOrderAscending)
	//}}AFX_MSG_MAP
	ON_WM_XTP_TAGCLOUDSELCHANGE()
	ON_WM_XTP_TAGCLOUDRIGHTCLK()
	ON_WM_XTP_TAGCLOUDDBLCLK()
END_MESSAGE_MAP()

static LPCTSTR tagName[] =
{
	_T("appetizer"),
	_T("avocado"),
	_T("bacon"),
	_T("baked"),
	_T("beef"),
	_T("blue cheese"),
	_T("buttermilk"),
	_T("chicken"),
	_T("CSA"),
	_T("farmers"),
	_T("market"),
	_T("greenmarket"),
	_T("grill"),
	_T("grilled"),
	_T("homegrown"),
	_T("ice"),
	_T("Italian"),
	_T("lobster"),
	_T("localvore"),
	_T("mail corse"),
	_T("maple syrup"),
	_T("mashed"),
	_T("Mediterranean"),
	_T("Mexican"),
	_T("mozzerella"),
	_T("no-cook"),
	_T("oven"),
	_T("pasta"),
	_T("pork"),
	_T("potatoes"),
	_T("prosciutto"),
	_T("roasted"),
	_T("roasting"),
	_T("seafood"),
	_T("shellfish"),
	_T("side dish"),
	_T("snack"),
	_T("soup"),
	_T("stove top"),
	_T("sustainable"),
	_T("sweet"),
	_T("potatoes"),
	_T("tomatoes"),
	_T("turkey"),
	_T("walnuts"),
};

/////////////////////////////////////////////////////////////////////////////
// CTagCloudDlg message handlers

BOOL CTagCloudDlg::OnInitDialog()
{
	CXTPResizeDialog::OnInitDialog();

	// set the default font for all dialog controls.
	SendMessageToDescendants(WM_SETFONT,
		(WPARAM)(HFONT)XTPFontManager()->GetFont());

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

	CXTPWindowRect rc(&m_wndPlaceHolder);
	ScreenToClient(&rc);

	m_wndTagCloud.Create(WS_BORDER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, rc, this, IDC_TAGCLOUD);

	m_bFocus   = m_wndTagCloud.IsFocusEnabled();
	m_bTooltip = m_wndTagCloud.IsTipEnabled();

	m_wndStyleList.InsertColumn(0, _T("Font Name"), LVCFMT_LEFT, 75);
	m_wndStyleList.InsertColumn(1, _T("Font Size"), LVCFMT_LEFT, 75);
	m_wndStyleList.InsertColumn(2, _T("Score"),     LVCFMT_LEFT, 75);

	RebuildTagCloudCtrl();
	RebuildTagStyleListCtrl();
	m_wndStyleList.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	UpdateData(FALSE);

	SetFlag(xtpResizeNoTransparentGroup);

	SetResize(IDC_TAGCLOUD,             XTP_ANCHOR_TOPLEFT,     XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_GBOX_STYLES,          XTP_ANCHOR_TOPRIGHT,    XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_LIST_STYLES,          XTP_ANCHOR_TOPRIGHT,    XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_BTN_STYLES_EDIT,      XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_BTN_STYLES_ADD,       XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_BTN_STYLES_DELETE,    XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_GBOX_TAG,             XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_BTN_TAG_EDIT,         XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_BTN_TAG_ADD,          XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_BTN_TAG_DELETE,       XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_GBOX_CONTROL,         XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_BTN_CONTROL_COLORS,     XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_CHK_CONTROL_TOOLTIP,  XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_CHK_CONTROL_FOCUS,    XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_COMBO_CONTROL_SORT,   XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_STATIC_CONTROL_SORT,  XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_BTN_CONTROL_RESET,    XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_CHK_CONTROL_ASC,      XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDCANCEL,                 XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);

	// reset recent colors list.
	CUIntArray arRecentColors;
	arRecentColors.Add(RGB(107, 199, 255));
	arRecentColors.Add(RGB( 33, 105, 198));
	arRecentColors.Add(RGB( 49, 162, 165));
	arRecentColors.Add(RGB(119, 185,   0));
	arRecentColors.Add(RGB(255, 152,  29));
	arRecentColors.Add(RGB( 66,  66,  66));
	arRecentColors.Add(RGB( 49,  49,  49));
	CXTPColorSelectorCtrl::SetRecentColors(arRecentColors);

	// update background colors for the tag cloud control.
//	m_wndTagCloud.SetBackColor(RGB(49, 49, 49));
//	m_wndTagCloud.SetBorderColor(RGB(0, 0, 0));
//	m_wndTagCloud.SetWindowPos(NULL, 0,0,0,0, SWP_NOMOVE|SWP_NOSIZE|SWP_FRAMECHANGED);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTagCloudDlg::RebuildTagStyleListCtrl()
{
	m_wndStyleList.DeleteAllItems();

	CClientDC dc(this);

	CXTPTagCloudStyleArray& arrStyles = XTPTabCloudStyleManager()->GetCloudStyleArray();

	for (int i = 0; i < arrStyles.GetSize(); ++i)
	{
		LOGFONT lf;
		arrStyles[i]->m_xtpFont.GetLogFont(&lf);

		CString strBuffer;
		strBuffer.Format(_T("%s"), lf.lfFaceName);
		m_wndStyleList.InsertItem(i, strBuffer);

		strBuffer.Format(_T("%d pt"), ::MulDiv(-lf.lfHeight, 72, dc.GetDeviceCaps(LOGPIXELSY)));
		m_wndStyleList.SetItemText(i, 1, strBuffer);

		strBuffer.Format(_T("%d"), arrStyles[i]->m_nScore);
		m_wndStyleList.SetItemText(i, 2, strBuffer);

		m_wndStyleList.SetItemData(i, (DWORD)arrStyles[i]->m_nScore);
	}

	int nMaxIndex = m_wndStyleList.GetItemCount() - 1;
	if (m_nSelItem > nMaxIndex)
		m_nSelItem = nMaxIndex;

	if (m_nSelItem != -1)
	{
		m_wndStyleList.SetItemState(m_nSelItem, LVIS_SELECTED, LVIS_SELECTED);
		m_wndStyleList.EnsureVisible(m_nSelItem, FALSE);
	}

	EnableButtons();
}

void CTagCloudDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTagCloudDlg::OnPaint() 
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
HCURSOR CTagCloudDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTagCloudDlg::OnChkTooltip() 
{
	m_bTooltip = !m_bTooltip;
	m_wndTagCloud.EnableTooltip(m_bTooltip);
	UpdateData(FALSE);
}

void CTagCloudDlg::OnChkFocus() 
{
	m_bFocus = !m_bFocus;
	m_wndTagCloud.EnableFocusRect(m_bFocus);
	UpdateData(FALSE);
}

void CTagCloudDlg::EnableButtons()
{
	m_btnStylesEdit.EnableWindow(m_nSelItem != -1);
	m_btnStylesDelete.EnableWindow(m_nSelItem != -1 && m_wndStyleList.GetItemCount() > 1);
	m_btnTagEdit.EnableWindow(m_pSelTag != NULL);
	m_btnTagDelete.EnableWindow(m_pSelTag != NULL);
}

void CTagCloudDlg::OnTagCloudSelChange(XTP_TAGCLOUDTAG* pTag)
{
	m_pSelTag = pTag;
	EnableButtons();
}

void CTagCloudDlg::OnTagCloudRightClk(XTP_TAGCLOUDTAG* pTag)
{
	CPoint point;
	::GetCursorPos(&point);

	CMenu menu;
	menu.LoadMenu(IDR_POPUP);

	CMenu* pPopup = menu.GetSubMenu(pTag ? 0 : 1);

	pPopup->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON,
		point.x, point.y, this);
}

void CTagCloudDlg::OnTagCloudDblClk(XTP_TAGCLOUDTAG* pTag)
{
	if (pTag)
	{
		OnBtnTagEdit();
	}
	else
	{
		OnBtnTagAdd();
	}
}

void CTagCloudDlg::OnItemChangedListStyles(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

    if (pNMListView->uChanged & LVIF_STATE)
	{
		if (pNMListView->uNewState & LVIS_SELECTED)
		{
			m_nSelItem = pNMListView->iItem;
		}
		else
		{
			m_nSelItem = -1;
		}
	}
	
	EnableButtons();
	*pResult = 0;
}

void CTagCloudDlg::OnTagEditTag() 
{
	OnBtnTagEdit();
}

void CTagCloudDlg::OnTagAddTag() 
{
	OnBtnTagAdd();
}

void CTagCloudDlg::OnTagDeleteTag() 
{
	OnBtnTagDelete();
}

void CTagCloudDlg::OnBtnStylesEdit() 
{
	CXTPTagCloudStyleArray& arrStyles = XTPTabCloudStyleManager()->GetCloudStyleArray();
	if (arrStyles.GetSize() == 0 || m_nSelItem == -1)
	{
		ASSERT(0);
		return;
	}

	CEditStyleDlg dlg(m_wndTagCloud.GetBackColor(), m_wndTagCloud.GetBorderColor(),
		_T("Edit Tag Style"), arrStyles[m_nSelItem], this);

	if (dlg.DoModal() == IDOK)
	{
		*arrStyles[m_nSelItem] = dlg.m_tagStyle;
		RebuildTagStyleListCtrl();
		m_wndTagCloud.RecalcLayout();
	}
}

void CTagCloudDlg::RebuildTagCloudCtrl(BOOL bRecalcLayout /*=TRUE*/)
{
	CXTPTagCloudStyleArray& arrStyles = XTPTabCloudStyleManager()->GetCloudStyleArray();
	INT_PTR nSize = arrStyles.GetSize();
	if (nSize == 0)
	{
		ASSERT(0);
		return;
	}

	m_pSelTag = NULL;
	m_wndTagCloud.RemoveAll();
	
	srand(1);

	for (int i = 0; i < _countof(tagName); ++i)
	{
		m_wndTagCloud.AddTag(new XTP_TAGCLOUDTAG(
			tagName[i], int(rand() % nSize + 1)));
	}

	if (bRecalcLayout)
	{
		m_wndTagCloud.RecalcLayout();
	}
}

void CTagCloudDlg::OnBtnStylesAdd() 
{
	CXTPTagCloudStyleArray& arrStyles = XTPTabCloudStyleManager()->GetCloudStyleArray();
	INT_PTR nSize = arrStyles.GetSize();
	if (nSize == 0)
	{
		ASSERT(0);
		return;
	}

	CEditStyleDlg dlg(m_wndTagCloud.GetBackColor(), m_wndTagCloud.GetBorderColor(),
		_T("Add Tag Style"), static_cast<int>(nSize + 1), this);

	if (dlg.DoModal() == IDOK)
	{
		XTPTabCloudStyleManager()->AddStyle(
			new CXTPTagCloudStyle(dlg.m_tagStyle));

		nSize = arrStyles.GetSize();

		RebuildTagCloudCtrl();
		RebuildTagStyleListCtrl();
	}
}

void CTagCloudDlg::OnBtnStylesDelete() 
{
	if (m_nSelItem == -1)
		return;

	if (AfxMessageBox(_T("Are you sure you want to delete the selected style?"), MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
		int nScore = (int)m_wndStyleList.GetItemData(m_nSelItem);
		if (XTPTabCloudStyleManager()->RemoveStyle(nScore))
		{
			RebuildTagCloudCtrl();
			RebuildTagStyleListCtrl();
		}
	}
}

void CTagCloudDlg::OnBtnTagEdit() 
{
	XTP_TAGCLOUDTAG* pTag = m_wndTagCloud.GetCurSel();

	CEditTagDlg dlg(m_wndTagCloud.GetBackColor(), m_wndTagCloud.GetBorderColor(),
		_T("Edit Tag"), pTag, this);

	if (dlg.DoModal() == IDOK)
	{
		pTag->strItem = dlg.m_strTagName;
		pTag->nScore = dlg.GetScore();
		m_wndTagCloud.RecalcLayout();
	}
}

void CTagCloudDlg::OnBtnTagAdd() 
{
	CEditTagDlg dlg(m_wndTagCloud.GetBackColor(), m_wndTagCloud.GetBorderColor(),
		_T("Add New Tag"), NULL, this);

	if (dlg.DoModal() == IDOK)
	{
		XTP_TAGCLOUDTAG* pTag = new XTP_TAGCLOUDTAG(
			dlg.m_strTagName, dlg.GetScore());

		m_wndTagCloud.AddTag(pTag);
		m_wndTagCloud.RecalcLayout();
	}
}

void CTagCloudDlg::OnBtnTagDelete() 
{
	XTP_TAGCLOUDTAG* pTag = m_wndTagCloud.GetCurSel();
	if (pTag)
	{
		CString strBuffer;
		strBuffer.Format(_T("Are you sure you want to delete the tag \"%s\"?"), pTag->strItem);
		
		if (AfxMessageBox(strBuffer, MB_ICONQUESTION|MB_YESNO) == IDYES)
		{
			m_wndTagCloud.RemoveTag(m_wndTagCloud.GetCurSel());
			m_wndTagCloud.RecalcLayout();
		}
	}
}

void CTagCloudDlg::Sort(XTPTagCloudSort nSort)
{
	m_nSort = nSort;
	m_wndTagCloud.SetSortOrder((XTPTagCloudSort)m_nSort, m_bAsc);
	m_chkAsc.EnableWindow((XTPTagCloudSort)m_nSort != xtpTagCloudNone);
	UpdateData(FALSE);
}

void CTagCloudDlg::OnSelendOkComboControlSort() 
{
	UpdateData();
	Sort((XTPTagCloudSort)m_nSort);
}

void CTagCloudDlg::OnBtnControlColors() 
{
	CEditTagCloudDlg dlg(m_wndTagCloud, this);

	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_nStyle == 0)
		{
			m_wndTagCloud.SetBackColor(dlg.m_clrLight);
		}
		else
		{
			CXTPPaintManagerColorGradient clrBack(dlg.m_clrLight, dlg.m_clrDark);
			m_wndTagCloud.SetBackColor(clrBack, (dlg.m_nStyle == 2));
		}
		
		m_wndTagCloud.SetBorderColor(dlg.m_clrBorder);
		m_wndTagCloud.SetMargin(dlg.m_nMargin);
		m_wndTagCloud.SetPadding(dlg.m_nPadding);
		m_wndTagCloud.RecalcLayout();
		m_wndTagCloud.SetWindowPos(NULL, 0,0,0,0, SWP_NOMOVE|SWP_NOSIZE|SWP_FRAMECHANGED);
	}
}

void CTagCloudDlg::OnBtnControlReset() 
{
	XTPTabCloudStyleManager()->InitDefaultStyles();
	RebuildTagCloudCtrl(FALSE);
	RebuildTagStyleListCtrl();

	m_wndTagCloud.RestoreDefaults();
	m_wndTagCloud.RecalcLayout();
	m_wndTagCloud.SetWindowPos(NULL, 0,0,0,0, SWP_NOMOVE|SWP_NOSIZE|SWP_FRAMECHANGED);

	m_nSort = 0;
	m_bAsc = TRUE;
	m_bTooltip = TRUE;
	m_bFocus = TRUE;
	UpdateData(FALSE);

	EnableButtons();
	m_chkAsc.EnableWindow(FALSE);
}

void CTagCloudDlg::OnControlTooltip() 
{
	OnChkTooltip();
}

void CTagCloudDlg::OnControlFocus() 
{
	OnChkFocus();
}

void CTagCloudDlg::OnControlSortOrderNone()
{
	Sort(xtpTagCloudNone);
}

void CTagCloudDlg::OnControlSortOrderByName() 
{
	Sort(xtpTagCloudAlpha);
}

void CTagCloudDlg::OnControlSortOrderByScore() 
{
	Sort(xtpTagCloudNumeric);
}

void CTagCloudDlg::OnControlEditCloudColors() 
{
	OnBtnControlColors();
}

void CTagCloudDlg::OnControlResetAll() 
{
	OnBtnControlReset();	
}

void CTagCloudDlg::OnChkControlAsc() 
{
	OnSelendOkComboControlSort();
}

void CTagCloudDlg::OnDblClkListStyles(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
{
	OnBtnStylesEdit();
	*pResult = 0;
}

void CTagCloudDlg::OnInitMenuPopup(CMenu* pMenu, UINT nIndex, BOOL bSysMenu) 
{
	CCmdUI cmdUI;
    cmdUI.m_nIndexMax = pMenu->GetMenuItemCount();
	
    for (UINT n = 0; n < cmdUI.m_nIndexMax; ++n)
    {
        CMenu* pSubMenu = pMenu->GetSubMenu(n);
        if (pSubMenu == NULL)
        {
            cmdUI.m_nIndex = n;
            cmdUI.m_nID = pMenu->GetMenuItemID(n);
            cmdUI.m_pMenu = pMenu;
            cmdUI.DoUpdate(this, FALSE);
        }
    }
}

void CTagCloudDlg::OnUpdateControlTooltip(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bTooltip);
}

void CTagCloudDlg::OnUpdateControlFocus(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bFocus);
}

void CTagCloudDlg::OnUpdateControlSortOrderNone(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_wndTagCloud.GetSortOrder() == xtpTagCloudNone);
}

void CTagCloudDlg::OnUpdateControlSortOrderByName(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_wndTagCloud.GetSortOrder() == xtpTagCloudAlpha);
}

void CTagCloudDlg::OnUpdateControlSortOrderByScore(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_wndTagCloud.GetSortOrder() == xtpTagCloudNumeric);
}

void CTagCloudDlg::OnControlSortOrderAscending() 
{
	m_bAsc = !m_bAsc;
	Sort((XTPTagCloudSort)m_nSort);

	m_chkAsc.SetCheck(m_bAsc);
	m_chkAsc.RedrawWindow();
}

void CTagCloudDlg::OnUpdateControlSortOrderAscending(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bAsc);
	pCmdUI->Enable(m_wndTagCloud.GetSortOrder() != xtpTagCloudNone);
}
