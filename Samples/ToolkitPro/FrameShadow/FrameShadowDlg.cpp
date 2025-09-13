// FrameShadowDlg.cpp
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
#include "FrameShadow.h"
#include "FrameShadowDlg.h"

#define _USE_MATH_DEFINES
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const float Pi = static_cast<float>(acos(-1.f));

class CToolWindow : public CWnd
{
public:
	explicit CToolWindow(int nNumber)
		: m_nNumber(nNumber)
	{
	}

	BOOL Create(CWnd* pOwner)
	{
		ASSERT_VALID(pOwner);

		LPCTSTR lpClassName = AfxRegisterWndClass(0, LoadCursor(NULL, IDC_ARROW), 
			reinterpret_cast<HBRUSH>(COLOR_WINDOW));

		CString strTitle;
		strTitle.Format(_T("Tool Window #%i"), m_nNumber);
		BOOL bSuccess = CWnd::CreateEx(WS_EX_TOOLWINDOW | WS_EX_TOPMOST, lpClassName,
			strTitle, WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_THICKFRAME, CW_USEDEFAULT, CW_USEDEFAULT,
			XTP_DPI_X(250), XTP_DPI_Y(250), pOwner->m_hWnd, NULL);
		return bSuccess;
	}

protected:
	virtual void PostNcDestroy()
	{
		delete this;
	}

private:
	int m_nNumber;
};


/////////////////////////////////////////////////////////////////////////////
// CFrameShadowDlg dialog

CFrameShadowDlg::CFrameShadowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFrameShadowDlg::IDD, pParent)
	, m_nToolWndCounter(0)
{
	//{{AFX_DATA_INIT(CFrameShadowDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	XTPFrameShadowManager()->SetDefaultOuterSize(XTP_DPI_Y(30));
	XTPFrameShadowManager()->SetDefaultInnerSize(XTP_DPI_Y(30));
	XTPFrameShadowManager()->SetDefaultColor(RGB(0, 0x80, 0xff));
	XTPFrameShadowManager()->SetDefaultTransparency(0x80);
}

void CFrameShadowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFrameShadowDlg)
	DDX_Control(pDX, IDC_SLIDER_OUTER_SIZE, m_ctlOuterSize);
	DDX_Control(pDX, IDC_SLIDER_INNER_SIZE, m_ctlInnerSize);
	DDX_Control(pDX, IDC_SLIDER_ANGLE, m_ctlAngle);
	DDX_Control(pDX, IDC_SLIDER_DISTANCE, m_ctlDistance);
	DDX_Control(pDX, IDC_SLIDER_RED, m_ctlRed);
	DDX_Control(pDX, IDC_SLIDER_GREEN, m_ctlGreen);
	DDX_Control(pDX, IDC_SLIDER_BLUE, m_ctlBlue);
	DDX_Control(pDX, IDC_SLIDER_TRANSPARENCY, m_ctlTransparency);
	DDX_Control(pDX, IDC_CHECK_BORDERLESS, m_ctlBorderless);
	DDX_Control(pDX, IDC_CHECK_SIZEABLETOOLWND, m_ctlSizeableToolWindows);
	DDX_Control(pDX, IDC_SLIDER_CENTER_POS, m_ctlCenterPos);
	DDX_Control(pDX, IDC_SLIDER_INNER_INTENSITY, m_ctlInnerIntensity);
	DDX_Control(pDX, IDC_SLIDER_CENTER_INTENSITY, m_ctlCenterIntensity);
	DDX_Control(pDX, IDC_SLIDER_OUTER_INTENSITY, m_ctlOuterIntensity);
	DDX_Control(pDX, IDC_CHECK_FLAG_DISABLED, m_ctlFlagDisabled);
	DDX_Control(pDX, IDC_CHECK_FLAG_INVISIBLE, m_ctlFlagInvisible);
	DDX_Control(pDX, IDC_CHECK_FLAG_NOT_RESIZEABLE, m_ctlFlagNotResizeable);
	DDX_Control(pDX, IDC_CHECK_FLAG_DISABLED_TSS, m_ctlFlagDisabledTss);
	DDX_Control(pDX, IDC_CHECK_FLAG_INVISIBLE_TSS, m_ctlFlagInvisibleTss);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFrameShadowDlg, CDialog)
	//{{AFX_MSG_MAP(CFrameShadowDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_ADD_TOOL_WINDOW, OnBnClickedButtonAddToolWindow)
	ON_BN_CLICKED(IDC_CHECK_BORDERLESS, OnBnClickedCheckBorderless)
	ON_BN_CLICKED(IDC_CHECK_SIZEABLETOOLWND, OnBnClickedSizeableToolWindows)
	ON_BN_CLICKED(IDC_RADIO_SAMPLE1, OnBnClickedRadioSample1)
	ON_BN_CLICKED(IDC_RADIO_SAMPLE2, OnBnClickedRadioSample2)
	ON_BN_CLICKED(IDC_RADIO_SAMPLE3, OnBnClickedRadioSample3)
	ON_BN_CLICKED(IDC_RADIO_SAMPLE4, OnBnClickedRadioSample4)
	ON_BN_CLICKED(IDC_CHECK_FLAG_DISABLED, OnBnClickedCheckFlags)
	ON_BN_CLICKED(IDC_CHECK_FLAG_INVISIBLE, OnBnClickedCheckFlags)
	ON_BN_CLICKED(IDC_CHECK_FLAG_NOT_RESIZEABLE, OnBnClickedCheckFlags)
	ON_BN_CLICKED(IDC_CHECK_FLAG_DISABLED_TSS, OnBnClickedCheckFlags)
	ON_BN_CLICKED(IDC_CHECK_FLAG_INVISIBLE_TSS, OnBnClickedCheckFlags)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFrameShadowDlg message handlers

BOOL CFrameShadowDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	XTPFrameShadowManager()->EnableShadow(this);

	m_ctlOuterSize.SetRange(0, XTP_DPI_Y(300));
	m_ctlInnerSize.SetRange(0, XTP_DPI_Y(300));

	m_ctlAngle.SetRange(0, 360);
	m_ctlDistance.SetRange(0, 300);
	
	m_ctlRed.SetRange(0, 255);

	m_ctlGreen.SetRange(0, 255);
	m_ctlBlue.SetRange(0, 255);
	m_ctlTransparency.SetRange(0, 255);

	m_ctlCenterPos.SetRange(0, 100);
	m_ctlCenterPos.SetPos(50);

	m_ctlInnerIntensity.SetRange(0, 100);
	m_ctlInnerIntensity.SetPos(100);

	m_ctlCenterIntensity.SetRange(0, 100);
	m_ctlCenterIntensity.SetPos(50);
	
	m_ctlOuterIntensity.SetRange(0, 100);
	m_ctlOuterIntensity.SetPos(0);

	m_ctlSizeableToolWindows.SetCheck(BST_CHECKED);

	SyncControls();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFrameShadowDlg::SyncControls()
{
	CXTPFrameShadowManager* pFrameShadowManager = XTPFrameShadowManager();
	pFrameShadowManager->FreezeUpdates();

	m_ctlOuterSize.SetPos(pFrameShadowManager->GetDefaultOuterSize());
	m_ctlInnerSize.SetPos(pFrameShadowManager->GetDefaultInnerSize());

	CPoint ptOffset = pFrameShadowManager->GetDefaultOffset();
	float nHyp = static_cast<float>(sqrt(static_cast<float>(ptOffset.x * ptOffset.x + ptOffset.y * ptOffset.y)));
	m_ctlDistance.SetRange(0, 300);
	m_ctlDistance.SetPos(static_cast<int>(nHyp));
	m_ctlAngle.SetPos(static_cast<int>((atan(nHyp / ptOffset.x) * 180) / Pi));

	m_ctlRed.SetPos(GetRValue(pFrameShadowManager->GetDefaultColor()));
	m_ctlGreen.SetPos(GetGValue(pFrameShadowManager->GetDefaultColor()));
	m_ctlBlue.SetPos(GetBValue(pFrameShadowManager->GetDefaultColor()));
	m_ctlTransparency.SetPos(pFrameShadowManager->GetDefaultTransparency());

	UINT nBlendingOptionsCount = pFrameShadowManager->GetDefaultBlendingOptions(NULL, NULL);
	if (3 == nBlendingOptionsCount)
	{
		CArray<float, float&> arrFactors, arrPositions;
		arrFactors.SetSize(nBlendingOptionsCount);
		arrPositions.SetSize(nBlendingOptionsCount);
		pFrameShadowManager->GetDefaultBlendingOptions(arrFactors.GetData(), arrPositions.GetData());
		m_ctlCenterPos.SetPos(static_cast<int>(arrPositions.GetAt(1) * 100));
		m_ctlOuterIntensity.SetPos(static_cast<int>(arrFactors.GetAt(0) * 100));
		m_ctlCenterIntensity.SetPos(static_cast<int>(arrFactors.GetAt(1) * 100));
		m_ctlInnerIntensity.SetPos(static_cast<int>(arrFactors.GetAt(2) * 100));
	}

	pFrameShadowManager->FreezeUpdates(FALSE);
}

void CFrameShadowDlg::SetBorderless(
	BOOL bBorderless /*= TRUE*/,
	BOOL bUpdateCheckbox /*= FALSE*/)
{
	DWORD dwBorderStyles = WS_BORDER | WS_CAPTION | DS_MODALFRAME | DS_3DLOOK | WS_SYSMENU;
	DWORD dwBorderStylesEx = WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE;

	if (bBorderless)
	{
		ModifyStyleEx(dwBorderStylesEx, 0);
		ModifyStyle(dwBorderStyles, 0, SWP_DRAWFRAME);
		
	}
	else
	{
		ModifyStyle(0, dwBorderStyles);
		ModifyStyleEx(0, dwBorderStylesEx, SWP_DRAWFRAME);
	}

	if (bUpdateCheckbox)
	{
		m_ctlBorderless.SetCheck(bBorderless ? BST_CHECKED : BST_UNCHECKED);
	}
}

void CFrameShadowDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFrameShadowDlg::OnPaint() 
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
HCURSOR CFrameShadowDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CFrameShadowDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	switch (pScrollBar->GetDlgCtrlID())
	{
	case IDC_SLIDER_OUTER_SIZE:
		XTPFrameShadowManager()->SetGlobalOuterSize(m_ctlOuterSize.GetPos());
		break;
	case IDC_SLIDER_INNER_SIZE:
		XTPFrameShadowManager()->SetGlobalInnerSize(m_ctlInnerSize.GetPos());
		break;
	case IDC_SLIDER_ANGLE:
	case IDC_SLIDER_DISTANCE:
		{
			int nDist = m_ctlDistance.GetPos();
			int nAngle = m_ctlAngle.GetPos();
			CPoint ptOffset(
				static_cast<int>(cos((Pi * nAngle) / 180) * nDist),
				static_cast<int>(sin((Pi * nAngle) / 180) * nDist));
			XTPFrameShadowManager()->SetGlobalOffset(ptOffset);
		}
		break;
	case IDC_SLIDER_RED:
	case IDC_SLIDER_GREEN:
	case IDC_SLIDER_BLUE:
		{
			BYTE bRed = m_ctlRed.GetPos() & 0xff;
			BYTE bGreen = m_ctlGreen.GetPos() & 0xff;
			BYTE bBlue = m_ctlBlue.GetPos() & 0xff;
			XTPFrameShadowManager()->SetGlobalColor(RGB(bRed, bGreen, bBlue));
		}
		break;
	case IDC_SLIDER_TRANSPARENCY:
		XTPFrameShadowManager()->SetGlobalTransparency(m_ctlTransparency.GetPos() & 0xff);
		break;
	case IDC_SLIDER_CENTER_POS:
	case IDC_SLIDER_INNER_INTENSITY:
	case IDC_SLIDER_CENTER_INTENSITY:
	case IDC_SLIDER_OUTER_INTENSITY:
		{
			float nFactors[] =
			{
				static_cast<float>(m_ctlInnerIntensity.GetPos()) / 100,
				static_cast<float>(m_ctlCenterIntensity.GetPos()) / 100,
				static_cast<float>(m_ctlOuterIntensity.GetPos()) / 100,
			};
			float nPositions[] = { 0, static_cast<float>(m_ctlCenterPos.GetPos()) / 100, 1.f };
			XTPFrameShadowManager()->SetGlobalBlendingOptions(_countof(nFactors), nFactors, nPositions);
		}
		break;
	default:
		CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
		break;
	}
}

void CFrameShadowDlg::OnBnClickedButtonAddToolWindow()
{
	CToolWindow* pToolWindow = new CToolWindow(++m_nToolWndCounter);
	if (pToolWindow->Create(this))
	{
		XTPFrameShadowManager()->EnableShadow(pToolWindow);
	}
	else
	{
		delete pToolWindow;
	}
}


void CFrameShadowDlg::OnBnClickedCheckBorderless()
{
	DWORD dwBorderStyles = WS_BORDER | WS_CAPTION | DS_MODALFRAME | DS_3DLOOK | WS_SYSMENU;
	DWORD dwBorderStylesEx = WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE;

	if (BST_CHECKED == m_ctlBorderless.GetCheck())
	{
		SetBorderless();
	}
	else if (BST_UNCHECKED == m_ctlBorderless.GetCheck())
	{
		SetBorderless(FALSE);
	}
}

void CFrameShadowDlg::OnBnClickedSizeableToolWindows()
{
	BOOL bSizeable = (BST_CHECKED == m_ctlSizeableToolWindows.GetCheck());

	POSITION pos = XTPFrameShadowManager()->GetFirstShadowPosition();
	while (NULL != pos)
	{
		CXTPFrameShadow* pShadow = XTPFrameShadowManager()->GetNextShadow(pos);
		ASSERT(NULL != pShadow);

		LONG_PTR exStyle = ::GetWindowLongPtr(pShadow->GetOwner(), GWL_EXSTYLE);
		if (0 != (exStyle & WS_EX_TOOLWINDOW))
		{
			LONG_PTR style = ::GetWindowLongPtr(pShadow->GetOwner(), GWL_STYLE);
			if (bSizeable)
			{
				style |= WS_SIZEBOX;
			}
			else
			{
				style &= ~WS_SIZEBOX;
			}

			::SetWindowLongPtr(pShadow->GetOwner(), GWL_STYLE, style);
		}
	}
}

void CFrameShadowDlg::OnBnClickedRadioSample1()
{
	CXTPFrameShadowManager* pFrameShadowManager = XTPFrameShadowManager();
	pFrameShadowManager->FreezeUpdates();

	pFrameShadowManager->SetGlobalOuterSize(30);
	pFrameShadowManager->SetGlobalInnerSize(0);
	pFrameShadowManager->SetGlobalOffset(CPoint(0, 0));
	pFrameShadowManager->SetGlobalColor(RGB(0, 0xff, 0xff));
	pFrameShadowManager->SetGlobalTransparency(0xff);

	float arrFactors[] = { 0.f, 1.f, 0.f };
	float arrPositions[] = { 0.f, 0.5f, 1.f };
	pFrameShadowManager->SetGlobalBlendingOptions(_countof(arrFactors), arrFactors, arrPositions);

	SyncControls();

	pFrameShadowManager->FreezeUpdates(FALSE);
}

void CFrameShadowDlg::OnBnClickedRadioSample2()
{
	CXTPFrameShadowManager* pFrameShadowManager = XTPFrameShadowManager();
	pFrameShadowManager->FreezeUpdates();

	pFrameShadowManager->SetGlobalOuterSize(100);
	pFrameShadowManager->SetGlobalInnerSize(0);
	pFrameShadowManager->SetGlobalOffset(CPoint(0, 0));
	pFrameShadowManager->SetGlobalColor(GetSysColor(COLOR_BTNFACE));
	pFrameShadowManager->SetGlobalTransparency(0xff);

	float arrFactors[] = { 1.f, 0.5f, 0.f };
	float arrPositions[] = { 0.f, 0.5f, 1.f };
	pFrameShadowManager->SetGlobalBlendingOptions(_countof(arrFactors), arrFactors, arrPositions);

	SetBorderless(TRUE, TRUE);
	SyncControls();

	pFrameShadowManager->FreezeUpdates(FALSE);
}

void CFrameShadowDlg::OnBnClickedRadioSample3()
{
	CXTPFrameShadowManager* pFrameShadowManager = XTPFrameShadowManager();
	pFrameShadowManager->FreezeUpdates();

	pFrameShadowManager->SetGlobalOuterSize(115);
	pFrameShadowManager->SetGlobalInnerSize(300);
	pFrameShadowManager->SetGlobalOffset(CPoint(30, 30));
	pFrameShadowManager->SetGlobalColor(RGB(0xff, 0xff, 0xff));
	pFrameShadowManager->SetGlobalTransparency(0xff);

	float arrFactors[] = { 0.5f, 0.5f, 0.f };
	float arrPositions[] = { 0.f, 0.75f, 1.f };
	pFrameShadowManager->SetGlobalBlendingOptions(_countof(arrFactors), arrFactors, arrPositions);

	SyncControls();

	pFrameShadowManager->FreezeUpdates(FALSE);
}

void CFrameShadowDlg::OnBnClickedRadioSample4()
{
	CXTPFrameShadowManager* pFrameShadowManager = XTPFrameShadowManager();
	pFrameShadowManager->FreezeUpdates();

	pFrameShadowManager->SetGlobalOuterSize(13);
	pFrameShadowManager->SetGlobalInnerSize(3);
	pFrameShadowManager->SetGlobalOffset(CPoint(3, 3));
	pFrameShadowManager->SetGlobalColor(RGB(0, 0, 0));
	pFrameShadowManager->SetGlobalTransparency(0xff);

	float arrFactors[] = { 1.f, 0.25f, 0.f };
	float arrPositions[] = { 0.f, 0.75f, 1.f };
	pFrameShadowManager->SetGlobalBlendingOptions(_countof(arrFactors), arrFactors, arrPositions);

	SetBorderless(TRUE, TRUE);
	SyncControls();

	pFrameShadowManager->FreezeUpdates(FALSE);
}

void CFrameShadowDlg::OnBnClickedCheckFlags()
{
	int nFlags = 0;
	if (BST_CHECKED == m_ctlFlagDisabled.GetCheck())
		nFlags |= xtpFrameShadowsDisabled;
	if (BST_CHECKED == m_ctlFlagInvisible.GetCheck())
		nFlags |= xtpFrameShadowsInvisible;
	if (BST_CHECKED == m_ctlFlagNotResizeable.GetCheck())
		nFlags |= xtpFrameShadowsNotResizeable;
	if (BST_CHECKED == m_ctlFlagDisabledTss.GetCheck())
		nFlags |= xtpFrameShadowsDisabledInTSS;
	if (BST_CHECKED == m_ctlFlagInvisibleTss.GetCheck())
		nFlags |= xtpFrameShadowsInvisibleInTSS;

	XTPFrameShadowManager()->SetFlags(nFlags);
	int f = XTPFrameShadowManager()->GetFlags();

	BOOL bEnabled = (0 == (nFlags & xtpFrameShadowsDisabled));
	m_ctlFlagInvisible.EnableWindow(bEnabled);
	m_ctlFlagNotResizeable.EnableWindow(bEnabled);
	m_ctlFlagDisabledTss.EnableWindow(bEnabled);
	m_ctlFlagInvisibleTss.EnableWindow(bEnabled);
}